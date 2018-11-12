#ifndef FUNC_H
#define FUNC_H
#include "ctd.h"

//Done this file

//Insert data to the bottom.
void insertBottom(ListUser *List, char new_name[], char new_phoneNo[]);  //Written
//Print data to screen
int printData(ListUser List);                                            //Written
int countUser(ListUser List);                                            //Written

UserPtr Search_byName(ListUser List, const char name[]);                 //Written
UserPtr Search_byPhoneNum(ListUser List, const char PhoneNo[]);          //Written
/*
 * Return the position before the found data.
 * Easier to define "delete_thisUser".
 */
void SortUser_byAlphabet(ListUser *List);                                //Written

int delete_User(ListUser *List, const char KEYWORD[]);                        //Written
#endif