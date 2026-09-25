#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TimeCode.h"

using namespace std;

// I read the assignment notes and followed their requirements.

// Extracts the UTC time from one CSV line.
TimeCode parse_line(const string& line)
{
    // We only care about the time, so finding " UTC" avoids
    // having to parse every other CSV field.
    size_t utc = line.find(" UTC");

    size_t timeStart = line.rfind(' ', utc - 1);
    string time = line.substr(timeStart + 1, utc - timeStart - 1);

    unsigned int hr;
    unsigned int min;
    char colon;

    stringstream ss(time);
    ss >> hr >> colon >> min;

    return TimeCode(hr, min, 0);
}

int main()
{
    ifstream file("Space_Corrected.csv");

    if (!file)
    {
        cout << "Could not open Space_Corrected.csv" << endl;
        return 1;
    }

    vector<TimeCode> times;
    string line;

    // The first line contains column names, not launch data.
    getline(file, line);

    while (getline(file, line))
    {
        // Launches without an exact time do not contain " UTC",
        // so they must not be included in the average.
        if (line.find(" UTC") == string::npos)
            continue;

        times.push_back(parse_line(line));
    }

    TimeCode total;

    // Use TimeCode's + operator as required by the assignment.
    for (const TimeCode& tc : times)
        total = total + tc;

    // Use TimeCode's / operator to calculate the average.
    TimeCode average = total / static_cast<double>(times.size());

    cout << times.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}