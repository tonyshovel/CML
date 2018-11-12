#include "ctd.h"
#include "UI.h"
#include "func.h"
void clear_stdin(void)
{    
    while (getchar() != '\n');
}

void mainUI(ListUser *List, const char filename[]){
    system("@cls||clear");
    printf("             ____   __  __   _      \n");     
    printf("            / ___| |  \\/  | | |    \n");    
    printf("           | |     | |\\/| | | |     \n");    
    printf("           | |___  | |  | | | |___  \n"); 
    printf("            \\____| |_|  |_| |_____|\n\n");
    printf("                    Version: 1.0\n");
    printf("\n\n");
    printf("\t\t\t\tA program made by TonyShovel.\n");
    printf("\t\t\t\t\t\"Contact Manager Lite\".\n");
    printf("PRESS TO CHOOSE OPTION: \n");
    printf("    1) Add a contact\n");
    printf("    2) Delete a contact\n");
    printf("    3) Search for a contact\n");
    printf("    4) Sort contacts Alphabetically\n");
    printf("    5) Write changes to file\n");
    printf("    6) Print all contact saved\n");
    printf("    ESC: Exit\n");

    int userOption = getch();
    switch(userOption) {
        case '1':
            AddUser(List);
            break;
        case '2':
            DeleteUser(List);
            break;
        case '3':
            SearchUser(List);
            break;
        case '4':
            SortbyAlphabet(List);
            break;
        case '5':
            WriteChangeToFile(*List, filename);
        case '6':
            PrintOutData(*List);
            break;
        case ESC:
            printf("All unsaved progress will be lost (Press [5] to save data).\n");
            if (getch() == '5') WriteChangeToFile(*List, filename);
            printf("Comfirm exit (y/N)\n"); userOption = getch();
            if (userOption == 'y') {
                system("@cls||clear");
                printf("Thanks for using =)), remember: My name is TonyShovel\n");
                printf("                                \"A young-buffalo kid\"\n");
                exit(EXIT_SUCCESS);
            }
            break;
        default:
            //This won't be printed out =))
            printf("Unknown key pressed\n");
            break;
    }
}

void AddUser(ListUser *List) {
    system("@cls||clear");
    int HaveChar(char ch, char str[]) {
        if (ch == '\0') return 1;
        for (int i = 0; i < strlen(str); i++)
            if (str[i] == ch)
                return 1;
            else if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
        return 0;
    }
    char phone_input[MAX_SIZE];
    char name_input[MAX_SIZE];
    do {
        printf("The name of the person (without spaces): ");
        fgets(name_input,MAX_SIZE,stdin);
    }
    while (HaveChar(' ', name_input));
    do {
        printf("The phone number of that person (without spaces): ");
        fgets(phone_input,MAX_SIZE,stdin);
    }
    while (HaveChar(' ', phone_input));
    insertBottom(List, name_input, phone_input);
    printf("Insert successfully!\n");
    printf("\nPress any key to continue\n");
    getch();
    return;
}
void DeleteUser(ListUser *List) {
    system("@cls||clear");
    printf("\t\tChoose a contact to delete\n\n");
    UserPtr curr = *List;
    int count_user = countUser(*List);
    for (int i = 0; i < count_user; i++) {
        printf("\t%d. %s: %s\n\n", i+1, curr->name, curr->phoneNum);
        if (curr->next != NULL) curr = curr->next;
    }

    int key_press;
    do {
        key_press = getch()-48;
        if (key_press > count_user || key_press <= 0) {
            printf("Unknown key pressed\n");
            printf("Press a key again\n");
        }
    }
    while (key_press > count_user || key_press <= 0);
    system("@cls||clear");
    printf("\n\n\n\n\t\t\t\tDELETE THIS USER ? (y/N)\n");
    if (getch() == 'y') {
        curr = *List;
        for (int i = 1; i < key_press; i++) curr = curr->next;
        delete_User(List, curr->name);
        printf("\n\t\t\t\tDelete data successfully!\n"); 
    }
    getch();
}

void SearchUser(ListUser *List){
    system("@cls||clear");
    char keyword[MAX_SIZE];
    printf("The keyword to search: "); scanf("%s", keyword);
    clear_stdin();
    UserPtr before_data = Search_byName(*List, keyword);
    if (before_data == NULL)
        before_data = Search_byPhoneNum(*List, keyword);

    char key_press;
    if (before_data != NULL) {
        printf("\nThe contact you've searched for has these following information:\n");
        printf("Name:          %s\n", before_data->next->name);
        printf("Phone Number:  %s\n\n\n", before_data->next->phoneNum);
        printf("        Press [D] to delete this contact!\n");
        printf("        Press [ESC] to go back to the menu!\n");
        
        key_press = getch();
        if (key_press == 'd' || key_press == 'D') {
            printf("\n\n\n\n\tTHESE DATA CANNOT BE RECOVERED, ARE YOU SURE ? (y/N)");
            if (getch() == 'y') {
                if (before_data->next == *List) *List = (*List)->next;
                if (before_data->next->next == NULL) before_data->next = NULL;
                else before_data->next = before_data->next->next;
                printf("\n\tDelete user sucessfully !\n");
            }
        }
        else if (key_press == ESC) return;
    }
    else if (before_data == NULL) {
        printf("Cannot find \"%s\" in the data, sorry !\n\n", keyword);
        printf("        Press [T] to search again!\n");
        printf("        Press [ESC] to go back to the menu!\n");
        key_press = getch();
        if (key_press == 't' || key_press == 'T') SearchUser(List);
        else if (key_press == ESC) return;
    }
    printf("\n\tPress any key to continue\n");
    getch();
    return;
}

void SortbyAlphabet(ListUser *List){
    system("@cls||clear");
    printf("After this operation, the changes will be applied!\n");
    printf("Are you sure ? (y/N)\n");
    if (getch() == 'y') SortUser_byAlphabet(List);
    printf("Operation complete successfully !\n");
    getch();
}

void WriteChangeToFile(ListUser List, const char fileName[]){
    system("@cls||clear");
    printf("Sure ?(y/N)\n");
    if (getch() == 'y') {
        writeChange(List, fileName);
        printf("\n\tChange Saved\n");
    }
    else printf("\n\tCanceled");
    getch();
    return;
}
void PrintOutData(ListUser List){
    system("@cls||clear");
    int count = printData(List);
    if (count == 0) printf("No data has been saved recently!\n");
    printf("\nPress any key to continue\n");
    getch();
    return;
}