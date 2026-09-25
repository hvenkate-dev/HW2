#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TimeCode.h"

using namespace std;

// I read the notes!

// Extracts the UTC time from one CSV line.
TimeCode parse_line(const string& line)
{
    // We only care about the time, so finding " UTC" avoids
    // having to parse every other CSV field.
    size_t utc = line.find(" UTC");

    // Find the space immediately before the UTC time.
    // Example: "Fri Aug 07, 2020 05:12 UTC"
    // rfind searches backward from "UTC" and finds the space before "05:12".
    size_t timeStart = line.rfind(' ', utc - 1);

    // Extract only the time between the space and " UTC".
    // Example: from "Fri Aug 07, 2020 05:12 UTC",
    // this extracts "05:12".
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

   
    for (const TimeCode& tc : times)
        total = total + tc;

    
    TimeCode average = total / static_cast<double>(times.size());

    cout << times.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}
