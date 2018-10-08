/*
4-15-2. Matrix-chain multiplication
*/

#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>
#include <utility>
#include <unordered_map>

class sudoMatrix{
public:
    static int multiCount;
    int _row;
    int _column;
    explicit sudoMatrix(int row, int column){
        _row = row;
        _column = column;
    }
    
    sudoMatrix operator *(const sudoMatrix& _rh){
        if (_column != _rh._row){
            throw std::out_of_range("invalid matrix multiplication");
        } else {
            
            multiCount += _row*_column*_rh._column;
            return sudoMatrix(_row, _rh._column);
        }
    }
    
    void toString(){
        std::cout<<"Matrix row is: "<<_row<<", column is: "<<_column<<std::endl;
        std::cout<<"Totally multuply: "<<multiCount<<" times"<<std::endl;
    }   
    
};

int sudoMatrix::multiCount = 0;
//note: use :: to initilazie a static member of function

int count(const std::vector<sudoMatrix> &input, int p, int r){
    
    if (p>= r){
        return 0;
    } else {
        
        int localMin = INT_MAX;
        int tempP;
        int tempQ;
        
        for (int q = p; q < r; q++){
            //q = [p, r - 1], not sure why r-1 instead of r?
            int temp = count(input, p, q) + count(input, q+1, r) + input[p]._row*input[q]._column*input[r]._column;
            localMin = temp < localMin ? temp : localMin;
        }
        
        return localMin;
        // min (count(input, p, q) + count(input, q+1, r) + input[p].row*input[q].column*input[r].column)   
    }
}

int countMemory(const std::vector<sudoMatrix> &input, std::vector <std::vector<int>> &memory, int p, int r){
    
    if (p>= r){
        return 0;
    } else {

        if (memory[p][r] != -1){
            return memory[p][r];
        } //else ::
        
        int localMin = INT_MAX;
        
        for (int q = p; q < r; q++){
            //q = [p, r - 1], not sure why r-1 instead of r?
            int temp = countMemory(input,memory, p, q) + countMemory(input,memory, q+1, r) + input[p]._row*input[q]._column*input[r]._column;
            localMin = temp < localMin ? temp : localMin;
        }
        
         // the key is a pair p,r
        memory[p][r] = localMin;
        return localMin;
        // min (count(input, p, q) + count(input, q+1, r) + input[p].row*input[q].column*input[r].column)   
    }
}

int main()
{
    sudoMatrix A0(30, 35);
    sudoMatrix A1(35, 15);
    sudoMatrix A2(15, 5);
    sudoMatrix A3(5, 10);
    sudoMatrix A4(10, 20);
    sudoMatrix A5(20, 25);
    
    std::vector<sudoMatrix> test = {A0, A1, A2, A3, A4, A5};
    std::cout<<count(test, 0, test.size() - 1)<<std::endl;
    //initilazie n*n, but we only need n*(n-1)/2
    std::vector<int> submemory(test.size(), -1);
    std::vector<std::vector<int>> memory (test.size(), submemory);
    std::cout<<countMemory(test, memory, 0, test.size() - 1)<<std::endl;
    return 0;
}




