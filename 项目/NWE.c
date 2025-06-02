#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNUMBER 1000;
typedef  struct Flight {
	int flightNumber;
	char from[50];
	char to[50];
	char  time[30];
	int seats;
	float price;
	struct Flight* next;

}Flight;
typedef struct Passager {
	char username[20];
	char password[20];
	int isAdmin;
	int request;

}User;

typedef struct Purchase {
	char username[20];
	int  flightNumber;
	char from[10];
	char to[10];
	char time[10];

}purchase;
typedef struct Node {
	Flight data;
	struct Node* next;


}Node;
typedef struct Node* PNode;

typedef struct QNode {
	purchase data;
	struct QNode* connect;

}QNode;
typedef struct QNode* PQNode;

PNode initList()
{
	PNode q = (PNode*)malloc(sizeof(PNode));
	if (q == NULL)
	{
		printf("error");
	}
	q->next = NULL;
	return q;
}
//初始化添加结点
PNode createNewNode(Flight x)
{

	PNode newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("error");
		exit(1);


	}
	newNode->data.flightNumber = x.flightNumber;
	strcpy(newNode->data.from, x.from);
	strcpy(newNode->data.to, x.to);
	strcpy(newNode->data.time, x.time);
	newNode->data.seats = x.seats;
	newNode->data.price = x.price;
	newNode->next = NULL;
	return newNode;


}
//增添结点(管理员）
void   insertPNode(PNode head)
{
	printf("-------添加航班操作页-------");
	Flight flight;
	PNode Node;
	int flightNumber;
	char SPlace[10], MPlace[10];
	char flighttime[10];
	float tickets;
	int seat;
	PNode current = head;
	printf("请输入需要添加的航班号，起始地，终点，起飞时间，机票，座位数");
	scanf("%d%s%s%s%f%d", &flightNumber, SPlace, MPlace, flighttime, &tickets, &seat);
	flight.flightNumber = flightNumber;
	strcpy(flight.from, SPlace);
	strcpy(flight.to, MPlace);
	strcpy(flight.time, flighttime);
	flight.price = tickets;
	flight.seats = seat;
	Node = createNewNode(flight);
	while (current->next != NULL)
	{
		current = current->next;

	}
	current->next = Node;

	printf("添加成功\n");


}
//用户删除

void deletePurchase(PQNode head, int flightnumber) {
		if (head == NULL || head->connect == NULL) {
			printf("没有购票记录\n");
			return;
		}

		PQNode current = head->connect;
		PQNode prev = head;

		while (current != NULL && current->data.flightNumber != flightnumber) {
			prev = current;
			current = current->connect;
		}

		if (current != NULL) {
			prev->connect = current->connect;
			free(current);
			printf("已取消航班 %d 的购票\n", flightnumber);
		}
		else {
			printf("未找到航班 %d 的购票记录\n", flightnumber);
		}

		
	
	}
//管理员删除
PNode* deleteNode(PNode head, int flightNumber)
{
	int t;
	
	if (head == NULL) {
		printf("error");

	}
	PNode current = head->next;
	PNode temp = head;
	while (current != NULL && current->data.flightNumber != flightNumber) {
		temp = current;
		current = current->next;

	}

	if (current != NULL)
	{
		temp->next = current->next;

		free(current);
		printf("删除成功\n");
		

	}
	else {
		printf("Not Find");

	}

	return head;

}

PQNode CreateList()
{
	PQNode head;
	head = (PQNode)malloc(sizeof(struct QNode));
	if (head == NULL)
	{

		printf("out of space");
		return 0;

	}
	head->connect = NULL;
	return head;
}
PQNode  NewPNode(PQNode* head, purchase x)
{
	PQNode newNode = (QNode*)malloc(sizeof(QNode));
	if (newNode == NULL)
	{
		printf("error");
		exit(1);

	}
	newNode->data.flightNumber=x.flightNumber;
	strcpy(newNode->data.from, x.from);
	strcpy(newNode->data.to, x.to);
	strcpy(newNode->data.time, x.time);
	strcpy(newNode->data.username, x.username);
	return newNode;

}
void NewList(PQNode head, purchase x)
{
	PQNode current = (QNode*)malloc(sizeof(QNode));
	current = NewPNode(head, x);
	if (head->connect == NULL) {
		head->connect = current;
		current->connect = NULL;
	}
	else {
		PQNode NewQNode = (QNode*)malloc(sizeof(QNode));
		while (NewQNode->connect != NULL)
		{
			NewQNode = NewQNode->connect;

		}
		NewQNode->connect = current;

	}

}


