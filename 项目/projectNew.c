#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNUMBER 1000

typedef struct Flight {
    int flightNumber;
    char from[50];
    char to[50];
    char time[30];
    int seats;
    float price;
    struct Flight* next;
} Flight;

typedef struct Passager {
    char username[20];
    char password[20];
    int isAdmin;
    int request;
} User;

typedef struct Purchase {
    char username[20];
    int flightNumber;
    char from[50];
    char to[50];
    char time[30];
} Purchase;

typedef struct Node {
    Flight data;
    struct Node* next;
} Node;
typedef Node* PNode;

typedef struct QNode {
    Purchase data;
    struct QNode* connect;
} QNode;
typedef QNode* PQNode;

typedef struct TreeNode {
    Flight data;
    struct TreeNode* LNode;
    struct TreeNode* RNode;
} TreeNode;

typedef struct Queue {
    Flight data[1000];
    int front;
    int rear;
} Queue;
typedef Queue* PlinkQueue;

// ��ʼ������
PNode initList() {
    PNode head = (PNode)malloc(sizeof(Node));
    if (head == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    head->next = NULL;
    return head;
}

// �����º���ڵ�
PNode createNewNode(Flight x) {
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

// ��Ӻ��ࣨ����Ա��
void insertPNode(PNode head) {
    Flight flight;
    printf("��������Ҫ��ӵĺ���ţ���ʼ�أ��յ㣬���ʱ�䣬Ʊ�ۣ���λ��: ");
    scanf("%d %s %s %s %f %d",
        &flight.flightNumber,
        flight.from,
        flight.to,
        flight.time,
        &flight.price,
        &flight.seats);

    PNode newNode = createNewNode(flight);
    PNode current = head;

    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    printf("��ӳɹ�\n");
}

// ɾ����Ʊ��¼
void deletePurchase(PQNode head, int flightNumber) {
    if (head == NULL || head->connect == NULL) return;

    PQNode current = head;
    while (current->connect != NULL) {
        if (current->connect->data.flightNumber == flightNumber) {
            PQNode temp = current->connect;
            current->connect = temp->connect;
            free(temp);
            printf("ɾ���ɹ�\n");
            return;
        }
        current = current->connect;
    }
    printf("δ�ҵ��ú���\n");
}

// ɾ�����ࣨ����Ա��
PNode deleteNode(PNode head, int flightNumber) {
    if (head == NULL) {
        printf("����Ϊ��\n");
        return NULL;
    }

    PNode current = head;
    PNode prev = NULL;

    while (current != NULL) {
        if (current->data.flightNumber == flightNumber) {
            if (prev == NULL) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("ɾ���ɹ�\n");
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("δ�ҵ��ú���\n");
    return head;
}

// ��ʼ����Ʊ����
PQNode CreatePurchaseList() {
    PQNode head = (PQNode)malloc(sizeof(QNode));
    if (head == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    head->connect = NULL;
    return head;
}

// �����¹�Ʊ�ڵ�
PQNode NewPurchaseNode(Purchase x) {
    PQNode newNode = (PQNode)malloc(sizeof(QNode));
    if (newNode == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newNode->data = x;
    newNode->connect = NULL;
    return newNode;
}

// ��ӹ�Ʊ��¼
void AddPurchase(PQNode head, Purchase x) {
    PQNode newNode = NewPurchaseNode(x);
    if (head->connect == NULL) {
        head->connect = newNode;
    }
    else {
        PQNode current = head->connect;
        while (current->connect != NULL) {
            current = current->connect;
        }
        current->connect = newNode;
    }
}

// �������ڵ�
TreeNode* createTreeNode(Flight x) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    node->data = x;
    node->LNode = NULL;
    node->RNode = NULL;
    return node;
}

// �������ڵ�
TreeNode* insertNodeTree(TreeNode* root, Flight x) {
    if (root == NULL) {
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

// ��ʼ������
PlinkQueue init_queue() {
    PlinkQueue q = (PlinkQueue)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

// �ж϶����Ƿ���
int is_full(PlinkQueue q) {
    return (q->rear == 999);
}

// �ж϶����Ƿ��
int is_empty(PlinkQueue q) {
    return (q->front == -1 || q->front > q->rear);
}

// ʱ��ת��Ϊ����
int time_to_minutes(const char* time) {
    int hours, minutes;
    sscanf(time, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

// �������
void enqueue_sorted(PlinkQueue q, Flight f) {
    if (is_full(q)) {
        printf("��������\n");
        return;
    }

    if (is_empty(q)) {
        q->front = 0;
        q->rear = 0;
        q->data[0] = f;
        return;
    }

    int pos;
    for (pos = q->front; pos <= q->rear; pos++) {
        if (time_to_minutes(f.time) < time_to_minutes(q->data[pos].time)) {
            break;
        }
    }

    for (int i = q->rear + 1; i > pos; i--) {
        q->data[i] = q->data[i - 1];
    }

    q->data[pos] = f;
    q->rear++;
}

// ����
Flight dequeue(PlinkQueue q) {
    if (is_empty(q)) {
        Flight empty = { 0 };
        return empty;
    }
    Flight f = q->data[q->front];
    q->front++;

    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }

    return f;
}

// д�뺽���ļ�
void writeToFile(PNode head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    PNode current = head->next;
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
    printf("�ļ���д��\n");
}

// ��ȡ�����ļ�
PNode readFile(PNode head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return head;
    }

    Flight f;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%f\n",
        &f.flightNumber, f.from, f.to, f.time, &f.seats, &f.price) == 6) {
        PNode newNode = createNewNode(f);
        PNode current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    fclose(file);
    printf("�ļ��Ѷ�ȡ\n");
    return head;
}

// ��ȡ������Ϣ������
void readFlightMessage(PlinkQueue q, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    Flight f;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%f\n",
        &f.flightNumber, f.from, f.to, f.time, &f.seats, &f.price) == 6) {
        enqueue_sorted(q, f);
    }
    fclose(file);
}

// ���ع�Ʊ��¼
void loadPurchaseList(PQNode head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    Purchase p;
    while (fscanf(file, "%[^,],%d,%[^,],%[^,],%[^\n]\n",
        p.username, &p.flightNumber, p.from, p.to, p.time) == 5) {
        AddPurchase(head, p);
    }
    fclose(file);
}

// д�빺Ʊ�ļ�
void writePurchaseFile(PQNode head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    PQNode current = head->connect;
    while (current != NULL) {
        fprintf(file, "%s,%d,%s,%s,%s\n",
            current->data.username,
            current->data.flightNumber,
            current->data.from,
            current->data.to,
            current->data.time);
        current = current->connect;
    }
    fclose(file);
    printf("��Ʊ�ļ���д��\n");
}

// ���������
void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->LNode);
        printf("����ţ�%d����ʼ�أ�%s���յ㣺%s�����ʱ�䣺%s����λ����%d��Ʊ�ۣ�%.2f\n",
            root->data.flightNumber,
            root->data.from,
            root->data.to,
            root->data.time,
            root->data.seats,
            root->data.price);
        inOrder(root->RNode);
    }
}

// ���ļ�������
TreeNode* buildTreeFromFile(const char* filename, TreeNode* root) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return root;
    }

    Flight f;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%f\n",
        &f.flightNumber, f.from, f.to, f.time, &f.seats, &f.price) == 6) {
        root = insertNodeTree(root, f);
    }
    fclose(file);
    return root;
}

