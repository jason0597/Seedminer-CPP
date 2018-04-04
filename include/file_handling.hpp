#include <vector>
#include <string>

namespace file_handling {
    //===== PRIVATE =====
    static std::string fixID0(std::string ID0);
    //===== PUBLIC =====
    std::vector<uint8_t> readAllBytes(std::string filename);
    void writeBytes(std::string filename, int offset, std::vector<uint8_t> data);
    void readMP1(movable_part1 *mp1);
}