typedef struct TreeNode
{
	Flight data;
	struct TreeNode* LNode;
	struct TreeNode* RNode;


}TreeNode;
//创建结点
TreeNode* createTreeNode(Flight x)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL)
	{
		printf("error");
		exit(1);
	}
	node->data.flightNumber=x.flightNumber;
	strcpy(node->data.from, x.from);
	strcpy(node->data.to, x.from);
	strcpy(node->data.time, x.time);
	node->data.seats = x.seats;
	node->data.price = x.price;
	node->LNode = node->RNode = NULL;
	return node;
}
TreeNode* initTree() {
	
	return NULL;

}



PNode createNewQNode(Flight x) {
	PNode newNode = (PNode)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("内存分配失败\n");
		exit(1);
	}
	newNode->data.flightNumber = x.flightNumber;
	strcpy(newNode->data.from, x.from);
	strcpy(newNode->data.to, x.to);
	strcpy(newNode->data.time, x.time);
	newNode->data.seats = x.seats;
	newNode->data.price = x.price;
	newNode->next = NULL;
	return newNode;
}

typedef struct Queue {
	Flight data[1000];
	int front;// 队头指针
	int rear;
	struct Queue* next;// 队尾指针
} Queue;
typedef struct  Queue* PlinkQueue;
// 初始化队列
PlinkQueue init_queue() {
	PlinkQueue q = (PlinkQueue)malloc(sizeof(Queue));
	q->front = -1;
	q->rear = -1;
	return q;
}
// 清空队列函数
void clearQueue(Queue* q) {
	
		if (q == NULL) return;
		q->front = -1;
		q->rear = -1;
	

}

// 判断队列是否已满
int is_full(Queue* q) {
	return (q->rear == 1000 - 1);
}

// 判断队列是否为空
int is_empty(Queue* q) {
	return (q->front == -1);
}

// 将时间字符串转换为分钟数
int time_to_minutes(const char* time) {
	return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 +
		((time[3] - '0') * 10 + (time[4] - '0'));
}

// 插入航班（插入时按时间排序，确保队列有序）
void enqueue_sorted(Queue* q, Flight f) {
	if (is_full(q)) {
		printf("队列已满！\n");
		return;
	}
	int i, pos;
	// 找到插入位置（从队头到队尾遍历，找到第一个时间晚于f的位置）
	for (pos = 0; pos <= q->rear; pos++) {
		if (time_to_minutes(f.time) <
			time_to_minutes(q->data[pos].time)) {
			break;
		}
	}
	// 移动元素，腾出插入位置
	if (q->rear >= pos) {
		for (i = q->rear + 1; i > pos; i--) {
			q->data[i] = q->data[i - 1];
		}
	}
	q->data[pos] = f;  // 插入元素
	if (q->front == -1) q->front = 0;  // 首次插入
	q->rear++;  // 队尾后移
}



//链表写入文件
void writeToFile(PNode head, const char* filename)
{
	if (head == NULL) {
		printf("错误：链表为空\n");
		return;
	}

	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("无法打开文件: %s\n", filename);
		return;
	}

	PNode current = head->next;  // 从第一个实际节点开始
	while (current != NULL) {
		fprintf(file, "%d,%s,%s,%s,%d,%.2f\n",
			current->data.flightNumber,
			current->data.from,
			current->data.to,
			current->data.time,
			current->data.seats,
			current->data.price);
		current = current->next;
	}

	fclose(file);
	printf("航班数据已保存到: %s\n", filename);

}
// 释放链表（保留头指针）
void freeList(PNode head)
{
	if (head == NULL) return;

	PNode current = head->next;  // 从第一个实际节点开始
	while (current != NULL)
	{
		PNode temp = current;
		current = current->next;
		free(temp);
	}
	head->next = NULL;  // 将头指针的next置为NULL
}

