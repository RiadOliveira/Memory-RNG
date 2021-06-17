#include <typeinfo>

template <typename T>
T GRand(T begin, T end) {
	static short ind = -1;
	ind++;

	static T previousValues[4] = {0}; //How much bigger this array is, more random the result will be, but will need more memory.

	ind = (ind == 4) ? 0 : ind;

	unsigned short lengthOfInterval;
	bool hasNegativeValues = false;

	if(begin < 0 || end < 0) { //If has some negative value, makes the interval positive.
		hasNegativeValues = true; //At the end, if is true, has 50% chance to return a negative number.

		//Gets positive values to make values comparsions.
		begin = begin > 0 ? begin : -begin;
		end = end > 0 ? end : -end;

		end = end > begin ? end : begin; //Receive the high value.
		begin = 0; //Starts on zero in order to reach all numbers (in module) of the original interval.
	}

	lengthOfInterval = (end-begin) + 1;
	
	long adressValue = long(&previousValues[ind])+previousValues[ind]; //Uses variable adress(random value) plus the previous value obtained.

	for(int i=0 ; i<ind ; i++) { //Created to increase randomness of the value.
		if(i%2 == 0) {
			adressValue += previousValues[i];
		} else {
			adressValue /= (previousValues[i] == -1) ? 2 : previousValues[i] + 1;
		}
	}

	long randomValue = adressValue%lengthOfInterval; //Gets some value pertencent to interval.

	previousValues[ind] = begin+randomValue; //Sum to beginValue to guarantee that the result will be on interval.

	double point = previousValues[0];
	
	if((typeid(begin) == typeid(float) || typeid(begin) == typeid(double)) && previousValues[ind] != end) {
		bool isGood;

		for(int i=0 ; i<ind ; i++) {
			if(i%2 == 0) {
				point *= previousValues[i];
			} else {
				point /= (previousValues[i] == -1) ? 2 : (previousValues[i] + 1);
			}
		}

		do {
			isGood = true;

			point += ((begin+1)/(end+1))*randomValue; //+1 is for cases where one of those values is 0.
			point -= int(point); //Get floating part.

			if((previousValues[ind]+point) > end) { //Because the point will be added to the value.
				isGood = false;
			}

		} while(!isGood);

		previousValues[ind] += point; //Adds more randomness on floating point to the value.
	}

	if(hasNegativeValues && previousValues[ind] != 0) {
		return bool(adressValue%2) ? previousValues[ind] : -previousValues[ind]; //50% chance to get a negative number.
	} else {
		return previousValues[ind];	
	}	
};