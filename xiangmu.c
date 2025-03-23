#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct BookList
{
	
	char author[30];
	char name[20];
	int id;
	float price;
	int count;

}PBookList;
typedef struct Node* PNode;
struct Node
{
	PBookList info;
	PNode connect;

};
typedef struct Node* Linklist;
Linklist head;
typedef struct user
{
	char name[20];
	int password;
	int type;
}user;
Linklist CreateList(void)
{
	
	head = (Linklist)malloc(sizeof(struct Node));
	if (head == NULL)
	{

		printf("out of space\n");
		return 0;

	}
	head->connect = NULL;
	return head;
}

PNode Insertbook(Linklist head, char* author, char* name, int  bookid, float bookprice, int  count)
{
	PNode newbook = (PNode)malloc(sizeof(struct Node));
	PNode newnode = head;
	if (newbook == NULL)
	{
		printf("out of space\n");
		return 0;
	}

	strcpy(newbook->info.author,author);
	strcpy(newbook->info.name ,name);
	newbook->info.id = bookid;
	newbook->info.price = bookprice;
	newbook->info.count = count;
	newbook->connect = NULL;
	return newbook;
}
void Register_books(Linklist head, char *author, char *name, int bookid, float bookprice, int count)
{
	void readfile(Linklist head);
	PNode newbook = head;
	while (newbook->connect != NULL)
	{
		newbook = newbook->connect;
	}
	PNode tailnode = Insertbook(head, author, name, bookid, bookprice, count);
	newbook->connect = tailnode;
	readfile(head);

}

void borrow_book(Linklist head, int bookid)
{

	void readfile(Linklist head);
	PNode nextlist = head;
	int number = 0;
	if (head == NULL)
	{
		printf("out of space\n");
		exit(-1);

	}
	while (nextlist)
	{
		if (nextlist->connect)
		{
			if (nextlist->connect->info.id == bookid)
			{
				if (nextlist->connect->info.count > 0)
				{

					nextlist->connect->info.count = nextlist->connect->info.count - 1;
					number = 1;
					printf("�ѽ���%s %s\n", nextlist->connect->info.author, nextlist->connect->info.name);
					break;

				}
				else {
					printf("�ݲ��ѿ�\n");
					number = 1;
					break;
				}
			}
			else
				nextlist = nextlist->connect;
		}
		else {
			break;
		}
	}
	if (number == 0)
	{

		printf("û���ҵ���ͼ��\n");
	}

	readfile(head);

}



