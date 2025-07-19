/* 
	Please use #include "dungeon.c" in the main part of the Machine project. 

	This Machine Project is made by:
	1. Jon Regan Choa
	2. Chester Aldrin G. Uy

	Subject: CCPROG2 | Programming with Structured Data Types
	Checked by: Arturo P. Caronongan III
	Department: Department of Software Technology
	
	NOTE
	1. Dungeon Border (0), Passable Tiles (1), Wall Tiles (2), Exit Tile (7), and Yohane (9) are done!
	Grid design is pending for other ones.
	2. Try checking the switch cases first. If it works, we'll use that method.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_ROW 20
#define MAX_COL 40

typedef int grid[MAX_ROW][MAX_COL];

// Array modification to apply symbols as part of the MP requirements

/*
	Please check the Machine Project for your convenience.
*/
void dungeonIdentifier(grid dimension2D, int nRow, int nCol){
	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 0) //Dungeon Border
				printf("*");
			else if(dimension2D[i][j] == 1) //Passable Tiles
				printf(".");
			else if(dimension2D[i][j] == 2) //Wall Tiles
				printf("v");
			else if(dimension2D[i][j] == 3) //Spike Tiles
				printf("x");
			else if(dimension2D[i][j] == 4) //Water Tiles
				printf("w");
			else if(dimension2D[i][j] == 5) //Heat Tile
				printf("h");
			else if(dimension2D[i][j] == 6) //Treasure Tile
				printf("T");
			else if(dimension2D[i][j] == 7) //Exit Tile
				printf("E");
			else if(dimension2D[i][j] == 8) //Bats Tile
				printf("b");
			else if(dimension2D[i][j] == 9) //Yohane
				printf("Y");
		}
		printf("\n");
	}
}

