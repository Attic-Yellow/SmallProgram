#include <iostream>
#include <vector>
#include <conio.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80
#define ENTER	13

using namespace std;

enum Driver
{
	DRIVER_1 = 1,
	DRIVER_2 = 2
	// �߰����� ����̹� Ÿ��...
};

enum Car
{
	CAR_1 = 1,
	CAR_2 = 2
	// �߰����� �� Ÿ��...
};

/// <summary>
/// �������� �⺻ �ɷ�
/// </summary>
class DriverStatus
{
	Driver driverType;
	int Pysical;
	int Dexterous;
	int Skill;
	int Luck;

public:

	int getPysical()
	{
		return Pysical;
	}
	int getDexterous()
	{
		return Dexterous;
	}
	int getSkill()
	{
		return Skill;
	}
	int getLuck()
	{
		return Luck;
	}

	void Status(Driver _driverType)
	{
		if (_driverType == DRIVER_1)
		{
			driverType = DRIVER_1;
			Pysical = 100;
			Dexterous = 80;
			Skill = 95;
			Luck = 18;
		}
		else if (_driverType == DRIVER_2)
		{
			driverType = DRIVER_2;
			Pysical = 80;
			Dexterous = 100;
			Skill = 75;
			Luck = 23;
		}
		else
		{
			driverType = DRIVER_1;
			Pysical = 100;
			Dexterous = 80;
			Skill = 95;
			Luck = 18;
		}
	}

	void PrintDriver()
	{
		cout << "\n\n";

		//cout << "�⺻ ���� : " << driver.Defance << "\n";
		cout << "\t\t������ ������ : " << Pysical << "\n";
		cout << "\t\t�������� ��ų : " << Skill << "\n";
		cout << "\t\t�������� ��ø�� : " << Dexterous << "\n";
		cout << "\t\t�������� ��� : " << Luck << "\n\n\n";

	}

};

/// <summary>
/// ���� �⺻ �ɷ�
/// </summary>
class CarStatus
{
	Car carType;
	int Speed;
	int Break;
	int Performance;
	int Weight;
	int Luck;

public:

	int getSpeed()
	{
		return Speed;
	}
	int getBreak()
	{
		return Break;
	}
	int getPerformance()
	{
		return Performance;
	}
	int getWeight()
	{
		return Weight;
	}
	int getLuck()
	{
		return Luck;
	}

	void Status(Car _car)
	{
		if (_car == CAR_1)
		{
			carType = CAR_1;
			Speed = 100;
			Break = 80;
			Performance = 95;
			Weight = 2000;
			Luck = 7;
		}
		else if (_car == CAR_2)
		{
			carType = CAR_2;
			Speed = 110;
			Break = 70;
			Performance = 75;
			Weight = 1800;
			Luck = 5;
		}
		else
		{
			carType = CAR_1;
			Speed = 100;
			Break = 80;
			Performance = 95;
			Weight = 200;
			Luck = 7;
		}
	}

	void PrintCar()
	{
		cout << "\t\t���� �ӵ� : " << Speed << "\n";
		cout << "\t\t���� �극��ũ ���� : " << Break << "\n";
		cout << "\t\t���� �⺻ ���� : " << Performance << "\n";
		cout << "\t\t���� ���� : " << Weight << "\n";
		cout << "\t\t���� ��� : " << Luck << "\n\n\n";
	}

};

string getDriver(Driver driverType);
string getCar(Car carType);
DriverStatus getDriverStatus(Driver driverType);
CarStatus getCarStatus(Car carType);

int pressKey();
void printDriver(vector<int>& job, int row);
void printCar(vector<int>& item, int row);
void initializeDriver(vector<int>& drivers);
void initializeCar(vector<int>& car);
void outPut(DriverStatus driver, CarStatus car);
void Calculate(DriverStatus driver, CarStatus car, int& luckPoint);
Driver chooseDriver(vector<int>& driver, int& row);
Car chooseCar(vector<int>& car, int& row);
void printSelected(Driver selectedJobType, Car selectedItemType);
void printResult(DriverStatus driver, CarStatus car, int& luckPoint);

int main()
{

	vector<int> driver(2);
	vector<int> car(2);

	srand((unsigned int)time(NULL));
	int luckPoint = (rand() % 4) + 1;

	initializeDriver(driver);
	initializeCar(car);

	int row = 0;
	Driver selectedJobType = chooseDriver(driver, row);
	Car selectedItemType = chooseCar(car, row);

	printSelected(selectedJobType, selectedItemType);

	DriverStatus selectedDriverStatus = getDriverStatus(selectedJobType);
	CarStatus selectedCarStatus = getCarStatus(selectedItemType);

	printResult(selectedDriverStatus, selectedCarStatus, luckPoint);

	return EXIT_SUCCESS;
}

//����Ű�� �Է¹޴� �Լ�
int pressKey()
{
	int key;
	key = _getch();

	if (key == 224)
	{
		return _getch();
	}

	return 0;
}

string getDriver(Driver driverType)
{
	switch (driverType)
	{
	case DRIVER_1:
		return "������ 1";
	case DRIVER_2:
		return "������ 2";
		// �߰����� ������...
	default:
		return "Unknown";
	}
}

string getCar(Car carType)
{
	switch (carType)
	{
	case CAR_1:
		return "�� 1";
	case CAR_2:
		return "�� 2";
	default:
		return "Unknown";
	}
}

