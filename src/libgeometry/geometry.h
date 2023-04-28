#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int errorMessage(int position, string message, string line, int circleCounter);

int print(int circleCounter, double circleArray[][100]);

int circleCalculation(int circleCounter, double circleArray[][100]);

int checkNumber(
        size_t& p,
        int& j,
        string line,
        int circleCounter,
        double circleArray[][100]);

int parsing(
        size_t& p, string line, int circleCounter, double circleArray[][100]);

int circle(string line, int circleCounter, double circleArray[][100]);

#endif
