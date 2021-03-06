#include <iostream>
#include <string>

#include "common.hpp"

#include "data_nodes.hpp"
#include "file_handling.hpp"
#include "launcher.hpp"

int32_t getMsed3Error(uint32_t num, std::vector<std::vector<int32_t>> nodes) {
    std::vector<int32_t> LFCSes = nodes[0];
    std::vector<int32_t> msed3s = nodes[1];

    int distance = std::abs((int)(LFCSes[0] - num));
    int idx = 0;
    for (int i = 0; i < LFCSes.size(); i++) {
        int cdistance = std::abs((int)(LFCSes[i] - num));
        if (cdistance < distance) {
            idx = i;
            distance = cdistance;
        }
    }
    return msed3s[idx];
}

bool stringIsHex(std::string str) {
    return (str.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos);
}

int main (int argc, char **argv) {
    if (argc == 1) {
        try {
            movable_part1 mp1;
            file_handling::readMP1(&mp1);
            std::vector<std::vector<int32_t>> nodes = data_nodes::readNodes(mp1.isNew3DS);

            uint32_t lfcs_num = mp1.LFCS[0] | (mp1.LFCS[1] << 8) | (mp1.LFCS[2] << 16) | (mp1.LFCS[3] << 24);
            std::cout << "lfcs_num: " << std::hex << lfcs_num << std::endl;
            if (lfcs_num == 0) {
                throw std::invalid_argument("The LFCS has been left blank!");
            }

            int32_t msed3error = getMsed3Error(lfcs_num >> 12, nodes);
            std::cout << "msed3error: " << std::dec << msed3error << std::endl;

            mp1.msed3estimate = ((lfcs_num / 5) + (-1) * msed3error);
            std::cout << "msed3estimate: " << std::hex << mp1.msed3estimate << std::endl;

            launcher::doMining(mp1);
        } catch (std::exception e) {
            std::cout << "An exception occurred!" << std::endl;
            std::cout << e.what() << std::endl;
            system("pause");
            return -1;
        }
    } 
    else if (argc > 1 && (strcmp(argv[1], "id0") == 0)) {
        try {
            if (argc < 3) 
                throw std::invalid_argument("id0 argument specified, but no id0 was provided!");
            if (strlen(argv[2]) != 32) 
                throw std::invalid_argument("The provided id0 is not 32 characters!");
            if (!stringIsHex(std::string(argv[2]))) 
                throw std::invalid_argument("The provided id0 is not a valid hexadecimal string!");

            std::vector<uint8_t> id0(32);
            memcpy(&id0[0], argv[2], 32);
            file_handling::writeBytes("movable_part1.sed", 16, id0);

            std::cout << "Inserted the id0 in the movable_part1.sed" << std::endl;
        } catch (std::exception e) {
            std::cout << "An exception occurred!" << std::endl;
            std::cout << e.what() << std::endl;
            system("pause");
            return -1;
        }
    } 
    else {
        std::cout << "Incorrect usage!" << std::endl;
        std::cout << "Correct usage:" << std::endl << " - Seedminer" << std::endl 
        << " - Seedminer id0 abcdef012345EXAMPLEdef0123456789" << std::endl;
        system("pause");
    }


    system("pause");
    return 0;
}