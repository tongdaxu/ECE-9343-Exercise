/*
16.3 HuffmanCode
*/

#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>

class Node{
    
public:
    Node* left = nullptr;
    Node* right = nullptr;
    int freq = 0;
    
    Node (){}
    Node (int _freq){
        freq = _freq;
    }
    Node (Node* _left, Node* _right){
        left = _left;
        right = _right;
        freq = _left->freq + _right->freq;
    }
    
    ~Node(){}
    
};

struct OrderByFreq
{
    bool operator() (Node* left, Node* right) { return left->freq > right->freq; }
};

void construct (std::priority_queue<Node*, std::vector<Node*>, OrderByFreq> &data){
    
    while (data.size() > 1){
        
        Node* X = data.top();
        data.pop();
        std::cout<<X->freq<<", ";
        
        Node* Y = data.top();
        data.pop();
        std::cout<<Y->freq<<", ";
        
        Node* Z = new Node (X,Y);
        data.push(Z);
        std::cout<<Z->freq<<std::endl;
        
    }
}

void inorder(Node* root){
    if(root == nullptr){
        return;
    } else {
        inorder(root->left);
        std::cout<<root->freq<<std::endl;
        inorder(root->right);
    }
}
    
int main()
{
    Node* a = new Node (45);
    Node* b = new Node (13);
    Node* c = new Node (12);
    Node* d = new Node (16);
    Node* e = new Node (9);
    Node* f = new Node (5);
    
    std::priority_queue<Node*, std::vector<Node*>, OrderByFreq> data;
    
    for (auto i : {a,b,c,d,e,f}){
        data.push (i);
    }
     
    construct(data);
    inorder(data.top());
    
    return 0;
}

