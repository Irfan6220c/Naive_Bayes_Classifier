#include <stdio.h>
#include <iostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include <string>
#include<sstream>

using namespace std;



int main(int argc, char *argv[])
	{
		char temp[10];
		int channel=4,samples=1000;
		int h,i=0,j,n,clas,c=0,row,col;		
		double sum,sum_of_squares=0,sum_of_absolutes=0;
		
		double **data=new double*[samples];
		
		for (int i=0;i<samples;i++)
			data[i]=new double[channel];
		
		double *RMS=new double[channel];
		double *WL=new double[channel];
		double *MAV=new double[channel];

		ifstream infile;
		ofstream outfile;
		outfile.open("./data/features.csv");
		
for(clas=0;clas<7;clas++)
		for (n=1;n<101;n++)
		
		{   ostringstream *convert0= new (ostringstream);
			ostringstream *convert1= new (ostringstream);
			string *line= new (string);
			string *Result0= new (string);
			string *Result1= new (string);
			string *adr= new (string);
			
			for(i=0;i<samples;i++)
					for (h=0; h<4; h++)
					data[i][h]=0;
				 
		*convert0 << clas;
		*Result0 = convert0->str();
		*convert1 << n;
		*Result1 = convert1->str();
		

		*adr="./raw_data/"+ *Result0 +"/"+ *Result1 + ".csv";
		
		infile.open(*adr);
		
        if(!infile) cout << "\nWhile opening a file an error is encountered" << endl;
		else { cout << "\nFile "<< (n)+(clas*100) <<" is successfully opened" << endl;}
		cout<<"reading data \n";	
		
		i=0;
		
		while(getline(infile,*line))

		{	c=0;j=0;h=0;

										
				while((*line)[c]!='\0')
			{	
						if ((*line)[c]==',')
						{temp[j]='\0';

						data[i][h]=atof(temp);
						c++; j=0; h++;
						continue;}
		
				temp[j]=(*line)[c];
				c++;j++;
	
			}
			temp[j]='\0';
			data[i][h]=atof(temp);
			i++;
		}
		
	
	infile.close();
	
	
	for(h=0;h<channel;h++)
		RMS[h]=0;

	for(h=0;h<channel;h++)
		WL[h]=0;

	for(h=0;h<channel;h++)
		MAV[h]=0;

	//calculating Features
	for(h=0;h<channel;h++)
	
	{	
		sum=0;
		sum_of_squares=0;
		sum_of_absolutes=0;
		
		for(row=0;row<samples;row++)
		{sum_of_squares=sum_of_squares+(data[row][h]*data[row][h]);
		sum_of_absolutes=sum_of_absolutes+abs(data[row][h]);}
		
		for(row=2;row<samples;row++)
		sum=sum+abs(data[row][h]-data[row-1][h]);


		RMS[h]=sqrt(sum_of_squares/samples);
		MAV[h]=sum_of_absolutes/samples;
		WL[h]=sum;
	}
	////////////////////////////////////////////////
	
		outfile<<(int)clas<<","<<RMS[0]<<","<<RMS[1]<<","<<RMS[2]<<","<<RMS[3]<<","
								<<MAV[0]<<","<<MAV[1]<<","<<MAV[2]<<","<<MAV[3]<<","
								<<WL[0]<<","<<WL[1]<<","<<WL[2]<<","<<WL[3]<<"\n";
	
	delete line;
	delete convert0;
	delete convert1;
	delete Result0;
	delete Result1;
	delete adr;
	
  }	

	outfile.close();
	cout<<"Features file is successfully created :) \n";
	getchar();
	return 0;


}




