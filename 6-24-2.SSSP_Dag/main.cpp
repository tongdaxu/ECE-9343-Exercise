/*
* 24.Single Source Shortest Path
* 24.2 DAG Acceleration algorithm
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
    
    //for BFS
    bool visited = false;
    int discovery = INT_MAX;
    int finish = INT_MAX;
    int color = white;

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
    
    void DagSSSP(GraphNode* root){
        topoSort();
        initializeSS(root);
        for (auto i : Vertex){
            //already in topo order
            for (auto j : i->Adjlist){
                relax (i, j.first);
            }
        }
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
            cout<<i->tag<<" has distance: "<<i->distance<<endl;
            
            if (i->parent == nullptr){
                cout<<"root is: "<<i->tag<<endl;
            } else {
                cout<<i->tag<<" has parent: "<<i->parent->tag<<endl;
            }
        }
    }


private:
    
    vector <GraphNode*> Vertex;
    int t;
    
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
            i->parent = nullptr;
        }
        root->distance = 0;
    }
    
    void relax (GraphNode* u, GraphNode* v){
        
        if (u->distance == INT_MAX){
            //catch overflow
            return;
        }
        
        if (v->distance > u->distance + weight(u,v)){
            cout<<u->tag<<": "<<u->distance<<", "<<v->tag<<": "<<v->distance<<endl;
            v->distance = u->distance + weight(u,v);
            v->parent = u;
        }
    }
    
    void DFSReset(){
        for (auto i: Vertex){
            i->color = white;
            i->parent = nullptr;
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
            
            if (i.first->color == white){
                i.first->parent = source;
                DFSVisit(i.first);
            }
        }
        
        source->color = black;
        ++t;
        source->finish = t;
        //cout<<source->tag<<", "<<source->discovery<<"/"<<source->finish<<endl;
    }
    
    void topoSort(){
        DFS();
        sort(Vertex.begin(), Vertex.end(), compareNode);
    }
    
};

int main()
{
    GraphNode* r = new GraphNode ("r");
    GraphNode* s = new GraphNode ("s");
    GraphNode* t = new GraphNode ("t");
    GraphNode* x = new GraphNode ("x");
    GraphNode* y = new GraphNode ("y");
    GraphNode* z = new GraphNode ("z");

    Graph myGraph(
        {r, s, t, x, y, z},
        {
            {r, {s, 5}},
            {r, {t, 3}},
            {s, {t, 2}},
            {s, {x, 6}},
            {t, {x, 7}},
            {t, {y, 4}},
            {t, {z, 2}},
            {x, {y, -1}},
            {x, {z, 1}},
            {y, {z, -2}}
        },
        false
    ); 
    
    myGraph.DagSSSP(s);
    myGraph.treeToString();

    return 0;
}