// ��ʼ����������
void initFlightData(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷������ļ�\n");
        return;
    }
    fprintf(file, "1001,����,�Ϻ�,8:00,23,290.40\n");
    fprintf(file, "1002,�Ͼ�,�ɶ�,13:20,45,230.20\n");
    fprintf(file, "1003,����,�Ϻ�,17:15,39,240.70\n");
    fclose(file);
}

// �鿴����
void viewFlight(PNode p, TreeNode* root, PlinkQueue q) {
    printf("-----��ǰ������Ϣ------\n");
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

    char choice;
    printf("\n�Ƿ�鿴��������ʽ? y or n: ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        printf("\n2. ��ʱ������:\n");
        PlinkQueue tempQueue = init_queue();
        readFlightMessage(tempQueue, "flights.txt");

        while (!is_empty(tempQueue)) {
            Flight f = dequeue(tempQueue);
            printf("����ţ�%d�����ʱ�䣺%s\n", f.flightNumber, f.time);
        }
        free(tempQueue);

        printf("\n3.�����������:\n");
        inOrder(root);
    }
}

// Ԥ������
void bookFlight(PlinkQueue q, const char* filename, PQNode purchaseHead, PNode flightHead) {
    int flightNumber;
    printf("�����뺽���: ");
    scanf("%d", &flightNumber);

    // ���Һ���
    PNode current = flightHead->next;
    while (current != NULL) {
        if (current->data.flightNumber == flightNumber) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("δ�ҵ��ú���\n");
        return;
    }

    if (current->data.seats <= 0) {
        printf("�ú���������Ʊ\n");
        return;
    }

    char username[20];
    printf("�������û���: ");
    scanf("%s", username);

    // ������Ʊ��¼
    Purchase p;
    strcpy(p.username, username);
    p.flightNumber = flightNumber;
    strcpy(p.from, current->data.from);
    strcpy(p.to, current->data.to);
    strcpy(p.time, current->data.time);

    // ������λ��
    current->data.seats--;
    writeToFile(flightHead, filename);

    // ��ӹ�Ʊ��¼
    AddPurchase(purchaseHead, p);
    writePurchaseFile(purchaseHead, "purchases.txt");

    printf("Ԥ���ɹ���\n");
}

