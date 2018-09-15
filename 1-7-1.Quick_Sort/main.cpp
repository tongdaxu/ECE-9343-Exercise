/*
7-1 quickSort and its reverse
7-3 random quickSort
Exercise 7.1-4
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

void quickSort(vector<int> &input, int p, int r){
    //T(n) = T(ax)+T((1-a)x) + x
    

    if (p < r){
        int q = partition(input, p, r);

        quickSort(input, p, q-1);
        quickSort(input, q+1, r);
    }
}

int main()
{
    vector <int> test = {7,48, 15, 23, 59, 77, -5};
    vector <int> test2 = {2,2,2,2,2,2,2,2,2};
    quickSort(test, 0, test.size() -1);
    
    for (const auto& i: test){
        std::cout << i << ", ";
    }

    return 0;
}
