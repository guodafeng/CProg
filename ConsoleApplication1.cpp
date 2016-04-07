// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <functional>
#include <vector>
#include <iterator>
#include <stdarg.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <assert.h>

using namespace std;
int randint(int a, int b)
{
	return (rand() % (b - a)) + a;
}
void printArray(const int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ", ";
	}
	cout << endl;
}
int* rand_array(int size, int valMin, int valMax)
{
	srand(time(0));
	int * res = new int[size];
	for (int i = 0; i < size; i++)
	{
		res[i] = randint(valMin, valMax);
	}
	return res;
}
//Node relationship for Cube
const int linkedP[8][3] = {
{ 1, 3, 4 },
{ 0, 2, 5 },
{ 1, 3, 7 },
{ 0, 2, 7 },
{ 0, 5, 7 },
{ 1, 4, 6 },
{ 2, 5, 7 },
{ 3, 4, 6 }
};

//Node relateionship for 3-Vertebra
//const int linkedP[4][3] = {
//	{ 1, 2, 3 },
//	{ 0, 2, 3 },
//	{ 0, 1, 3 },
//	{ 0, 1, 2 }
//};

const int STEPS = 5; //Steps inputsizeber Ant will walk
const int START = 0; //Start point of the Ant
const int DEST = 6;; //Destination point of the Ant

int allRoutines = 0;
int correctRoutines = 0;

void GoNextP(const int step, const int curP)
{
	for (int i = 0; i < sizeof(linkedP[curP])/sizeof(int); i++)
	{
		if (step <= 1) // the last step
		{
			allRoutines++;
			if (linkedP[curP][i] == DEST)
				correctRoutines++;
		}
		else
		{
			GoNextP((step - 1), linkedP[curP][i]);
		}
	}
}

//Use recursive function call
void f1()
{
	GoNextP(STEPS, START);
	cout << "Number of all routines are:" << allRoutines << endl;
	cout << "Number of correct routines are:" << correctRoutines << endl;
}

// Use for loop, need add loop if steps increased
void f2()
{
	for (int i1 = 0; i1 < sizeof(linkedP[0]) / sizeof(int); i1++)
	{
		//first step
		int secondP = linkedP[START][i1];
		for (int i2 = 0; i2 < sizeof(linkedP[0]) / sizeof(int); i2++)
		{
			//second step
			int thirdP = linkedP[secondP][i2];

			allRoutines++;
			if (thirdP == DEST)
				correctRoutines++;
		}
	}
	cout << "Number of all routines are:" << allRoutines << endl;
	cout << "Number of correct routines are:" << correctRoutines << endl;

}

// use stack, equal with recursive function call
void f3()
{
	struct StepInfo{
		int stepNum;
		int nodeP;
	};
	stack<StepInfo> stepStack;
	StepInfo curStep;

	int allRoutines = 0;
	int correctRoutines = 0;

	curStep.stepNum = 0;
	curStep.nodeP = START;
	while (1)
	{
		int stepNum = ++(curStep.stepNum);
		int curP = curStep.nodeP;

		for (int i = 0; i < sizeof(linkedP[0]) / sizeof(int); i++)
		{
			if (stepNum < STEPS)
			{
				StepInfo nextStep;
				nextStep.stepNum = stepNum;
				nextStep.nodeP= linkedP[curP][i];
				stepStack.push(nextStep);
			}
			else
			{
				allRoutines++;
				if (linkedP[curP][i] == DEST)
					correctRoutines++;
			}
		}

		if (stepStack.size() == 0)
			break;

		curStep = stepStack.top();
		stepStack.pop();

	}

	cout << "Number of all routines are:" << allRoutines << endl;
	cout << "Number of correct routines are:" << correctRoutines << endl;

}

const int TABLESIZE = 8;

