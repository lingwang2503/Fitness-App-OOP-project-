#include "Header.h"

Exercise storeExerciseList(string line) {
	Exercise one;
	string temp;
	int i = 0;
	while (i < line.length())
	{
		while ((line[i] != ',') && (i < line.length()))
		{
			temp += line[i];
			i++;
		}
		if (one.name == "")
			one.name = temp;
		else if (temp == "easy" || temp == "intermediate" || temp == "advanced")
			one.level = temp;
		else if (temp == "ABS" || temp == "BUTT" || temp == "THIGH")
			one.target = temp;
		else
			one.len = temp;
		temp.clear();
		i++;
	}
	return one;

}

User storeUserList(string line) {
	User one;
	one.age = one.weight = 0;
	string temp;
	int i = 0;
	while (i < line.length())
	{
		while ((line[i] != ',') && (i < line.length()))
		{
			temp += line[i];
			i++;
		}
		if (one.ID == "")
			one.ID = temp;
		else if (one.name == "")
			one.name = temp;
		else if (one.age == 0)
			one.age = stoi(temp);
		else if (one.weight == 0)
			one.weight = stoi(temp);
		else one.height = stof(temp);

		temp.clear();
		i++;
	}
	one.BMI = float(one.weight) / pow(one.height,2);
	return one;
}

UserTarget storeUserTargetList(string line) {
	UserTarget one;
	string temp;
	int i = 0;
	while (i < line.length())
	{
		while ((line[i] != ',') && (i < line.length()))
		{
			temp += line[i];
			i++;
		}
		if (one.userID == "")
			one.userID = temp;
		else if (one.name == "")
			one.name = temp;
		else if (one.level == "") one.level = temp;
		else one.dayRemaining = stoi(temp);
		temp.clear();
		i++;
	}
	
	return one;
}

User createAccount(vector<User> &listAcc)
{
	User acc;
	bool checkUsername = true;
	while (checkUsername)
	{
		cout << "-- REGISTER -- " << endl;
		cout << "Input username: ";
		cin >> acc.ID;
		bool flag = false;
		for (int i = 0; i < listAcc.size(); i++)
		{
			if (acc.ID == listAcc[i].ID)
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			checkUsername = false;
			break;
		}
	}

	cin.ignore();
	cout << "Full name: ";
	getline(cin, acc.name);
	
	cout << "Age: ";
	cin >> acc.age;
	
	cout << "Weight: ";
	cin >> acc.weight;
	
	cout << "Height: ";
	cin >> acc.height;
	acc.BMI = float(acc.weight) / pow(acc.height,2);

	listAcc.push_back(acc);

	return acc;
	
}

void Account::seeProfile() {
	cout << "-----------------------------------" << endl;
	cout << "Username: " << this->acc.ID << endl;
	cout << "Full name: " << this->acc.name << endl;
	cout << "Age: " << this->acc.age << endl;
	cout << "Weight: " << this->acc.weight << " kg" << endl;
	cout << "Height: " << this->acc.height << " metters" << endl;
	cout << "BMI: " << this->acc.BMI << endl;
	cout << "-----------------------------------" << endl;

	float w = this->acc.height;
	cout << "Your perfect weight: " << (int(w *100) % 100) * 9 / 10 << " kg" << endl;
	cout << "Your maximum weight: " << (int(w * 100) % 100) << " kg" << endl;
	cout << "Your minimum weigth: " << (int(w * 100) % 100) * 8 / 10 << " kg" << endl;
	cout << "-----------------------------------" << endl;
	system("pause");
}

User Account::editProfile(vector<User> list)
{
	cout << "Input new age: ";
	cin >> this->acc.age;
	cout << "Input new weight: ";
	cin >> this->acc.weight;
	cout << "Input new height: ";
	cin >> this->acc.height;
	this->acc.BMI = float(this->acc.weight) / this->acc.height;
	cout << "-----------------------------------------------" << endl;
	cout << "Edit profile successfully." << endl;
	system("pause");
	return this->acc;
}

void Account::seeTargets(vector<Exercise> list)
{
	//show id, tên target và level
	//chọn 1 id để xem list bài tập của target đó
	//lặp lại cho đến khi chọn 0 (break) 

	cout << "Your target list: " << endl;
	cout << "-----------------------------------------------" << endl;
	for (int i = 0; i < this->target.size(); i++)
	{
		cout << i + 1 << ". " << this->target[i].name << " - Level: " << this->target[i].level << " - Day remaining: " << this->target[i].dayRemaining << " days." << endl;
	}

	int C = 1;

	while (C != 0)
	{
		cout << "-----------------------------------------------" << endl;
		cout << "Choose a target to see the exercise list: ";
		cin >> C;
		if (C == 0) break;
		this->doingTarget = Workout(this->target[C - 1],this->getAcc(), list);
		this->doingTarget.showExerciseList(list);
	}

}

