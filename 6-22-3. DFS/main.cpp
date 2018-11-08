/*
22.2 Breadth-first search
*/

#include <vector>
#include <list>
#include <queue>
#include <stack>

#include <iostream>
#include <stdio.h>
#include <utility>      
#include <climits>

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
            cout<< i->value <<endl;
        }
    }
    
    
    void DFSReset(){
        for (auto i: Vertex){
            i->color = white;
            i->predecessor = nullptr;
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
    
    void DFSI(){
        DFSReset();
        for (auto i : Vertex){
            if (i->color == white){
                DFSIter(i);
            }
        }   
    }
    
    void DFSIter(GraphNode* source){
        //Exercise 22.3-7
        
        stack<GraphNode*> data;
        GraphNode* curr = source;
        
        ++t;
        curr->discovery = t;
        curr->color = grey;

        bool begin = true;

        while (1){
            
            while ((int) curr->Adjlist.size() != 0){
                //curr has child
                
                list<GraphNode*>::iterator iter = curr->Adjlist.begin();
                
                bool haswhite = false;
                
                while (iter != curr->Adjlist.end()){
                    
                    if ((*iter)->color == white){
                        data.push(curr);
                        curr = (*iter);
                        
                        ++t;
                        curr->discovery = t;
                        curr->color = grey;
                        haswhite = true;        
                        break;
                    }
                    
                    iter++;
                    
                }
                
                if (haswhite == false){
                    break;
                }
                
            } //curr has no white child !
            
            ++t;
            curr->color = black;
            curr->finish = t;
            cout<<curr->value<<", "<<curr->discovery<<"/"<<curr->finish<<endl;
            
            if ((int)data.size() == 0){
                break;
            }
            
            curr = data.top();
            data.pop();
            
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
    
    ~Graph(){}
    
private:
    vector <GraphNode*> Vertex;
    vector <vector<int>> Adjmatrix;
    int t = 0;
};


int main()
{

    GraphNode* u = new GraphNode (21);
    GraphNode* v = new GraphNode (22);
    GraphNode* w = new GraphNode (23);
    GraphNode* x = new GraphNode (24);
    GraphNode* y = new GraphNode (25);
    GraphNode* z = new GraphNode (26);
    
    Graph myGraph ({u,v,w,x,y,z}, 
                   {{u,v},{u,x},{v,y},{w,y},{w,z},{x,v},{y,x},{z,z}},
                   true,
                   false);
    
    myGraph.DFS();
    myGraph.DFSI();
    return 0;
}

