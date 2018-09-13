/*
6-3 Young tableaus c,d,e,f
*/
#include <stdio.h>
#include <vector>
#include <iostream>
#include <limits>

#define INFINITY std::numeric_limits<int>::max()

using namespace std;

void exchange(int &a, int &b){
    
    int temp = a;
    a = b;
    b = temp;
    
}

class youngTableaus{
public:
    
    vector<int> data;
    int m;
    int n;
    
    youngTableaus(){}
    
    youngTableaus(const vector<int> &input, const int &mm, const int &nn){
        
        data = input;
        m = mm;
        n = nn;
        
    }
    
    int indexCal(int i, int j){
        
        return i + m*j;
        
    }
    
    void youngTabify(int i, int j){
        //O = (m+n)
        //i = 0-m-1, j = 0-n-1
        
        int curr = indexCal(i,j);
        
        if (i < m - 1){
            
            int next = indexCal(i+1, j);
            
            if (data[curr] > data[next]){
                exchange(data[curr], data[next]);
                youngTabify(i+1, j);
            }//else pass
            
        }//else pass
        
        if (j < n-1){
            
            int next = indexCal(i, j+1);
            
            if (data[curr] > data[next]){
                exchange(data[curr], data[next]);
                youngTabify(i, j+1);
            }//else pass
            
        }//else pass

    }
    
    bool decreaseKey(int i, int j, int key){
        //decreaseKey in O(m+n)
        //exchange with the max only
        
        bool ifEqual = false;
        int curr = indexCal(i,j);
        
        if (data[curr] < key){
            return ifEqual;
        } else {
            //decrease data first'
            data[curr] = key;
        }
        
        while (i>0 || j>0){
            
            bool iPass = true;
            bool jPass = true;
            curr = indexCal(i,j);
            
            if (i>0 && j>0){
                
                int prevI = indexCal(i-1, j);
                int prevJ = indexCal(i, j-1);
                
                int prevMax = data[prevI]>data[prevJ] ? prevI:prevJ;
                if (data[prevMax] > data[curr]){
                    exchange(data[prevMax], data[curr]);
                    if (prevMax == prevI){
                        i--;
                        iPass = false;
                    }else {
                        j--;
                        jPass = false;
                    }
                } else if (data[prevMax] == data[curr]){
                    ifEqual = true;
                }
                
            } else if (i > 0){
                
                int prev = indexCal(i-1, j);
                
                if (data[prev] > data[curr]){
                    iPass = false;
                    exchange(data[prev], data[curr]);
                    i--;
                } else if (data[prev] == data[curr]){
                    ifEqual = true;
                }
                
            }else if (j > 0){
                
                int prev = indexCal(i, j-1);
                
                if (data[prev] > data[curr]){
                    jPass = false;
                    exchange(data[prev], data[curr]);
                    j--;
                } else if (data[prev] == data[curr]){
                    ifEqual = true;
                }
                
            }//else pass
            
            if (iPass&&jPass){
                break;
            }
            
        }
        
        return ifEqual;
        
    }
    
    int extractMin(){
    //6.3-b, extractMin in O(m+n)
    
        int temp = data[0];
        data[0] = INFINITY;
        youngTabify(0,0);
        
        return temp;
        
    }
    
    void insert(int key){
    //6-3.d, insert in O(m+n)
        if (data[data.size()-1] != INFINITY){
            cout<<"YT is full"<<endl;
        } else {
            decreaseKey(m-1, n-1, key);
        }
    }
    
    void buildYoungTab(const vector<int> &input, int mm, int nn){
        //6-3.e, insert n*m element, cost O(mn(m+n)) time, then extractMin n*m element, cost(mn(m+n)) time;
        //for a n*n vector, this cost O(n^3) in sum
        
        m = mm;
        n = nn;
        
        for (int i = 0; i < input.size(); i++){
            data.push_back(INFINITY);
        }
        
        for(int i = 0; i < input.size(); i++){
            insert(input[i]);
            for (int i = 0; i < data.size(); i++){
                //cout<<data[i]<<endl;
            }
            //cout<<"i = "<<i<<endl;
        }
        
    }
    
    void youngTabSort(const vector<int> &input, int mm, int nn){
        //6-3.e, insert n*m element, cost O(mn(m+n)) time, then extractMin n*m element, cost(mn(m+n)) time;
        //for a n*n vector, this cost O(n^3) in sum
        
        buildYoungTab(input, mm, nn);
        
        while (data[0] != INFINITY){
            cout<<extractMin()<<endl;
        }
    }
    
    bool find(int key){
        //6-3.f find an item in O(m+n) time complexity
        if (key == data[data.size()-1]){
            return true;
        } else if (key > data[data.size()-1]){
            return false;
        }else {
            return decreaseKey(m-1, n-1, key);
        }
    }
    
    void toString(){
        for (int i = 0; i < data.size(); i++){
            cout<<data[i]<<endl;
        }
    }
    
};

int main()
{
    vector<int> test = {2,5,8,9,3,6,18,0};
    youngTableaus testYT;
    //testYT.youngTabSort(test, 4, 2);
    
    vector<int> test2 = {2,5,8,9,3,6,18,0};
    youngTableaus testYT2;
    testYT2.buildYoungTab(test2, 4, 2);
    testYT2.toString();
    cout<<testYT2.find(11)<<endl;
    cout<<testYT2.find(9)<<endl;
    
    return 0;
}



