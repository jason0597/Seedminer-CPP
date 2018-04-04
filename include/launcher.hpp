#include <vector>

namespace launcher {
    //===== PRIVATE =====
    static std::vector<uint8_t> getKeyY(movable_part1 mp1);
    static std::string vectorToString(std::vector<uint8_t> vec);
    //===== PUBLIC =====
    void doMining(movable_part1 mp1);
}
