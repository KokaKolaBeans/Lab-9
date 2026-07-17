#include "invalidRange.h"
#include "invalidType.h"
#include "invalidUnit.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
const int MAX_READINGS = 10;
const double T_MIN = -50.0;
const double T_MAX = 150.0;
const double H_MIN = 0.0;
const double H_MAX = 100.0;
const double P_MIN = 800.0;
const double P_MAX = 1100.0;
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

    // to_string(value)
    {
        if (value < T_MIN || value > T_MAX)
        {
            stringstream ss; // Creates a stringstream object that converts 'value' to a string data member with one decimal place.
            ss << fixed << setprecision(1) << value; 

            stringstream tMinString;
            tMinString << fixed << setprecision(1) << T_MIN;

            stringstream tMaxString;
            tMaxString << fixed << setprecision(1) << T_MAX;

            throw invalidRange("Sensor reading of " + ss.str() + // ss.str() retrieves the string sitting in the stringstream object. 
                               " falls outside of acceptable range for temperature readings (" + tMinString.str() + " to " + tMaxString.str() + ")");
        }
    }

    else if (type == 'H')
    {
        if (value < H_MIN || value > H_MAX)
        {
            stringstream ss; 
            ss << fixed << setprecision(1) << value; 
            stringstream hMinString;
            hMinString << fixed << setprecision(1) << H_MIN;
            stringstream hMaxString;
            hMaxString << fixed << setprecision(1) << H_MAX;
            throw invalidRange("Sensor value of " + ss.str() +
                               " falls outside of the acceptable range for humidity measurements (" + hMinString.str() + " to " + hMaxString.str() + ")");
        }
    }
    else if (type == 'P')
    {
        if (value < P_MIN || value > P_MAX)

        {
            stringstream ss; 
            ss << fixed << setprecision(1) << value; 
            stringstream pMinString;
            pMinString << fixed << setprecision(1) << P_MIN;
            stringstream pMaxString;
            pMaxString << fixed << setprecision(1) << P_MAX;
            throw invalidRange("Sensor value of " + ss.str() +
                               " falls outside of the acceptable range for pressure measurements (" + pMinString.str() + " to " + pMaxString.str() + ")");
        }
    }

// 4. if all valid: format and append to readings vector

// Create a stringstream to format the double to 2 decimal places

    stringstream stream;
    stream << fixed << setprecision(1) << value;
    string formattedValue = stream.str(); // e.g. "23.5"

    // Construct the clean reading string
    string currentReading = string(1, type) + " " + formattedValue + " " + unit;

    readings.push_back(currentReading);
        // readings.push_back(/* formatted reading string */);
}

int main()

{
    cout << setprecision(1) << fixed;

    vector<string> readings;

        int typeError = 0;
        int unitError = 0;
        int rangeError = 0;
        int inputError = 0;
        int numReadings = 0;

    while (readings.size() < MAX_READINGS)
    {
        char type;
        double value;
        string unit;
        numReadings ++;
        
        cout << "Reading " << (readings.size() + 1) << " of " << MAX_READINGS << "\n";
        cout << "Enter type value unit (e.g. T 23.5 C): ";
        if (!(cin >> type >> value >> unit))
        
        { 
            inputError += 1;
            cout << "INPUT ERROR //// Please input a valid sensor reading" << endl;   // catches input that does not match the general expected format
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
            typeError += 1;
            cout << "TYPE ERROR //// " << e.what() << "\n";
            
        }
        catch (invalidUnit e)
        {
            unitError += 1;
            cout << "UNIT ERROR //// " << e.what() << "\n";
        }
        catch (invalidRange e)
        {
            rangeError += 1;
            cout << "RANGE ERROR //// " << e.what() << "\n";
        }
    };

    sort(readings.begin(), readings.end());

    // Output to terminal

    cout << "============================" << endl
    << setw(24) << "Sensor Data Readings" << endl
    << "============================" 
    << endl 
    << endl;

    for (int i=0; i < MAX_READINGS; i++) 
    {
        cout << readings[i] << endl;
    

    }

    cout << endl << endl;
    // Output to file 

    ofstream outFile("sensor_log.txt");

    if(outFile.is_open())
    {
        outFile << "============================" << endl
        << setw(24) << "Sensor Data Readings" << endl
        << "============================" 
        << endl 
        << endl;

        for (int i=0; i < MAX_READINGS; i++) 
        {
            outFile << readings[i] << endl;
        
        }

        outFile << endl << endl;

        outFile << "============================" << endl
        << setw(16) << "Error Summary" << endl
        << "============================";

        outFile << endl << endl;

        outFile << "TYPE ERRORS: " << typeError << endl;
        outFile << "UNIT ERRORS: " << unitError << endl;
        outFile << "RANGE ERRORS: " << rangeError << endl;
        outFile << "INPUT ERRORS: " << inputError << endl;
        outFile << "TOTAL READINGS: " << numReadings << endl;
        outFile << "TOTAL ERRORS: " << (typeError + unitError + rangeError + inputError) << endl;
        outFile << "TOTAL VALID READINGS: " << readings.size() << endl;
        outFile << "READING ERROR PERCENTAGE: " << fixed << setprecision(2) << (static_cast<double>(typeError + unitError + rangeError + inputError) / numReadings) * 100 
        << "%" << endl;
        outFile << "VALID READING PERCENTAGE: " << fixed << setprecision(2) << (static_cast<double>(readings.size()) / numReadings) * 100
        << "%" << endl;
        outFile << "INVALID TYPE ERROR PERCENTAGE: " << fixed << setprecision(2) << (static_cast<double>(typeError) / numReadings) * 100
        << "%" << endl;
        outFile << "INVALID UNIT ERROR PERCENTAGE: " << fixed << setprecision(2) << (static_cast<double>(unitError) / numReadings) * 100
        << "%" << endl;
        outFile << "INVALID RANGE ERROR PERCENTAGE: " << fixed << setprecision(2) << (static_cast<double>(rangeError) / numReadings) * 100  
        << "%" << endl;
        outFile << "INVALID INPUT ERROR PERCENTAGE: " << fixed << setprecision(2) << (static_cast<double>(inputError) / numReadings) * 100
        << "%" << endl;


        outFile.close();
    }
    else

    {
        cout << "ERROR: Unable to open file for writing." << endl;
    }







}