vector<UserTarget> Account:: chooseTaget(vector<Exercise> X, vector<UserTarget> &list)
{
	Workout target;
	string name;
	string level;
	bool check = false;
	while (!check)
	{
		cout << "Input your target: ";
		cin >> name;
		cout << "Inout your level: ";
		cin >> level;
		for (int i = 0; i < this->target.size(); i++)
		{
			if (this->target[i].name == name && this->target[i].level == level)
			{
				check = true;
				target = Workout(this->target[i], this->acc,X);
				cout << "-----------------------------------------------" << endl;
				cout << "Tutorial: Press enter to show the first exercise. Press enter again whenever you have finished the exercise to show the next exercise." << endl;
				cout << "-----------------------------------------------" << endl;
				int x = target.runningExerciseProgress();
				list = this->updateDayInList(list,target);
				break;
			}
			else
			{
				check = false;
			}
		}
		if (check == false)
		{
			cout << "-----------------------------------------------" << endl;
			cout << "There was no target / level in your list. Please check again. " << endl;
		}

	}

	return list;
}

vector<UserTarget> Account::createNewTarget(vector<Exercise> list, string name, string level, vector<UserTarget> listTarget) {

	UserTarget temp;
	temp.name = name;
	temp.level = level;
	temp.dayRemaining = 30;
	temp.userID = this->acc.ID;

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].name == name && list[i].level == level)
		{
			temp.exe.push_back(list[i]);
		}
	}
	cout << "-----------------------------------------------" << endl;
	cout << "Create new target successfully." << endl;
	system("pause");
	system("cls");
	cout << "Your new target: " << temp.name << " - " << temp.level << endl;
	cout << "Day remaining: " << temp.dayRemaining << endl;
	this->setTarget(temp);
	listTarget.push_back(temp);
	return listTarget;
}

void Workout:: showExercise(Exercise &x)
{
	cout << "Exercise name: " << x.name << endl;
	cout << "Times: x" << x.len << endl;
}

int Workout:: runningExerciseProgress() {
	vector<Exercise> x = this->getExe();
	int i = 0;
	char key_press;
	while (1)
	{
		key_press = _getch();
		if (key_press == 13)
		{
			cout << "-----------------------------------------------" << endl;
			this->showExercise(x[i]);
			i++;
			if (i == x.size())
			{
				this->target.dayRemaining = this->updateDay();
				cout << "-----------------------------------------------" << endl;
				cout << "You have finished the exercise. Day remaining: " << this->getDayRemaining() << " days" << endl;
				break;

			}
		}
		if (key_press == 27)
		{
			if (i == x.size())
			{
				this->updateDay();
				cout << "You have finished the exercise. Day remaining: " << this->getDayRemaining() << " days" << endl;
				break;
				
			}
			else break;
		}
	}
	return this->getDayRemaining();

}

void Workout:: showExerciseList(vector<Exercise> list)
{
	cout << endl;
	cout << "Your exercise list for this target: " << endl;
	for (int j = 0; j < list.size(); j++)
	{
		if(this->target.name == list[j].target && this->target.level == list[j].level)
			cout << list[j].name << " - " << list[j].len << " times" << endl;
	}
}

int menu1(int &n)
{
	cout << "\033[93m WELCOME TO FITNESS - WORKOUT APP! \033[0m" << endl;
	cout << endl;
	cout << "-- WHAT DO YOU WANT TO DO? -- " << endl;
	cout << "------------------------------" << endl;
	cout << "| 1. Register                |" << endl;
	cout << "| 2. Log in                  |" << endl;
	cout << "| 3. Exit                    |" << endl;
	cout << "------------------------------" << endl;
	
	cout << endl;
	cout << "Your choice: ";
	cin >> n;

	return n;
}

int menu2(int& n) {
	cout << "-- THAT DO YOU WANT TO DO? -- " << endl;
	cout << "------------------------------" << endl;
	cout << "| 1. See your profile        |" << endl;
	cout << "| 2. Edit profile            |" << endl;
	cout << "| 3. Choose new target       |" << endl;
	cout << "| 4. Your targets            |" << endl;
	cout << "| 5. Workout now             |" << endl;
	cout << "| 6. Log out                 |" << endl;
	cout << "------------------------------" << endl;
	cout << "Your choice: ";
	cin >> n;

	return n;
}

void menuTarget()
{
	cout << "1. ABS - easy: 3 exercises - 30 days" << endl;
	cout << "2. ABS - intermediate: 3 exercises - 30 days" << endl;
	cout << "3. ABS - advanced: 3 exercises - 30 days" << endl;
	cout << "4. BUTT - easy: 3 exercises - 30 days" << endl;
	cout << "5. BUTT - intermediate: 3 exercises - 30 days" << endl;
	cout << "6. BUTT - advanced: 3 exercises - 30 days" << endl;
	cout << "7. THIGH - easy: 3 exercises - 30 days" << endl;
	cout << "8. THIGH - intermediate: 3 exercises - 30 days" << endl;
	cout << "9. THIGH - advanced: 3 exercises - 30 days" << endl;
}

void writeTargetToFile(ofstream &output, vector<UserTarget> list)
{
	output.open("list_target.txt");
	for (int i = 0; i < list.size(); i++)
	{
		output << list[i].userID << "," << list[i].name << "," << list[i].level << "," << list[i].dayRemaining;
		if (i < list.size() - 1)
			output << "\n";
	}
	output.close();
}

void writeUsersToFile(ofstream &output, vector<User> list)
{
	output.open("user.txt");
	for (int i = 0; i < list.size(); i++)
	{
		output << list[i].ID << "," << list[i].name << "," << list[i].age << "," << list[i].weight << "," << list[i].height;
		if (i <= list.size() - 1)
			output << "\n";
	}
	output.close();
}
