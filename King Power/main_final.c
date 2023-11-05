#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBOOKS 40

//用户结构体定义
typedef struct user {
    char name[20];
    char password[20];
    char id[12];
    struct user* next;
} User;

//书籍结构体定义
typedef struct book {
    char ISBN[14];
    char name[50];
    char author[50];
    char publisher[50];
    int year;
    char shelf[10];
    int floor;
    int borrow;
    int lei;
    char leiname[50];
} Book;

//链表定义
typedef struct bookfile
{
    Book bookdata;
    struct bookfile* next;
} Bookfile;


//全局变量声明

Book bookfile[MAXBOOKS];
int booknum;
int length = sizeof(bookfile) / sizeof(Book);
char username[20];
//定义链表头
User* head = NULL;


//函数声明
int registerUser();//注册函数
int loginUser(char* m);//登录函数
void addBook();//添加图书
void deleteBook();//删除图书
void borrowBook(char* n);//借阅图书
void returnBook(char* username);//归还图书
void searchBook();//查询图书
void ReaderMenu();//读者界面
void ManagerMenu();//管理员界面
void BeginMenu();//开始菜单
void userSearchMenu();//用户查询菜单
void managerSearchMenu();//管理员查询菜单
void dayi();//答疑系统
void yanzhengma();//验证码
void bookreview();//书评查询
void tuijian();//好书推荐
void mohu();//模糊查询
void suijisearchBook();//随机选书
void gexinghua(); //个性化推荐
void outlei(struct book *p);
void feedback();//反馈与评价
void searchfeedback();//查询反馈与评价
Bookfile* creathead();//创建表头
Bookfile* creatnode(Book newbook);//创建节点
void erweima();//二维码

