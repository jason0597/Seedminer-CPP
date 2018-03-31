#include <iostream>
#include <vector>
#include <fstream>

#include "common.h"

#include "data_nodes.h"

using namespace std;

static vector<uint8_t> readAllBytes(ifstream* stream) {
    stream->seekg(0, std::ios::end);
    int filesize = stream->tellg();
    stream->seekg(0, ios::beg);

    vector<uint8_t> buffer(filesize);
    stream->read((char*)&buffer[0], filesize);

    return buffer;
}

static vector<vector<int32_t>> parseNodes(vector<uint8_t> nodes) {
    int no_of_nodes = nodes.size() / 8;

    vector<int32_t> LFCSes(no_of_nodes);
    vector<int32_t> msed3errors(no_of_nodes);
    
    for (int i = 0; i < nodes.size(); i += 8) {
        LFCSes[i / 8] = nodes[i] | (nodes[i+1] << 8) | (nodes[i+2] << 16) | (nodes[i+3] << 24);  
    }

    for (int i = 4; i < nodes.size(); i+= 8) {
        msed3errors[(i - 4) / 8] = nodes[i] | (nodes[i+1] << 8) | (nodes[i+2] << 16) | (nodes[i+3] << 24);
    }

    vector<vector<int32_t>> parsed_nodes;
    
    parsed_nodes.push_back(LFCSes);
    parsed_nodes.push_back(msed3errors);
    
    return parsed_nodes;
} 

vector<vector<int32_t>> readNodes(bool isNew3DS) {
    ifstream FileIn(isNew3DS ? "lfcs_new.dat" : "lfcs.dat", ios::binary);
    vector<uint8_t> nodes_raw = readAllBytes(&FileIn);
    FileIn.close();

    return parseNodes(nodes_raw); 
}
