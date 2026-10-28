/*
 * Name       : Muaz Ahmad
 * Reg No     : L1S26BSCS0074
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
//FIX 1: header file was missing ifstream and ofstream would be unknown
#include <fstream>         
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    //FIX 2 : Not in file is the true condition without it condition was inverted
    if (!inFile) {   
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    //FIX 3 : IOS APP was missing we have to keep the old lines
    ofstream reorder("reorder.txt", ios::app);   

    char code[10];
    int qty, count = 0, low = 0;
    double price; 

    //FIX 4 : Incorrect data type since price is in decimals     
    double total = 0;

    // FIX 5 : here we are ignoring the header line in the file
    inFile.ignore(100, '\n'); 

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;       
        if (qty < 10) {
            // FIX 6 : here endl is using to get items in each line "one item per line"
            reorder << code << " " << qty << endl; 
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
