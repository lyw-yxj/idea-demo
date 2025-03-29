#include<stdio.h>
#include<stdlib.h>
typedef struct Listlink
{
	struct Listlink* next;
	struct Listlink* prenext;
	int  data;

}Plist;
//申请节点
Plist* BuildNode(int x)
{
	Plist* Seplist = (Plist*)malloc(sizeof(Plist));
	if (Seplist == NULL)
	{
		printf("out of space");
		exit(1);

	}
	Seplist->prenext = Seplist->next;
	Seplist->data = x;
	return Seplist;
	
}
//判断是否为空
int ListEmperty(Plist* Head)
{
	if (Head->next == Head)
	{
		return 0;
	}
}
//打印双链表
void PrintList(Plist* Head)
{
	if (Head->next == Head)
	{
		exit(1);

	}
	Plist* Node = Head->next;
	while(Node!=Head)
	{
		Node = Node->next;
		print("%d", Node->data);

	}

}
//创建双链表
Plist* InList()
{
	int x;
	Plist* newList = BuildNode(x);
	return newList;

}

//尾插
int insert(Plist* Head, int x)
{
	if (Head->next == Head)
	{
		return -1;

	}
	Plist *NewNode = BuildNode(x);
	NewNode->next = Head;
	NewNode->prenext= Head->prenext;
	Head->prenext = NewNode;
	Head->prenext->next = NewNode;
	return 0;

}
//头插
int FinsertLink(Plist* Head, int x)
{
	Plist* Newnode = (Plist*)malloc(sizeof(Plist));
	if (Newnode == NULL)
	{
		printf("error");
		return -1;
	}
	Newnode->data = x;
	Newnode->next = Head->next;
	Newnode->prenext = Head;
	Head->next->prenext = Newnode;
	Head->next = Newnode;
	return 0;
}

//尾删
int deleteLink(Plist *Head)
{
	Plist* insert = Head->prenext;
	if (Head->next == Head)
	{

		printf("error");
		return -1;

	}
	insert->prenext->next = Head;
	Head->prenext = insert->prenext;
	free(insert);
	return 0;


}
//头删
int Pdeletelist(Plist* Head)
{

	if (Head->next == Head)
	{
		printf("error");
		return -1;

	}
	Plist* delete = Head->next;
	delete->next->prenext = Head;
	Head->next = delete->next;
	free(delete);
	return 0;

}
//查找
Plist* Find(Plist* Head,int x)
{
	
	Plist* Newnode = Head->next;
	if (Head->next ==Head)
	{
		printf("error");
		return -1;

	}
	while (Newnode->next != Head)
	{
		Newnode = Newnode->next;
		if (Newnode->data == x)
		{
			break;

		}
	}
	if (Newnode ->next == Head)
	{
		printf("out of space");
		return -1;

	}
	return Newnode;

}
//指定位置插入结点
int insertpre(Plist* pnode, Plist* Head, int x)
{
	Plist* newnode = BuildNode(x);

	if (pnode->next == Head)
	{
		printf("error");
		return -1;

	}
	newnode->next = pnode->next;
	newnode->prenext = pnode;
	pnode->next = newnode;
	pnode->next->prenext = newnode;
	return 0;


}
//删除指定位置的链表
int deleteposition(Plist* pnode,Plist*Head)
{

	if (pnode->next == Head)
	{
		printf("error");
		return -1;

	}
	pnode->next->prenext = pnode->prenext;
	pnode->prenext->next = pnode->next;
	free(pnode);
	return 0;



}
//销毁链表
void destroy(Plist* Head)
{
	if (Head->next == Head)
	{
		printf("error");
		return -1;

	}
	Plist *current = Head->next;
	Plist* Pnode = Head->next;

	while(current->next != Head)
	{
		free(current);
		current = Pnode;

	}
}