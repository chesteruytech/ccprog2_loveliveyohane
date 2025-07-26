#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MAX_IDOLS 8
#define MAX_NAME_LEN 30
#define MAX_HOSTAGES 3
#define MAX_ITEM_CHAR 50
#define MAX_INVENTORY 9
#define MAX_HANAMARU 9
#define MAX_ACHIEVEMENTS 28
#define MAX_DESCRIPTION 200
// IDOLS TO HANAMARU SHOP INDEX RATIO. DO NOT TOUCH!!!
#define SHOVEL_UP 2
#define BAT_TAMER 3
#define AIR_SHOES 4
#define STEWSHINE 5
#define MIKAN_MOCHI 6
#define KURO_MACHA 7 
#define ICE_CREAM 8

#define MAX_ROW 12
#define MAX_COL 55
#define SIREN_ROW 100
#define SIREN_COL 100

typedef int grid[MAX_ROW][MAX_COL]; //Global declaration for the grid

typedef char Name[MAX_NAME_LEN];
typedef char Description[MAX_DESCRIPTION];

struct idolDungeonTag{
    Name idol;
    Name dungeon;
};

struct inventoryTag{
	Name item;
	int itemCount;
	int hidden;
};

struct hanamaruTag{
	Name item;
	int price;
	int availability;
};

struct gameTag{
	int maxHP;
	float hp;
	int gold;
	int hostages[MAX_HOSTAGES];
	int rescuedCount[MAX_IDOLS];
	int clearStatus[MAX_IDOLS];
	int clearStatusTemp[MAX_HOSTAGES];
	int running;
	int dungeonClears;
	int goldSpent;
	float dmgTaken; 
	int currentPlaythroughClear;
	Name killed; // killed by
	int handIndex[3];
	int currentHandIndex; 
	int chocoMintUsageCount; // for that one ahievement
	int totalPlaythroughClear; // for ng+
	int flawless; // for step 0 to 1 achievement
	int newGamePlus;
	int hostagesSelected;
	int newGamePlusStatus;
	float lailapsHP;
	int maxLailapsHP; 
	int floorCount;
	int currentFloorIndex;
};

struct achievementTag{
	Name achievement;
	int earned;
	Description description;
	char dateEarned[20];
};

void initializeGame(struct gameTag *game);
void initializeIdolDungeon(struct idolDungeonTag idolDungeon[]);
void initializeInventory(struct inventoryTag inventory[]);
void initializeHanamaru(struct hanamaruTag hanamaru[]);
void initializeAchievements(struct achievementTag achievement[]);
void viewAchievementsCount(struct achievementTag achievement[], int achievementCount);
int isNumber(char choice[]);
int strToInt(char choice[]);
void intToStr(int num, char* str, int digits);
void getCurrentDate(char *output);
void achievementUnlock(struct achievementTag achievement[], struct gameTag *game, int win);
void viewAchievementDetails(char choice[], struct achievementTag achievement[], int achievementCount);
void viewAchievements(struct achievementTag achievement[]);
void selectHostages(struct gameTag *game);
void showHostages(struct idolDungeonTag idolDungeon[], struct gameTag *game);
void showDungeonMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]);
void showInventory(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]);

void hanamaruStore(struct idolDungeonTag idolDungeon[], struct gameTag *game, 
				struct inventoryTag inventory[], struct hanamaruTag hanamaru[], struct achievementTag achievement[]);
				
void itemUnlock(int charIdx, struct hanamaruTag hanamaru[]);

void saveGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
		struct hanamaruTag hanamaru[], struct achievementTag achievement[]);
		
void loadGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);
			
void dungeonIdentifier(grid dimension2D, int nRow, int nCol);
void wall(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void spike(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void water(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void heat(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void treasure(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void freedom(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void bats(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void batAbilities(grid dimension2D, int playerMove, struct gameTag *health, struct inventoryTag inventory[]);
void yohane(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void gold(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void hit(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void siren(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
void lailaps(grid dimension2D, int nRow, int nCol, int *tRow, int *tCol);
int tileValidation(grid dimension2D, int nRow, int nCol, int cRow, int cCol, int nDir);
void obtainTreasure(struct inventoryTag inventory[], struct gameTag game[]);
void obtainGoldBat(struct gameTag *game);
void movement(grid dimension2D, struct gameTag *game, struct inventoryTag inventory[], 
				int *yRow, int *yCol, int targetRow, int targetCol, int *verdict, int *currentTile);
void cycleItemForward(struct inventoryTag inventory[], struct gameTag *game);
void cycleItemBackward(struct inventoryTag inventory[], struct gameTag *game);
void useItem(struct inventoryTag inventory[], struct gameTag *game);
void gameOver(struct gameTag *game, struct inventoryTag inventory[]);

int yohaneBaseLogic(grid dimension2D, struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]);
					
int awashimaMarinePark(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]);
					
int izumitoSeaParadise(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]);
					
int shougetsuConfectionary(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]);
					
int sirenOfTheMirrorWorld(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]);
					
void gameMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);

void newGamePlusSetup(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);

void continueGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);

void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);

void newGamePlus(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);

void titleScreen(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]);
			