/* ==============================================================================================================
                                                   Exercise 1
                                                   
Input "X 23.5 C" --> invalidType exception. The error message is "TYPE ERROR //// Invalid sensor type: X"

Input "T 2222222 C" --> invalidRange exception. The error message is "RANGE ERROR //// Sensor reading of 2222222.0 
falls outside of acceptable range for temperature readings (-50.0 to 150.0)""

Input "T 23.5 X" --> invalidUnit exception. The error message is "UNIT ERROR //// Invalid unit type: X"
============================================================================================================== */



/* ==============================================================================================================
                                                   Exercise 2
                                                   
Input "X 999.0 INVALID" triggers the invalidType exception. This is because 'type' is measurement type is the
first exception that is checked in the validateReading function. The error message is "TYPE ERROR //// Invalid 
sensor type: X." 

Given the way my code is written, if the check for range were placed before the check for type, the input 
would actually fall through the range-check, because the range against which to check the input is determined
by the sensor type; if the sensor type-input is neither T nor H nor P, no range-check code block is executed.
So, my code would throw the same invalidType exception as before.

However, if a range check were placed before a type check, conceptually speaking, the range of acceptable inputs
would likely have to span the entire range of possible inputs. So only extreme numbers that fall outside the range
of all three input types at once would trigger an exception. Those would probably result a less effective, less
safe program overall. In other words, checking for sensor type first is a better design choice.

To take a hypotheticla example, onsider a rocket with a central processing unit that receives input from a number 
of different sensors. The CPU may have a function that is called to process altitude and one that is called to 
process temperature. These numerical representations would be subject to a different set of acceptable input and 
output ranges and be processed using different algorithms. In this case as well, validating sensor type would 
be a prerequisite to performing any further calculations or range-checks.  
============================================================================================================== */



/* ==============================================================================================================
                                                   Exercise 3
                                                   
Removing catch (invalidUnit e)) means that when the invalidUnit exception is thrown, there is no catch block
handle it. We get a runtime error: 

libc++abi: terminating due to uncaught exception of type invalidUnit
zsh: abort      ./Lab9

This unaccounted-for exception means the program crashes and the user is given no useful insight into the issue. 

When an error is thrown inside a function, the runtime engine stops execution and exits the function immediately. 
It destroys the function and associated local variables ("removes the function stack frame")–this cleanup is necessary 
to ensure memory integrity and safety. The runtime engine then moves 'back up the stack' to the calling function to 
search for a catch block to handle the exception. In this case, when validateReading sees an invalid unit type, 
it throws an invalidUnit exception exception object. The engine then moves into the calling function (main()) and 
sees that 'validateReading' was called inside a 'try' block. This tells the engine to look for the next catch block 
that can handle the exception type (in this case "invalidUnit e," which takes as an argument the invalidUnit exception 
object).

If the runtime engine gets all the way back to the "bottom" of the call stack and still cannot find a catch block
to handle the exception, it will terminate the program using the inbuilt terminate() function and display
a runtime error message, as in the above case when "invalidUnit e" is removed.
============================================================================================================== */