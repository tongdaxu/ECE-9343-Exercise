/*
22.1 Representation of Graph
*/

#include <vector>
#include <list>
#include <iostream>
#include <stdio.h>
#include <utility>      

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
    
    void toString(){
        for (auto i : Vertex){
            cout<< i->value <<endl;
        }
    }
    
    ~Graph(){}
    
private:
    vector <GraphNode*> Vertex;
    vector <vector<int>> Adjmatrix;
};


int main()
{
    GraphNode* node1 = new GraphNode (1);
    GraphNode* node2 = new GraphNode (2);
    GraphNode* node3 = new GraphNode (3);
    GraphNode* node4 = new GraphNode (4);
    GraphNode* node5 = new GraphNode (5);
    GraphNode* node6 = new GraphNode (6);

    Graph myGraph ({node1, node2, node3, node4, node5, node6}, 
                   {{node1, node2}, {node1, node4}, {node2, node5}, {node3, node5}, {node4, node2}, {node5, node4}, {node6, node6}});
    
    myGraph.toString();
    
    printf("Hello World");

    return 0;
}