//主函数
int main()
{
    int flag_1, flag_2, flag_3, flag_4,
        cash_1, cash_2;
    int choice;


    cash_1 = cash_2 = 1;
    yanzhengma();
    while (1) {
        //登录页面
        BeginMenu();
        scanf("%d", &choice);//登录与注册的分支
        switch (choice) {
        case 1:


            flag_1 = loginUser(username);
            cash_1 = 1;
            //flag_1=1为读者登录，2为管理者登录
            switch (flag_1)
            {
            case 1://读者模块
                while (cash_1) {

                    ReaderMenu();//读者页面

                    scanf("%d", &choice);//读者操作的分支
                    switch (choice)
                    {
                    case 1://借还图书等
                        borrowBook(username);//借阅图书
                        break;
                    case 2:
                        returnBook(username);//归还图书
                        break;
                    case 3:
                        userSearchMenu();
                        searchBook();//查询图书
                        break;
                    case 4:
                        bookreview();//书评查询
                        break;
                    case 5:
                        dayi();//答疑
                        break;
                    case 6:
                        suijisearchBook();//随机查询
                        break;
                    case 7:
                        tuijian();//好书推荐
                        break;
                    case 8:
                        gexinghua(); //个性化推荐
                        break;
                    case 9:
                        feedback();//反馈与评价
                        break;
                    case 10:
                        erweima();
                        break;
                    case 0:cash_1 = 0; break;
                    default:
                        break;
                    }
                }

                break;
            case 2://管理员模块
                while (cash_1) {
                    ManagerMenu();
                    //管理员页面
                    scanf("%d", &choice);//读者操作的分支
                    switch (choice)
                    {
                    case 1://增添图书
                        addBook(); break;
                    case 2: // 查询图书
                        managerSearchMenu();
                        searchBook(); break;
                    case 3://查询反馈与评价
                        searchfeedback();
                        break;
                    case 0:cash_1 = 0; break;
                    default:
                        break;
                    }
                }
                break;
            case 0:
                break;
            default:
                break;
            }

            break;
        case 2:

            registerUser();
            break;
        case 0:
            exit(0);
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }

    return 0;
}



//函数定义


//创建表头
Bookfile* creathead()
{
    Bookfile* head = (Bookfile*)malloc(sizeof(Bookfile));
    head->next = NULL;
    return head;
}

//创建节点
Bookfile* creatnode(Book newbook)
{
    Bookfile* Newbookfile= (Bookfile*)malloc(sizeof(Bookfile));
    Newbookfile->next = NULL;
    return Newbookfile;
}



//注册函数
int registerUser() {
    int i;
    system("cls");
    User* newUser = (User*)malloc(sizeof(User));
    printf("\n");
    printf("\t|--------------------图书管理系统-------------------------|\n");
    printf("\t|                      注册系统                           |\n");
    printf("\t|                    你好，新同学！                       |\n");
    printf("\t|                学号:_____________                       |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", newUser->id);
    printf("\t|                账号:_____________                       |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", newUser->name);
    printf("\t|                密码:____________                        |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", newUser->password);
    newUser->next = head;
    head = newUser;

    //将用户信息保存到文件中
    FILE* fp = fopen("users.txt", "a");
    fprintf(fp, "%s %s\n", newUser->name, newUser->password);
    fclose(fp);

    printf("\t\t\t 注册成功！！！按回车键登录……\n");
    getchar();
    getchar();
}

//登录函数
int loginUser(char* username) {
    char name[20], password[20];
    int result, i;
    system("cls");
    printf("\n");
    printf("\t|--------------------图书管理系统-------------------------|\n");
    printf("\t|                      登录系统                           |\n");
    printf("\t|                账号:_____________                       |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", name);
    printf("\t|                密码:____________                        |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", password);

    //从文件中读取用户信息并验证
    FILE* fp = fopen("users.txt", "r");
    char file_name[20], file_password[20];
    while (fscanf(fp, "%s %s", file_name, file_password) != EOF) {
        if (strcmp(file_name, name) == 0 && strcmp(file_password, password) == 0) {
            printf("\t\t\t    登录成功！！！\n");
            strcpy(username, name);
            getchar();
            getchar();
            fclose(fp);
            result = 1;
            return result;
        }
        else if (strcmp("guanli", name) == 0 && strcmp("guanli", password) == 0) {
            printf("\t\t\t   欢迎管理员！！！\n");
            getchar();
            getchar();
            fclose(fp);
            result = 2;
            return result;
        }
    }
    fclose(fp);
    printf("\t\t    用户名或密码错误，请重新输入。\n");
    getchar();
    getchar();
}


//验证码
void yanzhengma() {
    int code, input, i;
    int try3;
    try3 = 1;
    while (try3 = 1) {

        code = rand() % 9000 + 1000; // generate a random 4-digit code
        printf("\n");
        printf("\t|--------------------图书管理系统-------------------------|\n");
        printf("\t|            为确保您是人类，请输入验证码                 |\n");
        printf("\t|                        %d                             |\n", code);
        printf("\t|              验证码:____                                |");
        for (i = 0; i < 37; i++)	printf("\b");
        scanf("%d", &input);
        if (input == code) {

            printf("\t|                 验证码正确，欢迎进入\n");

            break;
        }
        else {
            printf("\t|                 验证码错误，请重新输入\n");
        }
    }





}

//增添图书
void addBook()//增添图书
{
    Book book;
    FILE* fp;
    int i, k = 0;
    struct book* p;
    p = &book;
    
    
    fp = fopen("books.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file\n");
    
    }
    system("cls");
    printf("\n");
    printf("\t|--------------------图书管理系统-------------------------|\n");
    printf("\t|                    图书增添系统                         |\n");
    printf("\t|               ISBN码:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.ISBN);
    printf("\t|                 书名:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.name);
    printf("\t|                 作者:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.author);
    printf("\t|               出版社:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.publisher);
    printf("\t|             出版年份:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.year);
    printf("\t|             贮存楼层:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.floor);
    printf("\t|             贮存书架:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.shelf);
    printf("\t|                 数量:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.borrow);
    printf("\t|                                                         |\n");
    printf("\t|                  1.马列主义、毛泽东思想                 |\n");
    printf("\t|                  2.哲学与社会科学                       |\n");
    printf("\t|                  3.自然科学                             |\n");
    printf("\t|                  4.文学小说                             |\n");
    printf("\t|                  5.经济理财                             |\n");
    printf("\t|                  6.教育学习                             |\n");
    printf("\t|                  7.历史                                 |\n");
    printf("\t|                  8.信息技术                             |\n");
    printf("\t|                  9.期刊杂志                             |\n");
    printf("\t|                                                         |\n");
    printf("\t|             图书类别:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.lei);
    outlei(p);
    booknum++;
    fprintf("%d\n", booknum);
    for (i = 0; i < booknum-1; i++)
    {
        fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, bookfile[i].year, bookfile[i].shelf, bookfile[i].floor, bookfile[i].borrow, bookfile[i].lei, bookfile[i].leiname);
    }
    fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", book.ISBN, book.name, book.author, book.publisher, book.year, book.shelf, book.floor, book.borrow,book.lei,book.leiname);
    printf("\t\t\t   图书添加成功！！！\n");
    printf("\t\t\t   按回车键继续……！\n");
    getchar();
    getchar();



    fclose(fp);

}

//删除图书
void deleteBook()//删除图书
{

}


//借阅图书
void borrowBook(char* username)//借阅图书
{
    char bookname[20];
    char bookauthor[15];
    char bookpublisher[20];
    int bookyear;
    Book book;
    FILE* fp;
    FILE* file;
    int i = 0, k = 0, door = 0;


    //// 打开文件以读取结构体数据
    //file = fopen("books.txt", "rb");
    //int found = 0;

    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }
    int readerid;

    system("cls");
    printf("\n");
    printf("\t|             借阅书名:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookname);
    printf("\t|                 作者:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookauthor);
    printf("\t|               出版社:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookpublisher);
    printf("\t|             出版年份:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &bookyear);
    i = 0;
    
    while (fscanf(fp, "%s %s %s %s %d %s %d %d %d %s\n", &bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, &bookfile[i].year, &bookfile[i].shelf, &bookfile[i].floor, &bookfile[i].borrow, &bookfile[i].lei, bookfile[i].leiname) != EOF)
    {
        i++;

    }
    for (i = 0; i < MAXBOOKS; i++)
    {
        if (strcmp(bookfile[i].ISBN, "\0") != 0)    k++;
        else continue;
    }
    for (i = 0; i < k; i++)
    {   
        
    
        if ((strcmp(bookfile[i].name, bookname) == 0) &&
            (strcmp(bookfile[i].author, bookauthor) == 0) &&
            (strcmp(bookfile[i].publisher, bookpublisher) == 0) &&
            (bookfile[i].year == bookyear))
        {
            if (bookfile[i].borrow >= 1) {
                printf("\n");
                printf("\t|                 ISBN：%s\n", bookfile[i].ISBN);
                printf("\t|             借阅书名：%s\n", bookfile[i].name);
                printf("\t|                 作者: %s\n", bookfile[i].author);
                printf("\t|               出版社: %s\n", bookfile[i].publisher);
                printf("\t|             出版年份: %d\n", bookfile[i].year);
                printf("\t|             贮存书架: %s\n", bookfile[i].shelf);
                printf("\t|             贮存楼层: %d\n", bookfile[i].floor);
                bookfile[i].borrow--;
                printf("\t|             剩余数量: %d\n", bookfile[i].borrow);

                strcpy(book.ISBN, bookfile[i].ISBN);
                strcpy(book.name, bookfile[i].name);
                strcpy(book.author, bookfile[i].author);
                strcpy(book.publisher, bookfile[i].publisher);
                book.year = bookfile[i].year;
                strcpy(book.shelf, bookfile[i].shelf);
                book.floor = bookfile[i].floor;
                
                


                fclose(fp);
                fp = fopen("books.txt", "w");
                

                for (i = 0; i < k; i++)
                    fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, bookfile[i].year, bookfile[i].shelf, bookfile[i].floor, bookfile[i].borrow, bookfile[i].lei, bookfile[i].leiname);

                fclose(fp);

                // 记录借阅信息到文件
                char filename[50];
                sprintf(filename, "reader_%s.txt", username);
                FILE* fp_name = fopen(filename, "a");
                fprintf(fp_name, "%s %s %s %s %d %s %d 借阅\n", book.ISBN, book.name, book.author, book.publisher, book.year, book.shelf, book.floor);

                fclose(fp_name);
                printf("\t|             借阅成功！！！\n");
                printf("\t|             按回车键继续……");
                system("pause");

            }
            else if (bookfile[i].borrow == 0) {
                printf("\t|             抱歉，此书已借出……\n");
                fclose(fp);
                system("pause");
                return;

            }
            door = 1;

            break;


        }

     

    }
    if(!door)
    {
        printf("\t|             抱歉，未找到此书……\n");
        system("pause");
        return;
    }
}


//归还图书
void returnBook(char* username)//归还图书
{
    char bookname[20];
    char bookauthor[15];
    char bookpublisher[20];
    int bookyear;
    int choice;
    Book book;
    FILE* fp;
    FILE* file;
    int i = 0, k = 0;


    //// 打开文件以读取结构体数据
    //file = fopen("books.txt", "rb");
    //int found = 0;

    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }
    int readerid;

    system("cls");
    printf("\n");
    printf("\t|             归还书名:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookname);
    printf("\t|                 作者:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookauthor);
    printf("\t|               出版社:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookpublisher);
    printf("\t|             出版年份:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &bookyear);
    i = 0;

    while (fscanf(fp, "%s %s %s %s %d %s %d %d %d %s\n", &bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, &bookfile[i].year, &bookfile[i].shelf, &bookfile[i].floor, &bookfile[i].borrow, &bookfile[i].lei, bookfile[i].leiname) != EOF)
    {
        i++;

    }
    for (i = 0; i < MAXBOOKS; i++)
    {
        if (strcmp(bookfile[i].ISBN, "\0") != 0)    k++;
        else continue;
    }
    for (i = 0; i < k; i++)
    {


        if ((strcmp(bookfile[i].name, bookname) == 0) &&
            (strcmp(bookfile[i].author, bookauthor) == 0) &&
            (strcmp(bookfile[i].publisher, bookpublisher) == 0) &&
            (bookfile[i].year == bookyear))
        {

            printf("\n");
            printf("\t|                 ISBN：%s\n", bookfile[i].ISBN);
            printf("\t|             借阅书名：%s\n", bookfile[i].name);
            printf("\t|                 作者: %s\n", bookfile[i].author);
            printf("\t|               出版社: %s\n", bookfile[i].publisher);
            printf("\t|             出版年份: %d\n", bookfile[i].year);
            printf("\t|             贮存书架: %s\n", bookfile[i].shelf);
            printf("\t|             贮存楼层: %d\n", bookfile[i].floor);
            bookfile[i].borrow++;
            printf("\t|             剩余数量: %d\n", bookfile[i].borrow);

            strcpy(book.ISBN, bookfile[i].ISBN);
            strcpy(book.name, bookfile[i].name);
            strcpy(book.author, bookfile[i].author);
            strcpy(book.publisher, bookfile[i].publisher);
            book.year = bookfile[i].year;
            strcpy(book.shelf, bookfile[i].shelf);
            book.floor = bookfile[i].floor;




            fclose(fp);
            fp = fopen("books.txt", "w");


            for (i = 0; i < k; i++)
                fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, bookfile[i].year, bookfile[i].shelf, bookfile[i].floor, bookfile[i].borrow, bookfile[i].lei, bookfile[i].leiname);

            fclose(fp);

            // 记录借阅信息到文件
            char filename[50];
            sprintf(filename, "reader_%s.txt", username);
            FILE* fp_name = fopen(filename, "a");
            fprintf(fp_name, "%s %s %s %s %d %s %d 归还\n", book.ISBN, book.name, book.author, book.publisher, book.year, book.shelf, book.floor);
            fclose(fp_name);
            printf("\t|             归还成功！！！\n");



            // 填写书评到文件 
            printf("\t|             是否填写书评？\n");
            printf("\t|             →1  是\n");
            printf("\t|             →2  否\n");
            printf("\t|             请输入（1 - 2）：");
            scanf("%d", &choice);
            char review[255];
            char time[15];
            int score;
            switch (choice)
            {
            case 1:
                

                
                system("cls");
                printf("日期（20XX年XX月XX日）：");
                scanf("%s", time);
                printf("评分：");
                scanf("%d", &score);
                printf("书评:\n");
                getchar();
                fgets(review, 255, stdin);
                char bookreview[50];
                sprintf(bookreview, "%s.txt", bookname);
                FILE* fp_review = fopen(bookreview, "a");

                fprintf(fp, "%s\t%s 评分：", time, username);
                for (i = 0; i < score; i++)    fprintf(fp, "★");
                fprintf(fp, "\n    %s\n\n", review);
                fclose(fp_review);
                printf("书评填写成功！按回车键继续……");
                getchar();
                break;
                //case 2:
                //    break;

                //default:
                //    break;
            }

            break;
        }


      

        else {
                printf("\t|             抱歉，未找到此书……\n");
                getchar();
            }

           

        
    }
}

//书名查询图书
void namesearchBook()//书名查询图书
{
    char name[50];
    Book book;
    FILE* fp;
    int found = 0;
    int i;

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");

    }

    printf("\t|                 书名:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", &name);

    while (fscanf(fp, "%s %s %s %s %d %s %d %d", book.ISBN, book.name, book.author, book.publisher, &book.year, book.shelf, &book.floor, &book.borrow) != EOF) {
        getchar();
        if (strcmp(book.name, name) == 0) {
            printf("\t|                   ISBN码: %s\n", book.ISBN);
            printf("\t|                     书名: %s\n", book.name);
            printf("\t|                     作者: %s\n", book.author);
            printf("\t|                   出版社: %s\n", book.publisher);
            printf("\t|                 出版年份: %d\n", book.year);
            printf("\t|                 贮存书架: %s\n", book.shelf);
            printf("\t|                 贮存楼层: %d\n", book.floor);
            printf("\t|                 剩余数量: %d\n", book.borrow);
            found = 1;
            printf("\t|                 按回车键继续……");
            getchar();
            break;
        }
    }

    if (!found) {
        printf("\t|                 抱歉，没有查询到此书……\n");
        printf("\t|                 按回车键继续……");
        getchar();
    }

    fclose(fp);
}

//ISBN查询图书
void ISBNsearchBook()//ISBN查询图书
{
    char id[14];
    Book book;
    FILE* fp;
    int found = 0;
    int i;

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");

    }

    printf("\t|                 ISBN码:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", id);

    while (fscanf(fp, "%s %s %s %s %d %s %d %d", book.ISBN, book.name, book.author, book.publisher, &book.year, &book.shelf, &book.floor, &book.borrow) != EOF) {
        getchar();
        if (strcmp(book.ISBN, id) == 0) {
            printf("\t|                   ISBN码: %s\n", book.ISBN);
            printf("\t|                     书名: %s\n", book.name);
            printf("\t|                     作者: %s\n", book.author);
            printf("\t|                   出版社: %s\n", book.publisher);
            printf("\t|                 出版年份: %d\n", book.year);
            printf("\t|                 贮存书架: %s\n", book.shelf);
            printf("\t|                 贮存楼层: %d\n", book.floor);
            printf("\t|                 剩余数量: %d\n", book.borrow);
            found = 1;
            printf("\t|                 按回车键继续……");
            getchar();


            break;
        }
    }

    if (!found) {
        printf("\t|                 抱歉，没有查询到此书……\n");
        printf("\t|                 按回车键继续……");
        getchar();
    }

    fclose(fp);
}

//图书查询
void searchBook()
{
    int choice;

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:namesearchBook(); break;
    case 2:ISBNsearchBook(); break;
    case 3:mohu(); break;
    case 0:break;
    default:
        break;
    }
}

//书评查询
void bookreview()
{
    FILE* fp;
    char bookreviewname[100] = { '\0' };
    char line[100];
    fp = NULL;

    printf("请输入书名：");
    scanf("%s", bookreviewname);
    strcat(bookreviewname, ".txt");
    fp = fopen(bookreviewname, "r");

    if (fp == NULL)
    {
        printf("无法打开文件\n");
    }
    system("cls");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);
    system("pause");

}

//读者界面
void ReaderMenu()
{
    system("cls");
    printf("\n");
    printf("\t|-----------------%s同学，欢迎进入---------------------|\n", username);
    printf("\t|                    读者页面系统                        |\n");
    printf("\t|                       主菜单                           |\n");
    printf("\t|                  →1   图书借阅                         |\n");
    printf("\t|                  →2   图书归还                         |\n");
    printf("\t|                  →3   图书查询                         |\n");
    printf("\t|                  →4   书评查询                         |\n");
    printf("\t|                  →5   答疑系统                         |\n");
    printf("\t|                  →6   随机推荐                         |\n");
    printf("\t|                  →7   好书推荐                         |\n");
    printf("\t|                  →8   个性化推荐                       |\n");
    printf("\t|                  →9   反馈与评价                       |\n");
    printf("\t|                  →10  图书馆信息（关于我们）           |\n");
    //printf("\t|                  →8   图书借阅排行榜                     |\n");
    //printf("\t|                  →9   读者排行榜                         |\n");
    printf("\t|                  →0   退出系统                         |\n");
    printf("\t|--------------------------------------------------------|\n");
    printf("\n");
    printf("\t\t请选择（0-9）：");
}

//管理员界面
void ManagerMenu()//管理员界面
{
    system("cls");
    printf("\n");
    printf("\t|-----------------尊敬的管理员，欢迎进入-------------------|\n");
    printf("\t|                    图书管理系统                          |\n");
    printf("\t|                       主菜单                             |\n");
    printf("\t|                  →1   增添图书                           |\n");
    printf("\t|                  →2   查询图书                           |\n");
    printf("\t|                  →3   查看反馈与评价                     |\n");
    printf("\t|                  →0   返回上级                           |\n");
    printf("\n");
    printf("\t\t请选择（0-3）：");
}

//用户查询图书页面
void userSearchMenu()
{
    system("cls");
    printf("\n");
    printf("\t|-----------------%s同学，欢迎进入---------------------|\n", username);
    printf("\t|                    图书查询系统                        |\n");
    printf("\t|                       主菜单                           |\n");
    printf("\t|                  →1 书名查询                           |\n");
    printf("\t|                  →2 ISBN查询                           |\n");
    printf("\t|                  →3 模糊查询                           |\n");
    printf("\t|                  →0 返回上级                           |\n");
    printf("\n");
    printf("\t\t请选择（0-2）：");

}

//管理员查询图书页面
void managerSearchMenu()
{
    system("cls");
    printf("\n");
    printf("\t|-----------------尊敬的管理员，欢迎进入-----------------|\n");
    printf("\t|                    图书查询系统                        |\n");
    printf("\t|                       主菜单                           |\n");
    printf("\t|                  →1 书名查询                           |\n");
    printf("\t|                  →2 ISBN查询                           |\n");
    printf("\t|                  →0 返回上级                           |\n");
    printf("\n");
    printf("\t\t请选择（0-2）：");

}

//开始菜单
void BeginMenu()//开始菜单
{
    system("cls");/*清屏函数*/
    printf("\n");
    printf("\t|-----------------------欢迎进入--------------------------|\n");
    printf("\t|                     图书管理系统                        |\n");
    printf("\t|                        主菜单                           |\n");
    printf("\t|                 →1     登录                             |\n");
    printf("\t|                 →2     注册                             |\n");
    printf("\t|                 →0     退出                             |\n");
    printf("\t|---------------------------------------------------------|\n");
    printf("\n");
    printf("\t\t请选择（0-2）：");
}


//答疑菜单
void dayi()
{
    int flag = 1;
    while (flag)
    {
        system("cls");
        printf("\n");
        printf("\t|----------------------%s同学，欢迎进入---------------------|\n", username);
        printf("\t|                        答疑系统                          |\n");
        printf("\t|                      请选择你的问题                      |\n");
        printf("\t|                  →1   图书逾期未归还                     |\n");
        printf("\t|                  →2   借阅的图书丢失或损坏               |\n");
        printf("\t|                  →3   图书管理系统出现故障               |\n");
        printf("\t|                  →0   返回上一级                         |\n");
        int choice;
        printf("\n");
        printf("\t\t请选择（0-3）：");
        scanf("%d", &choice);
        switch (choice)
        {
        case(1):
            system("cls");
            printf("\n");
            printf("\t|       解决方案：                                                          |\n");
            printf("\t|          请到一楼大厅咨询处找到图书管理员进行登记归还，并缴纳滞纳金，             \n\t        以弥补超过期限的滞纳行为                                            |\n");
            printf("\t|                                 (按回车键返回……)                          |\n");
            getchar();
            getchar();
            break;
        case(2):
            system("cls");
            printf("\n");
            printf("\t|       解决方案：                                                                           |\n");
            printf("\t|       1.如果书刊损坏，管理员进行评定后，根据污损程度不同，按照规定进行赔偿                 |\n");
            printf("\t|       2.如果书刊丢失，购买相同书名、相同作者、相同版本的图书进行赔偿，具体\n\t     书目信息可至借阅服务台查询                                                              |\n");
            printf("\t|                                 (按回车键返回……)                                           |\n");
            getchar();
            getchar();
            break;
        case(3):
            system("cls");
            printf("\n");
            printf("\t|       解决方案：                                                                   |\n");
            printf("\t|                      多次尝试无果后请致电图书馆技术人员进行故障修复                |\n");
            printf("\t|                        技术部门方师傅     联系电话：13960605609                    |\n");
            printf("\t|                                 (按回车键返回……)                                   |\n");
            getchar();
            getchar();
            break;
        case(0):
            flag = 0;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }

}


//好书推荐
void tuijian()
{

    system("cls");
    printf("\n");
    printf("\t|                          好书推荐                         |\n");
    printf("\t|本周好书推荐：《活着》                                     |\n");
    printf("\t|内容简介：                                                 |\n");
    printf("\t| 《活着》讲述一个人一生的故事，这是一个历尽世间沧桑和磨难  |\n");
    printf("\t|  老人的人生感言,是一幕演绎人生苦难经历的戏剧。            |\n");
    printf("\t|推荐理由：                                                 |\n");
    printf("\t|  作者用冰冷的笔调娓娓叙说着福贵悲惨的一生，这样冷静的态度 |\n");
    printf("\t|  足以看出其内心之强大。用主人公悲惨的境遇，道出被时代洪流 |\n");
    printf("\t|  所淹没的人们，福贵身边每个人的死都是时代的牺牲品。他并未 |\n");
    printf("\t|  将矛头直指时代，而是通过这些鲜活的例子，将时代悲剧展现给 |\n");
    printf("\t|  人们看。                                                 |\n");
    system("pause");
}

void suijisearchBook()//随机选书 
{

    Book book;
    FILE* fp;
    FILE* file;

    int i, k;

    i = 0;
    k = rand() % 5; // generate a random number between 1 and 9


    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }

    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }

    while (fscanf(fp, "%s %s %s %s %d %s %d %d\n", &bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, &bookfile[i].year, &bookfile[i].shelf, &bookfile[i].floor, &bookfile[i].borrow) != EOF)
    {
        getchar();
        i++;
        if (i >= length)  break;
    }
    printf("为您随机推荐以下图书\n");
    printf("ISBN: %s\n", bookfile[k].ISBN);
    printf("书名: %s\n", bookfile[k].name);
    printf("作者: %s\n", bookfile[k].author);
    printf("出版社: %s\n", bookfile[k].publisher);
    printf("出版年份: %d\n", bookfile[k].year);
    printf("贮存书架: %s\n", bookfile[k].shelf);
    printf("贮存楼层: %d\n", bookfile[k].floor);
    printf("剩余数量: %d\n", bookfile[k].borrow);
    fclose(fp);
    system("pause");
}

void gexinghua()
{
    system("cls");
    int seeklei=0;
    char seekname[100];

    printf("\t|              请输入你喜欢的类别：                       |\n");
    printf("\t|                                                         |\n");
    printf("\t|                  1.马列主义、毛泽东思想                 |\n");
    printf("\t|                  2.哲学与社会科学                       |\n");
    printf("\t|                  3.自然科学                             |\n");
    printf("\t|                  4.文学小说                             |\n");
    printf("\t|                  5.经济理财                             |\n");
    printf("\t|                  6.教育学习                             |\n");
    printf("\t|                  7.历史                                 |\n");
    printf("\t|                  8.信息技术                             |\n");
    printf("\t|                  9.期刊杂志                             |\n");
    printf("\t|                                                         |\n");
    scanf("%d",&seeklei);
        switch (seeklei)
    {
    case 1:
        strcpy(seekname, "马列主义、毛泽东思想");
        break;
    case 2:
        strcpy(seekname, "哲学与社会科学");
        break;
    case 3:
        strcpy(seekname, "自然科学");
        break;
    case 4:
        strcpy(seekname, "文学小说");
        break;
    case 5:
        strcpy(seekname, "经济理财");
        break;
    case 6:
        strcpy(seekname, "教育学习");
        break;
    case 7:
        strcpy(seekname, "历史");
        break;
    case 8:
        strcpy(seekname, "信息技术");
        break;
    case 9:
        strcpy(seekname, "期刊杂志");
        break;
    default:
        break;
    }
         FILE* file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("error");
    }
     char line[256];
    int linecount = 0;
    printf("该类别\"%s\"的书有：\n", seekname);
    printf("ISBN码 书名 作者 出版社 出版年份 贮存书架 贮存楼层 剩余数量\n");
    while (fgets(line, sizeof(line), file)) {
        //
        if (strstr(line, seekname) != NULL) {
            printf("%s", line);
        }
        linecount++;
    }
	system("pause");
    
    

}

//模糊查询

void mohu()
{
    system("cls");
    char seek[100];
    printf("请输入关键词:\n");
    scanf("%s", seek);

    FILE* file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("error");
    }

    char line[256];
    int linecount = 0;
    printf("包含关键词\"%s\"的书：\n", seek);
    printf("ISBN码 书名 作者 出版社 出版年份 贮存书架 贮存楼层 剩余数量\n");

    while (fgets(line, sizeof(line), file)) {
        //
        if (strstr(line, seek) != NULL) {
            printf("%s", line);
        }
        linecount++;
    }
    system("pause");
}

void outlei(struct book *p)
{
    switch (p->lei)
    {
    case 1:
        strcpy(p->leiname, "马列主义、毛泽东思想");
        break;
    case 2:
        strcpy(p->leiname, "哲学与社会科学");
        break;
    case 3:
        strcpy(p->leiname, "自然科学");
        break;
    case 4:
        strcpy(p->leiname, "文学小说");
        break;
    case 5:
        strcpy(p->leiname, "经济理财");
        break;
    case 6:
        strcpy(p->leiname, "教育学习");
        break;
    case 7:
        strcpy(p->leiname, "历史");
        break;
    case 8:
        strcpy(p->leiname, "信息技术");
        break;
    case 9:
        strcpy(p->leiname, "期刊杂志");
        break;
    default:
        break;
    }
}


//反馈评价模块
void feedback()
{
    int i;
    FILE* fp = fopen("feedback.txt", "a");
    char opinion[255];
    char time[15];
    system("cls");
    printf("\n");
    printf("\t|-----------------%s同学，欢迎进入---------------------|\n", username);
    printf("\t|                   反馈与评价系统                   |\n");
    printf("\t|     日期（20XX年XX月XX日）:______________");
    for (i = 0; i < 14; i++)	printf("\b");
    scanf("%s", time);
    printf("\t|     反馈与评价:\n");
    printf("\t|         ");
    getchar();
    fgets(opinion, 255, stdin);
    fprintf(fp, "%s\t%s：\n%s\n\n", time, username, opinion);
    fclose(fp);
    printf("\t|                                                    | \n");
    printf("\t|     反馈与评价填写成功！按回车键继续……             |\b\b\b\b\b");
    getchar();
}

//管理员查看反馈与评价
void searchfeedback()
{
    FILE* fp;
    char line[100];
    fp = NULL;
    fp = fopen("feedback.txt", "r");

    if (fp == NULL)
    {
        printf("无法打开文件\n");
    }
    system("cls");
    printf("\n");
    printf("以下为近期的所有反馈与评价：\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    fclose(fp);
    printf("展示完毕，按回车继续……");
    system("pause");
}


//二维码
void erweima()
{
    FILE* fp;
    char line[205];
    fp = fopen("ascii-art.txt", "r");//QR_Code.txt为二维码的文件名

    if (fp == NULL)
    {
        printf("无法打开文件\n");
    }
    system("cls");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);

    system("pause");
    getchar();

}