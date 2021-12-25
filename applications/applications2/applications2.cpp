#include <iostream>
#include<string>
#include<fstream>
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
	User(string name, string surname, int age,long id)
	{
		this->name = name;
		this->surname = surname;
		this->age = age;
		this->id = id;
	}
	friend ostream& operator<<(ostream& out, const User& user)
	{
		out << "Имя: " << user.name << "\nФамилия: " << user.surname << "\nВозраст: " << user.age;
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
	User& operator[](const int index)
	{
		if (index < size)
		{
			return this->arr[index];
		}
		else return arr[1];
	}
	void Add(User& tmp)
	{
		User* new_id = new User[this->size + 1];
		for (int i = 0; i < this->size; i++)
		{
			new_id[i] = this->arr[i];
		}
		new_id[size] = tmp;
		delete[] this->arr;
		this->arr = new_id;
		this->size++;
	}
	void load()
	{
		string path = "C:\\Users\\Admin\\source\\repos\\User\\applications\\applications\\file.txt";
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "Список пользователей пуст!\n";
		}
		else
		{
			while (!fin.eof())
			{
				string str;
				string str1;
				int age;
				long id;

				fin >> str >> str1 >> age>>id;
				this->Add(*(new User(str, str1, age,id)));
			}
			//for (int i = 0; i < this->size-1; i++)
			//{
			//	std::cout <<"\n"<< arr[i];
			//}
			cout << "Чтение произведено!\n";
		}
		fin.close();
	}
	void Delete(int pos)
	{
		User* new_id = new User[this->size - 1];
		for (int j = 0; j < pos && j < size; j++)
		{
			new_id[j] = arr[j];
		}
		for (int j = pos + 1; j < size; j++)
		{
			new_id[j - 1] = arr[j];
		}
		size--;
		delete[](arr);
		arr = new_id;
		cout << "Пользователь удалён!\n";
	}
	void RemoveUser()
	{
		string name;
		cin.ignore();
		cout << "Введите имя: ";
		getline(cin, name);
		string surname;
		cout << "Введите фамилию: ";
		getline(cin, surname);
		int age;
		cout << "Введите возраст: ";
		cin >> age;
		int f = 0;
		int pos = -1;
		for (int i = 0; i < this->size; i++)
		{
			if (name == arr[i].getName() && surname == arr[i].getSurname() && age == arr[i].getAge())
			{
				f = 1;
				pos = i;
			}
		}
		if (f == 1)
		{
			this->Delete(pos);
		}
		else
		{
			cout << "Нет пользователя с такими данными!\n";
		}
	}
	void RemoveId()
	{
		long id;
		cout << "Введите айди пользователя, которого хотите удалить: ";
		cin >> id;
		int pos = -1;
		int f = 0;
		for (int i = 0; i < this->size; i++)
		{
			if (id == arr[i].getId())
			{
				pos = i;
				f = 1;
			}
		}
		if (f == 1)
		{
			this->Delete(pos);
		}
		else
		{
			cout << "\nТакого пользователя нет в базе!\n";

		}
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
				fprintf(pf, "%s\t%s\t%i\t%i\n", this->arr[i].getName().c_str(), this->arr[i].getSurname().c_str(), this->arr[i].getAge(), this->arr[i].getId());
			}
			fclose(pf);
			cout << "Информация записана в файл!\n";
		}
		else
		{
			cout << "Error!\n";
		}
	}
	void Print()
	{
		if (this->size != 0)
		{
			for (int i = 0; i < this->size - 1; i++)
			{
				cout << "\n\nИмя: " << arr[i].getName() << "\nФамилия: " << arr[i].getSurname() << "\nВозраст: " << arr[i].getAge() << "\nАйди: " << arr[i].getId() << "\n";
			}
		}
		else
		{
			cout << "Каталог пуст!\n";
		}
	}
	User getbyID()
	{
		long id;
		cout << "Введите айди пользователя: ";
		cin >> id;
		int f = 0;
		for (int i = 0; i < this->size-1; i++)
		{
			if (id == arr[i].getId())
			{
				f = 1;
				return arr[i];
			}
		}
		if (f == 0)
		{
			cout << "Нет пользователя с таким айди!\n";
		}
	}

};
int main()
{
	setlocale(0, "");
	Users users;
	users.load();
	int ch;
	do
	{
		cout << "МЕНЮ:\n";
		cout << "1 - Вывод всего каталога пользователей на экран\n";
		cout << "2 - Удаление по айди\n";
		cout << "3 - Удаление по всем данным пользователя\n";
		cout << "4 - Поиск по айди\n";
		cout << "5 - Сохранение\n";
		cout << "0 - Выход\n";
		cout << "Ваш выбор: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			users.Print();
			cout << "\n";
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			users.RemoveId();
			cout << "\n";
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			users.RemoveUser();
			cout << "\n";
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			cout << users.getbyID();
			cout << "\n";
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			users.Save();
			cout << "\n";
			system("pause");
			system("cls");
			break;
		}
	} while (ch != 0);
	cout << "ВЫ ВЫШЛИ!\n";
}
