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
	// 추가적인 드라이버 타입...
};

enum Car
{
	CAR_1 = 1,
	CAR_2 = 2
	// 추가적인 차 타입...
};

/// <summary>
/// 운전자의 기본 능력
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

		//cout << "기본 방어력 : " << driver.Defance << "\n";
		cout << "\t\t운전자 피지컬 : " << Pysical << "\n";
		cout << "\t\t운전자의 스킬 : " << Skill << "\n";
		cout << "\t\t운전자의 민첩성 : " << Dexterous << "\n";
		cout << "\t\t운전자의 행운 : " << Luck << "\n\n\n";

	}

};

/// <summary>
/// 차의 기본 능력
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
		cout << "\t\t차의 속도 : " << Speed << "\n";
		cout << "\t\t차의 브레이크 성능 : " << Break << "\n";
		cout << "\t\t차의 기본 성능 : " << Performance << "\n";
		cout << "\t\t차의 무게 : " << Weight << "\n";
		cout << "\t\t차의 행운 : " << Luck << "\n\n\n";
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

//방향키를 입력받는 함수
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
		return "운전자 1";
	case DRIVER_2:
		return "운전자 2";
		// 추가적인 직업명...
	default:
		return "Unknown";
	}
}

string getCar(Car carType)
{
	switch (carType)
	{
	case CAR_1:
		return "차 1";
	case CAR_2:
		return "차 2";
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
		return driver;	// 운전자 1 기본 능력치
	case DRIVER_2:
		driver.Status(_driverType);
		return driver;	// 운전자 2 기본 능력치
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
		return car;		// 차 1 능력치
	case CAR_2:
		car.Status(carType);
		return car;		// 차 2 능력치
	default:
		car.Status(carType);
		return car;		// default case
	}
}

void printDriver(vector<int>& job, int row)
{
	system("cls");
	cout << "\n\n\t\t운전자와 차의 조합에 따라 최종 수치가 정해집니다." << "\n\n";

	for (int i = 0; i < job.size(); i++)
	{
		// 직업명을 출력 후 커서를 출력
		cout << "\n\n\t\t" << getDriver(static_cast<Driver>(job[i])) << (i == row ? "\t◀" : "") << endl;
	}
	cout << "\n\n\t\t" << "위 아래 이동읜 방향키 위, 아래(↑, ↓) 이고, 확인 버튼은 오른쪽 방향키(→) 입니다." << "\n\n";
}

void printCar(vector<int>& item, int row)
{
	system("cls");
	cout << "\n\n\t\t운전자와 차의 조합에 따라 최종 수치가 정해집니다." << "\n\n";

	for (int i = 0; i < item.size(); i++)
	{
		// 아이템명을 출력 후 커서를 출력
		cout << "\n\n\t\t" << getCar(static_cast<Car>(item[i])) << (i == row ? "\t◀" : "") << endl;
	}
	cout << "\n\n\t\t" << "위 아래 이동읜 방향키 위, 아래(↑, ↓) 이고, 확인 버튼은 오른쪽 방향키(→) 입니다." << "\n\n";
}

void initializeDriver(vector<int>& drivers)
{
	drivers[0] = DRIVER_1;
	drivers[1] = DRIVER_2;
	// 추가적인 직업 타입이 있다면 여기에 계속해서 추가해주세요.
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

	cout << "\t\t출력 가능한 최고 속도 : " << Speed << "\n";
	cout << "\t\t현재 브레이크 성능 : " << Break << "\n";
	cout << "\t\t현재 내구도 : " << Durability << "\n";
	cout << "\t\t현재 민첩성 : " << Dexterous << "\n";
	cout << "\t\t현재 행운 : " << Luck << "\n";
	cout << "\t\t현재 보너스 행운 : " << luckPoint << "\n\n\n\n";

	cout << "\t\t최고 속도와 브레이크 성능은 행운 수치의 영향을 받습니다." << "\n";
	cout << "\t\t내구도는 차의 파손도에 관여합니다." << "\n";
	cout << "\t\t내구도가 0이 되면 운전이 불가능해집니다." << "\n";
	cout << "\t\t파손량은 내구도 -(현재 주행 속도 / 보너스 행운 점수) 입니다." << "\n";
	cout << "\t\t민첩성은 차의 핸들링에 관여합니다." << "\n\n\n";

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
	cout << "\t\t선택된 운전자: " << getDriver(selectedJobType) << endl;
	cout << "\t\t선택된 차: " << getCar(selectedItemType) << endl;
}

void printResult(DriverStatus driver, CarStatus car, int& luckPoint)
{
	outPut(driver, car);
	Calculate(driver, car, luckPoint);
}
