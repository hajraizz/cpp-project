#include"admin.h"
#include"customer.h"
void admin(){
   
    cout << "|-----------------------------------------------------------------| \n";
    cout << "                        ADMIN OF SECURESHOP                          \n";
    cout << "|-----------------------------------------------------------------| \n";
    cout << "|                        Enter the details                        | \n";
    cout << "|-----------------------------------------------------------------| \n";
    if(adminlogin()){
        inventory();
    }
    
}

bool adminlogin(){
     fstream admin;
    char adminid[8], adminpass[15], fileid[8], filepass[15];
    cout << "| USERNAME:                                                       |\n";
    cin.ignore();
    cin.getline(adminid, 15, '\n');
    cout << "| PASSWORD:                                                       |\n";
    cin.getline(adminpass, 15, '\n');
    cout << "|-----------------------------------------------------------------| \n";
    admin.open("admin.txt", ios::in);
    while(admin >> fileid >> filepass){
        if(strcmp(adminid, fileid) && strcmp(adminpass, filepass)){
            if(twoFA()){
                return true;
            }
        }
    }
    admin.close();
    return false;
}
bool twoFA(){
    fstream generate;
    int otp , OTP, i = 0;
    srand(time(0));
    generate.open("otp.txt", ios::out);
   
        otp = 100000+rand()%1000000;
        generate << otp;
    
    generate.close();
    cout << "Enter the OTP:                                                     |\n";
    cin >> OTP;
    if(OTP == otp){
        return true;
    }
    return false;
}