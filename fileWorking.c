#include "ctd.h"
#include "func.h"

int readData_fromFile(ListUser *List, const char fileName[]) {
    FILE *fptr; //Declaration of file pointer;
    fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        perror("Error occurred");
        return errno;
    }
    else {
        int number_Users; char c, phone_scanner[MAX_SIZE], name_scanner[MAX_SIZE];
        fscanf(fptr, "%*s %d", &number_Users);

        for (int i = 0; i < number_Users; i++) {
            fscanf(fptr, "%s", name_scanner);
            fscanf(fptr, "%s", phone_scanner);
            insertBottom(List, name_scanner, phone_scanner);
        }
    }
    fclose(fptr);
    return 0;
}

int writeChange(ListUser List, const char fileName[]) {
    FILE *fptr = fopen(fileName, "w");
    fprintf(fptr, "Subcribers: %d\n\n", countUser(List));

    UserPtr curr = List;
    for (int i = 0; i < countUser(List); i++) {
        fprintf(fptr, "%s\n%s\n\n", curr->name, curr->phoneNum);
        curr = curr->next;
    }
    fprintf(fptr, "This function was compiled on: %s %s\n", __DATE__, __TIME__);
    fclose(fptr);
}