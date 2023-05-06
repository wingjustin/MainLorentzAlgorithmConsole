#pragma once

#include <string>
#include "ZFunction.h"
#include "RepetitionLocationCollection.h"

using namespace std;
using namespace ZAlgorithm;

namespace MainLorentzAlgorithm {
	class MainLorentz {
	private:
		static void LeftCovertToRepetitionLocation(RepetitionLocationCollection* locationCollection, int startIndex, int cntr, int length, int k1, int k2);
		static void RightCovertToRepetitionLocation(RepetitionLocationCollection* locationCollection, int startIndex, int cntr, int length, int k1, int k2);
		static void FindRepetitions(string& text, int startIndex, int endIndex, RepetitionLocationCollection* locationCollection);
	public:
		static RepetitionLocationCollection FindRepetitions(string text); // return count of repetitions
	};
}
