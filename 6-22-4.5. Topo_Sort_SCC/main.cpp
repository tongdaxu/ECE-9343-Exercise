/*
22.3-4 Topoiogical Sort and SCC
*/

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>

#include <iostream>
#include <stdio.h>
#include <utility>      
#include <climits>
#include <algorithm> 

using namespace std;

const int white = 0;
const int grey = 1;
const int black = 2;

class GraphNode{
public:
    int value;
    bool visited = false;
    list<GraphNode*> Adjlist;
    
    //Search Related
    GraphNode* predecessor = nullptr;
    list <GraphNode*> descendant;
    int discovery = INT_MAX;
    int finish = INT_MAX;
    int color = white;
    
    GraphNode(int _value){
    //well you can't declare it to be explicit    
        value = _value;
    }
    
    ~GraphNode(){}

private:

};

bool compare (GraphNode* LHS, GraphNode* RHS){
    
    if (LHS->finish > RHS->finish) {
        return true;
    } else {
        return false;
    }
    
}

class Graph{
//adjacency list graph
public:

    Graph(
        const vector<GraphNode*> &_Vertex = {}, const vector<pair<GraphNode*, GraphNode*>> _Edge = {}, bool _useList = true, bool _undirected = true
    ){
        setVertex (_Vertex, _useList);
        setEdge (_Edge, _useList, _undirected);
        
    }
    
    void setVertex(const vector<GraphNode*> &_Vertex, bool _useList){
        
        if (_useList){
            Vertex = _Vertex;
        } else {
            vector<int> nil (_Vertex.size(),0);
            Adjmatrix = vector <vector<int>> (Vertex.size(), nil);
        }
    }
    
    void setEdge(const vector<pair<GraphNode*, GraphNode*>> _Edge, bool _useList, bool _undirected){
        
        if (_useList){
            for (auto i : _Edge){
                i.first -> Adjlist.push_back(i.second);
                
                // if it is an undirected graph, add twice
                if (_undirected){
                    i.second -> Adjlist.push_back(i.first);   
                }
            }
        } else {
            //trouble
        }

    }
    
    void toString(){
        for (auto i : Vertex){
            
            cout<<i->value<<"->";
            
            for (auto j : i->Adjlist){
                cout<<j->value<<"->";
            }
            
            cout<<endl;
            
        }
    }
    
    void DFSReset(){
        for (auto i: Vertex){
            i->color = white;
            i->predecessor = nullptr;
            i->descendant.clear();
        }
        t = 0;
    }
    
    void DFS(){
        
        DFSReset();
        for (auto i : Vertex){
            if (i->color == white){
                DFSVisit(i);
            }
        }    
    }
    
    void DFSVisit(GraphNode* source){
        ++t;
        source->discovery = t;
        source->color = grey;
        
        for (auto i : source->Adjlist){
            
            if (i->color == white){
                i->predecessor = source;
                source->descendant.push_back(i);
                DFSVisit(i);
            }
        }
        
        source->color = black;
        ++t;
        source->finish = t;
        cout<<source->value<<", "<<source->discovery<<"/"<<source->finish<<endl;

    }
    
    void transpose (){
        
        list<GraphNode*> init= {};
        map <GraphNode*, list<GraphNode*>> newAdjlist;
        for (auto i : Vertex){
            newAdjlist[i] = {};
        }
        
        for (auto i : Vertex){
            for (auto j : i->Adjlist){
             (newAdjlist[j]).push_back(i);   
            }
        }
        
        for (auto i : Vertex){
            i->Adjlist = newAdjlist[i]; 
        }
        
    }
    
    void topoSort(){
        sort(Vertex.begin(), Vertex.end(), compare);
    }
    
    void SCC(){
        DFS();
        topoSort();
        transpose();
        DFS();
    }
    
    void DFSTree(){
        
        for (auto i : Vertex){
            if (i->predecessor == nullptr){
                cout<<"Tree element: ";
                DFSTreeAid(i);
                cout<<endl;
            }
        }
        
    }
    
    void DFSTreeAid(GraphNode* root){
        
        cout<<root->value<<", ";
        
        for (auto j : root->descendant){
            DFSTreeAid(j);
        }
    }
    
    ~Graph(){}
    
private:
    vector <GraphNode*> Vertex;
    vector <vector<int>> Adjmatrix;
    int t = 0;
};


int main()
{

    GraphNode* a = new GraphNode (1);
    GraphNode* b = new GraphNode (2);
    GraphNode* c = new GraphNode (3);
    GraphNode* d = new GraphNode (4);
    GraphNode* e = new GraphNode (5);
    GraphNode* f = new GraphNode (6);
    GraphNode* g = new GraphNode (7);
    GraphNode* h = new GraphNode (8);
    
    Graph myGraph ({a,b,c,d,e,f,g,h}, 
                   {{a,b},{b,e},{b,f},{b,c},{c,d},{c,g},{d,c},{d,h},
                   {e,a},{e,f},{f,g},{g,f},{g,h},{h,h}},
                   true,
                   false);
    
    myGraph.SCC();
    myGraph.DFSTree();
    return 0;
}



