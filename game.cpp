//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "Board.h"
#include "util.h"
#include <random>
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

Board *b;
int level;
int score;
int coun; 
//-------------------------------------------added functions prototypes
void mushroom_shot(int xc,int yc);
bool Centipede_shot(int xc,int yc);
int rnir(int s,int e);

//-------------------------------------------new classes
//board array of 34x28
class Cell{
public:
	int xc;//x coordinate
	int yc;//y coordinate
	int bn;//switch case borad no.(i.e what to draw on board)
	Cell(){xc=16;yc=13,bn=0;b->update_Board(xc,yc,bn);}
	Cell(int x,int y ,int n=0){
		xc=x;yc=y;bn=n;
		b->update_Board(xc,yc,bn);
	}
	Cell& operator=(const Cell& n){
		this->xc=n.xc;
		this->yc=n.yc;
		this->bn=n.bn;
		return *this;
	}
	void set_bn(int n){
		bn=n;
		b->update_Board(xc,yc,bn);
	}
	void set_null(){ 
		b->update_Board(xc,yc,0);
	}
	void new_set(int x,int y ,int n){
		xc=x;yc=y;bn=n;
		b->update_Board(xc,yc,bn);
	}
	void set(int x,int y ,int n){
		xc=x;yc=y;
		b->update_Board(xc,yc,n);
	}
	void set(int x,int y){
		xc=x;yc=y;
		b->update_Board(xc,yc,bn);
	}
	void redraw(){
		b->update_Board(xc,yc,bn);
	}
	void cell_up(){
		if(yc>0){
			set(xc,yc,0);
			if(b->get_cc(xc,yc-1)==3){ 
				mushroom_shot(xc,yc-1);
				new_set(xc,0,0);
			}
			else if(b->get_cc(xc,yc-1)==4){ 
				Centipede_shot(xc,yc-1);
				new_set(xc,0,0);
			}
			else{
				yc--;
				set(xc,yc);
			}
		}
	}
	void cell_down(){
		if(yc<(b->BOARD_Y)-1){
			set(xc,yc,0);
			yc++;
			set(xc,yc);
		}
	}
	void cell_right(){
		if(xc>0){
			set(xc,yc,0);
			xc--;
			set(xc,yc);
		}
	}
	void cell_left(){
		if(xc<(b->BOARD_X)-1){
			set(xc,yc,0);
			xc++;
			set(xc,yc);
		}
	}
};
class Mushroom : public Cell{//---------------------------------------------------------------------
public:
	int life;//max 2
	int mcn=3;//mushroom code number
	Cell mc;//mushroom cell
	Mushroom(){
		life=2;
		mc.set_bn(3); 
	}
	Mushroom& operator=(const Mushroom& n){
		this->life=n.life;
		this->mcn=n.mcn;
		this->mc=n.mc;
		return *this;
	}
	bool damage(){
		bool dead;
		cout<<"life was : "<<life<<endl;
		life--;
		cout<<"now life is : "<<life<<endl;
		if(life<=0){ 
			mc.set_bn(0);
			dead=true; 
		}
		else{
			dead=false;
		}
		return dead;
	}
	void p(){
		cout<<"("<< mc.xc<<","<< mc.yc<<"|"<< mc.bn<<")		";
	}
};
class Mushrooms{
public:
	Mushroom * m_array;
	int no;
	Mushrooms(){
		no=rnir(20,30);
		no=no+(level*0.2)*no;
		m_array=new Mushroom[no];
		fill_array();
		//add_m();
		//rem_m(m_array[0].mc.xc,m_array[0].mc.yc);
	}
	void fill_array(){
		int xc,yc;
		for(int i=0;i<no;i++){
			xc=rnir(0,16);yc=rnir(0,9); 
			m_array[i].mc.set(xc,yc); 
		}
	}
	void add_m(){
		bool ins=false;
		int xc,yc;
		while(!ins){
			ins=true; 
			xc=rnir(0,16);yc=rnir(0,9);
			for(int j=0;j<no;j++){
				if(m_array[j].mc.xc==xc && m_array[j].mc.yc==yc){
					j=no;
					ins=false;
				}
			}																						
		}
		Mushroom * nm_array=new Mushroom[no+1];
		for(int i=0;i<no;i++){
			nm_array[i]=m_array[i];
		}
		nm_array[no].mc.set(xc,yc);
		delete m_array;
		m_array=nm_array;
		no++;
		cout<<"new mushroom added --"<<endl;
	}
	int find_m(int xc,int yc){
		for(int j=0;j<no;j++){
			if(m_array[j].mc.xc==xc && m_array[j].mc.yc==yc){
				return j;
			}
		}																						
	} 
	void redraw_m(){
		for(int i=0;i<no;i++){
			m_array[i].mc.redraw();
		}
	}
	void p(){
		cout<<"--total Mushrooms : "<<no<<endl;
		for(int i=0 ; i<no ; i++){
			m_array[i].p();
		}
		cout<<endl;
	}
	void rem_m(int xc, int yc){ 
		int ind=find_m(xc,yc);
		m_array[ind].mc.set_bn(0);
		p();
		cout<<"out of print"<<endl;
		//problem here
		Mushroom * nm_array=new Mushroom[no-1];
		for(int j=0,i=0;j<no;j++){
			if(j!=ind){
				cout<<"updating array at index : "<<endl;

				//m_array[i].mc.set_bn(0);
				nm_array[i]=m_array[j]; 
				//nm_array[i].mc.set_bn(3);
				i++;

			} 																						
		}  
		delete m_array;
		m_array=nm_array;
		no--;
		p();
		cout<<"mushroom removed --"<<endl;
	}

};
class Segment{
	Cell cc;//centeped cell
};
class lazy: public Segment{

};
class magic: public Segment{

};
class Centipede : public Cell{
public:
	int ccn=4;//centipede code number
	int size;
	bool right;//if true then move right else left
	bool left;
	Cell *c_array;
	int step_size;
	Centipede(int s){
		right=true;
		left=false;
		size=s-level;
		step_size=level+1;
		c_array=new Cell[size];
		for(int i=0;i<size;i++){
			c_array[i].new_set(i,0,ccn); 
		}
	}
	bool move_right(){
		cout<<"moving right centipede----o"<<endl;
		bool cont=true;//continue
		for(int i=0;i<size;i++){
			c_array[i].set_null();
		}
		if(b->get_cc(c_array[size-1].xc+1,c_array[size-1].yc)==3 || c_array[size-1].xc+1==b->BOARD_X){//collosion
				cout<<"moving right centipede collided----o"<<endl;
				cont=false; 
				int j=0;
				for(int i=b->BOARD_X-1;j<size;i--){ 
					if(c_array[j].yc<10){
						c_array[j].set(i,c_array[j].yc+1,ccn); 
						j++;
					}else{
						c_array[j].set(i,c_array[j].yc,ccn); 
						coun++;
						j++;
					}
				}
		}
		else{
			for(int i=0;i<size;i++){ 
				c_array[i].set(c_array[i].xc+1,c_array[i].yc);
			}
		} 
		return cont;
	}
	bool move_left(){
		cout<<"moving left centipede----o"<<endl;
		bool cont=true;
		for(int i=0;i<size;i++){
			c_array[i].set_null();
		}
		if(b->get_cc(c_array[size-1].xc-1,c_array[size-1].yc)==3 || c_array[size-1].xc-1==0){//collosion
				cout<<"moving left centipede collided----o"<<endl;
				cont=false; 
				for(int i=0;i<size;i++){
					if(c_array[i].yc<10){
						c_array[i].set(i,c_array[i].yc+1,ccn); 
					}else{
						c_array[i].set(i,c_array[i].yc,ccn);
					}
				}
		}
		else{
			for(int i=0;i<size;i++){ 
				c_array[i].set(c_array[i].xc-1,c_array[i].yc);
			}
		}
		return cont;
	}
	void move_c(){
		if(right){
			right=move_right();
			if(!right){
				left=true;
				cout<<"value of right : "<<right<<endl;
			}
		}else if(left){
			left=move_left();
			if(!left){
				right=true;
				cout<<"value of left : "<<left<<endl;
			}
		}
	} 
	int index_c(int x,int y){
		for(int i=0;i<size;i++){
			if(c_array[i].xc==x && c_array[i].yc==y){
				return i;
			}
		}
	}
	int size_c(){
		return size;
	} 
	void dec_c(){
		Cell *nc_array = new Cell[size-1];
		for(int i=0;i<size-1;i++){
			nc_array[i]=c_array[i];
		}
		delete c_array;
		c_array= nc_array;
		size--;
	}
};
class Player{ //-----------------------------------------------------------------------
public:
	Cell pc;//player cell
	Cell bc;//bullet cell
	int pcn=1;//player code number
	int fcn=2;//fire code number
	Player(int x,int y){
		pc.new_set(x,y,pcn);
		bc.new_set(x,0,0);
	} 
	void move_right(){
		if(pc.xc<(b->BOARD_X)-1){
			pc.set(pc.xc,pc.yc,0);
			pc.xc++;
			pc.set(pc.xc,pc.yc); 
		}
		else{
			cout<<"can't move right out of board"<<endl;
		}
	} 
	void move_left(){
		if(pc.xc>0){
			pc.set(pc.xc,pc.yc,0);
			pc.xc--;
			pc.set(pc.xc,pc.yc); 
		}
		else{
			cout<<"can't move left out of board"<<endl;
		}
	}
	void fire(){
		if(bc.yc==0){
			bc.new_set(pc.xc,pc.yc-1,fcn);
			cout<<"new fire"<<endl;
	 	}
	}
	void update_fire(){
		if(bc.yc>0){
			bc.cell_up(); 
		}
		else{
			bc.set(bc.xc,bc.yc,0);
		}
	}
	~Player(){
		 
	}
};
Player *p; 
Mushrooms *m;
Centipede *c;
//--------------------------------------------functions
void mushroom_shot(int xc,int yc){
	int ind=m->find_m(xc,yc);
	cout<<"shot at index & coordinates : "<<ind<<" & "<<xc<<","<<yc<<endl;
	bool dead=m->m_array[ind].damage();
	score+=1;
	cout<<"dead? : "<<dead<<endl;
	if(dead==true){
		m->rem_m(xc,yc); 
		cout<<"removed mushroom"<<endl;	
		score+=5;	
	}
}
bool Centipede_shot(int xc,int yc){ 
	int ind=c->index_c(xc,yc);
	if(ind==(c->size_c())-1){
		c->dec_c();
		score+=100;
	}
	else{
		m->add_m();
		score+=10;
	}
}
int rnir(int s,int e)//random no in range
{
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(s, e); // define the range 
    return distr(eng); 
}
//--------------------------------------------------------------------------------------------
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */


