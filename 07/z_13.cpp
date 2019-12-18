#include<cassert>
#include<array>
#include<iostream>
#include<queue>
#include<unordered_map>
#include<string>
#include <algorithm>

using std::array;
using std::vector;
using std::cin;
using std::cout;
using std::queue;
using std::unordered_map;
using std::swap;
using std::ostream;
using std::endl;
using std::string;
using std::priority_queue;

static const size_t SideSize = 4;
static const size_t FieldSize = SideSize * SideSize;
static const array<char, FieldSize> FinishState = 
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
struct Hasher;

class GameState {
public:
	GameState(const array<char, FieldSize>& field);

	bool IsFinish() const;

	bool CanMoveLeft() const;
	bool CanMoveUp() const;
	bool CanMoveRight() const;
	bool CanMoveDown() const;

	GameState MoveLeft() const;
	GameState MoveUp() const;
	GameState MoveRight() const;
	GameState MoveDown() const;

	bool operator == (const GameState& state) const 
	{ 
		return field == state.field;
	}
	bool operator != (const GameState& state) const 
	{
		return !(field == state.field);
	}

	const char operator[](const size_t& i) const
	{
		if (i < FieldSize) return field[i];
		else
			throw std::out_of_range("out of range");
	}

	friend ostream& operator << (ostream& out, const GameState& state);
	friend Hasher;

	const bool operator < (const GameState& state) const noexcept
	{
		return comp() > state.comp();
	}


	const size_t comp() const
	{
		return path + 6 * Man_dst();
	}

	const size_t Man_dst() const
	{
		size_t dst = 0;
		for (int i = 0; i < FieldSize; ++i)
			if (field[i])
				dst += std::abs((int)(i % 4) - (field[i] - 1) % 4) +
				std::abs((int)(i / 4) - (field[i] - 1) / 4);
		return dst;
	}

private:
	array<char, FieldSize> field;
	char emptyPos;
	size_t path;
};

GameState::GameState(const array<char, FieldSize>& f) :
	field(f),
	emptyPos(-1),
	path(0)
{
	for (size_t i = 0; i < field.size(); i++)
		if (field[i] == 0) 
		{
			emptyPos = i;
			break;
		}
	assert(emptyPos != -1);
}

bool GameState::IsFinish() const
{
	return field == FinishState;
}

bool GameState::CanMoveLeft() const
{
	return emptyPos % SideSize != 0;
}

bool GameState::CanMoveUp() const
{
	return emptyPos >= SideSize;
}

bool GameState::CanMoveRight() const
{
	return emptyPos % SideSize < SideSize - 1;
}

bool GameState::CanMoveDown() const
{
	return emptyPos < FieldSize - SideSize;
}

GameState GameState::MoveLeft() const
{
	assert(CanMoveLeft());

	GameState newState(*this);
	swap(newState.field[emptyPos], newState.field[emptyPos - 1]);
	--newState.emptyPos;
	newState.path = path + 1;
	return newState;
}

GameState GameState::MoveUp() const
{
	assert(CanMoveUp());

	GameState newState(*this);
	swap(newState.field[emptyPos], newState.field[emptyPos - SideSize]);
	newState.emptyPos -= SideSize;
	newState.path = path + 1;
	return newState;
}

GameState GameState::MoveRight() const
{
	assert(CanMoveRight());

	GameState newState(*this);
	swap(newState.field[emptyPos], newState.field[emptyPos + 1]);
	++newState.emptyPos;
	newState.path = path + 1;
	return newState;
}

GameState GameState::MoveDown() const
{
	assert(CanMoveDown());

	GameState newState(*this);
	swap(newState.field[emptyPos], newState.field[emptyPos + SideSize]);
	newState.emptyPos += SideSize;
	newState.path = path + 1;
	return newState;
}

ostream& operator << (ostream& out, const GameState& state)
{
	for (int y = 0; y < SideSize; y++) 
	{
		for (int x = 0; x < SideSize; x++)
			out << static_cast<int>(state.field[y * SideSize + x]) << ' ';
		out << endl;
	}
	out << endl;
	return out;
}

struct Hasher {
	size_t operator()(const GameState& state) const
	{
		size_t hash = 0;
		for (size_t i = 0; i < SideSize; ++i)
			hash += state[i] * i;
		return hash;
	}
};

struct comparator
{
	bool operator()(const GameState& a, const GameState& b)
	{
		return a.comp() < b.comp();
	}
};

string GetPuzzleSolution(const GameState& state)
{
	priority_queue <GameState> qu;
	priority_queue < GameState, vector<GameState>, comparator > rqu;
	qu.push(state);
	unordered_map<GameState, char, Hasher> visited;
	bool hasSolution = false;
	visited[state] = 'S';
	while (qu.size() > 0) {
		GameState tempState = qu.top();
		qu.pop();
		if (tempState.IsFinish()) {
			hasSolution = true;
			break;
		}

		if (tempState.CanMoveLeft()) {
			GameState newState = tempState.MoveLeft();
			if (visited.find(newState) == visited.end()) {
				rqu.push(newState);
				visited[newState] = 'L';
			}
		}
		if (tempState.CanMoveUp()) {
			GameState newState = tempState.MoveUp();
			if (visited.find(newState) == visited.end()) {
				rqu.push(newState);
				visited[newState] = 'U';
			}
		}
		if (tempState.CanMoveRight()) {
			GameState newState = tempState.MoveRight();
			if (visited.find(newState) == visited.end()) {
				rqu.push(newState);
				visited[newState] = 'R';
			}
		}
		if (tempState.CanMoveDown()) {
			GameState newState = tempState.MoveDown();
			if (visited.find(newState) == visited.end()) {
				rqu.push(newState);
				visited[newState] = 'D';
			}
		}
		while (rqu.size() > 2) rqu.pop();
		while (!rqu.empty())
		{
			qu.push(rqu.top());
			rqu.pop();
		}
	}
	assert(hasSolution);

	string solution;
	GameState tempState(FinishState);
	char turn = visited[tempState];
	while (turn != 'S') {
		switch (turn) {
		case 'L':
			tempState = tempState.MoveRight();
			solution += 'R';
			break;
		case 'U':
			tempState = tempState.MoveDown();
			solution += 'D';
			break;
		case 'R':
			tempState = tempState.MoveLeft();
			solution += 'L';
			break;
		case 'D':
			tempState = tempState.MoveUp();
			solution += 'U';
			break;
		}
		turn = visited[tempState];
	}
	std::reverse(solution.begin(), solution.end());
	return solution;
}

bool HasSolution(const GameState& state)
{
	size_t K;
	size_t N = 0;
	for (size_t i = 0; i < FieldSize; ++i)
		if (state[i])
		{
			for (size_t j = i; j < FieldSize; ++j)
				if (state[i] > state[j] && state[j]) ++N;
		}
		else
			K = (i / SideSize) + 1;
	return !((N + K) % 2);
}

int main()
{
	array<char, FieldSize> StartState;
	int tmp;
	for (size_t i = 0; i < FieldSize; ++i)
	{
		std::cin >> tmp;
		StartState[i] = tmp;
	}
	GameState state(StartState);

	if (HasSolution(state))
	{
		string solution = GetPuzzleSolution(state);
		std::cout << solution.size() << '\n';
		std::cout << solution;
	}
	else
		std::cout << "-1";
	system("pause");
	return 0;
}
