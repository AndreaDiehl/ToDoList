#include "Tasks.h"
using namespace std; 


Task::Task() {
	name = "task";
	priorityLevel = 1;
	min = 10;
}
Task::Task(string name, int priorityLevel, int min) {
	this->name = name;
	this->priorityLevel = priorityLevel;
	this->min = min;
}

string Task::getName() {
	return name;
}
int Task::getPriority() {
	return priorityLevel;
}
int Task::getMin() {
	return min;
}
void Task::getInfo() {
	cout << endl << "Task name: " << name << endl;
	cout << "Priority level: " << priorityLevel << endl;
	cout << "Comletion time: " << min << " minutes" << endl;
}
void Task::setName() {
	cout << "Please enter the task's name: ";
	cin >> name;
	this->name = name;
}
void Task::setPriority() {
	cout << "Please enter the task's priority level from 1 (lowest) to 5 (highest): ";
	try {
		cin >> priorityLevel;
		if (cin.fail()) {
			throw invalid_argument("Please enter a number");
		}
		while (priorityLevel < 1 || priorityLevel > 5) {
			cout << "Please enter a number between 1 and 5: ";
			cin >> priorityLevel;
			if (cin.fail()) {
				throw invalid_argument("Please enter a number");
			}
		}
	} 
	catch (const invalid_argument& e) {
		cout << "Invalid argument error: " << e.what() << endl;
	}

	this->priorityLevel = priorityLevel;
}
void Task::setMin() {
	cout << "Please enter how many minutes this task should take to complete: ";
	try {
		cin >> min;
		if (cin.fail()) {
			throw invalid_argument("Please enter a number");
		}
		while(min < 0) {
			cout << "Please enter a positive number: "; 
			cin >> min;
			if (cin.fail()) {
				throw invalid_argument("Please enter a number");
			}
		}
	}
	catch (const invalid_argument& e) {
		cout << "Invalid argument error: " << e.what() << endl;
	}
	this->min = min;
}


void Manage::printTasks(Task list[], int size) {
	cout << endl << "You should complete your tasks in the following order: " << endl;
	for (int i = 0; i < size; i++) {
		cout << list[i].getName();
		if (list[i].getName().length() < 8) {
			cout << "\t";
		}
		cout << "\t (priority: " << list[i].getPriority() << ", " << list[i].getMin() << " min)" << endl;
	}
}
void Manage::addTasks(Task list[], int *size) {
	int num;
	int newSize; 

	//Number of new tasks
	cout << endl << "How many tasks would you like to add? ";
	
	try {
		cin >> num;
		if (cin.fail()) {
			throw invalid_argument("Please enter a number");
		}
		while (num < 0) {
			cout << "Out of range! Please enter a different value: ";
			cin >> num;
			if (cin.fail()) {
				throw invalid_argument("Please enter a number");
			}
		}
	}
	catch (const invalid_argument& e) {
		cout << "Invalid argument error: " << e.what() << endl;
	}

	if (num == 0) {
		cout << "0 tasks have been added" << endl;
		return;
	}

	newSize = *size + num;

	
	//Temporary Array 
	Task* bigArr = new Task[newSize];
	for (int i = 0; i < *size; i++) {
		bigArr[i] = list[i]; 
	}
	for (int i = *size; i < newSize; i++) {
		bigArr[i].setName(); 
		bigArr[i].setPriority(); 
		bigArr[i].setMin(); 
	}

	//Update values
	*size = newSize;

	for (int i = 0; i < newSize; i++) {
		list[i] = bigArr[i];
	}

	delete[] bigArr;
}

