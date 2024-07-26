#pragma once
#include <iostream>
#include <string>
using namespace std;

class Task {
private:
	string name;
	int priorityLevel;
	int min;
public:
	Task();
	Task(string name, int priorityLevel, int min);
	~Task() {}

	string getName();
	int getPriority();
	int getMin();
	void getInfo();
	void setName();
	void setPriority();
	void setMin();
};

class Manage {
private:

public:
	Manage() {}
	~Manage() {}

	void addTasks(Task list[], int *size);
	void removeTasks(Task list[], int *size);
	void printTasks(Task list[], int size);
	void searchByPrior(Task list[], int size);
	void sortByMin(Task list[], int size);
	void sortByPrior(Task list[], int size);

};


