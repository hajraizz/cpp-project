#include"customer.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<ctime>
#include<cstdio>
using namespace std;
void customer(){
    int acc_type;
    cout << "1. Login \n2. Regiter your accoount on Secure shop\n --- ";
    cin >> acc_type;    //To check k customer ne login karna hai ya register karna hai
    cin.ignore();           //SO that \n dont go to buffer of getline
    if (acc_type == 1)          //  if customer wants to login
        {
            if(login() == 1){
                cout << "login successful\n";
                arrange();                  //In which order to view
                functionality(); 
            }
            else{
                cout << "Not a valid account";
            }
        }
        else if(acc_type == 2){
            if(reg()){
                arrange(); 
                functionality();
            }
        } 
  }
bool reg()
{
    int uid;
    int age;
    char user_in_file[50]; //to check if user already exists
    char passInFile[50];
    fstream regis, reg2;
    char username[50];
    char password[50];
    char line;
    cout << "Username: ";
    cin.getline(username, 50, '\n');
    cout << "Password: ";
    cin.ignore();
    cin.getline(password, 50, '\n');
   
    while(!isStrongPassword(password, 50)){
        cout << "The password is weak. Enter again: ";
        cin.getline(password, 50, '\n');
    }
    cout << "Age: ";
    cin >> age; 
    bool a;
    //Under 18 cant register
    for(int i = 1; i <= 3; i++){
    if (age < 18) {
        cout << "You must be at least 18 years old to register.\n";
        return false;
    }
    }
        regis.open("credentials.txt", ios::in);
        
        while(regis >> uid >> user_in_file >> passInFile >> age){
            if(strcmp(username, user_in_file) == 0){
                cout << "User with this name already exist\n";
                return 0;
            }
            
        }   
          
    
    regis.close(); 
    uid = uid + 1;
    //Now to write in file
    regis.open("Unique.txt", ios::out);
    regis <<   uid << endl;

    regis.close();
    reg2.open("credentials.txt", ios::app);
    reg2 << ++uid << " " << username << " " << password << " " << age << endl; 
    cin.ignore();
    reg2.close();
        cout << "your account has been registered in Secure Shop\nNow you can shop!!<3\n"; 
       return true;   
}
bool strcmp(char username[], char user_in_file[]){
        int i=0;
        
        while(username[i] != '\0' && user_in_file[i] != '\0'){
            if(username[i] !=user_in_file[i]){
                return false;
            }
            i++;
        }
         
        return (username[i] == '\0' && user_in_file[i] == '\0');
}
bool login(){
    fstream login, id;
    char username[50], userpass[50];
    char user[50], pass[50];
    int uid, age, i = 0;
    cout << "----------------Enter your login credentials---------------------\n";
    cout << "Username: ";
    cin.getline(username, 50, '\n');
    cout << "Password: ";
    cin.getline(userpass, 50, '\n');
    
    //Comparing the credentials
    login.open("credentials.txt", ios::in);
    while(login >> uid >> user >> pass >> age){
       if(strcmp(user, username))
       {
            if(strcmp(pass, userpass))
            {
                return true;
            }
       }
    }
    id.open("Unique.txt", ios::out);
    id <<   uid << endl;

    id.close();
    login.close();
        return false;

}
bool isValidLength(char password[], int size)
{
    int i;
    for(i = 0; password[i] != '\0'; i++){
    
    }
    if(i < 7)
    {
        return 0;
    }
    else
        return 1;

}
bool hasUpperCase(char password[] , int size)
{
    for (int i = 0; i < size; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            return true;
        }
        
    }
    return false;
}
bool hasLowerCase(char password[], int size){
    for (int i = 0; i < size; i++)
    {
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            return true;
        }
        
    }
    return false;
}
bool hasDigit(char password[], int size){
    for (int i = 0; i < size; i++)
    {
        if (password[i] <= '9' && password[i] >= '0')
        {
            return true;
        }
        
    }
    return 0;
}
bool isStrongPassword(char password[], int size){
     if(hasUpperCase(password, size) == false)
    {
        return 0;
    }
    else if(isValidLength(password, size) == false)
    {
        return 0;
    }
    else if(hasDigit(password, size) == false)
    {
        return 0;
    }
    else if(hasLowerCase(password, size) == false)
    {
        return 0;
    }

    return 1;
}
void arrange(){
    int choice;
    fstream o1;
    int i = 0;
    int max, min;
    char categoryToShow[30];
    cout << "\nOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    cout << "In which order you want to see the weapons?\n";
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    cout << "1. Price\n2. availability\n3.Category\n4.All\n____";
    cin >> choice;
    switch (choice)
    {
    case 1:  //Show by price
        cout << "Minimum value: ";
        cin >> min;
        cout << "Maximum value: ";
        cin >> max;
        price(min , max);
        break;
    case 2: //Show by the availability
       availability();
       break;
    case 3:     //Show by category
        cout << "1.Bullet\n2.License\n3.Gun\n4.Explosives\n5.Chemical\n-----";
        cin.ignore();
        cin.getline(categoryToShow, 30, '\n');
        category(categoryToShow);
        break;
        case 4:     //all products
        allpd();
        break;
    default:
        break;
    }
}
void price(int min, int max){
    fstream file;
    int pid, quantity;
    char item[30], category[30];
    long double price;
    cout << "ID\tNAME\t\tSTOCK\tPRICE\tCATEGORY\n";
    file.open("products.txt", ios::in);
    while(file >> pid >> item >> quantity >> price >> category ){
        if(price > max && price > min){
            cout << pid << "\t" << item << "\t\t" << quantity << "\t" << price << " " << category << endl;

        }
    }
}
void allpd(){  //Show all products
    fstream file;
    int pid, quantity;
    char item[30], category[30];
    long double price;
    cout << "ID\tNAME\t\tSTOCK\tPRICE\tCATEGORY\n";
    file.open("products.txt", ios::in);
    while(file >> pid >> item >> quantity >> price >> category ){
        
        cout << pid << "\t" << item << "\t\t" << quantity << "\t" << price << " " << category << endl;
        
    }
}
void availability(){
    fstream file;
    int pid, quantity;
    char item[30], category[30];
    long double price;
    cout << "ID\tNAME\t\tSTOCK\tPRICE\tCATEGORY\n";
    file.open("products.txt", ios::in);
    while(file >> pid >> item >> quantity >> price >> category ){
        if(quantity > 0){
            cout << pid << "\t" << item << "\t\t" << quantity << "\t" << price << " " << category << endl;
        }
    }
}
void category(char ctgry[]){
    fstream file;
    int pid, quantity;
    char item[30], category[30];
    long double price;
    cout << "ID\tNAME\t\tSTOCK\tPRICE\tCATEGORY\n";
    file.open("products.txt", ios::in);
    while(file >> pid >> item >> quantity >> price >> category ){
        if(strcmp(ctgry, category) == 1){
            cout << pid << "\t" << item << "\t\t" << quantity << "\t" << price << " " << category << endl;
        }
    }
}
void functionality(){
        int menu;
            cout << "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|\n";
            cout << "1. Add items into cart.\n2, Add items into wishlist.\n3. View cart.\n4. View wishlist.\n5.checkout\n6.Remove item from cart\n7.View order history\n8.exit\n9.Give feedback";
            cin >> menu;
            cout << "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|\n";
            switch (menu)
            {
            case 1:
                addcart();
                break;
                case 2:
                addwish();
                break;
                case 3: 
                viewc();
                break;
                case 4:
                viewwish();
                break;
                case 5:
                checkout();
                break;
                case 6: 
                remove();
                break;
                case 7: 
                orderhistory();
                break;
                case 8: 
                exitProgram();
                break;
                case 9:
                feedback();
                default:
                    cout << "Please enter a valid option\n";
            }
   }
