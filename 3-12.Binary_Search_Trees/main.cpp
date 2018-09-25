/*
12 Binary Search Trees
*/
#include <stdlib.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>
#include <random>

template<class T>
class TreeNode{
public:
    TreeNode<T> *parent = nullptr;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
    
    T key;
    
    TreeNode(){}
    
    TreeNode
    (T _key, 
    TreeNode<T>* _parent = nullptr, 
    TreeNode<T>* _left = nullptr,
    TreeNode<T>* _right = nullptr){
        key = _key;
        parent = _parent;
        left = _left;
        right = _right;
    }
};

template<class T>
class BSTree{
public:
    TreeNode<T> *root = nullptr;
    
    BSTree(){}
    BSTree(T _key){
        root = new TreeNode<T> (_key);
    }
    
    BSTree(std::vector<T> _keys){
        //Exercise 12.3-2, h verse h-1
        for (int i = 0; i < _keys.size(); i++){
            insert(_keys[i]);
        }
    }
    
    TreeNode<T>* minimum(TreeNode<T>* _start){
        while (_start->left != nullptr){
            _start = _start->left;
        }
        return _start;
    }
    
    TreeNode<T>* minimumRecursive(TreeNode<T>* _start){
        //Exercise 12.2-2
        if (_start->left == nullptr){
            return _start;
        } else {
            return  minimumRecursive(_start->left);
        }
    }
    
    TreeNode<T>* maximun(TreeNode<T>* _start){
        while (_start->right != nullptr){
            _start = _start->right;
        }
        return _start;
    }
    
    TreeNode<T>* maximumRecursive(TreeNode<T>* _start){
        if (_start->right == nullptr){
            return _start;
        } else {
            return  minimumRecursive(_start->right);
        }
    }
    
    void insert(T _key){
        TreeNode<T>* temp = new TreeNode<T> (_key);
        insert(temp);
    }
    
    void insert(TreeNode<T>* _input){
        //if tree is empty
        if (root == nullptr){
            root = _input;
            return;
        }
    
        TreeNode<T>* curr = root;
        TreeNode<T>* prev = nullptr;
        
        while (curr != nullptr){
            prev = curr;
            curr = curr->key > _input->key ? curr->left:curr->right;
        }
        
        if (prev->key > _input->key){
            prev->left = _input;
        } else {
            prev->right = _input;
        }
        _input->parent = prev;
        
        return;
    }
    
    void insertRecursive(TreeNode<T>* _start, TreeNode<T>* _input){
        //Exercise 12.3-1, recursive insert, 
        
        if (_start == nullptr){
            _start = _input;
            //what about input->parent???
        } else {
            if (_start->key > _input){
                insertRecursive(_start->left, _input);
            }else{
                insertRecursive(_start->right, _input);
            }
        }
    }
    
    void transplant (TreeNode<T>* _ori, TreeNode<T>* _rep){
        if (_ori->parent == nullptr){
            //replacing the tree root
            root = _rep;
        } else if (_ori->parent->left == _ori){
            _ori->parent->left = _rep;
        } else if (_ori->parent->right == _ori){
            _ori->parent->right = _rep;
        } else {
            //pass, impossible condition
        }
        
        if (_rep != nullptr){
            _rep->parent = _ori->parent;
        }
        
        return;        
    }
    
    void deletion(TreeNode<T>* _input){
        
        if (_input->left == nullptr){
            transplant(_input, _input->right);
        } else if (_input->right == nullptr){
            transplant(_input, _input->left);
        } else {
            TreeNode<T>* commute = minimum(_input->right);
            //commute->key is larger than biggest of _input->left, but smaller than _input->right
            //commute->right is smaller than input->right
            
            if (commute->parent != _input){
                //make commute->parent == _input
                transplant(commute, commute->right);
                //organising right branch
                commute->right = _input->right;
                commute->right->parent = commute;
            }
            
            transplant(_input, commute);
            //organising left branch
            commute->left = _input->left;
            _input->left->parent = commute;
            
        }
        
        delete _input;
        return;
    }
    
    void sort(){
        //Exercise 12.3-3 sort in O(nlogn) time
        while (root != nullptr){
            TreeNode<T>* temp = minimum(root);
            std::cout<<temp->key<<std::endl;
            deletion(temp);
        }
    }

    TreeNode<T>* successor(TreeNode<T>* _this){
        //O(h), smallest element larger than _this
        if (_this->right != nullptr){
            return minimum(_this->right);
        } else {
        //the toppest ancestor whose right child could left all way down to _this
        /*
           /
           \
            \
             \
        */
            TreeNode<T>* commute = _this->parent;
            
            while (commute != nullptr && _this == commute->right){
                _this = commute;
                commute = commute->parent;
            }
            return commute;
        }
    }
    
    TreeNode<T>* precedent(TreeNode<T>* _this){
        //Exercise 12.2-3
        //O(h), smallest element larger than _this
        if (_this->right != nullptr){
            return maximun(_this->left);
        } else {
            TreeNode<T>* commute = _this->parent;
            
            while (commute != nullptr && _this != commute->right){
                _this = commute;
                commute = commute->parent;
            }
            return commute;
        }
    }
    
    TreeNode<T>* search(TreeNode<T>* _start, T _key){
        if (_start == nullptr){
            return _start;
        } else if (_start->key == _key){
            return _start;
        } else {
            
            if (_start->key > _key){
                return search(_start->left, _key);
            } else {
                return search(_start->right, _key);
            }
        }
    }
    
    void toStringPreorder(TreeNode<T>* _start){
        if (_start == nullptr){
            return;
        } else {
            std::cout<<"->"<<_start->key<<std::endl;
            toStringInorder(_start->left);
            toStringInorder(_start->right);
        }
    }
    
    void toStringInorder(TreeNode<T>* _start){
        if (_start == nullptr){
            return;
        } else {
            toStringInorder(_start->left);
            std::cout<<"->"<<_start->key<<std::endl;
            toStringInorder(_start->right);
        }
    }
    
    ~BSTree(){
        while (root != nullptr){
            TreeNode<T>* temp = minimum(root);
            deletion(temp);
        }
    }
    
};

int main()
{
    std::vector<int> test = {2,5,9,12,13,555,18,17,19,-87};
    BSTree<int> myTree(test);
    myTree.sort();
    
    return 0;
}




