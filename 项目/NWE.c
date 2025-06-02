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
//��ʼ����ӽ��
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
//������(����Ա��
void   insertPNode(PNode head)
{
	printf("-------��Ӻ������ҳ-------");
	Flight flight;
	PNode Node;
	int flightNumber;
	char SPlace[10], MPlace[10];
	char flighttime[10];
	float tickets;
	int seat;
	PNode current = head;
	printf("��������Ҫ��ӵĺ���ţ���ʼ�أ��յ㣬���ʱ�䣬��Ʊ����λ��");
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

	printf("��ӳɹ�\n");


}
//�û�ɾ��

void deletePurchase(PQNode head, int flightnumber) {
		if (head == NULL || head->connect == NULL) {
			printf("û�й�Ʊ��¼\n");
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
			printf("��ȡ������ %d �Ĺ�Ʊ\n", flightnumber);
		}
		else {
			printf("δ�ҵ����� %d �Ĺ�Ʊ��¼\n", flightnumber);
		}

		
	
	}
//����Աɾ��
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
		printf("ɾ���ɹ�\n");
		

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
//�������
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
		printf("�ڴ����ʧ��\n");
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
	int front;// ��ͷָ��
	int rear;
	struct Queue* next;// ��βָ��
} Queue;
typedef struct  Queue* PlinkQueue;
// ��ʼ������
PlinkQueue init_queue() {
	PlinkQueue q = (PlinkQueue)malloc(sizeof(Queue));
	q->front = -1;
	q->rear = -1;
	return q;
}
// ��ն��к���
void clearQueue(Queue* q) {
	
		if (q == NULL) return;
		q->front = -1;
		q->rear = -1;
	

}

// �ж϶����Ƿ�����
int is_full(Queue* q) {
	return (q->rear == 1000 - 1);
}

// �ж϶����Ƿ�Ϊ��
int is_empty(Queue* q) {
	return (q->front == -1);
}

// ��ʱ���ַ���ת��Ϊ������
int time_to_minutes(const char* time) {
	return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 +
		((time[3] - '0') * 10 + (time[4] - '0'));
}

// ���뺽�ࣨ����ʱ��ʱ������ȷ����������
void enqueue_sorted(Queue* q, Flight f) {
	if (is_full(q)) {
		printf("����������\n");
		return;
	}
	int i, pos;
	// �ҵ�����λ�ã��Ӷ�ͷ����β�������ҵ���һ��ʱ������f��λ�ã�
	for (pos = 0; pos <= q->rear; pos++) {
		if (time_to_minutes(f.time) <
			time_to_minutes(q->data[pos].time)) {
			break;
		}
	}
	// �ƶ�Ԫ�أ��ڳ�����λ��
	if (q->rear >= pos) {
		for (i = q->rear + 1; i > pos; i--) {
			q->data[i] = q->data[i - 1];
		}
	}
	q->data[pos] = f;  // ����Ԫ��
	if (q->front == -1) q->front = 0;  // �״β���
	q->rear++;  // ��β����
}



//����д���ļ�
void writeToFile(PNode head, const char* filename)
{
	if (head == NULL) {
		printf("��������Ϊ��\n");
		return;
	}

	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("�޷����ļ�: %s\n", filename);
		return;
	}

	PNode current = head->next;  // �ӵ�һ��ʵ�ʽڵ㿪ʼ
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
	printf("���������ѱ��浽: %s\n", filename);

}
// �ͷ���������ͷָ�룩
void freeList(PNode head)
{
	if (head == NULL) return;

	PNode current = head->next;  // �ӵ�һ��ʵ�ʽڵ㿪ʼ
	while (current != NULL)
	{
		PNode temp = current;
		current = current->next;
		free(temp);
	}
	head->next = NULL;  // ��ͷָ���next��ΪNULL
}

// ��ȡ�ļ�������������������ݣ�
PNode readFile(PNode head, const char* filename) {
	// ���������������ͷָ�룩
	freeList(head);

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("�޷����ļ�: %s\n", filename);
		return head;
	}

	Flight f;
	while (fscanf(file, "%d,%49[^,],%49[^,],%29[^,],%d,%f\n",
		&f.flightNumber, f.from, f.to, f.time, &f.seats, &f.price) == 6)
	{
		PNode newNode = createNewQNode(f);
		PNode current = head;

		// �ҵ�����ĩβ
		while (current->next != NULL) {
			current = current->next;
		}

		// ����½ڵ�
		current->next = newNode;
	}

	fclose(file);
	printf("�ļ��Ѽ���: %s\n", filename);
	return head;
}