//queen 
//marked array - value is marked coloum, index is marked row
bool IsMarkable(int* marked, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (marked[i] == col)
			return false;
		else if (abs(row - i) == abs(col - marked[i]))
			return false;
	}
	return true;
}
void PrintMarked(int* marked)
{
	static int count = 0;
	cout << "The" << ++count << "solution:" << endl;
	for (int i = 0; i < TABLESIZE; i++)
	{
		for (int j = 0; j < TABLESIZE; j++)
		{
			//cout << "|";
			if (marked[i] == j)
				cout << "Q";
			else
				cout << "I";
		}
		cout << endl;
	}
	cout << endl;
}
void MarkQueen(int row)
{
	static int marked[TABLESIZE];
	if (row >= TABLESIZE)
	{
		PrintMarked(marked);
	}
	for (int i = 0; i < TABLESIZE; i++)
	{
		if (IsMarkable(marked, row, i))
		{
			marked[row] = i;
			MarkQueen(row+1);
		}
	}
}

//quicksort
//
int x[] = { 45, 1, 9, 2, 40, 20, 21, 8, 15, 13 ,6,23,44};

void swap(int m, int n)
{
	if (m == n)
		return;
	int t = x[m];
	x[m] = x[n];
	x[n] = t;
}

void quicksort(int l, int u)
{
	int i, m;
	if (l >= u) return;
	int randinputsize = randint(l, u);
	cout << x[randinputsize] << endl;
	swap(l, randinputsize);
	m = l;
	for (i = l + 1; i <= u; i++)
		if (x[i] < x[l])
			swap(++m, i);

	swap(l, m);


	printArray(x, sizeof(x) / sizeof(int));

	quicksort(l, m - 1);
	quicksort(m + 1, u);
}

void testvar(int n, ...)
{
	va_list vap;
	va_start(vap, n);
}


void test_quicksort()
{
	cout << "the array to be sorted is:";
	printArray(x, sizeof(x) / sizeof(int));
	
	quicksort(0, sizeof(x) / sizeof(int) -1);
	cout << "the array sorted result is:";
	printArray(x, sizeof(x) / sizeof(int));

}


double my_itof(const char* inst)
{
	bool meetdot = false;
	double result = 0;
	int factor = 0;
	for (int i = 0; inst[i]!='\0'; i++)
	{
		if (inst[i] == '.')
		{
			meetdot = true;
			factor = 10;
			continue;
		}
		if (meetdot)
		{
			result += (double)(inst[i] - '0')/factor;
		}
		else
		{
			result *= 10;
			result += inst[i] - '0';
		}
	}
	return result;
}

void test_itof()
{
	string str;
	cout << "input the string for transfer:";
	while (cin>>str)
	{
		double res = my_itof(str.c_str());
		cout << "resultis:" << setprecision(6) << fixed << res << endl<<endl<<"input the string for transfer:";
	}
}

//todo:
double calc_expression(const char* express)
{
	int bracelevel = 0;
	int i = 0;
	while (express[i] != '\0')
	{
		
		i++;
	}
	return 0;
}
struct item
{
	int value;
	int size;
};



