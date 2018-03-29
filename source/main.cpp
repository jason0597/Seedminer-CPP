#include <iostream>
#include <string>

#include "common.h"

#include "file_reading.h"

using namespace std;

static void waitFor(void) {
    std::cout << "Press ENTER to continue...";
    std::string tmp_garbage; std::getline(std::cin, tmp_garbage);
}

int main () {
    movable_part1 mp1;

    try {
        read_mp1(&mp1);
    } catch (invalid_argument e) {
        cout << "An exception occurred!" << endl;
        cout << e.what() << endl;
        system("pause");
        return -1;
    }

    cout << "Printing what we got from the file..." << endl;

    cout << "LFCS is: " << endl;
    for (int i = 0; i < 8; i++) {
        cout << hex << (int)mp1.LFCS[i];
    }
    cout << endl << "ID0 is: " << mp1.ID0 << endl;


    system("pause");
    return 0;
}