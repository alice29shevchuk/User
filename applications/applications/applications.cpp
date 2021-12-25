#include <iostream>
#include<string>
using namespace std;
class User
{
	string name;
	string surname;
	int age;
	long id;
public:
	User()
	{
		this->name = "Alisa";
		this->surname = "Shevchuk";
		this->age = 19;
		this->id = 0;
	}
	User(string name,string surname,int age)
	{
		this->name = name;
		this->surname = surname;
		this->age = age;
		this->id = 0;
	}
	friend ostream& operator<<(ostream& out, const User& user)
	{
		out << "Имя: " << user.name << "\nФамилия: " << user.surname << "\nВозраст: " << user.age << "\n";
		return out;
	}
	void setName(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return this->name;
	}

	void setSurname(string surname)
	{
		this->surname = surname;
	}
	string getSurname()
	{
		return this->surname;
	}

	void setAge(int age)
	{
		this->age = age;
	}
	int getAge()
	{
		return this->age;
	}

	void setId(long id)
	{
		this->id = id;
	}
	long getId()
	{
		return this->id;
	}
};
class Users
{
	int size;
	User* arr;
public:
	Users()
	{
		this->size = 0;
	}
	Users(int size)
	{
		this->size = size;
		this->arr = new User[size];
	}
	void Add(User*&user)
	{
		user->setId(this->size + 1);
		User* tmp = new User[this->size + 1];
		for (int i = 0; i < this->size; i++)
		{
			tmp[i] = arr[i];
		}
		tmp[this->size] = *user;
		delete[]arr;
		arr = tmp;
		this->size++;
	}
	void Save()
	{
		FILE* pf;
		fopen_s(&pf, "file.txt", "wt");
		if (pf != nullptr)
		{
			//fprintf(pf, "%i\n", this->size);
			for (int i = 0; i < this->size; i++)
			{
				fprintf(pf, "%s\t%s\t%i\t%i\n", this->arr[i].getName().c_str(),this->arr[i].getSurname().c_str(),this->arr[i].getAge(),this->arr[i].getId());
			}
			fclose(pf);
			cout << "Информация записана в файл!\n";
		}
		else
		{
			cout << "Error!\n";
		}
	}
};
int main()
{
	setlocale(0, "");
	User* user = new User();
	Users users;
	int ch;
	int age;
	string name;
	string surname;
	do
	{
		cout << "МЕНЮ:\n";
		cout << "1 - Добавить пользователя\n";
		cout << "2 - Записать в файл\n";
		cout << "0 - Выход\n";
		cout << "Ваш выбор: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			cout << "Введите имя: ";
			cin >> name;
			user->setName(name);
			cout << "Введите фамилию: ";
			cin >> surname;
			user->setSurname(surname);
			cout << "Введите возраст: ";
			cin >> age;
			user->setAge(age);
			users.Add(user);
			system("cls");
			cout << "Пользователь добавлен!\n";
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			users.Save();
			system("pause");
			system("cls");
			break;
		}
	} while (ch != 0);
	system("cls");
	cout << "ВЫ ВЫШЛИ!";
}
