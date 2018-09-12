/*
heap and heap sort for chaper 6.1 - 6.3

*/
#include <stdio.h>
#include <vector>
#include <iostream>

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

int main()
{
    vector<int> test = {1, 9, 8, 7, 6, 5, -222290, 3, 2, 0, 19999};
    vector<int> result = heapSort (test);
    
    for (int i=0; i< result.size(); i++){
        cout<<result[i]<<endl;
    }

    return 0;
}
