#include <iostream>
#include <queue>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	char val;
};
void insert2bt(Node** head, char val)
{
	if (!(*head))
	{
		*head = new Node();
		(*head)->left = nullptr;
		(*head)->right = nullptr;
		(*head)->val = val;
	}
	else
	{
		if (val > (*head)->val) {
			insert2bt(&((*head)->right), val);
		}
		else if(val < (*head)->val) 
		{
			insert2bt(&((*head)->left), val);
		}
	}
}
Node* initbtree(char ary[], int size)
{
	Node* head = nullptr;
	for (int i = 0; i < size; i++)
	{
		insert2bt(&head,ary[i]);
	}
	return head;
}
void freebtree(Node* p)
{
	if (!p)
		return;
	if (p->left)
		freebtree(p->left);
	if (p->right)
		freebtree(p->right);
	delete p;
}

int getheight(Node* p)
{
	if (!p) return 0;
	int lh = getheight(p->left);
	int lr = getheight(p->right);
	return max(lh, lr) + 1;
}

void print_btree(Node* pTree)
{
	int tree_height = getheight(pTree);
	int tree_width = (1 << tree_height) - 1;
	// / \ / \
	// A B C D  //height 3, width 7
	char* pBuf = new char[(2 * tree_height - 1)*(tree_width + 1)];
	for (int i = 0; i < (2 * tree_height - 1); i++)
	{
		for (int j = 0; j < tree_width; j++)
		{
			pBuf[i*(tree_width + 1) + j] = ' ';
		}
		pBuf[i*(tree_width + 1) + tree_width] = '\0';
	}
	//height count from 1, index count from 0
	auto fillbuf = [pBuf,tree_height,tree_width](int height, int index, char val) {
		int start = 1 << (tree_height-height);
		int pos = (index * 2 + 1)*start;
		pBuf[(height * 2 - 2)*(tree_width + 1) + pos] = val;
		if (height > 1)
		{
			if (index % 2 == 0)
			{
				pBuf[(height * 2 - 3)*(tree_width + 1) + pos + start / 2] = '/';
			}
			else
			{

				pBuf[(height * 2 - 3)*(tree_width + 1) + pos - start / 2] = '\\';
			}
		}
	};

	struct qnode {
		Node* p;
		int height_in_tree;
		int index;
	};
	queue<qnode> tmpQ;
	auto pushQ = [&tmpQ](Node* p, int height, int index) {
		if (p) {
			qnode q = { p, height,index };
			tmpQ.push(q);
		}
	};
	auto popQ = [&tmpQ](Node *&p, int&height, int&index) {
		if (!tmpQ.empty())
		{
			qnode q = tmpQ.front();
			p = q.p;
			height = q.height_in_tree;
			index = q.index;
			tmpQ.pop();
		}
		else
		{
			p = nullptr;
		}
	};

	Node* pIter = pTree;
	int curIndex = 0;
	int curHeight = 1;
	while (pIter)
	{
		fillbuf(curHeight, curIndex, pIter->val);

		Node* left = pIter->left;
		Node* right = pIter->right;
		pushQ(left, curHeight + 1, curIndex*2);
		pushQ(right, curHeight + 1, curIndex*2+1);
		popQ(pIter, curHeight, curIndex);
	}

	for (int i = 0; i < 2 * tree_height - 1; i++)
	{
		cout << &pBuf[i*(tree_width + 1)] << endl;
	}
	delete pBuf;
}
int main()
{
	char input[250];
	cin.getline(input, 250);
	Node* head = initbtree(input, strlen(input));
	print_btree(head);
	cin.get();
	
}
