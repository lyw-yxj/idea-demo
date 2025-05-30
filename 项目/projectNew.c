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

// 初始化链表
PNode initList() {
    PNode head = (PNode)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    head->next = NULL;
    return head;
}

// 创建新航班节点
PNode createNewNode(Flight x) {
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

// 添加航班（管理员）
void insertPNode(PNode head) {
    Flight flight;
    printf("请输入需要添加的航班号，起始地，终点，起飞时间，票价，座位数: ");
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
    printf("添加成功\n");
}

// 删除购票记录
void deletePurchase(PQNode head, int flightNumber) {
    if (head == NULL || head->connect == NULL) return;

    PQNode current = head;
    while (current->connect != NULL) {
        if (current->connect->data.flightNumber == flightNumber) {
            PQNode temp = current->connect;
            current->connect = temp->connect;
            free(temp);
            printf("删除成功\n");
            return;
        }
        current = current->connect;
    }
    printf("未找到该航班\n");
}

// 删除航班（管理员）
PNode deleteNode(PNode head, int flightNumber) {
    if (head == NULL) {
        printf("链表为空\n");
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
            printf("删除成功\n");
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到该航班\n");
    return head;
}

// 初始化购票链表
PQNode CreatePurchaseList() {
    PQNode head = (PQNode)malloc(sizeof(QNode));
    if (head == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    head->connect = NULL;
    return head;
}

// 创建新购票节点
PQNode NewPurchaseNode(Purchase x) {
    PQNode newNode = (PQNode)malloc(sizeof(QNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = x;
    newNode->connect = NULL;
    return newNode;
}

// 添加购票记录
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

// 创建树节点
TreeNode* createTreeNode(Flight x) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    node->data = x;
    node->LNode = NULL;
    node->RNode = NULL;
    return node;
}

// 插入树节点
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

// 初始化队列
PlinkQueue init_queue() {
    PlinkQueue q = (PlinkQueue)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

// 判断队列是否满
int is_full(PlinkQueue q) {
    return (q->rear == 999);
}

// 判断队列是否空
int is_empty(PlinkQueue q) {
    return (q->front == -1 || q->front > q->rear);
}

// 时间转换为分钟
int time_to_minutes(const char* time) {
    int hours, minutes;
    sscanf(time, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

// 有序入队
void enqueue_sorted(PlinkQueue q, Flight f) {
    if (is_full(q)) {
        printf("队列已满\n");
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

// 出队
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

// 写入航班文件
void writeToFile(PNode head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
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
    printf("文件已写入\n");
}

// 读取航班文件
PNode readFile(PNode head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
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
    printf("文件已读取\n");
    return head;
}

// 读取航班信息到队列
void readFlightMessage(PlinkQueue q, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    Flight f;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%f\n",
        &f.flightNumber, f.from, f.to, f.time, &f.seats, &f.price) == 6) {
        enqueue_sorted(q, f);
    }
    fclose(file);
}

// 加载购票记录
void loadPurchaseList(PQNode head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    Purchase p;
    while (fscanf(file, "%[^,],%d,%[^,],%[^,],%[^\n]\n",
        p.username, &p.flightNumber, p.from, p.to, p.time) == 5) {
        AddPurchase(head, p);
    }
    fclose(file);
}

// 写入购票文件
void writePurchaseFile(PQNode head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
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
    printf("购票文件已写入\n");
}

// 中序遍历树
void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->LNode);
        printf("航班号：%d，起始地：%s，终点：%s，起飞时间：%s，座位数：%d，票价：%.2f\n",
            root->data.flightNumber,
            root->data.from,
            root->data.to,
            root->data.time,
            root->data.seats,
            root->data.price);
        inOrder(root->RNode);
    }
}

// 从文件构建树
TreeNode* buildTreeFromFile(const char* filename, TreeNode* root) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
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

// 初始化航班数据
void initFlightData(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法创建文件\n");
        return;
    }
    fprintf(file, "1001,北京,上海,8:00,23,290.40\n");
    fprintf(file, "1002,南京,成都,13:20,45,230.20\n");
    fprintf(file, "1003,北京,上海,17:15,39,240.70\n");
    fclose(file);
}

// 查看航班
void viewFlight(PNode p, TreeNode* root, PlinkQueue q) {
    printf("-----当前航班信息------\n");
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

    char choice;
    printf("\n是否查看其他排序方式? y or n: ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        printf("\n2. 按时间排序:\n");
        PlinkQueue tempQueue = init_queue();
        readFlightMessage(tempQueue, "flights.txt");

        while (!is_empty(tempQueue)) {
            Flight f = dequeue(tempQueue);
            printf("航班号：%d，起飞时间：%s\n", f.flightNumber, f.time);
        }
        free(tempQueue);

        printf("\n3.按航班号排序:\n");
        inOrder(root);
    }
}

// 预订航班
void bookFlight(PlinkQueue q, const char* filename, PQNode purchaseHead, PNode flightHead) {
    int flightNumber;
    printf("请输入航班号: ");
    scanf("%d", &flightNumber);

    // 查找航班
    PNode current = flightHead->next;
    while (current != NULL) {
        if (current->data.flightNumber == flightNumber) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("未找到该航班\n");
        return;
    }

    if (current->data.seats <= 0) {
        printf("该航班已无余票\n");
        return;
    }

    char username[20];
    printf("请输入用户名: ");
    scanf("%s", username);

    // 创建购票记录
    Purchase p;
    strcpy(p.username, username);
    p.flightNumber = flightNumber;
    strcpy(p.from, current->data.from);
    strcpy(p.to, current->data.to);
    strcpy(p.time, current->data.time);

    // 更新座位数
    current->data.seats--;
    writeToFile(flightHead, filename);

    // 添加购票记录
    AddPurchase(purchaseHead, p);
    writePurchaseFile(purchaseHead, "purchases.txt");

    printf("预订成功！\n");
}

// 取消预订
void cancelBooking(PQNode purchaseHead, PNode flightHead) {
    char username[20];
    int flightNumber;

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入航班号: ");
    scanf("%d", &flightNumber);

    // 查找购票记录
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
        printf("未找到您的预订记录\n");
        return;
    }

    // 更新航班座位数
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
    printf("已成功取消预订\n");
}

// 显示用户购票
void showUserPurchases(PQNode purchaseHead) {
    char username[20];
    printf("请输入用户名: ");
    scanf("%s", username);

    printf("\n您的购票记录:\n");
    PQNode current = purchaseHead->connect;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.username, username) == 0) {
            printf("航班号：%d，起始地：%s，终点：%s，起飞时间：%s\n",
                current->data.flightNumber,
                current->data.from,
                current->data.to,
                current->data.time);
            found = 1;
        }
        current = current->connect;
    }

    if (!found) {
        printf("您没有购票记录\n");
    }
}

