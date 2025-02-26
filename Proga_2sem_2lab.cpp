#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Student {
	string Name;
	string Surname;
	string Patronymic;
	unsigned int Score;
};

const int maxRecords = 100;
Student records[maxRecords];
int recordsCount = 0;

void displayMenu();
void readFromFile(const string&, bool isBinary);
void writeToFile(const string&, bool isBinary);
void readFromKeyboard();
void displayData();
void avgScore();
void addStudent();
void deleteStudent();
void handleFileError(const string&);

int main() {
	setlocale(LC_ALL, "ru");
	system("chcp 1251 > text");

	int choice;
	do {
		displayMenu();
		cin >> choice;
		switch (choice) {
		case 1: {
			int inputChoice;
			cout << "Выберите метод ввода:\n1. Текстовый файл\n2. Бинарный файл\n3. С клавиатуры\n";
			cin >> inputChoice;
			if (inputChoice == 1) {
				readFromFile("data.txt", false);
			}
			else if (inputChoice == 2) {
				readFromFile("data.bin", true);
			}
			else if (inputChoice == 3) {
				readFromKeyboard();
			}
			else {
				cerr << "Ошибка.\n";
			}
			break;
		}
		case 2:
			displayData();
			break;
		case 3:
			avgScore();
			break;
		case 4:
			addStudent();
			break;
		case 5:
			deleteStudent();
			break;
		case 6: {
			int outputChoice;
			cout << "Выберите метод вывода:\n1. Текстовый файл\n2. Бинарный файл\n";
			cin >> outputChoice;
			if (outputChoice == 1) {
				writeToFile("data.txt", false);
			}
			else if (outputChoice == 2) {
				writeToFile("data.bin", true);
			}
			else {
				cerr << "Ошибка.\n";
			}
			break;
		}
		case 7:
			cout << "Выход из программы.\n";
			break;
		default:
			cerr << "Ошибка, попробуйте снова.\n";
		}
	} while (choice != 7);
	return 0;
}

void displayMenu() {
	cout << "Меню: \n";
	cout << "1. Ввод данных.\n";
	cout << "2. Отображение данных.\n";
	cout << "3. Расчёт и вывод итоговых значений\n";
	cout << "4. Добавление записи.\n";
	cout << "5. Удаление записи.\n";
	cout << "6. Сохранить данные.\n";
	cout << "7. Выход из программы.\n";
	cout << "Введите свой вариант: ";
}

void readFromFile(const string& filename, bool isBinary) {
	ifstream file;
	if (isBinary) {
		file.open(filename, ios::binary);
	}
	else {
		file.open(filename);
	}
	if (!file) {
		handleFileError(filename);
		return;
	}
	recordsCount = 0;
	while (file && recordsCount < maxRecords) {
		if (isBinary) {
			file.read(reinterpret_cast<char*>(&records[recordsCount]), sizeof(Student));
		}
		else {
			file >> records[recordsCount].Surname >> records[recordsCount].Name >> records[recordsCount].Patronymic >> records[recordsCount].Score;
		}
		if (file) {
			++recordsCount;
		}
	}
}

void writeToFile(const string& filename, bool isBinary) {
	ofstream file;
	if (isBinary) {
		file.open(filename, ios::binary);
	}
	else {
		file.open(filename);
	}
	if (!file) {
		handleFileError(filename);
		return;
	}
	for (int i = 0; i < recordsCount; ++i) {
		if (isBinary) {
			file.write(reinterpret_cast<const char*>(&records[i]), sizeof(Student));
		}
		else {
			file << records[i].Surname << ' ' << records[i].Name << ' ' << records[i].Patronymic << ' ' << records[i].Score << '\n';
		}
	}
	file.close();
}

void readFromKeyboard() {
	cout << "Введите количество записей: ";
	cin >> recordsCount;
	if (recordsCount > maxRecords) {
		cerr << "Превышение максимального лимита записей.\n";
		recordsCount = maxRecords;
	}
	for (int i = 0; i < recordsCount; ++i) {
		std::cout << "Введите ФИО и балл: ";
		std::cin >> records[i].Surname >> records[i].Name >> records[i].Patronymic >> records[i].Score;
	}
}

void displayData() {
	cout << setw(5) << "No" << setw(20) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Балл" << '\n';
	for (int i = 0; i < recordsCount; ++i) {
		cout << setw(5) << i + 1 << setw(20) << records[i].Surname << setw(15) << records[i].Name << setw(15) << records[i].Patronymic << setw(15) << records[i].Score << '\n';
	}
}

void avgScore() {
	if (recordsCount == 0) {
		cerr << "Записи не найдены.";
		return;
	}
	float avg = 0;
	int sum = 0;
	for (int i = 0; i < recordsCount; i++) {
		sum += records[i].Score;
	}
	avg = sum / recordsCount;
	cout << "Средний балл среди студентов: " << avg << "\n";
}

void addStudent() {
	if (recordsCount >= maxRecords) {
		cerr << "Невозможно добавить запись, будет превышен лимит.\n";
		return;
	}
	cout << "Введите ФИО и балл: ";
	cin >> records[recordsCount].Surname >> records[recordsCount].Name >> records[recordsCount].Patronymic >> records[recordsCount].Score;
	++recordsCount;
}

void deleteStudent() {
	int recordNum;
	std::cout << "Введите номер записи, которую хотите удалить: ";
	std::cin >> recordNum;
	if (recordNum < 1 || recordNum > recordsCount) {
		cerr << "Неверный номер записи.\n";
		return;
	}
	for (int i = recordNum - 1; i < recordsCount - 1; ++i) {
		records[i] = records[i + 1];
	}
	--recordsCount;
}

void handleFileError(const string& filename) {
	cerr << "Ошибка открытия файла: " << filename << '\n';
}