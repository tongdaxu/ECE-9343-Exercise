/*
11.4 Open Addressing without universal hashing
*/
#include <stdio.h>
#include <vector>
#include <iostream> 
#include <stack>
#include <math.h>
#include <random>
#define HASH 2 // hashing function type = 0 (divison),1 (multipication), 2 (universal)
#define PROB 2 // probing type = 0 (linear), 1 (quadratic), 2 (double)
#define M 13   // size

int hash(int _key, int _type = HASH){
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

int probing(int _key, int _i){
    if (PROB == 0){
        return (hash(_key) + _i)%M;
    } else if (PROB == 1){
        //see Priblem set 11-3
        int c1 = 1;
        int c2 = 0;
        return (hash(_key) + c1*_i + c2*_i*_i)%M;
    } else if (PROB == 2){
        return (hash(_key, 1) + _i*hash(_key, 2))%M;
    }
    
}

template<class T>
class Bucket{
//Bucket for openAddressing
public:
    bool ifNull = 1;
    int key;
    T data;
    Bucket(){}
    Bucket(int _key){
        key = _key;
        data = key;
        ifNull = 0;
    }
    Bucket(int _key, T _data){
        key = _key;
        data = _data;
        ifNull = 0;
    }
};

template <class T>
class Table{
public:
    std::vector<Bucket<T>*> data;
    
    Table(){
        data.reserve(M);
        for (int i = 0; i<M; i++){
            data.push_back(NULL);
        }
    }
    
    Table(std::vector<T> _data){
        //only when key and value is int and equal
        data.reserve(M);
        for (int i = 0; i<M; i++){
            data.push_back(NULL);
        }
        
        for (int i = 0; i<_data.size(); i++){
            Bucket<T>* temp = new Bucket<T>(_data[i]);
            insert(temp);
        }
        
    }
    
    int insert(Bucket<T>* _input){
        int i = 0;
        while (i < M){
            if (data[probing(_input->key, i)] == NULL){
                data[probing(_input->key, i)] = _input;
                return i;
            } else {
                i++;
            }
        }
        throw std::out_of_range("hash table overflow");
    }
    
    void toString(){
        for (int i = 0; i<M; i++){
            if (data[i] == NULL){
                std::cout<<i<<"->"<<std::endl;
            } else {
                std::cout<<i<<"->"<<data[i]->data<<std::endl;
            }
            
        }

    }
    
    ~Table(){}
};

int main()
{   
    std::vector<int> myVector = {5,28,19,15,20,33,12,17,10,2,18,23,55};
    Table<int> myTable(myVector);
    myTable.toString();

    return 0;
}


