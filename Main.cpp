#include <iostream>
#include <random>
#include <chrono>


using namespace std;

inline void ClearScr()
{
	system("cls");
};

enum Cell : char {
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'

};

enum Progress : uint8_t {
	IN_PROGRESS,
	WON_AI,
	WON_HUMAN,
	DRAW
};

struct Coord {
	size_t y{ 0 };
	size_t x{ 0 };
};

#pragma pack(push, 1)
struct Game {
	Cell** ppField = nullptr;
	const size_t SIZE = 3;
	size_t turn = 0;
	Cell human = CROSS;
	Cell ai = ZERO;
	Progress progress = IN_PROGRESS;
};
#pragma pack(pop)

int32_t getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
};
void _fastcall initGame(Game& g)
{
	g.ppField = new Cell * [g.SIZE];
	for (size_t i = 0; i < g.SIZE; i++)
	{
		g.ppField[i] = new Cell[g.SIZE];
	};
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.ppField[y][x] = EMPTY;
		};
	};
	if (getRandomNum(0, 1000) > 500)
	{
		g.human = CROSS;
		g.ai = ZERO;
		g.turn = 0;
	}
	else
	{
		g.human = ZERO;
		g.ai = CROSS;
		g.turn = 1;
	};

};

void _fastcall deinitGame(Game& g)
{
	for (size_t i = 0; i < g.SIZE; i++)
	{
		delete[] g.ppField[i];
	}
	delete[] g.ppField;
	g.ppField = nullptr;
};

void PrintGame(const Game& g)
{
	cout << "    ";
	for (size_t x = 0; x < g.SIZE; x++)
		cout << x + 1 << "   ";
	cout << endl;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		cout << y + 1 << " | ";
		for (size_t x = 0; x < g.SIZE; x++)
		{
			cout << g.ppField[y][x] << " | ";
		};
		cout << endl;
	};

	cout << endl << "Human: " << g.human << endl << "AI: " << g.ai << endl;
};

void _fastcall congrats(const Game& g)
{
	if (g.progress == WON_HUMAN)
	{
		cout << "Human won! =)" << endl;
	}
	if (g.progress == WON_AI)
	{
		cout << "AI won! =(" << endl;
	}if (g.progress == DRAW)
	{
		cout << "Draw! =|" << endl;
	}
};

Coord getHumanCoord(const Game& g)
{
	Coord c;
	do {
		cout << "Enter x: ";
		cin >> c.x;

		cout << "Enter y: ";
		cin >> c.y;
	} while (c.x == 0 || c.x > 3 || c.y == 0 || c.y > 3 || g.ppField[c.y-1][c.x-1] != EMPTY);
	c.y--;
	c.x--;
	
	return c;
};

Coord getAICoord(Game& g)
{
	if (g.ppField[1][1] == EMPTY)
		return { 1,1 };

	Coord arr[4];
	size_t num{ 0 };

	if (g.ppField[0][0] == EMPTY)
	{
		arr[num] = { 0,0 };
		num++;
	}
	if (g.ppField[2][2] == EMPTY)
	{
		arr[num] = { 2,2 };
		num++;
	}
	if (g.ppField[0][2] == EMPTY)
	{
		arr[num] = { 0,2 };
		num++;
	}
	if (g.ppField[2][0] == EMPTY)
	{
		arr[num] = { 2,0 };
		num++;
	}
	if (num > 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return arr[index];
	};

	num = 0;

	if (g.ppField[0][1] == EMPTY)
	{
		arr[num] = { 0,1 };
		num++;
	}
	if (g.ppField[2][1] == EMPTY)
	{
		arr[num] = { 2,1 };
		num++;
	}
	if (g.ppField[1][0] == EMPTY)
	{
		arr[num] = { 1,0 };
		num++;
	}
	if (g.ppField[1][2] == EMPTY)
	{
		arr[num] = { 1,2 };
		num++;
	}
	if (num > 0)
	{
		const size_t index = getRandomNum(0, 1000) % num;
		return arr[index];
	};

	return {};
};

Progress getWon(const Game& g)
{
	for (size_t y = 0; y < g.SIZE; y++)
	{
		if (g.ppField[y][0] == g.ppField[y][1] && g.ppField[y][0] == g.ppField[y][2])
		{
			if (g.ppField[y][0] == g.human)
			{
				return WON_HUMAN;
			}
			if (g.ppField[y][0] == g.ai)
			{
				return WON_AI;
			}
		}
	}

	for (size_t x = 0; x < g.SIZE; x++)
	{
		if (g.ppField[0][x] == g.ppField[1][x] && g.ppField[0][x] == g.ppField[2][x])
		{
			if (g.ppField[0][x] == g.human)
			{
				return WON_HUMAN;
			}
			if (g.ppField[0][x] == g.ai)
			{
				return WON_AI;
			}
		}
	}


		if (g.ppField[0][0] == g.ppField[1][1] && g.ppField[0][0] == g.ppField[2][2])
		{
			if (g.ppField[0][0] == g.human)
			{
				return WON_HUMAN;
			}
			if (g.ppField[0][0] == g.ai)
			{
				return WON_AI;
			}
		}

		if (g.ppField[0][2] == g.ppField[1][1] && g.ppField[2][0] == g.ppField[1][1])
		{
			if (g.ppField[1][1] == g.human)
			{
				return WON_HUMAN;
			}
			if (g.ppField[1][1] == g.ai)
			{
				return WON_AI;
			}
		}

		bool draw = true;
		for (size_t y = 0; y < g.SIZE; y++)
		{
			for (size_t x = 0; x < g.SIZE; x++)
			{
				if (g.ppField[y][x] == EMPTY)
				{
					draw = false;
					break;
				}
			}
			if (!draw)
				break;
		};

		if (draw)
			return DRAW;

	return IN_PROGRESS;
};


int main()
{
	Game g;
	initGame(g);

	ClearScr();
	PrintGame(g);

	do {
		if (g.turn % 2 == 0)
		{
			Coord c = getHumanCoord(g);
			g.ppField[c.y][c.x] = g.human;
		}
		else
		{
			Coord c = getAICoord(g);
			g.ppField[c.y][c.x] = g.ai;
		}

		ClearScr();
		PrintGame(g);
		g.progress = getWon(g);
		g.turn++;

	} while (g.progress == IN_PROGRESS);

	congrats(g);

	deinitGame(g);
	return 0;
}
