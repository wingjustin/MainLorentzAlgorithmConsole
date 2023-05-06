// MainLorentzAlgorithmConsole.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include<conio.h>
#include "ZFunction.h"
#include "MainLorentz.h"

#define NORMAL_STYLE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#define HIGHLINE_STYLE (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE & FOREGROUND_GREEN & FOREGROUND_RED)

using namespace std;
using namespace MainLorentzAlgorithm;

/*
example 1 : "abcdeabcdeabcdeabcde"
example 2 : "acababaee"
example 3 : "ccababee"
example 4 : "exceed see say shehhehehe"
example 5 : "aaaaaaaaaaa"
*/

int main()
{
    string text = "";

    char operKey = 'E';
    do {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        //title
        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE ^ BACKGROUND_RED);
        cout << "Main-Lorentz Algorithm Repetition Searching";
        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
        cout << endl << "------------------------------------------------------------------------------------------" << endl;
        string inputWord = "";
        char temp;

        cout << "Please input ";
        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE);
        cout << "Text";
        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
        cout << " : " << "\n";
        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE);

        //insert words
        inputWord = "";
        temp;
        while (cin.get(temp) && temp != '\n') {
            inputWord += temp;
        }
        text = inputWord;

        int textLength = static_cast<int>(text.length());

        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);

        cout << "------------------------------------------------------------------------------------------" << endl;

        RepetitionLocationCollection locations = MainLorentz::FindRepetitions(text);

        //show the locations
        RepetitionLocation* location = locations.GetFirstLocation();
        cout << "Count : " << to_string(locations.GetLength());
        cout << endl;
        if (locations.GetLength() > 0) {
            SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
            while (location) {
                //show repetition
                cout << "Length : ";
                SetConsoleTextAttribute(hConsole, NORMAL_STYLE ^ FOREGROUND_RED);
                cout << to_string(location->length);
                SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
                cout << "\n ";
                bool skipBegin;
                int begin = (skipBegin = location->startPosition > 5) ? location->startPosition - 5 : 0;
                bool skipEnd;
                int end = (skipEnd = location->endPosition < (textLength - 6)) ? location->endPosition + 5 : textLength - 1;
                cout << (skipBegin ? "..." : "   ");
                for (int i = begin;
                    i <= end;
                    i++) {
                    if (i == location->startPosition)
                        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE | FOREGROUND_RED);
                    if (i == location->endPosition + 1)
                        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
                    cout << text[i];
                }
                SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
                cout << (skipEnd ? "..." : "   ");
                cout << "  ::::  ";
                SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE | FOREGROUND_BLUE);
                cout << text.substr(location->startPosition, location->length >>1);
                SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE | FOREGROUND_RED);
                cout << text.substr(location->startPosition + (location->length >> 1), location->length >> 1);
                SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE | FOREGROUND_BLUE);
                if (location->startPosition == location->endPosition)
                    cout << " (" + to_string(location->startPosition + 1) << ")";
                else
                    cout << " (" + to_string(location->startPosition + 1) << " - " << to_string(location->endPosition + 1) << ")";
                SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
                cout << ";" << endl;
                cout << "------------------------------------------------------------------------------ \n";
                //
                location = location->next;
            }
        }

        cout << endl << endl;

        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
        //check continue
        cout << "Press Any Key to start from Text; \"E\" for Exit : ";
        operKey = _getch();
        cout << "\n=========================================================================" << endl;
    } while (operKey != 'e' && operKey != 'E');
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
