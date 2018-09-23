/*
11.1 Direct Hashing
11.2 Hash Table
*/

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>

template<class T>
class Bucket{
public:
    int key;
    T data;
    Bucket<T>* next = NULL;
    Bucket(){}
    Bucket(int _key, T _data){
        key = _key;
        data = _data;
    }
};

int hash(int _key){
    //This is hash function
    int hashresult = 0;
    //hashresult = _input->key;
    return hashresult;
}

template<class T>
class Table{
public:
    int m;
    std::vector<Bucket<T>*> data;
    Table(){}
    Table(int _m){
        m = _m;
        data.reserve(m);
        for (int i = 0; i<m; i++){
            data.push_back(NULL);
        }
    }
    
    Bucket<T>* search(int key){
        
        int hVal = hash(key);
        Bucket<T>* curr = data[hash(key)];
        // curr = head of the node, you have to traverse the list
        
        while(curr != NULL){
            
            if (curr->key == key){
                break;
            } else {
                curr = curr->next;
            }
                
        }
        return curr;
    }
    
    Bucket<T>* searchDirect(int key){
        //key should be in [0,m-1]
        if (key > m-1){
            throw std::out_of_range("key overflow");
        }
        //note that we only return the first key;
        return data[key];
    }
    
    void insert(Bucket<T>* _input){
        
        int hVal = hash(_input->key);
        
        if (data[hVal] == NULL){
            data[hVal] = _input;
        } else {
            _input->next = data[hVal];
            data[hVal] = _input;
        }
    }
    
    void insertDirect(Bucket<T>* _input){
        //LinkNode of Exercise 11.1-3
        if (_input->key > m-1){
            throw std::out_of_range("key overflow");
        }
        
        if (data[_input->key] == NULL){
            data[_input->key] = _input;
        } else {
            _input->next = data[_input->key];
            data[_input->key] = _input;
        }
    }
    
    void deleteHash(Bucket<T>* _input){
        data[hash(_input->key)] = NULL;
    }
    
    void deleteDirect(Bucket<T>* _input){
        if (_input->key > m-1){
            throw std::out_of_range("key overflow");
        }
        
        data[_input->key] = NULL;
    }
    
};

int main()
{
    Table<float> myTable(100);
    Bucket<float>* testBucket = new Bucket<float>(44, 9.64);
    myTable.insertDirect(testBucket);
    Bucket<float>* result = myTable.searchDirect(44);
    std::cout<<result->data<<"\n";

    return 0;
}
