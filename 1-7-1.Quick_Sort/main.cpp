/*
7-1 quickSort and its reverse
7-3 random quickSort
Exercise 7.1-4
Problem Set 7-1 Hoare Partition and Hoare quickSort
Problem Set 7-4 Tail Recursive quickSort
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

void exchange(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

int partition(vector<int> &input, int p, int r){
    //partition or rearrange
    //random sample, since we could not afford to randomize whole input
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(p, r);
    
    int ran = dis(gen);
    exchange(input[ran], input[r]);

    int tail = input[r];
    int curr = p;
    int prev = p-1;
    
    while (curr < r){
        
        if (input[curr] <= tail){
            // > decrease, < increase
            //throw it to front
            prev++;
            exchange(input[prev], input[curr]);
        } else {
            //eat it, do nothing
        }
        
        //promise (prev, curr] is larger than prev, and finally prev is larger than [p, prev)
        curr ++;
    }
    
    exchange(input[prev + 1], input[r]);
    return prev + 1;
    
}

int hPartition(vector<int> &input, int p, int r){
    
    int x = input[p];
    int i = p;
    int j = r;
    
    while (1){
        
      while (input[j]>x){
        j--;  
      }
      
      while (input[i]<x){
        i++;  
      }  
      
      if (i<j){
          exchange(input[i], input[j]);
      }else {
          return j;
      }
    }
}

void quickSort(vector<int> &input, int p, int r){
    //T(n) = T(ax)+T((1-a)x) + x
    

    if (p < r){
        int q = partition(input, p, r);

        quickSort(input, p, q-1);
        quickSort(input, q+1, r);
    }
}

void hQuickSort(vector<int> &input, int p, int r){
    
    //T(n) = T(ax)+T((1-a)x) + x
    if (p < r){
        int q = hPartition(input, p, r);

        hQuickSort(input, p, q-1);
        hQuickSort(input, q+1, r);
    }
}

void tailQuickSort(vector<int> &input, int p, int r){
    //elevating the stack space load, which means, less resursion 
    //could not solve 7-4-c, looking for help here 
    
    while (p < r){
        int q = partition(input, p, r);

        quickSort(input, p, q-1);
        p = q+1;
    }
}

class Interval{
public:

    vector<int> left;
    int length; 
    //vector<int> length;
    
    Interval(){
    }
    
    Interval(const vector<int> &_left, int _length){
        left = _left;
        length = _length;
    }

    int IntervalpPartition(int p, int r){
    
        int tail = left[r];
        int curr = p;
        int prev = p-1;
        
        while (curr < r){
            
            //this compare process would take ???
            if (left[curr] <= tail - length){
                // > decrease, < increase
                //throw it to front
                prev++;
                exchange(left[prev], left[curr]);
            } else {
                //eat it, do nothing
            }
            
            //promise (prev, curr] is larger than prev, and finally prev is larger than [p, prev)
            curr ++;
        }
        
        exchange(left[prev + 1], left[r]);
        return prev + 1;
        
    }
    
    void qsInterval(int p, int r){
        
    }
    
};

int main()
{
    vector <int> test = {7,48, 15, 23, 59, 77, -5};
    vector <int> test2 = {2,2,2,2,2,2,2,2,2};
    vector <int> testh = {13,19,9,5,12,8,7,4,11,2,6,21};
    
    tailQuickSort(testh, 0, testh.size() - 1);
    
    for (const auto& i: testh){
        std::cout << i << ", ";
    }

    return 0;
}