void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors 
	//1020x840 - using pixels
	/*DrawSquare( 10,10 ,30,colors[GREEN]); 
	DrawSquare( 0, 810,30,colors[RED]); 
	DrawSquare(  990,0,30,colors[YELLOW]); 
	DrawSquare( 990,810 ,30,colors[BROWN]); */

	//34x28 - using board array
	/*b->update_Board(0,0,1);//BROWN-top right
	b->update_Board(16,13,3);//LIGHT_GREEN-left bottom
	b->update_Board(0,13,4);//RED-right bottom
	b->update_Board(16,0,2);//SLATE_GRAY-top left*/
	if(coun>=10 && coun<=13){ 
		//DrawString( 50, 10, "              ", colors[MISTY_ROSE]);
		DrawString( 300, 10, "|-GAME FINISHED-|", colors[ORANGE]);
		//cout<<"game finished"<<endl;
		//cout.flush();
		//usleep(5000000); 
		//exit(1);
	}
	if(coun>=14){
		exit(1);
	}
	//SCORE
	DrawString( 50, 10, "Score="+to_string(score), colors[MISTY_ROSE]);
	/*int x=0;int y=0;
	//PLAYER
	DrawLine(x+20, y, x+20, y+40, 3, colors[YELLOW]);
	DrawLine(x+60-20, y, x+60-20, y+40,  3, colors[YELLOW]);
	DrawTriangle(x, y, x+60, y, x+(60/2), y+(60/2),colors[MISTY_ROSE] );//gun*
	x=0;y=60;
	//BULLET
	DrawLine(x+60/2, y, x+60/2, y+60,  2, colors[BROWN]);
	//MUSHROOM
	y+=60;
	DrawCircle(x+30.0, y+30.0, 20,colors[RED] );
	//CENTIPEDE
	y+=60;
	DrawLine(x, y+25, x+60, y+25,  10, colors[ORANGE]);
*/
	p->update_fire(); 
	c->move_c();
	m->redraw_m();
	b->Draw();
	glutSwapBuffers(); // do not modify this line.. 
	
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed... 
		p->move_left();


	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) { 
		p->move_right();
	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}



}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 'q'/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	if (key == ' ') //Key for placing the bomb
	{
		//player is shooting
		p->fire();
	} 
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int Iunused) {

	// implement your functionality here
		/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/ 
	glutPostRedisplay();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(140.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl; 
}
void MouseMoved(int x, int y) {
 
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl; 
		
	} 
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		
	} 
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	level=0;
	score=0;
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b = new Board(60, 60); // create a new board object to use in the Display Function ... 
	b->InitalizeBoard(width, height);//34x28

	p = new Player(10,12); 
	m = new Mushrooms();
	c = new Centipede(5);
	coun=0;
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	Timer(0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */

