#include"myfunctions.h"

// random generator function:
int myrandom (int i) { return std::rand()%i;}

int randomArray(int array_size,int *arr)
{

	  std::srand ( unsigned ( std::time(0) ) );
  std::vector<int> myvector;

  // set some values:
  for (int i=0; i<array_size; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  // using built-in random generator:
  std::random_shuffle ( myvector.begin(), myvector.end() );

  // using myrandom:
  std::random_shuffle ( myvector.begin(), myvector.end(), myrandom);

  // print out content:
  /*std::cout << "myvector contains:";*/
 int c=0;
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
  {arr[c]=*it;
  c++;
	/*  std::cout << ' ' << *it;*/

 

  }
  /* std::cout << '\n';*/
  return 0;
}

