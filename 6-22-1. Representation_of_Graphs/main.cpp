/*
22.1 Representation of Graph
*/

#include <vector>
#include <list>
#include <iostream>
#include <stdio.h>
#include <utility>      
#include <map>

using namespace std;

class GraphNode{
public:
    int value;
    bool discovered = false;
    bool visited = false;
    list<GraphNode*> Adjlist;
    
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
        const vector<GraphNode*> &_Vertex = {}, const vector<pair<GraphNode*, GraphNode*>> _Edge = {}, bool _useList = true
    ){
        setVertex (_Vertex, _useList);
        setEdge (_Edge, _useList);
        
    }
    
    void setVertex(const vector<GraphNode*> &_Vertex, bool _useList = true){
        
        if (_useList){
            Vertex = _Vertex;
        } else {
            vector<int> nil (_Vertex.size(),0);
            Adjmatrix = vector <vector<int>> (Vertex.size(), nil);
        }

    }
    
    void setEdge(const vector<pair<GraphNode*, GraphNode*>> _Edge, bool _useList = true){
        
        if (_useList){
            for (auto i : _Edge){
                i.first -> Adjlist.push_back(i.second);
            }
        } else {
            //trouble
        }

    }
    
    void setMatrix(const vector<pair<GraphNode*, GraphNode*>> _Edge){
        
    }
    
    void transpose (){
        
    //Exercise 22.1-3
        
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
    
    void toString(){
        for (auto i : Vertex){
            
            cout<<i->value<<"->";
            
            for (auto j : i->Adjlist){
                cout<<j->value<<"->";
            }
            
            cout<<endl;
            
        }
    }
    
    ~Graph(){}
    
private:
    vector <GraphNode*> Vertex;
    vector <vector<int>> Adjmatrix;
};


int main()
{
    
    GraphNode* r = new GraphNode (18);
    GraphNode* s = new GraphNode (19);
    GraphNode* t = new GraphNode (20);
    GraphNode* u = new GraphNode (21);
    GraphNode* v = new GraphNode (22);
    GraphNode* w = new GraphNode (23);
    GraphNode* x = new GraphNode (24);
    GraphNode* y = new GraphNode (25);
    
    Graph myGraph ({r,s,t,u,v,w,x,y}, 
                   {{r, s}, {r, v}, {s, w}, {t, w}, {t, x}, {t, u}, {u, x}, {w, x}, {x,y}});

    myGraph.toString();
    myGraph.transpose();
    cout<<"transpose"<<endl;
    
    myGraph.toString();
    
    return 0;
}



