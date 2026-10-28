/*
 * Name       : Muaz Ahmad
 * Reg No     : L1S26BSCS0074
 * Assignment : 02 - File Handling
 * Question   : Q5_expense_tracker
 */

#include <iostream>
#include <fstream>
 // FIX 1: cstring is needed for strcmp yk
#include <cstring>
using namespace std;

int main()
{
    int choice;
    char category[20], wanted[20];
    int amount;

    // FIX 2: do while loop shows the menu at least once and repeats until the user chooses 5 as asked in the question
    do
    {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            if (amount <= 0)
            {
                cout << "Invalid amount!" << endl;
            }
            else
            {
                // FIX 3: ios::app to keep the old expenses
                ofstream out("expenses.txt", ios::app);
                out << category << " " << amount << endl;
                out.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2)
        {
            // FIX 4: file is opening again so we can always see the latest data
            ifstream in("expenses.txt");
            char cats[100][20];
            int amts[100];
            int n = 0, total = 0, big = 0;

            while (n < 100 && in >> cats[n] >> amts[n])
            {
                total += amts[n];
                // FIX 5: Must be greater so the first expense stays largest
                if (amts[n] > amts[big])
                {
                    big = n;
                }
                n++;
            }
            in.close();

            if (n == 0)
            {
                cout << "No expenses yet." << endl;
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    cout << i + 1 << ". " << cats[i] << " " << amts[i] << endl;
                }
                cout << "Total spent: " << total << endl;
                cout << "Largest expense: " << cats[big] << " (" << amts[big] << ")" << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Enter category: ";
            cin >> wanted;

            // FIX 6: File is opened again here too, so the latest data is used like the upper i did
            ifstream in("expenses.txt");
            int count = 0, total = 0;
            while (in >> category >> amount)
            {
                // FIX 7: strcmp == 0 means the two words are same
                if (strcmp(category, wanted) == 0)
                {
                    count++;
                    total += amount;
                }
            }
            in.close();

            if (count == 0)
            {
                cout << "No expenses found for " << wanted << endl;
            }
            else
            {
                cout << "Expenses in " << wanted << ": " << count << endl;
                cout << "Total for " << wanted << ": " << total << endl;
            }
        }
        else if (choice == 4)
        {
            // FIX 8:Plain ofstream erases the old content
            ofstream out("expenses.txt");
            out.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5)
        {
            cout << "Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}