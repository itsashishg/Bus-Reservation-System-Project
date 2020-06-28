using namespace std;
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
#include<iomanip>
#include<fstream>
void gotoxy(short x, short y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
int addr,ad,flag,f1,d,m,i,amt;
float tamt;
class detail
{
	public:
	int bno;
	string bname,bp,dest;
	int c1,c1fare;
	int d,m,y;
	void getdetail()
	{
		cout<<"Enter the details as follows\n";
		cout<<"Bus no:";
		cin>>bno;
		cout<<"Bus name:";
		cin>>bname;
		cout<<"Boarding point:";
		cin>>bp;
		cout<<"Destination pt:";
		cin>>dest;
		cout<<"No of seats in Seats:";
		cin>>c1;
		cout<<"Enter Cost per seat:";
		cin>>c1fare;
		cout<<"Date of travel:";cin>>d>>m>>y;
	}
	void displaydetail()
	{
		//system("cls");
		cout<<"Bus Number="<<bno<<"\tBus Name="<<bname;
		cout<<"\nBoarding Point="<<bp<<"\tDestination="<<dest;
		cout<<"Number of Seats="<<c1<<"\tCost/seat="<<c1fare;
		cout<<"Date="<<d<<"-"<<m<<"-"<<y<<"\t"<<endl;
	}
};
class reser
{
	public:
	int pnr;
	int bno;
	string bname,bp,dest,pname[5];
	int age[20];
	int nosr;
	int i;
	int d,m,y;
	float amc;
	void getresdet()
	{
		cout<<"Enter the details as follows\n";
		cout<<"Bus no:";
		cin>>bno;
		cout<<"Bus name:";
		cin>>bname;
		cout<<"Boarding point:";
		cin>>bp;
		cout<<"Destination pt:";
		cin>>dest;
		cout<<"No of seats required:";cin>>nosr;
		for(i=0;i<nosr;i++)
		{
			cout<<"Passenger name:";
			cin>>pname[i];
			cout<<"Passenger age:";
			cin>>age[i];
		}
		cout<<"Date of travel:";cin>>d>>m>>y;
		cout<<"............END OF GETTING DETAILS............\n";
	}
	void displayresdet()
	{
		system("cls");
		cout<<"...............................................\n";
		cout<<"...............................................\n";
		cout<<"Pnr no:"<<pnr;
		cout<<"\nBus no:"<<bno;
		cout<<"\nBus name:"<<bname;
		cout<<"\nBoarding point:"<<bp;
		cout<<"\nDestination pt:"<<dest;
		cout<<"\nNo of seats reserved:"<<nosr;
		for(i=0;i<nosr;i++)
		{
			cout<<"\nPassenger name:";
			cout<<pname[i];
			cout<<"\tPassenger age:"<<age[i]<<endl;
		}
	cout<<"\nDate of reservation:"<<d<<"-"<<m<<"-"<<y;
	cout<<"\nYou must pay:"<<amc<<endl;
	cout<<"***********************************************\n";
	cout<<".........END OF RESERVATION.................\n";
	cout<<"***********************************************\n";
	}
};

void manage();
void can();
void user();
void database();
void res();
void reserve();
void displaypassdetail();
void cancell();
void enquiry();

void intro()
{
	system("cls");
		 gotoxy(27,10);
 		printf("Bus Reservation");
 		gotoxy(30,12);
 		printf("System");
 		printf("\n");
 		gotoxy(20,18);
 			{
 				printf("MADE BY : Ashish Gupta\n");
 				printf("\t\t\t  K17KWA30");
  			}
 
 	Sleep(5000);
	system("cls");
	gotoxy(25,10);
	printf("Welcome to");
	gotoxy(27,12);
	printf("Bus Reservation System");
	Sleep(3000);
	system("cls");
}

void database()
{
	int i=0;
	char *password;
	cout<<"Enter the admininistrator password:";
	while (i<8)
	 {
	    password[i]=getch();
	    cout<<"*";
	    ++i;
	 }
    password[i]='\0';
	detail a;
	fstream f;
	int ch;
	char c;
	if(strcmp(password,"12345678")!=0)
	{
		cout<<"Enter the password correctly \n";
		cout<<"You are not permitted to logon this mode\n";
	}
	if(strcmp(password,"12345678")==0)
	{
		char c;
		do
		{
			system("cls");
			cout<<"\n...........ADMINISTRATOR MENU...........\n";
			cout<<"1.Create detail data base\n2.Add details\n";
			cout<<"3.Display details\n";
			cout<<"4.Display passenger details\n5.Return to main menu\n";
			cout<<"Enter your choice:";
			cin>>ch;
			cout<<endl;
			switch(ch)
			{
				case 1:
				f.open("t.dat",ios::binary);
				do
				{
					a.getdetail();
					f.write((char *)&a,sizeof(a));
					cout<<"Do you want to add one more record?\n";
					cout<<"y-for Yes\nn-for No\n";
					cin>>c;
				}while(c=='y');
				f.close();
				break;
				case 2:
				f.open("t.dat",ios::binary|ios::app);
				a.getdetail();
				f.write((char *)&a,sizeof(a));
				f.close();
				break;
				case 3:
				f.open("t.dat",ios::in);
				f.seekg(0);
				while(f.read((char *)&a,sizeof(a)))
				{
					a.displaydetail();
				}
				f.close();
				break;
				case 4:
				displaypassdetail();
				break;
			}
		}while(ch<=4);
	f.close();
	}
}

void reserve()
{
	int ch;
	do	
	{
		cout<<"1.Reserve\n2.Return to the main menu\n";
		cout<<"Enter your choice:";
		cin>>ch;
		cout<<endl;
		switch(ch)
		{
			case 1:
			res();
			break;
		}
	}while(ch==1);
	getch();
}

void res()
{
	int flag=0;
	detail a;
	reser b;
	fstream f1,f2;
	time_t t;
	f1.open("t.dat",ios::in|ios::binary);
	f2.open("p.dat",ios::binary|ios::app);
	int ch;
	b.getresdet();
	while(f1.read((char *)&a,sizeof(a)))
	{
		if(a.bno==b.bno)
		{
			if(a.c1>=b.nosr)
			{
				amt=a.c1fare;
				addr=f1.tellg();
				ad=sizeof(a.c1);
				f1.seekp(addr-(7*ad));
				a.c1=a.c1-b.nosr;
				f1.write((char*)&a.c1,sizeof(a.c1));
				b.amc=b.nosr*amt;
				srand((unsigned) time(&t));
				b.pnr=rand();
				f2.write((char*)&b,sizeof(b));
				b.displayresdet();
				cout<<"------------------------------------------------------\n";
				cout<<"--------------Your ticket is reserved-----------\n";
				cout<<"-----------------End of reservation menu-------\n";
			}
		}
		else
		{
			flag=1;
		}
	}
	if(flag==1)
	{	
		cout<<"............Wrong Bus no......................\n";
		cout<<"......Enter the Bus no from the data base.....\n";
	}
	f1.close();
	f2.close();
	getch();
}
void displaypassdetail()
{
	fstream f;
	reser b;
	f.open("p.dat",ios::in|ios::binary);
	f.seekg(0);
	while(f.read((char*)&b,sizeof(b)))
	{
		b.displayresdet();
	}
	f.close();
	getch();
}
void enquiry()
{
	fstream f;
	f.open("t.dat",ios::in|ios::binary);
	detail a;
	f.seekg(0);
	while(f.read((char*)&a,sizeof(a)))
	{
		a.displaydetail();
	}
}

void user()
{
	int main();
	int ch;
	cout<<"*****************************************************\n";
	cout<<"***********WELCOME TO THE USER MENU**\n";
	cout<<"****************************************************\n";
		do
		{
			cout<<"1.Reserve\n2.Enquiry\n3.Return to the main menu\n";
			cout<<"Enter your choice:";
			cin>>ch;
			cout<<endl;
			switch(ch)
			{
				case 1:
						reserve();
						break;
				case 2:
						enquiry();
				break;
				case 3:
						main();
			}
		}while(ch<=3);
}
int main()
{
	//intro();
	int ch;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<".......WELCOME TO BUS RESERVATION SYSTEM..........\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	do
	{
		system("cls");
		cout<<"^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^\n";
		cout<<"1.Admin mode\n2.User mode\n3.Exit\n";
		cout<<"Enter your choice:";
		cin>>ch;
		cout<<endl;
		switch(ch)
		{
		case 1:
				database();
				break;
		case 2:
				user();
				break;
		case 3:
				exit(0);
		}
	}
	while(ch<=3);
	getch();
}