// ȡ��Ԥ��
void cancelBooking(PQNode purchaseHead, PNode flightHead) {
    char username[20];
    int flightNumber;

    printf("�������û���: ");
    scanf("%s", username);
    printf("�����뺽���: ");
    scanf("%d", &flightNumber);

    // ���ҹ�Ʊ��¼
    PQNode prev = purchaseHead;
    PQNode current = purchaseHead->connect;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.username, username) == 0 &&
            current->data.flightNumber == flightNumber) {
            prev->connect = current->connect;
            free(current);
            found = 1;
            break;
        }
        prev = current;
        current = current->connect;
    }

    if (!found) {
        printf("δ�ҵ�����Ԥ����¼\n");
        return;
    }

    // ���º�����λ��
    PNode flightNode = flightHead->next;
    while (flightNode != NULL) {
        if (flightNode->data.flightNumber == flightNumber) {
            flightNode->data.seats++;
            writeToFile(flightHead, "flights.txt");
            break;
        }
        flightNode = flightNode->next;
    }

    writePurchaseFile(purchaseHead, "purchases.txt");
    printf("�ѳɹ�ȡ��Ԥ��\n");
}

// ��ʾ�û���Ʊ
void showUserPurchases(PQNode purchaseHead) {
    char username[20];
    printf("�������û���: ");
    scanf("%s", username);

    printf("\n���Ĺ�Ʊ��¼:\n");
    PQNode current = purchaseHead->connect;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.username, username) == 0) {
            printf("����ţ�%d����ʼ�أ�%s���յ㣺%s�����ʱ�䣺%s\n",
                current->data.flightNumber,
                current->data.from,
                current->data.to,
                current->data.time);
            found = 1;
        }
        current = current->connect;
    }

    if (!found) {
        printf("��û�й�Ʊ��¼\n");
    }
}

// �޸��û���Ϣ
void changeUserInfo() {
    char filename[] = "users.txt";
    char tempFile[] = "temp_users.txt";
    char username[20], newUsername[20], password[20];
    int isAdmin, request;

    printf("�����뵱ǰ�û���: ");
    scanf("%s", username);
    printf("�����뵱ǰ����: ");
    scanf("%s", password);

    FILE* file = fopen(filename, "r");
    FILE* temp = fopen(tempFile, "w");
    if (file == NULL || temp == NULL) {
        printf("�ļ�����ʧ��\n");
        return;
    }

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char fileUser[20], filePass[20];
        int fileAdmin, fileRequest;

        sscanf(line, "%[^,],%[^,],%d,%d", fileUser, filePass, &fileAdmin, &fileRequest);

        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            printf("���������û���: ");
            scanf("%s", newUsername);
            printf("������������: ");
            scanf("%s", password);

            fprintf(temp, "%s,%s,%d,%d\n", newUsername, password, fileAdmin, 0);
            found = 1;
        }
        else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(filename);
        rename(tempFile, filename);
        printf("�û���Ϣ�Ѹ���\n");
    }
    else {
        remove(tempFile);
        printf("�û������������\n");
    }
}

