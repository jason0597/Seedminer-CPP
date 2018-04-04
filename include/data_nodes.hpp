#include <vector>
#include <fstream>

namespace data_nodes {
    //===== PRIVATE =====
    static std::vector<std::vector<int32_t>> parseNodes(std::vector<uint8_t> nodes);
    //===== PUBLIC =====
    std::vector<std::vector<int32_t>> readNodes(bool isNew3DS);
}
