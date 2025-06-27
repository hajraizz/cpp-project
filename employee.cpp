#include<iostream>
#include"employee.h"

void employee(){
    cout << "----------------------------------------------------------------------\n";
    cout << "                   EMPLOYEE LOG IN\n";
    cout << "----------------------------------------------------------------------\n\n";
   if(emplog()){        //If successfully logged in
    cout << "|-------------------------|\n";
    cout << "\033[1;37;41m|    Successful Log In    |\033[0m\n";
    cout << "|-------------------------|\n";
    inventory();            //function to edit inventory
   }
   else{
    cout << "\n|-------------------------|\n";
    cout << "\033[1;37;41m| You can not log in      |\033[0m\n";
    cout << "|-------------------------|\n";
   }
}
bool emplog(){          //Log In of employee
    fstream emp;
    char ename[15], epass[15], fileid[8], filepass[15];
    int key; //A key only employees know
    cout << "___________________________________________________________________\n";
    cout << "Enter your user id: ";
    cin.ignore();
    cin.getline(ename, 15, '\n');
    cout << "enter your password: ";
    cin.getline(epass, 15, '\n');
    cout << "ENTER THE EMPLOYEE KEY: ";
    cin >> key;
    emp.open("employee.txt", ios::in);
    while(emp >> fileid >> filepass){       //reading employee file
        if(strcmp(ename, fileid) && strcmp(epass, filepass)){
            if(key == 1090){
                return true;
            }
        }
    }
    return false;
}
void inventory(){
    int menu;
    do{
    cout << "__________________________MENU_______________________________\n";
    cout << "1.Delete a product\n2.Add a product\n3.Edit details\n4.Exit\n__________";
    cin >> menu;
    switch(menu){
        case 1:         //delete product
        delproduct();
        break;
        case 2:     //add product
        addproduct();
        break;
        case 3:        //modify detail
        modifydetail();
        break;
        case 4: //Exit the program
        return;
        default: 
        cout << "Not a valid option\n";
    }
    }while(menu != 4);
}
void delproduct(){
    fstream delet, temp;
    int remid, pid, quantity;
    char name[30], category[30];
    long double pr;
    bool find = false;      //this will check k id exist karti bhi hai k nahi
    cout << "Enter the product ID you want to remove from the list: ";
    cin >> remid;
    delet.open("products.txt", ios::in);
    temp.open("temp.txt", ios::out);
    while(delet >> pid >> name >> quantity >> pr >> category){
        if(pid == remid){
            find = true;
            continue;  //takey woh temp file mein na jaye
        }
        temp << pid << " " << name << " " << quantity << " " << pr << " " << category << endl;
    }
    temp.close();
    delet.close();
    //removing old file
    remove("products.txt");
    //naming temp file
    rename("temp.txt", "products.txt");
    if(find == true){
        cout << "Item removed from the catalog\n";
    }
    else{
        cout << "Item not found\n";
    }
}
void addproduct(){
    int pid, quantity;
    long double pr;
    char  name[30], category[30];
    fstream product;
    product.open("products.txt", ios::in);
    while (product >>pid >> name >> quantity >> pr >> category)
    {

    }
    pid = pid + 1;
    product.close();
    cin.ignore();
    cout << "Enter product title: ";
    cin.getline(name, 30, '\n');
    cout << "Enter stock quantity: ";
    cin >> quantity;
    cout << "Enter the price: ";
    cin >> pr;
    cin.ignore();
    cout << "enter the category: ";
    cin.getline(category, 30, '\n');
    product.open("products.txt", ios::app);
    product << endl << pid << " " << name << " " << quantity << " " << pr << " " << category << endl;
    product.close();
    cout << "Product added!\n";
}
void modifydetail(){
    int choice;
    int ID, pid, quantity;
    long double pr;
    char  name[30], category[30] , name2[30], newC[30];
    fstream modify, temp;
    bool found;
    cout << "Which detail you want to change?\n\n";
    cout << "1.name                         |\n2.quantity                         |\n3.category                         |\n4.price                         |\n";
    cin >> choice;
    cout << "Enter the product Id: ";  //ID of product to be modified
    cin >> ID;
    
    modify.open("products.txt", ios::in); // Open the original file in read mode
    temp.open("temp.txt", ios::out);    // Open a temporary file in write mode


    while (modify >> pid >> name >> quantity >> pr >> category) {
        if (pid == ID) {
            found = true;
            switch (choice) {
                case 1:  // Modify Name
                    cout << "Enter the new name: ";
                    cin.ignore(); 
                    cin.getline(name2, 30, '\n');
                      for (int i = 0; i < 30; ++i) {
                        name[i] = name2[i];       //changing each letter
                        if (name2[i] == '\0') break; 
                    } 
                    break;
                case 2:  // Modify Quantity
                    cout << "Enter the new quantity: ";
                    cin >> quantity;
                    break;
                case 3:  // Modify Category
                    cout << "Enter the new category: ";
                    cin.ignore(); // Clear buffer
                    cin.getline(newC, 30, '\n');
                    for (int i = 0; i < 30; ++i) {
                        category[i] = newC[i];
                        if (newC[i] == '\0') break; 
                    }
                    break;
                case 4:  // Modify Price
                    cout << "Enter the new price: ";
                    cin >> pr;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
            }
        }
        temp << pid << " " << name << " " << quantity << " " << pr << " " << category << endl;
    }
    modify.close();
    temp.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");
    if (found==1) {
        cout << "Product details updated successfully.\n";
    } else {
        cout << "Product with ID " << ID << " not found.\n";
    }
}
