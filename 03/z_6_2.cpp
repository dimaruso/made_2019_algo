#include <iostream>
#include <stack>
class BinTree
{
public:
	BinTree();
	~BinTree();
	struct Node;
	void Insert(const int value);
	Node* Find(int const value);
	Node* FindMin(int const value);
	void DFS();
private:
	size_t Count;
	Node* Root;
	void DFSN(Node* node);
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
}

BinTree::Node::Node(int _k) :
	Key(_k),
	Left(nullptr),
	Right(nullptr)
{
}

BinTree::Node::~Node()
{
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

BinTree::Node* BinTree::Find(int const value)
{
	Node* last = Root;
	while (value != last->Key && (last->Left || last->Right))
	{
		if (value < last->Key)
			last = last->Left;
		else if (value > last->Key)
			last = last->Right;
	}
	return last;
}

BinTree::Node* BinTree::FindMin(int const value)
{
	Node* cur = Root;
	if (cur)
	while (cur->Left != nullptr)
		cur = cur->Left;
	return cur;
}

void BinTree::DFS()
{
	DFSN(Root);
	return;
}

void BinTree::DFSN(Node* node)
{
	
	std::stack<Node*> s;
	Node* cur = Root;

	while (true)
	{
		if (cur->Key == 10)
			s.empty();
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
				std::cout << s.top()->Key << " ";
				s.pop();
				cur = cur->Right;
			}
			else
			{
				while (!s.empty() && !cur->Right)
				{
					std::cout << s.top()->Key << " ";
					s.pop();
					if(!s.empty()) cur = s.top();
				}
				if (!s.empty() && cur->Right)
				{
					std::cout << s.top()->Key << " ";
					s.pop();
					cur = cur->Right;
				}
				else break;
			}
		}
	}
	std::cout << '\n';
	return;
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

	MyBinTree.DFS();
	//system("pause");
	return 0;
}
