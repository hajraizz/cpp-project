#include"customer.h"
#include"employee.h"
#include<iostream>
#include"admin.h"
int main(){
    char user_role;
    

    cout << "\033[1;32m-----------------------------Secure Shop------------------------------------\n         where shopping is secure <3\033[0m" << endl;
    cout << "\nEnter a if you are admin and c for customer and e for employee: ";
    cin >> user_role;
    switch (user_role) //To know if the person is user,admin or employee
    {
    case 'a':               //admin
         admin();
        break;
    case 'c':       //customer
              customer();
              break;
    case 'e':           //employee
        employee();
        break;
    default:
        break;
    }

   
}
