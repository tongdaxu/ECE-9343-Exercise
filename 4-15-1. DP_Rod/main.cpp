/*
4-15-1. Dynamic Programming - Rod cutting problem
*/
#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>

int p(int i){
    
    if (i == 1){
        return 1;
    } else if (i == 2){
        return 5;
    } else if (i == 3){
        return 8;
    } else if (i == 4){
        return 9;
    } else if (i == 5){
        return 10;
    } else if (i == 6){
        return 17;
    } else if (i == 7){
        return 17;
    } else if (i == 8){
        return 20;
    } else if (i == 9){
        return 24;
    } else if (i == 10){
        return 30;
    } else {
        throw std::out_of_range("invalid i input");
    }
    
    return -1;
}

int cutRod (int n){
    
    if (n == 0){
        return 0;
    } 
    
    //else :
    
    int q = INT_MIN;
    
    //not that this cost O 2^n
    for (int i = 1; i <= n; i++){
        int r = p(i) + cutRod(n-i);
        q = q > r ? q : r;
    }
    
    return q;
    
}

int main()
{
    std::cout<<cutRod(10)<<std::endl;
    
    
    
    
    printf("Hello World");

    return 0;
}