//���ļ��е���Ϣд�����
void readFlightMessage(PlinkQueue q, const char* filename)
{
	

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("�޷����ļ�: %s\n", filename);
		return;
	}

	char line[200];
	while (fgets(line, sizeof(line), file) != NULL) {
		Flight f1;
		// ����������Ϣ
		if (sscanf(line, "%d,%[^,],%[^,],%[^,],%d,%f\n",
			&f1.flightNumber, f1.from, f1.to, f1.time, &f1.seats, &f1.price) == 6) {
			// ʹ��������뷨������������
			enqueue_sorted(q, f1);
		}
	}

	fclose(file);
	printf("������Ϣ�Ѽ��ص�����: %s\n", filename);
}




//���ļ�д������Ʊ
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
//��Ʊд���ļ�
void writeNewFile(PQNode head, const char* filename)
{
	PQNode current = head->connect;
	if (current == NULL) {
		// ��������Ϊ�յ����������ֱ�ӷ��ػ�����ʾ��Ϣ
		printf("����Ϊ��\n");
		return;
	}
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("д��ʧ��");
		exit(1);
	}
	while (current->connect != NULL) {
		fprintf(file, "%s,%d,%s,%s", current->data.username, current->data.flightNumber,
			current->data.to, current->data.time);
		current = current->connect;
	}
	// �����˹ر��ļ�
	fclose(file);


}
//��������
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
//��������Ϣд���ļ�,����
void writeFlightFile(PlinkQueue q, const char* filename)
{
		FILE* file = fopen(filename, "w");
		if (file == NULL) {
			printf("�޷��򿪺����ļ�: %s\n", filename);
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
		printf("�����ļ��Ѹ���\n");

}
//������������
void inOrder(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
		inOrder(root->LNode);
		printf("����ţ�%d����ʼ�أ�%s,�յ㣺%s,���ʱ�䣺%s,��λ����%d,Ʊ�ۣ�%f\n", root->data.flightNumber,
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

//��ʼ��������Ϣ����
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
//��ʼ�ļ�
void writeFlightMessage(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL)
	{

		printf("error");
		exit(0);

	}
	Flight f1 = { 1001,"����","�Ϻ�","17:15",23,290.4 };
	Flight f2 = { 1002,"�Ͼ�","�ɶ�","13:20",45,230.2 };
	Flight f3 = { 1003,"����","�Ϻ�","08:00",39,240.7 };
	fprintf(file, "%d,%s,%s,%s,%d,%f\n", f1.flightNumber, f1.from, f1.to, f1.time, f1.seats, f1.price);
	fprintf(file, "%d,%s,%s,%s,%d,%f\n", f2.flightNumber, f2.from, f2.to, f2.time, f2.seats, f2.price);
	fprintf(file, "%d,%s,%s,%s,%d,%f\n", f3.flightNumber, f3.from, f3.to, f3.time, f3.seats, f3.price);
	fclose(file);





}//�û��鿴

void viewFlight(PNode p, TreeNode* root, PlinkQueue q)
{
	int   choice;
	char  choice1;
	PNode new = p->next;
	printf("Ŀǰ��Ʊ��Ϣ���£�");
	while (new != NULL)
	{
		printf("%d,%s,%s,%s,%d,%f\n", new->data.flightNumber, new->data.from, new->data.to, new->data
			.time, new->data.seats, new->data.price);
		new = new->next;
	}


	while (1)
	{
		int c;
		printf("�Ƿ�Ҫ�鿴��������,Y OR N\n");
		while ((c = getchar()) != '\n' && c != EOF);  // ��ջ�����
		scanf("%c", &choice1);
		while ((c = getchar()) != '\n' && c != EOF);
		if (choice1 == 'Y')
		{
			printf("��ѡ����Ҫ�鿴�ķ�ʽ:\n");

			printf("1.������˳������\n");
			

			scanf("%d", &choice);

			if (choice == 1)
			{
				printf("���ΰ�ʱ��˳������\n");
				inOrder(root);

			}
			else {
				printf("������󣬸�ʽΪ1��2\n");
			}
		}
		else {
			return;

		}
	}
}
//������Ʊ������

void bookFlight(PlinkQueue q, const char* filename, const char* filename1, PQNode head) {
	int id, i;
	int found = 0;
	int flight_index = -1;
	purchase Message;
	char username[20];
	char newChoice;
	int c;

	printf("\n----��ӭ���붩����Ʊҳ��----\n");
	printf("�����뺽����: ");
	scanf("%d", &id);

	// ������뻺����
	while ((c = getchar()) != '\n' && c != EOF);

	// �ڶ����в��Һ���
	if (!is_empty(q)) {
		for (i = q->front; i <= q->rear; i++) {
			if (q->data[i].flightNumber == id) {
				printf("\n�ҵ�������Ϣ:\n");
				printf("����ţ�%d\n��ʼ�أ�%s\n�յ㣺%s\n���ʱ�䣺%s\n��λ����%d\nƱ�ۣ�%.2f\n",
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
		printf("\n����δ�ҵ������Ϊ %d �ĺ���\n", id);
		return;
	}

	printf("\n�Ƿ񶩹��û�Ʊ? (Y/N): ");
	scanf("%c", &newChoice);
	while ((c = getchar()) != '\n' && c != EOF);

	if (newChoice == 'Y' || newChoice == 'y') {
		if (q->data[flight_index].seats > 0) {
			printf("\n����������û���: ");
			scanf("%19s", username);
			while ((c = getchar()) != '\n' && c != EOF);

			printf("\n��Ʊ�ɹ���\n");

			// ������λ��
			q->data[flight_index].seats--;

			// ���º����ļ�
			writeFlightFile(q, filename);

			// ���������¼
			Message.flightNumber = q->data[flight_index].flightNumber;
			strcpy(Message.from, q->data[flight_index].from);
			strcpy(Message.to, q->data[flight_index].to);
			strcpy(Message.time, q->data[flight_index].time);
			strcpy(Message.username, username);

			// ��ӵ������б�
			NewList(head, Message);
			writeNewFile(head, "purchase.txt");
		}
		else {
			printf("\n���󣺸ú������޿�����λ\n");
		}
	}
	else if (newChoice == 'N' || newChoice == 'n') {
		printf("\n��ȡ����Ʊ����\n");
	}
	else {
		printf("\n������Чѡ�������� Y �� N\n");
	}
}

//ɾ������
void deleteFlight(PQNode head, PNode Phead) {

		int id, c;
		char choice;

		// ���뺽���
		printf("��������Ҫȡ���ĺ����: ");
		if (scanf("%d", &id) != 1) {
			printf("������Ч\n");
			// ������뻺����
			while ((c = getchar()) != '\n' && c != EOF);
			return;
		}

		// ������뻺����
		while ((c = getchar()) != '\n' && c != EOF);

		// ���ҹ�Ʊ��¼
		PQNode current = head->connect;
		int found = 0;
		while (current != NULL) {
			if (current->data.flightNumber == id) {
				found = 1;
				printf("�ҵ���Ʊ��¼:\n");
				printf("�û���: %s\n�����: %d\n������: %s\nĿ�ĵ�: %s\n���ʱ��: %s\n",
					current->data.username,
					current->data.flightNumber,  // �޸����Ƴ�&����
					current->data.from,
					current->data.to,
					current->data.time);
				break;
			}
			current = current->connect;
		}

		if (!found) {
			printf("û���ҵ����� %d �Ĺ�Ʊ��¼\n", id);
			return;
		}

		printf("�Ƿ�Ҫȡ���û�Ʊ? (Y/N): ");
		scanf("%c", &choice);
		while ((c = getchar()) != '\n' && c != EOF);

		if (choice == 'Y' || choice == 'y') {
			// �ָ���λ��
			PNode flightNode = Phead->next;  // ��ͷ�ڵ����һ����ʼ
			while (flightNode != NULL) {
				if (flightNode->data.flightNumber == id) {
					flightNode->data.seats += 1;
					printf("�ѻָ�һ����λ\n");
					break;
				}
				flightNode = flightNode->next;
			}

			// ɾ����Ʊ��¼
			deletePurchase(head, id);

			// ���º����ļ�
			writeToFile(Phead, "Flight.txt");

			printf("��Ʊȡ���ɹ�\n");
		}
		else {
			printf("��ȡ������\n");
		}
	}

void manageFlight(PlinkQueue p)
{
	int i;
	printf("======��ӭ���뺽�����ϵͳ====\n");
	printf("�Ѿ���������ʱ��������Ƚ���");

	while (p->front == -1)
	{
		printf("����Ϊ��");
		return;
	}
	for (i = p->front; i <= p->rear; i++)
	{

		printf("����ţ�%d, ��ʼ�أ�%s, �յ㣺%s, ���ʱ�䣺%s, ��λ����%d, Ʊ�ۣ�%f\n", p->data[i].flightNumber, p->data[i].from,
			p->data[i].to, p->data[i].time, p->data[i].seats, p->data[i].price);

	}
}


//��ӡ��Ʊ
void printView(PQNode head)
{
	PQNode current = head->connect;
	while (current!= NULL)
	{
		printf("%s,%d,%s,%s,%s", current->data.username, current->data.flightNumber, current->data.from, current->data.to,
			current->data.time);
		current = current->connect;

	}

}//�޸��û���
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
	printf("����������û���");
	scanf("%s", name);
	printf("�������������");
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
		printf("����ʧ��\n");
		exit(1);

	}
	while (fgets(line, sizeof(line), file))
	{

		sscanf(line, "%[^,],%[^,],%d,%d", rname, repassword, &IsAdmin, &request);
		if (strcmp(name, rname) == 0 && strcmp(repassword , password)==0)
		{

			if (request == 2&&IsAdmin==0)
			{
				printf("���ύ��������ͬ��");

				printf("������������û���������");
				scanf("%s%s", newname, newpassword);
				fprintf(temp, "%s,%s,%d,%d\n", newname, newpassword, 0, 0);
				fclose(file);
				printf("�����޸ĳɹ�\n");
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
				printf("�Ƿ��ύ�����޸����룬Y OR N\n");
				while ((c = getchar()) != '\n' && c != EOF);  // ��ջ�����
				scanf("%c", &choice1);
				fprintf(temp, "%s,%s,%d,%d\n", rname, repassword, 0, 1);
				printf("�ύ�ɹ�,�ȴ�����Ա����\n");
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
//��������Ϣ
void Adminview(PNode p)
{
	printf("\n��ǰ������Ϣ:\n");
	printf("1. ������ʽ:\n");
	PNode current = p->next;
	while (current != NULL) {
		printf("����ţ�%d����ʼ�أ�%s���յ㣺%s�����ʱ�䣺%s����λ����%d��Ʊ�ۣ�%.2f\n",
			current->data.flightNumber,
			current->data.from,
			current->data.to,
			current->data.time,
			current->data.seats,
			current->data.price);
		current = current->next;
	}
}
// ����Ա�鿴�û��޸��������루��changeUser()ƥ��İ汾��
void UserMessage() {
	int count = 0;
	char username[50] = { 0 };
	char password[50] = { 0 };
	int isadmin, request;
	char line[256] = { 0 };

	FILE* file = fopen("users.txt", "r");
	if (!file) {
		perror("�ļ���ʧ��");
		return;
	}

	FILE* temp = fopen("tmp.txt", "w");
	if (!temp) {
		fclose(file);
		perror("��ʱ�ļ�����ʧ��");
		return;
	}

	printf("�鿴�����޸ĵ��û�����\n");
	int hasRequests = 0;

	while (fgets(line, sizeof(line), file)) {
	
		if (sscanf(line, "%[^,],%[^,],%d,%d",
			username, password, &isadmin, &request) != 4) {
			fputs(line, temp); 
			continue;
		}

		if (request == 1) {  // ƥ���û��ύ������״̬
			hasRequests = 1;
			printf("�������룺�û�[%s] �����޸�����\n", username);
			printf("�Ƿ�ͬ���޸ģ�(Y/N): ");

			// ������뻺����
			int c;
			while ((c = getchar()) != '\n' && c != EOF);

			char choice;
			scanf(" %c", &choice);
			getchar(); 

			if (toupper(choice) == 'Y') {
				
				fprintf(temp, "%s,%s,%d,2\n", username, password, isadmin);
				count++;
				printf("�� ����׼���루�û��´ε�¼���޸����룩\n");
			}
			else {
				
				fprintf(temp, "%s,%s,%d,0\n", username, password, isadmin);
				printf("�� �Ѿܾ�����\n");
			}
		}
		else {
		
			fputs(line, temp);
		}
	}

	fclose(file);
	fclose(temp);

	if (!hasRequests) {
		printf("û���û������޸�����\n");
		remove("tmp.txt");
		return;
	}

	remove("users.bak");
	if (rename("users.txt", "users.bak") == 0) {
		if (rename("tmp.txt", "users.txt") == 0) {
			printf("���봦����ɣ������� %d ������\n", count);
		}
		else {
			perror("�ļ�����ʧ��");
			rename("users.bak", "users.txt");
		}
	}
	else {
		perror("�޷���������");
		remove("tmp.txt");
	}
}


void userMenu(PNode p, PlinkQueue q, TreeNode* root, char filename[], char filename1[], PQNode head) {
	int choice;
	printf("��������������ӭ����˿Ͳ˵����桪����������\n");
	printf("1.�鿴������Ϣ\n");
	printf("2.�����Ʊ\n");
	printf("3.ȡ����Ʊ\n");
	printf("4.��ʾ��Ʊ\n");
	printf("5.�����û���������\n");
	printf("���������ѡ��,0�˳�\n");

	while (1) {
		scanf("%d", &choice);
		if (choice < 0 || choice > 6) {
			printf("ѡ�����������ѡ��\n");
			continue;
		}
		if (choice == 0) {
			break;  // ���� 0 ʱ�˳�ѭ��
		}
		switch (choice) {
		case 1:
			printf("���Զ�Ϊ��չʾ���Ż�ʱ�亽������");
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
	printf("����������ӭ�������Ա�˵����桪����������\n");
	printf("1.�鿴��ǰ����\n");
	printf("2.�Ż����ȵ�ǰ����\n");
	printf("3.ɾ������\n");
	printf("4.���Ӻ���\n");
	printf("5.�û��ύ��Ϣ\n");
	printf("���������ѡ��,�˳�0\n");
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
			printf("����������Ҫɾ���ĺ�����");
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
			printf("�����������������");
			scanf("%d", &a);
			break;

		}
		scanf("%d", &a);
	}
}
int regist() {
	char username[20], password[20];
	int isAdmin;

	printf("\n�û�ע��\n");
	printf("�û���: ");
	scanf("%s", username);
	printf("����: ");
	scanf("%s", password);
	printf("�Ƿ�Ϊ����Ա? 1 or 0 : ");
	scanf("%d", &isAdmin);

	FILE* file = fopen("users.txt", "w+");
	if (file == NULL) {
		printf("�޷����û��ļ�\n");
		return 0;
	}

	fprintf(file, "%s,%s,%d,0\n", username, password, isAdmin);
	fclose(file);

	printf("ע��ɹ���\n");
	return 1;
}

void   login(PlinkQueue p, PNode q, TreeNode* root, char filename[], char filename1[], PQNode head) {
	char username[20], password[20];
	int isAdmin = 0;

	printf("\n�û���¼\n");
	printf("�û���: ");
	scanf("%s", username);
	printf("����: ");
	scanf("%s", password);

	FILE* file = fopen("users.txt", "r");
	if (file == NULL) {
		printf("�޷����û��ļ�\n");
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
		printf("��¼�ɹ���\n");
		if (isAdmin) {
			adminMenu(q, p);
		}
		else {
			userMenu(q, p, root, filename, filename1, head);
		}
	}
	else {
		printf("�û������������\n");
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

	printf("����������������������ӭ���뺽�չ��������ϵͳ��������������������\n");

	int choice;
	while (1)
	{
		printf("���������ѡ��\n");
		printf("1.��¼\n");
		printf("2.ע��\n");
		printf("3.�˳�\n");

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			login(q, new, root, filename1, filename, t);

			break;

		case 2:
			t = regist();
			if (t)
			{
				printf("�Ƿ�����¼ҳ��,Y,OR,N");
				scanf("%c", &choice1);
				if (choice1 == "Y")
				{
					printf("���ڽ���");

					login(q, new, root, filename1, filename, t);
				}
				else {
					break;
				}
			}
			else {
				printf("������");

			}

		case 3:
			printf("�˳�ϵͳ");
			return 0;

		default:
			printf("����������ѡ��");
			break;



		}
	}
	return 0;
}

