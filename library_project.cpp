#include<iostream>
using namespace std;
#include<string.h>
#include<fstream>
class book;
class student;
class admin;
class issuebook;
class book{
    char name[50];
    char author[50];
    int year;
    int quantity;
    int bookid;
    int available;
public:
    book(){
        strcpy(name,"no title");
       strcpy(author,"no author");
       year=-1;
       bookid=-1;
       quantity=-1;
       available=-1;
    }
    void getdata(){
    cout<<"BOOK ID: "<<bookid<<"     NAME: "<<name<<"     AUTHOR:"<<author<<"       YOP:"<<year<<"        QUANTITY:"<<quantity<<"    available:"<<available<<endl;
    }

    void addbook(){
        int c=0;
        cout<<"enter book id : ";
        int id;
        cin>>id;cin.ignore();
        ifstream i;
        i.open("bookinfo.dat",ios::in|ios::binary);
        i.read((char *)this,sizeof(*this));
        while(!i.eof()&&c==0){
            if(bookid==id){
                cout<<"book is already added \n";
                c++;
            }
            i.read((char *)this,sizeof(*this));
        }
        i.close();
        if(c==0){
            bookid=id;
            cout<<"enter book name : ";
            cin.getline(name,50);
            cout<<"enter author name : ";
            cin.getline(author,50);
            cout<<"enter year of published : ";
            cin>>year;
            cin.ignore();
            cout<<"enter quantity : ";
            cin>>quantity;
            cin.ignore();
            available=quantity;
            ofstream o;
            o.open("bookinfo.dat",ios::app|ios::binary);
            o.write((char *)this,sizeof(*this));
            cout<<"book added successfully !! \n";
            o.close();
        }
    }
    void viewallbooks(){
        ifstream i;
       i.open("bookinfo.dat",ios::in|ios::binary);
        if(!i)
            cout<<"there is no book in the record !!\n";
        else{
            cout<<"\n\nLIST OF BOOKS ->\n\n";
            i.read((char *)this,sizeof(*this));
            while(!i.eof()){
                getdata();
                i.read((char *)this,sizeof(*this));
            }
        }
        i.close();
    }
    void deletebook(){
        int c=0;
        int d=0;
        int id;
        ifstream i1;
        ofstream t;
        i1.open("bookinfo.dat",ios::in|ios::binary);
        t.open("temp.dat",ios::out|ios::binary);
        cout<<" \nenter book id which you want to delete: ";
        cin>>id;cin.ignore();
        i1.read((char *)this,sizeof(*this));
        while(!i1.eof()){
            if(bookid==id){
                c++;d++;
            }
            if(c==0)
                t.write((char *)this,sizeof(*this));
            i1.read((char *)this,sizeof(*this));
            c=0;
        }
        t.close();
        i1.close();
        if(d!=0)cout<<"\nbook deleted successfully !!\n";
        else cout<<"\nbook not found !!\n";
        remove("bookinfo.dat");
        rename("temp.dat","bookinfo.dat");
        }
    void updatebook(){
        int c=0;
        int d=0;
        int id;
        ifstream i1;
        ofstream t;
        i1.open("bookinfo.dat",ios::in|ios::binary);
        t.open("temp.dat",ios::out|ios::binary);
        cout<<" \nenter book id which you want to update: ";
        cin>>id;cin.ignore();
        i1.read((char *)this,sizeof(*this));
        while(!i1.eof() && d==0){
            if(bookid==id){
                d++;
                while(c==0){
                    cout<<"\n1.update name\n2.update author\n3.update yop\n4.update quantity\n5.done\n";
                    int ch;
                    cout<<"enter your choice : ";
                    cin>>ch;
                    cin.ignore();
                    switch (ch){
                        case 1: cout<<"enter new name : ";
                                cin.getline(name,50);
                                break;
                        case 2: cout<<"enter new author name : ";
                                 cin.getline(author,50);break;
                        case 3: cout<<"enter correct year of published : ";
                                 cin>>year;cin.ignore();break;
                        case 4: cout<<"enter new quantity : ";
                                cin>>quantity;cin.ignore();break;
                        case 5 : cout<<"\nbook updated successfully !!\n";
                                    c=1;break;
                        default :cout<<"enter right choice : ";
                    }
                }
            }
            t.write((char *)this,sizeof(*this));
            i1.read((char *)this,sizeof(*this));
        }
        t.close();
        i1.close();
        if(d==0)cout<<"\nno book with id : "<<id<<endl;
        remove("bookinfo.dat");
        rename("temp.dat","bookinfo.dat");

    }
    int searchbook(){
        int id;
        ifstream i1;
        i1.open("bookinfo.dat",ios::in|ios::binary);
        cout<<" \nenter book id : ";
        cin>>id;cin.ignore();
        i1.read((char *)this,sizeof(*this));
        while(!i1.eof()){
            if(bookid==id){
                getdata();
                return 1;
            }
            i1.read((char *)this,sizeof(*this));
        }
        i1.close();
        cout<<"book not found:\n\n";
        return 0;
    }
    int decreasebook(int id){
        int c=0;
        ifstream i1;
        ofstream t;
        i1.open("bookinfo.dat",ios::in|ios::binary);
        t.open("temp.dat",ios::out|ios::binary);
        i1.read((char *)this,sizeof(*this));
        while(!i1.eof()){
            if(bookid==id){
                if(available==0){
                    c++;
                }
                else
                    available--;
            }

            t.write((char *)this,sizeof(*this));
            i1.read((char *)this,sizeof(*this));
        }
        t.close();
        i1.close();
        remove("bookinfo.dat");
        rename("temp.dat","bookinfo.dat");
        if(c==0)return 1;
        else return 0;
    }


