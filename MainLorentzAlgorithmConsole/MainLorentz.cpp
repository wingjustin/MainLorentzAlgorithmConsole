#include "MainLorentz.h"

using namespace MainLorentzAlgorithm;

RepetitionLocationCollection MainLorentz::FindRepetitions(string text) {
	RepetitionLocationCollection locationCollection;
	FindRepetitions(text, 0, (static_cast<int>(text.length())) - 1, &locationCollection);
	return locationCollection;
}

void MainLorentz::FindRepetitions(string& text, const int startIndex, const int endIndex, RepetitionLocationCollection* locationCollection) {
	if (startIndex >= endIndex)
		return;
	const int divideIndex = (startIndex + endIndex) >> 1;

	//do partition first
	FindRepetitions(text, startIndex, divideIndex, locationCollection);
	FindRepetitions(text, divideIndex + 1, endIndex, locationCollection);

	const int length = endIndex - startIndex + 1;

	const int leftLength = divideIndex - startIndex + 1;
	const int rightLength = endIndex - divideIndex;
	const string left = text.substr(startIndex, leftLength);
	const string right = text.substr(divideIndex + 1, rightLength);

	const int middleIndex = divideIndex - startIndex;

	string k2_str;
	k2_str.append(right);
	k2_str.append(1, '`');
	k2_str.append(left);
	//left repetition
	int* z_Left_k1 = NULL;
	int z_Left_k1_Length = ZFunction::GetReverseZArray(left, z_Left_k1);

	int* z_Left_k2 = NULL;
	int z_Left_k2_Length = ZFunction::GetZArray(k2_str, z_Left_k2);

	//right repetition
	int* z_Right_k1 = NULL;
	int z_Right_k1_Length = ZFunction::GetZArray(right, z_Right_k1);

	int* z_Right_k2 = NULL;
	int z_Right_k2_Length = ZFunction::GetReverseZArray(k2_str, z_Right_k2);

	for (int cntr = 0; cntr < length; cntr++) {
		// left repetition
		//find the same char of the right first char
		int zIndex = 0;
		if (cntr <= middleIndex) {
			//check if it is repetition
			int repetitionLength = leftLength - cntr; // Length(left) - cntr
			zIndex = cntr - 1;
			int k1 = zIndex < 0 || zIndex >= z_Left_k1_Length ? 0 : z_Left_k1[zIndex]; // previous char of cntr conver to z array index of left
			zIndex = rightLength + 1 + cntr;
			int k2 = zIndex < 0 || zIndex >= z_Left_k2_Length ? 0 : z_Left_k2[zIndex]; // this char of cntr conver to z array index of "right left"

			if (k1 + k2 >= repetitionLength)
				LeftCovertToRepetitionLocation(locationCollection, startIndex, cntr, repetitionLength, k1, k2);
		}
		// right repetition
		//find the same char of the left first char
		else {
			//check if it is repetition
			int repetitionLength = cntr - leftLength + 1; // cntr - Length(left) + 1
			zIndex = repetitionLength;
			int k1 = zIndex < 0 || zIndex >= z_Right_k1_Length ? 0 : z_Right_k1[zIndex]; // next char of cntr conver to z array index of right
			zIndex = cntr - leftLength;
			int k2 = zIndex < 0 || zIndex >= z_Right_k2_Length ? 0 : z_Right_k2[zIndex]; // last char of left substring conver to z array index of "thgir tfel"

			if (k1 + k2 >= repetitionLength)
				RightCovertToRepetitionLocation(locationCollection, startIndex, cntr, repetitionLength, k1, k2);
		}
	}

	delete[] z_Left_k1;
	delete[] z_Left_k2;
	delete[] z_Right_k1;
	delete[] z_Right_k2;
}

void MainLorentz::LeftCovertToRepetitionLocation(RepetitionLocationCollection* const locationCollection, const int startIndex, const int cntr, const int length, const int k1, const int k2) {
	int totLength = length << 1; //2*l
	//if k1 is overlap, go to looping to get all repetition strings
	int repetitionCount = k1 < length ? k1 : (length - 1); // k1 should less than length, do not overlap the cntr
	for (int k1_i = length - k2
		; k1_i <= repetitionCount; k1_i++) {
		RepetitionLocation* location = new RepetitionLocation();
		location->length = totLength;
		location->startPosition = startIndex + cntr - k1_i;
		location->endPosition = location->startPosition + totLength - 1;
		locationCollection->InsertLocation(location);
	}
}

void MainLorentz::RightCovertToRepetitionLocation(RepetitionLocationCollection* const locationCollection, const int startIndex, const int cntr, const int length, const int k1, const int k2) {
	int totLength = length << 1; //2*l
	//if k1 is overlap, go to looping to get all repetition strings
	int repetitionCount = k1 < length ? k1 : (length - 1); // k1 should less than length, do not overlap the cntr
	for (int k1_i = (length - k2 > 1 ? length - k2 : 1) // avoid to repeat with left when l1 is 0
		; k1_i <= repetitionCount; k1_i++) {
		RepetitionLocation* location = new RepetitionLocation();
		location->length = totLength;
		location->endPosition = startIndex + cntr + k1_i;
		location->startPosition = location->endPosition - totLength + 1;
		locationCollection->InsertLocation(location);
	}
}
