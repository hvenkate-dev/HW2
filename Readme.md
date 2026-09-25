# HW2 Part 2

This project contains three C++ programs for time-code operations, NASA launch-time analysis, and paint-drying calculations.

## TimeCode

The TimeCode program represents and manipulates time using hours, minutes, and seconds.

Run the tests:

```bash
make tct
./tct
```

## NASA Launch Analysis

The NASA Launch Analysis program reads launch times from Space_Corrected.csv and calculates the average launch time.

Run:

```bash
make nasa
./nasa
```

Make sure Space_Corrected.csv is in the same directory.

## Paint Dry Timer

The Paint Dry Timer calculates drying times based on the surface area of a sphere and tracks paint batches.

Run:

```bash
make pdt
./pdt
```

## Build All Programs

To compile all three programs:

```bash
make
```

This creates:

- `tct` for the TimeCode tests
- `nasa` for NASA Launch Analysis
- `pdt` for Paint Dry Timer

## Clean Build Files

To remove the compiled programs:

```bash
make clean

## THANK YOU