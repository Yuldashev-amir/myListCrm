// ������� ������� ���� �� ������ ����������� ������. ��� ���� ������� crm-�������

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#define CLS system("cls")
#define FFLUSH while(getchar() != '\n')

#define MAX_TITLE 50
#define MAX_DESC 250
#define MAX_BRIEF 300

/* ����� ������� ������ � ������� ��������-�������� */

struct task
{
    unsigned id; // ���������� ����� ������
    char titleTask[MAX_TITLE]; // ��������� ������
    char descriptionTask[MAX_DESC]; // �������� ������
    char briefTask[MAX_BRIEF]; // ����������� �������
    struct task * next; // ����� ���������� ����

};

struct task * firstNode;
struct task * newNode;
struct task * current;

char * filename = "list.dat";   // ��� ����� ��� ����� ��������� ������

// ���������� �������
int showMenu(void); // �������� ������
void addNode(void); // ���������� ������ ���� � ����� ���������� ������
void removeNode(void); // �������� ���� �� ���������� ������
void showList(void); // �������� ��� �������� ���������� ������
struct task * memAlloc(void); // ��������� ������ ��� ����� ���� ���������� ������
char * s_gets(char * st, int n); // ������� ����� ������ ����� ���� ������
time_t taimer(void);
void loadList(void);
void saveList(void);


int main(void)
{
    system("chcp 1251 > 0");
    int choice = '\0'; // ����� ������������
    firstNode = NULL; // ���������� ������ ����.

    loadList(); // ��������� �������� �������� ������ ��� ������� ���������

    while(choice != 'Q') // ���� �� ������ ���� Q - ������������ ������
    {
        choice = showMenu();
        switch (choice)
        {
        case 'S':
            CLS;
            showList();
            saveList();
            break;
        case 'A':
            CLS;
            addNode();
            saveList();
            break;
        case 'R':
            CLS;
            removeNode();
            saveList();
            break;
        case 'Q':
            system("pause");
            puts("Exit");
            saveList();
            break;
        case 'T':
            CLS;
            puts("time on work for task\n");
            taimer();
        default:
            CLS;
            puts("Incorrect input");
            saveList();
            break;
        }
    }
    putchar('\n');
    printf("seconds 0.%lf", taimer);
    return 0;
}

int showMenu(void)
{
    int ch = '\0';
    printf("A - add Task, R - remove Task, S - show list, Q - exit in program\n");
    ch = getch();   // ��� ���������������
    return (toupper(ch));
}

struct task * memAlloc(void)
{
    struct task * temp;
    temp = (struct task *)malloc(sizeof(struct task));
    if(temp == NULL)
    {
        perror("Error of allocation\n Exit...");
        system("pause");
        exit(EXIT_FAILURE);
    }
    return temp;
};

void addNode()
{
    if(firstNode == NULL) // ������ �������� ������� ����-�� ������ ��������
    {
        firstNode = memAlloc(); // ������� ������ �������
        current = firstNode; // ������� ��� �������
    }
    else // ���� � ������ ��� ���� ��������
    {
        current = firstNode;
        while(current->next != NULL) // ���� ��������� ������� ������
            current = current->next; // � ������ ��� �������
        newNode = memAlloc(); // ������� ����� �������
        current->next = newNode; // ��������� ��� � ����� ������
        current = newNode; // ������� ��� �������
    }

    printf("��������� ��������� ����������.\n\
            1 - ����� �������,\n \
            2 - �������,\n \
            3 - ��������� ����� (������� ���������),\n\
            4 - �� ������,\n\
            5 - ������� �� ��������� (�� ������������)\n");

    fflush(stdin);
    scanf(&current->id);
    puts("������� ��������� ����� ������ �� ������� (�� ����� 50 ��������):\n");
    s_gets(current->titleTask, MAX_TITLE);
    puts("������� �������� ����� ������ ��� ��������� ��� ������� (�� ����� 250 ��������):\n");
    s_gets(current->descriptionTask, MAX_DESC);
    puts("��������� ��������� ����������� ������� �� ����� ������ (�� ����� 500 ��������):\n");
    s_gets(current->briefTask, MAX_BRIEF);
    current->next = NULL; // ����� �� ������, ������� ����� ����������
                          // �� ������������� �������� (������� ������)
}