    void writefile(){
        cout<<"enter book name,author,year,quantity,and book id\n";
        cin>>bookid;
        cin.ignore();
        cin.getline(name,50);
        cin.getline(author,50);
        cin>>year;
        cin.ignore();
        cin>>quantity;
        cin.ignore();
        available=quantity;
        ofstream o;
        o.open("tempinfo.dat",ios::app|ios::binary);
        if(!o)
            cout<<"no record found !!\n";
        else
            o.write((char *)this,sizeof(*this));
        o.close();
    }


    void readfile(){
        ifstream i;
        i.open("tempinfo.dat",ios::in|ios::binary);
        if(!i)
            cout<<"no record found !!\n";
        else{
           i.read((char *)this,sizeof(*this));
        i.close();
        if(bookid!=-1)
        getdata();
        }
        }
};


class student{
    char fn[15];
    char ln[15];
    char prn[30];
    char pass[20];
public:
    student(){
        strcpy(fn,"no name");
        strcpy(ln,"no name");
        strcpy(prn,"0");
        strcpy(pass,"no password");
    }
    void showdata(){
        cout<<"PRN: "<<prn<<"       name : "<<fn<<" "<<ln<<endl;
    }
    int login(){
        char temp[30];char temp1[20];int counter=0;
        cout<<"enter your PRN :  ";
        cin.getline(temp,30);
        cout<<"enter your password : ";
        cin.getline(temp1,20);
        ifstream in;
        in.open("studentinfo.txt",ios::in);
        in.getline(prn,30,',');
        in.getline(fn,15,',');
        in.getline(ln,15,',');
        in.getline(pass,20,'\n');
        while(!in.eof()&&counter==0){
            if(strcmp(prn,temp)==0){
                counter++;
                break;
            }
            in.getline(prn,30,',');
            in.getline(fn,15,',');
            in.getline(ln,15,',');
            in.getline(pass,20,'\n');
        }
        in.close();
        if(strcmp(temp1,pass)==0&&(strcmp(prn,temp)==0&&counter==1)){
            cout<<"logged in successfully\n";return 1;}
        cout<<"wrong password or PRN \n";
        return 0;
    }
    void signup(){
        int c=0;int c1=0;
        char pas1[20],pas[20];
        char pn[30];
        cout<<"enter your PRN : ";
        cin.getline(pn,30);
        ifstream inn;
        inn.open("studentinfo.txt",ios::in);
        inn.getline(prn,30,',');
        inn.getline(fn,15,',');
        inn.getline(ln,15,',');
        inn.getline(pass,20,'\n');
        while(!inn.eof()&&c==0){
            if(strcmp(pn,prn)==0){
                c++;
                cout<<"already signed up by this number\n";
            }
            inn.getline(prn,30,',');
            inn.getline(fn,15,',');
            inn.getline(ln,15,',');
            inn.getline(pass,20,'\n');
        }
        inn.close();

        ifstream inn1;
        inn1.open("studentrequest.txt",ios::in);
        inn1.getline(fn,15,',');
        inn1.getline(ln,15,',');
        inn1.getline(prn,30,',');
        inn1.getline(pass,20,'\n');
        while(!inn1.eof()&&c1==0){
            if(strcmp(pn,prn)==0){
                c1++;
                cout<<"request already sent \n";
            }
            inn1.getline(fn,15,',');
            inn1.getline(ln,15,',');
            inn1.getline(prn,30,',');
            inn1.getline(pass,20,'\n');
        }
        inn1.close();

        if(c==0&&c1==0){
            cout<<"enter first name :  ";
            cin.getline(fn,15);
            cout<<"enter last name :  ";
            cin.getline(ln,15);
            cout<<"re enter your prn :";
            cin.getline(prn,30);
            reenter:
            cout<<"enter password :  ";
            cin.getline(pas1,20);
            cout<<"re enter password :  ";
            cin.getline(pas,20);
            if(strcmp(pas1,pas)){
                cout<<"password not matched\n";
                goto reenter;
            }
            ofstream of;
            of.open("studentrequest.txt",ios::app);
            if(!of)
                cout<<"record not found \n";
            else{
                strcpy(pass,pas1);
                 of<<prn<<','<<fn<<','<<ln<<','<<pass<<'\n';
                cout<<"request is sent to admin\n";
            }
            of.close();
        }
    }
    void studentlist(){
        ifstream inn;
        inn.open("studentinfo.txt",ios::in);
        if(!inn){
            cout<<"record not found \n";
        }
        else{
                inn.getline(prn,30,',');
                inn.getline(fn,15,',');
                inn.getline(ln,15,',');
                inn.getline(pass,20,'\n');
            while(!inn.eof()){
                showdata();
                inn.getline(prn,30,',');
                inn.getline(fn,15,',');
                inn.getline(ln,15,',');
                inn.getline(pass,20,'\n');
            }
            inn.close();
        }
    }
    void readrequest(){
        ifstream io;
        io.open("studentrequest.txt",ios::in);
        if(!io.eof()){
                io.getline(prn,30,',');
                io.getline(fn,15,',');
                io.getline(ln,15,',');
                io.getline(pass,20,'\n');
        }
        else cout<<"no request\n";
        io.close();
        if(strcmp(prn,"0")!=0)showdata();
    }
    void writeinfo(){
        ofstream os;
        os.open("studentinfo.txt",ios::app);
        if(!os)cout<<"record not found : ";
        else{
            if(strcmp(prn,"0")!=0){
                os<<prn<<','<<fn<<','<<ln<<','<<pass<<'\n';
                cout<<"\nRequest accepted successfully !!\n";
            }
        }
        os.close();
    }
    void deleterequest(){
        int c=0;
        char pn[30];
        strcpy(pn,prn);
        ifstream i1;
        ofstream t;
        i1.open("studentrequest.txt",ios::in);
        t.open("temp.txt",ios::out);
        i1.getline(prn,30,',');
        i1.getline(fn,15,',');
        i1.getline(ln,15,',');
        i1.getline(pass,20,'\n');
        while(!i1.eof()){
            if(strcmp(prn,pn)==0){
                c++;
            }
            if(c==0)
                t<<prn<<','<<fn<<','<<ln<<','<<pass<<'\n';
            i1.getline(prn,30,',');
            i1.getline(fn,15,',');
            i1.getline(ln,15,',');
            i1.getline(pass,20,'\n');
            c=0;
        }
        t.close();
        i1.close();
        remove("studentrequest.txt");
        rename("temp.txt","studentrequest.txt");
    }
    void listbook(){
        book b;
        b.viewallbooks();
    }
    void booksearch(){
        book b;
        b.searchbook();
    }
    void removestudent(){
        int c=0;
        int d=0;
        char pn[30];
        ifstream i1;
        ofstream t;
        i1.open("studentinfo.txt",ios::in);
        t.open("temp.txt",ios::out);
        cout<<" \nenter prn of student which you want to remove: ";
        cin.getline(pn,30);
       i1.getline(prn,30,',');
        i1.getline(fn,15,',');
        i1.getline(ln,15,',');
        i1.getline(pass,20,'\n');
        while(!i1.eof()){

            if(strcmp(prn,pn)==0){
                c++;d++;
            }
            if(c==0)
                t<<prn<<','<<fn<<','<<ln<<','<<pass<<'\n';
            i1.getline(prn,30,',');
        i1.getline(fn,15,',');
        i1.getline(ln,15,',');
        i1.getline(pass,20,'\n');
            c=0;
        }
        t.close();
        i1.close();
        if(d!=0)cout<<"\nstudent removed successfully !!\n";
        else cout<<"\nnot found!!\n";
        remove("studentinfo.txt");
        rename("temp.txt","studentinfo.txt");
    }
    int checkprn(){
        char pn[30];
        cout<<"enter your PRN : ";
        cin.getline(pn,30);
        ifstream inn;
        inn.open("studentinfo.txt",ios::in);
        inn.getline(prn,30,',');
        inn.getline(fn,15,',');
        inn.getline(ln,15,',');
        inn.getline(pass,20,'\n');
        while(!inn.eof()){
            if(strcpy(prn,pn)==0){
                inn.close();
                return 1;
            }
        inn.getline(prn,30,',');
        inn.getline(fn,15,',');
        inn.getline(ln,15,',');
        inn.getline(pass,20,'\n');
        }
        inn.close();
        cout<<"PRN not registered \n\n\n";
        return 0;
    }

};
class issuebook{
        int bid;
        char sid[30];
        int d1,m1,y1;
        int d2,m2,y2;
    public:
        issuebook(){
            bid=-1;
            strcpy(sid,"no id");
            d1=0,m1=0,y1=0;
            d2=m2=y2=0;
        }
        void showdata(){
            cout<<"book id:"<<bid<<"     PRN:"<<sid<<"     issue date"<<d1<<"/"<<m1<<"/"<<y1<<"     due date"<<d2<<"/"<<m2<<"/"<<y2<<endl;
        }
        int issued(char pn[30]){
            ifstream i1;
            i1.open("issuedbook.dat",ios::in|ios::binary);
            i1.read((char *)this,sizeof(*this));
            while(!i1.eof()){
                if(strcpy(pn,sid)==0){
                    cout<<"you already issued book !!\n\n\n";
                    i1.close();
                    return 1;
                }
                i1.read((char *)this,sizeof(*this));
            }
            i1.close();
            return 0;
        }

