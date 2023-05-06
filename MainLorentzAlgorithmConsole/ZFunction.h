#pragma once

#include <string>

using namespace std;

namespace ZAlgorithm {
	class ZFunction {
	public:
		static int GetZArray(string keyword, int*& zArray); //return length of z array
		static int GetReverseZArray(string keyword, int*& zArray); //return length of z array
		static int KeywordSearch(string keyword, string text, int*& locationArray); //return count of matches
	};
}