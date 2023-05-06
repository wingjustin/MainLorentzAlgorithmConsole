#include "ZFunction.h"

using namespace ZAlgorithm;

int ZFunction::GetZArray(const string keyword, int*& z) {
	const int length = static_cast<int>(keyword.length());
	if (length < 1)
		return length;
	z = new int[length];
	//z[0] = length;
	z[0] = 0;

	for (int i = 1, j = 0, L = 0, R = 0; i < length; i++) {
		if (i > R) {
			//i is outside the z box, update z box
			j = 0;
			L = i;
			while (i + j < length && keyword[i + j] == keyword[j])
				j++;
			z[i] = j;
			R = L + j - 1;
		}
		else {
			if (z[i - L] <= R - i) { // if ((z[i - L] + 1) <= (R - i + 1))
				//when the z[i - L] (the length of matched prefix) is equal or less than the distance from i to R at current z box
				// , it can be copied as the current z value.
				// if z[i - L] is more than the length of current z box, it cannot be used.
				// example : "ccchhhccccee"
				// if the z-array of prefix "ccch" is "x,2,1,0"
				//, the z-array of current z box "ccccee" is "3,?,?,?,?,?" and index i is at second 'c', "ccc" is not equal to "cch" at the last character
				// the the length of z-values "2,1,0" of "cch" is 3 but the z-values "3,?,?" of z box "ccc" is only match 2 characters
				//, so the z-values "2" of "c" at first "cch" cannot be used
				// "aaaaabaaaaaaaaaaz" = {17, 4, 3, 2, 1, 0, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0} is never run this code, because (R - i) always less than (z[i - L])
				// but "aaaaabaaaaaaaaaab" = {17, 4, 3, 2, 1, 0, 5, 5, 5, 5, 5, 6, 4, 3, 2, 1, 0} will run this code, because (R - i) equal to (z[i - L]) at the last z box
				z[i] = z[i - L];
			}
			else {
				//i is inside the z box, but the value z[i - L] cannot be used
				//index j jump to outside z box, inside z box is already matched, the length is already known
				j = R - i + 1;
				L = i;
				while (i + j < length && keyword[i + j] == keyword[j])
					j++;
				z[i] = j;
				R = L + j - 1;
			}
		}
	}
	return length;
}

//reverse
int ZFunction::GetReverseZArray(const string reverseKeyword, int*& z) {
	const int length = static_cast<int>(reverseKeyword.length());
	if (length < 1)
		return length;
	z = new int[length];
	//z[length - 1] = length;
	z[length - 1] = 0;

	for (int i = length - 2, j = 0, L = length - 1, R = L; i > -1; i--) {
		if (i < L) {
			j = 0;
			R = i;
			while (i - j > -1 && reverseKeyword[i - j] == reverseKeyword[length - j - 1])
				j++;
			z[i] = j;
			L = R - j + 1;
		}
		else {
			if (z[length - 1 - (R - i)] <= i - L) { // if (z[length - 1 - (R - i)] + 1 <= i - L + 1)
				z[i] = z[length - 1 - (R - i)];
			}
			else {
				j = i - L + 1;
				R = i;
				while (i - j > -1 && reverseKeyword[i - j] == reverseKeyword[length - j - 1])
					j++;
				z[i] = j;
				L = R - j + 1;
			}
		}
	}
	return length;
}

//example 1 : "aab$baabaa" = { 10, 1, 0, 0, 0, 3, 1, 0, 2, 1 }
//example 2 : "he$sshehehe" = { 11, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0 }
int ZFunction::KeywordSearch(const string keyword, const string text, int*& locationArray) { //return length of array
	const int keywordLength = static_cast<int>(keyword.length());
	const int textLength = static_cast<int>(text.length());
	if (keywordLength < 1 || textLength < 1)
		return 0;
	// create new string with pattern "keyword$text"
	string newString;
	newString.append(keyword);
	newString.append(1, '$');
	newString.append(text);
	int* zArray;
	const int zArrayLength = GetZArray(newString, zArray);

	int locationLength = 0;
	locationArray = NULL;
	for (int c = keywordLength + 1; c < zArrayLength; c++) {
		if (zArray[c] == keywordLength) {
			const int* const oldArray = locationArray;
			locationArray = new int[locationLength + 1];
			//copy old values
			for (int i = 0; i < locationLength; i++)
				locationArray[i] = oldArray[i];
			locationArray[locationLength++] = c - keywordLength - 1;
			if (oldArray)
				delete[] oldArray;
		}
	}

	delete[] zArray;
	zArray = NULL;
	return locationLength;
}

////slower
//int ZFunction::GetZArray(const string keyword, int*& z) {
//	const int length = static_cast<int>(keyword.length());
//	if (length < 1)
//		return length;
//	z = new int[length];
//	z[0] = length;
//	
//	for (int i = 1, j = 0, L = 0, R = 0; i < length; i++) {
//		if (i > R) {
//			//i is outside the z box, update z box
//			j = 0;
//			L = R = i;
//			while (i + j < length && keyword[i + j] == keyword[j])
//				j++;
//			z[i] = j;
//			R = L + j - 1;
//		}
//		else {
//			if ((z[i - L] + 1) <= (R - i + 1)) {
//				//when the z[i - L] (the length of matched prefix) is equal or less than the distance from i to R at current z box
//				// , it can be copied as the current z value.
//				// if z[i - L] is more than the length of current z box, it cannot be used.
//				// example : "ccchhhccccee"
//				// if the z-array of prefix "ccch" is "x,2,1,0"
//				//, the z-array of current z box "ccccee" is "3,?,?,?,?,?" and index i is at second 'c', "ccc" is not equal to "cch" at the last character
//				// the the length of z-values "2,1,0" of "cch" is 3 but the z-values "3,?,?" of z box "ccc" is only match 2 characters
//				//, so the z-values "2" of "c" at first "cch" cannot be used
//				//"aaaaabaaaaaaaaaaz" = {17, 4, 3, 2, 1, 0, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0} is never run this code, because R - i always less than z[i - L]
//				// but "aaaaabaaaaaaaaaab" = {17, 4, 3, 2, 1, 0, 5, 5, 5, 5, 5, 6, 4, 3, 2, 1, 0} will run this code, because (R - i) equal to (z[i - L]) at the last z box
//				z[i] = z[i - L];
//			}
//			else {
//				//i is inside the z box, but the value z[i - L] cannot be used
//				j = 0;
//				L = R = i;
//				while (i + j < length && keyword[i + j] == keyword[j])
//					j++;
//				z[i] = j;
//				R = L + j - 1;
//			}
//		}
//	}
//	return length;
//}
