#include <vector>
#include <string>

void read_mp1(movable_part1 *mp1);
static std::vector<std::string> readAllLines(std::ifstream* stream);
static std::vector<uint8_t> HexToBytes(std::string str, int subchars);