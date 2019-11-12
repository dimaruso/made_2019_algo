#include <iostream>
#include <stack>

class BinTree
{
public:
	BinTree();
	~BinTree();
	void Insert(const int value);
	void DeleteNode(const int value);
	void DFS(void(*TakeValue)(const int value))const;
	bool Find(int const value)const;
	int FindMin()const;
private:
	size_t Count;
	struct Node;
	Node* Root;
	void DFSN(Node* node, void(*TakeValue)(const int value))const;
	Node* FindN(int const value)const;
	Node* FindMinN()const;
};

struct BinTree::Node
{
	Node(int _k);
	~Node();
	int Key;
	Node* Left;
	Node* Right;
};

BinTree::BinTree() :
	Count(0),
	Root(nullptr)
{
}

BinTree::~BinTree()
{
	if(Root != nullptr)
		Root->~Node();
}

BinTree::Node::Node(int _k) :
	Key(_k),
	Left(nullptr),
	Right(nullptr)
{
}

BinTree::Node::~Node()
{
	if (Left != nullptr) delete Left;
	if (Right != nullptr) delete Right;
}

void BinTree::Insert(const int value)
{
	++Count;
	Node* m = new Node(value);

	if (Root == nullptr) Root = m;
	else
	{
		Node* last = Root;
		while (last)
		{
			if (value < last->Key)
			{
				if (last->Left)
					last = last->Left;
				else
				{
					last->Left = m;
					break;
				}
			}
			else if (value > last->Key)
			{
				if (last->Right)
					last = last->Right;
				else
				{
					last->Right = m;
					break;
				}
			}
			else
			{
				if (!last->Left)
				{
					last->Left = m;
					break;
				}
				else if (!last->Right)
				{
					last->Right = m;
					break;
				}
				last = last->Right;
			}
		}
	}
}

void BinTree::DeleteNode(const int value)
{

		Node* last = Root; //Parent
		Node* cur = Root;

		if (Root->Key == value)
		{
			if (!Root->Left)
			{
				Root = Root->Right;
			}
			else if (!Root->Right)
			{
				Root = Root->Left;
			}
		}
		//Find Parent & current
		while (last && value != last->Key && (last->Left || last->Right))
		{
			if (value < last->Key)
			{
				if (last->Left && last->Left->Key == value)
				{
					cur = last->Left;
					break;
				}
				last = last->Left;
			}
			else if (value > last->Key)
			{
				if (last->Right && last->Right->Key == value)
				{
					cur = last->Right;
					break;
				}
				last = last->Right;
			}
		}

		//delete current
		if (cur->Key == value)
		{
			while (cur)
			{
				if (!cur->Left)
				{
					if (last->Left == cur)
						last->Left = cur->Right;
					else if (last->Right == cur)
						last->Right = cur->Right;
					break;
				}
				else if (!cur->Right)
				{
					if (last->Left == cur)
						last->Left = cur->Left;
					else if (last->Right == cur)
						last->Right = cur->Left;
					break;
				}
				else
				{
					last = cur;
					cur->Key = cur->Right->Key;
					cur = cur->Right;
				}
			}
			delete cur;
		}
}

BinTree::Node* BinTree::FindN(int const value)const
{
	Node* last = Root;
	while (value != last->Key && (last->Left || last->Right))
	{
		if (value < last->Key)
			last = last->Left;
		else if (value > last->Key)
			last = last->Right;
	}
	if (last->Key == value)
		return last;
	else
		return nullptr;
}

bool BinTree::Find(int const value)const
{
	Node* last = FindN(value);
	return (last && last->Key == value);
}


BinTree::Node* BinTree::FindMinN()const
{
	Node* cur = Root;
	if (cur)
	while (cur->Left != nullptr)
		cur = cur->Left;
	return cur;
}

int BinTree::FindMin()const
{
	Node* cur = FindMinN();
	if (cur)
		return cur->Key;
	else
	{
		throw std::out_of_range("Tree is empty");
		return -1;
	}
}

void BinTree::DFS( void(*TakeValue)(const int value))const
{
	DFSN(Root, TakeValue);
	return;
}

void BinTree::DFSN(Node* node, void(*TakeValue)(const int value))const
{
	
	std::stack<Node*> s;
	Node* cur = node;

	while (true)
	{
		while (cur)
		{
			s.push(cur);
			cur = cur->Left;
		}

		if (s.empty()) break;
		else
		{
			cur = s.top();
			if (cur->Right)
			{
				TakeValue(s.top()->Key);
				s.pop();
				cur = cur->Right;
			}
			else
			{
				while (!s.empty() && !cur->Right)
				{
					TakeValue(s.top()->Key);
					s.pop();
					if(!s.empty()) cur = s.top();
				}
				if (!s.empty() && cur->Right)
				{
					TakeValue(s.top()->Key);
					s.pop();
					cur = cur->Right;
				}
				else break;
			}
		}
	}
	return;
}

void PrintValue(const int value)
{
	std::cout << value << " ";
}

int main()
{
	BinTree MyBinTree;
	size_t n;
	std::cin >> n;
	int num;
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> num;
		MyBinTree.Insert(num);
	}
	MyBinTree.DFS(PrintValue);

	//system("pause");
	return 0;
}
