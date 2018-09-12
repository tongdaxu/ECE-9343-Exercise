/*
heap and heap sort for chaper 6.1 - 6.4
priority queue for chaper 6.5
*/
#include <stdio.h>
#include <vector>
#include <iostream>
#include <limits>

#define INFINITY std::numeric_limits<int>::max()

using namespace std;

int parent(int i){
    return i/2;
}

int leftChild(int i){
    return i*2;
}

int rightChild(int i){
    return i*2 + 1;
}

void exchange(int &i1, int &i2){
    
    int temp = i1;
    i1 = i2;
    i2 = temp;
    
}

void maxHeapify(vector<int> &input, int i){
    
    //input i /in [1, size]
    int l = leftChild(i) - 1;
    int r = rightChild(i) - 1;
    i = i - 1;
    
    if (r < input.size()){
        
        int maxI = input[r] > input[l] ? r : l;
        maxI = input[i] > input[maxI] ? i : maxI;
        
        if (maxI != i){
            exchange (input[i], input[maxI]);
            maxHeapify (input, maxI + 1);
        }
        
    } else if (l < input.size()){
        
        int maxI = input[i] > input[l] ? i : l;
        
        if (maxI != i){
            exchange (input[i], input[l]);
        }
        
    } else {
        //pass, do nothing
    }
    
}

void buildMaxHeap(vector<int> &input){
    
    //note that this is O(n)
    for (int i = input.size()/2; i > 0; i--){
        maxHeapify(input, i);
    }
}

vector<int> heapSort(vector<int> &input){
    
    vector<int> sortResult;
    
    buildMaxHeap(input);
    
    for (int i = input.size(); i > 0; i--){
        
        exchange(input[i-1], input[1-1]);
        sortResult.push_back(input[i-1]);
        
        input.erase(input.begin() + i-1);
        maxHeapify(input, 1);
        
    }
    
    return sortResult;
    
}

class maxPriorityQueue{
    
public:
    
    vector<int> data;
    
    maxPriorityQueue(vector<int> input){
        buildMaxHeap(input);
        data = input;
    }
    
    void insert (int in){
        data.push_back(in);
    }
    
    int maximum(){
        return data[0];
    }
    
    int extractMax(){
        
        if (data.size()==0){
            return -INFINITY;
        }
        
        int temp = data[0];
        
        exchange(data[0], data[data.size()-1]);
        data.erase(data.begin() + data.size()-1);
        maxHeapify(data, 1);
        
        return temp;
        
    }
};

int main()
{
    vector<int> test = {1, 9, 8, 7, 6, 5, -222290, 3, 2, 0, 19999};
    maxPriorityQueue myQueue (test);
    
    while (myQueue.data.size()>0){
        cout<<myQueue.extractMax()<<endl;
    }

    return 0;
}
