#include "Tasks.h"
#include <iostream>
#include <string>
#include <exception>
using namespace std;


int main() {
	int size;
	int answer1;
	char answer2;
	bool loop = true;
	Manage managing;

	cout << "Welcome to your to do list manager!" << endl;

	try {
		cout << "How many tasks would you like to enter? ";
		cin >> size;

		if (cin.fail()) {
			throw invalid_argument("Please enter a number");
		}
		if (size < 1) {
			throw invalid_argument("Please enter at least one task");
		}

		Task* arbeit = new Task[size];

		for (int i = 0; i < size; i++) {
			arbeit[i].setName();
			arbeit[i].setPriority();
			arbeit[i].setMin();
		}

		cout << endl << "Thank you! Here's the info I have: " << endl;

		for (int i = 0; i < size; i++) {
			arbeit[i].getInfo();
		}

		while (loop) {
			cout << endl << "Please enter the number for one of the following commands: " << endl;
			cout << "1. Add Tasks" << endl;
			cout << "2. Remove Tasks" << endl;
			cout << "3. Print Tasks" << endl;
			cout << "4. Print Tasks by Priority Level" << endl;
			cout << "5. Sort Tasks by Time to Complete" << endl;
			cout << "6. Sort Tasks by Priority" << endl;
			cin >> answer1;

			if (cin.fail()) {
				throw invalid_argument("Please enter a number");
			}
			while (answer1 < 1 || answer1 > 6) {
				cout << "Please enter a number between 1 and 6: ";
				cin >> answer1; 
			}

			if (answer1 == 1)
				managing.addTasks(arbeit, &size);
			if (answer1 == 2)
				managing.removeTasks(arbeit, &size);
			if (answer1 == 3)
				managing.printTasks(arbeit, size);
			if (answer1 == 4)
				managing.searchByPrior(arbeit, size);
			if (answer1 == 5)
				managing.sortByMin(arbeit, size);
			if (answer1 == 6)
				managing.sortByPrior(arbeit, size);

			cout << endl << "Would you like to enter more commands? (y/n) ";
			cin >> answer2;

			while (answer2 != 'y' && answer2 != 'Y' && answer2 != 'n' && answer2 != 'N') {
				cout << "Please enter y or n: ";
				cin >> answer2;
			}

			if (answer2 == 'n' || answer2 == 'N') {
				cout << "Bye!";
				loop = false;
			}
		}
		delete[] arbeit; 
	}
	catch (const invalid_argument& e) {
		cout << "Invalid argument error: " << e.what() << endl; 
	}
	catch (...) {
		cout << "Unknown Error" << endl; 
	}

	return 0;
}