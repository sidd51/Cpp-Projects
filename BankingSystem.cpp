#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

class Bank_Account{
    int account_number;
    string name;
    char type;
    int money_Deposit;

public:
    void modify();
    int retdeposit() const
    {
        return money_Deposit;
    }
    void draw(int x)
    {
        money_Deposit-=x;
        cout<<"\t Bank Balance: "<<money_Deposit<<endl;
    }
    void dep(int x)
    {
        money_Deposit+=x;
        cout<<"\t Bank Balance: "<<money_Deposit<<endl;
    }
    void report() const;
    int retacno() const
    {
        return account_number;
    }
    void create_Account();
    void display_Account();
};
void Bank_Account::modify()
{
    cout<<"\t Account number :"<<account_number<<endl;
    cout<<"\t Enter the name of the account holder: ";
    cin.ignore();
    getline(cin,name);
    cout<<"\t Enter the type of the account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount of Deposit(>=500 for Savings | >=1000 for Current)  :";
    cin>>money_Deposit;
    cout<<"\t Account Modified....:)"<<endl;


}
void Bank_Account::report() const{
        cout<<account_number<<setw(10)<<"     "<< name<<setw(10)<<"   "<<type<<setw(6)<<money_Deposit<<endl;
}

void Bank_Account::create_Account(){
    system("clear");
    cout<<"\t Enter the account number :";
    cin>>account_number;
    cout<<"\t Enter the name of the account holder: ";
    cin.ignore();
    getline(cin,name);
    cout<<"\t Enter the type of the account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount of deposit: ";
    cin>>money_Deposit;
    type=toupper(type);
    cout<<"\t Account Created.....:)"<<endl;
}

void Bank_Account::display_Account()
{
    cout<<"\t Bank Account Number: "<<account_number<<endl;
    cout<<"\t Account Holder Name: "<<name<<endl;
    cout<<"\t Type of Account: "<<type<<endl;
    cout<<"\t Balance amount: "<<money_Deposit<<endl;
}
void write_account();
void delete_account(int n);
void display_details(int n);
void display_all();
void Money_deposit_withdraw(int n,int option);
void Updation(int n); 

int main()
{
   
    char ch;
    int num;
     do{
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t\t       | Welcome to the Bank Management System |"<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"\t\t--Main Menu--"<<endl;
    cout<<"\t 1. Create Account"<<endl;
    cout<<"\t 2. Deposit Money"<<endl;
    cout<<"\t 3. Withdraw Money"<<endl;
    cout<<"\t 4. Balance Enquiry"<<endl;
    cout<<"\t 5. All Account Holder List"<<endl;
    cout<<"\t 6. Close an Account"<<endl;
    cout<<"\t 7. Modify an Account"<<endl;
    cout<<"\t 8. Exit"<<endl;

    cout<<"Enter your choice: ";
    cin>>ch;
    switch (ch)
    {
    case '1': 
        // create account function
        write_account();
        break;
    case '2':
        system("clear");
            cout<<"\t Enter the account number: ";
            cin>>num;
            Money_deposit_withdraw(num,1);//deposit function
        break;
     case '3':
        system("clear");
            cout<<"\t Enter the account number: ";
            cin>>num;
            Money_deposit_withdraw(num,2);//withdraw function
        break;
    case '4':
        system("clear");
            cout<<"\t Enter the account number: ";
            cin>>num;
            //balance enquiry function
            display_details(num);
           break;
    case '5':
        display_all();// display all function
        break;

    case '6':
        system("clear");
            cout<<"\t Enter the account number: ";
            cin>>num;
            delete_account(num);//close account function
            break;
    case '7':
        system("clear");
            cout<<"\t Enter the account number: ";
            cin>>num;
                Updation(num);               //modify account function
    case '8':
            return 0;
    default:
        cout<<"Invalid Input!!"<<endl;
        break;
    }
     cin.ignore();
    cin.get();
    }
   
    while(ch!=8);
    return 0;
}

void write_account()//function to write record in binary file
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_Account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int n)//function to delete an account
{
         Bank_Account ac;
         ofstream outFile; //output file stream
         ifstream inFile;   //input file stream
         inFile.open("account.dat",ios::binary);
         if(!inFile){
            cout<<"File cannot be open !! Press any key...";
            return;

         }
         outFile.open("Temp.dat",ios::binary);
         inFile.seekg(0,ios::beg);

         while(inFile.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account)))
         {
            if(ac.retacno()!=n){
                outFile.write(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));
            }
         }
         inFile.close();
         outFile.close();
         remove("Bank_Account.dat");
         rename("Temp.dat","Bank_Account.dat");
         cout<<"\t Account has been deleated...:)";
}

void display_details(int n)
{
    Bank_Account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
         if(!inFile){
            cout<<"File cannot be found !! Press any key...";
            return;
         }
         cout<<"Bank Account Details...."<<endl;
         while(inFile.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account)))
         {
            if(ac.retacno()==n){
                ac.display_Account();
                flag=true;
            }
         }
         inFile.close();
         if(flag==false)
         {
                cout<<"\t Account number does not exist"<<endl;
         }

}

void display_all()
{
    Bank_Account ac;
    ifstream inFile;   //input file stream
    inFile.open("account.dat",ios::binary);
    if(!inFile){
            cout<<"File cannot be open !! Press any key...";
            return;
         }
    cout<<"\t Bank account Holder's List"<<endl;
    cout<<"========================================================================================"<<endl;
    cout<<"A/c no.         NAME                TYPE                      BALANCE"<<endl;
    cout<<"========================================================================================"<<endl;
    while(inFile.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account)))
    {
       
        ac.report();
    }
    inFile.close();

}


void Money_deposit_withdraw(int n,int option)
{
    int amt;
    bool found=false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
     if(!File){
            cout<<"File cannot be open !! Press any key...";
            return;
         }
         while(!File.eof() && found==false){
            File.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));
            if(ac.retacno()==n){
                ac.display_Account();
                if(option==1)
                {
                    cout<<"\t Enter the amount to be deposited: ";
                    cin>>amt;
                    ac.dep(amt);

                }
                if(option==2){
                    cout<<"\t Enter the amount to be withdraw: ";
                    cin>>amt;
                    int balance=ac.retdeposit()-amt;
                    if(balance<0)
                    {
                        cout<<"\t Insufficient Balance!!";
                    }
                    else{
                        ac.draw(amt);
                    }
                }
                int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
                File.seekp(pos,ios::cur);  //move the pointer to the position of the file
                File.write(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));

                found = true;
            }


         }
         File.close();
         if(found==0)
         {
            cout<<"\t Record not Found!!";
         }
}



void Updation(int n)
{
    bool found=false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
     if(!File){
            cout<<"File cannot be open !! Press any key...";
            return;
     }
     while(!File.eof() && found==false){
            File.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));
            if(ac.retacno()==n){
                ac.display_Account();
                cout<<"\t Enter the new details of the account"<<endl;
                ac.modify();
                int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
                File.seekp(pos,ios::cur);  //move the pointer to the position of the file
                File.write(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));
                cout<<"\t Record Updated"<<endl;
                found = true;
            }
     }
    File.close();
    if(found==0)
    {
        cout<<"\t Record not Found!!";
     }


}