void return_books(Linklist head, int bookid , int count)
{
	void readfile(Linklist head);
	PNode nextlist= head->connect;
	if (head == NULL)
	{

		exit(0);

	}
	while (nextlist)
	{

		if (nextlist->info.id == bookid)
		{
			nextlist->info.count += count;
			break;
		}
		else
			nextlist = nextlist->connect;

	}

	readfile(head);

}
searchbookList(Linklist head, char* bookauthor, char* bookname)
{
	PNode newbook = head->connect;
	int number = 1;
	if (head == NULL)
	{

		return NULL;

	}
	while (newbook)
	{
		if (strcmp(newbook->info.author, bookauthor) == 0 && strcmp(newbook->info.name, bookname) == 0)
		{
			printf("���ҵ��鼮����ʾ����\n");
			number = 0;
			printf("%s %s %d %f %d\n", newbook->info.author, newbook->info.name, newbook->info.id, newbook->info.price,
				newbook->info.count);
			break;
		}

		else {
			newbook = newbook->connect;


		}
	}
	if (number == 1)
	{
		printf("û���ҵ�����\n");

	}

}
void sortdelete(Linklist head, int bookid)
{
	int number = 0;

	PNode newbook = head;
	PNode delete = (PNode)malloc(sizeof(struct Node));
	if (head == NULL)
	{

		exit(0);

	}
	while (newbook!=NULL)
	{

		if (newbook->connect->info.id == bookid)
		{
			printf("�ҵ����鼮��ɾ���ɹ�\n");
			delete = newbook->connect;
			newbook->connect = newbook->connect->connect;
			free(delete);
			number = 1;
			break;

		}
		else {


			newbook = newbook->connect;

		}

	}
	if (number == 0)
	{
		printf("û���ҵ����鼮\n");
	}

}
void print_book(Linklist head)
{
	PNode newbook = head->connect;
	if (head == NULL)
	{

		exit(0);

	}
	while (newbook)
	{

		printf("%s %s %d %f %d\n", newbook->info.author, newbook->info.name, newbook->info.id, newbook->info.price,
			newbook->info.count);
		newbook = newbook->connect;


	}

}
void Modify_book_information(Linklist head, int bookid)
{
	void readfile(Linklist head);
	char bookauthor[20], bookname[30];
	int count, bookidnew;
	float bookprice;
	int number = 0;
	PNode newbook = head->connect;

	if (head == NULL)
	{
		printf("����Ϊ�գ��޷��޸ģ�\n");
		exit(0);
	}

	while (newbook)
	{
		if (newbook->info.id == bookid)
		{
			printf("��������Ҫ�޸ĵ����\n");
			printf("1. ����\n");
			printf("2. ����\n");
			printf("3. ���\n");
			printf("4. ��Ǯ\n");
			printf("5. ����\n");
			printf("����0�����޸�\n");
			scanf("%d", &number);

			while (number != 0)
			{
				// ������뻺����
				while (getchar() != '\n');

				if (number == 1)
				{
					printf("�������µ�������\n");
					fgets(bookauthor, sizeof(bookauthor), stdin);
					bookauthor[strcspn(bookauthor, "\n")] = 0; // ȥ�����з�
					strcpy(newbook->info.author, bookauthor);
					printf("�������޸�Ϊ��%s\n", bookauthor);
				}
				else if (number == 2)
				{
					printf("�������µ����ߣ�\n");
					fgets(bookname, sizeof(bookname), stdin);
					bookname[strcspn(bookname, "\n")] = 0; // ȥ�����з�
					strcpy(newbook->info.name, bookname);
					printf("�������޸�Ϊ��%s\n", bookname);
				}
				else if (number == 3)
				{
					printf("�������µı�ţ�\n");
					scanf("%d", &bookidnew);
					newbook->info.id = bookidnew;
					printf("������޸�Ϊ��%d\n", bookidnew);
				}
				else if (number == 4)
				{
					printf("�������µļ�Ǯ��\n");
					scanf("%f", &bookprice);
					newbook->info.price = bookprice;
					printf("��Ǯ���޸�Ϊ��%.2f\n", bookprice);
				}
				else if (number == 5)
				{
					printf("�������µ�������\n");
					scanf("%d", &count);
					newbook->info.count = count;
					printf("�������޸�Ϊ��%d\n", count);
				}
				else
				{
					printf("��Ч��ѡ����������룡\n");
				}

				// ��ʾ�û������޸�
				printf("��������Ҫ�޸ĵ����\n");
				printf("1. ����\n");
				printf("2. ����\n");
				printf("3. ���\n");
				printf("4. ��Ǯ\n");
				printf("5. ����\n");
				printf("����0�����޸�\n");
				scanf("%d", &number);
			}

			break; // �޸���ɺ��˳�ѭ��
		}

		newbook = newbook->connect; // �ƶ�����һ���ڵ�
	}

	if (newbook == NULL)
	{
		printf("δ�ҵ����Ϊ %d ���鼮��\n", bookid);
	}
	else
	{
		readfile(head); // �����޸ĺ������
	}
}

void organize_books(Linklist head)
{
	PNode nextnode = head->connect;
	PNode newnode = head->connect;
	PBookList book;
	for (nextnode; nextnode != NULL; nextnode = nextnode->connect)
	{
		for (newnode; newnode->connect != NULL; newnode = newnode->connect)
		{
			if (newnode->info.count > newnode->connect->info.count)
			{
				book = newnode->info;
				newnode->info = newnode->connect->info;
				newnode->connect->info = book;
			}

		}

	}
	readfile(head);
}

