#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

// Class to operation performed on Equipment's

class equipment
{
	char eno[6];           // Equipment Model no.
	char ename[50];        // Equpment Name
	char aname[20];        // Company Name
  public:


//      Function to add Equipment


	void create_eqp()
	{
		cout<<"\nNEW Equipment ENTRY...\n";
		cout<<"\nEnter The Equipment Model no.";
		cin>>eno;
		cout<<"\n\nEnter The Name of The Equipment ";
		gets(ename);
		cout<<"\n\nEnter The Company's Name ";
		gets(aname);
		cout<<"\n\n\nBook Created..";
	}


//      Function to Show Equipment


	void show_eqp()
	{
		cout<<"\nEquipment Model no. : "<<eno;
		cout<<"\nEquipment Name : ";
		puts(ename);
		cout<<"Company Name : ";
		puts(aname);
	}


//	Function to modify Equipment

	void modify_eqp()
	{
		cout<<"\nEquipment Model no. : "<<eno;
		cout<<"\nModify Equipment Name : ";
		gets(ename);
		cout<<"\nModify Company's Name of Equipment : ";
		gets(aname);
	}

//      Function to return equipment no.

	char* reteno()
	{
		return eno;
	}

//	Function to generate Report

	void report()
	{cout<<eno<<setw(30)<<ename<<setw(30)<<aname<<endl;}



};


//	Class to operation Performed on  Player

class player
{
	char admno[6];          // Player Addmission No.
	char name[20];          // Player Name
	char stbno[6];          // Equipment Model No. which is issued
	char game[10];          // Game Played by Player
	int token;
public:

//	Function to Add Player

	void create_player()
	{
		clrscr();
		cout<<"\nNEW PLAYER ENTRY...\n";
		cout<<"\nEnter The admission no. ";
		cin>>admno;
		cout<<"\n\nEnter The Name of The Player ";
		gets(name);
		cout<<"Enter Game played by Player: ";
		gets(game);
		token=0;
		stbno[0]='/0';
		cout<<"\n\nPlayer Record Created..";
	}


//	Function to Show Player

	void show_player()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nPlayer Name : ";
		puts(name);
		cout<<"\nGame Played: ";
		puts(name);
		cout<<"\nNo of Equipment issued : "<<token;
		if(token==1)
			cout<<"\nEquipment No "<<stbno;
	}

//	Function to modify Player

	void modify_player()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Player Name : ";
		gets(name);
	}

//	Function to return Admin no.


	char* retadmno()
	{
		return admno;
	}

//	Function to return Equipment no.


	char* retstbno()
	{
		return stbno;
	}

//	Function to return Token

	int rettoken()
	{
		return token;
	}

//	Function to create Token i.e, no. of Equipment issued

	void addtoken()
	{token=1;}


//	Function to reset Token

	void resettoken()
	{token=0;}

//	Function to Issue Token in Player id


	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}


//	Function to Generate Player Report


	void report()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(18)<<game<<setw(10)<<token<<endl;}
};



// Global Function Decelaration


fstream fp,fp1;    // fp for equipment File & fp1 for Player File
equipment bk;      // Equipment object Created
player st;         // Player object Created



//    	Function to write in file


