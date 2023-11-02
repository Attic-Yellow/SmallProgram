#include <iostream>
#include <vector>
#include <conio.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80

using namespace std;

enum PlayerLevel
{
	LEVEL_1 = 3,
	LEVEL_2 = 4,
	LEVEL_3 = 5,
	LEVEL_4 = 6,

};

enum Item
{
	ITEM_0 = 0,
	ITEM_1 = 1,
	ITEM_2 = 2,
	ITEM_3 = 3,
	ITEM_4 = 4

};

string getPlayerChoice(PlayerLevel playerLevel)
{
	switch (playerLevel)
	{
	case LEVEL_1:
		return "\t3 x 3 공간";
	case LEVEL_2:
		return "\t4 x 4 공간";
	case LEVEL_3:
		return "\t5 x 5 공간";
	case LEVEL_4:
		return "\t6 x 6 공간";
	default:
		return "비어있는 공간";
	}
}

string getItemChoice(Item item)
{
	switch (item)
	{
	case ITEM_0:
		return "\t 아이템 0";
	case ITEM_1:
		return "\t 아이템 1";
	case ITEM_2:
		return "\t 아이템 2";
	case ITEM_3:
		return "\t 아이템 3";
	default:
		return "비어있는 공간";
	}
}


void printPlayer(vector<int>& player, int row)
{
	system("cls");

	cout << "\n\n" << "\t 공간 크기 설정" << "\n\n";

	for (int i = 0; i < player.size(); i++)
	{

		cout << getPlayerChoice(static_cast<PlayerLevel>(player[i])) << (i == row ? "\t◀" : "") << "\n\n";
	}
}

void printInven(vector<vector<int>>& inven, int row, int col)
{
	system("cls");

	cout << "\n\n" << "\n\n" << "\t\t|";
	for (int i = 0; i < inven.size(); i++)
	{
		cout << "--------------------------------";
	}
	cout << "|\n";

	for (int i = 0; i < inven.size(); i++)
	{
		cout << "\t\t| ";

		for (int j = 0; j < inven[i].size(); j++)
		{
			cout << "\t" << "  " << getPlayerChoice(static_cast<PlayerLevel>(inven[i][j])) << (i == row && j == col ? " ◀" : "\t") << "\t |";
		}
		cout << "\n" << "\t\t|";
		for (int i = 0; i < inven.size(); i++)
		{
			cout << "--------------------------------";
		}
		cout << "|\n";
	}
}

void initializePlayer(vector<int>& player)
{
	player[0] = LEVEL_1;
	player[1] = LEVEL_2;
	player[2] = LEVEL_3;
	player[3] = LEVEL_4;
}

void initializeInven(vector<vector<int>>& inven)
{
	inven[0][0] = ITEM_1;
	inven[0][1] = ITEM_2;
	inven[0][2] = ITEM_3;
	inven[0][3] = ITEM_4;
}


// 방향키를 입력받는 함수
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

void Puzzle(int& num, int& row, int& col)
{
	vector<vector<int>> inven(num, vector<int>(num));

	for (int i = 0; i < inven.size(); ++i)
	{
		for (int j = 0; j < inven[i].size(); ++j)
		{
			inven[i][j] = 0;
		}
	}

	while (1)
	{
		printInven(inven, row, col);

		cout << "\n\t\t>> 방향키( ←, ↓, ↑, → )를 통하여 조작 하세요!!\n";

		int key = pressKey();

		switch (key)
		{
		case LEFT:
			if (col > 0)
			{
				col--;
			}
			break;

		case RIGHT:
			if (col < inven[row].size() - 1)
			{
				col++;
			}
			break;

		case DOWN:
			if (row < inven.size() - 1)
			{
				row++;
			}

			break;

		case UP:

			if (row > 0)
			{
				row--;
			}

			break;

		default:
			continue;
		}

	}

}

int main()
{

	vector<int> playerChoice(4);

	vector<vector<int>> inven(10, vector<int>(10));

	int num = 0;

	initializePlayer(playerChoice);

	PlayerLevel selectedPlayerType = LEVEL_1;
	Item selectedItem = ITEM_0;

	int row = 0;
	int col = 1;

	while (1)
	{

		string result = "a";
		printPlayer(playerChoice, row);
		int key = pressKey();

		switch (key)
		{
		case DOWN:
			if (row < playerChoice.size() - 1)
			{
				row++;
			}
			else if (row == 3)
			{
				row = 0;
			}
			break;
		case UP:
			if (row > 0)
			{
				row--;
			}
			else if (row == 0)
			{
				row = 3;
			}
			break;
		case RIGHT:

			// 유저가 선택한 레벨을 저장함
			selectedPlayerType = static_cast<PlayerLevel>(playerChoice[row]);

			num = selectedPlayerType;

			row = num - 1;
			col = num - 1;

			Puzzle(num, row, col);

			return EXIT_SUCCESS;
		default:
			continue;
		}
	}


}