void readfile(Linklist head)
{
	FILE* fp = fopen("new_book.txt", "w");
	if (fp == NULL) {
		printf("�޷����ļ�����д��\n");
		exit(0);
	}

	PNode p = head;
	while (p->connect != NULL) {
		// ��ʽ��д���鼮��Ϣ��ÿ���ֶ��ÿո�ָ��������
		fprintf(fp, "%s %s %d %.2f %d\n", p->info.author, p->info.name, p->info.id, p->info.price,p->info.count);
		p = p->connect;
	}

	fclose(fp);
	printf("��Ϣ�ѳɹ�д���ļ� \n");
}

Linklist insertbook(Linklist head, PBookList book)
{

	PNode newnode = (PNode)malloc(sizeof(struct Node));
	PNode code = head;
	newnode->info = book;
	newnode->connect = NULL;
	if (head == NULL) {
		return newnode;  // �������Ϊ�գ��½ڵ����ͷ�ڵ�
	}
	while (code->connect != NULL)
	{
		code = code->connect;


	}
	code->connect = newnode;
	return head;
}
void writefile(Linklist head)
{

	PBookList book1 = { "³Ѹ","�ź�",101,25.21,4 };
	PBookList book2 = { "̩���ʫѡ","���������",102,18.67,5 };
	head=insertbook(head, book1);
	head=insertbook(head, book2);
	FILE* fp = fopen("D:\\new_book.txt", "w");
	if (fp == NULL)

	{
		printf("���ļ�ʧ�ܣ��޷�д��\n");
		exit(0);

	}
	PNode p = head;
	while (p != NULL)
	{
		fprintf(fp, "%s %s %d %f %d\n", p->info.author, p->info.name, p->info.id, p->info.price, p->info.count);
		p = p->connect;
	}
	fclose(fp);
	printf("�ļ�д��ɹ�\n");

	}