// 修改用户信息
void changeUserInfo() {
    char filename[] = "users.txt";
    char tempFile[] = "temp_users.txt";
    char username[20], newUsername[20], password[20];
    int isAdmin, request;

    printf("请输入当前用户名: ");
    scanf("%s", username);
    printf("请输入当前密码: ");
    scanf("%s", password);

    FILE* file = fopen(filename, "r");
    FILE* temp = fopen(tempFile, "w");
    if (file == NULL || temp == NULL) {
        printf("文件操作失败\n");
        return;
    }

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char fileUser[20], filePass[20];
        int fileAdmin, fileRequest;

        sscanf(line, "%[^,],%[^,],%d,%d", fileUser, filePass, &fileAdmin, &fileRequest);

        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            printf("请输入新用户名: ");
            scanf("%s", newUsername);
            printf("请输入新密码: ");
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
        printf("用户信息已更新\n");
    }
    else {
        remove(tempFile);
        printf("用户名或密码错误\n");
    }
}

// 管理员查看航班
void adminViewFlights(PNode head) {
    printf("--------航班管理系统-------\n");
    PNode current = head->next;
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

// 优化航班调度
void optimizeSchedule(PlinkQueue q) {
    printf("\n优化后的航班调度（按时间排序）:\n");
    PlinkQueue tempQueue = init_queue();
    readFlightMessage(tempQueue, "flights.txt");

    while (!is_empty(tempQueue)) {
        Flight f = dequeue(tempQueue);
        printf("航班号：%d，起飞时间：%s\n", f.flightNumber, f.time);
    }
    free(tempQueue);
}

// 处理用户请求
void processUserRequests() {
    printf("\n用户请求处理功能\n");
 
}

// 用户菜单
void userMenu(PNode flightHead, PlinkQueue q, TreeNode* root, PQNode purchaseHead) {
    int choice;
    do {
        printf("-----用户菜单------\n");
        printf("1. 查看航班信息\n");
        printf("2. 预订机票\n");
        printf("3. 取消预订\n");
        printf("4. 查看我的机票\n");
        printf("5. 修改账户信息\n");
        printf("0. 退出\n");
        printf("请选择: ");
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
            printf("返回主菜单\n");
            break;
        default:
            printf("无效选择\n");
        }
    } while (choice != 0);
}

// 管理员菜单
void adminMenu(PNode flightHead, PlinkQueue q) {
    int choice;
    do {
        printf("---管理员菜单---\n");
        printf("1. 查看航班信息\n");
        printf("2. 优化航班调度\n");
        printf("3. 删除航班\n");
        printf("4. 添加航班\n");
        printf("5. 处理用户请求\n");
        printf("0. 退出\n");
        printf("请选择: ");
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
            printf("输入要删除的航班号: ");
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
            printf("返回主菜单\n");
            break;
        default:
            printf("无效选择\n");
        }
    } while (choice != 0);
}

// 用户注册
int registerUser() {
    char username[20], password[20];
    int isAdmin;

    printf("-----用户注册-----\n");
    printf("用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);
    printf("是否为管理员? (1/0): ");
    scanf("%d", &isAdmin);

    FILE* file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("无法打开用户文件\n");
        return 0;
    }

    fprintf(file, "%s,%s,%d,0\n", username, password, isAdmin);
    fclose(file);

    printf("注册成功！\n");
    return 1;
}

// 用户登录
void login(PNode flightHead, PlinkQueue q, TreeNode* root, PQNode purchaseHead) {
    char username[20], password[20];
    int isAdmin = 0;

    printf("----用户登录----\n");
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

        sscanf(line, "%[^,],%[^,],%d,%d", fileUser, filePass, &fileAdmin, &fileRequest);

        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            found = 1;
            isAdmin = fileAdmin;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("登录成功！\n");
        if (isAdmin) {
            adminMenu(flightHead, q);
        }
        else {
            userMenu(flightHead, q, root, purchaseHead);
        }
    }
    else {
        printf("用户名或密码错误\n");
    }
}

int main() {
    // 初始化数据文件
    initFlightData("flights.txt");

    // 初始化数据结构
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
        printf("-------航空管理系统------\n");
        printf("1. 登录\n");
        printf("2. 注册\n");
        printf("3. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            login(flightHead, queue, flightTree, purchaseHead);
            break;
        case 2:
            if (registerUser()) {
                printf("请使用新账户登录\n");
            }
            break;
        case 3:
            printf("谢谢使用，再见！\n");
            break;
        default:
            printf("无效选择\n");
        }
    } while (choice != 3);

    // 释放内存
    free(queue);
  
    return 0;
}