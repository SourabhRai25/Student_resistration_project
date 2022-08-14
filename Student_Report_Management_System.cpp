#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// the class that stores data of each student;
class XII_student
{
int rollno;
char name[50];
int english_marks, math_marks, chemistry_marks, physics_marks, CS_marks;
double average;
char grade;

public:
void get_data();
void show_data() const;
void calculate_grade();
int return_rollno() const;
}; //class ends here

void XII_student::calculate_grade()
{
average=(english_marks + math_marks + chemistry_marks + physics_marks + CS_marks)/5.0;
if(average>=90)
grade='A';
else if(average>=75)
grade='B';
else if(average>=50)
grade='C';
else
grade='F';
}

void XII_student::get_data()   // getting data of each students
{
cout<<"\nEnter student's roll number: ";
cin>>rollno;
cout<<"\nEnter student name:          ";
cin.ignore();
cin.getline(name,50);
cout<<"\n\n\t* All marks should be out of 100";
cout<<"\n\nEnter marks in English:         ";
cin>>english_marks;
cout<<"\nEnter marks in Math:              ";
cin>>math_marks;
cout<<"\nEnter marks in Chemistry:         ";
cin>>chemistry_marks;
cout<<"\nEnter marks in Physics:           ";
cin>>physics_marks;
cout<<"\nEnter marks in Computer science:  ";
cin>>CS_marks;
calculate_grade();
}
void XII_student::show_data() const
{
cout<<"\n\n\t---------------------------";
cout<<"\n\t|  Name        : "<<name;
cout<<"\n\t|  Roll number : "<<rollno;
cout<<"\n\t---------------------------";
cout<<"\n\t---------------------------";
cout<<"\n\t|  English   ||       "<<english_marks<<"  |";
cout<<"\n\t|  Maths     ||       "<<math_marks<<"  |";
cout<<"\n\t|  Chemistry ||       "<<chemistry_marks<<"  |";
cout<<"\n\t|  Physics   ||       "<<physics_marks<<"  |";
cout<<"\n\t|  CS        ||       "<<CS_marks<<"  |";
cout<<"\n\t---------------------------";
cout<<"\n\t|\t  Average  :  "<<average<<"  |";
cout<<"\n\t|\t  Grade    :   "<<grade<<"  |";
cout<<"\n\t---------------------------\n";
}
int  XII_student::return_rollno() const
{
return rollno;
}
//write student details to file
void create_student()
{
XII_student stud;
ofstream oFile;
oFile.open("student.dat",ios::binary|ios::app);
stud.get_data();
oFile.write(reinterpret_cast<char *> (&stud), sizeof(XII_student));
oFile.close();
cout<<"\n\nStudent record Has Been Created ";
cin.ignore();
cin.get();
}
// read file records
void display_all()
{
XII_student stud;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be opened !! Press any Key to exit";
cin.ignore();
cin.get();
return;
}
system("cls");
cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(XII_student)))
{
stud.show_data();
cout<<"\n\n====================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}
//read specific record based on roll number
void display_sp(int n)
{
XII_student stud;
ifstream iFile;
iFile.open("student.dat",ios::binary);
if(!iFile)
{
cout<<"File could not be opened... Press any Key to exit";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(XII_student)))
{
if(stud.return_rollno()==n)
{ system("cls");
  stud.show_data();
flag=true;
}
}
iFile.close();
if(flag==false)
cout<<"\n\nrecord does not exist";
cin.ignore();
cin.get();
}
// modify record for specified roll number
void change_student(int n)
{
bool found=false;
XII_student stud;
fstream fl;
fl.open("student.dat",ios::binary|ios::in|ios::out);
if(!fl)
{
cout<<"File could not be opened. Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
     while(!fl.eof() && found==false)
{
fl.read(reinterpret_cast<char *> (&stud), sizeof(XII_student));
if(stud.return_rollno()==n)
{
stud.show_data();
cout<<"\nEnter new student details:"<<endl;
stud.get_data();
    int pos=(-1)*static_cast<int>(sizeof(stud));
    fl.seekp(pos,ios::cur);
    fl.write(reinterpret_cast<char *> (&stud), sizeof(XII_student));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
fl.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}
//delete record with particular roll number
void delete_student(int n)
{
XII_student stud;
ifstream iFile;
iFile.open("student.dat",ios::binary);
if(!iFile)
{
cout<<"File could not be opened... Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
ofstream oFile;
oFile.open("Temp.dat",ios::out);
iFile.seekg(0,ios::beg);
while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(XII_student)))
{
if(stud.return_rollno()!=n)
{
oFile.write(reinterpret_cast<char *> (&stud), sizeof(XII_student));
}
}
oFile.close();
iFile.close();
remove("student.dat");
rename("Temp.dat","student.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}
//MAIN
int main()
{
char ch;
cout<<setprecision(2); 
do
{
char ch;
int num;
system("cls");
cout<<"\n\n\n\tMENU";
cout<<"\n\n\t1.Create student record";
cout<<"\n\n\t2.Search student record";
cout<<"\n\n\t3.Display all students records ";
cout<<"\n\n\t4.Delete student record";
cout<<"\n\n\t5.Modify student record";
cout<<"\n\n\t6.Exit";
cout<<"\n\nEnter your Choice (1/2/3/4/5/6) ";
cin>>ch;
system("cls");
switch(ch)
{
case '1': create_student(); 
          break;
case '2': cout<<"\n\n\tEnter The roll number "; 
          cin>>num;
          display_sp(num); 
          break;
case '3': display_all(); 
          break;
case '4': cout<<"\n\n\tEnter The roll number: "; 
          cin>>num;
          delete_student(num);
          break;
case '5': cout<<"\n\n\tEnter The roll number "; 
          cin>>num;
          change_student(num);
          break;
case '6': cout<<"Exiting, Thank you!";
          exit(0);

}
}while(ch!='6');
return 0;
}