        int bookissue(){
            book b;
            student s;
            char pn[30];
            cout<<"enter your prn : ";
            cin.getline(pn,30);
            if(!issued(pn)){
            if(b.searchbook()){
                cout<<"enter book id :";
                cin>>bid;cin.ignore();
                if(b.decreasebook(bid)){
                    cout<<"enter todays date (dd/mm/yy): ";
                    cin>>d1;cin.ignore();
                    cin>>m1;cin.ignore();
                    cin>>y1;cin.ignore();
                    cout<<"book issued successfully !!\n\n\n";
                    d2=d1;
                    m2=m1+1;
                    if(m2>12){
                        m2=m2-12;
                        y2=y1+1;
                    }
                    else y2=y1;
                    strcpy(sid,pn);
                    ofstream o;
                    o.open("issuedbook.dat",ios::app|ios::binary);
                    o.write((char *)this,sizeof(*this));
                    o.close();
                    showdata();}
                else cout<<"sorry book is not available \n\n\n";
            }
            else cout<<"book not found  !!\n\n\n";
            }
        }
};

class admin:public book{
    char username[30];
    char password[20];
public:
     admin(){
        strcpy(username,"Kaushik8511");
        strcpy(password,"12345678");
    }
    int confirm(){
        char temp1[30],temp2[20];
        cout<<"user name :  ";
        cin.getline(temp1,30);
        cout<<"password :  ";
        cin.getline(temp2,20);
        if(strcmp(temp1,username)==0 && strcmp(temp2,password)==0){
            cout<<"logged in successfully\n";
            return 1;
        }
         cout<<"user name or password wrong\n";
         return 0;
    }
     void confirmstudent(){
        student s1;
        s1.readrequest();
        char c;
        cout<<"\nenter 'c' to confirm request or 'r' to reject request\n";
        cin>>c;
        cin.ignore();
        if(c=='c'){
            s1.writeinfo();
        }
        else cout<<"\nrequest not accepted !!\n";
        s1.deleterequest();
    }
    void liststudent(){
        student s1;
        s1.studentlist();
    }
    void studentremove(){
        student s1;
        s1.removestudent();
    }
    void issuebook(){

    }
};

