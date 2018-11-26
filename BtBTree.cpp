#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
#include <iomanip>
#include <conio.h>

typedef struct NODE
{
	int info;
	NODE* pleft;
	NODE* pright;
};

typedef struct BNODE
{
	NODE* root = NULL;
};

NODE* createNode(int x)
{
	NODE* p = new NODE;
	p->info = x;
	p->pleft = NULL;
	p->pright = NULL;
	return p;
}
// debug cac function sau khi return thi no tiep tuc thuc hien function 
int insertNode(NODE* &p, int x)
{
	if (p != NULL)
	{
		if (x == p->info)
			return -1;
		if (x < p->info)
			return insertNode(p->pleft, x);
		else
			return insertNode(p->pright, x);
	}
	else
	{
		p = createNode(x);
		if (p != NULL)
			return 1;
		else
			return 0;
	}
}

void createBTree(BNODE &btree)
{
	int x;
	while (true)
	{
		printf("Nhap gia tri: ");
		scanf("%d", &x);
		if (x == 0)
		{
			printf("Ban da ket thuc viec nhap du lieu\n");
			break;
		}
		else
		{
			int kq = insertNode(btree.root, x);
			if (kq == -1)
				printf("Du lieu nhap vao bi trung\n");
			else if (kq == 0)
				printf("Khong tao duoc Node chua du lieu\n");
		}
	}
}

void xuatBTree(NODE* p/*int k*/)
{
	if (p == NULL)
		return;
	xuatBTree(p->pleft /*k + 1*/);
	cout << p->info << ' ';
	xuatBTree(p->pright/* k + 1*/);
}

int search(NODE* p, int x)
{
	if (p != NULL)
	{
		if (x == p->info)
			return p->info;
		else if (x < p->info)
			return search(p->pleft, x);
		else
			return search(p->pright, x);
	}
	else
		return 0;
}

NODE* findMax(NODE* p)
{
	if (p->pright == NULL)
		return p;
	else
		return findMax(p->pright);
}

NODE* findMin(NODE* p)
{
	if (p->pleft == NULL)
		return p;
	else
		return findMin(p->pleft);
}

void searchStandFor(NODE* &q, NODE* &sf)
{
	if (sf->pleft != NULL)
		searchStandFor(q, sf->pleft);
	else
	{
		q->info = sf->info;
		q = sf;
		sf = sf->pright;
	}
}

void deleteNode(NODE* &p, int x)
{
	if (x < p->info)
		return deleteNode(p->pleft, x);
	else if (x > p->info)
		return deleteNode(p->pright, x);
	else
	{
		NODE* q = p;
		if (p->pleft == NULL && p->pright == NULL)
			p = NULL;
		else if (p->pleft == NULL)
			p = p->pleft;
		else if (p->pright == NULL)
			p = p->pright;
		else
		{
			searchStandFor(q, p->pright);
			delete q;
		}
	}
}

int main()
{
	BNODE btree;
	createBTree(btree);
	int k = 0;
	xuatBTree(btree.root);
	int soCanTim;
	printf("\nNhap so can tim: ");
	scanf("%d", &soCanTim);
	int kq = search(btree.root, soCanTim);
	if (kq == 0)
		printf("Khong tim thay du lieu\n");
	else
		printf("%d la so can tim\n", kq);
	printf("Gia tri lon nhat la: %d\n", findMax(btree.root)->info);
	printf("Gia tri nho nhat la: %d\n", findMin(btree.root)->info);
	int soCanXoa;
	printf("Nhap so can xoa: ");
	scanf("%d", &soCanXoa);
	deleteNode(btree.root, soCanXoa);
	xuatBTree(btree.root);
	_getch();
}