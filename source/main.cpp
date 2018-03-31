#include <iostream>
#include <string>
#include <cstdlib>

#include "common.h"

#include "data_nodes.h"
#include "file_reading.h"
#include "launcher.h"

using namespace std;

int32_t getMsed3Error(uint32_t num, vector<vector<int32_t>> nodes) {
    vector<int32_t> LFCSes = nodes[0];
    vector<int32_t> msed3s = nodes[1];

    int distance = abs((int)(LFCSes[0] - num));
    int idx = 0;
    for (int i = 0; i < LFCSes.size(); i++) {
        int cdistance = abs((int)(LFCSes[i] - num));
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
        vector<vector<int32_t>> nodes = readNodes(mp1.isNew3DS);

        uint32_t lfcs_num = mp1.LFCS[0] | (mp1.LFCS[1] << 8) | (mp1.LFCS[2] << 16) | (mp1.LFCS[3] << 24);
        cout << "lfcs_num: " << hex << lfcs_num << endl;

        int32_t msed3error = getMsed3Error(lfcs_num >> 12, nodes);
        cout << "msed3error: " << dec << msed3error << endl;

        mp1.msed3estimate = ((lfcs_num / 5) + (-1) * msed3error);
        cout << "msed3estimate: " << hex << mp1.msed3estimate << endl;

    } catch (invalid_argument e) {
        cout << "An exception occurred!" << endl;
        cout << e.what() << endl;
        system("pause");
        return -1;
    }

    return 0;
}