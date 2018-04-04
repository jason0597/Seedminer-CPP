#include <iostream>
#include <vector>

#include "common.hpp"

#include "launcher.hpp"

namespace launcher {
    //===== PRIVATE =====
    std::vector<uint8_t> getKeyY(movable_part1 mp1) {
        std::vector<uint8_t> key_y(16);

        for (int i = 0; i < 8; i++) 
            key_y[i] = mp1.LFCS[i];

        key_y[12] = mp1.msed3estimate & 0x000000FF;
        key_y[13] = (mp1.msed3estimate & 0x0000FF00) >> 8;
        key_y[14] = (mp1.msed3estimate & 0x00FF0000) >> 16;
        key_y[15] = (mp1.msed3estimate & 0xFF000000) >> 24;

        return key_y;
    }

    std::string vectorToString(std::vector<uint8_t> vec) {
        std::string return_str;

        char buf[] = "00";
        for (int i = 0; i < vec.size(); i++) {
            sprintf(buf, "%02X", vec[i]);
            std::string buf_str = std::string(buf);
            return_str += buf_str;
        }
        
        return return_str;
    }

    //===== PUBLIC =====
    void doMining(movable_part1 mp1) {
        std::vector<uint8_t> key_y = getKeyY(mp1);

        std::string key_y_str = vectorToString(key_y);

        std::string command = "bfcl msky " + key_y_str + " " + mp1.id0 + " 00000000";

        std::cout << "Executing command \"" << command << "\"" << std::endl;
        std::cout << "BEGINNING BRUTEFORCE\n==========================" << std::endl;

        system(command.c_str());
    }
}