// 读取文件进入链表（清空现有数据）
PNode readFile(PNode head, const char* filename) {
	// 首先清空链表（保留头指针）
	freeList(head);

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件: %s\n", filename);
		return head;
	}

	Flight f;
	while (fscanf(file, "%d,%49[^,],%49[^,],%29[^,],%d,%f\n",
		&f.flightNumber, f.from, f.to, f.time, &f.seats, &f.price) == 6)
	{
		PNode newNode = createNewQNode(f);
		PNode current = head;

		// 找到链表末尾
		while (current->next != NULL) {
			current = current->next;
		}

		// 添加新节点
		current->next = newNode;
	}

	fclose(file);
	printf("文件已加载: %s\n", filename);
	return head;
}

//将文件中的信息写入队列
void readFlightMessage(PlinkQueue q, const char* filename)
{
	

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件: %s\n", filename);
		return;
	}

	char line[200];
	while (fgets(line, sizeof(line), file) != NULL) {
		Flight f1;
		// 解析航班信息
		if (sscanf(line, "%d,%[^,],%[^,],%[^,],%d,%f\n",
			&f1.flightNumber, f1.from, f1.to, f1.time, &f1.seats, &f1.price) == 6) {
			// 使用排序插入法将航班加入队列
			enqueue_sorted(q, f1);
		}
	}

	fclose(file);
	printf("航班信息已加载到队列: %s\n", filename);
}




//将文件写入链表购票
void  loadList(const char* filename)
{
	purchase* new = (purchase*)malloc(sizeof(purchase));
	PQNode* head = CreateList();
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("error");
		exit(1);


	}
	while (scanf(file, "%s,%s,%s,%s,%d", new->username, new->from, new->to, new->time, &new->flightNumber))
	{
		NewList(head, *new);

	}
	fclose(file);


}
//车票写入文件
void writeNewFile(PQNode head, const char* filename)
{
	PQNode current = head->connect;
	if (current == NULL) {
		// 处理链表为空的情况，比如直接返回或者提示信息
		printf("链表为空\n");
		return;
	}
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("写入失败");
		exit(1);
	}
	while (current->connect != NULL) {
		fprintf(file, "%s,%d,%s,%s", current->data.username, current->data.flightNumber,
			current->data.to, current->data.time);
		current = current->connect;
	}
	// 别忘了关闭文件
	fclose(file);


}
//添加树结点
TreeNode* insertNodeTree(TreeNode* root, Flight x)
{
	if (root == NULL)
	{
		return createTreeNode(x);

	}
	if (x.flightNumber < root->data.flightNumber) {
		root->LNode = insertNodeTree(root->LNode, x);

	}
	else {
		root->RNode = insertNodeTree(root->RNode, x);

	}
	return root;
}
//将航班信息写入文件,队列
void writeFlightFile(PlinkQueue q, const char* filename)
{
		FILE* file = fopen(filename, "w");
		if (file == NULL) {
			printf("无法打开航班文件: %s\n", filename);
			return;
		}

		if (is_empty(q)) {
			fclose(file);
			return;
		}

		for (int i = q->front; i <= q->rear; i++) {
			fprintf(file, "%d,%s,%s,%s,%d,%.2f\n",
				q->data[i].flightNumber,
				q->data[i].from,
				q->data[i].to,
				q->data[i].time,
				q->data[i].seats,
				q->data[i].price);
		}

		fclose(file);
		printf("航班文件已更新\n");

}
//树的排序后输出
void inOrder(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
		inOrder(root->LNode);
		printf("航班号：%d，起始地：%s,终点：%s,起飞时间：%s,座位数：%d,票价：%f\n", root->data.flightNumber,
			root->data.from, root->data.to, root->data.time, root->data.seats,
			root->data.price);
		inOrder(root->RNode);
	}


void clearTree(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	clearTree(root->LNode);	
	clearTree(root->RNode);	
	free(root);  	

}

//初始化航班信息，树
TreeNode* buildTreeFromFile(const char* filename, TreeNode* root)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("error");
		return NULL;
	}
	Flight f1;
	while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%f", &f1.flightNumber, f1.from, f1.to, f1.time, &f1.seats,
		&f1.price) == 6)
	{
		root = insertNodeTree(root, f1);

	}
	fclose(file);
	return root;


}
//初始文件
void writeFlightMessage(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL)
	{

		printf("error");
		exit(0);

	}
	Flight f1 = { 1001,"北京","上海","17:15",23,290.4 };
	Flight f2 = { 1002,"南京","成都","13:20",45,230.2 };
	Flight f3 = { 1003,"北京","上海","08:00",39,240.7 };
	fprintf(file, "%d,%s,%s,%s,%d,%f\n", f1.flightNumber, f1.from, f1.to, f1.time, f1.seats, f1.price);
	fprintf(file, "%d,%s,%s,%s,%d,%f\n", f2.flightNumber, f2.from, f2.to, f2.time, f2.seats, f2.price);
	fprintf(file, "%d,%s,%s,%s,%d,%f\n", f3.flightNumber, f3.from, f3.to, f3.time, f3.seats, f3.price);
	fclose(file);





}//用户查看

