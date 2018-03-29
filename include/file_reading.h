#include <vector>
#include <string>

void readMP1(movable_part1 *mp1);
static std::vector<std::string> readAllLines(std::ifstream* stream);
static std::vector<uint8_t> HexToBytes(std::string str, int subchars);
static std::string fixID0(std::string ID0);