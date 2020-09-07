#include"myNaiveBayes.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand


double naiveBayes::GPC(double value ,double u,double a)
{
	double probability=0;
	double power=0;
	probability=1/(sqrtf(2*pi*a));
	power=(pow((value-u),2))/(2*a);
	probability=probability*exp(-1*power);
	return probability;
	

}

void naiveBayes::result(){
	int ret;
	int no_of_true_results=0,no_of_false_results=0;
	double arr[no_of_features];
	 training_data[no_of_examples][no_of_features][no_of_classes];
	

	 int** result = new int*[2];
		for(int i = 0; i < 2; ++i)
			result[i] = new int[no_of_test_examples*no_of_classes];


	for(int k=0;k<no_of_classes;k++)
		 for(int i=0;i<no_of_test_examples;i++)
			{
			for(int j=0;j<no_of_features;j++)
					arr[j]=test_data[i][j][k];
			ret=predict(arr);
			result[0][k*10+i]=k;
			result[1][k*10+i]=ret;

				}
cout<<"\n*****The final Result is*****\n";
for(int i=0;i<2;i++)
/*{for(int j=0;j<no_of_test_examples*no_of_classes;j++) 
   	cout<<result[i][j]<<"\t";
	cout<<endl;}*/

for(int i=0;i<no_of_classes*no_of_test_examples;i++)
	{if(result[0][i]==result[1][i])
		no_of_true_results++;
	else
		no_of_false_results++;}

cout<<"\nTotal Number of True Predictions="<<no_of_true_results<<"\nTotal Number of wrong predictions="<<no_of_false_results;
for(int k=0;k<no_of_classes;k++)
{
	no_of_false_results=0;
	no_of_true_results=0;
	for(int i=0;i<no_of_test_examples;i++)
	{if(result[0][10*k+i]==result[1][10*k+i])
			no_of_true_results++;
		else
			no_of_false_results++;}

	cout<<"\n***Result of Class no."<<k<<"***";
	cout<<"\nNumber of true predictions="<<no_of_true_results<<"\nNumber of False predictions="<<no_of_false_results;
}

}


int naiveBayes::predict(double values[])
{
	
	int MLC=0;
	double** probabilities=new double*[no_of_classes];
	
	for(int i=0;i<no_of_classes;i++)
		probabilities[i]=new double[no_of_features];
	double* final_probabilities=new double[no_of_classes];

	for(int c=0;c<no_of_classes;c++)
		final_probabilities[c]=1;


	for(int c=0;c<no_of_classes;c++)
		for(int f=0;f<no_of_features;f++)
		   probabilities[c][f]=GPC(values[f],parameter[0][f][c],parameter[1][f][c]);
	
	
	
	for(int c=0;c<no_of_classes;c++)
		for(int f=0;f<no_of_features;f++)
			final_probabilities[c]=final_probabilities[c]*probabilities[c][f];

	for(int c=0;c<no_of_classes;c++)
		{if (final_probabilities[c]>final_probabilities[MLC])
			MLC=c;
			cout<<"\nClass no."<<c<<" probility="<<final_probabilities[c];     
								}
	
	
	
	cout<<"\nSelected Class is: "<<MLC;
	
	return MLC;
				

}

void naiveBayes::train()
{
	
	//cout<<"IN the training ";
    // cout<<class_count[2];
	double sum=0,diff=0;

	for(int i=0;i<no_of_classes;i++)
      for(int k=0;k<no_of_features;k++)
		{for(int j=0;j<class_count[i];j++)		
				sum=sum+data[j][k][i];
	
				parameter[0][k][i]=sum/class_count[i];sum=0;}
	
	for(int i=0;i<no_of_classes;i++)
     for(int f=0;f<no_of_features;f++)
		{for(int j=0;j<class_count[i];j++)		
		   diff=diff+pow((data[j][f][i]-parameter[0][f][i]),2);
				//cout<<diff<<"\t";
				parameter[1][f][i]=diff/class_count[i];	diff=0;}     
	  
}



void naiveBayes::percentTrain()
{
	
	//cout<<"IN the training ";
    // cout<<class_count[2];
	double sum=0,diff=0;

	for(int i=0;i<no_of_classes;i++)
      for(int k=0;k<no_of_features;k++)
		{for(int j=0;j<percent_class_count[i];j++)		
				sum=sum+training_data[j][k][i];
	
				parameter[0][k][i]=sum/percent_class_count[i];sum=0;}
	
	for(int i=0;i<no_of_classes;i++)
     for(int f=0;f<no_of_features;f++)
		{for(int j=0;j<percent_class_count[i];j++)		
		   diff=diff+pow((training_data[j][f][i]-parameter[0][f][i]),2);
				//cout<<diff<<"\t";
				parameter[1][f][i]=diff/percent_class_count[i];	diff=0;}     
	  
}

