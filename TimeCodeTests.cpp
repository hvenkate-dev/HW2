#include <cassert>
#include <iostream>

#include "TimeCode.h"

using namespace std;


// ============================================================
// GROUP 1: Constructors, conversions, and getter functions
// ============================================================

void TestComponentsToSeconds()
{
    cout << "Testing ComponentsToSeconds" << endl;

    // Checks a normal conversion to total seconds.
    long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
    assert(t == 11862);

    long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
    assert(t2 == 0);

    long long unsigned int t3 = TimeCode::ComponentsToSeconds(1, 1, 1);
    assert(t3 == 3661);

    cout << "PASSED!" << endl << endl;
}

void TestDefaultConstructor()
{
    cout << "Testing Default Constructor" << endl;

    TimeCode tc;

    // cout << "Testing ToString()" << endl;
    // cout << "tc: " << tc.ToString() << endl;

    assert(tc.ToString() == "0:0:0");
    assert(tc.GetHours() == 0);
    assert(tc.GetMinutes() == 0);
    assert(tc.GetSeconds() == 0);
    assert(tc.GetTimeCodeAsSeconds() == 0);

    cout << "PASSED!" << endl << endl;
}

void TestComponentConstructor()
{
    cout << "Testing Component Constructor" << endl;

    TimeCode tc1(0, 0, 0);
    assert(tc1.ToString() == "0:0:0");

    // Checks that extra minutes and seconds roll over into higher units.
    TimeCode tc2(3, 71, 3801);
    assert(tc2.ToString() == "5:14:21");

    TimeCode tc3(1, 1, 1);
    assert(tc3.ToString() == "1:1:1");

    // Checks that very large seconds are converted and rolled over correctly.
    TimeCode tcLarge(2, 71, 234719572143);
    assert(tcLarge.GetHours() == 65199884);
    assert(tcLarge.GetMinutes() == 20);
    assert(tcLarge.GetSeconds() == 3);

    // Checks that 61 seconds rolls over into 1 minute and 1 second.
    TimeCode tc4(0, 0, 61);
    assert(tc4.ToString() == "0:1:1");

    // Checks that 61 minutes rolls over into 1 hour and 1 minute.
    TimeCode tc5(0, 61, 0);
    assert(tc5.ToString() == "1:1:0");

    cout << "PASSED!" << endl << endl;
}

// Checks that the copied TimeCode has the same value as the original.
void TestCopyConstructor()
{
    cout << "Testing Copy Constructor" << endl;

    TimeCode original(5, 2, 18);
    TimeCode copy(original);

    assert(copy.ToString() == "5:2:18");
    assert(copy.GetTimeCodeAsSeconds() == original.GetTimeCodeAsSeconds());

    cout << "PASSED!" << endl << endl;
}

void TestGetComponents()
{
    cout << "Testing GetComponents" << endl;

    unsigned int h;
    unsigned int m;
    unsigned int s;

    // Regular values
    TimeCode tc = TimeCode(5, 2, 18);
    tc.GetComponents(h, m, s);

    assert(h == 5 && m == 2 && s == 18);

    // Checks that GetComponents returns normalized hours, minutes, and seconds.
    TimeCode tc2 = TimeCode(3, 71, 3801);
    tc2.GetComponents(h, m, s);

    assert(h == 5 && m == 14 && s == 21);

    cout << "PASSED!" << endl << endl;
}

void TestGetHours()
{
    cout << "Testing GetHours" << endl;

    TimeCode tc(7, 25, 42);

    assert(tc.GetHours() == 7);

    cout << "PASSED!" << endl << endl;
}

void TestGetMinutes()
{
    cout << "Testing GetMinutes" << endl;

    TimeCode tc(7, 25, 42);

    assert(tc.GetMinutes() == 25);

    cout << "PASSED!" << endl << endl;
}

void TestGetSeconds()
{
    cout << "Testing GetSeconds" << endl;

    TimeCode tc(7, 25, 42);

    assert(tc.GetSeconds() == 42);

    cout << "PASSED!" << endl << endl;
}

void TestGetTimeCodeAsSeconds()
{
    cout << "Testing GetTimeCodeAsSeconds" << endl;

    TimeCode tc(1, 1, 1);

    assert(tc.GetTimeCodeAsSeconds() == 3661);

    cout << "PASSED!" << endl << endl;
}

void TestToString()
{
    cout << "Testing ToString" << endl;

    TimeCode tc(12, 34, 56);

    assert(tc.ToString() == "12:34:56");

    cout << "PASSED!" << endl << endl;
}


// ============================================================
// GROUP 2: Setter and reset functions
// ============================================================

void TestSetHours()
{
    cout << "Testing SetHours" << endl;

    TimeCode tc(5, 20, 30);

    tc.SetHours(8);

    assert(tc.ToString() == "8:20:30");

    cout << "PASSED!" << endl << endl;
}

void TestSetMinutes()
{
    cout << "Testing SetMinutes" << endl;

    TimeCode tc = TimeCode(8, 5, 9);
    tc.SetMinutes(15);

    assert(tc.ToString() == "8:15:9");

    try
    {
        tc.SetMinutes(80);
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Expected exception.
    }

    assert(tc.ToString() == "8:15:9");

    tc.SetMinutes(0);
    assert(tc.ToString() == "8:0:9");

    tc.SetMinutes(59);
    assert(tc.ToString() == "8:59:9");

    cout << "PASSED!" << endl << endl;
}

