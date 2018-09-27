/*
13.Red black tree 
*/
#include <stdio.h>
#include <vector>
#include <iostream> 
#include <stack>
#include <math.h>
#include <random>

/*special defination for Black Red Tree*/
#define RED 0
#define BLACK 1
typedef bool COLOR;


template<class T>
class TreeNode{
public:
    
    TreeNode<T> *parent = nullptr;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
    
    COLOR color;
    T key;
    
    TreeNode(){}
    TreeNode(COLOR _color){
        color = _color;
    }
    
    TreeNode
    (T _key, 
    COLOR _color,
    TreeNode<T>* _parent = nullptr, 
    TreeNode<T>* _left = nullptr,
    TreeNode<T>* _right = nullptr){
        key = _key;
        parent = _parent;
        left = _left;
        right = _right;
        color = _color;
    }
};

template<class T>
class BRTree{
public:
    TreeNode<T> *root = nullptr;
    
    BRTree(){

    }
    
    BRTree(const std::vector<T> &_keys){
        //Exercise 12.3-2, h verse h-1
        for (int i = 0; i < _keys.size(); i++){
            //insert(_keys[i]);
        }
    }
    
    void lRotate(TreeNode<T>* _x){
        //assume that x.right != nullptr
        TreeNode<T> *_y = _x.right;
        _x->right = _y->left;
        if (_y->left != nullptr){
            _y->left->parent = _x;
        }
        
        _y->parent = _x->parent;
        
        if (_x->parent = nullptr){
            root = _y;
        } else if (_x == _x->parent->left){
            _x->parent->left = _y;
        } else {
            _x->parent->right = _y;
        }
        
        _y->left = _x;
        _x->parent = _y;
        
    }

    
    ~BRTree(){
    }
    
};

int main()
{   
    BRTree<int> myBRTree;
    printf("Hello World");

    return 0;
}