int naiveBayes::load(string fileName){
	char adr[100],temp[10],ch;
	int i,j,c,t=0;
	double f,temp_values[30];
	ifstream file(fileName);
	string line;
	current_class=0;
	for(int z=0;z<no_of_classes;z++)
			class_count[z]=0;
start:

//cout<<"\nEnter the address of the tranning data file.\nAdress should be like:\n\/home/root/Desktop/data.txt";
//cout<<"\nSample of the data file is given below.";
//cout<<"\nclassNo,feature1,feature2.....feature n";
//cin>>adr;
//
//            file.open (adr);
            if(!file) {cout << "\nWhile opening a file an error is encountered" << endl;
					   cout<<"Enter 'x' to exit Training.\n Or enter anyother key to Retry loading file with different address.";
					   if(getchar()=='x') return -1;
					   else goto start;}
			else { cout << "\nFile is successfully opened" << endl;}
			

		

	
	while(getline(file,line))

	{
		 
	
		
	    c=0;j=0;

		while(1)	{if (line[c]==','){ c++ ;break;}	temp[j]=line[c];c++;j++;}

	    temp[j]='\0';
		current_class=atoi(temp);
		//cout << endl<<current_class << endl;
		
	
	j=0;
	i=0;
		

	while(line[c]!='\0')
	{
	
	
		if (line[c]==',')
		{temp[j]='\0';
		data[(class_count[current_class])][i][current_class]=atof(temp);
		j=0;i++;c++;
		continue;}
		
		temp[j]=line[c];
	    c++;j++;
	
	}

			temp[j]='\0';
			data[(class_count[current_class])][i][current_class]=atof(temp);
			class_count[current_class]++;
	}		
			



return 1;


}

void naiveBayes::display(void)
{
	
	cout<<"\n\nOriginal Data array.\n";
	for(int c=0;c<no_of_classes;c++)
	{cout<<"class no."<<c<<endl;
	for(int j=0;j<class_count[c];j++)
		{for(int k=0;k<no_of_features;k++)
		cout<<data[j][k][c]<<"\t";
	cout<<endl;                   } cout<<endl<<endl;     }	
cout<<"\n\nTraining array.\n";
	for(int c=0;c<no_of_classes;c++)
		{cout<<"class no."<<c<<endl;
		for(int j=0;j<no_of_training_examples;j++)
			{for(int k=0;k<no_of_features;k++)
			cout<<training_data[j][k][c]<<"\t";
			cout<<endl;                   } cout<<endl<<endl;     }	

	cout<<"\n\ntest array.\n";
	for(int c=0;c<no_of_classes;c++)
		{cout<<"class no."<<c<<endl;
		for(int j=0;j<no_of_test_examples;j++)
			{for(int k=0;k<no_of_features;k++)
			cout<<test_data[j][k][c]<<"\t";
			cout<<endl;                   } cout<<endl<<endl;     }	
	
	
	cout<<"\n\nParameters array.\n";
for(int i=0;i<no_of_classes;i++)
{     cout<<"\n\nClass No."<<i<<endl;
	  for(int k=0;k<no_of_features;k++)
		{for(int j=0;j<2;j++)
			cout<<parameter[j][k][i]<<"\t\t\t";
			cout<<endl;}}
}


int  naiveBayes::randomData(int trainingPercent) {
  
	no_of_training_examples=class_count[0]*trainingPercent/100;
	no_of_test_examples=class_count[0]-no_of_training_examples;

	for(int i=0;i<no_of_classes;i++)
		percent_class_count[i]=no_of_training_examples;

int randomArr[100];
randomArray(100,randomArr);

int i=0;
for(i=0;i<no_of_training_examples;i++)
	for(int j=0;j<no_of_features;j++)
		for(int k=0;k<no_of_classes;k++)
	training_data[i][j][k]=data[randomArr[i]][j][k];

for(int t=0;t<no_of_test_examples;i++,t++)
	for(int j=0;j<no_of_features;j++)
		for(int k=0;k<no_of_classes;k++)
		test_data[t][j][k]=data[randomArr[i]][j][k];


//
//cout<<endl;
//  for(int i=0;i<100;i++)
//	  std::cout << ' ' << randomArr[i];




  return 0;
}