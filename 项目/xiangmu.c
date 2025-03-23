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
					printf("已借阅%s %s\n", nextlist->connect->info.author, nextlist->connect->info.name);
					break;

				}
				else {
					printf("馆藏已空\n");
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

		printf("没有找到该图书\n");
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
			printf("已找到书籍，显示内容\n");
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
		printf("没有找到该书\n");

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
			printf("找到该书籍，删除成功\n");
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
		printf("没有找到该书籍\n");
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
		printf("链表为空，无法修改！\n");
		exit(0);
	}

	while (newbook)
	{
		if (newbook->info.id == bookid)
		{
			printf("请输入你要修改的类别：\n");
			printf("1. 书名\n");
			printf("2. 作者\n");
			printf("3. 编号\n");
			printf("4. 价钱\n");
			printf("5. 数量\n");
			printf("输入0结束修改\n");
			scanf("%d", &number);

			while (number != 0)
			{
				// 清除输入缓冲区
				while (getchar() != '\n');

				if (number == 1)
				{
					printf("请输入新的书名：\n");
					fgets(bookauthor, sizeof(bookauthor), stdin);
					bookauthor[strcspn(bookauthor, "\n")] = 0; // 去除换行符
					strcpy(newbook->info.author, bookauthor);
					printf("书名已修改为：%s\n", bookauthor);
				}
				else if (number == 2)
				{
					printf("请输入新的作者：\n");
					fgets(bookname, sizeof(bookname), stdin);
					bookname[strcspn(bookname, "\n")] = 0; // 去除换行符
					strcpy(newbook->info.name, bookname);
					printf("作者已修改为：%s\n", bookname);
				}
				else if (number == 3)
				{
					printf("请输入新的编号：\n");
					scanf("%d", &bookidnew);
					newbook->info.id = bookidnew;
					printf("编号已修改为：%d\n", bookidnew);
				}
				else if (number == 4)
				{
					printf("请输入新的价钱：\n");
					scanf("%f", &bookprice);
					newbook->info.price = bookprice;
					printf("价钱已修改为：%.2f\n", bookprice);
				}
				else if (number == 5)
				{
					printf("请输入新的数量：\n");
					scanf("%d", &count);
					newbook->info.count = count;
					printf("数量已修改为：%d\n", count);
				}
				else
				{
					printf("无效的选项，请重新输入！\n");
				}

				// 提示用户继续修改
				printf("请输入你要修改的类别：\n");
				printf("1. 书名\n");
				printf("2. 作者\n");
				printf("3. 编号\n");
				printf("4. 价钱\n");
				printf("5. 数量\n");
				printf("输入0结束修改\n");
				scanf("%d", &number);
			}

			break; // 修改完成后退出循环
		}

		newbook = newbook->connect; // 移动到下一个节点
	}

	if (newbook == NULL)
	{
		printf("未找到编号为 %d 的书籍！\n", bookid);
	}
	else
	{
		readfile(head); // 保存修改后的数据
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
		printf("无法打开文件进行写入\n");
		exit(0);
	}

	PNode p = head;
	while (p->connect != NULL) {
		// 格式化写入书籍信息，每个字段用空格分隔，最后换行
		fprintf(fp, "%s %s %d %.2f %d\n", p->info.author, p->info.name, p->info.id, p->info.price,p->info.count);
		p = p->connect;
	}

	fclose(fp);
	printf("信息已成功写入文件 \n");
}

