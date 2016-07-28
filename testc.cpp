// testc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <queue>
using namespace std;
class A
{
	char b;
	char c;
	double d;
	int i;
};
class A1
{

	virtual void a()
	{
	}
	int d;
};
class B : public A, virtual public A1
{
};

class A2
{
	int a;
};
class B2
{
	int b;
};
class C2
{
	char c;
};
class D2:public C2
{
};
class E2 : public virtual A2, public virtual B2,  public virtual D2
{
};

class A3
{
};
class B3
{
	int b;
};
class C3
{
};
class D3
{
};
class E3 : public virtual A3, public virtual B3, public virtual C3, public virtual D3
{
};

class A4
{
	int a;
	int c[8];
};
class B4:virtual public A4
{
	int b;
};
class C4:virtual public A4
{
};
class E4 : public virtual B4, public virtual C4
{
};
class E42: public B4, public C4
{};


void find_theonly1repeated(int A[], int n) {
	int ones = 0;
	int twos = 0;
	int not_threes, x;

	for (int i = 0; i<n; ++i) {
		x = A[i];
		twos |= ones & x;
		ones ^= x;
		if (i == n - 1) {
			cout << ones << endl;
		}
		not_threes = ~(ones & twos);
		ones &= not_threes;
		twos &= not_threes;
	}
	cout << ones << endl;
}
//http://stackoverflow.com/questions/7338070/finding-an-element-in-an-array-where-every-element-is-repeated-odd-number-of-tim
void find_theonly3repeated(int A[], int n) {
	int ones = 0;
	int twos = 0;
	int not_threes, x;

	for (int i = 0; i<n; ++i) {
		x = A[i];
		twos |= ones & x;
		if (i == n - 1) {
			ones ^= x;
			cout << ones << endl;
			break;
		}
		not_threes = ~(ones & twos);
		ones &= not_threes;
		twos &= not_threes;
	}
	ones = 6;
	for (int i = 0; i < n; ++i)
	{
		x = A[i];
		ones ^= x;
	}

	cout << ones << endl;
}

void fiab(int n)
{
	int* fs = new int[n];
	fs[0] = 0;
	fs[1] = 1;
	cout << "0 1";
	for (int i = 2; i < n;i++) {
		fs[i] = fs[i - 1] + fs[i - 2];
		cout << " "<< fs[i]<<"'"<<double(fs[i])/fs[i-1]<<"'";
	}



}
int word_dist(char* str1, char* str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int* dists = new int[len1*len2];
	auto getdist = [dists,len2](auto r, auto c) {
		if (r < 0 && c < 0) return 0;
		if (r < 0 || c < 0) return 255;
		else
			return dists[r*len2 + c];
	};

	for (int i = 0; i < len1; i++)
	{
		for (int j = 0; j < len2; j++)
		{
			int ds1 = getdist(i, j - 1) + 1;
			int ds2 = getdist(i - 1, j) + 1;
			int ds3 = getdist(i - 1, j - 1) + ((str1[i] == str2[j]) ? 0 : 1);
			dists[i*len2 + j] = min(ds3, min(ds1, ds2));
			cout <<  setw(4) << dists[i*len2 + j] << " ";
		}
		cout << endl;
	}
	int ret = getdist(len1 - 1, len2 - 1);
	delete dists;
	return ret;
}
void test_worddist()
{
	char t1[5][255] = {  "computer","what","whatsapp","stupid","wonderfully" };
	char t2[5][255] = { "computor", "who","whoisa","clever","weather" };
	for (int i = 0; i < 5; i++)
	{
		cout << word_dist(t1[i], t2[i]) << endl << endl;
	}
}
void f_cpu() {
	while (1)
	{ 
		int j;
		for (int i=0;i<10000000;i++)
		{
			j = i;
		}
		Sleep(10);
	}
}
struct node {
	int value;
	node* next;
	node* sible;
};
node* initlist()
{
	const int size = 6;
	node *ps[6];
	for (int i = 0; i < size; i++)
	{
		ps[i] = new node();
		ps[i]->value = 'A' + i;
		ps[i]->next = nullptr;
		ps[i]->sible = nullptr;
		if (i > 0) {
			ps[i - 1]->next = ps[i];
		}
	}


	for (int i = 0; i < size; i++)
	{
		ps[i]->sible = ps[(i + 2) % 6];
	}
	return ps[0];
}
void print_nodep(node* p)
{
	while (p)
	{
		cout <<(char) p->value;
		if (p->sible)
		{
			cout << "   sible:" << (char)(p->sible->value);
		}
		cout << endl;
		p = p->next;

	}
}

void setclonesible(node* p)
{
	while (p) {
		node* clone = p->next;
		clone->sible = p->sible->next;
		p->next = clone->next;
		p = clone->next;
		if (p)	clone->next = p->next;
	}
}

node* clone(node* p)
{
	node* pclone = nullptr;
	if (p != nullptr)
	{
		pclone = new node();
		node* nextp = p->next;
		
		p->next = pclone;
		pclone->value = p->value;
		pclone->next = nextp;
		pclone->sible = nullptr;
		clone(nextp);
	}
	return pclone;
}

void testclonenode()
{
	node* head = initlist();
	print_nodep(head);
	node* clone_head = clone(head);
	setclonesible(head);
	cout << "print cloned node" << endl;
	print_nodep(clone_head);
}