void viewwish(){
    fstream wish;
    char opt;
    int ID, pid, quantity;
    char name[30], category[30];
    long double pr;
    wish.open("wishlist.txt", ios::in);
    while (wish >> ID >> name >> quantity >> pr >> category)
    {
        cout << ID << " " << name<< " " << quantity << " "<< pr << " " << category << endl;
    }
     cout << "Want to: \n1. add more\n2. checkout ";
    cin >> opt;
    if(opt == 1){
        addwish();
    }
    else if(opt == 2){
        checkout();
    }
    else{
        functionality();
    }
   }
void viewc(){
    char opt;
    fstream cart, x;
    int ID, pid, quantity;
    char name[30], category[30];
    long double pr;
    cart.open("cart.txt", ios::in);
    while (cart >> ID >> name >> quantity >> pr >> category)
    {
        cout << ID << " " << name<< " " << quantity << " "<< pr << " " << category << endl;
    }
    cart.close();
     cout << "Want to: \n1. add more\n2. checkout ";
    cin >> opt;
    if(opt == 1){
        addcart();
    }
    else if(opt == 2){
        checkout();
    }
    else{
        functionality();
    }
}      
void addwish(){
    fstream cart, x;
    int user, ID, pid, quantity;
    char name[30], category[30];
    char opt;
    long double pr;
    x.open("Unique.txt", ios::in);
    x >> user;
    x.close();
    cout << "Enter the product ID to add in wishlist and enter 0 if your plan has changed: ";
    cin >> pid;
    cart.open("products.txt", ios::in);
    
    while(cart >> ID >> name >> quantity >> pr >> category){
        
        if(pid == ID){
            x.open("wishlist.txt", ios::app);
            x << ID << " " << name<< " " << quantity << " "<< pr << " " << category << endl;
            cout << "Product added in the wishlist!\n";
        }
        
    }
     cout << "Want to go back to options(Y for yes and N for no): ";
    cin >> opt;
    if(opt == 'Y' || opt == 'y'){
        functionality();
    }
    else{
        addwish();
    }
}
void addcart(){
    char opt;
    fstream cart, x;
    int ID, pid, quantity;
    char name[30], category[30];
    long double pr;
    do{
    cout << "Enter the product ID to add in cart and enter 0 to stop adding: ";
    cin >> pid;
    cart.open("products.txt", ios::in);
    
    while(cart >> ID >> name >> quantity >> pr >> category){
        
        if(pid == ID){
            x.open("cart.txt", ios::app);
            x << ID << " " << name<< " " << quantity << " "<< pr << " " << category << endl;
            x.close();
            cout << "Product added in the cart!\n";
        }
        
    }
    cart.close();
    char opt;
     cout << "Want to go back to options(Y for yes and N for no): ";
    cin >> opt;
    if(opt == 'Y' || opt == 'y'){
        functionality();
    }

   }while(pid != 0 );

   }
void remove(){      //remove item from cart
    fstream temp,cart;
    bool find = false;
    int ID, pid, quantity;
    char name[30], category[30];
    long double pr;
    cout << "Enter Product ID you want to remove: ";
    cin >> pid;
    cart.open("cart.txt", ios::in);
    temp.open("temp.txt", ios::app);
    while(cart >> ID >> name >> quantity >> pr >> category){
    if(ID == pid){
        find = true;
        continue;
    }
    temp << ID << " " << name << " " << quantity << " " << pr << " " << category << endl;
    }
    temp.close();
    cart.close();
    remove("cart.txt");
    rename("temp.txt", "cart.txt"); //to change the name of file back to cart.txt takey humare program ki functionality affect na ho
    if(find == true){
        cout << "Item removed from the cart\n";

    }
    else{
        cout << "Item was not in the cart\n";
    }
    functionality();
}
void exitProgram() {
    char confirm;
    cout << "Are you sure you want to exit? (Y/N): ";
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y') {
        cout << "Thank you for using Secure Shop! Goodbye!\n";
        exit(0); 
    }
    else{
        cout << "Lets go back to the menu\n----------------------------\n";
        functionality();
    }
}
void checkout(){
    fstream bill, id, cart, code, product;
    int unique; //to access the unique id from unique file which contains info about current user
    int ID, ID1, pid1, pid,qtty1, quantity, qchange;
    char name[30],name1[30], ctgry[30], category[30], opt1, opt2, coupon[12], code1[12], cname[30], number[16];
    long double pr, pr1, sum = 0.0, discount;
    cart.open("cart.txt", ios::in);
    cout<< "::::::Your cart contains::::::\n";
    while (cart >> ID >> name >> quantity >> pr >> category)
    {
        cout << ID << " " << name<< " " << quantity << " "<< pr << " " << category << endl;
    }
    cart.close();
    cout << "\nYou want to proceed?(Enter 'n' for no)";
    cin >> opt1;
    if(opt1 == 'N' || opt1 == 'n'){
        functionality();
    }
    else{
    cout << "Any coupon to apply>>>> (Enter 'n' for no and y for yes)";
    cin >> opt2;
    if(opt2 == 'Y' || opt2 == 'y'){
        cout << "Enter your coupon: ";
        cin.getline(coupon, 12, '\n');
        code.open("discode.txt", ios::in);
        while(code >> code1 >> discount){
            if(strcmp(coupon, code1) == 1)
            {
                break;
            }
        }
    }
    id.open("unique.txt", ios::in); //reading the id
    id >> unique;
    id.close();
    bill.open("cart.txt", ios::in); 
    if(cart.is_open()){
            cout << "Your cart is empty";
        addcart();

        }
        else{
        //reading details from cart
        id.open("order.txt", ios::out);     //storing the details from cart and unique.txt in this file
            product.open("product.txt", ios::app);
            while(product >>ID1 >> name1 >> qtty1 >> pr1 >> ctgry){
                while (bill >> ID >> name >> quantity >> pr >> category)
                {
                    if(ID == ID1){
                        ID1--;
                    }
                    id << unique << " " << ID << " " << name << " " << quantity << " " << pr << " " << category << endl;
                    sum = sum + pr;
                }
            }
    sum = sum-discount;
    cout << "Your total bill is: " << sum << endl;
    cout << "\t-----Proceeding to payment-----\n";
    cout << "Only card payment is accepted:::::\n";
    cout << "Cardholder Name: ";
    cin >> name;
    cout << "Card Number: ";
    cin >> number;
    cout << "______________________Order Successful___________________________\n";
    bill.close();
    }
    bill.open("cart.txt",ios::out | ios::trunc);
    bill.close();
    }
}
void orderhistory(){
    fstream view;
    int ID, pid, quantity;
    char name[30], category[30];
    long double pr;
    view.open("order.txt", ios::in);
    while(view >> ID >> pid >> name >> quantity >> pr >> category){
        cout << pid << " " << name << " " << quantity << " " << pr << " " << category <<endl;
    }
}
void feedback(){
    char fb[300];
    int uid;
    fstream feedback;
    cin.ignore();
    cout << "Enter your feedback: ";
    cin.getline(fb, 300, '\n');
    feedback.open("Unique.txt", ios::in);
    feedback >> uid;
    feedback.close();
    feedback.open("feedback.txt", ios::app);
    feedback << uid << fb << endl;
    feedback.close();
    cout << "Feedback sent! We will respond shortly!";
}