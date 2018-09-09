
/*
Merge Sort in CLRS MERGE.A; p; q; r;
*/

#include <iostream>
#include <vector>
#include <limits>

#define INFINITY std::numeric_limits<int>::max()

using namespace std;

void
Merge (std::vector < int >&input, int aStart, int aEnd, int bEnd)
{

  vector < int >subA;
  vector < int >subB;

  int bStart = aEnd + 1;

  for (int i = aStart; i < aEnd + 1; i++)
    {
      subA.push_back (input[i]);
    }

  for (int i = bStart; i < bEnd + 1; i++)
    {
      subB.push_back (input[i]);
    }

  subA.push_back (INFINITY);
  subB.push_back (INFINITY);

  /*
     slice into subA, subB;
     add a sential node at the end, now subA.size() = aEnd - aStart + 2; 
   */

  int counterA = 0;
  int counterB = 0;
  int counterR = aStart;

  /*
     Merge Sort
   */

  while (counterR < (bEnd + 1))
    {

      std::cout << "inside start: " << aStart << std::endl;

      if (subA[counterA] < subB[counterB])
	{

	  input[counterR] = subA[counterA];
	  counterA++;

	}
      else
	{

	  input[counterR] = subB[counterB];
	  counterB++;

	}

      counterR++;

    }

  std::cout << "one merge complete" << std::endl;

}

void
MergeSort (std::vector < int >&input, int start, int end)
{

  if (start < end)
    {

      int mid = (start + end) / 2;
      MergeSort (input, start, mid);
      MergeSort (input, mid + 1, end);

      Merge (input, start, mid, end);

    }

}

int
main ()
{
  vector < int >vect
  {
  -9, 55, 0, 7, 14, 5921, 56, 1, 10, 20, 30, 15, 25, 35};
  MergeSort (vect, 0, vect.size () - 1);

  for (int i = 0; i < vect.size (); i++)
    {

      std::cout << vect[i] << std::endl;

    }

  return 0;
}
