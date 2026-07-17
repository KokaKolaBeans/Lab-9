#include "invalidRange.h"
#include "invalidType.h"
#include "invalidUnit.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
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

// 4. if all valid: format and append to readings vector

// Create a stringstream to format the double to 2 decimal places

    stringstream stream;
    stream << fixed << setprecision(2) << value;
    string formattedValue = stream.str(); // e.g. "23.50"

    // Construct the clean reading string
    string currentReading = string(1, type) + " " + formattedValue + " " + unit;

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
        if (!(cin >> type >> value >> unit))
        
        { 
            cout << "INPUT ERROR: Please input a valid sensor reading";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        };

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

    sort(readings.begin(), readings.end());


    cout << "============================" << endl
    << setw(24) << "Sensor Data Readings" << endl
    << "============================" 
    << endl 
    << endl;

    for (int i=0; i < 10; i++) 
    {
        cout << readings[i] << endl;
    

    }

    cout << endl << endl;


}



/* ==============================================================================================================
                                                   Exercise 1:
                                                   
Input "X 23.5 C" --> invalidType exception. The error message is "TYPE ERROR: invalid sensor type: X"

Input "T 9000 C" --> invalidRange exception. The error message is "RANGE ERROR: Sensor reading of 9000.000000 
falls outside of acceptable range for temperature readings (-50.0 to 150.0)"

Input "T 23.5 Z" --> invalidUnit exception. The error message is "Invalid unit type: Z"
============================================================================================================== */