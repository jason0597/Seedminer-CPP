#include <string>

struct movable_part1 {
    uint8_t LFCS[8];
    bool isNew3DS;
    uint32_t msed3estimate;
    std::string ID0; //This is the PARSED ID0!!!
};