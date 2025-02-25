// Создаем простую СУБД на основе сввязанного списка. Как базу будущей crm-системы

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

/* Будем хранить данные о заказах интернет-магазина */

struct task
{
    unsigned id; // Уникальный номер заказа
    char titleTask[MAX_TITLE]; // Заголовок задачи
    char descriptionTask[MAX_DESC]; // Описание задачи
    char briefTask[MAX_BRIEF]; // Техническое задание
    struct task * next; // Адрес следующего узла

};

struct task * firstNode;
struct task * newNode;
struct task * current;

char * filename = "list.dat";   // Имя файла где будем сохранять данные

// Добавление функций
int showMenu(void); // Показать список
void addNode(void); // Добавление нового узла в конец связанного списка
void removeNode(void); // Удаление узла из связанного списка
void showList(void); // Показать все элементы связанного списка
struct task * memAlloc(void); // Выделение памяти под новый узел связанного списка
char * s_gets(char * st, int n); // Функция ввода данных полям узла списка
time_t taimer(void);
void loadList(void);
void saveList(void);


int main(void)
{
    system("chcp 1251 > 0");
    int choice = '\0'; // Выбор пользователя
    firstNode = NULL; // Изначально список пуст.

    loadList(); // Загружаем элементы связного списка при запуске программы

    while(choice != 'Q') // Пока не выбран знак Q - обрабатывать список
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
    ch = getch();   // Для интерактивности
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
    if(firstNode == NULL) // Сперва проверка наличия хотя-бы одного элемента
    {
        firstNode = memAlloc(); // Создать первый элемент
        current = firstNode; // Сделать его текущим
    }
    else // Если в списке уже есть элементы
    {
        current = firstNode;
        while(current->next != NULL) // Ищем последний элемент списка
            current = current->next; // И делаем его текущим
        newNode = memAlloc(); // Создали новый элемент
        current->next = newNode; // Поставили его в конец списка
        current = newNode; // Сделаем его текущим
    }

    printf("Поставьте приоритет выполнения.\n\
            1 - Самое срочное,\n \
            2 - Срочное,\n \
            3 - Ближайшее время (Средний приоритет),\n\
            4 - Не срочно,\n\
            5 - Дедлайн не определен (На согласовании)\n");

    fflush(stdin);
    scanf(&current->id);
    puts("Введите заголовок вашей задачи на сегодня (Не более 50 символов):\n");
    s_gets(current->titleTask, MAX_TITLE);
    puts("Введите описание вашей задачи или дополните под задачей (Не более 250 символов):\n");
    s_gets(current->descriptionTask, MAX_DESC);
    puts("Распишите подробное техничесоке задание по вашей задаче (Не более 500 символов):\n");
    s_gets(current->briefTask, MAX_BRIEF);
    current->next = NULL; // нужно не забыть, указать адрес следующего
                          // не существующего элемента (закрыть список)
}

// Выводим весь список на экран
void showList(void)
{
    int count = 1; // Номер выводимого элемента

    if(firstNode == NULL) // Если список пустой
    {
        printf("Список пуст! Добавьте в него элементы\n");
        return;
    }
    puts("Список:\n");
    current = firstNode; // Начинаем обход списка с первого элемента
    while (current != NULL) // Пока элементы существуют
    {
        printf("Запись № %u:\n Описание задачи %s\n Бриф на работу%s\n", count, current->descriptionTask, current->briefTask);
        current = current->next; // Делаем следующий узел текущим
        count++;
    }
    putchar('\n');
}

void removeNode(void)
{
    struct task * previous; // Адрес предшествующего элемента удаляемому
    unsigned delNum; // Номер удаляемого узла
    unsigned num = 1; // Текущий по порядку элемент

    if(firstNode == NULL) // Проверка есть ли хотя-бы один элемент
    {
        puts("Список пустой! удалять нечего");
        return;
    }
    puts("Пожалуйста выберите узел для удаления:\n");
    showList(); // Выводим список
    printf("Удалить узел: ");
    fflush(stdin);
    scanf(" %u", &delNum);
    FFLUSH;
    current = firstNode; // Делаем первый узел текущим
    previous = NULL; // У первого элемента нет предыдущего
    while(num != delNum) // Проверим есть ли в цикле такой элемент
    {
            previous = current; // Сохраняем текущее значение
            current = current->next; // Обходим список по порядку
            num++;
            if(current == NULL) // Достигли конца списка
            {
                puts("Такой записи в списке нет.\n");
                return;
            }
    }
    if(previous == NULL) // Если удаляем первый элемент
        firstNode = current->next; // Сделать первым следующий элемент
    else // Предыдущая запись должна указывать на следующую
        // как бы перескакивая текущую
        previous->next = current->next;

    printf("Запись N%u удалена\n", delNum);
    putchar('\n');
    free(current); // Высвобождаем память удаленного узла
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
        else // Требуется надичие words[i] == '\0'
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




