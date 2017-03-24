#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<cctype>
#include<stdlib.h>
#include<queue>
#include<fstream>

#define color(x) SetConsoleTextAttribute(hConsole,x)
#define LEFT 'a'
#define MID 's'
#define RIGHT 'd' 


using namespace std;

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

char arena[3][54];
int limit, bottcoord, lives;
float tfactor;
time_t start;
queue<char> ord;

void gotoxy(int x, int y) {
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(hConsole,coord);
}

void display() {
	gotoxy(0,0);
	color(0);
	cout<<"\n\n\t\t\t";
	color(255);
	cout<<"##################################################"<<endl;
	color(0);
	cout<<"\t\t\t";
	for (int i=4; i<=limit; ++i) {
			color(255);
			cout<<"#";
			for (int j=0; j<3; ++j) {
				if (arena[j][i]==' ')	color(119);
				else color(0);
				cout<<"\t\t"<<arena[j][i];
				color(255);
				cout<<"#";
			}
			cout<<endl;
			color(0);
			cout<<"\t\t\t";
	}
	color(255);
	cout<<"##################################################"<<endl<<endl;
	gotoxy(27,55);
	color(7);
	cout<<"LIVES LEFT : ";
	for (int i=0; i<lives; ++i)
		cout<<char(1);
	cout<<"\t\t\t\t\t\t\t";
	gotoxy(60,55);
	cout<<"TIME : ";
	cout<<time(0)-start;
}

void make() {
	int x=rand()%3;
	switch(x) {
		case 0 :
			ord.push(LEFT);
			for (int i=0; i<5; ++i)
				arena[0][i]='.';
			break;
		case 1 :
			ord.push(MID);
			for (int i=0; i<5; ++i)
				arena[1][i]='.';
			break;
		case 2 :
			ord.push(RIGHT);
			for (int i=0; i<5; ++i)
				arena[2][i]='.';
			break;
	}
	
}

void delay(float t) {
	clock_t t1=clock();
	while((((float)(clock()-t1))/CLOCKS_PER_SEC) < t);
}

void movedown() {
	for (int j=0; j<3; ++j) {
		for (int i=53; i>0; --i)
			arena[j][i]=arena[j][i-1];
		arena[j][0]=' ';
	}
}

void input() {
	char x=getch(); x=tolower(x);
	int a=-1;
	if (x==LEFT)	a=0;
	else if (x==MID)	a=1;
	else if (x==RIGHT)	a=2;
	else if (x=='p')	a=3;
	if (x==ord.front()) {
		ord.pop();
		for (int i=0; i<5; ++i)
			arena[a][bottcoord-i]=' ';
		bottcoord-=5;
	}
	else if (a!=-1 && x!='p')	lives-=1;
	else if (x=='p') {
		char p='\0';
		do {
			p=getch();
		}while(p!='p');
	}
}

