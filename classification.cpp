#include "./include/myNaiveBayes.h"
#include "./include/myfunctions.h"
#include <string>
using namespace std;


int main(int argc, char *argv[])
{
	naiveBayes classifier;
	int ret;
	//extracting arguments 
	if (argc>1) {
		string fileName=argv[1];
		ret=classifier.load(fileName);}
	else
	{
		ret=classifier.load("./data/allscaled.csv");
	}
	

	
	

	
	//classifier.train();
	classifier.randomData(90);
	classifier.display();
	classifier.train();
	classifier.result();

	cout<<"\nHit enter to exit.";
	getchar();
	return 0;
} 