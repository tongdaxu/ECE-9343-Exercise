//16.1 An activity-selection problem

#include <utility>		// std::pair, std::make_pair
#include <string>		// std::string
#include <iostream>
#include <vector>
#include <stdio.h>
#include <climits>

using namespace std;

int updateSk(const vector <pair<int, int>> &data, vector <pair <int, int>> &solution, vector <pair <int, int>> &Sk, int i, int j){

    int k0 = -1;
    
    for (int k=i+1; k<j; k ++){
        if (data[k].first >= data[i].second && data[k].second <= data[j].first){
            Sk.push_back(data[k]);
            if (k0 == -1){
                k0 = k;
            }
        }
    }
    
    return k0;
    
}

void 
activityselectionrecursive
  (const vector <pair<int, int>> &data, vector <pair <int, int>> &solution, int i, int j)
{

    //if S_{ij} = null
    vector <pair<int, int>> Sk;
    int k0 = updateSk(data, solution, Sk, i, j);
    
    if ((int)Sk.size() == 0){
        return;
    } else {
        solution.push_back(Sk[0]);
        return activityselectionrecursive(data, solution, k0, j);
        //this is a tail recursion, very easy to build a iterate version
    }

}

void 
activityselection(const vector <pair<int, int>> &data, vector <pair <int, int>> &solution)
{
    
    int i = 0;
    int j = data.size() - 1;
    vector <pair<int, int>> Sk;
    
    //initialzie Sk, k0
    int k0 = updateSk(data, solution, Sk, i, j);
    
    while((int)Sk.size() != 0){
    
        solution.push_back(Sk[0]);
    
        //update Sk,k0
        Sk.clear();
        k0 = updateSk(data, solution, Sk, k0, j);

    }
}

int
main ()
{

  //mono increase order of end time

  vector < pair < int, int >>data = {
    pair <int, int> (INT_MIN,INT_MIN),
    pair < int, int >(1, 4),
    pair < int, int >(3, 5),
    pair < int, int >(0, 6),
    pair < int, int >(5, 7),
    pair < int, int >(3, 9),
    pair < int, int >(5, 9),
    pair < int, int >(6, 10),
    pair < int, int >(8, 11),
    pair < int, int >(8, 12),
    pair < int, int >(2, 14),
    pair < int, int >(12, 16),
    pair <int, int> (INT_MAX, INT_MAX)
  };


  vector < pair < int, int >>solution;
  vector < pair < int, int >>solutionPrime;
  
  activityselectionrecursive (data, solution, 0, 12);
  activityselection (data, solutionPrime);
  
  for (auto i : solution){
      cout<<i.first<<","<<i.second<<endl;
  }
  
  for (auto i : solutionPrime){
      cout<<i.first<<","<<i.second<<endl;
  }

  return 0;
}