void readermenu()
{
	printf("****************************\n");
	printf("���ã���ӭʹ��ͼ�����ϵͳ\n");
	printf("1.�����鼮\n");
	printf("2.�黹�鼮\n");
	printf("3.�����鼮\n");
	printf("4.�˳�\n");
	printf("5.��ӡĿǰϵͳ�鼮\n");
	printf("****************************\n");

}
void userinteractive(Linklist head)
{
	char bookauthor[20], bookname[30];
	int  bookid, count;
	float bookprice;
	int choice;
	printf("���������ѡ��\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("����ͼ��\n");
		printf("�������鼮�ı��\n");
		scanf("%d", &bookid);
		borrow_book(head, bookid);
		break;
	case 2:
		printf("�黹�鼮\n");
		printf("�������鼮�ı��,�������ÿո����\n");
		scanf("%d %d", &bookid, &count);
		return_books(head, bookid, count);
		break;
	case 3:
		printf("�����鼮\n");
		printf("�������鼮�����ߣ��������ÿո����\n");
		scanf("%s %s", bookauthor, bookname);
		searchbookList(head, bookauthor, bookname);
		break;
	case 4:
		printf("�˳�ϵͳ\n");
		break;

	case 5:
		printf("��ӡĿǰϵͳ�鼮\n");
		print_book(head);
		break;
	default:
		printf("�������\n");
		break;

	}
}
void admininteractive(Linklist head)
{
	char bookauthor[20], bookname[30];
	int  bookid, count;
	float bookprice;
	int choice;
	printf("���������ѡ��\n");
	scanf("%d", &choice);
	switch (choice)
	{
	
	case 1:
		printf("�����鼮\n");
		printf("�������鼮�����ߣ��������ÿո����\n");
		scanf("%s %s", bookauthor, bookname);
		searchbookList(head, bookauthor, bookname);
		break;
	case 2:
		printf("ɾ���鼮\n");
		printf("������Ҫɾ���鼮�ı��");
		scanf("%d", &bookid);
		sortdelete(head, bookid);
		break;
	case 3:
		printf("�����鼮\n");
		organize_books(head);
		break;
	case 4:
		printf("�Ǽ��鼮\n");
		printf("�������鼮�����ߣ���������ţ��۸�,��Ŀ���ÿո����\n");
		scanf("%s %s %d %.2f %d", bookauthor, bookname, &bookid, &bookprice, &count);
		Register_books(head, bookauthor, bookname, bookid, bookprice, count);
		break;
	case 5:
		printf("�˳�ϵͳ\n");
		break;

	case 6:
		printf("��ӡĿǰϵͳ�鼮\n");
		print_book(head);
		break;
	case 7:
		printf("�޸��鼮��Ϣ\n");
		printf("�����鼮�ı��\n");
		scanf("%d", &bookid);
		Modify_book_information(head, bookid);
		break;
	default:
		printf("�������\n");
		break;

	}
}
void Change_name(char *name)
{
	user users;
	FILE* fp;
	char  newname[20];
	user* p = (user*)malloc(sizeof(user));
	fp = fopen("D:\\new_user.txt", "r+");
	if (fp == NULL) {
		printf("�޷����ļ�\n");
		exit(0);
	}
	// ���ļ��ж�ȡ��Ϣ���洢���ṹ��
	while (fscanf(fp, "%s %d %d", users.name, &users.password, &users.type) != EOF)
	{

		if (strcmp(name, users.name) == 0) 
		{
			printf("���������û���\n");
			scanf("%s", newname);
			strcpy(users.name, newname);
			// ����򵥴����ȹر��ļ�������ļ�����������д���޸ĺ����Ϣ
			fclose(fp);
			fp = fopen("D:\\new_user.txt", "w");
			fprintf(fp, "%s %d %d\n", users.name, users.password, users.type);
			fclose(fp);
			printf("��Ϣ�ѳɹ�д���ļ� \n");
			return;
		}
	}
	fclose(fp);

	printf("δ�ҵ���Ӧ���û���\n");
}

void Change_Password(int password)
{
	user users;
	FILE* fp;
	int newpassword;
	user* p;
	fp = fopen("D:\\new_user.txt", "r+");
	if (fp == NULL) {
		printf("�޷����ļ�\n");
		exit(0);
	}
	// ���ļ��ж�ȡ��Ϣ���洢���ṹ��
	while (fscanf(fp, "%s %d %d", users.name, &users.password, &users.type) != EOF)
	{

		if (password==users.password)
		{
			printf("������������\n");
			scanf("%d", &newpassword);
			users.password = newpassword;
			// ����򵥴����ȹر��ļ�������ļ�����������д���޸ĺ����Ϣ
			fclose(fp);
			fp = fopen("D:\\new_user.txt", "w");
			fprintf(fp, "%s %d %d\n", users.name, users.password, users.type);
			fclose(fp);
			printf("��Ϣ�ѳɹ�д���ļ� \n");
			return;
		}
	}
	fclose(fp);

	printf("δ�ҵ���Ӧ���û���\n");
}
	

