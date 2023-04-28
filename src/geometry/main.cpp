#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <libgeometry/geometry.h>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int main()
{
    string line;
    int circleCounter;
    double circleArray[100][100];
    ifstream inFile;
    inFile.open("geometry-input");
    if (inFile.is_open()) {
        circleCounter = 0;
        while (getline(inFile, line)) {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            if (line.rfind("circle", 0) == 0) {
                if (circle(line, circleCounter, circleArray) == 1) {
                    circleCounter++;
                } else {
                    return 0;
                }
            } else {
                cout << line << endl
                     << "^" << endl
                     << "expected circle, triangle or polygon at position 0";
                return 0;
            }
        }
        circleCalculation(circleCounter, circleArray);
        print(circleCounter, circleArray);
    } else {
        cout << "Failed to open geometry-input";
        return 0;
    }
    return 0;
}
