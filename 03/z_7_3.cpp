#include <iostream>
#include <ctime>

class Treap
{
public:
	Treap();
	~Treap();
	struct Node;
	void Insert(int const value);
	void DeleteNode(int const value);
	Node* Find(int const value)const;
	int FindCount(int const value)const;
	Node* FindMin(int const value)const;
	void DFS()const;
private:
	Node* Root;
	void Split(Node* node, int key,
		Node*& left, Node*& right);
	Node* Merge(Node* left, Node* right);
	bool UpdateCount(Node* locRoot, int const value, int const dlt);
	void DFSN(Node* node)const;
};

struct Treap::Node
{
	Node(int _k, int _p);
	~Node();
	size_t Count;
	int Key;
	int Priority;
	Node* Left;
	Node* Right;
};

Treap::Treap() :
	Root(nullptr)
{
}

Treap::~Treap()
{
}

Treap::Node::Node(int _k, int _p) :
	Count(1),
	Key(_k),
	Priority(_p),
	Left(nullptr),
	Right(nullptr)
{
}

Treap::Node::~Node()
{
}

// Разрезание декартового дерева по ключу.
void Treap::Split(Node* node, int key,
	Node*& left, Node*& right)
{
	if (node == nullptr) 
	{
		left = right = nullptr;
		return;
	}
	else if (node->Key <= key) {
		Split(node->Right, key,
			node->Right, right);
		left = node;
	}
	else {
		Split(node->Left, key,
			left, node->Left);
		right = node;		
	}
	node->Count = 1;
		if (node->Left)
			node->Count += node->Left->Count;
		if (node->Right)
			node->Count += node->Right->Count;
}

// Слияние двух декартовых деревьев.
Treap::Node* Treap::Merge(Node* left, Node* right)
{
	if (!left || !right)
		return left == 0 ? right : left;

	Node* localRoot = left->Priority > right->Priority ? left : right;
	Node* tmp;
	while (left && right) 
	{
		if (left->Priority > right->Priority) 
		{
			while (left->Right && left->Right->Priority > right->Priority)
			{
				left->Count = left->Count + right->Count;
				left = left->Right;
			}
			tmp = left->Right;
			left->Count = left->Count + right->Count;
			left->Right = right;
			left = tmp;
		}
		else 
		{
			while (right->Left && right->Left->Priority >= left->Priority)
			{
				right->Count = left->Count + right->Count;
				right = right->Left;
			}
			tmp = right->Left;
			right->Count = left->Count + right->Count;
			right->Left = left;
			right = tmp;
		}
	}
	return localRoot;
}

bool Treap::UpdateCount(Node* locRoot, int const value, int const dlt)
{
	Node* last = locRoot;
	if (!last) return false;
	while (value != last->Key && (last->Left || last->Right))
	{
		last->Count += dlt;

		if (value < last->Key)
			last = last->Left;
		else if (value > last->Key)
			last = last->Right;
	}
	if (value == last->Key)
	{
		last->Count = 1;
		if (last->Left)
			last->Count += last->Left->Count;
		if (last->Right)
			last->Count += last->Right->Count;
		return true;
	}
	else
	{
		return false;
	}
}

void Treap::Insert(int const value)
{
	int pr = 512;
	if (Root)
	{
		Node* l;
		Node* r;
		Split(Root, value, l, r);
		//if (pr < Root->Count) pr = Root->Count;
		Node* m = new Node(value, 1+rand() % pr);
		Root = Merge(Merge(l, m), r);
	} 
	else
	{
		Root = new Node(value, 1+ rand() % pr);
		Root->Count = 1;
	}
}

void Treap::DeleteNode(int const value)
{
	
	if (UpdateCount(Root, value, -1))
	{

		/////////Find Parent//////////
		Node* last = Root; //Parent
		Node* cur = Root; 

		if (Root->Key == value)
		{
			Root = Merge(cur->Left, cur->Right);
			return;
		}

		while (value != last->Key && (last->Left || last->Right))
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
		/////////////////////////////
		
		if (cur->Key == value)
		{
			if (last->Left == cur)
				last->Left = Merge(cur->Left, cur->Right);
			else if (last->Right == cur)
				last->Right = Merge(cur->Left, cur->Right);
		}	
	}
}

Treap::Node* Treap::Find(int const value)const
{
	Node* last = Root;
	while (value != last->Key && (last->Left || last->Right))
	{
		if (value < last->Key)
			last = last->Left;
		else if (value > last->Key)
			last = last->Right;
	}
	if (value == last->Key)
		return last;
	else
		return nullptr;
}
int Treap::FindCount(int const value)const
{
	Node* last = Root;
	size_t cur = value;
	size_t lcount = 0;
	if (last->Left) lcount = last->Left->Count;
	size_t rcount = 0;
	if (last->Right) rcount = last->Right->Count;

	while ((last->Left || last->Right) && cur-1 != lcount)
	{
		if (cur-1 < lcount)
			last = last->Left;
		else if (cur <= last->Count && rcount)
		{
			last = last->Right;
			cur -= (1+lcount);
		}
    		//error case
		else return -1;

		lcount = 0;
		if (last->Left) lcount = last->Left->Count;
		rcount = 0;
		if (last->Right) rcount = last->Right->Count;
	}
	return last->Key;
}

Treap::Node* Treap::FindMin(int const value)const
{
	Node* cur = Root;
	while (cur->Left != nullptr)
		cur = cur->Left;
	return cur;
}

void Treap::DFS()const
{
	DFSN(Root);
	std::cout << std::endl;
	return;
}
void Treap::DFSN(Node* node)const
{
	if (!node) return;
	DFSN(node->Left);
	std::cout << node->Key << " ";
	DFSN(node->Right);
	return;
}

int main()
{
	srand(time(0));
	size_t n;
	std::cin >> n;
	int num;
	int k;
	Treap MyTreap;

	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> num >> k;

		if (num > 0)
			MyTreap.Insert(num);
		else if (num < 0)
			MyTreap.DeleteNode(-num);

		std::cout << MyTreap.FindCount(k+1) << std::endl;
		//MyTreap.DFS();
	}
	system("pause");
	return 0;
}
