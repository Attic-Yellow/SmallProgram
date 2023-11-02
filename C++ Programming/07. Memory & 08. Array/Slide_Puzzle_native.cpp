﻿// 

#include <iostream>
#include <vector>
#include <conio.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80

using namespace std;

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

void printPuzzle(vector<vector<int>>& puzzleNum)
{
	system("cls");

	for (int i = 0; i < puzzleNum.size(); i++)
	{
		for (int j = 0; j < puzzleNum[i].size(); j++)
		{
			if (puzzleNum[i][j])
			{
				cout << puzzleNum[i][j] << "\t";
			}
			else
			{
				cout << "★" << "\t";
			}

			if (j == puzzleNum[i].size() - 1)
			{
				cout << "\n";
			}
		}


	}
}

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

void shuffle(vector<vector<int>>& puzzleNum)
{
	for (int i = 0; i < 100; i++)
	{
		int dest1 = rand() % 5;
		int dest2 = rand() % 5;
		int sour1 = rand() % 5;
		int sour2 = rand() % 5;

		int temp = puzzleNum[dest1][sour1];
		puzzleNum[dest1][sour1] = puzzleNum[dest1][sour2];
		puzzleNum[dest1][sour2] = puzzleNum[dest2][sour1];
		puzzleNum[dest2][sour1] = puzzleNum[dest2][sour2];
		puzzleNum[dest2][sour2] = temp;

	}

	int rememberA, rememberB;

	if (puzzleNum[4][4] != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (puzzleNum[i][j] == 0)
				{
					rememberA = i;
					rememberB = j;
					int temp = puzzleNum[4][4];
					puzzleNum[4][4] = puzzleNum[i][j];
					puzzleNum[i][j] = temp;
				}
			}
		}
	}
}

int main()
{
	//난수 생성기 초기화
	srand((unsigned int)time(NULL));

	vector<vector<int>> puzzleNum(5, vector<int>(5));

	int row = 4;
	int col = 4;

	for (int i = 0; i < puzzleNum.size(); ++i)
	{
		for (int j = 0; j < puzzleNum[i].size(); ++j)
		{
			puzzleNum[i][j] = i * puzzleNum.size() + j + 1;
		}
	}

	puzzleNum[puzzleNum.size() - 1][puzzleNum[0].size() - 1] = 0;

	shuffle(puzzleNum);

	while (!isEnding(puzzleNum))
	{
		printPuzzle(puzzleNum);
		cout << ">> 방향키 선택\n";

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

	cout << "축하합니다! 게임을 클리어 하셨습니다!\n";

	return EXIT_SUCCESS;
}