// ����Ա�鿴����
void adminViewFlights(PNode head) {
    printf("--------�������ϵͳ-------\n");
    PNode current = head->next;
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

// �Ż��������
void optimizeSchedule(PlinkQueue q) {
    printf("\n�Ż���ĺ�����ȣ���ʱ������:\n");
    PlinkQueue tempQueue = init_queue();
    readFlightMessage(tempQueue, "flights.txt");

    while (!is_empty(tempQueue)) {
        Flight f = dequeue(tempQueue);
        printf("����ţ�%d�����ʱ�䣺%s\n", f.flightNumber, f.time);
    }
    free(tempQueue);
}

// �����û�����
void processUserRequests() {
    printf("\n�û���������\n");
 
}

// �û��˵�
void userMenu(PNode flightHead, PlinkQueue q, TreeNode* root, PQNode purchaseHead) {
    int choice;
    do {
        printf("-----�û��˵�------\n");
        printf("1. �鿴������Ϣ\n");
        printf("2. Ԥ����Ʊ\n");
        printf("3. ȡ��Ԥ��\n");
        printf("4. �鿴�ҵĻ�Ʊ\n");
        printf("5. �޸��˻���Ϣ\n");
        printf("0. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            viewFlight(flightHead, root, q);
            break;
        case 2:
            bookFlight(q, "flights.txt", purchaseHead, flightHead);
            break;
        case 3:
            cancelBooking(purchaseHead, flightHead);
            break;
        case 4:
            showUserPurchases(purchaseHead);
            break;
        case 5:
            changeUserInfo();
            break;
        case 0:
            printf("�������˵�\n");
            break;
        default:
            printf("��Чѡ��\n");
        }
    } while (choice != 0);
}

// ����Ա�˵�
void adminMenu(PNode flightHead, PlinkQueue q) {
    int choice;
    do {
        printf("---����Ա�˵�---\n");
        printf("1. �鿴������Ϣ\n");
        printf("2. �Ż��������\n");
        printf("3. ɾ������\n");
        printf("4. ��Ӻ���\n");
        printf("5. �����û�����\n");
        printf("0. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            adminViewFlights(flightHead);
            break;
        case 2:
            optimizeSchedule(q);
            break;
        case 3: {
            int flightNumber;
            printf("����Ҫɾ���ĺ����: ");
            scanf("%d", &flightNumber);
            flightHead = deleteNode(flightHead, flightNumber);
            writeToFile(flightHead, "flights.txt");
            break;
        }
        case 4:
            insertPNode(flightHead);
            writeToFile(flightHead, "flights.txt");
            break;
        case 5:
            processUserRequests();
            break;
        case 0:
            printf("�������˵�\n");
            break;
        default:
            printf("��Чѡ��\n");
        }
    } while (choice != 0);
}

// �û�ע��
int registerUser() {
    char username[20], password[20];
    int isAdmin;

    printf("-----�û�ע��-----\n");
    printf("�û���: ");
    scanf("%s", username);
    printf("����: ");
    scanf("%s", password);
    printf("�Ƿ�Ϊ����Ա? (1/0): ");
    scanf("%d", &isAdmin);

    FILE* file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("�޷����û��ļ�\n");
        return 0;
    }

    fprintf(file, "%s,%s,%d,0\n", username, password, isAdmin);
    fclose(file);

    printf("ע��ɹ���\n");
    return 1;
}

// �û���¼
void login(PNode flightHead, PlinkQueue q, TreeNode* root, PQNode purchaseHead) {
    char username[20], password[20];
    int isAdmin = 0;

    printf("----�û���¼----\n");
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

        sscanf(line, "%[^,],%[^,],%d,%d", fileUser, filePass, &fileAdmin, &fileRequest);

        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            found = 1;
            isAdmin = fileAdmin;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("��¼�ɹ���\n");
        if (isAdmin) {
            adminMenu(flightHead, q);
        }
        else {
            userMenu(flightHead, q, root, purchaseHead);
        }
    }
    else {
        printf("�û������������\n");
    }
}

int main() {
    // ��ʼ�������ļ�
    initFlightData("flights.txt");

    // ��ʼ�����ݽṹ
    PNode flightHead = initList();
    flightHead = readFile(flightHead, "flights.txt");

    PlinkQueue queue = init_queue();
    readFlightMessage(queue, "flights.txt");

    TreeNode* flightTree = NULL;
    flightTree = buildTreeFromFile("flights.txt", flightTree);

    PQNode purchaseHead = CreatePurchaseList();
    loadPurchaseList(purchaseHead, "purchases.txt");

    int choice;
    do {
        printf("-------���չ���ϵͳ------\n");
        printf("1. ��¼\n");
        printf("2. ע��\n");
        printf("3. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            login(flightHead, queue, flightTree, purchaseHead);
            break;
        case 2:
            if (registerUser()) {
                printf("��ʹ�����˻���¼\n");
            }
            break;
        case 3:
            printf("ллʹ�ã��ټ���\n");
            break;
        default:
            printf("��Чѡ��\n");
        }
    } while (choice != 3);

    // �ͷ��ڴ�
    free(queue);
  
    return 0;
}