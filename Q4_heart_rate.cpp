/*
 * Name       : Muaz Ahmad
 * Reg No     : L1S26BSCS0074
 * Assignment : 02 - File Handling
 * Question   : Q4 - Heart Rate Cleaner
 */

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("heart_rate.txt");
    if (!inFile) {
        cout << "heart_rate.txt not found!" << endl;
        return 1;
    }

    int rate[100];
    int count = 0;      
    int bad = 0;        
    int x;
    char junk[50];
    int reason = 0;   

    while (true) {
        // FIX 1 : Check if the array is full before reading the next value
        if (count == 100) {
            reason = 3;
            break;
        }
        if (inFile >> x) {
            // FIX 2 : -1 is the sentinel, so stop reading
            if (x == -1) {
                reason = 1;
                break;
            }
            rate[count] = x;
            // FIX 3 : Move to the next free slot in the array
            count++;
        }
        // FIX 4 : Checking eof() first so the end of the file is not counted as junk
        else if (inFile.eof()) {
            reason = 2;
            break;
        }
        else {
            // FIX 5 : Clear the failed state, otherwise reading never works again
            inFile.clear();
            inFile >> junk;
            bad++;
        }
    }
    inFile.close();

    // FIX 6 (TODO 1): Write every valid reading to the clean file, one per line
    ofstream outFile("clean_heart_rate.txt");
    for (int i = 0; i < count; i++)
        outFile << rate[i] << endl;
    outFile.close();

    // FIX 7 (TODO 2): Always show the valid and junk counts
    cout << "Valid readings: " << count << endl;
    cout << "Junk skipped: " << bad << endl;

    // FIX 8 (TODO 3): If there are no readings show a message, else calculate the results
    if (count == 0)
        cout << "No valid readings!" << endl;
    else {
        int total = 0, highest = rate[0], above = 0, alerts = 0;
        for (int i = 0; i < count; i++) {
            total += rate[i];
            if (rate[i] > highest) highest = rate[i];
            if (rate[i] > 100) alerts++;
        }
        double avg = (double)total / count;   
        for (int i = 0; i < count; i++)
            if (rate[i] > avg) above++;       

        cout << "Average: " << avg << endl;
        cout << "Highest: " << highest << endl;
        cout << "Above average: " << above << endl;
        cout << "Alerts (above 100): " << alerts << endl;
    }

    // FIX 9 (TODO 4): is showing why the loop stopped
    cout << "Stopped because: ";
    if (reason == 1) cout << "sentinel found" << endl;
    else if (reason == 2) cout << "end of file" << endl;
    else cout << "array full" << endl;

    return 0;
}