#include <iostream>
#include <string>
#include <stdint.h>
#include<vector>
#include <stack>
#include <algorithm>
#include<unordered_map>
#include<map>
#include <fstream>
#include <ios>
#include "Huffman.h"
using namespace std;
size_t BytesToint(unsigned char* c)
{
	size_t r = 0;
	for (int i = 0, k = 16777216; i < 4; ++i, k /= 256)
	{
		r += c[i] * k;
	}
	return r;
}
unsigned char BitsToChar(unsigned char* c)
{
	unsigned char r = 0;
	for (int i = 7, k = 128; i >=0 ; --i, k /= 2)
		if (c[i] == '1')
			r += k;
	return r;
}
unsigned char* intToBytes(const size_t& value) {
	unsigned char* bytes = new unsigned char[4];
	bytes[3] = (char)value;
	bytes[2] = (char)(value >> 8);
	bytes[1] = (char)(value >> 16);
	bytes[0] = (char)(value >> 24);
	return bytes;
}
bool ReadBit(const unsigned char& bit, const int pos)
{
	unsigned char tmp = bit;
	tmp |= 1 << (pos % 8);
	return tmp == bit;
}
////////////////////////////////////////////////////////
class OutBitStream {
public:
	OutBitStream();

	void WriteBit(unsigned char bit);
	void WriteByte(unsigned char byte);

	const unsigned char* GetBuffer() const;
	uint64_t GetBitsCountNode() const;
	uint64_t GetSize() const;

private:
	vector<unsigned char> buffer;
	uint64_t bitsCountNode;
};
OutBitStream::OutBitStream() :bitsCountNode(0)
{
}
void OutBitStream::WriteBit(unsigned char bit)
{
	if (bitsCountNode + 1 > buffer.size() * 8)
		buffer.push_back(0);

	if (bit != '0')
		buffer[bitsCountNode / 8] |= 1 << (bitsCountNode % 8);

	++bitsCountNode;
}
void OutBitStream::WriteByte(unsigned char byte)
{
	if (bitsCountNode % 8 == 0) {
		buffer.push_back(byte);
	}
	else {
		int offset = bitsCountNode % 8;
		buffer[bitsCountNode / 8] |= byte << offset;
		buffer.push_back(byte >> (8 - offset));
	}
	bitsCountNode += 8;
}
const unsigned char*  OutBitStream::GetBuffer() const
{
	return buffer.data();
}
uint64_t OutBitStream::GetBitsCountNode() const
{
	return bitsCountNode;
}
uint64_t OutBitStream::GetSize() const
{
	return buffer.size();
}
////////////////////////////////////////////////////////
struct Hasher {
	size_t operator()(const unsigned char& state) const 
	{
		size_t hash = state*127;
		return hash;
	}
};
////////////////////////////////////////////////////////
class BinTree
{
public:
	BinTree(std::string s);
	BinTree(std::string s, size_t _sizeTree);
	~BinTree();
	void CreateTable(std::string& s, OutBitStream& _out);
	std::string DecodeS(std::string& s, const size_t& start, const size_t& end) const;
	size_t size()
	{
		return CountNode;
	}
	bool isEmpty()
	{
		return !CountNode;
	}
private:
	struct Node;
	size_t CountNode;
	size_t CountChar;
	Node* Root;
	std::unordered_map<unsigned char, std::string, Hasher> CodeTable;
	void DFSN(Node* node, const std::string& s);
	void NewZipTree(Node *_cur, OutBitStream& _out);
};
////////////////////////////////////////////////////////
struct BinTree::Node
{
	unsigned char Letter;//значение байта
	int Key;//частота - ключ дял кучи
	Node* Left;
	Node* Right;
	Node() :
		Left(nullptr),
		Right(nullptr)
	{}
	Node(const unsigned char& c);
	Node(const int& p);
	Node(const Node& second);
	~Node();

	friend const bool operator<(const Node& l, const Node& r)
	{
		return l.Key > r.Key;
	}
	friend const bool operator>(const Node& l, const Node& r)
	{
		return l.Key < r.Key;
	}
	friend const bool operator==(const Node& l, const Node& r)
	{
		return l.Key == r.Key;
	}
	friend const bool operator!=(const Node& l, const Node& r)
	{
		return l.Key != r.Key;
	}
};
BinTree::Node::Node(const unsigned char& c) :
	Letter(c),
	Key(1),
	Left(nullptr),
	Right(nullptr)
{
}
BinTree::Node::Node(const int& p) :
	Key(p),
	Left(nullptr),
	Right(nullptr)
{
}
BinTree::Node::Node(const Node& second) :
	Letter(second.Letter),
	Key(second.Key),
	Left(second.Left),
	Right(second.Right)
{
}
BinTree::Node::~Node()
{
}