Linklist insertbook(Linklist head, PBookList book)
{

	PNode newnode = (PNode)malloc(sizeof(struct Node));
	PNode code = head;
	newnode->info = book;
	newnode->connect = NULL;
	if (head == NULL) {
		return newnode;  // 如果链表为空，新节点就是头节点
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

	PBookList book1 = { "鲁迅","呐喊",101,25.21,4 };
	PBookList book2 = { "泰戈尔诗选","重庆出版社",102,18.67,5 };
	head=insertbook(head, book1);
	head=insertbook(head, book2);
	FILE* fp = fopen("D:\\new_book.txt", "w");
	if (fp == NULL)

	{
		printf("打开文件失败，无法写入\n");
		exit(0);

	}
	PNode p = head;
	while (p != NULL)
	{
		fprintf(fp, "%s %s %d %f %d\n", p->info.author, p->info.name, p->info.id, p->info.price, p->info.count);
		p = p->connect;
	}
	fclose(fp);
	printf("文件写入成功\n");

	}
void readermenu()
{
	printf("****************************\n");
	printf("您好，欢迎使用图书管理系统\n");
	printf("1.借阅书籍\n");
	printf("2.归还书籍\n");
	printf("3.查找书籍\n");
	printf("4.退出\n");
	printf("5.打印目前系统书籍\n");
	printf("****************************\n");

}
void userinteractive(Linklist head)
{
	char bookauthor[20], bookname[30];
	int  bookid, count;
	float bookprice;
	int choice;
	printf("请输入你的选择\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("借阅图书\n");
		printf("请输入书籍的编号\n");
		scanf("%d", &bookid);
		borrow_book(head, bookid);
		break;
	case 2:
		printf("归还书籍\n");
		printf("请输入书籍的编号,数量，用空格隔开\n");
		scanf("%d %d", &bookid, &count);
		return_books(head, bookid, count);
		break;
	case 3:
		printf("查找书籍\n");
		printf("请输入书籍的作者，书名，用空格隔开\n");
		scanf("%s %s", bookauthor, bookname);
		searchbookList(head, bookauthor, bookname);
		break;
	case 4:
		printf("退出系统\n");
		break;

	case 5:
		printf("打印目前系统书籍\n");
		print_book(head);
		break;
	default:
		printf("输入错误\n");
		break;

	}
}
void admininteractive(Linklist head)
{
	char bookauthor[20], bookname[30];
	int  bookid, count;
	float bookprice;
	int choice;
	printf("请输入你的选择\n");
	scanf("%d", &choice);
	switch (choice)
	{
	
	case 1:
		printf("查找书籍\n");
		printf("请输入书籍的作者，书名，用空格隔开\n");
		scanf("%s %s", bookauthor, bookname);
		searchbookList(head, bookauthor, bookname);
		break;
	case 2:
		printf("删除书籍\n");
		printf("请输入要删除书籍的编号");
		scanf("%d", &bookid);
		sortdelete(head, bookid);
		break;
	case 3:
		printf("整理书籍\n");
		organize_books(head);
		break;
	case 4:
		printf("登记书籍\n");
		printf("请输入书籍的作者，书名，编号，价格,数目，用空格隔开\n");
		scanf("%s %s %d %.2f %d", bookauthor, bookname, &bookid, &bookprice, &count);
		Register_books(head, bookauthor, bookname, bookid, bookprice, count);
		break;
	case 5:
		printf("退出系统\n");
		break;

	case 6:
		printf("打印目前系统书籍\n");
		print_book(head);
		break;
	case 7:
		printf("修改书籍信息\n");
		printf("输入书籍的编号\n");
		scanf("%d", &bookid);
		Modify_book_information(head, bookid);
		break;
	default:
		printf("输入错误\n");
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
		printf("无法打开文件\n");
		exit(0);
	}
	// 从文件中读取信息并存储到结构体
	while (fscanf(fp, "%s %d %d", users.name, &users.password, &users.type) != EOF)
	{

		if (strcmp(name, users.name) == 0) 
		{
			printf("请输入新用户名\n");
			scanf("%s", newname);
			strcpy(users.name, newname);
			// 这里简单处理，先关闭文件，清空文件内容再重新写入修改后的信息
			fclose(fp);
			fp = fopen("D:\\new_user.txt", "w");
			fprintf(fp, "%s %d %d\n", users.name, users.password, users.type);
			fclose(fp);
			printf("信息已成功写入文件 \n");
			return;
		}
	}
	fclose(fp);

	printf("未找到对应的用户名\n");
}

void Change_Password(int password)
{
	user users;
	FILE* fp;
	int newpassword;
	user* p;
	fp = fopen("D:\\new_user.txt", "r+");
	if (fp == NULL) {
		printf("无法打开文件\n");
		exit(0);
	}
	// 从文件中读取信息并存储到结构体
	while (fscanf(fp, "%s %d %d", users.name, &users.password, &users.type) != EOF)
	{

		if (password==users.password)
		{
			printf("请输入新密码\n");
			scanf("%d", &newpassword);
			users.password = newpassword;
			// 这里简单处理，先关闭文件，清空文件内容再重新写入修改后的信息
			fclose(fp);
			fp = fopen("D:\\new_user.txt", "w");
			fprintf(fp, "%s %d %d\n", users.name, users.password, users.type);
			fclose(fp);
			printf("信息已成功写入文件 \n");
			return;
		}
	}
	fclose(fp);

	printf("未找到对应的用户名\n");
}
	

void administratormenu()
{
	printf("****************************\n");
	printf("您好，欢迎使用图书管理系统\n");
	printf("1.查找书籍\n");
	printf("2.删除书籍\n");
	printf("3.整理书籍\n");
	printf("4.登记书籍\n");
	printf("5.退出\n");
	printf("6.打印目前系统书籍\n");
	printf("7.修改书籍信息\n");
	printf("****************************\n");

}
void readermainmenu()
{

	printf("****************************\n");
	printf("读者您好，欢迎使用图书管理系统\n");
	printf("1.修改密码\n");
	printf("2.修改用户名\n");
	printf("3.进入图书系统\n");
}
void administratormainmenu()
{
	printf("****************************\n");
	printf("管理员您好，欢迎使用图书管理系统\n");
	printf("1.修改密码\n");
	printf("2.修改用户名\n");
	printf("3.进入图书系统\n");

}
void adminchoice()
{

	int choice;
	int passworld;
	char name[20];
	printf("请输入你的选择\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("修改密码\n");
		printf("请输入你的原始密码\n");
		scanf("%d", &passworld);
		Change_Password(passworld);
		break;


	case 2:
		printf("修改用户名\n");
		printf("请输入你的用户名\n");
		scanf("%s", name);
		Change_name(name);
		break;



	case 3:
		printf("进入图书系统\n");
		administratormenu();
		admininteractive(head);
		break;


	default:
		printf("输入错误\n");
		break;

	}

}
void readerchoice()
{
	int choice;
	int passworld;
	char name[20];
	printf("请输入你的选择\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("修改密码\n");
		printf("请输入你的原始密码\n");
		scanf("%d", &passworld);
		Change_Password(passworld);
		break;

	case 2:
		printf("修改用户名\n");
		printf("请输入你的用户名\n");
		scanf("%s", name);
		Change_name(name);
		break;

	case 3:
		printf("进入图书系统\n");
		readermenu();
		userinteractive(head);
		break;
	default:
		printf("输入错误\n");
		break;

	}
}
void registerUser()
{

	user* p = (user*)malloc(sizeof(user));
	char name[20];
	int password;
	int choice;

	printf("读者注册输入1，管理员注册输入2\n");
	scanf("%d", &choice);
	if (choice == 1 || choice == 2)
	{
		printf("请输入你的姓名\n");
		scanf("%s", name);
		printf("请输入你的密码\n");
		scanf("%d", &password);
		FILE* fp = fopen("D:\\new_user.txt", "w");
		if (fp == NULL)

		{
			printf("打开文件失败，无法写入\n");
			exit(0);

		}
		fprintf(fp, "%s %d %d\n", name,password,choice);

		fclose(fp);
		printf("文件写入成功\n");
		free(p);
	}
	else
		printf("输入错误\n");

}
void login(Linklist head)
{
	FILE* fp;
	char name[20];
	int password;
	user users;
	int choice, number = 0;
	// 打开文件
	fp = fopen("D:\\new_user.txt", "r");
	if (fp == NULL) {
		printf("无法打开文件\n");
		exit(0);
	}

	// 从文件中读取信息并存储到结构体
	while (fscanf(fp, "%s %d %d\n", users.name, &users.password,&users.type))
	{
		// 输出结构体中的信息
		printf("请输入你的姓名，密码，用空格隔开\n");
		scanf("%s %d", name, &password);

		if (strcmp(name, users.name) == 0 && password == users.password)
		{
			printf("ok\n");
			printf("欢迎进入\n");
			number = 1;
			break;
		}
	}
	
	if (number = 0)
	{
		printf("用户名或密码错误,请重新输入\n");
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
	

	// 关闭文件
	fclose(fp);

	
}


int main()
{
	head = CreateList();
	writefile(head);
	int choice;
	while (1) {
		printf("1. 注册\n");
		printf("2. 登录\n");
		printf("3. 退出\n");
		printf("请选择操作: ");
		while (scanf("%d", &choice) != 1) {
			// 清空输入缓冲区
			while (getchar() != '\n');
			printf("输入错误，请输入一个整数: ");
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
			printf("无效的选择，请重新输入。\n");
			break;
		}
	}
	return 0;
}
