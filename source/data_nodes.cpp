#include <iostream>
#include <vector>
#include <fstream>

#include "common.h"

#include "data_nodes.h"

using namespace std;

void parseNodes(bool isNew3DS) {
    ifstream FileIn(isNew3DS ? "lfcs_new.dat" : "lfcs.dat", ios::binary);
    vector<uint8_t> nodes_raw = readAllBytes(&FileIn);
    FileIn.close();

    cout << "the filesize is: " << nodes_raw.size() << endl;
}

static vector<uint8_t> readAllBytes(ifstream* stream) {
    stream->seekg(0, std::ios::end);
    int filesize = stream->tellg();
    stream->seekg(0, ios::beg);

    vector<uint8_t> buffer(filesize);
    stream->read((char*)&buffer[0], filesize);

    return buffer;
}
