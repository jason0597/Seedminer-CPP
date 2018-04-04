#include <iostream>
#include <string>

#include "common.h"

#include "data_nodes.h"
#include "file_reading.h"
#include "launcher.h"

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

int main () {
    movable_part1 mp1;

    try {
        readMP1(&mp1);
        std::vector<std::vector<int32_t>> nodes = readNodes(mp1.isNew3DS);

        uint32_t lfcs_num = mp1.LFCS[0] | (mp1.LFCS[1] << 8) | (mp1.LFCS[2] << 16) | (mp1.LFCS[3] << 24);
        std::cout << "lfcs_num: " << std::hex << lfcs_num << std::endl;

        int32_t msed3error = getMsed3Error(lfcs_num >> 12, nodes);
        std::cout << "msed3error: " << std::dec << msed3error << std::endl;

        mp1.msed3estimate = ((lfcs_num / 5) + (-1) * msed3error);
        std::cout << "msed3estimate: " << std::hex << mp1.msed3estimate << std::endl;

        doMining(mp1);

    } catch (std::exception e) {
        std::cout << "An exception occurred!" << std::endl;
        std::cout << e.what() << std::endl;
        system("pause");
        return -1;
    }

    return 0;
}