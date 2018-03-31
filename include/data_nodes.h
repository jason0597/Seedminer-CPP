#include <vector>
#include <fstream>

static std::vector<std::vector<int32_t>> parseNodes(std::vector<uint8_t> nodes);
static std::vector<uint8_t> readAllBytes(std::ifstream* stream);
std::vector<std::vector<int32_t>> readNodes(bool isNew3DS);