int* max_01_bag(const item *items, const int iteminputsize, const int bagsize)
{
	int *maxvalues = new int[(iteminputsize+1)*(1+bagsize)];
	
	for (int i = 0; i < (iteminputsize + 1)*(1 + bagsize); i++)
	{
		maxvalues[i] = 0;
	}
  
	for (int i = 1; i <= iteminputsize; i++)
	{
		for (int j = 1; j <= bagsize; j++)
		{
			int val2 = maxvalues[(i - 1)*(bagsize + 1) + j];

			if (j >= items[i-1].size)
			{
				int val1 = maxvalues[(i - 1)*(bagsize + 1) + j - items[i-1].size] + items[i-1].value;
				if (val1 > val2)
				{
					maxvalues[i*(bagsize + 1) + j] = val1;
				}
				else
				{
					maxvalues[i*(bagsize + 1) + j] = val2;
				}
			}
			else
			{
				maxvalues[i*(bagsize + 1) + j] = val2;

			}

		}
	}

	//
	return maxvalues;
}
void test_01_bag()
{
	item items[] = { { 5, 2 }, { 5, 3 }, { 11, 4 }, { 14, 5 }, { 19, 6 }, { 7, 2 }, { 9, 3 }, { 2, 1 }, { 7, 1 } };
	const int MAX_BAGSISE = 15;
	const int ITEMNUM = sizeof(items) / sizeof(item);
	int* maxvalues = max_01_bag(items, ITEMNUM, MAX_BAGSISE);

	//print maxvalues , and the selected items
	for (int i = 2; i <= MAX_BAGSISE; i++)
	{
		cout << "Bag size is " << i << " and the max values can be put in the bag is " << maxvalues[ITEMNUM*(MAX_BAGSISE + 1) + i] << endl;
		cout << "The selected items are:";
		int sizeremain = i;
		for (int j = ITEMNUM; j >0 ; j--)
		{
			if (maxvalues[j*(MAX_BAGSISE + 1) + sizeremain] > maxvalues[(j - 1)*(MAX_BAGSISE + 1) + sizeremain])
			{
				cout << setw(4) << j;
				sizeremain -= items[j - 1].size;

			}
		}
		cout << endl<<endl;

	}

	//print maxmvales for debuging
	for (int i = 1; i <= ITEMNUM; i++)
	{
		for (int j = 1; j <= MAX_BAGSISE; j++)
		{
			cout << setw(4)<<maxvalues[i*(MAX_BAGSISE + 1) + j] << "  ";

		}
		cout << endl;
	}

	delete maxvalues;
}
void swap(char* p, char* q, const int n)
{
	char c;
	for (int i = 0; i < n; i++,p++,q++)
	{
		c = *p;
		*p = *q;
		*q = c;
	}
}
void reversed(char *str, const int d)
{
	int n = strlen(str);
	if (d == 0 || d == n)
		return;
	int i = d, p = d;
	int	j = n - p;
	while (i != j)
	{
		if (i > j)
		{
			swap(&str[p - i], &str[p], j);
			i -= j;
		}
		else{
			swap(&str[p - i], &str[p + j - i], i);
			j -= i;
		}
	}
	swap(&str[p - i], &str[p], i);
			
}
void test_reversed()
{
	char str[] = "abcdefg";
	reversed(str, 4);
	cout << str << endl;
}

void test_pointerarray()
{
	char a[6] = "abcde";
	char (*p)[6] = &a;

	cout << "p=" << hex << p << "; *p=" << hex<<(int)(*p) << "; *p+1=" << (*p + 1) << endl;

}


int max_subarray(const int* vals, const int len)
{
	int maxVal = INT_MIN;
	int *curVals = new int[len];
	memset(curVals, 0, len*sizeof(int));
	int curVal = 0;

	for (int i = 0; i < len; i++)
	{
		curVal += vals[i];
		curVals[i] = curVal;
		if (curVal > maxVal)
			maxVal = curVal;

		if (curVal < 0)
			curVal = 0;
	}


	//print the sub array
	for (int i = len - 1; i >= 0; i--)
	{
		if (curVals[i] == maxVal)
		{ 
			int first = i,last = i;
			
			for (int j = i-1; j >= 0; j--)
			{
				if (curVals[j] < 0)
				{
					first = j + 1;
					break;
				}
			}

			printArray(&vals[first], last - first + 1);

			break;
		}

	}

	delete curVals;
	return maxVal;

}

void test_max_subarray()
{
	int iarr[] = { -10, -2, 4, -5, 3,5,7,-9,10 ,5,-3,12,-11,-4,20,-2,-98};

	cout << "The maxvalue of sub array is:" << max_subarray(iarr, sizeof(iarr)/sizeof(int));

}

struct NODE{
	NODE* pLeft;
	NODE* pRight;
	char chValue;
};
void Rebuild(const char* pPreOrder, const char* pInOrder, const int nLen, NODE** pRoot)
{
	if (nLen <= 0) *pRoot = 0;
	else
	{
		NODE* root = new NODE();
		root->pLeft = 0;
		root->pRight = 0;
		root->chValue = *pPreOrder;
		*pRoot = root;

		//find the root in pInorder
		int rootPos = -1;
		for (int i = 0; i < nLen; i++)
			if (pInOrder[i] == pPreOrder[0])
			{
				rootPos = i;
				break;
			}

		Rebuild(pPreOrder + 1, pInOrder, rootPos, &(root->pLeft));
		Rebuild(pPreOrder + rootPos+ 1, pInOrder+rootPos+1, nLen -1 -rootPos, &(root->pRight));
	}
}

