#include <vector>
#include <string>

namespace file_reading {
    //===== PRIVATE =====
    static std::string fixID0(std::string ID0);
    //===== PUBLIC =====
    std::vector<uint8_t> readAllBytes(std::string filename);
    void readMP1(movable_part1 *mp1);
}
