
#include <iostream>

using namespace std;

/*
Insertion Sort in C++
*/

void InsertionSort (int input[], int asize){
    
    int temp;
    int result [asize];
    
    for (int i = 1; i < asize; i++){
        
        temp = input[i];
        int j = i;
        
        while ((j>0) && (input[j] < input[j-1])){
            
            input[j] = input[j-1];
            input[j-1] = temp;
            j--;
        }
    }
    
    for (int k = 0; k<asize; k++){
        std::cout<<input[k]<<std::endl;
    }
    
}

int test1[] = {9,5,3,7,1,6};
int test2[] = {557,698,214,7706,254,749,3314,0,1575987};

int main()
{
    InsertionSort(test1, 6);
    InsertionSort(test2, 9);

    return 0;
}