void PreVisit(NODE* root)
{
	if (root != 0)
	{
		cout << root->chValue << " ";
		PreVisit(root->pLeft);
		PreVisit(root->pRight);
	}
}

void InVisit(NODE* root)
{
	if (root != 0)
	{
		InVisit(root->pLeft);
		cout << root->chValue << " ";
		InVisit(root->pRight);
	}
}

void test_Rebuild()
{
	char preOrder[] = "abdcef";
	char inOrder[] = "dbaecf";

	NODE* rootNode = 0;

	Rebuild(preOrder, inOrder, sizeof(preOrder) / sizeof(char), &rootNode);

	cout << "the Previsit result is:";
	PreVisit(rootNode);
	cout << endl;
	cout << "the InVisit result is:";
	InVisit(rootNode);
}
//merge sort
int* do_merge(int* left, int leftsize, int* right, int rightsize)
{
	int* res = new int[leftsize + rightsize];
	int l(0),r(0);
	for (int i = 0; i < leftsize+rightsize; i++)
	{   
		
		if (l < leftsize && r < rightsize)
		{
			if (left[l] <= right[r])
			{
				res[i] = left[l++];
			}
			else
			{
				res[i] = right[r++];
			}
		}
		else if (l < leftsize)
			res[i] = left[l++];
		else if (r < rightsize)
			res[i] = right[r++];
	}
	return res;
}
void merge_sort(int* vals, int size)
{
	if (size > 1)
	{
		int* left = vals;
		int leftsize = size / 2;
		int rightsize = size - leftsize;
		int* right = vals + leftsize;

		merge_sort(left, leftsize);
		merge_sort(right, rightsize);

		int *res = do_merge(left, leftsize, right, rightsize);
		for (int i = 0; i < size; i++)
			vals[i] = res[i];
		delete res;
	}
}

void test_merge_sort()
{
	int* res1 = rand_array(20, 5, 100);
	
	cout << "the array to be sorted:";
	printArray(res1, 20);
	merge_sort(res1, 20);
	cout << endl << "sorted result is: ";
	printArray(res1, 20);

}
//end merge sort

void test_fread()
{
	FILE * stream=0;
	fopen_s(&stream, "f:\\test.dat", "r");
	if (stream == 0)
		return ;


	__int64 iValue1(0), iValue2(0);

	fscanf_s(stream, "%08X\n", &iValue1);
	fscanf_s(stream, "%08X\n", &iValue2);

}
void revertstr(char* str, int begin, int end)
{
	char tmp;
	int len = end - begin;
	for (int i = 0; i < len / 2; i++){
		tmp = str[begin + i];
		str[begin + i] = str[begin +len - i - 1];
		str[begin+len - i - 1] = tmp;
	}
}

void revertsentencinword(char* sentence)
{
	//revert each word first
	char wordbound[] = "	 ,.?!;";
	int begin_w(-1), end_w(-1);
	int len = strlen(sentence);
	for (int i = 0; i < len; i++)
	{
		if (begin_w < 0 && strchr(wordbound, sentence[i]) ==0)
		{
			begin_w = i;
		}
		if (begin_w >= 0 && (strchr(wordbound, sentence[i+1]) !=0 || i+1 == len))
		{
			end_w = i + 1;
			revertstr(sentence, begin_w, end_w);
			begin_w = -1;
			end_w = -1;
		}

	}
	revertstr(sentence, 0, len);
}
void test_revertstr()
{
	char str[1000] = "\0";
	cin.getline(str,1000);

	revertsentencinword(str);
	
	cout << str << endl;
}
//test constructor init
class A{
protected:
	int pa;
public:
	int a;
};

class B :public A{
public:
	B(int i);
	int b;
};

B::B(int i) : b(i){
	cout << "B created";
	a = 3;
}

