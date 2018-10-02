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
    } //else
    
    int q = INT_MIN;
    
    //not that this cost O 2^n
    for (int i = 1; i <= n; i++){
        int r = p(i) + cutRod(n-i);
        q = q > r ? q : r;
    }
    
    return q;
    
}


int memoryRodCutAid(int n, std::vector<int> &_memory){
    
    if (_memory[n]>= 0){
        return _memory[n];
    }
    
    int q = 0;
    
    if (n != 0){
        q = INT_MIN;
        
        for (int i = 1; i <= n; i++){
            int r = p(i) + memoryRodCutAid (n-i, _memory);
            q = q > r ? q : r;
        }
    } //else: pass
    
    _memory[n] = q;
    return q;
}

int memoryRodCut(int n){
    
    std::vector<int> memory(n+1, INT_MIN);
    //just to avoid the trouble
    //write the function separately, or the vector has to be static
    
    return memoryRodCutAid(n, memory);
    
}

int memoryRodCutExtAid(int n, std::vector<int> &_memory, std::vector<int> &_choice){
    //Exercise 15.1-4
    if (_memory[n]>= 0){
        return _memory[n];
    }
    
    int q = 0;
    
    if (n != 0){
        q = INT_MIN;
        
        for (int i = 1; i <= n; i++){
            int r = p(i) + memoryRodCutAid (n-i, _memory);
            _choice[n] = r > q ? i : _choice[n];
            q = q > r ? q : r;
        }
    } //else: pass
    
    _memory[n] = q;
    return q;
}

void memoryRodCutExt(int n){
    
    std::vector<int> memory(n+1, INT_MIN);
    std::vector<int> choice(n+1, 0);
    //just to avoid the trouble
    //write the function separately, or the vector has to be static
    
    std::cout<< memoryRodCutExtAid(n, memory, choice) <<std::endl;
    while (n > 0){
        std::cout<<choice[n]<<std::endl;
        n = n - choice[n];
    }
    
}

int upRodCut(int n){
    std::vector<int> memory;
    memory.push_back(0);
    
    for (int i = 1; i <= n; i++){
        int q = INT_MIN;
        for (int j = 1; j <= i; j++){
            int r = p(j) + memory[i-j];
            q = q > r ? q : r;
        }
        
        //memory[i] = q
        memory.push_back(q);
    }
    return memory[n];
}

int upRodCutCost(int n, int c){
    //Exercise 15.1-3, cutting with cost c
    std::vector<int> memory;
    memory.push_back(0);
    
    for (int i = 1; i <= n; i++){
        int q = INT_MIN;
        for (int j = 1; j <= i; j++){
            
            int r;
            
            if (i-j == 0){
               r = p(j) + memory[i-j]; 
            } else {
               r = p(j) + memory[i-j] - c;
            }
            
            q = q > r ? q : r;
        }
        
        //memory[i] = q
        memory.push_back(q);
    }
    return memory[n];
}

std::vector<std::vector<int>> upRodCutExt(int n){
    
    std::vector<std::vector<int>> result; 
    std::vector<int> memory (n+1, 0);
    std::vector<int> choice (n+1, 0);
    
    for (int i = 1; i <= n; i++){
        int q = INT_MIN;
        for (int j = 1; j <= i; j++){
            int r = p(j) + memory[i-j];
            choice[i] = q < r ? j : choice[i];
            q = q < r ? r : q;
        }
        
        //memory[i] = q
        memory[i] = q;
    }
    
    result.push_back(memory);
    result.push_back(choice);
    return result;
}

void printRod(int n){
    std::vector<std::vector<int>> getResult = upRodCutExt(n);
    while (n > 0){
        std::cout<<getResult[1][n]<<std::endl;
        n = n - getResult[1][n];
    }
}

int upFibnocci(int n){
    //Fibnocci in O(n)
    std::vector<int> memory (n+1, 0);
    //0 is unused, with memory[n] exist
    int i = 1;
    
    while (i <= n){
        
        if (i == 1){
            memory[i] = 1;
        } else if (n == 2){
            memory[i] = 1;
        } else {
            memory[i] = memory[i-1] + memory[i-2];
        }
        
        i++;
    }
    
    return memory[n];
}


//return unordered_map::end in O(1) time 

int main()
{
    //std::cout<<cutRod(10)<<std::endl;
    
    std::cout<<upRodCutCost(9, 1)<<std::endl;
    //cutting with cost
    
    std::cout<<upRodCut(9)<<std::endl;
    //cutting up to top
    
    printRod(9);
    //cutting with result print
    
    memoryRodCutExt(10);
    //cutting with memory result print
    
    std::cout<<upFibnocci(30)<<std::endl;
    
    return 0;
}


