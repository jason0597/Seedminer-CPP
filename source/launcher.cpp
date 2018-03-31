#include <vector>

#include "common.h"

using namespace std;

static vector<uint8_t> getKeyY(movable_part1 mp1) {
    vector<uint8_t> key_y(16);

    for (int i = 0; i < 8; i++) 
        key_y[i] = mp1.LFCS[i];

    vector<uint8_t> msed3estimate(4);

    msed3estimate[0] = mp1.msed3estimate & 0x1;
    msed3estimate[1] = mp1.msed3estimate & 0x1;
    msed3estimate[2] = mp1.msed3estimate & 0x1;
    msed3estimate[3] = mp1.msed3estimate & 0x1;

    return msed3estimate;
}

void doMining(movable_part1 mp1) {
    vector<uint8_t> key_y = getKeyY(mp1);
    
    

}