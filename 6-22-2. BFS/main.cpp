/*
22.2 Breadth-first search
*/

#include <vector>
#include <list>
#include <queue>

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
    bool discovered = false;
    bool visited = false;
    list<GraphNode*> Adjlist;
    
    //Search Related
    GraphNode* predecessor = nullptr;
    list <GraphNode*> descendant;
    int distance = INT_MAX;
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
    
    void resetBFS(){
        for (auto i : Vertex){
            i->distance = INT_MAX;
            i->color = white;
            i->predecessor = nullptr;
            i->descendant.clear();
        }
    }
    
    void BFS(GraphNode* source){
        
        resetBFS();
        
        source->distance = 0;
        source->color = grey;
        source->predecessor = nullptr;
        source->descendant.clear();
        
        GraphNode* curr = source;
        queue<GraphNode*> data;
        
        data.push (curr);
        
        while ((int) data.size() != 0){
            
            curr = data.front();
            data.pop();
            
            for (auto i : curr->Adjlist){
                
                if (i->color == white){
                    i->color = grey;
                    i->predecessor = curr;
                    i->distance = curr->distance + 1;
                    curr->descendant.push_back(i);
                    data.push(i);
                }
            }
            
            curr->color = black;
            cout<<"Node value is: " <<curr->value<<"; Node height is:"<<curr->distance<<endl;
            
        }
    }
    
    void printPath(GraphNode* _start, GraphNode* _end){
        if (_start == _end){
            cout <<"Node value is: "<<_end->value<<endl;
            return;
        } else {
            if (_end->predecessor == nullptr){
                cout<<"No path exist"<<endl;
            } else {
                printPath (_start, _end->predecessor);
                cout <<"Node value is: "<<_end->value<<endl;
            }
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
    
    myGraph.BFS(s);
    myGraph.printPath(s, y);
    
    return 0;
}




