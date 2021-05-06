#include "Header.h"

int main()
{
    ofstream output;
    ifstream f;
    string line;

    //đọc từ file list tất cà bài tập của app 

    Exercise oneExercise;
    vector<Exercise> exerciseList;
    f.open("exercises.txt");
    if (f.fail())
    {
        cout << "Failed to open this file!" << std::endl;
    }
    else {
        while (!f.eof())
        {
            getline(f, line);
            oneExercise = storeExerciseList(line);
            exerciseList.push_back(oneExercise);
        }
        f.close();
    }

    // Đọc từ file danh sách user hiện có của app
    User anUser;
    vector<User> userList;

    f.open("user.txt");
    if (f.fail())
    {
        cout << "Failed to open this file!" << std::endl;
    }
    else {
        while (!f.eof())
        {
            getline(f, line);
            anUser = storeUserList(line);
            userList.push_back(anUser);
        }
        f.close();
    }

    Account user;

    //đọc từ file dữ liệu các bài tập của Users
    UserTarget t;
    vector<UserTarget> listTarget;
    f.open("list_target.txt");
    if (f.fail())
    {
        cout << "Failed to open this file!" << std::endl;
    }
    else {
        while (!f.eof())
        {
            getline(f, line);
            t = storeUserTargetList(line);
            listTarget.push_back(t);
        }
        f.close();
    }

    int n = 0;
    while (n != 3) {
        system("cls");
        n = menu1(n);
        switch (n) {
        case 1:
        {
            system("cls");
            anUser = createAccount(userList);
            bool check = false;
            for (int i = 0; i < userList.size(); i++)
            {
                if (userList[i].ID == anUser.ID)
                {
                    check = true;
                    break;
                }
            }
            if (check)
            {
                cout << endl;
                cout << "Register successed. Please login to workout." << endl;
                system("pause");
                writeUsersToFile(output, userList);
            }
            else
            {
                cout << "Register failed. Please register again or login." << endl;
                cout << endl;
            }
            break;
        }
        case 2:
        {
            system("cls");
            string id;
            bool flag = false;
            cout << "Username: ";
            cin >> id;

            for (int i = 0; i < userList.size(); i++)
            {
                if (userList[i].ID == id)
                {
                    user = Account(userList[i], listTarget);
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                cout << "Wrong username or password. Please login again or register. " << endl;
                cout << endl;
                system("pause");
            }
            else

            {
                int m = 0;
                while (m != 6) {
                    system("cls");
                    cout << "\033[93m Welcome " << user.getAcc().name << "! \033[0m" << endl;
                    cout << endl;
                    m = menu2(m);
                    switch (m) {
                    case 1:
                    {
                        system("cls");
                        user.seeProfile();
                        break;
                    }
                    case 2: 
                    {
                        system("cls");
                        anUser = user.editProfile(userList);
                        for (int i = 0; i < userList.size(); i++)
                        {
                            if (anUser.ID == userList[i].ID)
                                userList[i] = anUser;
                        }
                        writeUsersToFile(output, userList);
                        break;
                    }
                    case 3:
                    {
                        string name;
                        string level;
                        bool flag = false;
                        while (flag == false)
                        {
                            system("cls");
                            menuTarget();
                            cout << "Input the target name and level you want to do (<name> <level>) : ";
                            cin >> name >> level;
                            if (name == "0") break;
                            if (user.getTargetList().size() == 0)
                            {
                                flag - true;
                                break;
                            }
                            else
                            {
                                for (int i = 0; i < user.getTargetList().size(); i++)
                                {
                                    if (user.getTargetList()[i].name == name && user.getTargetList()[i].level == level)
                                    {
                                        flag = false;
                                        cout << endl;
                                        cout << "This target is already existed in your list. Please choose another target." << endl;
                                        system("pause");
                                        break;
                                    }
                                    else flag = true;
                                }
                            }
                        }
                        if (name == "0") break;
                        else
                        {
                            listTarget = user.createNewTarget(exerciseList, name, level, listTarget);
                            writeTargetToFile(output, listTarget);
                            for (int i = 0; i < listTarget.size(); i++)
                            {
                                if (listTarget[i].name == name && listTarget[i].level == level)
                                {
                                    cout << "You've created new target. Let's start workout!" << endl;
                                    break;
                                }
                            }
                            system("pause");
                            break;
                        }
                    }
                       
                    case 4:
                    {
                        system("cls");
                        user.seeTargets(exerciseList);
                        system("pause");
                        break;
                    }

                    case 5:
                    {
                        system("cls");
                        cout << "Your target list: " << endl;
                        cout << "-----------------------------------------------" << endl;
                        for (int i = 0; i < user.getTargetList().size(); i++)
                        {
                            cout << i + 1 << ". " << user.getTargetList()[i].name << " - Level: " << user.getTargetList()[i].level << " - Day remaining: " << user.getTargetList()[i].dayRemaining << " days." << endl;
                        }
                        cout << endl;
                        listTarget = user.chooseTaget(exerciseList, listTarget);
                        writeTargetToFile(output, listTarget);
                        user.updateTargetList(listTarget);
                        system("pause");
                        break;
                    }
                    default:
                    {
                        m = 6;
                        break;
                    }
                    }
                    if (m == 6) break;
                }

            }
            break;
        }
        default:
        {
            n = 3;
            break;
        }
            
        }
        if (n == 3) break;
    }
    
    //ghi lại lần nữa dữ liệu sau khi thoát app
    writeTargetToFile(output, listTarget);
    writeUsersToFile(output, userList);

    return 0;
}

