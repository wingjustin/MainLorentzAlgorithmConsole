#pragma once

#include <string>

using namespace std;

namespace MainLorentzAlgorithm {
	struct RepetitionLocation {
		int startPosition = INT_MIN;
		int endPosition = INT_MIN;
		int length = 0;

		RepetitionLocation* prev = NULL;
		RepetitionLocation* next = NULL;
	};
	class RepetitionLocationCollection {
		int length;
		RepetitionLocation* firstLocation;
		RepetitionLocation* lastLocation;
	public:
		RepetitionLocationCollection();
		~RepetitionLocationCollection();

		bool IsEmpty();
		int GetLength();

		RepetitionLocation* GetFirstLocation();
		RepetitionLocation* GetLastLocation();

		RepetitionLocation* InsertLocation(RepetitionLocation* newLocation);
	};
}