BinTree::BinTree(std::string s, size_t _sizeTree):
	CountNode(_sizeTree)
{
	Node* cur;
	unsigned char c;
	unsigned char* testc = new unsigned char[8];
	std::stack<Node*> st;
	size_t i = 0;
	while (i<_sizeTree)
	{
		if (s[i] == '1')
		{
			for (size_t j = 0; j < 8; ++j)
				testc[j] = s[i + 1 + j];
			i += 8;
			c = BitsToChar(testc);
			cur = new Node(c);
			st.push(cur);
		}
		else
		{
			cur = new Node();
			cur->Right = st.top();
			st.pop();
			cur->Left = st.top();
			st.pop();
			st.push(cur);
		}
		++i;
	}
	Root = st.top();
}

BinTree::BinTree(std::string s) :
	CountNode(0),
	CountChar(0),
	Root(nullptr)
{
	vector<Node> table;
	//считаем частоты букв
	vector<unsigned char> let;
	map<unsigned char, Node> Freq;
	int size = s.size();
	int i = 0;
	while (i < size) {
		if (Freq.find(s[i]) == Freq.cend())
		{
			let.push_back(s[i]);
			Freq[s[i]] = Node((unsigned char)s[i]);

		}
		else
			++Freq[s[i]].Key;
		++i;
	}
	for (size_t i = 0; i < let.size(); ++i)
		table.push_back(Freq[let[i]]);

	std::make_heap(table.begin(), table.end());
	////////////////////////////////////////////////////////
	while (!table.empty())
	{
		Node* l = new Node(table.front());
		++CountNode;
		table.front().Left = nullptr;
		table.front().Right = nullptr;
		pop_heap(table.begin(), table.end());
		table.pop_back();
		Node* r = nullptr;
		if (!table.empty())
		{
			r = new Node(table.front());
			++CountNode;
			table.front().Left = nullptr;
			table.front().Right = nullptr;
			pop_heap(table.begin(), table.end());
			table.pop_back();
		}
		else
			Root = l;

		if (!table.empty())
		{
			table.push_back(Node(l->Key + r->Key));
			table.back().Left = l;
			table.back().Right = r;
			std::push_heap(table.begin(), table.end());
		}
		else
		{
			Root = new Node(l->Key + r->Key);
			Root->Left = l;
			Root->Right = r;
			++CountNode;
		}
	}
}
BinTree::~BinTree()
{
	if (Root != nullptr)
	{
		std::stack<Node*> s;
		Node* cur = Root;
		s.push(cur);
		while (!s.empty())
		{
			cur = s.top();
			s.pop();
			if (cur->Left)
			{
				s.push(cur->Left);
				cur->Left = nullptr;
			}
			if (cur->Right)
			{
				s.push(cur->Right);
				cur->Right = nullptr;
			}
			delete cur;
		}
	}
	if (!CodeTable.empty()) 
		CodeTable.clear();
	CountNode = 0;
	Root = nullptr;
}

void BinTree::DFSN(Node* node, const std::string& s)
{
	if (!node->Left && !node->Right)
	{
		CodeTable[node->Letter] = s;
		return;
	}
	DFSN(node->Left, s + '0');
	DFSN(node->Right, s + '1');
	return;
}
void BinTree::NewZipTree(Node *node, OutBitStream& _out)
{
	if (!node->Left && !node->Right)
	{
		_out.WriteBit('1');
		_out.WriteByte(node->Letter);
		return;
	}
	NewZipTree(node->Left, _out);
	NewZipTree(node->Right,_out);
	_out.WriteBit('0');
	return;
}
void BinTree::CreateTable(std::string& s, OutBitStream& _out)
{
	DFSN(Root, "");
	NewZipTree(Root, _out);
	size_t sizetree = _out.GetBitsCountNode();
	for (uint64_t i = 0; i < s.size(); ++i)
	{
		for(size_t j=0; j< CodeTable[s[i]].size(); ++j)
			_out.WriteBit(CodeTable[s[i]][j]);
	}
	size_t sizecode = _out.GetBitsCountNode() - sizetree;
	CountNode = sizetree;
	return;
}
std::string BinTree::DecodeS(std::string& s, const size_t& start, const size_t& end) const
{
	Node* cur = Root;
	std::string res;
	for (size_t i = start; i < end; ++i)
	{
		if (s[i] == '0') cur = cur->Left;
		if (s[i] == '1') cur = cur->Right;
		if (!cur->Left && !cur->Right)
		{
			res += cur->Letter;
			cur = Root;
		}
	}
	return res;
}

