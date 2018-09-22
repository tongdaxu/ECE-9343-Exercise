/*
10.1 stack queues
*/
#include <stdio.h>
#include <vector>
#include <iostream>

template<class T>
class Stacks{
private:
    std::vector<T> _data;
    
public:
    Stacks(){}
    
    int size(){
        return _data.size();
    }
    
    bool empty(){
        if (_data.size() == 0){
            return true;
        } else {
            return false;
        }
    }
    
    void push(T input){
        _data.push_back(input);
    }
    
    T top(){
        if (empty()){
            throw std::out_of_range("stack is empty");
        }
        return _data[_data.size()-1];
    }
    
    T pop(){
        T temp = top();
        //security check by top
        _data.erase(_data.begin()+_data.size()-1);
        return temp;
    }
};

template<class T>
class Queues{
private:
    std::vector<T> _data;
    
public:
    Queues(){}
    
    int size(){
        return _data.size();
    }
    
    bool empty(){
        if (_data.size() == 0){
            return true;
        } else {
            return false;
        }
    }
    
    void enqueue(T input){
        _data.push_back(input);
    }
    
    T dequeue(){
        if (empty()){
            throw std::out_of_range("Queue underflow");
        }
        T temp = _data[0];
        //security check by top
        _data.erase(_data.begin());
        return temp;
    }
};


int main()
{
    Stacks<int> myStack;
    Queues<int> myQueue;
    myStack.push(5);
    std::cout<<myStack.top()<<"\n";
    myStack.pop();
    
    myQueue.enqueue(76);
    std::cout<<myQueue.dequeue()<<"\n";
    //myQueue.dequeue();

    return 0;
}