void viewFlight(PNode p, TreeNode* root, PlinkQueue q)
{
	int   choice;
	char  choice1;
	PNode new = p->next;
	printf("目前机票信息如下：");
	while (new != NULL)
	{
		printf("%d,%s,%s,%s,%d,%f\n", new->data.flightNumber, new->data.from, new->data.to, new->data
			.time, new->data.seats, new->data.price);
		new = new->next;
	}


	while (1)
	{
		int c;
		printf("是否要查看其他排列,Y OR N\n");
		while ((c = getchar()) != '\n' && c != EOF);  // 清空缓冲区
		scanf("%c", &choice1);
		while ((c = getchar()) != '\n' && c != EOF);
		if (choice1 == 'Y')
		{
			printf("请选择你要查看的方式:\n");

			printf("1.按车次顺序排列\n");
			

			scanf("%d", &choice);

			if (choice == 1)
			{
				printf("车次按时间顺序排列\n");
				inOrder(root);

			}
			else {
				printf("输入错误，格式为1或2\n");
			}
		}
		else {
			return;

		}
	}
}
//订购机票（主）

void bookFlight(PlinkQueue q, const char* filename, const char* filename1, PQNode head) {
	int id, i;
	int found = 0;
	int flight_index = -1;
	purchase Message;
	char username[20];
	char newChoice;
	int c;

	printf("\n----欢迎进入订购机票页面----\n");
	printf("请输入航班编号: ");
	scanf("%d", &id);

	// 清空输入缓冲区
	while ((c = getchar()) != '\n' && c != EOF);

	// 在队列中查找航班
	if (!is_empty(q)) {
		for (i = q->front; i <= q->rear; i++) {
			if (q->data[i].flightNumber == id) {
				printf("\n找到航班信息:\n");
				printf("航班号：%d\n起始地：%s\n终点：%s\n起飞时间：%s\n座位数：%d\n票价：%.2f\n",
					q->data[i].flightNumber,
					q->data[i].from,
					q->data[i].to,
					q->data[i].time,
					q->data[i].seats,
					q->data[i].price);

				found = 1;
				flight_index = i;
				break;
			}
		}
	}

	if (!found) {
		printf("\n错误：未找到航班号为 %d 的航班\n", id);
		return;
	}

	printf("\n是否订购该机票? (Y/N): ");
	scanf("%c", &newChoice);
	while ((c = getchar()) != '\n' && c != EOF);

	if (newChoice == 'Y' || newChoice == 'y') {
		if (q->data[flight_index].seats > 0) {
			printf("\n请输入你的用户名: ");
			scanf("%19s", username);
			while ((c = getchar()) != '\n' && c != EOF);

			printf("\n订票成功！\n");

			// 减少座位数
			q->data[flight_index].seats--;

			// 更新航班文件
			writeFlightFile(q, filename);

			// 创建购买记录
			Message.flightNumber = q->data[flight_index].flightNumber;
			strcpy(Message.from, q->data[flight_index].from);
			strcpy(Message.to, q->data[flight_index].to);
			strcpy(Message.time, q->data[flight_index].time);
			strcpy(Message.username, username);

			// 添加到购买列表
			NewList(head, Message);
			writeNewFile(head, "purchase.txt");
		}
		else {
			printf("\n错误：该航班已无可用座位\n");
		}
	}
	else if (newChoice == 'N' || newChoice == 'n') {
		printf("\n已取消订票操作\n");
	}
	else {
		printf("\n错误：无效选择，请输入 Y 或 N\n");
	}
}

