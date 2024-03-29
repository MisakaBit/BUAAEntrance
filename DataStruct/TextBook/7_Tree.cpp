﻿#include "7_Tree.hpp"

//打印每个元素
void PrintTreeNode(char c, int h, int index) {
	//基础空格
	int blank = 3;

	//用于标记是否为每行第一个元素
	bool flag = false;
	//确定元素所在行
	int line = 1;
	for (; line <= h; line++) {
		if (index <= pow(2, line - 1)) {
			if (index == pow(2, line - 1)) {
				flag = true;
			}
			else {
				line--;
			}
			break;
		}
	}

	//每个字母的空格倍数
	int itemblank = blank;
	for (int i = 1; i < h - line + 1; i++) {
		itemblank = itemblank * 2 + 1;
	}

	//每行开头字母的空格倍数
	int headblank = (itemblank - 1) / 2 - 1;
	if (flag) {
		//新的一行的回车数
		int changelinenum = (itemblank - 1) / 4;
		if (changelinenum < 1) {
			changelinenum = 1;
		}
		if (line == 1) {
			changelinenum = 1;
		}

		//先回车换行
		for (int j = 0; j < changelinenum; j++) {
			printf("\n");
		}
		//在打印空格到正确的位置
		for (int i = 0; i < headblank; i++) {
			printf(" ");
		}

		//最后打印每行的第一个元素
		printf("%c", c);
	}
	else {
		//先打印空格到正确的位置
		for (int i = 0; i < itemblank; i++) {
			printf(" ");
		}
		//打印元素
		printf("%c", c);
	}
}
//h为二叉树的高度
void PrintTree(BTree T, int h) {
	printf("\n");

	//二叉树元素序号
	int index = 0;

	queue<BTree> Q;

	//第一个元素先入队
	Q.push(T);

	//总数大于满二叉树最大值则退出循环
	while (index < pow(2, h) - 1) {
		BTNode* node = Q.front();
		Q.pop();
		index++;
		//将空的子树也入队，这样方便计算
		if (node == NULL) {
			Q.push(NULL);
			Q.push(NULL);
			//打印第index个元素
			PrintTreeNode(' ', h, index);
		}
		else {
			Q.push(node->lchild);
			Q.push(node->rchild);
			//打印第index个元素
			PrintTreeNode(node->data, h, index);
		}
	}

	printf("\n");
}

// <数据结构教程>p160 从字符串创建
BTree CreateBinTree(string s) {
	BTree stack[100] = {}, p = NULL, T = NULL;
	char ch = 0;
	int flag = 0, top = -1;
	for (char ch : s)
	{
		switch (ch)
		{
		case '@':
			return T;
		case ' ':
			break;
		case '(':
			stack[++top] = p;
			flag = 1;
			break;
		case ')':
			top--;
			break;
		case ',':
			flag = 2;
			break;
		default:
			p = (BTree)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = NULL;
			p->rchild = NULL;
			if (T == NULL)
				T = p;
			else if (flag == 1)
				stack[top]->lchild = p;
			else
				stack[top]->rchild = p;
			break;
		}
	}
	return NULL;
}
void CreateBinTreeTest() {
	BTree t = CreateBinTree("A(B(D, E(G)), C(F(, H)))@");
	PrintTree(t, 4);
}

// <数据结构教程>p161 从数组创建树
BTree BuildBinTree(int BT[]) {

	BTree T = (BTree)malloc(sizeof(BTNode));
	T->data = BT[0];
	T->lchild = NULL;
	T->rchild = NULL;

	BTree PTR[100] = { T };

	for (int i = 1; i < 100; i++) {
		if (BT[i] != 0) {
			PTR[i] = (BTree)malloc(sizeof(BTNode));
			T->data = BT[i];
			T->lchild = NULL;
			T->rchild = NULL;

			int j = (i - 1) / 2;
			if (i - 2 * j - 1 == 0)
				PTR[j]->lchild = PTR[i];
			else
				PTR[j]->rchild = PTR[i];
		}
	}
	return T;
}

// <数据结构教程>p162 递归求二叉树叶节点数目
int CountLeaf(BTree t) {
	if (t == NULL)
		return 0;
	if (t->lchild == NULL && t->rchild == NULL)
		return 1;
	return CountLeaf(t->lchild) + CountLeaf(t->rchild);
}

