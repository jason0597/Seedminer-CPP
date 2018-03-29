#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "common.h"

#include "file_reading.h"

using namespace std;

void readMP1(movable_part1 *mp1) {
    ifstream FileIn("movable_part1.txt");

    if (!FileIn.is_open()) 
        throw invalid_argument("Failed to open movable_part1.txt!");
    
    vector<string> mp1_txt = readAllLines(&FileIn);
    FileIn.close();

    if (mp1_txt.size() != 7) 
        throw invalid_argument("movable_part1.txt is not 7 lines!");
    if (mp1_txt.at(1).size() < 16) 
        throw invalid_argument("The LFCS is not 16 characters!");
    if (mp1_txt.at(5).size() < 32) 
        throw invalid_argument("The ID0 is not 32 characters!");

    vector<uint8_t> LFCS = HexToBytes(mp1_txt.at(1), 16); 

    for (int i = 0; i < 8; i++) 
        mp1->LFCS[i] = LFCS[i];

    cout << "Before --> " << mp1_txt.at(5) << endl;
    mp1->ID0 = fixID0(mp1_txt.at(5));
    cout << "After  --> " << mp1->ID0 << endl;
    cout << "Should --> " << "464d34a6314fe64bcef402c6c04698dd" << endl;
}

static vector<string> readAllLines(ifstream* stream) {
    vector<string> mp1_txt;

    string line;
    while (getline(*stream, line)) {
        mp1_txt.push_back(line);
    }

    return mp1_txt;
}

static string fixID0(string ID0) {
    //a6344d464be64f31c602f4cedd9846c0
    //a6344d46 4be64f31 c602f4ce dd9846c0
    //464d34a6 314fe64b cef402c6 c04698dd
    //464d34a6314fe64bcef402c6c04698dd
    string parts[4] = {ID0.substr(0, 8), ID0.substr(8, 8), ID0.substr(16, 8), ID0.substr(24, 8)};

    string return_value = "";
    for (int i = 0; i < 4; i++) {
        string tmp = "";
        for (int j = 7; j >= 0; j -= 2) {
            tmp.push_back(parts[i].at(j));
            tmp.push_back(parts[i].at(j-1));
        }
        return_value += tmp;
    }

    return return_value;
}

// The second parameter of this function tells it how many
// of the characters to parse as an actual hex string.
// For example, you may give it a string "2B2F    ", where
// the last 4 characters don't mean anything. You want to tell this
// function how many of the characters in the string you have given it
// are actually the ones you want to be parsed
static vector<uint8_t> HexToBytes(string hexstr, int subchars) {
    string str = hexstr.substr(0, subchars);
    vector<uint8_t> bytes;

    for (int i = 0; i < str.length(); i += 2) {
        string byteString = str.substr(i, 2);
        bytes.push_back((uint8_t)stoi(byteString, nullptr, 16));
    }

    return bytes;
}
