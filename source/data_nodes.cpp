#include <iostream>
#include <vector>
#include <fstream>

#include "common.hpp"

#include "data_nodes.hpp"

namespace data_nodes {
    //===== PRIVATE =====
    std::vector<uint8_t> readAllBytes(std::ifstream* stream) {
        stream->seekg(0, std::ios::end);
        int filesize = stream->tellg();
        stream->seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer(filesize);
        stream->read((char*)&buffer[0], filesize);

        return buffer;
    }

    std::vector<std::vector<int32_t>> parseNodes(std::vector<uint8_t> nodes) {
        int no_of_nodes = nodes.size() / 8;

        std::vector<int32_t> LFCSes(no_of_nodes);
        std::vector<int32_t> msed3errors(no_of_nodes);
        
        for (int i = 0; i < nodes.size(); i += 8) {
            LFCSes[i / 8] = nodes[i] | (nodes[i+1] << 8) | (nodes[i+2] << 16) | (nodes[i+3] << 24);  
        }

        for (int i = 4; i < nodes.size(); i+= 8) {
            msed3errors[(i - 4) / 8] = nodes[i] | (nodes[i+1] << 8) | (nodes[i+2] << 16) | (nodes[i+3] << 24);
        }

        std::vector<std::vector<int32_t>> parsed_nodes;
        
        parsed_nodes.push_back(LFCSes);
        parsed_nodes.push_back(msed3errors);
        
        return parsed_nodes;
    } 

    //===== PUBLIC =====
    std::vector<std::vector<int32_t>> readNodes(bool isNew3DS) {
        std::ifstream FileIn(isNew3DS ? "lfcs_new.dat" : "lfcs.dat", std::ios::binary);
        std::vector<uint8_t> nodes_raw = readAllBytes(&FileIn);
        FileIn.close();

        return parseNodes(nodes_raw); 
    }
}
