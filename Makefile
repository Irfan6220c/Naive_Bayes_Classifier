all:
		g++  classification.cpp ./include/myNaiveBayes.cpp ./include/myfunctions.cpp -o classification
		g++ featuresCal.cpp -o featuresCal
clean:
		rm featuresCal
		rm classification