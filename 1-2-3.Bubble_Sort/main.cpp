
/*2-2 bubble sort*/

#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &input){
    
    for (int i = input.size(); i > 1; i--){
        
        for (int j = 0; j < i - 1; j++){
            
            if (input[j] > input[j+1]){
                
                int temp = input[j];
                input[j] = input[j+1];
                input[j+1] = temp;
                
            }
        }
    }
}

int main()
{
    vector<int> test = {5,32,8,7,2598743,15,-17,9};
    bubbleSort (test);
    
    for (int i = 0; i< test.size(); i++){
        
        cout<<test[i]<<endl;
        
    }
    
    return 0;
}
