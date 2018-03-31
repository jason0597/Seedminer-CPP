#include <iostream>
#include <string>

#include "common.h"

#include "data_nodes.h"
#include "file_reading.h"

using namespace std;

int main () {
    movable_part1 mp1;

    try {
        readMP1(&mp1);
        vector<vector<int32_t>> nodes = readNodes(mp1.isNew3DS);
        

    } catch (invalid_argument e) {
        cout << "An exception occurred!" << endl;
        cout << e.what() << endl;
        system("pause");
        return -1;
    }

    system("pause");
    return 0;
}