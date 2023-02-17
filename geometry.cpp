#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

ofstream outFile;

string line;

int errorMessage(int pointer, string str)
{
    ofstream outFile;
    outFile.open("geometry-output");
    outFile << line << endl;
    int x = 0;
    for (x = x; x < pointer; x++) {
        outFile << ' ';
    }
    outFile << '^' << endl << str;
    return 0;
}

int validNumber(string str, int pointer)
{
    outFile.open("geometry-output");

    size_t k = 0;
    size_t l = str.length() - 1;

    string expectedNumber = "expected number";

    // if string is of length 1 and the only
    // character is not a digit
    if (k == l && !(str[k] >= '0' && str[k] <= '9')) {
        errorMessage(pointer + k, expectedNumber);
        return 0;
    }
    // If the 1st char is not '+', '-', '.' or digit
    if (str[k] != '.' && str[k] != '+' && str[k] != '-'
        && !(str[k] >= '0' && str[k] <= '9')) {
        errorMessage(pointer + k, expectedNumber);
        return 0;
    }

    // To check if a '.' is found in given
    // string. We use this flag to make sure that
    // either of them appear only once.
    bool flagDot = false;

    for (k = k; k <= l; k++) {
        // If any of the char does not belong to
        // {digit, .}
        if (str[k] != '.' && !(str[k] >= '0' && str[k] <= '9')) {
            errorMessage(pointer + k, expectedNumber);
            return 0;
        }

        // checks if the char '.' has already
        // occurred before '.' If yes, return 0.
        if (str[k] == '.') {
            if (flagDot == true) {
                errorMessage(pointer + k, expectedNumber);
                return 0;
            }

            // If '.' is the last character.
            if (k + 1 > str.length()) {
                errorMessage(pointer + k, expectedNumber);
                return 0;
            }

            // if '.' is not followed by a digit.
            if (!(str[k + 1] >= '0' && str[k + 1] <= '9')) {
                errorMessage(pointer + k, expectedNumber);
                return 0;
            }
        }

        else if (str[k] == '.') {
            // set flagDot = 1 when . is encountered.
            flagDot = true;

            // if there is no digit before '.'.
            if (!(str[k - 1] >= '0' && str[k - 1] <= '9')) {
                errorMessage(pointer + k, expectedNumber);
                return 0;
            }

            // If '.' is the last Character
            if (k + 1 > str.length()) {
                errorMessage(pointer + k, expectedNumber);
                return 0;
            }

            // if . is not followed either by a digit
            if (!(str[k + 1] >= '0' && str[k] <= '9')) {
                errorMessage(pointer + k, expectedNumber);
                return 0;
            }
        }
    }

    /* If the string skips all above cases, then
    it is numeric*/
    return 1;
}

const int maxLength = 20;
int p;
int i;
size_t g;

int nToArray(char seperator, double array[maxLength])
{
    ofstream outFile;
    bool flag = false;
    for (g = g; g < line.length(); g++) {
        if (line[g] == seperator) {
            flag = true;
            break;
        }
    }
    if (flag == true) {
        string number = line.substr(p, g - p);
        if (validNumber(number, p)) {
            // convert string to double
            double num_double = stod(number);
            array[i] = num_double;
            i++;
            g++;
            p = g;
            return 1;
        } else {
            return 0;
        }
    } else {
        outFile.open("geometry-output");
        outFile << line << endl << "expected seperator between numeric values";
        return 0;
    }
}

void circle()
{
    if (line.rfind('(', 6) == 6) {
        double circleArray[maxLength];
        g = 0;
        p = 7;
        i = 0;
        if (nToArray(' ', circleArray)) {
            if (nToArray(',', circleArray)) {
                g++;
                p++;
                if (nToArray(')', circleArray)) {
                    if (g == line.length()) {
                        double circlePerimeter = 2 * M_PI * circleArray[2];
                        double circleArea = M_PI * pow(circleArray[2], 2);
                        ofstream outFile;
                        outFile.open("geometry-output");
                        outFile << "1. " << line << endl
                                << "    perimeter = " << circlePerimeter << endl
                                << "    area = " << circleArea;
                    } else {
                        errorMessage(g, "expected end of line");
                    }
                }
            }
        }
    } else {
        outFile.open("geometry-output");
        outFile << line << endl
                << "      ^" << endl
                << "expected '(', at position 6";
    }
}

void triangle()
{
}

void polygon()
{
}

int main()
{
    ifstream inFile;
    inFile.open("geometry-input");
    ofstream outFile;
    outFile.open("geometry-output");
    line = "";
    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            if (line != "") {
                transform(line.begin(), line.end(), line.begin(), ::tolower);
                if (line.rfind("circle", 0) == 0
                    || line.rfind("triangle", 0) == 0
                    || line.rfind("polygon", 0) == 0) {
                    if (line.rfind("circle", 0) == 0) {
                        circle();
                    }
                    if (line.rfind("triangle", 0) == 0) {
                        triangle();
                    }
                    if (line.rfind("polygon", 0) == 0) {
                        polygon();
                    }
                    return 0;
                } else {
                    outFile << line << endl
                            << "^" << endl
                            << "expected circle, triangle or polygon at "
                               "position 0";
                    return 0;
                }
            }
        }
        outFile << "No input detected";
        return 0;
    } else if (!inFile.is_open()) {
        outFile << "Failed to open geometry-input";
        return 0;
    } else if (!outFile.is_open()) {
        outFile << "Failed to open geometry-output";
        return 0;
    }
}
