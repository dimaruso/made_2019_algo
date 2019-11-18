#include<vector>
#include<string>
#include<iostream>
#include<assert.h>

using std::vector;
using std::string;
using std::cin;
using std::cout;

//Хеш-функция, реализованная методом Горнера
struct Hasher
{
	unsigned int operator()(const string& str) const 
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < str.length(); ++i)
			hash = hash * 127 + str[i];
		return hash;
	}
};

//Хэш-таблица
template<class T, class H>
class HashTable
{
public:
	HashTable(const H& _hasher);
	HashTable(const HashTable& t) = delete;
	HashTable& operator=(const HashTable& t) = delete;
	~HashTable();

	bool Add(const T& key);
	bool Delete(const T& key);
	bool Has(const T& key) const;

private:
	unsigned int keysCount;
	unsigned int placeCount;
	struct Node;
	vector<Node> Table;
	H hasher;
	void growTable();
	int Probe(const int& hash, const int& i, const int& m) const;

};

template<class T, class H>
struct HashTable<T, H>::Node
{
	T Key;
	int Visited; //0 = no, 1 = yes, 2 = del
	Node(): Visited(0) {}
	Node(const T& key) : Key(key), Visited(1) {}
};

template<class T, class H>
HashTable<T, H>::HashTable(const H& _hasher) :
	keysCount(0),
	placeCount(8),
	Table(8),
	hasher(_hasher)	
{
}

template<class T, class H>
HashTable<T, H>::~HashTable()
{
}

// Вставка ключа в хеш-таблицу.
template<class T, class H>
bool HashTable<T, H>::Add(const T& _key)
{
	// used 3/4 tables
	if (4 * keysCount > placeCount * 3)
		growTable();
	int hash = hasher(_key)% Table.size();
	int lastdel = -1;
	for (int i = 0, j = hash; i < Table.size(); ++i, j = (j + i) % Table.size())
	{
		if (lastdel == -1 && Table[j].Visited == 2) lastdel = j;

		if (Table[j].Visited == 1 && Table[j].Key == _key)
			break;//return false;
		if (Table[j].Visited == 0) 
		{
			if (lastdel == -1)
			{
				Table[j] = Node(_key);
				--placeCount;
			}
			else
				Table[lastdel] = Node(_key);
			++keysCount;
			return true;
		}
	}
	return false;
}

//Удаление ключа из таблицы
template<class T, class H>
bool HashTable<T, H>::Delete(const T& _key)
{
	int hash = hasher(_key) % Table.size();
	for (int i = 0, j = hash; i < Table.size(); ++i, j = (j + i) % Table.size())
	{
		if (Table[j].Visited == 1 && Table[j].Key == _key)
		{
			Table[j].Visited = 2;
			--keysCount;
			return true;
		}
		if (Table[j].Visited == 0) break;
	}	
	return false;
}

//Проверка наличия ключа в таблице
template<class T, class H>
bool HashTable<T, H>::Has(const T& _key) const
{
	int hash = hasher(_key) % Table.size();
	for (int i = 0, j = hash; i < Table.size(); ++i, j =(j + i)% Table.size())
	{
		if (Table[j].Visited == 1 && Table[j].Key == _key)
			return true;
		if (Table[j].Visited == 0) break;
	}
	return false;
}

//Квадратичное пробирование (в методах класса реализуется итеративно)
//g(k, i)=g(k, i-1) + i (mod m), m - степень двойки.
template<class T, class H>
int HashTable<T, H>::Probe(const int& _hash, const int& _i, const int& m) const
{
	return (_hash + _i * (_i + 1) / 2) % m;
}

//Динамическое расширение таблицы в 2 раза
template<class T, class H>
void HashTable<T, H>::growTable()
{
	vector<Node> newTable(Table.size()*2);
	placeCount = newTable.size();
	for (int i = 0; i < Table.size(); ++i)
	{
		if (Table[i].Visited == 1)
		{
			int hash = hasher(Table[i].Key) % newTable.size();
			for (int k = 0, j = hash; k < newTable.size(); ++k, j = (j + k) % newTable.size())
			{
				if (newTable[j].Visited != 1)
				{
					newTable[j].Visited = 1;
					newTable[j].Key = Table[i].Key;
					--placeCount;
					break;
				}
			}
		}
	}
	Table = std::move(newTable);
}

int main()
{
	Hasher hasher;
	HashTable<string, Hasher> table(hasher);	
	char command;
	string word;
	while (cin >> command >> word) {
		switch (command) {
		case '+':
			cout << (table.Add(word) ? "OK" : "FAIL") << "\n";
			break;
		case '-':
			cout << (table.Delete(word) ? "OK" : "FAIL") << "\n";
			break;
		case '?':
			cout << (table.Has(word) ? "OK" : "FAIL") << "\n";
			break;
		default:
			assert(false);
		}
	}
	return 0;
}
