#include <iostream>
#include <string>

#include "common.h"

#include "file_reading.h"

using namespace std;


int main () {
    movable_part1 mp1;

    try {
        readMP1(&mp1);
    } catch (invalid_argument e) {
        cout << "An exception occurred!" << endl;
        cout << e.what() << endl;
        system("pause");
        return -1;
    }

    system("pause");
    return 0;
}