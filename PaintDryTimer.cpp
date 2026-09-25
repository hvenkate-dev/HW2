#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "TimeCode.h"

using namespace std;

struct DryingSnapShot
{
    string name;
    time_t startTime;
    TimeCode *timeToDry;
};


// Returns how many seconds are left for a batch.
long long int get_time_remaining(DryingSnapShot dss)
{
    time_t currentTime = time(0);
    long long int elapsed = currentTime - dss.startTime;

    // Subtract elapsed time so the remaining time decreases in real time.
    long long int remaining =
        dss.timeToDry->GetTimeCodeAsSeconds() - elapsed;

    return remaining;
}


// Creates the text shown when a batch is displayed.
string drying_snap_shot_to_string(DryingSnapShot dss)
{
    long long int remaining = get_time_remaining(dss);

    if (remaining <= 0)
        return dss.name + " DONE!";

    TimeCode remainingTime(0, 0, remaining);

    return dss.name +
           " (takes " + dss.timeToDry->ToString() +
           " to dry) time remaining: " +
           remainingTime.ToString();
}


// Calculates the surface area of a sphere.
double get_sphere_sa(double rad)
{
    // Surface area determines the number of seconds needed to dry.
    return 4.0 * M_PI * rad * rad;
}


// Converts surface area into the required drying TimeCode.
TimeCode *compute_time_code(double surfaceArea)
{
    // The assignment defines surface area in cm^2 as drying time in seconds.
    return new TimeCode(0, 0, surfaceArea);
}


void tests()
{
    // get_time_remaining
    DryingSnapShot dss;
    dss.startTime = time(0);

    TimeCode tc(0, 0, 7);
    dss.timeToDry = &tc;

    long long int ans = get_time_remaining(dss);

    assert(ans >= 6 && ans <= 7);


    // get_sphere_sa
    double sa = get_sphere_sa(2.0);

    assert(50.2654 < sa && sa < 50.2655);


    // compute_time_code
    TimeCode *tc2 = compute_time_code(1.0);

    assert(tc2->GetTimeCodeAsSeconds() == 1);

    delete tc2;


    // Test zero radius.
    assert(get_sphere_sa(0.0) == 0.0);


    // Test another radius.
    TimeCode *tc3 = compute_time_code(50.0);

    assert(tc3->GetTimeCodeAsSeconds() == 50);

    delete tc3;


    cout << "ALL TESTS PASSED!" << endl;
}


int main()
{
    tests();

    vector<DryingSnapShot> batches;

    char choice;

    while (true)
    {
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> choice;

        if (choice == 'a' || choice == 'A')
        {
            double radius;

            cout << " radius: ";
            cin >> radius;

            TimeCode *dryTime =
                compute_time_code(get_sphere_sa(radius));

            DryingSnapShot batch;

            batch.name = "Batch-" + to_string(rand());
            batch.startTime = time(0);
            batch.timeToDry = dryTime;

            batches.push_back(batch);

            cout << " " << drying_snap_shot_to_string(batch) << endl;
        }
        else if (choice == 'v' || choice == 'V')
        {
            for (size_t i = 0; i < batches.size(); )
            {
                if (get_time_remaining(batches[i]) <= 0)
                {
                    cout << " " << batches[i].name << " DONE!" << endl;

                    // Delete the heap object before removing the batch.
                    delete batches[i].timeToDry;

                    batches.erase(batches.begin() + i);
                }
                else
                {
                    cout << " " << drying_snap_shot_to_string(batches[i])
                         << endl;

                    ++i;
                }
            }

            cout << " " << batches.size()
                 << " batches being tracked." << endl;
        }
        else if (choice == 'q' || choice == 'Q')
        {
            break;
        }
    }


    // Delete any batches that are still active when the program quits.
    for (DryingSnapShot& batch : batches)
        delete batch.timeToDry;

    return 0;
}