static void copyStream(IInputStream& input, IOutputStream& output)
{
	byte value;
	while (input.Read(value))
	{
		output.Write(value);
	}
}

void Encode(IInputStream& original, IOutputStream& compressed)
{
	string s;
	byte value;
	while (original.Read(value))
		s.push_back(value);

	BinTree Tr(s);
	OutBitStream test;
	Tr.CreateTable(s, test);
	
	size_t sizetree = Tr.size();
	unsigned char* csizetree = intToBytes(sizetree);

	size_t sizecode = test.GetBitsCountNode()-sizetree;
	unsigned char* csizecode = intToBytes(sizecode);

	if (s.size() < test.GetSize())
	{
		value = 255;
		compressed.Write(value);
		size_t i = 0;
		while (i < s.size())
		{
			value = s[i];
			compressed.Write(value);
			++i;
		}
		return;
	}
	for (size_t i = 0; i < sizeof(size_t); ++i)
		compressed.Write(csizetree[i]);
	for (size_t i = 0; i < sizeof(size_t); ++i)
		compressed.Write(csizecode[i]);
	for (size_t i = 0; i < test.GetSize(); ++i)
		compressed.Write(test.GetBuffer()[i]);
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
	string s;
	byte value;
	size_t sizecode;
	size_t sizetree;
	unsigned char* cbuf = new unsigned char[sizeof(size_t)];
	unsigned char* i = cbuf;
	int j = 0;
	while (j < sizeof(size_t))
	{
		compressed.Read(value);
		if(j == 0 && value == 255)
		{
			compressed.Read(value);
			original.Write(value);
			copyStream(compressed, original);
			return;
		}
		i[0] = value;
		++i;
		++j;
	}
	sizetree = BytesToint(cbuf);
	j = 0;
	i = cbuf;
	while (j < sizeof(size_t))
	{
		compressed.Read(value);
		i[0] = value;
		++i;
		++j;
	}
	sizecode = BytesToint(cbuf);
	//read bytes
	j = 0;
	s = "";
	while (compressed.Read(value))
	{
		s.push_back(value);
		++j;
	}
	string bytes;
	for (size_t i = 0; i < s.size(); ++i)
	{	
		for (int k = 0; k < 8; ++k)
		{
			if(ReadBit(s[i], k))
				bytes.push_back('1');
			else
				bytes.push_back('0');
		}
	}
	BinTree Tr(bytes, sizetree);
	string result = Tr.DecodeS(bytes, sizetree, sizecode + sizetree);
	for (size_t jojo = 0; jojo < result.size(); ++jojo)
	{
		original.Write(result[jojo]);
	}
}
////////////////////////////////////////////////////////
void CreateTest()
{
	std::ofstream original("input.txt", std::ios::binary);
	original << "abracadabra\tada";
}
void testEncode()
{

	string inp = "input.txt";
	string comp = "zipfile";
	string res = "result.txt";
	std::ifstream finp(inp, std::ios::binary);
	std::ofstream fcomp(comp, std::ios::binary);

	IInputStream inps(inp, finp);
	IOutputStream ocomp(comp, fcomp);

	Encode(inps, ocomp);
}
void testDecode()
{
	string inp = "input.txt";
	string comp = "zipfile";
	string res = "result.txt";
	std::ifstream fcomp2(comp, std::ios::binary);
	std::ofstream fres2(res, std::ios::binary);

	IInputStream icomp(comp, fcomp2);
	IOutputStream ores(res, fres2);

	Decode(icomp, ores);
}

bool isEqual(const vector<byte>& v1, const vector<byte>& v2)
{
	if (v1.size() != v2.size()) {
		return false;
	}
	for (unsigned int i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i]) {
			return false;
		}
	}
	return true;
}
void readfile(const string& filename, vector<byte>& v1)
{
	ifstream file;
	file.open(filename.c_str());
	byte value;
	while (file >> value) {
		v1.push_back(value);
	}
}
int main()
{
	CreateTest();
	testEncode();
	testDecode();
	
	vector<byte> input;
	vector<byte> result;
	readfile("input.txt", input);
	readfile("result.txt",result);

	cout << isEqual(input, result);

	system("pause");
	return 0;
}