//删除订购
void deleteFlight(PQNode head, PNode Phead) {

		int id, c;
		char choice;

		// 输入航班号
		printf("请输入需要取消的航班号: ");
		if (scanf("%d", &id) != 1) {
			printf("输入无效\n");
			// 清空输入缓冲区
			while ((c = getchar()) != '\n' && c != EOF);
			return;
		}

		// 清空输入缓冲区
		while ((c = getchar()) != '\n' && c != EOF);

		// 查找购票记录
		PQNode current = head->connect;
		int found = 0;
		while (current != NULL) {
			if (current->data.flightNumber == id) {
				found = 1;
				printf("找到购票记录:\n");
				printf("用户名: %s\n航班号: %d\n出发地: %s\n目的地: %s\n起飞时间: %s\n",
					current->data.username,
					current->data.flightNumber,  // 修复：移除&符号
					current->data.from,
					current->data.to,
					current->data.time);
				break;
			}
			current = current->connect;
		}

		if (!found) {
			printf("没有找到航班 %d 的购票记录\n", id);
			return;
		}

		printf("是否要取消该机票? (Y/N): ");
		scanf("%c", &choice);
		while ((c = getchar()) != '\n' && c != EOF);

		if (choice == 'Y' || choice == 'y') {
			// 恢复座位数
			PNode flightNode = Phead->next;  // 从头节点的下一个开始
			while (flightNode != NULL) {
				if (flightNode->data.flightNumber == id) {
					flightNode->data.seats += 1;
					printf("已恢复一个座位\n");
					break;
				}
				flightNode = flightNode->next;
			}

			// 删除购票记录
			deletePurchase(head, id);

			// 更新航班文件
			writeToFile(Phead, "Flight.txt");

			printf("机票取消成功\n");
		}
		else {
			printf("已取消操作\n");
		}
	}

void manageFlight(PlinkQueue p)
{
	int i;
	printf("======欢迎进入航班调度系统====\n");
	printf("已经依据最优时间排序调度进行");

	while (p->front == -1)
	{
		printf("队列为空");
		return;
	}
	for (i = p->front; i <= p->rear; i++)
	{

		printf("航班号：%d, 起始地：%s, 终点：%s, 起飞时间：%s, 座位数：%d, 票价：%f\n", p->data[i].flightNumber, p->data[i].from,
			p->data[i].to, p->data[i].time, p->data[i].seats, p->data[i].price);

	}
}


