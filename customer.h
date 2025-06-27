#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<ctime>
#include<cstdio>
using namespace std;
bool login();       //login function
bool reg();     //registration function
void customer();    //performs all the functionality necessary for function
bool isValidLength(char password[], int size);
bool hasUpperCase(char password[], int size);
bool hasLowerCase(char password[], int size);
bool hasDigit(char password[], int size);
bool isStrongPassword(char password[], int size);
bool strcmp(char[], char[]);
void arrange();
void allpd();
void price(int , int);
void availability();
void category(char ctgry[]);
void functionality();
void viewwish();
void viewc();
void addwish();
void addcart();
void checkout();
void remove();
void exitProgram();
void checkout();
void orderhistory();
void feedback();
#endif