void wall(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 2){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void freedom(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 7){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void yohane(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 9){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

int tileValidation(grid dimension2D, int nRow, int nCol, int cRow, int cCol, int nDir){
	int valid = 0;

	if(nDir == 1){
		cRow--;
		if(cRow >= 0 && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}else if(nDir == 2){
		cCol--;
		if(cCol >= 0 && dimension2D[cRow][cCol] != 0)
			valid = 1;	
	}else if(nDir == 3){
		cRow++;
		if(cRow < nRow && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}else if(nDir == 4){
		cCol++;
		if(cCol < nCol && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}

	return valid;
}

//Base Logic Package (e.g., character moving, tile finding and validation, winning, quitting)
void yohaneBaseLogic(grid dimension2D)
{
	int row = MAX_ROW;
	int col = MAX_COL;
	int quit = 0, win = 0;
	int wRow, wCol, eRow, eCol, yRow, yCol;
	char move;

	wall(dimension2D,row,col,&wRow,&wCol);
	freedom(dimension2D,row,col,&eRow,&eCol);
	yohane(dimension2D,row,col,&yRow,&yCol);
	do{
		system("cls");
		// if(pRow != -1 && pCol != -1)
		// 	printf("Yohane found at R%dC%d!\n", pRow, pCol);
		// else
		// 	printf("Error 404: Yohane is missing, game over!");
		dungeonIdentifier(dimension2D,row,col);
		printf("\n Game Controls \n");
		printf("[W] Up | [A] Left | [S] Down | [D] Right | [X] Freeze | [Q] Save and Quit \n");
		move = getch();

		switch(move){
			case 'W': case 'w':
				if(tileValidation(dimension2D,row,col,yRow,yCol,1)){
					// Dig a wall
					if(dimension2D[yRow-1][yCol] == 2)
						dimension2D[yRow-1][yCol] = 1;
					
					//Check next tile if passable
					if(dimension2D[yRow-1][yCol] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow-1][yCol] = 9;
						yRow--;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
				}
				break;
			case 'A': case 'a':
				if(tileValidation(dimension2D,row,col,yRow,yCol,2)){
					// Dig a wall
					if(dimension2D[yRow][yCol-1] == 2)
						dimension2D[yRow][yCol-1] = 1;

					//Check next tile if passable
					if(dimension2D[yRow][yCol-1] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow][yCol-1] = 9;
						yCol--;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
				}
				break;
			case 'S': case 's':
				if(tileValidation(dimension2D,row,col,yRow,yCol,3)){
					// Dig a wall
					if(dimension2D[yRow+1][yCol] == 2)
						dimension2D[yRow+1][yCol] = 1;

					//Check next tile if passable
					if(dimension2D[yRow+1][yCol] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow+1][yCol] = 9;
						yRow++;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
				}
			case 'D': case 'd':
				if(tileValidation(dimension2D,row,col,yRow,yCol,4)){
					// Dig a wall
					if(dimension2D[yRow][yCol+1] == 2)
						dimension2D[yRow][yCol+1] = 1;

					// Check next tile if passable
					if(dimension2D[yRow][yCol+1] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow][yCol+1] = 9;
						yCol++;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
				}
				break;
			case 'X': case 'x':
				dimension2D[yRow][yCol] = 9;
				break;
			case 'Q': case 'q':
				quit = 1;
				break;
		}
		
		// if(move == 'W' || move == 'w'){
		// 	if(tileValidation(dimension2D,row,col,yRow,yCol,1)){
		// 		// Dig a wall
		// 		if(dimension2D[yRow-1][yCol] == 2)
		// 			dimension2D[yRow-1][yCol] = 1;
					
		// 		//Check next tile if passable
		// 		if(dimension2D[yRow][yCol+1] == 1){
		// 			dimension2D[yRow][yCol] = 1;
		// 			dimension2D[yRow][yCol+1] = 9;
		// 			yRow--;
		// 		}else //Yohane stays at the same tile if impassable
		// 			dimension2D[yRow][yCol] = 9;
		// 	}
		// }else if (move == 'A' || move == 'a'){
		// 	if(tileValidation(dimension2D,row,col,yRow,yCol,2)){
		// 		// Dig a wall
		// 		if(dimension2D[yRow][yCol-1] == 2)
		// 			dimension2D[yRow][yCol-1] = 1;

		// 		//Check next tile if passable
		// 		if(dimension2D[yRow][yCol+1] == 1){
		// 			dimension2D[yRow][yCol] = 1;
		// 			dimension2D[yRow][yCol+1] = 9;
		// 			yCol--;
		// 		}else //Yohane stays at the same tile if impassable
		// 			dimension2D[yRow][yCol] = 9;
		// 	}
		// }else if (move == 'S' || move == 's'){
		// 	if(tileValidation(dimension2D,row,col,yRow,yCol,3)){
		// 		// Dig a wall
		// 		if(dimension2D[yRow+1][yCol] == 2)
		// 			dimension2D[yRow+1][yCol] = 1;

		// 		//Check next tile if passable
		// 		if(dimension2D[yRow+1][yCol] == 1){
		// 			dimension2D[yRow][yCol] = 1;
		// 			dimension2D[yRow+1][yCol] = 9;
		// 			yRow++;
		// 		}else //Yohane stays at the same tile if impassable
		// 			dimension2D[yRow][yCol] = 9;
		// 	}
		// }else if (move == 'D' || move == 'd'){
		// 	if(tileValidation(dimension2D,row,col,yRow,yCol,4)){
		// 		// Dig a wall
		// 		if(dimension2D[yRow][yCol+1] == 2)
		// 			dimension2D[yRow][yCol+1] = 1;

		// 		// Check next tile if passable
		// 		if(dimension2D[yRow][yCol+1] == 1){
		// 			dimension2D[yRow][yCol] = 1;
		// 			dimension2D[yRow][yCol+1] = 9;
		// 			yCol++;
		// 		}else //Yohane stays at the same tile if impassable
		// 			dimension2D[yRow][yCol] = 9;
		// 	}
		// }else if (move == 'X' || move == 'x'){
		// 	dimension2D[yRow][yCol] = 9;
		// }else if (move == 'Q' || move == 'q')
		// 	quit = 1;

		if(yRow == eRow && yCol == eCol)
			win = 1;
	}while(!quit && !win);
	
	printf("\n");
	if(win)
		printf("You have found the door to the exit. おめでとうございます!!!");
}

// Dungeon Level One: Awashima Marine Park
void awashimaMarinePark(){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	yohaneBaseLogic(dungeon);
}

// Dungeon Level Two: Izu-mito Sea Paradise
void izumitoSeaParadise(){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	yohaneBaseLogic(dungeon);
}

// Dungeon Level Three: Shougetsu Confectionary
void shougetsuConfectionary(){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	yohaneBaseLogic(dungeon);
}

// Dungeon Level Boss: Siren in the Mirror World! Later for Lailaps
void sirenOfTheMirrorWorld(){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
					{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	printf("Final Battle: Siren of the Mirror World!");
	yohaneBaseLogic(dungeon);
}