#include <iostream>
#include <string>

using namespace std;

#define CAPACITY 100

string names[CAPACITY];      // names
string numbers[CAPACITY];    // phone number
int n = 0;                  // 저장된 사람의 수

void add();
void find();
void status();
void remove();

int main()
{
    string text;
    while (1)
    {
        cout << "$ ";
        getline(cin, text);
        
        if (text == "add")
            add();
        else if (text == "find")
            find();
        else if (text == "status")
            status();
        else if (text == "remove")
            remove();
        else if (text == "exit")
            break;
    }
    return 0;

}


void add()
{
    string name, number;
    cout << "이름을 입력하세요. : ";
    cin >> name;
    names[n] = name;

    cout << "번호를 입력하세요. : ";
    cin >> number;
    numbers[n] = number;
    n++;
    
    cout << name << "이 추가 되었습니다." << endl;
}

void find()
{
    string name;
    cout << "찾고자하는 이름을 입력하세요 :";
    cin >> name;
    for (int i = 0; i < n; i++)
    {
        if (names[i] == name)
        {
            cout << numbers[i] << endl;
        }

        else cout << "찾을 수 없습니다." << endl;
    }
}
void status()
{
    for (int i = 0; i < n; i++)
    {
        cout << names[i] << " " << numbers[i] << endl;
    }
    cout << "입력되어 있는 사람은 " << n << "명 입니다." << endl;
}

void remove()
{
    string name;
    cout << "지울 이름을 입력하세요 : ";
    cin >> name;

    for (int i = 0; i < n; i++)
    {
        if (names[i] == name)
        {
            names[i] = names[n - 1];
            numbers[i] = names[n - 1];
            n--;
            cout << name << "을 지웠습니다." << endl;
        }

        else  cout << "존재하지 않습니다." << endl;
    }
}