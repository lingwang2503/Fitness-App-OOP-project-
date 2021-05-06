#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <math.h>
#include<stdio.h>
#include "dos.h"
#include <stdlib.h>
using namespace std;



struct Exercise {
	string name;
	string len;
	string level;
	string target;
};

struct User {
	string ID;
	string name;
	int age, weight, BMI;
	float height;
};

struct UserTarget {
	vector<Exercise> exe;
	string name;
	string userID;
	string level;
	int dayRemaining;
};

class Workout {
private:
	UserTarget target;
public:

	
	int getDayRemaining()
	{
		return this->target.dayRemaining;
	}

	int updateDay()
	{
		this->target.dayRemaining -= 1;
		return this->target.dayRemaining;
	}

	vector<Exercise> getExe()
	{
		return this->target.exe;
	}

	void setExe(vector<Exercise>x) {
		for (int i = 0; i < x.size(); i++)
		{
			if (this->target.name == x[i].target && this->target.level == x[i].level)
				this->target.exe.push_back(x[i]);
		}
	}
	string getName()
	{
		return this->target.name;
	}

	string getUserID()
	{
		return this->target.userID;
	}

	string getLevel()
	{
		return this->target.level;
	}

	void setExerciseList(vector<Exercise> list)
	{
		Exercise x;
		for (int i = 0; i < list.size(); i++)
		{
			if (this->getName() == list[i].target && this->getLevel() == list[i].level)
			{
				x = list[i];
				this->getExe().push_back(x);
			}
		}
	}
	Workout(UserTarget x, User acc, vector<Exercise> X)
	{
		this->target.name = x.name;
		this->target.level = x.level;
		this->setExe(X);
		this->target.dayRemaining = x.dayRemaining;
		this->target.userID = acc.ID;
	}

	Workout()
	{

	}
	~Workout()
	{

	}

	int runningExerciseProgress();
	void showExercise(Exercise& x);
	void showExerciseList(vector<Exercise> list);

};

class Account {
private:
	User acc;
	vector<UserTarget> target;
	Workout doingTarget;

public:

	void setTarget(UserTarget x)
	{
		this->target.push_back(x);
	}
	User getAcc()
	{

		return this->acc;
	}
	vector<UserTarget> getTargetList()
	{
		return this->target;
	}
	vector<UserTarget> updateTargetList(vector<UserTarget> list)
	{
		this->target.clear();
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].userID == this->acc.ID)
				this->setTarget(list[i]);
		}
		return this->target;
	}

public:
	Account() {
		this->acc.age = this->acc.weight = 0;
		this->acc.height = 0;
		this->acc.BMI = 0;
	}

	Account(User a, vector<UserTarget> t)
	{
		this->acc = a;
		UserTarget x;
		for (int i = 0; i < t.size(); i++)
		{
			if (t[i].userID == this->acc.ID)
			{
				x = t[i];
				this->target.push_back(x);
			}
		}
		
	}

	~Account()
	{
		this->acc.age = this->acc.weight = 0;
		this->acc.height = 0;
		this->acc.BMI = 0;
		this->acc.ID = "";
		this->acc.name = "";
		this->target.clear();
	}

	
public:
	void seeProfile();
	User editProfile(vector<User> list);
	void seeTargets(vector<Exercise> list);
	vector<UserTarget> createNewTarget(vector<Exercise> list, string name, string level, vector<UserTarget> listTarget);
	vector<UserTarget> chooseTaget(vector<Exercise> X,vector<UserTarget> &list);
	vector<UserTarget> updateDayInList(vector<UserTarget> list, Workout target)
	{
		for (int j = 0; j < list.size(); j++)
		{
			if (list[j].name == target.getName() && list[j].level == target.getLevel())
				list[j].dayRemaining = target.getDayRemaining();
		}
		return list;
	}
};

Exercise storeExerciseList(string line);
User storeUserList(string line);
User createAccount(vector<User> &listAcc);
UserTarget storeUserTargetList(string line);
int menu1(int& n);
int menu2(int& n);
void menuTarget();
void writeTargetToFile(ofstream &output, vector<UserTarget> list);
void writeUsersToFile(ofstream &output, vector<User> list);