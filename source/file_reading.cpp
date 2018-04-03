#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "common.h"

#include "file_reading.h"

void readMP1(movable_part1 *mp1) {
    std::ifstream FileIn("movable_part1.txt");

    if (!FileIn.is_open()) 
        throw std::invalid_argument("Failed to open movable_part1.txt!");
    
    std::vector<std::string> mp1_txt = readAllLines(&FileIn);
    FileIn.close();

    if (mp1_txt.size() != 7) 
        throw std::invalid_argument("movable_part1.txt is not 7 lines!");
    if (mp1_txt.at(1).size() < 16) 
        throw std::invalid_argument("The LFCS is not 16 characters!");
    if (mp1_txt.at(5).size() < 32) 
        throw std::invalid_argument("The ID0 is not 32 characters!");

    std::vector<uint8_t> LFCS = HexToBytes(mp1_txt.at(1), 16); 

    for (int i = 0; i < 8; i++) 
        mp1->LFCS[i] = LFCS[i];

    mp1->isNew3DS = (LFCS[4] & 0b00000010 == 0b00000010);
    mp1->id0 = fixID0(mp1_txt.at(5));
}

static std::vector<std::string> readAllLines(std::ifstream* stream) {
    std::vector<std::string> mp1_txt;

    std::string line;
    while (getline(*stream, line)) {
        mp1_txt.push_back(line);
    }

    return mp1_txt;
}

static std::string fixID0(std::string ID0) {
    std::string parts[4] = {ID0.substr(0, 8), ID0.substr(8, 8), ID0.substr(16, 8), ID0.substr(24, 8)};

    std::string return_value = "";
    for (int i = 0; i < 4; i++) {
        std::string tmp = "";
        for (int j = 7; j >= 0; j -= 2) {
            tmp.push_back(parts[i].at(j-1));
            tmp.push_back(parts[i].at(j));
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
static std::vector<uint8_t> HexToBytes(std::string hexstr, int subchars) {
    std::string str = hexstr.substr(0, subchars);
    std::vector<uint8_t> bytes;

    for (int i = 0; i < str.length(); i += 2) {
        std::string byteString = str.substr(i, 2);
        bytes.push_back((uint8_t)std::stoi(byteString, nullptr, 16));
    }

    return bytes;
}
