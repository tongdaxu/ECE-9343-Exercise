/*
* Chapter 23. Minimum Spanning Tree in CLRS
* Graph is smplified for weighted undirected graph
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

class GraphNode{
    
public:

    string tag;
    string MSTSet;
    int key;
    bool inqueue;
    //weighted graph only
    list<pair <GraphNode*, int>> Adjlist;
    GraphNode* parent = nullptr;

    GraphNode(string _tag){
    //well you can't declare it to be explicit    
        tag = _tag;
    }
    
    ~GraphNode(){}

private:
};

/*
struct vertexCompare
{
    bool operator()(GraphNode* LHS, GraphNode* RHS)
    { return LHS->key < RHS->key; }
};
*/

bool vertexCompare(GraphNode* LHS, GraphNode* RHS){
    return LHS->key < RHS->key;
}

class Edge{
public:
    GraphNode* start = nullptr;
    GraphNode* end = nullptr;
    int weight;
    
    Edge(){}
    Edge(GraphNode* _start, GraphNode* _end, int _weight){
        
        start = _start;
        end = _end;
        weight = _weight;

    }
    
};

bool edgeCompare(const Edge &LHS, const Edge &RHS){
    //sort in non decreasing order
    return (LHS.weight < RHS.weight);
}

class Graph{
//adjacency list graph
public:
    
    vector <GraphNode*> Vertex;
    vector <Edge> weight;
    
    Graph(
        const vector<GraphNode*> &_Vertex, const vector<pair<GraphNode*, pair <GraphNode*, int>>> _Edge, bool undirected = true
    ){
        Vertex = _Vertex;
        
        for (auto i : _Edge){
            
            i.first -> Adjlist.push_back(i.second);
            weight.push_back(Edge(i.first, i.second.first, i.second.second));
            if (undirected){
                i.second.first-> Adjlist.push_back(pair<GraphNode*, int> (i.first, i.second.second));
            }
        }
    }
    
    vector<Edge> MSTKruskal(){
        
        vector<Edge> A;
        
        for (auto i : Vertex){
            i->MSTSet = i->tag;
        }
        
        sort(weight.begin(), weight.end(), edgeCompare);
        for (auto j : weight){
            
            if (j.start->MSTSet != j.end->MSTSet){
                //find cost O(1) time
                A.push_back(j);
                
                for (auto k : Vertex){
                    //brutal force union operation, takes V time, very stupid 
                    if (k->MSTSet == j.end->MSTSet){
                        k->MSTSet = j.start->MSTSet;
                    }
                }
            }
        }
        return A;
    }
    
    void MSTPrim(GraphNode* root){
        
        list <GraphNode*> data;
        
        for (auto i : Vertex){
            i->key = INT_MAX;
            i->parent = nullptr;
            i->inqueue = true;
            data.push_back(i);

        }
        
        root->key = 0;
        
        while (data.size() != 0){
            //akaward priority queue
        
            auto temp = min_element(data.begin(), data.end(), vertexCompare);
            GraphNode* tempVertex = *temp;
            data.erase(temp);
            
            tempVertex->inqueue = false;
            cout<<tempVertex->tag<<"," <<tempVertex->key<<endl;
            
            for (auto j : tempVertex->Adjlist){
                /*j pair<GraphNode*, weight>
                 *j.first = GraphNode* v
                 *j.second = weight (u,v)
                 */

                if (j.first->inqueue == true && j.second < j.first->key){
                    j.first->parent = tempVertex;
                    j.first->key = j.second;

                }
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
    
};

int main()
{
    GraphNode* a = new GraphNode ("a");
    GraphNode* b = new GraphNode ("b");
    GraphNode* c = new GraphNode ("c");
    GraphNode* d = new GraphNode ("d");
    GraphNode* e = new GraphNode ("e");
    GraphNode* f = new GraphNode ("f");
    GraphNode* g = new GraphNode ("g");
    GraphNode* h = new GraphNode ("h");
    GraphNode* i = new GraphNode ("i");

    Graph myGraph(
        {a, b, c, d, e, f, g, h, i},
        {
            {a, {b, 4}},
            {a, {h, 8}},
            {b, {c, 8}},
            {b, {h, 11}},
            {c, {d, 7}},
            {c, {f, 4}},
            {c, {i, 2}},
            {d, {e, 9}},
            {d, {f, 14}},
            {e, {f, 10}},
            {f, {g, 2}},
            {g, {h, 1}},
            {g, {i, 6}},
            {h, {i, 7}}
            
        }
    ); 
    
    //myGraph.toString();

    vector<Edge> result = myGraph.MSTKruskal();
    
    for (auto i : result){
        cout<<i.start->tag<<" - "<<i.end->tag<<" = "<<i.weight<<endl;
    }
    
    myGraph.MSTPrim(a);
    
    for (auto j : myGraph.Vertex){
        
        if (j->parent != nullptr){
            cout<<j->tag<<"->"<<j->parent->tag<<endl;
        } else {
            cout<<"root is: "<<j->tag<<endl;
        }
    }
    
    return 0;
}