DriverStatus getDriverStatus(Driver _driverType)
{
	DriverStatus driver;

	switch (_driverType)
	{
	case DRIVER_1:
		driver.Status(_driverType);
		return driver;	// ������ 1 �⺻ �ɷ�ġ
	case DRIVER_2:
		driver.Status(_driverType);
		return driver;	// ������ 2 �⺻ �ɷ�ġ
	default:
		driver.Status(_driverType);
		return driver;	// default case
	}
}


CarStatus getCarStatus(Car carType)
{
	CarStatus car;

	switch (carType)
	{
	case CAR_1:
		car.Status(carType);
		return car;		// �� 1 �ɷ�ġ
	case CAR_2:
		car.Status(carType);
		return car;		// �� 2 �ɷ�ġ
	default:
		car.Status(carType);
		return car;		// default case
	}
}

void printDriver(vector<int>& job, int row)
{
	system("cls");
	cout << "\n\n\t\t�����ڿ� ���� ���տ� ���� ���� ��ġ�� �������ϴ�." << "\n\n";

	for (int i = 0; i < job.size(); i++)
	{
		// �������� ��� �� Ŀ���� ���
		cout << "\n\n\t\t" << getDriver(static_cast<Driver>(job[i])) << (i == row ? "\t��" : "") << endl;
	}
	cout << "\n\n\t\t" << "�� �Ʒ� �̵��� ����Ű ��, �Ʒ�(��, ��) �̰�, Ȯ�� ��ư�� ������ ����Ű(��) �Դϴ�." << "\n\n";
}

void printCar(vector<int>& item, int row)
{
	system("cls");
	cout << "\n\n\t\t�����ڿ� ���� ���տ� ���� ���� ��ġ�� �������ϴ�." << "\n\n";

	for (int i = 0; i < item.size(); i++)
	{
		// �����۸��� ��� �� Ŀ���� ���
		cout << "\n\n\t\t" << getCar(static_cast<Car>(item[i])) << (i == row ? "\t��" : "") << endl;
	}
	cout << "\n\n\t\t" << "�� �Ʒ� �̵��� ����Ű ��, �Ʒ�(��, ��) �̰�, Ȯ�� ��ư�� ������ ����Ű(��) �Դϴ�." << "\n\n";
}

void initializeDriver(vector<int>& drivers)
{
	drivers[0] = DRIVER_1;
	drivers[1] = DRIVER_2;
	// �߰����� ���� Ÿ���� �ִٸ� ���⿡ ����ؼ� �߰����ּ���.
}

void initializeCar(vector<int>& car)
{
	car[0] = CAR_1;
	car[1] = CAR_2;
}

void outPut(DriverStatus driver, CarStatus car)
{
	driver.PrintDriver();
	car.PrintCar();
}


void Calculate(DriverStatus driver, CarStatus car, int& luckPoint)
{

	int Speed = ((driver.getPysical() + car.getPerformance()) + ((car.getWeight() >> 2) / (driver.getLuck() + car.getLuck()) * luckPoint));
	int Break = ((driver.getDexterous() + car.getBreak()) + ((car.getWeight() >> 2) / (driver.getLuck() + car.getLuck()) * luckPoint));
	int Durability = (car.getWeight() * driver.getSkill()) >> 8;
	int Dexterous = ((car.getWeight() >> 1) - (driver.getDexterous() << 3)) >> 1;
	int Luck = driver.getLuck() + car.getLuck();

	cout << "\t\t��� ������ �ְ� �ӵ� : " << Speed << "\n";
	cout << "\t\t���� �극��ũ ���� : " << Break << "\n";
	cout << "\t\t���� ������ : " << Durability << "\n";
	cout << "\t\t���� ��ø�� : " << Dexterous << "\n";
	cout << "\t\t���� ��� : " << Luck << "\n";
	cout << "\t\t���� ���ʽ� ��� : " << luckPoint << "\n\n\n\n";

	cout << "\t\t�ְ� �ӵ��� �극��ũ ������ ��� ��ġ�� ������ �޽��ϴ�." << "\n";
	cout << "\t\t�������� ���� �ļյ��� �����մϴ�." << "\n";
	cout << "\t\t�������� 0�� �Ǹ� ������ �Ұ��������ϴ�." << "\n";
	cout << "\t\t�ļշ��� ������ -(���� ���� �ӵ� / ���ʽ� ��� ����) �Դϴ�." << "\n";
	cout << "\t\t��ø���� ���� �ڵ鸵�� �����մϴ�." << "\n\n\n";

}

Driver chooseDriver(vector<int>& driver, int& row)
{
	while (true)
	{
		printDriver(driver, row);
		int key = pressKey();

		switch (key)
		{
		case DOWN:
			if (row < driver.size() - 1) row++;
			break;
		case UP:
			if (row > 0) row--;
			break;
		case RIGHT:
			return static_cast<Driver>(driver[row]);
		default:
			continue;
		}
	}
}

Car chooseCar(vector<int>& car, int& row)
{
	while (true)
	{
		printCar(car, row);
		int key = pressKey();

		switch (key)
		{
		case DOWN:
			if (row < car.size() - 1) row++;
			break;
		case UP:
			if (row > 0) row--;
			break;
		case RIGHT:
			return static_cast<Car>(car[row]);
		default:
			continue;
		}
	}
}

void printSelected(Driver selectedJobType, Car selectedItemType)
{
	system("cls");
	cout << "\n\n";
	cout << "\t\t���õ� ������: " << getDriver(selectedJobType) << endl;
	cout << "\t\t���õ� ��: " << getCar(selectedItemType) << endl;
}

void printResult(DriverStatus driver, CarStatus car, int& luckPoint)
{
	outPut(driver, car);
	Calculate(driver, car, luckPoint);
}
