/*
* 24.Single Source Shortest Path
* 24.1 Bellman-Ford algorithm
*/

#include <stdio.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <queue>
#include <set>

#include <climits>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

const int white = 0;
const int grey = 1;
const int black = 2;

class GraphNode{
    
public:

    string tag;
    int distance;
    list<pair <GraphNode*, int>> Adjlist;
    GraphNode* parent = nullptr;

    GraphNode(string _tag){
        tag = _tag;
    }
    
    ~GraphNode(){}

private:
};

bool compareNode (GraphNode* LHS, GraphNode* RHS){
    //node compare function for Topo sort
    return LHS->finish > RHS->finish;
}

class Graph{
//adjacency list graph
public:
    
    Graph(
        const vector<GraphNode*> &_Vertex, const vector<pair<GraphNode*, pair <GraphNode*, int>>> _Edge, bool undirected = true
    ){
        Vertex = _Vertex;
        
        for (auto i : _Edge){
            
            i.first -> Adjlist.push_back(i.second);
            if (undirected){
                i.second.first-> Adjlist.push_back(pair<GraphNode*, int> (i.first, i.second.second));
            }
        }
    }
    
    bool bellmanFord(GraphNode* root){
        initializeSS(root);
        for (int i = 1; i < Vertex.size(); i++){
            //for each edge (u,v) \in G.E
            
            for (auto j : Vertex){
                for (auto k : j->Adjlist){
                    relax(j, k.first);
                }
            }
        }
        
        //for each edge (u,v) \in G.E
        for (auto l : Vertex){
            for (auto m : l->Adjlist){
                
                if (l->distance == INT_MAX){
                    //pass, the > could not be true
                } else if (m.first->distance > l->distance + weight (l, m.first)){
                    return false;
                }
                
            }
        }
        
        return true;
    }
    
    void toString(){
        for (auto i : Vertex){
            cout<< i->tag << " has list:";
            for (auto j : i->Adjlist){
                cout<<" -> "<<j.first->tag<<": "<<j.second;
            }
            cout<<endl;
            
        }
    }
    
    void treeToString(){
        
        for (auto i : Vertex){
            if (i->parent == nullptr){
                cout<<"root is: "<<i->tag<<endl;
            } else {
                cout<<i->tag<<" has parent: "<<i->parent->tag<<endl;
            }
        }
    }

private:
    
    vector <GraphNode*> Vertex;
    
    int weight(GraphNode* _start, GraphNode* _end){
        for (auto i : _start->Adjlist){
            if (i.first == _end){
                return i.second;
            }
        }
        
        //well, this should not happen, but just in case...
        return INT_MAX;
    }

    void initializeSS(GraphNode* root){
        for (auto i : Vertex){
            i->distance = INT_MAX;
            i->parent;
        }
        root->distance = 0;
    }
    
    void relax (GraphNode* u, GraphNode* v){
        
        if (u->distance == INT_MAX){
            //catch overflow
            return;
        }
        
        if (v->distance > u->distance + weight(u,v)){
            cout<<"relax"<<endl;
            v->distance = u->distance + weight(u,v);
            v->parent = u;
        }
    }
};

int main()
{
    GraphNode* s = new GraphNode ("s");
    GraphNode* t = new GraphNode ("t");
    GraphNode* x = new GraphNode ("x");
    GraphNode* y = new GraphNode ("y");
    GraphNode* z = new GraphNode ("z");

    Graph myGraph(
        {s, t, x, y, z},
        {
            {s, {t, 6}},
            {s, {y, 7}},
            {t, {x, 5}},
            {t, {y, 8}},
            {t, {z, -4}},
            {x, {t, -2}},
            {y, {x, -3}},
            {y, {z, 9}},
            {z, {s, 2}},
            {z, {x, 7}}
        },
        false
    ); 
    
    myGraph.bellmanFord(s);
    myGraph.treeToString();

    return 0;
}