// <数据结构教程>p162 递归求二叉树深度
int BinTreeDepth(BTree t) {
	int leftdep = 0, rightdep = 0;
	if (t == NULL)
		return 0;
	else
	{
		leftdep = BinTreeDepth(t->lchild);
		rightdep = BinTreeDepth(t->rchild);
		if (leftdep > rightdep)
			return leftdep + 1;
		else
			return rightdep + 1;
	}
}

// <数据结构教程>p163 二叉树的三种递归遍历方式
// 前序
void PreOrder(BTree t) {
	if (t != NULL) {
		cout << t->data << " ";
		PreOrder(t->lchild);
		PreOrder(t->rchild);
	}
}
// 中序
void InOrder(BTree t) {
	if (t != NULL) {
		InOrder(t->lchild);
		cout << t->data << " ";
		InOrder(t->rchild);
	}
}
// 后序
void PostOrder(BTree t) {
	if (t != NULL) {
		PostOrder(t->lchild);
		PostOrder(t->rchild);
		cout << t->data << " ";
	}
}
void OrderTest() {
	BTree t = CreateBinTree("A(B(D, E(G)), C(F(, H)))@");
	PrintTree(t, 4);
	cout << endl;
	PreOrder(t);
	cout << endl;
	InOrder(t);
	cout << endl;
	PostOrder(t);
	cout << endl;
}

// <数据结构教程>p165 二叉树的非递归中序遍历
void InOrderNonRecursive(BTree t) {
	BTree stack[100] = {}, p = t;
	int top = -1;
	if (t != NULL) {
		while (!(p == NULL && top == -1)) {
			while (p != NULL) { // 首先一路进到左子树的尽头
				stack[++top] = p;
				p = p->lchild;
			}
			p = stack[top--]; // 取出栈顶
			cout << p->data << " "; // 栈顶作为没有child的中间节点输出
			p = p->rchild; // 进入右子树
		}
	}
}
// <数据结构教程>p167 二叉树的非递归后序遍历
void PostOrderNonRecursive(BTree t) {
	BTree stack[100] = {}, p = t;
	int flag_stack[100], flag = 0, top = -1;
	if (t != NULL) {
		while (!(p == NULL && top == -1)) {
			while (p != NULL) { // 首先一路进到左子树的尽头
				stack[++top] = p;
				flag_stack[top] = 0;
				p = p->lchild;
			}
			p = stack[top]; // 取出栈顶
			flag = flag_stack[top--];
			if (flag == 0) {
				stack[++top] = p;
				flag_stack[top] = 1;
				p = p->rchild;
			}
			else
			{
				cout << p->data << " ";
				p = NULL;
			}
		}
	}
}

// <数据结构教程>p169 二叉树的非递归层次遍历
void LayerOrder(BTree t) {
	if (t == NULL)
		return;

	BTree q[100] = { t }, p = NULL;
	int front = -1, rear = 0;
	while (front < rear) {
		p = q[++front];
		cout << p->data << " ";
		if (p->lchild != NULL)
			q[++rear] = p->lchild;
		if (p->rchild != NULL)
			q[++rear] = p->rchild;
	}
}

void OrderNonRecursiveTest() {
	BTree t = CreateBinTree("A(B(D, E(G)), C(F(, H)))@");
	PrintTree(t, 4);
	cout << endl;
	InOrder(t);
	cout << endl;
	InOrderNonRecursive(t);
	cout << endl;
	PostOrderNonRecursive(t);
	cout << endl;
	LayerOrder(t);
	cout << endl;
}

// <数据结构教程>p172 树的相似或等价的判定
bool Similar(BTree t1, BTree t2) {
	if (t1 == NULL && t2 == NULL)
		return true;
	if (t1 && t2 && Similar(t1->lchild, t2->lchild) && Similar(t1->rchild, t2->rchild))
		return true;
	return false;
}