// ������� ���� ������ �� �����
void showList(void)
{
    int count = 1; // ����� ���������� ��������

    if(firstNode == NULL) // ���� ������ ������
    {
        printf("������ ����! �������� � ���� ��������\n");
        return;
    }
    puts("������:\n");
    current = firstNode; // �������� ����� ������ � ������� ��������
    while (current != NULL) // ���� �������� ����������
    {
        printf("������ � %u:\n �������� ������ %s\n ���� �� ������%s\n", count, current->descriptionTask, current->briefTask);
        current = current->next; // ������ ��������� ���� �������
        count++;
    }
    putchar('\n');
}

void removeNode(void)
{
    struct task * previous; // ����� ��������������� �������� ����������
    unsigned delNum; // ����� ���������� ����
    unsigned num = 1; // ������� �� ������� �������

    if(firstNode == NULL) // �������� ���� �� ����-�� ���� �������
    {
        puts("������ ������! ������� ������");
        return;
    }
    puts("���������� �������� ���� ��� ��������:\n");
    showList(); // ������� ������
    printf("������� ����: ");
    fflush(stdin);
    scanf(" %u", &delNum);
    FFLUSH;
    current = firstNode; // ������ ������ ���� �������
    previous = NULL; // � ������� �������� ��� �����������
    while(num != delNum) // �������� ���� �� � ����� ����� �������
    {
            previous = current; // ��������� ������� ��������
            current = current->next; // ������� ������ �� �������
            num++;
            if(current == NULL) // �������� ����� ������
            {
                puts("����� ������ � ������ ���.\n");
                return;
            }
    }
    if(previous == NULL) // ���� ������� ������ �������
        firstNode = current->next; // ������� ������ ��������� �������
    else // ���������� ������ ������ ��������� �� ���������
        // ��� �� ������������ �������
        previous->next = current->next;

    printf("������ N%u �������\n", delNum);
    putchar('\n');
    free(current); // ������������ ������ ���������� ����
    return;
}

char * s_gets(char * st, int n)
{
    fflush(stdin);
    char * ret_val;
    int i = 0;
    ret_val = fgets(st, n, stdin);
    if(ret_val)
    {
        while(st[i] != '\n' && st[i] != '\0')
            i++;
        if(st[i] == '\n')
            st[i] = '\0';
        else // ��������� ������� words[i] == '\0'
            while(getchar() != '\n')
                continue;
    }
    return ret_val;
}

void loadList(void)
{
    FILE * fptr;
    struct task loaded;
    int records = 0;

    fptr = fopen(filename, "rb+");
    if(fptr == NULL)
        return;

    // fread(&loaded, sizeof(struct task), 1, fptr);

    while(fread(&loaded, sizeof(struct task), 1, fptr))
    {
        if(firstNode == NULL)
        {
            firstNode = memAlloc();
            current = firstNode;
        }
        else
        {
            current = firstNode;
            while(current->next)
                current = current->next;
            newNode = memAlloc();
            current->next = newNode;
            current = newNode;
        }
        current->id = loaded.id;
        current->titleTask[MAX_TITLE] = loaded.titleTask[MAX_TITLE];
        current->descriptionTask[MAX_DESC] = loaded.descriptionTask[MAX_DESC];
        current->briefTask[MAX_BRIEF] = loaded.briefTask[MAX_BRIEF];

        current->next = NULL;
        records++;
    }
    fclose(fptr);
    printf("%d records read frpm \'%s'\n", records, filename);
}

void saveList(void)
{
    int records = 0;
    FILE * fptr;

    fptr = fopen(filename, "wb+");
        if(fptr == NULL)
        {
            puts("It is not possible to create file for save!\n");
            return;
        }
    current = firstNode;
    while(current)
    {
        fwrite(current, sizeof(struct task), 1, fptr);
        current = current->next;
        records++;
    }
    fclose(fptr);
    printf("%d records are written to the \'%s\'\n", records, filename);
}

time_t taimer(void)
{
    time_t start = clock();
    printf("taimer %lf", start);
}




