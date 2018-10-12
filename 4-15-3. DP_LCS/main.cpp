/*
4.15-4. Longest common subsequence
*/

#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>
#include <utility>
#include <unordered_map>
#include <string>

int LCS(std::string x, int m, std::string y, int n){
    
    if (m < 0 || n < 0){
        return 0;
        
    } else {
     
        if (x[m] == y[n]){
            return LCS(x, m-1, y, n-1) + 1;    
        } else {
            //not easy to get a result directly
            int tempX = LCS(x, m-1, y, n);
            int tempY = LCS(x, m, y, n-1);
            
            if (tempX > tempY){
                return tempX;
            } else {
                return tempY;
            }
        }
    }
}


void printResult (const std::string &x, int m, const std::string &y, int n, const std::vector<std::vector<char>> &action){
    if (m == 0 || n == 0){
        return;
    } else {
        if (action[m][n] == 'Q'){
            printResult(x, m-1, y, n-1, action);
            std::cout<<x[m];
        } else if (action[m][n] == 'A'){
            printResult(x, m-1, y, n, action);
        } else {
            //action[m][n] == 'W'
            printResult(x, m, y, n-1, action);
        }
    }
}

void printSimple (const std::string &x, int m, const std::string &y, int n, const std::vector<std::vector<int>> &memory){
    //Exercise 15.4-2
    if (m == 0 || n == 0){
        return;
    } else {
        if (x[m] == y[n]){
            printSimple(x, m-1, y, n-1, memory);
            std::cout<<x[m];
        } else if (memory[m-1][n] > memory[m][n-1]){
            printSimple(x, m-1, y, n, memory);
        } else {
            //memory[i-1][j] < memory[i][j-1]
            printSimple(x, m, y, n-1, memory);
        }
    }
}

int LCSMemory(const std::string &x, int m, const std::string &y, int n, std::vector<std::vector<int>> &memory, std::vector<std::vector<char>> &action){
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            
            if (x[i] == y[j]){
                action[i][j] = 'Q';
                memory[i][j] = memory[i-1][j-1] + 1;
            } else {
                action[i][j] = memory[i-1][j] > memory[i][j-1] ? 'A' : 'W';
                memory[i][j] = memory[i-1][j] > memory[i][j-1] ? memory[i-1][j] : memory[i][j-1];
            }
        }
    }
    
    std::cout<<"LCS Length is: "<<memory[m][n]<<std::endl;
    std::cout<<"LCS is: ";
    printResult (x, m, y, n, action);
    std::cout<<std::endl;
    return memory[m][n];
    
}

int LCSMemorySimple(const std::string &x, int m, const std::string &y, int n, std::vector<std::vector<int>> &memory){
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            
            if (x[i] == y[j]){
                memory[i][j] = memory[i-1][j-1] + 1;
            } else {
                memory[i][j] = memory[i-1][j] > memory[i][j-1] ? memory[i-1][j] : memory[i][j-1];
            }
        }
    }
    
    std::cout<<"LCS Length is: "<<memory[m][n]<<std::endl;
    std::cout<<"LCS is: ";
    printSimple (x, m, y, n, memory);
    std::cout<<std::endl;

    return memory[m][n];
    
}

int LCSMemory2Min(const std::string &x, int m, const std::string &y, int n){
    //Exercise 15-4.4-1, LCS in min (m,n) space complexity
    int i, j = 1;
    
    std::vector<int> curr(n+1, 0);
    std::vector<int> prev(n+1, 0);
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            
            if (x[i] == y[j]){
                curr[j] = prev[j-1] + 1;
            } else {
                curr[j] = prev[j] > curr[j-1] ? prev[j] : curr[j-1];
            }
        }
        prev = curr;
    }


    std::cout<<"LCS Length with 2 mini step is: "<<curr[n]<<std::endl;
    return curr[n];
    
}

int LCSMemoryMin(const std::string &x, int m, const std::string &y, int n){
    //Exercise 15-4.4-1, LCS in min (m,n) space complexity
    int i, j = 1;
    
    std::vector<int> curr(n+1, 0);
    std::vector<int> prev(n+1, 0);
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            
            if (x[i] == y[j]){
                curr[j] = curr[j-1] + 1;
            } else {
                curr[j] = curr[j] > curr[j-1] ? curr[j] : curr[j-1];
            }
        }
        //prev = curr;
    }


    std::cout<<"LCS Length with mini step is: "<<curr[n]<<std::endl;

    return curr[n];
    
}


int LCSRealMemory(const std::string &x, int m, const std::string &y, int n, std::vector<std::vector<int>> &memory){
    //Exercise 15.4-3: recursive memory with O(mn) time
    
    if (m == 0 || n == 0){
        return 0; 
    } else {
        
        if (memory[m][n] != 0){
            return memory[m][n];
        } else {
            if (x[m] == y[n]){
                memory[m][n] = LCSRealMemory(x, m-1, y, n-1, memory) + 1;
                return memory[m][n];
            } else {
                int temp1 = LCSRealMemory(x, m-1, y, n, memory);
                int temp2 = LCSRealMemory(x, m, y, n-1, memory);
                
                memory[m][n] = temp1 > temp2 ? temp1 : temp2;
                return memory[m][n];
            }
        }
    }
}

std::string LongestIncrease(const std::string &s, int m){
    
    if (m == 0){
        return std::string(1, s[0]);
    } else {
        
        std::string prev = LongestIncrease(s, m-1);
        
        if (s[m] > prev[prev.size()-1]){
            return prev + s[m];
        } else {
            return prev;
        }
        
    }
    
}
    
int main()
{
    std::string S1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    std::string S2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    
    std::vector<int> row (S2.size(), 0);
    std::vector<std::vector<int>> memory (S1.size(), row);
    std::vector<char> Arow (S2.size(), '-');
    std::vector<std::vector<char>> action (S1.size(), Arow);
    LCSMemory(S1, S1.size() - 1, S2, S2.size()-1, memory, action);
    LCSMemorySimple(S1, S1.size() - 1, S2, S2.size()-1, memory);
    
    //Exercise 15.4-4
    LCSMemory2Min(S1, S1.size() - 1, S2, S2.size()-1);
    LCSMemoryMin(S1, S1.size() - 1, S2, S2.size()-1);
    
    //Exercise 15.4-1
    std::string S3 = "10010101";
    std::string S4 = "010110110";
    
    std::vector<int> rowA (S4.size(), 0);
    std::vector<std::vector<int>> memoryA (S3.size(), rowA);
    std::vector<char> ArowA (S4.size(), '-');
    std::vector<std::vector<char>> actionA (S3.size(), ArowA);
    //LCSMemory(S3, S3.size() - 1, S4, S4.size()-1, memoryA, actionA);
    std::cout<<"LCS Length is: "<<LCSRealMemory(S3, S3.size() - 1, S4, S4.size()-1, memoryA)<<std::endl;
    
    //Exercise 15.4-5
    std::string S5 = "DABC";
    std::cout<<LongestIncrease(S5, S5.size() - 1)<<std::endl;;
    
    return 0;
}