// <数据结构教程>p174 遍历对二叉树的一系列操作
namespace walkbt {
	// 1.创建
	void BuildBT(BTree& t, queue<char>& q) {
		if (q.empty())
			return;

		char ch = q.front();
		q.pop();
		cout << ch;
		if (ch == ' ')
			t = NULL;
		else
		{
			t = (BTree)malloc(sizeof(BTNode));
			t->data = ch;
			BuildBT(t->lchild, q);
			BuildBT(t->rchild, q);
		}
	}
	// 2.销毁
	void DestoryBT(BTree t) {
		if (t != NULL) {
			DestoryBT(t->lchild);
			DestoryBT(t->rchild);
			free(t);
		}
	}
	void ClearBT(BTree& t) {
		DestoryBT(t);
		t = NULL;
	}
	// 3.复制
	BTree CopyBT(BTree t1) {
		if (t1 == NULL)
			return NULL;
		BTree t2 = (BTree)malloc(sizeof(BTNode));
		t2->data = t1->data;
		t2->lchild = CopyBT(t1->lchild);
		t2->rchild = CopyBT(t1->rchild);
		return t2;
	}
	// 4.等价
	bool EqualBT(BTree t1, BTree t2) {
		if (t1 == NULL && t2 == NULL)
			return true;
		if (t1 && t2
			&& t1->data == t2->data
			&& EqualBT(t1->lchild, t2->lchild)
			&& EqualBT(t1->rchild, t2->rchild)
			)
			return true;
		return false;
	}
	// 5.深度(非递归)
	int DepthBT(BTree t) {
		BTree stack1[100] = {}, p = t;
		int stack2[100] = {};
		int curdepth = 1, maxdepth = 0, top = -1;
		if (t == NULL)
			return maxdepth;
		while (!(p == NULL && top == -1)) {
			while (p != NULL) {
				stack1[++top] = p;
				stack2[top] = curdepth;
				p = p->lchild;
				curdepth++;
			}
			p = stack1[top];
			curdepth = stack2[top--];
			if (p->lchild == NULL && p->rchild == NULL)
				if (curdepth > maxdepth)
					maxdepth = curdepth;
			p = p->rchild;
			curdepth++;
		}
		return maxdepth;
	}
	// 6.层次(非递归)
	int LayerBT(BTree t, int item) {
		BTree stack1[100] = {}, p = t;
		int stack2[100] = {}, flag = 0, top = -1;
		while (!(p == NULL && top == -1)) {
			while (p != NULL) {
				stack1[++top] = p;
				stack2[top] = 0;
				p = p->lchild;
			}
			p = stack1[top];
			flag = stack2[top--];
			if (flag == 0) { // 后序遍历, 左右中
				stack1[++top] = p;
				stack2[top] = 1;
				p = p->rchild;
			}
			else
			{
				if (p->data == item)
					return top + 2;
				p = NULL;
			}
		}
		return -1;
	}
	// 7.删除(非递归)
	BTree DeleteBT(BTree& t, int item) {
		BTree stack[100] = {}, q = NULL, p = t;
		int top = -1;
		if (t->data == item) {
			DestoryBT(t);
			return NULL;
		}
		while (!(p == NULL && top == -1)) {
			while (p != NULL) {
				if (p->data == item) {
					if (q->lchild == p)
						q->lchild = NULL;
					else
						q->rchild = NULL;
					DestoryBT(p);
					return t;
				}
				stack[++top] = p;
				q = p;
				p = p->lchild;
			}
			p = stack[top--];
			q = p;
			p = p->rchild;
		}
	}
	// 8.交换(翻转二叉树)
	void ExchangeBT(BTree t) {
		if (t == NULL)
			return;
		BTree queue[100] = { t }, temp = NULL, p = t;
		int front = -1, rear = 0;
		while (front < rear) {
			p = queue[++front];
			temp = p->lchild;
			p->lchild = p->rchild;
			p->rchild = temp;
			if (p->lchild != NULL)
				queue[++rear] = p->lchild;
			if (p->rchild != NULL)
				queue[++rear] = p->rchild;
		}
	}

	void BTTest() {
		BTree t = NULL;
		queue<char> q;
		for (char item : "ABC  DE  F  G   ")
			q.push(item);
		BuildBT(t, q);
		PrintTree(t, DepthBT(t));
	}
}

// <数据结构教程>p182 中序线索二叉树的指定节点求直接前驱节点
TBTree InPrior(TBTree x) {
	TBTree s;
	s = x->lchild;
	// 当lbit==0的时候说明是s的直接前驱节点
	if (x->lbit == 1)
		// 不断找右子树, 当rbit==0的时候说明是s的直接前驱节点(绕了一圈?)
		while (s->rbit == 1)
			s = s->rchild;
	return s;
}

