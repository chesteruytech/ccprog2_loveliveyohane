/* 
	Please use #include "dungeon.c" in the main part of the Machine Project. 

	This Machine Project is made by:
	1. Jon Regan Choa | prog2mp.c
	2. Chester Aldrin G. Uy | dungeon.c

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

typedef int grid[MAX_ROW][MAX_COL]; //Global declaration for the grid

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
			else if(dimension2D[i][j] == 4){ //Water Tiles
				printf("\e[0;34m"); //Blue color
				printf("w");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 5){ //Heat Tile
				printf("\e[0;3214m"); //Orange color
				printf("h");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 6){ //Treasure Tile
				printf("\e[0;33m"); //Yellow color
				printf("T");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 7){ //Exit Tile
				printf("\e[0;33m"); //Yellow color
				printf("E");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 8){ //Bats Tile
				printf("\e[0;31m"); //Red color
				printf("b");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 9){ //Yohane
				printf("\e[1;34m"); //Bold blue color
				printf("Y");
				printf("\e[0m"); //Resets the color to default
			}
				
			// Additional identifiers not specified in specs
			else if(dimension2D[i][j] == 10){ //Gold Tile
				printf("\e[0;33m"); //Yellow color
				printf("g");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 11){ //Got attacked bat Tile
				printf("\e[0;31m"); //Red color
				printf("B");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 12){ //Siren tile
				printf("\e[0;31m"); //Red color
				printf("S");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 13){ //Lailaps
				printf("\e[0;38m"); //Grey color
				printf("S");
				printf("\e[0m"); //Resets the color to default
			}
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

void spike(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 3){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void water(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 4){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void heat(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 5){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void treasure(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 6){
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

void bats(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 8){
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

void gold(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 10){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void hit(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 11){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void siren(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 12){
				*tRow = i;
				*tCol = j;
			}
		}
	}
}

void lailaps(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol){
	*tRow = -1;
	*tCol = -1;

	for(int i = 0; i < nRow; i++){
		for(int j = 0; j < nCol; j++){
			if(dimension2D[i][j] == 13){
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
int yohaneBaseLogic(grid dimension2D)
{
	int row = MAX_ROW;
	int col = MAX_COL;
	int quit = 0, verdict = 0;
	int wlRow, wlCol, spikeRow, spikeCol, wtRow, wtCol, heatRow, heatCol, tRow, tCol, eRow, eCol, bRow, bCol, yRow, yCol, gRow, gCol, hitRow, hitCol, sirenRow, sirenCol, lRow, lCol;
	char move;

	// Tile location/s
	wall(dimension2D,row,col,&wlRow,&wlCol);
	spike(dimension2D,row,col,&spikeRow,&spikeCol);
	water(dimension2D,row,col,&wtRow,&wtCol);
	heat(dimension2D,row,col,&heatRow,&heatCol);
	treasure(dimension2D,row,col,&tRow,&tCol);
	freedom(dimension2D,row,col,&eRow,&eCol);
	bats(dimension2D,row,col,&bRow,&bCol);
	yohane(dimension2D,row,col,&yRow,&yCol);
	gold(dimension2D,row,col,&gRow,&gCol);
	hit(dimension2D,row,col,&hitRow,&hitCol);
	siren(dimension2D,row,col,&sirenRow,&sirenCol);
	lailaps(dimension2D,row,col,&lRow,&lCol);

	do{
		system("cls");
		dungeonIdentifier(dimension2D,row,col);
		printf("\n Game Controls \n"); //  | ゲームコントロール
		printf("[W] Up | [A] Left | [S] Down | [D] Right | [X] Freeze \n");
		// printf("[W] 上 | [A] 左 | [S] 下 | [D] 右 | [X] フリーズ \n");		
		move = getch();

		switch(move){
			case 'W': case 'w':
				if(tileValidation(dimension2D,row,col,yRow,yCol,1)){
					//Check next tile if passable
					if(dimension2D[yRow-1][yCol] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow-1][yCol] = 9;
						yRow--;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;

					// Tile identification
					if(dimension2D[yRow-1][yCol] == 2) //Wall digging
						dimension2D[yRow-1][yCol] = 1;
					else if(dimension2D[yRow-1][yCol] == 8){ //Yohane attacks bat
						dimension2D[yRow-1][yCol] = 10;
						if(dimension2D[yRow-1][yCol] == 10){
							dimension2D[yRow][yCol] = 1;
							dimension2D[yRow-1][yCol] = 9; //Yohane obtains gold
							yRow--;
						}
					}
				}
			case 'A': case 'a':
				if(tileValidation(dimension2D,row,col,yRow,yCol,2)){
					//Check next tile if passable
					if(dimension2D[yRow][yCol-1] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow][yCol-1] = 9;
						yCol--;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
						
					// Tile identification
					if(dimension2D[yRow][yCol-1] == 2) //Wall digging
						dimension2D[yRow][yCol-1] = 1;
					else if(dimension2D[yRow][yCol-1] == 8){ //Yohane attacks bat
						dimension2D[yRow][yCol-1] = 10; //Gold spotted!
						if(dimension2D[yRow][yCol-1] == 10){
							dimension2D[yRow][yCol] = 1;
							dimension2D[yRow][yCol-1] = 9;  //Yohane obtains gold
							yCol--;
						}
					}
				}
				break;
			case 'S': case 's':
				if(tileValidation(dimension2D,row,col,yRow,yCol,3)){
					//Check next tile if passable
					if(dimension2D[yRow+1][yCol] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow+1][yCol] = 9;
						yRow++;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
					
					// Tile identification
					if(dimension2D[yRow+1][yCol] == 2) //Wall digging
						dimension2D[yRow+1][yCol] = 1;
					else if(dimension2D[yRow+1][yCol] == 8){ //Yohane attacks bat
						dimension2D[yRow+1][yCol] = 10; //Gold spotted!
						if(dimension2D[yRow+1][yCol] == 10){
							dimension2D[yRow][yCol] = 1;
							dimension2D[yRow+1][yCol] = 9;  //Yohane obtains gold
							yRow++;
						}
					}
				}
				break;
			case 'D': case 'd':
				if(tileValidation(dimension2D,row,col,yRow,yCol,4)){
					// Check next tile if passable
					if(dimension2D[yRow][yCol+1] == 1){
						dimension2D[yRow][yCol] = 1;
						dimension2D[yRow][yCol+1] = 9;
						yCol++;
					}else //Yohane stays at the same tile if impassable
						dimension2D[yRow][yCol] = 9;
						
					// Tile identification
					if(dimension2D[yRow][yCol+1] == 2) //Wall digging
						dimension2D[yRow][yCol+1] = 1; 
					else if(dimension2D[yRow][yCol+1] == 8){ //Yohane attacks bat
						dimension2D[yRow][yCol+1] = 10; //Gold spotted!
						if(dimension2D[yRow][yCol+1] == 10){
							dimension2D[yRow][yCol] = 1;
							dimension2D[yRow][yCol+1] = 9;  //Yohane obtains gold
							yCol++;
						}
					}
				}
				break;
			case 'X': case 'x':
				dimension2D[yRow][yCol] = 9;
				break;
			default:
				printf("Error 7611111810176105118101: Your choice is invalid. Please try again.");
				// printf("エラー 7611111810176105118101: 無効な選択肢です。もう一度やり直してください。");
		}

		if(yRow == eRow && yCol == eCol)
			if(dimension2D[yRow-1][yCol] == 7 || dimension2D[yRow][yRow-1] == 7 || dimension2D[yRow+1][yCol] == 7 || dimension2D[yRow][yCol+1] == 7)
				verdict = 1;
	}while(!quit && !verdict);
	
	printf("\n");
	if(verdict){
		printf("You have found the door to the exit. Congratulations!!!");
		// printf("あなたは出口への扉を見つけた。おめでとうございます!!!");
	}

	return verdict;
}

// Dungeon Level One: Awashima Marine Park 1/2/3/4/5/7/8/9
void awashimaMarinePark(){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,2,2,1,2,2,1,1,1,1,1,1,2,1,1,2,2,7,0}, 
				 	{0,1,2,2,1,2,2,1,1,1,8,1,1,2,1,1,2,2,2,0}, 
				 	{0,1,5,1,2,1,2,1,1,1,1,1,1,2,1,1,2,2,2,0}, 
				 	{0,1,5,1,2,1,2,1,1,1,1,1,1,2,1,1,1,1,1,0},
				 	{0,1,2,2,1,2,2,1,1,9,1,1,1,4,1,1,1,8,1,0}, 
				 	{0,1,2,2,1,2,2,2,1,1,1,1,1,4,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,2,1,1,1,1,3,3,3,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,2,5,5,5,1,3,8,3,1,1,1,1,0}, 
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
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,7,0}, 
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
				 	{0,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,7,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
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

	printf("Final Battle: Siren of the Mirror World!\n");
	// printf("最終決戦: 鏡の世界のセイレーン!\n");
	yohaneBaseLogic(dungeon);
}