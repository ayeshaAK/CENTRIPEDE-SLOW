/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include <cstdio>

// Asteroids board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
/*
0-nill
1-player

*/
// defining some utility functions...

/* board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };*/

// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	cout << "Initialize board" << endl;
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			// can use G_BRICK, R_BRICK, or S_BRICK here
			board_array[i][j] = 0;
		}
	}
}
//Constructor
Board::Board(int xsize, int ysize) {
	cout << "Constructor board" << endl;
	xcellsize = xsize;
	ycellsize = ysize; 
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED; 
	gcolor = PINK;
	for (int i = 0; i < BOARD_Y; ++i)
		for (int j = 0; j < BOARD_X; ++j)
			board_array[i][j] = 0; 
//set up board
}
void Board::update_Board(int x,int y,int type){
	if(x>=0 && x<BOARD_X){
		if(y>=0 && y<BOARD_Y)
			board_array[y][x]=type;	
	}
	else{
		cout<<"update_Board : x or y out of bound :  "<<x<<","<<y<<endl;
	} 
}
int Board::get_cc(int x,int y)
{//cc = creature code
	if(x>=0 && x<BOARD_X){
		if(y>=0 && y<BOARD_Y)
			return board_array[y][x];	
	}
	return 0;
}
void Board::Draw() {
	glColor3f(0, 0, 1); 
	glPushMatrix();

	for (int i = BOARD_Y - 1, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case 0:
				// Empty space
				break;
			case 1://player
				DrawLine(x+25, y, x+25, y+40, 3, colors[YELLOW]);
				DrawLine(x+60-25, y, x+60-25, y+40,  3, colors[YELLOW]);
				DrawTriangle(x, y, x+60, y, x+(60/2), y+(60/2),colors[MISTY_ROSE] );//gun*
				break;
			case 2://fire
				DrawLine(x+60/2, y, x+60/2, y+60,  2, colors[BROWN]);
				break;
			case 3://mushroom
				DrawCircle(x+30.0, y+30.0, 15,colors[RED] );
				break;
			case 4://centipede
				DrawLine(x, y+25, x+60, y+25,  10, colors[ORANGE]);
				break;
			}
		}
	}
	glPopMatrix();
}

void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}


