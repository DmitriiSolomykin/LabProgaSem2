#include <iostream>
#include <string>

using namespace std;

class Driver {
private:
	string fullName;
	int driverExp;
public:
	Driver(string fullName, int driverExp) : fullName(fullName), driverExp(driverExp) {}

	string getFullName() const {
		return fullName;
	}

	int getDriverExp() {
		return driverExp;
	}

	void setFullName(const string& fullName) {
		this->fullName = fullName;
	}

	void setDriverExp(int driverExp) {
		this->driverExp = driverExp;
	}

	string toString() const {
		return "Водитель: " + this->fullName + ".\nСтаж вождения: " + to_string(this->driverExp);
	}
};

class Engine {
private:
	int power;
	string host;
public:
	Engine(int power, string host) : power(power), host(host) {}

	int getPower() const {
		return this->power;
	}

	string getHost() const {
		return this->host;
	}

	void setPower(int power) {
		this->power = power;
	}

	void setHost(const string& host) {
		this->host = host;
	}

	string toString() {
		return "Мощность: " + to_string(this->power) + " л.с." + "\nПроизводитель: " + this->host;
	}
};

class Car {
private:
	string brand;
	string classCar;
	int weight;
	Driver* driver;
	Engine* engine;
public:
	Car(string brand, string classCar, int weight, Driver* driver, Engine* engine) : brand(brand), 
	classCar(classCar), weight(weight), driver(driver), engine(engine){}

	~Car() {
		delete this->driver;
		delete this->engine;
	}

	string getBrand() const {
		return this->brand;
	}

	string getClassCar() const {
		return this->classCar;
	}

	int getWeight() const {
		return this->weight;
	}

	void setBrand(const string& brand) {
		this->brand = brand;
	}

	void setClassCar(const string& classCar) {
		this->classCar = classCar;
	}

	void setWeight(int weight) {
		this->weight = weight;
	}

	void setDriver(Driver* driver) {
		if (this->driver != nullptr) {
			delete this->driver;
		}
		this->driver = driver;
	}

	void setEngine(Engine* engine) {
		if (this->engine != nullptr) {
			delete this->engine;
		}
		this->engine = engine;
	}

	void start() {
		cout << "Поехали\n";
	}

	void stop() {
		cout << "Останавливаемся\n";
	}

	void turnRight() {
		cout << "Поворот направо\n";
	}

	void turnLeft() {
		cout << "Поворот налево\n";
	}

	string toString() const {
		string driverStr = (this->driver != nullptr) ? this->driver->toString() : "Водитель не указан.";
		string engineStr = (this->engine != nullptr) ? this->engine->toString() : "Двигатель не указан.";

		return "Марка: " + this->brand + "\n" +
			"Класс: " + this->classCar + "\n" +
			"Вес: " + to_string(this->weight) + " кг" + "\n" +
			driverStr + "\n" + engineStr;
	}
};

class Lorry : public Car {
private:
	int tonnage;
public:
	Lorry(string brand, string classCar, int weight, Driver* driver, Engine* engine, int tonnage) : 
		Car(brand, classCar, weight, driver, engine), tonnage(tonnage){}

	int getTonnage() const {
		return this->tonnage;
	}

	void setTonnage(int tonnage) {
		this->tonnage = tonnage;
	}

	string toString() const {
		return Car::toString() + "\nГрузоподъемность: " + to_string(this->tonnage) + " кг";
	}
};

class SportCar : public Car {
private:
	int maxSpeed;
public:
	SportCar(string brand, string classCar, int weight, Driver* driver, Engine* engine, int maxSpeed) : 
		Car(brand, classCar, weight, driver, engine), maxSpeed(maxSpeed) {}

	int getMaxSpeed() const {
		return this->maxSpeed;
	}

	void setMaxSpeed(int maxSpeed) {
		this->maxSpeed = maxSpeed;
	}

	string toString() const {
		return Car::toString() + "\nМаксимальна скорость: " + to_string(this->maxSpeed) + " км/ч";
	}
};

const int MAX_CARS = 10;

