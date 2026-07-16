#include "invalidRange.h"
#include "invalidType.h"
#include "invalidUnit.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void validateReading(char type, double value, string unit, vector<string> &readings)
{

    // 1. validate type — throw invalidType if not T, H, or P

    if (type != 'T' && type != 'H' && type != 'P')
    {

        throw invalidType("Invalid sensor type: " + string(1, type));
    }

    // 2. validate unit for this type — throw invalidUnit if mismatch

    if (type == 'T')
    {
        if (unit != "C" && unit != "F" && unit != "K")
        {
            throw invalidUnit("Invalid unit type: " + unit);
        }
    }

    else if (type == 'H')

    {
        if (unit != "PCT")

            throw invalidUnit("Invalid unit type: " + unit);
    }
    else if (type == 'P')
    {
        if (unit != "HPA" && unit != "PSI" && unit != "ATM")
        {
            throw invalidUnit("Invalid unit type: " + unit);
        }
    }

    // 3. validate range — throw invalidRange if value out of bounds
    // ... (check value against min/max for type)

    if (type == 'T')

    {
        if (value < -50.0 || value > 150.0)
        {
            throw invalidRange("Sensor reading of " + to_string(value) +
                               " falls outside of acceptable range for temperature readings (-50.0 to 150.0)");
        }
    }

    else if (type == 'H')
    {
        if (value < 0.0 || value > 100.0)
        {
            throw invalidRange("Sensor value of " + to_string(value) +
                               " falls outside of the acceptable range for humidity measurements (0.0 to 100.0)");
        }
    }
    else if (type == 'P')
    {
        if (value < 800.0 || value > 1100.0)
        {
            throw invalidRange("Sensor value of " + to_string(value) +
                               " falls outside of the acceptable range for pressure measurements (800.0 to 1100.0)");
        }
    }

    // 4. if all valid: format and append to readings vector

    string currentReading = string(1, type) + " " + to_string(value) + " " + unit;

    readings.push_back(currentReading);

    // readings.push_back(/* formatted reading string */);
}

int main()

{
    vector<string> readings;

    while (readings.size() < 10)
    {
        char type;
        double value;
        string unit;

        cout << "Reading " << (readings.size() + 1) << " of 10\n";
        cout << "Enter type value unit (e.g. T 23.5 C): ";
        cin >> type >> value >> unit;

        try
        {
            validateReading(type, value, unit, readings);
            cout << "Reading accepted.\n";
        }
        catch (invalidType e)
        {
            cout << "TYPE ERROR: " << e.what() << "\n";
        }
        catch (invalidUnit e)
        {
            cout << "UNIT ERROR: " << e.what() << "\n";
        }
        catch (invalidRange e)
        {
            cout << "RANGE ERROR: " << e.what() << "\n";
        }
    };
}