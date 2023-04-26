#include <libgeometry/geometry.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int errorMessage(int position, string message, string line, int circleCounter)
{
	cout << circleCounter + 1 << ". " << line << endl;
	int x = 0;
	for (x = x; x < position; x++)
	{
		cout << ' ';
	}
	cout << "   " << '^' << endl << message << endl;
	return 0;
}

int print(int circleCounter, double circleArray[][100])
{
	for (int i = 0; i < circleCounter; i++)
	{
		cout << i + 1 << ". " << "circle(" << circleArray[i][0] << ' ' << circleArray[i][1] << ", " << circleArray[i][2] << ')' << endl
			<< '	' << "perimeter = " << circleArray[i][3] << endl
			<< '	' << "area = " << circleArray[i][4] << endl;
		if (circleArray[i][5] > 0)
		{
			cout << '	' << "intersects: " << endl;
			for (int j = 0; j < circleArray[i][5]; j++)
			{
				cout << "		" << circleArray[i][6 + j] << ". circle" << endl;
			}
		}
	}
	return 0;
}

int circleCalculation(int circleCounter, double circleArray[][100])
{
	for (int g = 0; g < circleCounter; g++)
	{
		circleArray[g][3] = 2 * M_PI * circleArray[g][2];
		circleArray[g][4] = M_PI * pow(circleArray[g][2], 2);
		circleArray[g][5] = 0;
	}
	for (int g = 0; g <= circleCounter; g++)
	{
		for (int h = g + 1; h <= circleCounter; h++)
		{
			if (pow((circleArray[g][2] - circleArray[h][2]), 2) <= pow((circleArray[g][0] - circleArray[h][0]), 2) + pow((circleArray[g][1] - circleArray[h][1]), 2)
				&& pow((circleArray[g][0] - circleArray[h][0]), 2) + pow((circleArray[g][1] - circleArray[h][1]), 2) <= pow((circleArray[g][2] + circleArray[h][2]), 2))
			{
				int temp = circleArray[g][5];
				circleArray[g][6 + temp] = h + 1;
				circleArray[g][5] += 1;
				temp = circleArray[h][5];
				circleArray[h][6 + temp] = g + 1;
				circleArray[h][5] += 1;
			}
		}
	}
	return 0;
}

int checkNumber(size_t& p, int& j, string line, int circleCounter, double circleArray[][100])
{

	// If the 1st char is not '+', '-', or digit
	if (line[p] != '+' && line[p] != '-'
		&& !(line[p] >= '0' && line[p] <= '9'))
	{
		errorMessage(p, "expected Number", line, circleCounter);
		return 0;
	}

	int start = p;

	p += 1;

	bool flagDot = false;

	for (p = p; p < line.length(); p++)
	{

		if (line[p] == ' ')
		{
			int end = p;
			string number = line.substr(start, end - start);
			double num_double = stod(number);
			circleArray[circleCounter][j] = num_double;
			p++;
			return 1;
		}

		if (line[p] == ',' && j == 1)
		{
			int end = p;
			string number = line.substr(start, end - start);
			double num_double = stod(number);
			circleArray[circleCounter][j] = num_double;
			return 1;
		}

		if (line[p] == ')' && j == 2)
		{
			if (line.length() > p + 1)
			{
				errorMessage(p + 1, "expected end of line", line, circleCounter);
				return 0;
			}
			int end = p;
			string number = line.substr(start, end - start);
			double num_double = stod(number);
			circleArray[circleCounter][j] = num_double;
			return 1;
		}

		// If any of the char after the first does not belong to
		// {digit, .}
		if (line[p] != '.'
			&& !(line[p] >= '0' && line[p] <= '9'))
		{
			errorMessage(p, "expected Number", line, circleCounter);
			return 0;
		}
		// checks if the char '.' has already occurred before
		if (line[p] == '.')
		{
			if (flagDot == true)
			{
				errorMessage(p, "expected Number", line, circleCounter);
				return 0;
			}
			// If '.' is the last character.
			if (p + 1 > line.length())
			{
				errorMessage(p, "expected Number", line, circleCounter);
				return 0;
			}
			// if '.' is not followed by a digit.
			if (!(line[p + 1] >= '0' && line[p + 1] <= '9'))
			{
				errorMessage(p + 1, "expected Number", line, circleCounter);
				return 0;
			}
			// if there is no digit before '.'.
			if (!(line[p - 1] >= '0' && line[p - 1] <= '9'))
			{
				errorMessage(p, "expected Number", line, circleCounter);
				return 0;
			}
			// set flagDot = 1 when '.' is encountered.
			flagDot = true;
		}
	}
	errorMessage(p, "expected input", line, circleCounter);
	return 0;
}

int parsing(size_t& p, string line, int circleCounter, double circleArray[][100])
{
	for (int j = 0; j < 3; j++)
	{
		if (line.length() == p)
		{
			errorMessage(p, "expected input", line, circleCounter);
			return 0;
		}
		while (line[p] == ' ')
		{
			if (line.length() > p + 1)
			{
				p++;
			}
			else
			{
				errorMessage(p + 1, "expected input", line, circleCounter);
				return 0;
			}
		}
		if (j == 2)
		{
			if (line[p] == ',')
			{
				p++;
				while (line[p] == ' ')
				{
					if (line.length() > p + 1)
					{
						p++;
					}
					else
					{
						errorMessage(p + 1, "expected input", line, circleCounter);
						return 0;
					}
				}
			}
			else
			{
				cout << p;
				errorMessage(p - 1, "expected ','", line, circleCounter);
				return 0;
			}

		}
		if (checkNumber(p, j, line, circleCounter, circleArray) == 0)
		{
			return 0;
		}
	}
	while (line[p] == ' ')
	{
		if (line.length() > p + 1)
		{
			p++;
		}
		else
		{
			errorMessage(p + 1, "expected input", line, circleCounter);
			return 0;
		}
	}
	if (line[p] != ')')
	{
		errorMessage(p + 1, "expected ')'", line, circleCounter);
		return 0;
	}
	else
	{
		if (line.length() == p + 1)
		{
			return 1;
		}
		else
		{
			errorMessage(p + 1, "expected end of line", line, circleCounter);
			return 0;
		}
	}

}

int circle(string line, int circleCounter, double circleArray[][100])
{
	if (line[6] != '(')
	{
		errorMessage(6, "expected '('", line, circleCounter);
		return 0;
	}
	if (line.length() == 7)
	{
		errorMessage(7, "expected input", line, circleCounter);
		return 0;
	}
	size_t p = 7;
	return(parsing(p, line, circleCounter, circleArray));
}
