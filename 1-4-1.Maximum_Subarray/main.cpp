/*
4-1 Recursive Max Subarray Sum O(n)
4-1-5 Linear Max Subarray Sum O(n)
*/

#include <iostream>
#include <vector>
#include <limits>       //limits
#include <algorithm>    // std::max

#define INFINITY std::numeric_limits<int>::max()

using namespace std;

int maxSubLinear(vector <int> &input){
    
    int maxSub = -INFINITY;
    int maxSubTail = -INFINITY;
    
    for (int i = 0; i < input.size(); i++){
        
        /*keep tracking of maxSubTail, this cost O(n) alone*/
        
        if (maxSubTail < 0){
            maxSubTail = input[i];
        } else {
            maxSubTail += input[i];
        }
        
        /*then worry about if input[i] should be included, this cost O(n) alone*/
        
        if (maxSubTail > maxSub){
            maxSub = maxSubTail;
        } else {
            //pass, do nothing
        }
    }
    
    return maxSub;
    
}

int maxSub(vector<int> &input, int start, int end){
    
    if (start<end){
    
        int mid = (start + end)/2;
        
        int leftMax = -INFINITY;
        int rightMax = -INFINITY;
        int currentLeftSum = 0;
        int currentRightSum = 0;
        
        for (int i = mid; i > -1; i--){
            
            currentLeftSum += input[i];
            
            if (currentLeftSum > leftMax){
                leftMax = currentLeftSum;    
            }
            
        }
        
        for (int j = mid + 1; j < end + 1; j ++){
            
            currentRightSum += input[j];
            
            if (currentRightSum > rightMax){
                rightMax = currentRightSum;    
            }
            
        }
        
        int midMax = leftMax + rightMax;
        
        return std::max ((std::max(maxSub (input, start, mid),maxSub (input, mid + 1, end))),midMax);
    
    } else {
        
        return input[start];
        
    }

}

int main()
{
    std::vector<int> test = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    std::cout<<"Recursively: "<<maxSub(test, 0, 15)<<std::endl;
    std::cout<<"Non-recursively: "<<maxSubLinear(test)<<std::endl;
    return 0;
}
