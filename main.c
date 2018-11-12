/*
-This program is made by TonyShovel - a secondary student.
Please help me to correct my program and find bugs

"If you had any opinion or better changes for my code, please inbox me"
My contact:
Facebook ID: tony.shovel.90
Email: hcthuynhcongtoai@gmail.com

*/

#include "ctd.h"
#include "func.h"
#include "UI.h"

const char fileName[] = "phonesubs.txt";

int main()
{/*
    ListUser List = NULL;
    readData_fromFile(&List, fileName);
    SortUser_byAlphabet(&List);
    delete_User(&List, "Annete");
    printData(List);
    writeChange(List, fileName);
*/
    ListUser List = NULL;
    char program[] = "Running";
    
    readData_fromFile(&List, fileName);
    while (strcmp(program, "Running") == 0) /*While program is running*/ 
        mainUI(&List, fileName);
    return 0;
}