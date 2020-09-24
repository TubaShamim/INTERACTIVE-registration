#include <iostream>
#include <curses.h> 
#include <fstream>
#include <assert.h> 
#include "coord.h"   
using namespace std; 
fstream usernames;
fstream mmn;
fstream pass;
char c;  
string newpassword;
string username;
string MMN; 
string confpassword;
int movement;
enum movement {abox,cbox,dbox,ebox,fbox,gbox};
coord frontcursorloc[6]={coord(26,4),coord(26,7),coord(26,10),coord(26,13),coord(22,21),coord(43,21)}; 
/*coord backcursorlocname[6]={coord(26,4),coord(43,21),coord(22,21),coord(26,13),coord(26,10),coord(26,7)};*/

void cycletab(){
    int i=movement++%6;
    move(frontcursorloc[i].my,frontcursorloc[i].mx);
    cout << frontcursorloc[i].my;
} 

/*void backcycletab1(){ 
int i=movement++%7;
    move(backcursorlocname[i].my,backcursorlocname[i].mx);
    cout << backcursorlocname[i].my;
}*/
 
void nxtbox(){
noecho();
keypad(stdscr, TRUE);  
cycletab();

while (int c=getch()){
int tab=(movement%6==0)?5:movement%6-1;
assert(tab >= 0 && tab < 6);
switch (c){

	case 10:
  case -53:
		//if (c==' '){ 
			if(tab==fbox)return; 
			if(tab==gbox){
   	 	username="<no input>";
			MMN="<no input>";
    	newpassword="<no input>"; 
			confpassword="<no input>";
			return;
			}
      break;
		//}

	case KEY_RIGHT:
		cycletab();
		break;

	/*case KEY_LEFT:
			backcycletab1();
	break;*/
 
	default:
    switch(tab){ 
      case abox:
      if(int(c)!=127)printw("%c",c);
       username.append(1,c);
			usernames.open("names.txt");
			usernames<<username;
			usernames.close();
      break;
			case cbox:
       if(int(c)!=127)printw("%c",c);
       MMN.append(1,c);
			 mmn.open("MMN.txt");
			 mmn<<MMN;
			 mmn.close();
      break;
			case dbox:
       if(int(c)!=127)printw("%c",'*');
       newpassword.append(1,c);
      break;
			case ebox:
       if(int(c)!=127)printw("%c",'*');
       confpassword.append(1,c);
      break;
        }

}
}
}



void name(){
	mvprintw(4,4,"Username");  

	WINDOW* abox = newwin(3, 36, 3, 25);
	refresh();
	box(abox, 0, 0);
	wrefresh(abox);
}
 
void MMName(){
	mvprintw(7,4,"Mother's maiden name");

	WINDOW* cbox = newwin(3, 36, 6, 25);
	refresh();
	box(cbox, 0, 0);
	wrefresh(cbox);
}

void registration(){ 
int x=0, y=1, w=67, h=25;

	WINDOW *win = newwin(h,w,y,x);

	refresh();
	move(1, 25);
	
	attron(A_BOLD);
	printw("REGISTRATION");
	attron(A_BOLD);

	box(win, 0, 0); 
	wrefresh(win);
} 

void displayPassword(){
	mvprintw(10, 4, "New Password");

	WINDOW* dbox = newwin(3, 36, 9, 25);
	refresh();
	box(dbox, 0, 0);
	wrefresh(dbox);
}
 
void displayPassword2(){
	mvprintw(13, 4, "Confirm New Password");
 
	WINDOW* ebox = newwin(3, 36, 12, 25);
	refresh();
	box(ebox, 0, 0);
	wrefresh(ebox);
}

void displayOkCancel(){
	WINDOW* fbox = newwin(3, 10, 20, 18);
	refresh();
	box(fbox, 0, 0);
	mvwprintw(fbox, 1, 1, "   Ok");
	wrefresh(fbox);


	WINDOW* gbox = newwin(3, 10, 20, 39);
	refresh();
	box(gbox, 0, 0);
	mvwprintw(gbox,1, 1, " Cancel");
	wrefresh(gbox);
}  

void comparepass(string newpassword, string confpassword){
	    if (newpassword != confpassword) 
        cout << "error: passwords do not match. unable to register.";
			else if (newpassword == confpassword) {
      	cout << "passwords match. you are now a registered user.";
				pass.open("pass.txt");
				pass<<confpassword;
				pass.close();
			}
			else
			cout<<"error";
}

int main(){
initscr();
noecho();
cbreak();


    registration();
    name();
    MMName();
    displayPassword();
		displayPassword2();
		displayOkCancel();
		nxtbox();
		//cycletab();
	getch();

	//deallocate memory and ends ncurses
	endwin();
cout << "\n\nusername received was : " << username << endl;
cout << "MMN received was : " << MMN << endl;
cout << "passw obtained was : " << confpassword << endl;
comparepass(newpassword, confpassword);
	return 0;
}