int main() {
	setlocale(LC_ALL, "ru");
	system("chcp 1251 > text");

	Car* cars[MAX_CARS];
	int numCars = 0;

	bool progRun = true;

	while (progRun) {
		cout << "\nМеню: \n";
		cout << "1. Добавить автомобиль.\n";
		cout << "2. Удалить автомобиль.\n";
		cout << "3. Управление автомобилем.\n";
		cout << "4. Показать список автомобилей.\n";
		cout << "5. Закрыть программу.\n";
		cout << "Выберите действие: ";

		int choice;
		cin >> choice;

		if (cin.fail()) {
			cout << "Некорректный ввод.\n";
			cin.clear();
			cin.ignore();
			continue;
		}
		cin.ignore();

		switch (choice) {
		case 1: {
			if (numCars >= MAX_CARS) {
				cout << "Достигнуто максимальное число автомобилей.\n";
				break;
			}
			string type;
			cout << "Выберите тип автомобиля - Car/Lorry/SportCar: ";
			getline(cin, type);

			string brand, classCar, driverName, engineHost;
			int weight, driverExp, enginePower, tonnage, maxSpeed;

			cout << "Марка: ";
			getline(cin, brand);

			cout << "Класс: ";
			getline(cin, classCar);

			while (true) {
				cout << "Вес: ";
				cin >> weight;

				if (cin.fail() || weight <= 0) {
					cout << "Некорректный ввод.\n";
					cin.clear();
					cin.ignore();
				}
				else {
					cin.ignore();
					break;
				}
			}
			cout << "ФИО водителя: ";
			getline(cin, driverName);

			while (true) {
				cout << "Стаж: ";
				cin >> driverExp;
				if (cin.fail() || driverExp < 0) {
					cout << "Некорректный ввод.\n";
					cin.clear();
					cin.ignore();
				}
				else {
					cin.ignore();
					break;
				}
			}

			cout << "Производитель двигателя: ";
			getline(cin, engineHost);

			while (true) {
				cout << "Мощность: ";
				cin >> enginePower;

				if (cin.fail() || enginePower <= 0) {
					cout << "Некорректный ввод.\n";
					cin.clear();
					cin.ignore();
				}
				else {
					cin.ignore();
					break;
				}
			}

			Driver* driver = new Driver(driverName, driverExp);
			Engine* engine = new Engine(enginePower, engineHost);

			if (type == "Car") {
				cars[numCars] = new Car(brand, classCar, weight, driver, engine);
			}
			else if (type == "Lorry") {
				while (true) {
					cout << "Грузоподъемность: ";
					cin >> tonnage;

					if (cin.fail() || tonnage <= 0) {
						cout << "Неккоректный ввод.\n";
						cin.clear();
						cin.ignore();
					}
					else {
						cin.ignore();
						break;
					}
				}
				cars[numCars] = new Lorry(brand, classCar, weight, driver, engine, tonnage);
			}
			else if (type == "SportCar") {
				while (true) {
					cout << "Максимальная скорость: ";
					cin >> maxSpeed;

					if (cin.fail() || maxSpeed <= 0) {
						cout << "Некорректный ввод.\n";
						cin.clear();
						cin.ignore();
					}
					else {
						cin.ignore();
						break;
					}
				}
				cars[numCars] = new SportCar(brand, classCar, weight, driver, engine, maxSpeed);
			}
			else {
				cout << "Неверный тип автомобиля.\n";
				delete driver;
				delete engine;
				break;
			}
			numCars++;
			break;
		}
		case 2: {
			if (numCars == 0) {
				cout << "Список автомобилей пуст.\n";
				break;
			}

			int delChoice;
			cout << "Введите номер в списке, который хотите удалить: ";
			cin >> delChoice;

			if (cin.fail() || delChoice <= 0 || delChoice > numCars) {
				cout << "Некорректный ввод.\n";
				cin.clear();
				cin.ignore();
				break;
			}
			cin.ignore();
			delete cars[delChoice - 1];
			cars[delChoice - 1] = nullptr;

			for (int i = delChoice - 1; i < numCars; i++) {
				cars[i] = cars[i + 1];
			}

			numCars--;
			cout << "Автомобиль удален.\n";
			break;
		}
		case 3: {
			if (numCars == 0) {
				cout << "Список автомобилей пуст, сначала добавьте автомобили.";
				break;
			}

			cout << "\nСписок доступных автомобилей:\n";
			for (int i = 0; i < numCars; i++) {
				if (cars[i] != nullptr) {
					cout << "Автомобиль номер " << i + 1 << ":\n";
					cout << cars[i]->toString() << endl;
				}
			}

			int carChoice;
			cout << "Выберите номер автомобиля: ";
			cin >> carChoice;

			if (cin.fail() || carChoice <= 0 || carChoice > numCars) {
				cout << "Некорректный ввод.\n";
				cin.clear();
				cin.ignore();
				break;
			}
			if (cars[carChoice] - 1 != nullptr) {
				bool runn = true;
				while (runn) {
					cout << "\nУправление автомобилем\n";
					cout << "1. Газ\n";
					cout << "2. Тормоз\n";
					cout << "3. Налево\n";
					cout << "4. Направо\n";
					cout << "0. Выйти\n";
					cout << "Выберите вариант: ";
					
					int x;
					cin >> x;
					if (cin.fail()) {
						cout << "Некорректный ввод.\n";
						cin.clear();
						cin.ignore();
						continue;
					}
					cin.ignore();
					switch (x) {
					case 1:
						cars[carChoice - 1]->start();
						break;
					case 2:
						cars[carChoice - 1]->stop();
						break;
					case 3:
						cars[carChoice - 1]->turnLeft();
						break;
					case 4:
						cars[carChoice - 1]->turnRight();
						break;
					case 0:
						runn = false;
						break;
					default:
						cout << "Неверный выбор, попробуйте еще раз.\n";
					}
				}
			}
			else {
				cout << "Автомобиль с таким номером не существует.\n";
			}
			break;

		}
		case 4: {
			if (numCars == 0) {
				cout << "Список автомобилей пуст.\n";
			}
			else {
				cout << "\nСписок автомобилей:\n";
				for (int i = 0; i < numCars; i++) {
					if (cars[i] != nullptr) {
						cout << "Автомобиль номер " << i + 1 << ":\n";
						cout << cars[i]->toString() << endl;
					}
					else {
						cout << i + 1 << ". (Удален)\n";
					}
				}

			}
			break;
		}
		case 5:
			progRun = false;
			break;
		default:
			cout << "Неверный выбор, попробуйте еще раз.\n";
		}
	}

	for (int i = 0; i < numCars; ++i) {
		if (cars[i] != nullptr) {
			delete cars[i];
		}
	}

	return 0;
}