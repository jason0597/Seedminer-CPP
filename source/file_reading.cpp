#include <fstream>
#include <vector>
#include <string>

#include "common.hpp"

#include "file_reading.hpp"

namespace file_reading {
    //===== PRIVATE =====
    std::string fixID0(std::string ID0) {
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

    //===== PUBLIC =====
    std::vector<uint8_t> readAllBytes(std::string filename) {
        std::ifstream stream(filename, std::ios::binary | std::ios::ate);

        if (!stream.is_open()) {
            throw std::invalid_argument("Failed to open " + filename);
        }

        std::streampos filesize = stream.tellg();
        stream.seekg(0);

        std::vector<uint8_t> buffer(filesize);
        stream.read((char*)&buffer[0], filesize);

        stream.close();
        return buffer;
    }

    void readMP1(movable_part1 *mp1) {
        std::vector<uint8_t> mp1_sed = readAllBytes("movable_part1.sed");

        if (mp1_sed.size() < 48) {
            throw std::invalid_argument("movable_part1.sed is not 48 bytes!");
        }

        memcpy(mp1->LFCS, &mp1_sed[0], 8);
        mp1->isNew3DS = (mp1->LFCS[4] & 0b00000010 == 0b00000010);

        char str_char[33];
        memcpy(str_char, &mp1_sed[16], 33);
        std::string str(str_char, 32);

        mp1->id0 = fixID0(str);
    }
}