//打印机票
void printView(PQNode head)
{
	PQNode current = head->connect;
	while (current!= NULL)
	{
		printf("%s,%d,%s,%s,%s", current->data.username, current->data.flightNumber, current->data.from, current->data.to,
			current->data.time);
		current = current->connect;

	}

}//修改用户名
void changeUser()
{
	int c;
	User information;
	char choice1;
	char name[20], rname[20];
	char password[20], repassword[20];
	char line[40], newname[20];
	char newpassword[20];
	int IsAdmin, request;
	char tempfile[100] = "temp.txt";
	printf("请输入你的用户名");
	scanf("%s", name);
	printf("请输入你的密码");
	scanf("%s", password);
	FILE* file = fopen("users.txt", "r+");
	if (file == NULL)
	{
		printf("error");
		exit(1);

	}
	FILE* temp = fopen(tempfile, "w+");
	if (temp == NULL)
	{
		printf("创建失败\n");
		exit(1);

	}
	while (fgets(line, sizeof(line), file))
	{

		sscanf(line, "%[^,],%[^,],%d,%d", rname, repassword, &IsAdmin, &request);
		if (strcmp(name, rname) == 0 && strcmp(repassword , password)==0)
		{

			if (request == 2&&IsAdmin==0)
			{
				printf("您提交的申请已同意");

				printf("请输入你的新用户名和密码");
				scanf("%s%s", newname, newpassword);
				fprintf(temp, "%s,%s,%d,%d\n", newname, newpassword, 0, 0);
				fclose(file);
				printf("密码修改成功\n");
				rename("users.txt", "oldName.txt");
				if (rename("temp.txt", "users.txt") == -1)
				{
					perror("rename");

				}
				else {
					printf("OK");
				}

			}
			else if (request == 0&&IsAdmin==0)
			{
				printf("是否提交密码修改申请，Y OR N\n");
				while ((c = getchar()) != '\n' && c != EOF);  // 清空缓冲区
				scanf("%c", &choice1);
				fprintf(temp, "%s,%s,%d,%d\n", rname, repassword, 0, 1);
				printf("提交成功,等待管理员审批\n");
				rename("users.txt", "oldname.txt");
				if (rename("temp.txt", "users.txt") == -1)
				{
					perror("rename");

				}
				else {
					printf("OK");
				}
			}
			else {
				fprintf(temp, "%s", line);

			}
		}
		else {
			fprintf(temp, "%s", line);


		}
	}
	fclose(file);
	fclose(temp);
	
	
}
//管理航班信息
void Adminview(PNode p)
{
	printf("\n当前航班信息:\n");
	printf("1. 链表形式:\n");
	PNode current = p->next;
	while (current != NULL) {
		printf("航班号：%d，起始地：%s，终点：%s，起飞时间：%s，座位数：%d，票价：%.2f\n",
			current->data.flightNumber,
			current->data.from,
			current->data.to,
			current->data.time,
			current->data.seats,
			current->data.price);
		current = current->next;
	}
}
// 管理员查看用户修改密码申请（与changeUser()匹配的版本）
void UserMessage() {
	int count = 0;
	char username[50] = { 0 };
	char password[50] = { 0 };
	int isadmin, request;
	char line[256] = { 0 };

	FILE* file = fopen("users.txt", "r");
	if (!file) {
		perror("文件打开失败");
		return;
	}

	FILE* temp = fopen("tmp.txt", "w");
	if (!temp) {
		fclose(file);
		perror("临时文件创建失败");
		return;
	}

	printf("查看密码修改的用户申请\n");
	int hasRequests = 0;

	while (fgets(line, sizeof(line), file)) {
	
		if (sscanf(line, "%[^,],%[^,],%d,%d",
			username, password, &isadmin, &request) != 4) {
			fputs(line, temp); 
			continue;
		}

		if (request == 1) {  // 匹配用户提交的申请状态
			hasRequests = 1;
			printf("发现申请：用户[%s] 申请修改密码\n", username);
			printf("是否同意修改？(Y/N): ");

			// 清除输入缓冲区
			int c;
			while ((c = getchar()) != '\n' && c != EOF);

			char choice;
			scanf(" %c", &choice);
			getchar(); 

			if (toupper(choice) == 'Y') {
				
				fprintf(temp, "%s,%s,%d,2\n", username, password, isadmin);
				count++;
				printf("√ 已批准申请（用户下次登录可修改密码）\n");
			}
			else {
				
				fprintf(temp, "%s,%s,%d,0\n", username, password, isadmin);
				printf("× 已拒绝申请\n");
			}
		}
		else {
		
			fputs(line, temp);
		}
	}

	fclose(file);
	fclose(temp);

	if (!hasRequests) {
		printf("没有用户申请修改密码\n");
		remove("tmp.txt");
		return;
	}

	remove("users.bak");
	if (rename("users.txt", "users.bak") == 0) {
		if (rename("tmp.txt", "users.txt") == 0) {
			printf("申请处理完成！共处理 %d 个申请\n", count);
		}
		else {
			perror("文件更新失败");
			rename("users.bak", "users.txt");
		}
	}
	else {
		perror("无法创建备份");
		remove("tmp.txt");
	}
}


void userMenu(PNode p, PlinkQueue q, TreeNode* root, char filename[], char filename1[], PQNode head) {
	int choice;
	printf("——————欢迎进入乘客菜单界面——————\n");
	printf("1.查看航班信息\n");
	printf("2.购买机票\n");
	printf("3.取消机票\n");
	printf("4.显示机票\n");
	printf("5.更改用户名和密码\n");
	printf("请输入你的选择,0退出\n");

	while (1) {
		scanf("%d", &choice);
		if (choice < 0 || choice > 6) {
			printf("选择错误，请重新选择\n");
			continue;
		}
		if (choice == 0) {
			break;  // 输入 0 时退出循环
		}
		switch (choice) {
		case 1:
			printf("已自动为您展示最优化时间航班排列");
			manageFlight(q);
			viewFlight(p, root, q);
			break;
		case 2:
			bookFlight(q, filename, filename1, head);
			freeList(p);
			p=readFile(p, filename);
			clearTree(root);
			root = initTree();
			root = buildTreeFromFile(filename, root);
			break;
		case 3:
			deleteFlight(head, p);
			clearQueue(q);
			readFlightMessage(q, filename);
			clearTree(root);
			root = initTree();
			root = buildTreeFromFile(filename, root);
			writeNewFile(head, "purchase.txt");
			break;
		case 4:
			printView(head);
			break;
		case 5:
			changeUser();
			break;
		default:
			break;
		}
	}
}


