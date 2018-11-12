#include "func.h"
#include "ctd.h"
#include "UI.h"

int printData(ListUser List) {
    int count;
    UserPtr curr = List;
    while (curr != NULL) {
        count++;
        printf("%s: %s\n", curr->name, curr->phoneNum);
        curr = curr->next;
    }
    return count;
}

void insertBottom(ListUser *List, char new_name[], char new_phoneNo[]) {
    UserPtr new_node = (PhoneUser*)malloc(sizeof(PhoneUser));
    new_node->name = (char*)malloc(strlen(new_name)*sizeof(char)+1);
    strcpy(new_node->name, new_name);

    new_node->phoneNum = (char*)malloc(strlen(new_phoneNo)*sizeof(char)+1);
    strcpy(new_node->phoneNum, new_phoneNo);

    new_node->next = NULL;

    if (*List == NULL) *List = new_node;
    else {
        UserPtr curr = *List;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new_node;
    }
}

int countUser(ListUser List) {
    int count = 0;
    UserPtr curr = List;
    while(curr != NULL) {
        curr = curr->next;
        count++;
    }
    return count;
}

UserPtr Search_byName(ListUser List, const char KEYWORD[]) { /*Bug fixed*/
    UserPtr before_list = (PhoneUser*)malloc(sizeof(PhoneUser));
    before_list->name = NULL;
    before_list->phoneNum = NULL;
    before_list->next = List;

    UserPtr runner = before_list;
    while (runner->next != NULL) {
        if (strcmp(runner->next->name,KEYWORD)==0) return runner;
        else runner = runner->next;
    }
    if (runner->next == NULL) {/*
        printf("Couldn't find \"%s\" in the file!\n", KEYWORD);*/
        return NULL;
    }
/*
    else if (strcmp(runner->next->name,KEYWORD)==0) {  
        printf("The subcriber that you searched has these following information:\n");
        printf("Name: %s\n", runner->next->name);
        printf("Phone number: %s\n", runner->next->phoneNum);
        return runner;
    }
*/
}

UserPtr Search_byPhoneNum(ListUser List, const char KEYWORD[]) {
    UserPtr before_list = (PhoneUser*)malloc(sizeof(PhoneUser));
    before_list->name = NULL;
    before_list->phoneNum = NULL;
    before_list->next = List;

    UserPtr runner = before_list;
    while (runner->next != NULL) {
        if (strcmp(runner->next->phoneNum,KEYWORD)==0) return runner;
        else runner = runner->next;
    }
    if (runner->next == NULL) {/*
        printf("Can't find \"%s\" in the file!\n", KEYWORD);*/
        return NULL;
    }
/*
    else if (strcmp(runner->next->phoneNum,KEYWORD)==0) {        
        printf("The subcriber that you searched has these following information:\n");
        printf("Name: %s\n", runner->next->name);
        printf("Phone number: %s\n", runner->next->phoneNum);
        return runner;
    }
*/
}

void SortUser_byAlphabet(ListUser *List) {
    void swapElement_only(UserPtr User1, UserPtr User2) {
        char *tmp1 = User1->name;
        char *tmp2 = User1->phoneNum;
        User1->name = User2->name;
        User1->phoneNum = User2->phoneNum;

        User2->name = tmp1;
        User2->phoneNum = tmp2;
    }
    UserPtr curr = *List; UserPtr runner;
    while (curr->next != NULL) {
        runner = curr;
        while (runner->next != NULL) {
            if (strcasecmp(runner->name,runner->next->name) > 0) //Linux
                swapElement_only(runner, runner->next);
            /* For Windows
            if (strcmpi(runner->name, runner->next->name) > 0)
                swapElement_only(runner, runner->next);
            */
            runner = runner->next;
        }
        curr = curr->next;
    }
}

int delete_User(ListUser *List, const char KEYWORD[]) {
    UserPtr before = Search_byName(*List, KEYWORD);
    
    //Checking the condition
    if (before == NULL) Search_byPhoneNum(*List, KEYWORD); 
    if (before == NULL) return 0;
    if (before->next == *List) *List = (*List)->next;
    if (before->next->next == NULL) {
        before->next = NULL;
        return 1;
    }
    //Progress
    UserPtr after = before->next->next;
    before->next = after;
    return 1;
}
/*
Don't care about those code below
Those code define the getch() function
I coding on linux, so I don't have the <conio.h> to include
*/















static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        new.c_lflag |= ECHO; /* set echo mode */
    } else {
        new.c_lflag &= ~ECHO; /* set no echo mode */
        }
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
    return getch_(1);
}