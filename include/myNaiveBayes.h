#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include"myfunctions.h"


#define pi 3.14
#define no_of_examples 150
#define no_of_features 12 
#define no_of_classes 7
using namespace std;

class naiveBayes
{
	unsigned int class_count[no_of_classes],current_class,no_of_test_examples,no_of_training_examples,percent_class_count[no_of_classes];
	double data[no_of_examples][no_of_features][no_of_classes];
	double training_data[no_of_examples][no_of_features][no_of_classes];
	double test_data[no_of_examples][no_of_features][no_of_classes];
	double parameter[2][no_of_features][no_of_classes];
	double GPC(double value ,double u,double a);
	
	public:
	int  randomData(int trainingPercent);
	int predict(double values[]);
	void train();
	int load(string fileName);
	void display(void);
	void percentTrain();
	void result();
};