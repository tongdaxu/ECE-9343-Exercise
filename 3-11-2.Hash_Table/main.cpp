/*
11.1 Direct Hashing
11.2 Hash Table with LinkNode
11.3 Hash Function
*/
#include <stdlib.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>
#include <random>
#define HASH 2

template<class T>
class Bucket{
public:
    int aRecord = -1;
    int bRecord = -1;
    int key;
    T data;
    Bucket<T>* next = NULL;
    Bucket(){}
    Bucket(int _key){
        key = _key;
        data = key;
    }
    Bucket(int _key, T _data){
        key = _key;
        data = _data;
    }
};

template<class T>
int hash(int _key){
    int hashresult;
    //Should be unsigned int
    if (HASH == 0){
        //divison method
        hashresult = _key%9;
    } else if (HASH == 1){
        //multipication method, normally m = 2^n, here m = 9
        hashresult = floor (9*((0.6180339887*_key) - floor(0.6180339887*_key)));
    } else if (HASH == 2){

            int p = 8819; // a big prime
            
            srand (_key);
            int a = rand() % (p-2) + 1; //a [1, p-1]
            srand (_key*_key);
            int b = rand() % (p-2); //b [0, p-1]
            
            hashresult = ((a*_key + b)%p)%9;
        
    }else {
        //throw a mistake
        //p is a large enough prime number
        throw std::out_of_range("hash function type invalid");
    }
    
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
    
    Table(std::vector<T> _data, int _m){
        m = _m;
        data.reserve(m);
        
        for (int i = 0; i<m; i++){
            data.push_back(NULL);
        }
        
        for (int i = 0; i<m; i++){
            Bucket<T>* temp = new Bucket<T>(_data[i]);
            insert(temp);
        }
        
    }
    
    Bucket<T>* search(int key){
        
        int hVal = hash<T>(key);
        Bucket<T>* curr = data[hash<T>(key)];
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

        int hVal = hash<T>(_input->key);
        
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
        data[hash<T>(_input->key)] = NULL;
    }
    
    void deleteDirect(Bucket<T>* _input){
        if (_input->key > m-1){
            throw std::out_of_range("key overflow");
        }
        
        data[_input->key] = NULL;
    }
    
    void toString(){
        for (int i = 0; i < data.size(); i++){
            
            if (data[i] == NULL){
                std::cout<<i<<"->"<<std::endl;
            } else {
                std::cout<<i<<"->";
                Bucket<T>* curr = data[i];
                
                while (curr != NULL){
                    std::cout<<curr->data<<"->";
                    curr = curr->next;
                }
                
                std::cout<<std::endl;
            }
        }
    }
    
};

int main()
{
    /*
    Test case for Exercise 11.2-2
    */
    
    std::vector<int> myVector = {5,28,19,15,20,33,12,17,10,2,18,23};
    Table<int> myTable(myVector, 9);
    myTable.toString();
    std::cout<<myTable.search(28)->data<<std::endl;
    
    return 0;
}









