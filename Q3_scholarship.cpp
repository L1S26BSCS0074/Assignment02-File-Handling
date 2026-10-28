/*
 * Name       : Muaz Ahmad
 * Reg No     : L1S26BSCS0074
 * Assignment : 02 - File Handling
 * Question   : Q3_scholarship
 */

// FIX 1: Well this defines that warning/error
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main()
{
	char path[100];
	cout << "Enter the file name: ";
	// FIX 1: I Used thiosss because file name may contain spaces
	cin.getline(path, 100);

	ifstream inFile(path);
	// FIX 2: IT checks whether the file opened
	if (!inFile.is_open())
	{
		cout << "Could not open " << path << "!" << endl;
		return 1;
	}

	int n;
	inFile >> n;
	// FIX 3: Used this otherwise the first name would start with a leftover new line
	inFile.ignore(100, '\n');
	// FIX 4: If n is more than 30(the limit is given in the question) show too many students
	if (n > 30)
	{
		cout << "Too many students!" << endl;
		return 1;
	}

	// FIX 5: (old content is erased), as the question requires
	ofstream scholarship("scholarship.txt");

	char name[30], topName[30] = "";
	
	double cgpa, sum = 0, top = -1;

	int count = 0, eligible = 0;

	for (int i = 0; i < n; i++)
	{
		if (!inFile.getline(name, 30, ',') || !(inFile >> cgpa))
		{
			break;
		}
		// FIX 6: ignore(100, '\n') after the CGPA so the next name does not start with a new line
		inFile.ignore(100, '\n');

		
		cout << "[" << name << "] CGPA: " << cgpa << endl;
		count++;
		sum = sum + cgpa;

		// FIX 7: Students with a CGPA of 3.50 or more (>=) are written to scholarship.txt as "Full Name,CGPA"
		if (cgpa >= 3.50)
		{
			scholarship << name << "," << cgpa << endl;
			eligible++;
		}
		if (cgpa > top)
		{
			top = cgpa;
			strcpy(topName, name);
		}
	}
	// FIX 8: Both files are closed after the loop because reading and writing are finished
	inFile.close();
	scholarship.close();

	
	if (count < n)
	{
		cout << "Warning: only " << count << " of " << n << " records found." << endl;
	}
	
	if (count == 0)
	{
		cout << "No students found!" << endl;
		return 1;
	}

	// FIX 9: The four summary lines; the average uses count (not n) so it stays correct even when the file ends early
	cout << "Students: " << count << endl;
	cout << "Average CGPA: " << sum / count << endl;
	cout << "Eligible for scholarship: " << eligible << endl;
	cout << "Top student: " << topName << " (" << top << ")" << endl;
	return 0;
}