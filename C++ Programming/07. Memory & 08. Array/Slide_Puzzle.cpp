﻿// 5x5 판을 생성하고 랜덤한 숫자를 배치한다.
// 시작위치는 상관없으며 ArrowKey입력시 해당 방향으로 이동한다.
// 단, 밖으로 벗어날 수 없다.
// 아래 예시는 ★이 움직이는 것으로 가정한다


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

string getPlayerChoice(PlayerLevel playerLevel)
{
	switch (playerLevel)
	{
	case LEVEL_1:
		return "\t3 x 3 퍼즐 : 레벨1";
	case LEVEL_2:
		return "\t4 x 4 퍼즐 : 레벨2";
	case LEVEL_3:
		return "\t5 x 5 퍼즐 : 레벨3";
	case LEVEL_4:
		return "\t6 x 6 퍼즐 : 레벨4";
	default:
		return "Unknown";
	}
}

/// <summary>
/// 레벨 선택창을 출력하는 함수
/// </summary>
/// <param name="player"> 유저가 선택하는 레벨 </param>
/// <param name="row"> 커서의 위치 </param>
void printPlayer(vector<int>& player, int row)
{
	system("cls");

	cout << "\n\n" << "\t슬라이드 퍼즐!!" << "\n\n";

	for (int i = 0; i < player.size(); i++)
	{

		cout << getPlayerChoice(static_cast<PlayerLevel>(player[i])) << (i == row ? "\t◀" : "") << "\n\n";
	}
}

/// <summary>
/// 레벨을 저장하는 함수
/// </summary>
/// <param name="player"> 레벨 </param>
void initializePlayer(vector<int>& player)
{
	player[0] = LEVEL_1;
	player[1] = LEVEL_2;
	player[2] = LEVEL_3;
	player[3] = LEVEL_4;
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

/// <summary>
/// 퍼즐을 출력하는 함수
/// </summary>
/// <param name="puzzleNum"> 퍼즐의 번호 </param>
void printPuzzle(vector<vector<int>>& puzzleNum)
{
	system("cls");

	cout << "\n\n" << "\n\n";

	for (int i = 0; i < puzzleNum.size(); i++)
	{
		for (int j = 0; j < puzzleNum[i].size(); j++)
		{
			if (puzzleNum[i][j])
			{
				cout << "\t\t" << puzzleNum[i][j] << "\t";
			}
			else
			{
				cout << "\t\t" << "★" << "\t";
			}

			if (j == puzzleNum[i].size() - 1)
			{
				cout << "\n\n\n";
			}
		}


	}
}

/// <summary>
/// 클리어를 확인하는 함수
/// </summary>
/// <param name="puzzleNum"> 퍼즐 번호 </param>
/// <returns> 번호의 순서가 맞지 않을 시 false 반환, 번호의 숫자가 맞을 시 true를 반환 </returns>
bool isEnding(const vector<vector<int>>& puzzleNum)
{
	int count = 1;

	for (int i = 0; i < puzzleNum.size(); ++i)
	{
		for (int j = 0; j < puzzleNum[0].size(); ++j)
		{
			if (puzzleNum[i][j] != count++ % (puzzleNum.size() * puzzleNum[0].size()))
			{
				return false;
			}
		}
	}

	return true;
}

/// <summary>
/// 퍼즐을 섞는 함수
/// </summary>
/// <param name="puzzleNum"> 퍼즐 번호 </param>
/// <param name="num"> 유저가 선택한 레벨 </param>
void shuffle(vector<vector<int>>& puzzleNum, int num)
{
	for (int i = 0; i < 100; i++)
	{
		int dest1 = rand() % num;
		int dest2 = rand() % num;
		int sour1 = rand() % num;
		int sour2 = rand() % num;

		int temp = puzzleNum[dest1][sour1];
		puzzleNum[dest1][sour1] = puzzleNum[dest1][sour2];
		puzzleNum[dest1][sour2] = puzzleNum[dest2][sour1];
		puzzleNum[dest2][sour1] = puzzleNum[dest2][sour2];
		puzzleNum[dest2][sour2] = temp;

	}

	int rememberA, rememberB;

	if (puzzleNum[num / 2][num / 2] != 0)
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (puzzleNum[i][j] == 0)
				{
					rememberA = i;
					rememberB = j;
					int temp = puzzleNum[num / 2][num / 2];
					puzzleNum[num / 2][num / 2] = puzzleNum[i][j];
					puzzleNum[i][j] = temp;
				}
			}
		}
	}
}

/// <summary>
/// 게임을 진행하는 함수
/// </summary>
/// <param name="num"> 유저가 선택한 레벨 </param>
/// <param name="row"> 세로 값 </param>
/// <param name="col"> 가로 값 </param>
void Puzzle(int& num, int& row, int& col)
{
	vector<vector<int>> puzzleNum(num, vector<int>(num));

	for (int i = 0; i < puzzleNum.size(); ++i)
	{
		for (int j = 0; j < puzzleNum[i].size(); ++j)
		{
			puzzleNum[i][j] = i * puzzleNum.size() + j + 1;
		}
	}

	puzzleNum[puzzleNum.size() - 1][puzzleNum[0].size() - 1] = 0;

	shuffle(puzzleNum, num);

	while (!isEnding(puzzleNum))
	{
		printPuzzle(puzzleNum);

		cout << "\n\t\t>> 방향키( ←, ↓, ↑, → )를 통하여 플레이 하세요!!\n";

		int key = pressKey();

		switch (key)
		{
		case LEFT:
			if (col > 0)
			{
				swap(puzzleNum[row][col], puzzleNum[row][col - 1]);
				col--;
			}
			break;

		case RIGHT:
			if (col < puzzleNum[row].size() - 1)
			{
				swap(puzzleNum[row][col], puzzleNum[row][col + 1]);
				col++;
			}
			break;

		case DOWN:
			if (row < puzzleNum.size() - 1)
			{
				swap(puzzleNum[row][col], puzzleNum[row + 1][col]);
				row++;
			}

			break;

		case UP:

			if (row > 0)
			{
				swap(puzzleNum[row][col], puzzleNum[row - 1][col]);
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
	//난수 생성기 초기화
	srand((unsigned int)time(NULL));

	vector<int> playerChoice(4);

	vector<vector<int>> puzzleNum(10, vector<int>(10));

	int num = 0;

	initializePlayer(playerChoice);

	PlayerLevel selectedPlayerType = LEVEL_1;

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

			row = num / 2;
			col = num / 2;

			Puzzle(num, row, col);

			system("cls");

			cout << "\n\n\t\t축하합니다! 게임을 클리어 하셨습니다!\n";

			return EXIT_SUCCESS;
		default:
			continue;
		}
	}


}