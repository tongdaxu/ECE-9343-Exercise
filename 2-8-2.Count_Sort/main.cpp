/*
8. sorting in linear time
8.2 counting sort
*/
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

//assume that we know the max = k
vector<int> countingSort(const vector<int> &nums, int k){
    
    vector<int> c(k+1, 0);
    vector<int> b(nums.size(),0);
    
    for (const auto& i: nums){
        c[i] ++;
    }
    
    //c now contains the element number of each val
    
    for (int i=1; i<=k; i++){
        c[i] += c[i-1];
    }
    
    //c now contains the numver of element \le than i
    //Ex 8.2-4, just return c[ceil(b)] - c[floor(a)] in O(1)
    //Build up of c takes O(n+k)
    
    for (int j = nums.size() - 1; j >= 0; j--){
        //c[nums[i] - 1] is the place that nums[i] should stay
        //Ex 8.2-3 note that it works for j 0~n, but lose stability 
        b[c[nums[j]] - 1] = nums[j];
        c[nums[j]]--;
    }
    
    return b;
    
}

int main()
{
    vector<int> test = {2,5,3,0,2,3,0,3};
    vector<int> out = countingSort(test, 5);
    
    for (const auto& i: out){
        cout<<i<<", ";
    }
    return 0;
}

