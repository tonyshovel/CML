#ifndef UI_H
#define UI_H
#include <termios.h>
#define ESC 27

void mainUI(ListUser *List, const char fileName[]);
void AddUser(ListUser *List);
void DeleteUser(ListUser *List);
void SearchUser(ListUser *List);
void SortbyAlphabet(ListUser *List);
void WriteChangeToFile(ListUser List, const char fileName[]);
void PrintOutData(ListUser List);

#endif