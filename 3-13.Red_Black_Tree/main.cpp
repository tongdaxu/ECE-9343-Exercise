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
            TreeNode<T> *temp = new TreeNode<T> (_keys[i], RED);
            //always insert as red
            insert(temp);
        }
    }

    void insert(TreeNode<T> *_z){
        TreeNode<T> *_x = root;
        TreeNode<T> *_y = nullptr;
        //y = root->parent
        
        while (_x != nullptr){
            
            _y = _x;
            
            if (_z->key < _x->key){
                _x = _x->left;
            } else {
                _x = _x->right;
            }
        }
        
        _z->parent = _y;
        
        if (_y == nullptr){
            root = _z;
        } else if (_z->key < _y->key){
            _y->left = _z;
        } else {
            _y->right = _z;
        }
        
        _z->left = nullptr;
        _z->right = nullptr;
        _z->color = RED;
        
        //no diff from BST insert until now
        insertFix(_z);
    }
    
    void deletion(TreeNode<T> *_z){
        
        TreeNode<T> *_y = _z;
        TreeNode<T> *_x = nullptr;
        COLOR yOriginal = _y->color;
        
        if (_z->left == nullptr){
            _x = _z->right;
            transplant(_z, _z->right);
        } else if (_z->right == nullptr){
            _x = _z->left;
            transplant(_z, _z->left);
        } else {
            _y = minimum(_z->right);
            yOriginal = _y->color;
            _x = _y->right;
            
            if (_y->parent == _z){
                _x->parent = _y;
            } else {
                transplant(_y, _y->right);
                _y->right = _z->right;
                _y->right->parent = _y;
            }
            
            transplant(_z, _y);
            _y->left = _z->left;
            _y->left->parent = _y;
            _y->color = _z->color;
        }
        
        if (yOriginal == BLACK){
            deleteFix(_x);
        }
    }
    
    void toStringPreorder(TreeNode<T>* _start){
        if (_start == nullptr){
            return;
        } else {
            std::cout<<"->"<<_start->key<<", "<<_start->color<<std::endl;
            toStringPreorder(_start->left);
            toStringPreorder(_start->right);
        }
    }
    
    
    ~BRTree(){
    }
    
private: 

    TreeNode<T>* minimum(TreeNode<T>* _start){
        while (_start->left != nullptr){
            _start = _start->left;
        }
        return _start;
    }
    
    TreeNode<T>* maximun(TreeNode<T>* _start){
        while (_start->right != nullptr){
            _start = _start->right;
        }
        return _start;
    }

    void lRotate(TreeNode<T>* _x){
        //assume that x.right != nullptr
        TreeNode<T> *_y = _x->right;
        _x->right = _y->left;
        if (_y->left != nullptr){
            _y->left->parent = _x;
        }
        
        _y->parent = _x->parent;
        
        if (_x->parent == nullptr){
            root = _y;
        } else if (_x == _x->parent->left){
            _x->parent->left = _y;
        } else {
            _x->parent->right = _y;
        }
        
        _y->left = _x;
        _x->parent = _y;
        
    }
    
    void rRotate(TreeNode<T>* _y){
        //assume that y.left != nullptr
        //Exercise 13.2-1
        //Exercise 13.3-2
        
        TreeNode<T> *_x = _y->left;
        _y->left = _x->right;
        if (_x->right != nullptr){
            _x->right->parent = _y;
        }
        
        _x->parent = _y->parent;
        
        if (_y->parent == nullptr){
            root = _x;
        } else if (_y->parent->left == _y){
            _y->parent->left = _x;
        } else {
            _y->parent->right = _x;
        }
        
        _x->right = _y;
        _y ->parent = _x;
        
    }
    
    void insertFix(TreeNode<T> *_z){
        //suspect of this shit works or not
        
        while (_z->parent != nullptr && _z->parent->color == RED){
            
            if (_z->parent->parent == nullptr){
                //this means _z->parent == root, it is OK, do damn nothing and break;
                break;
            }
            
            if (_z->parent == _z->parent->parent->left){
                
                TreeNode<T>* _y = _z->parent->parent->right;
                if (_y != nullptr && _y->color == RED){
                    //case 1
                    _z->parent->color = BLACK;
                    _y->color = BLACK;
                    _z->parent->parent->color = RED;
                    _z = _z->parent->parent;
                    //z up up, now check if z grand parent violate rule 4
                } else if (_z == _z->parent->right){
                    //case 2
                    _z = _z->parent;
                    lRotate(_z);
                } else {
                    //case 3
                    _z->parent->color = BLACK;
                    _z->parent->parent->color = RED;
                    rRotate(_z->parent->parent);
                }
            } else {
                
                TreeNode<T>* _y = _z->parent->parent->left;
                if (_y != nullptr && _y->color == RED){
                    //case 1
                    _z->parent->color = BLACK;
                    _y->color = BLACK;
                    _z->parent->parent->color = RED;
                    _z = _z->parent->parent;
                } else if (_z == _z->parent->left){
                    //case 2
                    _z = _z->parent;
                    rRotate(_z);
                } else {
                    //case 3
                    _z->parent->color = BLACK;
                    _z->parent->parent->color = RED;
                    lRotate(_z->parent->parent);
                }   
            }
            
        }
        
        root->color = BLACK;
        
    }
    
    void deleteFix(TreeNode<T> *_x){
        
        while (x != root && x->color == BLACK){
            
            if (x == x->parent->left){
                //since x != root, this compare is safe
                TreeNode<T> *_w = x->parent->right;
                
                if (_w != nullptr && w->color == RED){
                    //case 1
                    _w->color = BLACK;
                    _x->parent->color = RED;
                    lRotate(_x->parent);
                    _w = _x->parent->right;
                    
                }
                
                if (_w != nullptr && _w->left->color == BLACK && _w->right->color == BLACK){
                    //case 2
                    _w->color = RED;
                    _x = _x->parent;
                } else if (_w != nullptr && _w->right->color == BLACK){
                    if (_w->left->)
                }
                
                
                
            }
            
            
            
            
        }
        
        
        
        
        
    }

    void transplant (TreeNode<T>* _ori, TreeNode<T>* _rep){
        //differs from BST transplant
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
    
};

int main()
{   
    std::vector <int> test = {41, 38, 31, 12, 19, 9, 12, 17, 37, 23 ,29, 8};
    BRTree<int> myBRTree(test);
    myBRTree.toStringPreorder(myBRTree.root);

    return 0;
}