//------24 caculate
int* merge2input(int* input, int inputsize, int index1, int index2, char op){
	int newvalue = 0;
	switch (op)  {
	case '+':
		newvalue = input[index1] + input[index2];
		break;
	case '-':
		newvalue = input[index1] - input[index2];
		break;
	case '/':
		newvalue = input[index1] / input[index2];
		break;
	case '*':
		newvalue = input[index1] * input[index2];
		break;
	default:
		break;
	}
	int * retarr = new int[inputsize - 1];
	retarr[0] = newvalue;
	for (int i = 0, j = 1; i < inputsize; i++)
	{

		if (i != index1 && i!=index2) retarr[j++] = input[i];
	}
	return retarr;
}
int* removeat(int* input, int inputsize, int index)
{
	int* retarr = NULL;
	if (inputsize > 1 && index >= 0 && index < inputsize)
	{
		retarr = new int[inputsize - 1];
		for (int i=0,j = 0; i < inputsize; i++)
		{
			if (i != index) retarr[j++] = input[i];
		}
	}
	return retarr;
}
std::stack<string> s_exp;
const int LEN = 32;
char oneexp[LEN];
char ops[] = { '+', '-', '*', '/'};
char ops_r[] = { '-', '+', '/', '*' };
void outputexp(stack<string> s)
{
	while (!s.empty()){
		cout << s.top();
		s.pop();
	}
	cout << endl;
}
float getnextval(float val, int input, char op){
	switch (op)  {
	case '+':
		return val + input;
	case '-':
		return val - input;
	case '/':
		return val / input;
	case '*':
		return val * input;
	}
}
string cacu(int* input, int inputsize, float val )
{
	if (inputsize == 1 && input!=NULL)
	{
		if (abs(val - *input) < 0.001)
		{
			_snprintf_s(oneexp, LEN, "%d", *input);
			return oneexp;
		}
		else
			return "";
	}

	for (int i = 0; i < inputsize; i++)
	{
		int* nextinput = removeat(input, inputsize, i);
		for (int j = 0; j < sizeof(ops) / sizeof(char); j++)
		{
			_snprintf_s(oneexp, LEN, " %c %d", ops_r[j], input[i]);
			string subexp2 = oneexp;
			float nextval = getnextval(val, input[i], ops[j]);
			string subexp = cacu(nextinput, inputsize - 1, nextval);
			string finalexp;
			if (subexp.length()>0)
			{
				if (ops[j] == '/' || ops[j] == '*')
					finalexp = string("(") + subexp + string(")") + subexp2;
				else
					finalexp = subexp + subexp2;
				return finalexp;
			}
		}
		delete nextinput;
	}
	return "";
}

void cacu_all(int* input, int inputsize, float val)
{
	if (inputsize == 1 && input!=NULL)
	{
		if (abs(val - *input) < 0.001)
		{
			_snprintf_s(oneexp, LEN, "%d", *input);
			s_exp.push(oneexp);
			outputexp(s_exp);
			s_exp.pop();
		}
	}

	for (int i = 0; i < inputsize; i++)
	{
		int* nextinput = removeat(input, inputsize, i);
		for (int j = 0; j < sizeof(ops) / sizeof(char); j++)
		{
			if (input[i] == 0 && ops_r[j] == '/')
				continue;

			_snprintf_s(oneexp, LEN, " %c %d", ops_r[j], input[i]);
			s_exp.push(oneexp);
			float nextval = getnextval(val, input[i], ops[j]);

			cacu_all(nextinput, inputsize - 1, nextval);

			s_exp.pop();
		}
		delete nextinput;
	}
	if (inputsize < 4) return; //no need to check 2-composed values under the condition

	for (int i = 0; i < inputsize; i++)
	{
		for (int j = i + 1; j < inputsize; j++){
			for (int k = 0; k < sizeof(ops) / sizeof(char); k++)
			{
				if (input[j] == 0 && ops[k] == '/')
					continue;
				int* nextinput = merge2input(input, inputsize, i, j, ops[k]);
				_snprintf_s(oneexp, LEN, "(%d %c %d)", input[i], ops[k], input[j]);
				s_exp.push(oneexp);
				cacu_all(nextinput, inputsize - 1, val);
				s_exp.pop();
			}
		}
	}
}
void test_cacu()
{
	while (1){
		cout << "please input numbers to be caculated, seprated by space, the dest value is 24." << endl;
		string str;
		getline(cin, str);

		stringstream ss(str);
		vector<int> vec;

		int Integer;
		while (true)
		{
			ss >> Integer;
			if (!ss)
				break;

			vec.push_back(Integer);
		}
//		cout << "the expression is:" << cacu(vec.data(), vec.size(), 24, true) << endl;
		cacu_all(vec.data(), vec.size(), 24);
	}
}
//

