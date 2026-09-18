#include <iostream>
#include <stdexcept>
#include "TimeCode.h"

using namespace std;


TimeCode::TimeCode(unsigned int hr,
                   unsigned int min,
                   long long unsigned int sec)
{
    // Using one conversion keeps the stored value as total seconds.
    t = ComponentsToSeconds(hr, min, sec);
}


TimeCode::TimeCode(const TimeCode& tc)
{
    t = tc.t;
}


long long unsigned int TimeCode::ComponentsToSeconds(
    unsigned int hr,
    unsigned int min,
    long long unsigned int sec)
{
    // Keeping the conversion here avoids repeating the same calculation elsewhere.
    return hr * 3600 + min * 60 + sec;
}


void TimeCode::GetComponents(
    unsigned int& hr,
    unsigned int& min,
    unsigned int& sec) const
{
    // References let this function return all three components through its parameters.
    hr = t / 3600;

    unsigned long long int remainder = t % 3600;

    min = remainder / 60;

    sec = remainder % 60;
}


unsigned int TimeCode::GetHours() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return hr;
}


unsigned int TimeCode::GetMinutes() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return min;
}


unsigned int TimeCode::GetSeconds() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return sec;
}


string TimeCode::ToString() const
{
    return to_string(GetHours()) + ":" +
           to_string(GetMinutes()) + ":" +
           to_string(GetSeconds());
}


void TimeCode::SetHours(unsigned int hr)
{
    unsigned int oldHr;
    unsigned int oldMin;
    unsigned int oldSec;

    GetComponents(oldHr, oldMin, oldSec);

    t = ComponentsToSeconds(hr, oldMin, oldSec);
}


void TimeCode::SetMinutes(unsigned int min)
{
    // Minutes are limited here so setters cannot create an invalid component.
    if (min >= 60)
    {
        throw invalid_argument("Minutes must be between 0 and 59");
    }

    unsigned int oldHr;
    unsigned int oldMin;
    unsigned int oldSec;

    GetComponents(oldHr, oldMin, oldSec);

    t = ComponentsToSeconds(oldHr, min, oldSec);
}


void TimeCode::SetSeconds(unsigned int sec)
{
    // Seconds are limited here so setters cannot create an invalid component.
    if (sec >= 60)
    {
        throw invalid_argument("Seconds must be between 0 and 59");
    }

    unsigned int oldHr;
    unsigned int oldMin;
    unsigned int oldSec;

    GetComponents(oldHr, oldMin, oldSec);

    t = ComponentsToSeconds(oldHr, oldMin, sec);
}


void TimeCode::reset()
{
    t = 0;
}




TimeCode TimeCode::operator+(const TimeCode& tc) const
{
    TimeCode result;

    // Adding total seconds lets the result roll over naturally.
    result.t = t + tc.t;

    return result;
}


TimeCode TimeCode::operator-(const TimeCode& tc) const
{
    // Preventing this case keeps TimeCode from representing negative time.
    if (t < tc.t)
    {
        throw invalid_argument("TimeCode cannot be negative");
    }

    TimeCode result;

    result.t = t - tc.t;

    return result;
}


TimeCode TimeCode::operator*(double multiplier) const
{
    // Negative time is not allowed, so a negative multiplier is rejected.
    if (multiplier < 0)
    {
        throw invalid_argument("Multiplier cannot be negative");
    }

    TimeCode result;

    result.t = t * multiplier;

    return result;
}


TimeCode TimeCode::operator/(double divisor) const
{
    // Division by zero or a negative divisor cannot produce a valid TimeCode.
    if (divisor <= 0)
    {
        throw invalid_argument("Divisor must be greater than zero");
    }

    TimeCode result;

    result.t = t / divisor;

    return result;
}


bool TimeCode::operator==(const TimeCode& tc) const
{
    return t == tc.t;
}


bool TimeCode::operator!=(const TimeCode& tc) const
{
    return t != tc.t;
}


bool TimeCode::operator<(const TimeCode& tc) const
{
    return t < tc.t;
}


bool TimeCode::operator>(const TimeCode& tc) const
{
    return t > tc.t;
}


bool TimeCode::operator<=(const TimeCode& tc) const
{
    return t <= tc.t;
}


bool TimeCode::operator>=(const TimeCode& tc) const
{
    return t >= tc.t;
}