void Manage::removeTasks(Task list[], int *size) {
	int num;

	//Which tasks to remove 
	cout << endl << "How many tasks would you like to remove? ";

	try {
		cin >> num;
		if (cin.fail()) {
			throw invalid_argument("Please enter a number");
		}
		while (num < 0 || num > *size) {
			cout << "Out of range! Please enter a different value: ";
			cin >> num;
			if (cin.fail()) {
				throw invalid_argument("Please enter a number");
			}
		}
	}
	catch (const invalid_argument& e) {
		cout << "Invalid argument error: " << e.what() << endl;
	}

	if (num == 0) {
		cout << "0 tasks have been removed" << endl; 
		return; 
	}
	

	int newSize = *size - num;
	int* completed = new int[num];

	cout << "Here are your curent tasks: " << endl;
	for (int i = 0; i < *size; i++) {
		cout << i + 1 << ": " << list[i].getName() << endl;
	}
	cout << endl << "Please enter the numbers of the tasks you would like to remove: ";
	for (int i = 0; i < num; i++) {
		cin >> completed[i];
		if (completed[i]<1 || completed[i] > *size){
			cout << "Out of bounds error: Invalid task number";
			return; 
		 }
	}
	//sort completed[]
	int min = 0;
	int index = 0;
	int temp = 0;

	for (int i = 0; i < (num - 1); i++) {
		index = i;
		min = completed[i];
		for (int j = i + 1; j < num; j++) {
			if (completed[j] < min) {
				index = j;
				min = completed[j];
			}
		}
		if (i != index) {
			temp = completed[i];
			completed[i] = completed[index];
			completed[index] = temp;
		}
	}

	//Temporary Array
	Task* smallArr = new Task[newSize];

	for (int i = 0, j = 0, k = 0; i < *size; i++) {
		if (j < num && completed[j] - 1 == i) {
			j++;
		}
		else {
			smallArr[k++] = list[i]; 
		}
	}

	//Confirmation statement 
	for (int i = 0; i < num; i++) {
		if (i == num - 1 && num > 1) {
			cout << "and ";
		}
		cout << list[completed[i] - 1].getName();
		if (i < num - 1 && num > 2) {
			cout << ", ";
		}
		else if (num == 2 && i < num - 1) {
			cout << " ";
		}
	}
	if (num > 1) {
		cout << " have been removed" << endl;
	}
	if (num == 1) {
		cout << " has been removed" << endl;
	}
	
	//Final details
	for (int i = 0; i < newSize; i++) {
		list[i] = smallArr[i];
	}
	*size = newSize;

	delete[] completed; 
	delete[] smallArr; 

}

void Manage::searchByPrior(Task list[], int size) {
	int val;
	int index = -1;
	
	cout << endl << "Which priority level would you like to see? ";

	try {
		cin >> val;
		if (cin.fail()) {
			throw invalid_argument("Please enter a number");
		}

		while (val < 1 || val > 5) {
			cout << "Please enter a number between 1 and 5: ";
			cin >> val;
			if (cin.fail()) {
				throw invalid_argument("Please enter a number");
			}
		}

		cout << endl << "The tasks at the priority level " << val << " are: " << endl;
		for (int i = 0; i < size; i++) {
			if (list[i].getPriority() == val) {
				index = i;
				cout << "   " << list[i].getName() << " (" << list[i].getMin() << " min) " << endl;
			}
		}
		if (index == -1) {
			cout << "   N/A\n";
		}
	}
	catch (const invalid_argument& e) {
		cout << "Invalid argument error: " << e.what() << endl;
	}
}

void Manage::sortByMin(Task list[], int size) {
	int minMin = 0;
	int minIn = 0;
	Task temp = { "temp", 0, 0 };
		for (int i = 0; i < (size - 1); i++) {
		minIn = i;
		minMin = list[i].getMin();
		for (int j = i + 1; j < size; j++) {
			if (list[j].getMin() < minMin) {
				minIn = j;
				minMin = list[j].getMin();
			}
		}
		if (i != minIn) {
			temp = list[i];
			list[i] = list[minIn];
			list[minIn] = temp;
		}
	}
	cout << "Tasks have been sorted" << endl;
}

void Manage::sortByPrior(Task list[], int size) {
	Task temp = { "temp", 0, 0 };
	bool flag;

	for (int i = 0; i < size - 1; i++) {
		flag = true;
		for (int j = 0; j < size - i - 1; j++) {
			if (list[j].getPriority() > list[j + 1].getPriority()) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
				flag = false;
			}
		}
		if (flag) {
			break;
		}
	}
	cout << "Tasks have been sorted" << endl;
}