void  adminMenu(PNode p, PlinkQueue q) {
	int a;
	int  flightNumber;
	printf("————欢迎进入管理员菜单界面——————\n");
	printf("1.查看当前航班\n");
	printf("2.优化调度当前航班\n");
	printf("3.删除航班\n");
	printf("4.增加航班\n");
	printf("5.用户提交信息\n");
	printf("请输入你的选择,退出0\n");
	scanf("%d", &a);
	while (1)
	{
		switch (a)
		{
		case 1:
			
			Adminview(p);
			break;
		case 2:
			
			manageFlight(q);
			break;
		case 3:
			printf("请输入你想要删除的航班班号");
			scanf("%d", &flightNumber);
			deleteNode(p, flightNumber);
			writeToFile(p,"Flight.txt");
			readFlightMessage(q, "Flight.txt");
			readFile(p, "Flight.txt");
			break;
		case 4:
			insertPNode(p);
			writeToFile(p, "Flight.txt");
			readFlightMessage(q, "Flight.txt");
			readFile(p, "Flight.txt");
			break;

		case 5:
			UserMessage();
			break;
		case 0:
			return;

		default:
			printf("输入错误，请重新输入");
			scanf("%d", &a);
			break;

		}
		scanf("%d", &a);
	}
}
int regist() {
	char username[20], password[20];
	int isAdmin;

	printf("\n用户注册\n");
	printf("用户名: ");
	scanf("%s", username);
	printf("密码: ");
	scanf("%s", password);
	printf("是否为管理员? 1 or 0 : ");
	scanf("%d", &isAdmin);

	FILE* file = fopen("users.txt", "w+");
	if (file == NULL) {
		printf("无法打开用户文件\n");
		return 0;
	}

	fprintf(file, "%s,%s,%d,0\n", username, password, isAdmin);
	fclose(file);

	printf("注册成功！\n");
	return 1;
}

void   login(PlinkQueue p, PNode q, TreeNode* root, char filename[], char filename1[], PQNode head) {
	char username[20], password[20];
	int isAdmin = 0;

	printf("\n用户登录\n");
	printf("用户名: ");
	scanf("%s", username);
	printf("密码: ");
	scanf("%s", password);

	FILE* file = fopen("users.txt", "r");
	if (file == NULL) {
		printf("无法打开用户文件\n");
		return;
	}

	char line[100];
	int found = 0;

	while (fgets(line, sizeof(line), file)) {
		char fileUser[20], filePass[20];	
		int fileAdmin, fileRequest;
		sscanf(line, "%[^,],%[^,],%d,%d\n", fileUser, filePass, &fileAdmin, &fileRequest);

		if (strcmp(username, fileUser) == 0 && strcmp(password,filePass)==0) {
			found = 1;
			isAdmin = fileAdmin;
			break;
		}
	}

	fclose(file);

	if (found) {
		printf("登录成功！\n");
		if (isAdmin) {
			adminMenu(q, p);
		}
		else {
			userMenu(q, p, root, filename, filename1, head);
		}
	}
	else {
		printf("用户名或密码错误\n");
	}
}


int main() {
	char choice1;
	PlinkQueue q = init_queue();

	PNode* new;
	TreeNode* root;
	char filename[50] = "users.txt";
	char filename1[50] = "Flight.txt";
	writeFlightMessage(filename1);
	 
	readFlightMessage(q, filename1);
	root = initTree();
	root=buildTreeFromFile(filename1, root);
	PNode* head = initList();
	new = readFile(head, filename1);
	PQNode t = CreateList();

	printf("——————————欢迎进入航空管理与服务系统——————————\n");

	int choice;
	while (1)
	{
		printf("请输入你的选择\n");
		printf("1.登录\n");
		printf("2.注册\n");
		printf("3.退出\n");

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			login(q, new, root, filename1, filename, t);

			break;

		case 2:
			t = regist();
			if (t)
			{
				printf("是否进入登录页面,Y,OR,N");
				scanf("%c", &choice1);
				if (choice1 == "Y")
				{
					printf("正在进入");

					login(q, new, root, filename1, filename, t);
				}
				else {
					break;
				}
			}
			else {
				printf("出错了");

			}

		case 3:
			printf("退出系统");
			return 0;

		default:
			printf("出错，请重新选择");
			break;



		}
	}
	return 0;
}

