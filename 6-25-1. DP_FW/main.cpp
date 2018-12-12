/*
* 25.All Pair Shortest Path
* 25.1 Matrix Representation
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

class Graph{
//adjacency list graph
public:
    
    Graph(
        const vector<GraphNode*> &_Vertex, const vector<pair<GraphNode*, pair <GraphNode*, int>>> _Edge, bool undirected = true
    ){
        Vertex = _Vertex;
        
        for (auto u : Vertex){
            
            unordered_map<GraphNode*, int> temp;
            for (auto v : Vertex){
                if (u == v){
                    temp.emplace(v, 0);
                } else {
                    temp.emplace(v, INT_MAX);
                }
            }
            Weight.emplace(u, temp);
        }
        
        for (auto i : _Edge){
            
            i.first -> Adjlist.push_back(i.second);
            Weight[i.first][i.second.first] = i.second.second;
            
            if (undirected){
                i.second.first-> Adjlist.push_back(pair<GraphNode*, int> (i.first, i.second.second));
                Weight[i.second.first][i.first] = i.second.second;
            }
        }
    }
    
    void listToString(){
        for (auto i : Vertex){
            cout<< i->tag << " has list:";
            for (auto j : i->Adjlist){
                cout<<" -> "<<j.first->tag<<": "<<j.second;
            }
            cout<<endl;
        }
    }
    
    void matrixToString(){
        for (auto i : Vertex){
            cout<<i->tag<<": ";
            for (auto j : Vertex){
                if(Weight[i][j] == INT_MAX){
                    cout<<"-"<<" ";
                } else {
                    cout<<Weight[i][j]<<" ";
                }
            }
            cout<<endl;
        }
    }
    
private:
    
    unordered_map<GraphNode*, unordered_map<GraphNode*, int>>  Weight;
    vector <GraphNode*> Vertex;

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
    
    myGraph.matrixToString();
    return 0;
}