struct node2 {
	node2* left;
	node2* right;
	int val;
};
node2* minNode(node2*p) {
	while (p->left) {
		p = p->left;
	}
	return p;
}
node2* maxNode(node2*p) {
	while (p->right) {
		p = p->right;
	}
	return p;
}
void convert(node2* p, node2** prenode)
{
	node2* l = p->left;
	node2* r = p->right;
	node2* head = nullptr;
	if (l)
	{
		convert(l, prenode);
	}

	if (*prenode) (*prenode)->right = p;
	p->left = *prenode;

	*prenode = p;
	if (r) {
		convert(r, prenode);
	}
}

void insert2bt(node2** head, int val)
{
	if (!(*head))
	{
		*head = new node2();
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
node2* initbtree(int ary[], int size)
{
	node2* head = nullptr;
	for (int i = 0; i < size; i++)
	{
		insert2bt(&head,ary[i]);
	}
	return head;
}


int getheight(node2* p)
{
	if (!p) return 0;
	int lh = getheight(p->left);
	int lr = getheight(p->right);
	return max(lh, lr) + 1;
}
void print_btree(node2* pTree)
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
		node2* p;
		int height_in_tree;
		int index;
	};
	queue<qnode> tmpQ;
	auto pushQ = [&tmpQ](node2* p, int height, int index) {
		if (p) {
			qnode q = { p, height,index };
			tmpQ.push(q);
		}
	};
	auto popQ = [&tmpQ](node2 *&p, int&height, int&index) {
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

	node2* pIter = pTree;
	int curIndex = 0;
	int curHeight = 1;
	while (pIter)
	{
		fillbuf(curHeight, curIndex, pIter->val + 'A');

		node2* left = pIter->left;
		node2* right = pIter->right;
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

//print btree - the first implementation
void print_node2(node2* p, const int pos)
{
	auto coutspace = [](int num) {for (int i = 0; i < num; i++) cout << " "; };
	int height = getheight(p);
	queue<node2*> qnode;
	queue<int> qpos;
	queue<int> qlevel;
	queue<int> qbranch; //record all branchs' position need to draw

	int prelevel = 0, curlevel = 0, curpos = 0;
	qnode.push(p);
	qpos.push(pos);
	qlevel.push(0);
	int prepos = 0;
	int width = 0;
	while (!qnode.empty())
	{
			p = qnode.front();
			qnode.pop();
			curpos = qpos.front();
			qpos.pop();
			curlevel = qlevel.front();
			qlevel.pop();

		if (curlevel > prelevel)
		{
			prelevel = curlevel;
			prepos = 0;
			cout << endl;
			int bpos1 = 0, bpos2 = 0;
			while (!qbranch.empty())
			{
				bpos2 = qbranch.front();
				coutspace(bpos2 - bpos1);
				cout << "/";
				coutspace(width);
				cout << "\\";
				bpos1 = bpos2 + width + 2;
				qbranch.pop();
			}
			cout << endl;
		}
		width = 1 << (height - curlevel - 2);
		coutspace(curpos - prepos);
		prepos = curpos + 1;
		cout << p->val;
		qbranch.push(curpos - width/2-1);

		if (p->left)
		{
			qnode.push(p->left);
			qpos.push(curpos - width);
			qlevel.push(curlevel + 1);
		}
		if (p->right)
		{
			qnode.push(p->right);
			qpos.push(curpos + width );
			qlevel.push(curlevel + 1);
		}
	}
	cout << endl;
}
void testnode2()
{
	//int ary[] = { 17, 5, 8, 3,9,4,2,6,7,1,0 ,11,20,24,16,18,19,23};
	int ary[] = { 10, 5,15,3,8,2,7,9,4,13,12,14};
	node2 *head = initbtree(ary, sizeof(ary)/sizeof(int));
	print_btree(head);
	node2* prenode = nullptr;
	convert(head, &prenode);
	int count = 0;
	while (prenode->left) {
		prenode = prenode->left;
		count++;
	}
	cout << "using prenode goback " << count << "steps" << endl;
	count = 0;
	while (head->left) {
		head = head->left;
		count++;
	}
	cout << "using head goback " << count << "steps" << endl;
	while (head)
	{
		cout << head->val << "=";
		head = head->right;
	}
}
int main()
{
	//cout << "sizeof(A)" << sizeof(A) << "sizeof(A1)" << sizeof(A1) << "sizeof(B)" << sizeof(B) << endl;
	//cout << "sizeof(C2)" << sizeof(C2) <<"sizeof(D2)"<<sizeof(D2)<< "sizeof(E2)" << sizeof(E2) << endl;
	//cout << "sizeof(A4)" << sizeof(A4) <<"sizeof(B4)"<<sizeof(B4)<<"sizeof(C4)"<<sizeof(C4)<< "sizeof(E4)3" << sizeof(E4) << "sizeof(E42)" << sizeof(E42) << endl;
	//int rds[] = { 5,7,5,8,3,9,11,5,5,5,7,8,3,11,9,11,9,7,8,3,22 };
	//int rds[] = { 5,9,9,9,21,5,5 };
	//find_theonly1repeated(rds, sizeof(rds)/sizeof(int));

	//int rds[] = { 2,13,29,13,14, 9,9,9 };
//	int rds[] = { 2,5,7,2,2,7,3,3,3 };
//	find_theonly1repeated(rds, sizeof(rds)/sizeof(int));
	//fiab(30);
	//f_cpu();
	//test_worddist();
	//testclonenode();
	testnode2();
	return 0;
}