void TestSetSeconds()
{
    cout << "Testing SetSeconds" << endl;

    TimeCode tc(8, 15, 30);

    tc.SetSeconds(45);
    assert(tc.ToString() == "8:15:45");

    tc.SetSeconds(0);
    assert(tc.ToString() == "8:15:0");

    tc.SetSeconds(59);
    assert(tc.ToString() == "8:15:59");

    try
    {
        tc.SetSeconds(80);
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Expected exception.
    }

    assert(tc.ToString() == "8:15:59");

    cout << "PASSED!" << endl << endl;
}

void TestReset()
{
    cout << "Testing reset" << endl;

    TimeCode tc(10, 20, 30);

    tc.reset();

    assert(tc.ToString() == "0:0:0");
    assert(tc.GetTimeCodeAsSeconds() == 0);

    cout << "PASSED!" << endl << endl;
}


// ============================================================
// GROUP 3: Arithmetic and comparison operators
// ============================================================

void TestAdd()
{
    cout << "Testing Add" << endl;

    TimeCode tc1(1, 15, 22);
    TimeCode tc2(2, 9, 5);

    TimeCode tc3 = tc1 + tc2;

    assert(tc3.ToString() == "3:24:27");

    // Checks that adding seconds across a minute boundary rolls over correctly.
    TimeCode tc4(1, 15, 55);
    TimeCode tc5(0, 1, 25);

    TimeCode tc6 = tc4 + tc5;

    assert(tc6.ToString() == "1:17:20");

    cout << "PASSED!" << endl << endl;
}

void TestSubtract()
{
    cout << "Testing Subtract" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(0, 50, 0);
    TimeCode tc3 = tc1 - tc2;

    assert(tc3.ToString() == "0:10:0");

    TimeCode tc4 = TimeCode(1, 15, 45);

    try
    {
        TimeCode tc5 = tc1 - tc4;
        cout << "tc5: " << tc5.ToString() << endl;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Checks that subtraction cannot produce a negative TimeCode.
    }

    // Subtract equal times
    TimeCode tc6 = tc1 - tc1;
    assert(tc6.ToString() == "0:0:0");

    // Checks that subtracting across a minute boundary borrows correctly.
    TimeCode tc7(1, 0, 0);
    TimeCode tc8(0, 0, 1);
    TimeCode tc9 = tc7 - tc8;

    assert(tc9.ToString() == "0:59:59");

    cout << "PASSED!" << endl << endl;
}

void TestMultiply()
{
    cout << "Testing Multiply" << endl;

    TimeCode tc(1, 0, 0);

    TimeCode doubled = tc * 2.0;
    assert(doubled.ToString() == "2:0:0");

    // Checks that fractional multiplication correctly reduces the time.
    TimeCode half = tc * 0.5;
    assert(half.ToString() == "0:30:0");

    TimeCode zero = tc * 0.0;
    assert(zero.ToString() == "0:0:0");

    try
    {
        TimeCode negative = tc * -1.0;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Checks that a negative multiplier is rejected.
    }

    cout << "PASSED!" << endl << endl;
}

void TestDivide()
{
    cout << "Testing Divide" << endl;

    TimeCode tc(1, 0, 0);

    TimeCode half = tc / 2.0;
    assert(half.ToString() == "0:30:0");

    // Checks that dividing by a fraction increases the total time.
    TimeCode doubled = tc / 0.5;
    assert(doubled.ToString() == "2:0:0");

    try
    {
        TimeCode zero = tc / 0.0;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Checks that division by zero is rejected.
    }

    try
    {
        TimeCode negative = tc / -1.0;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Checks that a negative divisor is rejected.
    }

    cout << "PASSED!" << endl << endl;
}

void TestComparisons()
{
    cout << "Testing Comparisons" << endl;

    TimeCode earlier(1, 0, 0);
    TimeCode later(2, 0, 0);
    TimeCode same(1, 0, 0);

    assert(earlier == same);
    assert(earlier != later);

    assert(earlier < later);
    assert(earlier <= later);

    assert(later > earlier);
    assert(later >= earlier);

    // Checks that <= and >= both work when the values are equal.
    assert(earlier <= same);
    assert(earlier >= same);

    cout << "PASSED!" << endl << endl;
}


// ============================================================
// MAIN: Runs all tests by assignment group
// ============================================================

int main()
{
    // Group 1: Constructors, conversions, and getter functions
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestCopyConstructor();
    TestGetComponents();
    TestGetHours();
    TestGetMinutes();
    TestGetSeconds();
    TestGetTimeCodeAsSeconds();
    TestToString();

    // Group 2: Setter and reset functions
    TestSetHours();
    TestSetMinutes();
    TestSetSeconds();
    TestReset();

    // Group 3: Arithmetic and comparison operators
    TestAdd();
    TestSubtract();
    TestMultiply();
    TestDivide();
    TestComparisons();

    cout << "PASSED ALL TESTS!!!" << endl;

    return 0;
}