void adminlogin(){
    admin a;
    if(a.confirm()){
        int c=0;int i;
        while(c==0){
            cout<<"1.add book\n2.remove book\n3.update book\n4.confirm student\n5.view student list\n6.view book list\n7.remove student\n8.logout\n";
            cout<<"enter your choice : ";
            cin>>i;
            cin.ignore();
            switch(i){
                case 1: a.addbook();cout<<"\n\n\n";break;
                case 2:a.deletebook();cout<<"\n\n\n";break;
                case 3:a.updatebook();cout<<"\n\n\n";break;
                case 4:a.confirmstudent();cout<<"\n\n\n";break;
                case 5:a.liststudent();cout<<"\n\n\n";break;
                case 6: a.viewallbooks();cout<<"\n\n\n";break;
                case 7: a.studentremove();cout<<"\n\n\n";break;
                case 8: cout<<"logged out successfully !! ";cout<<"\n\n\n";c=1;break;
                default:cout<<"\nwrong choice !!\n\n\n";
            }
        }
    }
}

void studentlogin(){
    student s;
    if(s.login()){
        int c=0;int i;
        while(c==0){
            cout<<"1.book list\n2.search book\n3.issue book\n4.logout\n";
            cout<<"enter your choice : ";
            cin>>i;
            cin.ignore();
            switch(i){
                case 1:s.listbook();cout<<"\n\n\n";break;
                case 2:s.booksearch();cout<<"\n\n\n";break;
                case 3:// s.bookissue();cout<<"\n\n\n";break;
                case 4:cout<<"\nlogged out successfully !!\n\n\n";c=1;break;
                default:cout<<"\nwrong choice !!!\n\n\n";
            }
        }
    }
}
void studentsignup(){
    student s;
    s.signup();
}

int main(){
   cout<<"1.admin login\n2.student login\n3.sign up for student\n4.exit\n";
   int c;
   cout<<"enter your choice : ";
   cin>>c;
   cin.ignore();
   switch(c){
        case 1: adminlogin();main();
                break;
        case 2: studentlogin();main();
                break;
        case 3:studentsignup();main();
                break;
        case 4: cout<<"thank you !!\n";
                break;
        default: cout<<"\nenter right choice!!\n";
   }
   return 0;
}