// <数据结构教程>p182 中序线索二叉树的指定节点求直接后继节点
TBTree InSucc(TBTree x) {
	TBTree s;
	s = x->rchild;
	// 当lbit==0的时候说明是s的直接前驱节点
	if (x->rbit == 1)
		// 不断找右子树, 当rbit==0的时候说明是s的直接前驱节点(绕了一圈?)
		while (s->lbit == 1)
			s = s->lchild;
	return s;
}

// <数据结构教程>p182 利用线索二叉树遍历二叉树
void TinOrder(TBTree head) {
	TBTree p = head;
	while (true) {
		p = InSucc(p);
		if (p == head)
			break;
		cout << p->data << " ";
	}
}

// TODO: 略过了线索二叉树的建立/更新 

// <数据结构教程>p187 二叉排序树的建立(非递归)
void InsertBST1(BTree& t, int item) {
	BTree newptr = (BTree)malloc(sizeof(BTNode));
	newptr->data = item;
	newptr->lchild = NULL;
	newptr->rchild = NULL;

	if (t == NULL)
		t = newptr;
	else {
		BTree q = t;
		while (true)
			if (item < q->data)
				if (q->lchild = NULL) {
					q->lchild = newptr;
					break;
				}
				else
					q = q->lchild;
			else
			{
				if (q->rchild == NULL) {
					q->rchild = newptr;
					break;
				}
				else
					q = q->rchild;
			}
	}
}
BTree SortTree(int k[], int n) {
	BTree t = NULL;
	if (n > 0)
		for (int i = 0; i < n; i++)
			InsertBST1(t, k[i]);
	return t;
}

// <数据结构教程>p188 二叉排序树的建立(递归)
void InsertBST2(BTree& t, int item) {
	if (t == NULL) {
		t = (BTree)malloc(sizeof(BTNode));
		t->data = item;
		t->lchild = NULL;
		t->rchild = NULL;
	}
	else
		if (item < t->data)
			InsertBST2(t->lchild, item);
		else
			InsertBST2(t->rchild, item);
}

// <数据结构教程>p190 二叉排序树的删除 要删除的节点是p, 其双亲节点是q
void DeleteBST(BTree& t, BTree p, BTree q) {
	if (p->lchild == NULL) {
		if (p == t)
			t = p->rchild;
		else if (p == q->lchild) // 要判断一下子节点是双亲节点的left还是right
			q->lchild = p->rchild;
		else
			q->rchild = p->rchild;
	}
	else if (p->rchild == NULL) {
		if (p == t)
			t = p->lchild;
		else if (p == q->lchild)
			q->lchild = p->lchild;
		else
			q->rchild = p->lchild;
	}
	else {
		BTree s = p, r = s->rchild;
		while (r->lchild != NULL) {
			s = r;
			r = r->lchild;
		}
		r->lchild = p->lchild;
		if (s != p) {
			s->lchild = r->rchild;
			r->rchild = p->rchild;
		}
		if (p == t)
			t = r;
		else {
			if (p == q->lchild)
				q->lchild = r;
			else
				q->rchild = r;
		}
	}
}

// <数据结构教程>p191 二叉排序树的查找(非递归)
BTree SearchBST1(BTree t, int item) {
	BTree p = t;
	while (p != NULL) {
		if (p->data == item)
			return p;
		if (item < p->data)
			p = p->lchild;
		else
			p = p->rchild;
	}
	return NULL;
}

// <数据结构教程>p192 二叉排序树的查找(递归)
BTree SearchBST2(BTree t, int item) {
	if (t == NULL)
		return NULL;
	if (t->data == item)
		return t;
	if (item < t->data)
		return SearchBST2(t->lchild, item);
	else
		return SearchBST2(t->rchild, item);
}

// TODO: 略过了平衡二叉树

// TODO: <数据结构教程>p202 哈夫曼编码
void HuffCode(int w[100], int weight[], int parent[], int lchild[], int start[], int code[][100], int n, int m) {

}

//int main() {
//	walkbt::BTTest();
//}