//------
class Exp
{
	Exp* subExpl;
	Exp* subExpr;
	char op;
	float value;
public:
	float getvalue()
	{
		return value;
	}
	Exp(){};
	Exp(float val)
	{
		value = val;
		subExpl = subExpr = NULL;
		op = 0;
	}
	Exp(Exp* expL, Exp* expR, char op_in)
	{
		subExpl = expL;
		subExpr = expR;
		op = op_in;
	
		switch (op){
		case '+':
			value = expL->value + expR->value;
			break;
		case '-':
			value = expL->value - expR->value;
			break;
		case '*':
			value = expL->value * expR->value;
			break;
		case '/':
			value = expL->value / expR->value;
			break;
		default:
			assert(false);
		}
	}

	string toString()
	{
		if (subExpl && subExpr)
		{
			return string("(") + subExpl->toString() + op + subExpr->toString() + string(")");
		}
		else
		{
			stringstream ss;
			ss << value;
			return ss.str();
		}
	}
};
void mergeexps(Exp* const exps, int size, int lindex, int rindex, char op, Exp*  outexps)
{
	Exp* first = new((void*)&(outexps[0]))Exp(&(exps[lindex]), &(exps[rindex]), op);
	for (int i = 0; i < size; i++)
	{
		if (i == lindex || i == rindex)
			continue;
		*(++outexps) = exps[i];
	}
}

void calcnew(Exp* exps, int expsnum)
{
	if (expsnum == 1){
		if (fabs(exps->getvalue() - 24) < 0.0001)
		{//get the expected result, output the expression
			string a;
			cout << exps->toString();
			cout << endl;
		}
		return;
	}

	//caculate 2 exps to 1 exp
	Exp* merged_exps = new Exp[expsnum - 1];
	for (int i = 0; i < expsnum; i++)
	{
		for (int j = i + 1; j < expsnum; j++)
		{
			for (int k = 0; k < sizeof(ops) / sizeof(char); k++)
			{
				//skip the condition div by 0 
				if ((fabs(exps[j].getvalue()) < 0.0001 && ops[k] == '/') || (fabs(exps[i].getvalue()) < 0.0001 && ops[k] == '$'))
					continue;

				mergeexps(exps, expsnum, i, j, ops[k], merged_exps);
				calcnew(merged_exps, expsnum - 1);

				if (ops[k] == '-' || ops[k] == '/')
				{
					//swap the left and right
					mergeexps(exps, expsnum, j, i, ops[k], merged_exps);
					calcnew(merged_exps, expsnum - 1);
				}
			}

		}
	}
	delete merged_exps;
}
void test_cacunew()
{
	while (1){
		cout << "please input numbers to be caculated, seprated by space, the dest value is 24." << endl;
		string str;
		getline(cin, str);

		stringstream ss(str);
		vector<Exp> vec;

		int Integer;
		while (true)
		{
			ss >> Integer;
			if (!ss)
				break;

			Exp exp(Integer);
			vec.push_back(exp);
		}
		calcnew(vec.data(), vec.size());
	}
}
//----------

int _tmain(int argc, _TCHAR* argv[])
{
	//cout << "-----------------Use recursive function call to implement-------------------------" << endl;
	//f1();
	////f2();
	//cout << "-------------------Use stack to implement--------------------------------------" << endl;
	//f3();
	//8-queen problem
	//MarkQueen(0);

	//test_quicksort();
	//test_itof();
	//test_01_bag();
	///test_reversed();
	//test_pointerarray();

	//test_max_subarray();
	//test_Rebuild();
	//test_merge_sort();
	//test_revertstr();
	test_cacunew();
	return 0;
}

