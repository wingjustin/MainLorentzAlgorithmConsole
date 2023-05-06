#include "RepetitionLocationCollection.h"

using namespace MainLorentzAlgorithm;

RepetitionLocationCollection::RepetitionLocationCollection() {
	length = 0;
	firstLocation = NULL;
	lastLocation = NULL;
}

RepetitionLocationCollection::~RepetitionLocationCollection() {
	RepetitionLocation* current = firstLocation;
	if (current) {
		RepetitionLocation* temp = current;
		do {
			temp = current;
			current = temp->next;
			temp->prev = NULL;
			temp->next = NULL;
			delete temp;
		} while (current);
		temp = NULL;
	}
	firstLocation = NULL;
	lastLocation = NULL;
}

bool RepetitionLocationCollection::IsEmpty() {
	return length == 0;
}

int RepetitionLocationCollection::GetLength() {
	return length;
}

RepetitionLocation* RepetitionLocationCollection::GetFirstLocation() {
	return firstLocation;
}

RepetitionLocation* RepetitionLocationCollection::GetLastLocation() {
	return lastLocation;
}

RepetitionLocation* RepetitionLocationCollection::InsertLocation(RepetitionLocation* const newLocation) {
	if (lastLocation) {
		lastLocation->next = newLocation;
		newLocation->prev = lastLocation;
		lastLocation = newLocation;
		lastLocation->next = NULL;
		length++;

		return lastLocation;
	}
	else {
		lastLocation = firstLocation = newLocation;
		firstLocation->prev = NULL;
		lastLocation->next = NULL;
		length++;

		return lastLocation;
	}
}