void write_eqp()
{
	char ch;   // more record Entry y/n
	fp.open("equipment.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_eqp();
		fp.write((char*)&bk,sizeof(equipment));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


void write_player()
{
	char ch;    // more record entry y/n
	fp.open("player.dat",ios::out|ios::app);
	do
	{
		st.create_player();
		fp.write((char*)&st,sizeof(player));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


//    	function to read specific record from file


void display_spb(char n[])
{
	cout<<"\nEquipment DETAILS\n";
	int flag=0;
	fp.open("equipment.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(equipment)))
	{
		if(strcmpi(bk.reteno(),n)==0)
		{
			bk.show_eqp();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nEquipment does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"\nPLAYER DETAILS\n";
	int flag=0;
	fp.open("player.dat",ios::in);
	while(fp.read((char*)&st,sizeof(player)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_player();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nPlayer does not exist";
	getch();
}


//    	function to modify record of file


void modify_eqp()
{
	char n[6];     // Model no. of Equipment
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY EQUIPMENT REOCORD.... ";
	cout<<"\n\n\tEnter The Model no. of The Equipment: ";
	cin>>n;
	fp.open("equipment.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(equipment)) && found==0)
	{
		if(strcmpi(bk.reteno(),n)==0)
		{
			bk.show_eqp();
			cout<<"\nEnter The New Details of Equipment"<<endl;
			bk.modify_eqp();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(equipment));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}


void modify_player()
{
	char n[6];      //Addmission no. of Player
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY PLAYER RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The player";
	cin>>n;
	fp.open("player.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(player)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_player();
			cout<<"\nEnter The New Details of Player"<<endl;
			st.modify_player();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(player));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//    	function to delete record of file


void delete_player()
{
	char n[6];     // Addmission no. of player
	int flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETE PLAYER RECORD...";
	cout<<"\n\nEnter The admission no. of the Player You Want To Delete : ";
	cin>>n;
	fp.open("player.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(player)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(player));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("player.dat");
	rename("Temp.dat","player.dat");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}


void delete_eqp()
{
	char n[6];    //Model no. of Equipment
	clrscr();
	cout<<"\n\n\n\tDELETE EQUIPMENT ...";
	cout<<"\n\nEnter The Model no. of the Equipment You Want To Delete : ";
	cin>>n;
	fp.open("equipment.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(equipment)))
	{
		if(strcmpi(bk.reteno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(equipment));
		}
	}

	fp2.close();
	fp.close();
	remove("equipment.dat");
	rename("Temp.dat","equipment.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}




//    	function to display all Players list


void display_alls()
{
	clrscr();
	fp.open("player.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tPLAYER LIST\n\n";
	cout<<"===============================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Game Name"<<setw(25)<<"Equipment Issued\n";
	cout<<"===============================================================================\n";

	while(fp.read((char*)&st,sizeof(player)))
	{
		st.report();
	}

	fp.close();
	getch();
}



//    	function to display Equipments list


void display_allb()
{
	clrscr();
	fp.open("equipment.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tEQUIPMENT LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Model Number"<<setw(25)<<"Equipment Name"<<setw(32)<<"Company Name\n";
	cout<<"=========================================================================\n";

	while(fp.read((char*)&bk,sizeof(equipment)))
	{
		bk.report();
	}
	fp.close();
	getch();
}




//    	function to issue Equipment


void eqp_issue()
{
	char sn[6],bn[6]; 	//sn => Player admission no.  & bn => Equipment model no.
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nEQUIPMENT ISSUE ...";
	cout<<"\n\n\tEnter The Player admission no.";
	cin>>sn;
	fp.open("player.dat",ios::in|ios::out);
	fp1.open("equipment.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(player)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				cout<<"\n\n\tEnter the Model no. ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(equipment))&& flag==0)
				{
					if(strcmpi(bk.reteno(),bn)==0)
					{
						bk.show_eqp();
						flag=1;
						st.addtoken();
						st.getstbno(bk.reteno());
						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(player));
						cout<<"\n\n\t Equipment issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day +after 15 days period";
					}
				}
				if(flag==0)
					cout<<"Equipment Model no does not exist";
			}
			else
				cout<<"You have not returned the last Equipment ";

		}
	}
	if(found==0)
		cout<<"Player record not exist...";
	getch();
	fp.close();
	fp1.close();
}


//    	function to deposit equipment


void eqp_deposit()
{
    char sn[6],bn[6];   	//sn => Player admission no.  & bn => Equipment model no.
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\nEQUIPMENT DEPOSIT ...";
    cout<<"\n\n\tEnter The Player admission no.";
    cin>>sn;
    fp.open("player.dat",ios::in|ios::out);
    fp1.open("equipment.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(player)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(equipment))&& flag==0)
			{
			   if(strcmpi(bk.reteno(),st.retstbno())==0)
			{
				bk.show_eqp();
				flag=1;
				cout<<"\n\nEquipment deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(player));
					cout<<"\n\n\t Equipment deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Equipment Model no does not exist";
		      }
		 else
			cout<<"No Equipment is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Player record not exist...";
	getch();
  fp.close();
  fp1.close();
  }



//    	INTRODUCTION FUNCTION


void intro()
{
	clrscr();
	gotoxy(35,11);
	cout<<"SPORT CLUB";
	gotoxy(35,14);
	cout<<"MANAGEMENT";
	gotoxy(35,17);
	cout<<"SYSTEM";
	cout<<"\n\nMADE BY : KEERTI";
	cout<<"\n\nCOLLEGE : SAGAR INSTITUTE OF SCIENCE & TECHNOLOGY, BHOPAL";
	getch();
}




//    	ADMINISTRATOR MENU FUNCTION

void admin_menu()
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.ADD PLAYER RECORD";
	cout<<"\n\n\t2.DISPLAY ALL PLAYER RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC PLAYER RECORD ";
	cout<<"\n\n\t4.MODIFY PLAYER RECORD";
	cout<<"\n\n\t5.DELETE PLAYER RECORD";
	cout<<"\n\n\t6.ADD EQUIPMENT";
	cout<<"\n\n\t7.DISPLAY ALL EQUIPMENT ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC EQUIPMENT ";
	cout<<"\n\n\t9.MODIFY EQUIPMENT ";
	cout<<"\n\n\t10.DELETE EQUIPMENT ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_player();break;
		case 2: display_alls();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The Admission No. ";
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_player();break;
		case 5: delete_player();break;
		case 6: clrscr();
			write_eqp();break;
		case 7: display_allb();break;
		case 8: {
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The equipment model No. ";
			cin>>num;
			display_spb(num);
			break;
			}
		case 9: modify_eqp();break;
		case 10: delete_eqp();break;
		case 11: return;
		default:cout<<"\a";
	}
	admin_menu();
}


//    	THE MAIN FUNCTION OF PROGRAM


void main()
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. EQUIPMENT ISSUE";
		cout<<"\n\n\t02. EQUIPMENT DEPOSIT";
		cout<<"\n\n\t03. ADMINISTRATOR MENU";
		cout<<"\n\n\t04. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-4) ";
		ch=getche();
		switch(ch)
		{
			case '1':clrscr();
				 eqp_issue();
				 break;
			case '2':eqp_deposit();
				 break;
			case '3':admin_menu();
				 break;
			case '4':exit(0);
			default :cout<<"\a";
		}
	}while(ch!='4');
}

