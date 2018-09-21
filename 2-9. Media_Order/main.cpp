/*
Chapter 9 Median and Order
input: 1 \le i \le n
output: element x larger than exactly i-1 other element of A

*/
#include <stdio.h>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

void exchange(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

int partition(vector<int> &input, int p, int r){
    //partition or rearrange

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

int brutualMin(const vector<int> nums){
    
    int Min = INT_MAX;
    for (auto i : nums){
        Min = i<Min?i:Min;
    }
    
    return Min;
    
}

vector<int> twoThirdM (vector<int> &nums){
    
    //make every input even, in 3/2 [n] time
    if (nums.size()%2 != 0){
        nums.push_back(nums[nums.size()-1]);
    }
    
    vector<int> result;
    
    int max = INT_MIN;
    int min = INT_MAX;
    
    for (int i = 0; i<nums.size(); i += 2){

        if (nums[i]>nums[i+1]){
            
            max = max > nums[i]? max : nums[i];
            min = min < nums[i+1]? min : nums[i+1];
            
        } else {
            
            max = max > nums[i+1]? max : nums[i+1];
            min = min < nums[i]? min : nums[i];
            
        }
        
    }
    
    result.push_back(max);
    result.push_back(min);
    
    return result;
    
}

int selection(vector<int> &nums, int p, int r, int i){
    //Input: A set of n (distinct) numbers and an integer i
    //Output: The element x  that is larger than exactly i - 1 other elements of A (rank of i)
    if (p==r){
        return nums[p];
    }
    
    int q = partition(nums, p, r);
    
    int k = q-p+1;
    
    if(k<i){
        return selection(nums, q+1, r, i-k);
    }else if(k>i){
        return selection(nums, p, q-1, i);
    }else{
        //q==r
        return nums[q];
    }
}

int main()
{
    vector<int> test = {7,6,4,8,7,9,12,5987};
    
    //cout<<brutualMin(test)<<endl;
    
    int j = selection(test, 0, test.size()-1, 10);
    cout<<j;

    return 0;
}

