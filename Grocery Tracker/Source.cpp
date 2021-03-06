#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

const char frequencyPyFile[]	= "Frequency";				// Module name for Frequency Python module ("Frequency.py")
const char itemFile[]			= "ItemsPurchased.txt";		// File that stores items to be read in.
const char frequencyDataFile[]	= "frequency.dat";			// File that stores the itmes and their quantity

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule(frequencyPyFile);
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString(frequencyPyFile);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString(frequencyPyFile);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void GetItemCountMenu() {
	string userString;	// String to store user input.
	int itemCount = 0;	// Item count.

	while (true) {												// Prompt for item name.
		cout << endl << "Enter the name of the item: ";
		cin >> userString;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << endl << "Invalid entry. Please try again." << endl;
			continue;
		}
		break;
	}

	cout << "Quantity: " << callIntFunc("GetItemCount", userString) << endl;	// Outout result.
}

void DisplayHistogram() {	// Display a histogram by reading, writing then reading a file again...
	string item = "";								// Item description.
	unsigned int quantity;							// Item quantity.
	unsigned int maxItemStrLen = 0;					// Longest item string length aid in formating output.
	vector<tuple<string, unsigned int> > items;		// Vector of tuples to store items.

	CallProcedure("WriteFrequencyFile");			// Write out the frequency data file using Python.

	ifstream inFS;	// Input file stream.
	inFS.open(frequencyDataFile);	// Open the file.

	if (!inFS.is_open()) {							// Check to make sure the file is open.
		cout << "Could not open file." << endl;
	}

	cout << "Histogram" << endl
		 << "---------" << endl;
	while (!inFS.fail()) {								// Read in the file...
		inFS >> item >> quantity;
		if (inFS.fail()) {break;}						// Break if input fails, typically if the the end of file is reached and the last line is empty.
		if (item.length() > maxItemStrLen) { maxItemStrLen = item.length(); }
		items.push_back(make_tuple(item, quantity));
	}
	inFS.close();

	for (size_t i = 0; i < items.size(); ++i) {	// Display each item for the histogram.
		tie(item, quantity) = items[i];			// Pull the data back out of the vector.
		cout << right << setw(maxItemStrLen) << item << ": " << string(quantity, '*') << endl;
	}

}

void GroceryMenu() {	// Display the main menu for the Grocery application.
	int userInput = 0;

	while (userInput != 4) {		// Display menu and validate input.
		cout << endl << "Please make a selection: " << endl;
		cout	<< "1: Display list of items and quantity purchased." << endl
				<< "2: Get specific item quantity." << endl
				<< "3: Display Item Histogram." << endl
				<< "4: Exit." << endl;
		cin >> userInput;
		if (cin.fail()) {	// Handle invalid entries.
			cin.clear();
			cin.ignore();
			cout << endl << "Invalid entry. Please try again." << endl;
			continue;
		}

		switch (userInput) {
		case 1:								// Display items.
			CallProcedure("DisplayItems");
			break;
		case 2:								// Search for specific items.
			GetItemCountMenu();
			break;
		case 3:								// Display Histogram.
			DisplayHistogram();
			break;
		default:
			break;
		}
	}
}

void main() {
	GroceryMenu();	// Launch Grocery Menu.
}