int main() {
	system("mode 100,100");
	system("cls");
	srand(time(0));
	bool firstLog=true;
	char choice='0';
	do {
		do {
			limit=53;
			bottcoord=3;
			lives=10;
			tfactor=.125;
			while(!ord.empty())	ord.pop();
			system("cls");
			for (int i=0; i<54; ++i)
				for (int j=0; j<3; ++j)
					arena[j][i]=' ';
	
			char startsplash1[9][55]={
				"                                                      ",
				"                                                      ",
				"######   ##     ######    ####  ##  ##      ..........",
				"##   ##  ##     ##  ##   ##     ## ##       ..........",
				"######   ##     ##  ##  ##      ####        ..........",
				"##   ##  ##     ##  ##   ##     ##  ##      ..........",
				"######   #####  ######    ####  ##  ##      ..........",
				"                                                      ",
				"                                                      "
			};
	
				
			for (int i=0; i<9; ++i) {
				gotoxy(4,15+i);
				for (int j=0; j<52; ++j) {
					if (startsplash1[i][j]=='#')	color(255);
					else if (startsplash1[i][j]=='.')	color(238);
					else	color(0);
					cout<<startsplash1[i][j];
				}
			}
			gotoxy(0,60);
			if (firstLog)
				delay(1.5);
			
			char startsplash2[9][53]={
				"                                                 ",
				"                                                 ",
				"######   ##   ##  ######  ########  #####  ##### ",
				"##   ##  ##   ##  ##         ##     ##     ##  ##",
				"######   ##   ##  ######     ##     ####   ##### ",
				"##   ##  ##   ##      ##     ##     ##     ## ## ",
				"######   #######  ######     ##     #####  ##  ##",
				"                                                 ",
				"                                                 "
			};
			
			float t=0.025;
			for (int k=0; k<16; ++k) {
				int h = k < 9 ? 9-k : 0;	
				for (int i=h; i<9; ++i) {
					gotoxy(47,k+i);
					for (int j=0; j<52; ++j) {
						if (startsplash2[i][j]=='#')	color(204);
						else	color(0);
						cout<<startsplash2[i][j];
					}
				}
				delay(t);
				t-=0.0025;
			}
			gotoxy(0,60);
			if (firstLog) {
				clock_t splashtime=clock();
				while((((float)(clock()-splashtime))/CLOCKS_PER_SEC) < 1.5 && kbhit()==0);
				firstLog=false;
			}
			color(15);
			gotoxy(0,28);
			cout<<"\t\t\t\t\t   1. PLAY\n\n\t\t\t\t\t   2. INSTRUCTIONS\n\n\t\t\t\t\t   3. EXIT\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t   Developed by NU";
			gotoxy(0,60);
			do {
				choice=getch();
			}while (choice!='1' && choice!='2' && choice!='3');
			if (choice=='2') {
				system("cls");
				cout<<"\n\n\n\n\n\t\t\t\t\t      CONTROLS\n\t\t\t\t\t      ========\n\n\n\t\t\t\t\t     LEFT   - A\n\n\t\t\t\t\t     MIDDLE - S\n\n\t\t\t\t\t     RIGHT  - D\n\n\t\t\t\t\t     PAUSE  - P\n\n\n\n\n\n\n\n\n";
				cout<<"\n\tUse the A S D keys to remove the blocks as they fall. Entering the wrong key causes \n\n\tyou to lose a life. The game ends when a block touches the white bottom or when you \n\n\t";
				cout<<"lose all 10 of your lives. The speed with which the blocks fall increase throughout \n\n\tthe game and the white bottom keeps getting higher! May you last long...\n\n\n\n\n\t\t\t\t";
				system("pause");
			}
			else if (choice=='3')	exit(0);
		}while(choice!='1');
		system("cls");
		time_t speedtime,warptime;
		speedtime=time(0);
		warptime=time(0);
		start=time(0);
		int trig=4;
		do {
			display();
			delay(tfactor);
			movedown();
			++trig;
			++bottcoord;
			if (trig==5) {
				make();
				trig=0;
			}
			if (kbhit())	input();
			display();
			if (time(0)-start==10) {
				tfactor*=.8;
				speedtime=time(0);
			}
			if ((time(0)-warptime)==20 && limit>27) {
				--limit; display();
				--limit; display();
				--limit;
				warptime=time(0);
			}
		}while(bottcoord!=limit && lives!=0);
		
		char endsplash[11][86]={
			"                                                                                     ",
			"                                                                                     ",
			"  #######   ######   ###     ##   ######      ######   ##      #   ######   ######   ",
			"  ##        ##  ##   ## ## ####   ##          ##  ##    ##    #    ##       ##   ##  ",
			"  ##  ###   ######   ##  ##  ##   ####        ##  ##     ##  #     ####     ######   ",
			"  ##   ##   ##  ##   ##      ##   ##          ##  ##      ###      ##       ##  ##   ",
			"  #######   ##  ##   ##      ##   ######      ######       #       ######   ##   ##  ",
			"                                                                                     ",
			"                                                                                     ",
			"                                                                                     ",
			"                                                                                     "};
		for (int i=0; i<11; ++i) {
			gotoxy(7,24+i);
			for (int j=0; j<86; ++j) {
				if (endsplash[i][j]=='#')	color(204);
				else	color(0);
				cout<<endsplash[i][j];
			}
		}
		color(12);
		gotoxy(38,33);
		cout<<"You survived "<<time(0)-start<<" seconds...";
		getch();
		color(15);
		gotoxy(35,60);
		system("pause");
	}while (true);
	return 0;
}