void administratormenu()
{
	printf("****************************\n");
	printf("���ã���ӭʹ��ͼ�����ϵͳ\n");
	printf("1.�����鼮\n");
	printf("2.ɾ���鼮\n");
	printf("3.�����鼮\n");
	printf("4.�Ǽ��鼮\n");
	printf("5.�˳�\n");
	printf("6.��ӡĿǰϵͳ�鼮\n");
	printf("7.�޸��鼮��Ϣ\n");
	printf("****************************\n");

}
void readermainmenu()
{

	printf("****************************\n");
	printf("�������ã���ӭʹ��ͼ�����ϵͳ\n");
	printf("1.�޸�����\n");
	printf("2.�޸��û���\n");
	printf("3.����ͼ��ϵͳ\n");
}
void administratormainmenu()
{
	printf("****************************\n");
	printf("����Ա���ã���ӭʹ��ͼ�����ϵͳ\n");
	printf("1.�޸�����\n");
	printf("2.�޸��û���\n");
	printf("3.����ͼ��ϵͳ\n");

}
void adminchoice()
{

	int choice;
	int passworld;
	char name[20];
	printf("���������ѡ��\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("�޸�����\n");
		printf("���������ԭʼ����\n");
		scanf("%d", &passworld);
		Change_Password(passworld);
		break;


	case 2:
		printf("�޸��û���\n");
		printf("����������û���\n");
		scanf("%s", name);
		Change_name(name);
		break;



	case 3:
		printf("����ͼ��ϵͳ\n");
		administratormenu();
		admininteractive(head);
		break;


	default:
		printf("�������\n");
		break;

	}

}
void readerchoice()
{
	int choice;
	int passworld;
	char name[20];
	printf("���������ѡ��\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("�޸�����\n");
		printf("���������ԭʼ����\n");
		scanf("%d", &passworld);
		Change_Password(passworld);
		break;

	case 2:
		printf("�޸��û���\n");
		printf("����������û���\n");
		scanf("%s", name);
		Change_name(name);
		break;

	case 3:
		printf("����ͼ��ϵͳ\n");
		readermenu();
		userinteractive(head);
		break;
	default:
		printf("�������\n");
		break;

	}
}
void registerUser()
{

	user* p = (user*)malloc(sizeof(user));
	char name[20];
	int password;
	int choice;

	printf("����ע������1������Աע������2\n");
	scanf("%d", &choice);
	if (choice == 1 || choice == 2)
	{
		printf("�������������\n");
		scanf("%s", name);
		printf("�������������\n");
		scanf("%d", &password);
		FILE* fp = fopen("D:\\new_user.txt", "w");
		if (fp == NULL)

		{
			printf("���ļ�ʧ�ܣ��޷�д��\n");
			exit(0);

		}
		fprintf(fp, "%s %d %d\n", name,password,choice);

		fclose(fp);
		printf("�ļ�д��ɹ�\n");
		free(p);
	}
	else
		printf("�������\n");

}
void login(Linklist head)
{
	FILE* fp;
	char name[20];
	int password;
	user users;
	int choice, number = 0;
	// ���ļ�
	fp = fopen("D:\\new_user.txt", "r");
	if (fp == NULL) {
		printf("�޷����ļ�\n");
		exit(0);
	}

	// ���ļ��ж�ȡ��Ϣ���洢���ṹ��
	while (fscanf(fp, "%s %d %d\n", users.name, &users.password,&users.type))
	{
		// ����ṹ���е���Ϣ
		printf("������������������룬�ÿո����\n");
		scanf("%s %d", name, &password);

		if (strcmp(name, users.name) == 0 && password == users.password)
		{
			printf("ok\n");
			printf("��ӭ����\n");
			number = 1;
			break;
		}
	}
	
	if (number = 0)
	{
		printf("�û������������,����������\n");
		exit(0);
	}
	if (users.type == 1)
	{
		readermainmenu();
		readerchoice();
	}
	if(users.type==2)
	{
		administratormainmenu();
		adminchoice();
	}
	

	// �ر��ļ�
	fclose(fp);

	
}


int main()
{
	head = CreateList();
	writefile(head);
	int choice;
	while (1) {
		printf("1. ע��\n");
		printf("2. ��¼\n");
		printf("3. �˳�\n");
		printf("��ѡ�����: ");
		while (scanf("%d", &choice) != 1) {
			// ������뻺����
			while (getchar() != '\n');
			printf("�������������һ������: ");
		}

		switch (choice) {
		case 1:
			registerUser();
			break;
		case 2:
			login(head);
			break;
		case 3:
			return 0;
		default:
			printf("��Ч��ѡ�����������롣\n");
			break;
		}
	}
	return 0;
}
