/*
10.4 Representing rooted trees
*/

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>

template<class T>
class TreeNode{
public:
    TreeNode<T>* left = NULL;
    TreeNode<T>* right = NULL;
    TreeNode<T>* parent = NULL;
    
    T key;
    
    TreeNode(){}
    TreeNode(TreeNode<T>* _parent){
        parent = _parent;
    }
    TreeNode(T _key, TreeNode<T>* _parent){
        parent = _parent;
        key = _key;
    }
    ~TreeNode(){}
};

template<class T>
class TreeNodeR{
public:
    TreeNodeR<T>* left = NULL;
    TreeNodeR<T>* rightsib = NULL;
    TreeNodeR<T>* parent = NULL;
    
    T key;
    
    TreeNodeR(){}
    TreeNodeR(TreeNodeR<T>* _parent){
        parent = _parent;
    }
    TreeNodeR(T _key, TreeNodeR<T>* _parent){
        parent = _parent;
        key = _key;
    }
    ~TreeNodeR(){}
};

template<class T>
class BTree{
public:
    TreeNode<T>* root = NULL;
    
    BTree(){
        root = new TreeNode<T>(0);
    }
    
    void LFR(TreeNode<T>* _current){
        //Exercise 10.4.2
        std::cout<<_current->key<<"\n";
        
        if(_current->left != NULL){
            LFR(_current->left);
        } else if (_current->right != NULL){
            LFR(_current->right);
        } else {
            return;
        }
    }

    void LFRS(){
        //non recursive method, Exercise 10.4.3
        TreeNode<T>* curr = root;
        std::stack<TreeNode<T>*> TStack;
        
        while(1){
            
            std::cout<<curr->key<<"\n";
            
            if (curr->left != NULL){
                if (curr->right != NULL){
                    TStack.push(curr->right);
                }
                curr = curr->left;
            } else {
                if(!TStack.empty()){
                    curr = TStack.pop();
                } else {
                    break;
                }
            }
        }    
    }
    
    ~BTree(){
        delete root;
    }
};


int main()
{
    printf("Hello World");

    return 0;
}


