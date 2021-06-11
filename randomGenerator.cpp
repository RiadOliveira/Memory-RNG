#include <typeinfo>

template <typename T>
T GRand(T begin, T end) {
	static T previousValue = 0;
	
	unsigned short lengthOfInterval = (end-begin)+1;
	
	long adressValue = long(&previousValue)+previousValue; //Uses variable adress(random value) plus the previous value obtained.
	long randomValue = adressValue%lengthOfInterval; //Gets some value pertencent to interval.

	double point = 0;
	
	if(typeid(begin) == typeid(float) || typeid(begin) == typeid(double)) {
		point = (previousValue+1)*((begin+1)/(end+1))*randomValue; //+1 is for cases where one of those values is 0.

		point -= int(point); //Get floating part.
	}

	previousValue = begin+randomValue; //Sum to beginValue to guarantee that the result will be on interval.
	previousValue = point ? previousValue+point : previousValue; //If the function was call with floating values.
	
	return previousValue;
};