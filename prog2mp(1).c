/* 
mp is 95% complete

to do by priority: 
- final boss 
- test cases

Complete:
- Main menu
- achievements
- dungeon menu
- hostage selection
- inventory
- hanamaru shop
- save file
- load file
- game over
- use and cycle items
- new game + 
- player movements
- bat movements
- dungeon floors
*/

/*
Description: Yohane the Parhelion! Siren in the Mirror World Machine Project CCPROG2
Programmed by: Jon Regan Choa, Chester Aldrin Uy, S14
Last modified: July 29, 2025
Version: v10.0
[Acknowledgements: time.h, conio.h, an older CCPROG2 machine project that was done by Regan]
*/
#include "prog2mp.h"

/* This function initalizes the game structure
Precondition: Program is running
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void initializeGame(struct gameTag *game){
	
	int i;
	game->hp = 3;
    game->maxHP = 3;
    game->gold = 0;  
	game->running = 1;
	game->dungeonClears = 0;
	game->goldSpent = 0;
	game->dmgTaken = 0;
	game->currentPlaythroughClear = 0;
	
	for (i = 0; i < MAX_IDOLS; i++) {
    	game->clearStatus[i] = 0;
	}
	
	for (i = 0; i < MAX_HOSTAGES; i++) {
    	game->clearStatusTemp[i] = 0;
	}
	
	for (i = 0; i < MAX_IDOLS; i++){
		game->rescuedCount[i] = 0;
	}
	
	game->handIndex[0] = 0; // Noppo 
	game->handIndex[1] = 1; // Tears
	game->handIndex[2] = 8; // Icecream
	game->currentHandIndex = -1; // N/A
	
	game->chocoMintUsageCount = 0;
	game->totalPlaythroughClear = 0;
	game->flawless = 0;
	game->newGamePlus = 0;
	game->hostagesSelected = 0;
	game->lailapsHP = 4;
	game->maxLailapsHP = 4;
	game->floorCount = 1;
	game->currentFloorIndex = 0;
}

/* This function initalizes the idol and dungeon pair structure
Precondition: Program is running
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
*/
void initializeIdolDungeon(struct idolDungeonTag idolDungeon[]){
	
    strcpy(idolDungeon[0].idol, "Chika");
    strcpy(idolDungeon[0].dungeon, "Yasudaya Ryokan");

    strcpy(idolDungeon[1].idol, "Riko");
    strcpy(idolDungeon[1].dungeon, "Numazu Deep Sea Aquarium");

    strcpy(idolDungeon[2].idol, "You");
    strcpy(idolDungeon[2].dungeon, "Izu-Mito Sea Paradise");

    strcpy(idolDungeon[3].idol, "Hanamaru");
    strcpy(idolDungeon[3].dungeon, "Shougetsu Confectionary");

    strcpy(idolDungeon[4].idol, "Ruby");
    strcpy(idolDungeon[4].dungeon, "Nagahama Castle Ruins");

    strcpy(idolDungeon[5].idol, "Dia");
    strcpy(idolDungeon[5].dungeon, "Numazugoyotei");

    strcpy(idolDungeon[6].idol, "Kanan");
    strcpy(idolDungeon[6].dungeon, "Uchiura Bay Pier");

    strcpy(idolDungeon[7].idol, "Mari");
    strcpy(idolDungeon[7].dungeon, "Awashima Marine Park");
    
}

/* This function initalizes the player's inventory
Precondition: Program is running
@param struct inventoryTag inventory[]: the structure containing the player's inventory
*/
void initializeInventory(struct inventoryTag inventory[]){
	
	strcpy(inventory[0].item, "Tears of a fallen angel");
	inventory[0].itemCount = 0;
	inventory[0].hidden = 0;
	
	strcpy(inventory[1].item, "Noppo Bread");
	inventory[1].itemCount = 0;
	inventory[1].hidden = 0;
	
	strcpy(inventory[2].item, "Shovel Upgrade");
	inventory[2].itemCount = 0;
	inventory[2].hidden = 1;
	
	strcpy(inventory[3].item, "Bat Tamer");
	inventory[3].itemCount = 0;
	inventory[3].hidden = 1;
	
	strcpy(inventory[4].item, "Air Shoes");
	inventory[4].itemCount = 0;
	inventory[4].hidden = 1;
	
	strcpy(inventory[5].item, "Stewshine");
	inventory[5].itemCount = 0;
	inventory[5].hidden = 1;
	
	strcpy(inventory[6].item, "Mikan Mochi");
	inventory[6].itemCount = 0;
	inventory[6].hidden = 1;
	
	strcpy(inventory[7].item, "Kurosawa Macha");
	inventory[7].itemCount = 0;
	inventory[7].hidden = 1;
	
	strcpy(inventory[8].item, "Choco-Mint Ice Cream");
	inventory[8].itemCount = 0;
	inventory[8].hidden = 0;
	
}

/* This function initalizes the hanamaru shop
Precondition: Program is running
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
*/
void initializeHanamaru(struct hanamaruTag hanamaru[]){
	
	strcpy(hanamaru[0].item, "Tears of a fallen angel");
	hanamaru[0].price = 30;
	hanamaru[0].availability = 1;
	
	strcpy(hanamaru[1].item, "Noppo Bread");
	hanamaru[1].price = 100;
	hanamaru[1].availability = 33550336;
	
	strcpy(hanamaru[2].item, "Shovel Upgrade");
	hanamaru[2].price = 300;
	hanamaru[2].availability = 0;
	
	strcpy(hanamaru[3].item, "Bat Tamer");
	hanamaru[3].price = 400;
	hanamaru[3].availability = 0;
	
	strcpy(hanamaru[4].item, "Air Shoes");
	hanamaru[4].price = 500;
	hanamaru[4].availability = 0;
	
	strcpy(hanamaru[5].item, "Stewshine");
	hanamaru[5].price = 1000;
	hanamaru[5].availability = 0;
	
	strcpy(hanamaru[6].item, "Mikan Mochi");
	hanamaru[6].price = 1000;
	hanamaru[6].availability = 0;
	
	strcpy(hanamaru[7].item, "Kurosawa Macha");
	hanamaru[7].price = 1000;
	hanamaru[7].availability = 0;
	
	strcpy(hanamaru[8].item, "Choco-Mint Ice Cream");
	hanamaru[8].price = 2000;
	hanamaru[8].availability = 0;
	
}

/* This function initalizes the game's achievements
Precondition: Program is running
@param struct achievementTag achievement[]: the structure containing the contents of the achievements
*/
void initializeAchievements(struct achievementTag achievement[]){
	
	strcpy(achievement[0].achievement, "Yohane Descends!");
	achievement[0].earned = 0;
	strcpy(achievement[0].description, "Cleared first dungeon");
	
	strcpy(achievement[1].achievement, "Mikan Power!");
	achievement[1].earned = 0;
	strcpy(achievement[1].description, "Rescued Chika for the first time");
	
	strcpy(achievement[2].achievement, "Riko-chan BEAM!");
	achievement[2].earned = 0;
	strcpy(achievement[2].description, "Rescued Riko for the first time");
	
	strcpy(achievement[3].achievement, "Yousoro!");
	achievement[3].earned = 0;
	strcpy(achievement[3].description, "Rescued You for the first time");
	
	strcpy(achievement[4].achievement, "It's the future, zura!");
	achievement[4].earned = 0;
	strcpy(achievement[4].description, "Rescued Hanamaru for the first time");
	
	strcpy(achievement[5].achievement, "Ganbaruby!");
	achievement[5].earned = 0;
	strcpy(achievement[5].description, "Rescued Ruby for the first time");
	
	strcpy(achievement[6].achievement, "Buu-buu desu wa!");
	achievement[6].earned = 0;
	strcpy(achievement[6].description, "Rescued Dia for the first time");
	
	strcpy(achievement[7].achievement, "Hug!!!");
	achievement[7].earned = 0;
	strcpy(achievement[7].description, "Rescued Kanan for the first time");
	
	strcpy(achievement[8].achievement, "Shiny!");
	achievement[8].earned = 0;
	strcpy(achievement[8].description, "Rescued Mari for the first time");
	
	strcpy(achievement[9].achievement, "In This Unstable World!");
	achievement[9].earned = 0;
	strcpy(achievement[9].description, "Beat the Final boss for the first time");
	
	strcpy(achievement[10].achievement, "One more sunshine story!");
	achievement[10].earned = 0;
	strcpy(achievement[10].description, "Rescued Chika twice");
	
	strcpy(achievement[11].achievement, "Pianoforte Monologue!");
	achievement[11].earned = 0;
	strcpy(achievement[11].description, "Rescued Riko twice");
	
	strcpy(achievement[12].achievement, "Beginner's Sailing!");
	achievement[12].earned = 0;
	strcpy(achievement[12].description, "Rescued You twice");
	
	strcpy(achievement[13].achievement, "Oyasuminasan!");
	achievement[13].earned = 0;
	strcpy(achievement[13].description, "Rescued Hanamaru twice");
	
	strcpy(achievement[14].achievement, "Red Gem Wink!");
	achievement[14].earned = 0;
	strcpy(achievement[14].description, "Rescued Ruby twice");
	
	strcpy(achievement[15].achievement, "White First Love!");
	achievement[15].earned = 0;
	strcpy(achievement[15].description, "Rescued Dia twice");
	
	strcpy(achievement[16].achievement, "Sakana ka Nandaka!");
	achievement[16].earned = 0;
	strcpy(achievement[16].description, "Rescued Kanan twice");
	
	strcpy(achievement[17].achievement, "New Winding Road!");
	achievement[17].earned = 0;
	strcpy(achievement[17].description, "Rescued Mari twice");
	
	strcpy(achievement[18].achievement, "Deep Resonance!");
	achievement[18].earned = 0;
	strcpy(achievement[18].description, "Beat the Final boss twice");
	
	strcpy(achievement[19].achievement, "No. 10!");
	achievement[19].earned = 0;
	strcpy(achievement[19].description, "Clear 10 dungeons");
	
	strcpy(achievement[20].achievement, "CYaRon!");
	achievement[20].earned = 0;
	strcpy(achievement[20].description, "Rescued Chika, You, and Ruby (Not necessarily in one playthrough)");
	
	strcpy(achievement[21].achievement, "AZALEA!");
	achievement[21].earned = 0;
	strcpy(achievement[21].description, "Rescued Hanamaru, Dia, and Kanan (Not necessarily in one playthrough)");
	
	strcpy(achievement[22].achievement, "Guilty Kiss!");
	achievement[22].earned = 0;
	strcpy(achievement[22].description, "Rescued Riko and Mari (Not necessarily in one playthrough)");
	
	strcpy(achievement[23].achievement, "Eikyuu Hours!");
	achievement[23].earned = 0;
	strcpy(achievement[23].description, "Have Yohane rescue all Aqours members for the first time");
	
	strcpy(achievement[24].achievement, "Aozora Jumping Heart!");
	achievement[24].earned = 0;
	strcpy(achievement[24].description, "Clear a dungeon without incurring any damage");
	
	strcpy(achievement[25].achievement, "Mitaiken Horizon!");
	achievement[25].earned = 0;
	strcpy(achievement[25].description, "Accumulate a total of 5000G spent on Hanamaru's stores across multiple playthroughs");
	
	strcpy(achievement[26].achievement, "Ruby-chan! Hai? Nani ga suki?");
	achievement[26].earned = 0;
	strcpy(achievement[26].description, "Get saved by a fatal blow from Ruby�s choco-mint ice cream item.");
	
	strcpy(achievement[27].achievement, "Step! ZERO to ONE!");
	achievement[27].earned = 0;
	strcpy(achievement[27].description, "Complete a playthrough with 0G on-hand at the end");
}

/* This function views the amount of achievments obtained
Precondition: Program is running
@param struct achievementTag achievement[]: the structure containing the achievements
@param achievementCount: the amount of achievements obtained by the player
*/
void viewAchievementsCount(struct achievementTag achievement[], int achievementCount){
	
	system("cls");
    printf("************************************************************\n");
    printf("                    Achievements module                     \n");
    printf("                      Obtained: %d / %d                     \n", achievementCount, MAX_ACHIEVEMENTS);
    printf("************************************************************\n");
}

/* This function confirms that the input of the player is an integer
Precondition: Program is running
@param char choice[]: The string containing the input of the player 
@return 1 if input is a number, 0 if no input or not an integer
*/
int isNumber(char choice[]){
    int count = 0;

    if (choice[0] == '\0')
        return 0;

    while (choice[count] != '\0') {
        if (choice[count] < '0' || choice[count] > '9')
            return 0;
		else 
        	count++;
    }

    return 1; 
}
/* This function converts the input of the player (char type) to an integer
Precondition: Program is running
@param char choice[]: The string containing the input of the player 
@return the integer that was converted by the function
*/
int strToInt(char choice[]){
    int count = 0;
    int num = 0;

    while (choice[count] != '\0') {
        num = num * 10 + (choice[count] - '0');
        count++;
    }

    return num;
}
/* This function converts an integer to a string
Referenced one of Regan's previous CCPROG2 machine project for this function
Precondition: Program is running
@param num: the time now 
@param str: the current month/day/year in the form of a string
@param digits: string length of date format
*/
void intToStr(int num, char* str, int digits) {
    int i, pos = digits - 1;

    for (i = 0; i < digits; i++)
        str[i] = '0';

    str[digits] = '\0';

    while (num > 0 && pos >= 0) {
        str[pos] = (num % 10) + '0';
        num /= 10;
        pos--;
    }
}

/* This function gets the current date basd on function named intToStr.
Referenced one of Regan's previous CCPROG2 machine project for this function
Precondition: Get an achievement in game
@param output: the string containing the current date and time
*/
void getCurrentDate(char *output){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char mm[3], dd[3], yyyy[5], hh[3], min[3];

    intToStr(t->tm_mon + 1, mm, 2); // month
    intToStr(t->tm_mday, dd, 2); // day
    intToStr(t->tm_year + 1900, yyyy, 4); // year
    intToStr(t->tm_hour, hh, 2); // hour
    intToStr(t->tm_min, min, 2); // minutes

 
    output[0] = '\0'; 

    strcat(output, mm);
    strcat(output, "-");
    strcat(output, dd);
    strcat(output, "-");
    strcat(output, yyyy);
    strcat(output, " ");
    strcat(output, hh);
    strcat(output, ":");
    strcat(output, min);
}
/* This function checks whether an achievements should be unlocked based on certain in game conditions
Precondition: Get an achievement in game
@param struct achievementTag achievement[]: the structure containing the achievments in game
@param struct gameTag *game: the structure containing the in game player's statistics
@param win: confirms whether a dungeon was cleared, 1 if yes, 0 if no
*/
void achievementUnlock(struct achievementTag achievement[], struct gameTag *game, int win){
				 
		int i;
		int rescueCounter = 0;
		
		// rescue counter for achievement index 23 (24) this has to meet 8
		for (i = 0; i < MAX_IDOLS; i++){
			if (game->rescuedCount[i] > 0)
				rescueCounter++;
		}
		
		// achievement conditions (index 0)
		if (game->dungeonClears > 0 && achievement[0].earned == 0){
			achievement[0].earned = 1;
			getCurrentDate(achievement[0].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[0].achievement);
			system("pause");
		}
		
		// achievement rescue for first time, index 1 to 8 
		for (i = 0; i < MAX_IDOLS; i++) 
			if (game->rescuedCount[i] > 0 && achievement[i+1].earned == 0){
			achievement[i+1].earned = 1;
			getCurrentDate(achievement[i+1].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[i+1].achievement);	
			system("pause");
		}
		
		// beat final boss once (index 9)
		if (game->totalPlaythroughClear == 1 && achievement[9].earned == 0){		
			achievement[9].earned = 1;
			getCurrentDate(achievement[9].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[9].achievement);
			system("pause");
		}
		
		// achievement rescue twice, index 10 to 17 
		for (i = 0; i < MAX_IDOLS; i++) 
			if (game->rescuedCount[i] > 1 && achievement[i+10].earned == 0){
			achievement[i+10].earned = 1;
			getCurrentDate(achievement[i+10].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[i+10].achievement);
			system("pause");	
		}
		
		// beat final boss twice (index 18)
		if (game->totalPlaythroughClear == 2 && achievement[18].earned == 0){		
			achievement[18].earned = 1;
			getCurrentDate(achievement[18].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[18].achievement);
			system("pause");
		}
		
		// clear 10 dungeons (index 19)
		if ((game->dungeonClears + game->totalPlaythroughClear) >= 10 && achievement[19].earned == 0){
			achievement[19].earned = 1;
			getCurrentDate(achievement[19].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[19].achievement);
			system("pause");
		}
		
		// rescue chika, you, ruby (index 20)
		if (game->rescuedCount[0] > 0 && game->rescuedCount[2] > 0 && game->rescuedCount[4] > 0 && achievement[20].earned == 0){
			achievement[20].earned = 1;
			getCurrentDate(achievement[20].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[20].achievement);
			system("pause");
		}
		
		// rescue hanamaru, dia, kanan (index 21)
		if (game->rescuedCount[3] > 0 && game->rescuedCount[5] > 0 && game->rescuedCount[6] > 0 && achievement[21].earned == 0){
			achievement[21].earned = 1;
			getCurrentDate(achievement[21].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[21].achievement);
			system("pause");
		}
		
		// rescue riko, mari (index 22)
		if (game->rescuedCount[1] > 0 && game->rescuedCount[7] > 0 && achievement[22].earned == 0){
			achievement[22].earned = 1;
			getCurrentDate(achievement[22].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[22].achievement);
			system("pause");
		}
		
		// Have Yohane rescue all Aqours members for the first time (index 23)
		if (rescueCounter == 8 && achievement[23].earned == 0){
			achievement[23].earned = 1;
			getCurrentDate(achievement[23].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[23].achievement);
			system("pause");
		}
		
		// no damage taken (index 24)
		if (game->dmgTaken == 0 && achievement[24].earned == 0 && win == 1){
			achievement[24].earned = 1;
			getCurrentDate(achievement[24].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[24].achievement);
			system("pause");
		}
		
		// 5000g spent across all playthroughs (index 25)
		if (game->goldSpent >= 5000 && achievement[25].earned == 0){
			achievement[25].earned = 1;
			getCurrentDate(achievement[25].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[25].achievement);
			system("pause");
		}
		
		// get saved by ruby ice cream
		if (game->chocoMintUsageCount == 1 && achievement[26].earned == 0){
			achievement[26].earned = 1;
			getCurrentDate(achievement[26].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[26].achievement);
			system("pause");
		}
		
		// finish game with no gold on-hand (index 27)
		if (game->gold == 0 && achievement[27].earned == 0 && game->flawless == 1){
			achievement[27].earned = 1;
			getCurrentDate(achievement[27].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[27].achievement);
			system("pause");
		}
		
		
}
/* This function allows the player to view achievement details for each achievement in the achievements menu
Precondition: Open the achievements menu in game
@param choice[]: the input of the player in the form of a string
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
@param achievementCount: the amount of achievements obtained in game
*/
void viewAchievementDetails(char choice[], struct achievementTag achievement[], int achievementCount){
	int index;

	do{
		index = strToInt(choice) - 1;
		system("cls");
		viewAchievementsCount(achievement, achievementCount);

		if (index >= 0 && index < 28 && isNumber(choice) == 1){
			printf("Achievement Name: %s\n", achievement[index].achievement);
			printf("\n");
			printf("Status: ");
	
			if (achievement[index].earned == 1){
				printf("EARNED!\n\n");
				printf("Date Earned: %s\n\n", achievement[index].dateEarned);
			}
			else{
				printf("NOT EARNED!\n\n");			
				printf("Description: \n");
				printf("%s\n\n", achievement[index].description);
			}
		}

		else
			printf("Invalid choice!\n\n");
							
		printf("[R]eturn to Achievements Module\n\n");
		printf("Choice: ");
		scanf("%s", choice);		
	} while (!(choice[0] == 'R' || choice[0] == 'r') && choice[1] == '\0');
	
	choice[0] = '\0';
}
/* This function allows the player to view list of achievements with a navigatable menu
Precondition: Open the achievements menu in game
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void viewAchievements(struct achievementTag achievement[]){
    int currentPage = 0;
    int totalPages = 4;
	int achievementCount = 0; 
	int achievementsPerPage = 8;
    char choice[10];
    int i, startIdx, endIdx;
	
    for (i = 0; i < MAX_ACHIEVEMENTS; i++)
        if (achievement[i].earned == 1)
            achievementCount++;

    do {
        viewAchievementsCount(achievement, achievementCount);

        startIdx = currentPage * achievementsPerPage;  
        endIdx = startIdx + achievementsPerPage;
				
        if (endIdx > MAX_ACHIEVEMENTS) 
			endIdx = MAX_ACHIEVEMENTS;

       	for (i = startIdx; i < endIdx; i++){
			printf("[%d] %-28s", i+1, achievement[i].achievement);
			printf("\t\t\t");
			
			if (achievement[i].earned == 1)
				printf("EARNED!\n");
			else
				printf("NOT EARNED!\n");
		}

        printf("\n");
        printf("Page %d of %d\n", currentPage + 1, totalPages);
    	printf("\n");
    	printf("[N]ext Page\n");
		printf("[P]revious Page\n");
		printf("[R]eturn to Main Menu\n");
		printf("\n");
		
        printf("Choice: ");
        scanf("%s", choice);
		
		if ((choice[0] == 'N' || choice[0] == 'n') && choice[1] == '\0'){
			if (currentPage < totalPages - 1)
                currentPage++;
            else{
            	printf("Maximum page reached.\n");
            	system("pause");
            }
        }
        
        else if ((choice[0] == 'P' || choice[0] == 'p') && choice[1] == '\0'){
        	if (currentPage > 0)
                currentPage--;
            else{
            	printf("Minimum page reached.\n");
            	system("pause");
            }
		}
		
		else if ((choice[0] == 'R' || choice[0] == 'r') && choice[1] == '\0'){
        	printf("Returning to Main Menu...\n");
		}
		
		else if (isNumber(choice) == 1)
			viewAchievementDetails(choice, achievement, achievementCount);
			
			
		else{
			printf("Invalid choice!\n");
			system("pause");
		}

    } while (!((choice[0] == 'R' || choice[0] == 'r') && choice[1] == '\0'));
}
/* This function selects the hostages that must be rescued by the player
Precondition: Start a playthrough in game
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void selectHostages(struct gameTag *game){
	int index;
    int used[MAX_IDOLS] = {0};
    int attempts = 0;
    int i;
    game->hostagesSelected = 0;
    
    while (game->hostagesSelected < MAX_HOSTAGES && attempts < 9999){
        index = rand() % MAX_IDOLS;
        attempts++;
        if (used[index] == 0 && game->rescuedCount[index] == 0){
            used[index] = 1;
            game->hostages[game->hostagesSelected] = index;	// randomly selected indexes go to hostage array
            game->hostagesSelected++;
        }
    }
    
    for (i = game->hostagesSelected; i < MAX_HOSTAGES; i++)  // if there are less than three hostages left
    	game->hostages[i] = -1;
}
/* This function shows the list of hostages that must be rescued by the player
Precondition: Start a playthrough in game
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void showHostages(struct idolDungeonTag idolDungeon[], struct gameTag *game){
	int i, idx;
	int rescued = 0;

	printf("Hostages: \n");
    for (i = 0; i < MAX_HOSTAGES; i++){
        idx = game->hostages[i];
        
        if (game->hostages[i] != -1)
        	printf("- %s in %s\n", idolDungeon[idx].idol, idolDungeon[idx].dungeon);
        	
    }
    
    for (i = 0; i < MAX_IDOLS; i++){
		if (game->rescuedCount[i] > 0)
			rescued++;
	}
	
	if (rescued == 8)
		printf("No more hostages!!!\n");
    
    system("pause");
    system("cls");
}
/* This function shows the in-game menu containing the dungeons that must be traversed, and player statistics
Precondition: Start a playthrough in game
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
*/
void showDungeonMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]){
	int i, idx, invIdx;
	
	if (game->currentPlaythroughClear < game->hostagesSelected)
    	printf("Lailaps: Yohane! Where should we go to now?\n\n");
    else
		printf("Lailaps: Yohane! It's time to face the Siren!\n\n");
		
    printf("HP: %.1f / %d", game->hp, game->maxHP);
    printf("\t\t\t\t");
    printf("Total Gold: %d GP\n", game->gold);
    
    if (game->currentHandIndex != -1){
	    invIdx = game->handIndex[game->currentHandIndex];
	    
		if (inventory[invIdx].itemCount > 0){
		    if (inventory[invIdx].itemCount == 1)
				printf("Item on hand: %s\n", inventory[invIdx].item);
			else
			     printf("Item on hand: %s (%d)\n", inventory[invIdx].item, inventory[invIdx].itemCount);
		}
		else
			printf("Item on hand: N/A\n");
	}else
	    printf("Item on hand: N/A\n");
		    
    printf("\n");
    
	if (game->currentPlaythroughClear < game->hostagesSelected){
		for (i = 0; i < 3; i++){
        	idx = game->hostages[i];
        	if (idx != -1){  
            	if (game->clearStatusTemp[i] == 1)
                	printf("[X] Visit %s\n", idolDungeon[idx].dungeon);
            	else
                	printf("[%d] Visit %s\n", i+1, idolDungeon[idx].dungeon);
        	}
    	}
	}else
	    printf("[1] Face the Siren of Numazu\n");
	
    printf("\n[I]nventory");
    printf("\t\t");
	printf("[S]ave and Quit");
	printf("\t\t");
	
	if (game->rescuedCount[3] > 0)
		printf("[H]anamaru Store");
		
	printf("\n\n");
}
/* This function shows the in-game inventory of the player
Precondition: Open inventory in game by pressing I
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
*/
void showInventory(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]){
	char choice;
	int i;
	int count = 1;
	printf("Lailaps: These are the items you have, Yohane!\n\n");
	printf("HP: %.1f / %d", game->hp, game->maxHP);
	printf("\t\t\t\t");
    printf("Total Gold: %d GP\n", game->gold);
	printf("Items available\n\n");
	
	for (i = 0; i < MAX_INVENTORY; i++)
		if (!inventory[i].hidden){
			printf("%d. %-30s \t x \t %d\n", count, inventory[i].item, inventory[i].itemCount);
			count++;
		}

	printf("\n");
	printf("[R]eturn\n\n");

	do{
		printf("Choice: ");
		scanf(" %c", &choice);
		
		switch(choice){
			case 'R': case 'r':
				system("cls");
		    	showDungeonMenu(idolDungeon, game, inventory);
		    	break;
		    default:
		    	printf("Invalid choice\n");
			}
	} while (choice != 'R' && choice != 'r');
}

/* This function shows the contents of the hanamaru store
Precondition: Rescue Hanamaru, then press H in dungeon menu
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
*/
void hanamaruStore(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	int i;
	char choice;
	int index; // THIS IS ONLY FOR HANAMARU STORE. DO NOT TOUCH	

	do{
		printf("Hanamaru: Yohane-chan, zura! What can I do for you today?\n\n");
		printf("Total Gold: %d GP\n\n", game->gold);
		
		// Displays shop
		for (i = 0; i < MAX_HANAMARU; i++)
		    printf("[%d] %-25s \t %6dGP Stock: %2d\n", i+1, hanamaru[i].item, hanamaru[i].price, hanamaru[i].availability);       
		
		printf("[R]eturn\n\n");
		printf("Choice: ");
		scanf(" %c", &choice);
		
		// For buying the items	
		if (choice >= '1' && choice <= '9'){ 
			index = choice - '1'; 
			
			// Noppo Bread bc unlimited
		    if (index == 1){  
		        if (game->gold >= hanamaru[index].price){
					game->gold -= hanamaru[index].price;
					inventory[index].itemCount++;
					game->goldSpent = game->goldSpent + hanamaru[index].price;
					printf("One %s successfully purchased! You now have %d %s(s)\n", inventory[index].item, inventory[index].itemCount,inventory[index].item);
					system("pause");
					system("cls");
					}
				else{
					printf("Not enough GP\n");
					system("pause");
					system("cls");
				}
			}
			
			// For all other items not named Noppo Bread (since everything else is a one-time purchase)
			else{ 
		        if (game->gold >= hanamaru[index].price && hanamaru[index].availability == 1){
		            game->gold -= hanamaru[index].price;
		            inventory[index].itemCount++;
		            game->goldSpent = game->goldSpent + hanamaru[index].price;
		            
		            if (index >= 5 && index <= 7 && hanamaru[index].availability == 1){
					    game->maxHP += 1;
					    game->hp += 1;
					}

		            hanamaru[index].availability = 0;
		            printf("One %s successfully purchased! You now have %d %s(s)\n", inventory[index].item, inventory[index].itemCount, inventory[index].item);
		        } 
				else if (game->gold < hanamaru[index].price) 
		            printf("Not enough GP\n");
				else
		            printf("This item is no longer available\n");
	
			    system("pause");
			    system("cls");
			}
		}
		
		// Return
		else if (choice == 'R' || choice == 'r'){
		    system("cls");
		    showDungeonMenu(idolDungeon, game, inventory);
		}
		
		// Anything else
		else{
		    printf("Invalid choice!\n");
		    system("pause");
		    system("cls");
		}	
		
		achievementUnlock(achievement, game, 0);
	} while (choice != 'R' && choice != 'r');	
}

/* This function unlocks items in hanamaru store depending on which idol was rescued
Precondition: Rescue an idol 
@param charIdx: The index of the character from the idolDungeon structure
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
*/
void itemUnlock(int charIdx, struct hanamaruTag hanamaru[]){
		// Unlock item after clearing dungeon
		if (charIdx == 0) // Chika
			hanamaru[MIKAN_MOCHI].availability = 1;	
		if (charIdx == 1) // Riko
			hanamaru[BAT_TAMER].availability = 1;
		if (charIdx == 2) // You
			hanamaru[AIR_SHOES].availability = 1;
		if (charIdx == 4) // Ruby
			hanamaru[ICE_CREAM].availability = 1;
		if (charIdx == 5) // Dia
			hanamaru[KURO_MACHA].availability = 1;
		if (charIdx == 6) // Kanan
			hanamaru[SHOVEL_UP].availability = 1;
		if (charIdx == 7) // Mari
			hanamaru[STEWSHINE].availability = 1;	
}

/* This function saves the game's contents into a binary file named "yohane.bin"
Precondition: Press "S" in dungeon menu (Save and Quit) 
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void saveGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	FILE *ptr;
	
	ptr = fopen("yohane.bin", "wb");
	
    fwrite(game, sizeof(struct gameTag), 1, ptr);
    fwrite(inventory, sizeof(struct inventoryTag), MAX_INVENTORY, ptr);
    fwrite(hanamaru, sizeof(struct hanamaruTag), MAX_HANAMARU, ptr);
    fwrite(achievement, sizeof(struct achievementTag), MAX_ACHIEVEMENTS, ptr);

    fclose(ptr);
}

/* This function loads the game's contents from a binary file named "yohane.bin"
Precondition: Press "C" in the title screen (Continue) or "N" in title screen during new game plus
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void loadGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	FILE *ptr;
	
	ptr = fopen("yohane.bin", "rb");
	
	if (ptr == NULL || game->running == 0)
		game->running = 0;
	else{
	fread(game, sizeof(struct gameTag), 1, ptr);
    fread(inventory, sizeof(struct inventoryTag), MAX_INVENTORY, ptr);
    fread(hanamaru, sizeof(struct hanamaruTag), MAX_HANAMARU, ptr);
    fread(achievement, sizeof(struct achievementTag), MAX_ACHIEVEMENTS, ptr);
	}

	fclose(ptr);
}
/* This function converts the integers in the dungeon functions into its respective symbols for the dungeon layout
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
*/
void dungeonIdentifier(grid dimension2D, int nRow, int nCol){
	for(int i = 0; i < MAX_ROW; i++){
		for(int j = 0; j < MAX_COL; j++){
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
				printf("L");
				printf("\e[0m"); //Resets the color to default
			}else if(dimension2D[i][j] == 14) //Switches
				printf("0");	
			
		}
		printf("\n");
	}
}
/* This function identifies the walls in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the spikes in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the water tiles in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the heat tiles in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the treasure tile in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the exit tile in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the bat tiles in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the abilities of the bats in game and updates their 
position in the map, including their behavior depending on dungeon level
Precondition: Press any key while in a dungeon 
@param dimension2D: the size of the dungeon in rows and columns
@param playerMove: the amount of times the player has moved
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
*/
void batAbilities(grid dimension2D, int playerMove, struct gameTag *game, struct inventoryTag inventory[]){
	
    int i, j;
    
    // directions by index
    int rowDirection[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; 
    int colDirection[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    
    int tempGrid[MAX_ROW][MAX_COL];
    int direction;
    int targetRow, targetCol;
    int targetTile;
    int nDir;
    int attacked = 0;
    int currentTile;

    // this updates the bats in real time (revert big B to small after attacking the player)
    for (i = 0; i < MAX_ROW; i++)
        for (j = 0; j < MAX_COL; j++){
            if (dimension2D[i][j] == 11)
                tempGrid[i][j] = 8;
            else
                tempGrid[i][j] = dimension2D[i][j];
        }
        

    if ((game->currentPlaythroughClear == 0 && playerMove % 2 == 0) || game->currentPlaythroughClear >= 1){
    	
        for (i = 0; i < MAX_ROW; i++)
            for (j = 0; j < MAX_COL; j++){
                if (dimension2D[i][j] == 8 && tempGrid[i][j] == 8){
                	
                    if (game->currentPlaythroughClear == 2)
                        direction = rand() % 8; // diagonal moves
                    else
                        direction = rand() % 4; // cardinal

                    nDir = direction + 1; 
                    
                    targetRow = i + rowDirection[direction];
                    targetCol = j + colDirection[direction];

                    if (tileValidation(dimension2D, MAX_ROW, MAX_COL, i, j, nDir)){
                        targetTile = dimension2D[targetRow][targetCol];

                        if (targetTile == 1 && tempGrid[targetRow][targetCol] == 1){
                        	
                            if (dimension2D[i][j] == 4)
                                currentTile = 4;
                            else
                                currentTile = 1;

                            tempGrid[targetRow][targetCol] = 8;
                            tempGrid[i][j] = currentTile;
                        }
                        else if (targetTile == 4 && tempGrid[targetRow][targetCol] == 4){
                            currentTile = 4;
                            tempGrid[targetRow][targetCol] = 8;
                            tempGrid[i][j] = currentTile;
                        }
                        
                        else if (targetTile == 9 && attacked == 0){
                            tempGrid[i][j] = 11; // convert to big B

                            if (inventory[2].itemCount > 0){
                            	game->hp -= 0.5;
                            	game->dmgTaken += 0.5;
							}
                            else if (game->currentPlaythroughClear == 0){
                            	game->hp -= 0.5;
                            	game->dmgTaken += 0.5;
							}
                            else if (game->currentPlaythroughClear == 1){
                            	game->hp -= 1;
                            	game->dmgTaken += 1;
							}
							else{
								game->hp -= 1.5;
								game->dmgTaken += 1.5;
							}   
                			
                			if (game->hp <= 0)
                            	strcpy(game->killed, "Bat");
                            	
                            attacked = 1;
                        }
                    }
                }
            }
    }

    // update the map after everything 
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++) {
            dimension2D[i][j] = tempGrid[i][j];
        }
    }
    
}
/* This function identifies the player in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the gold tiles in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the bat tiles in the dungeon, if the player gets hit
It converts a small b (bat) into a B (bat attacked player)
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the siren (final boss) in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function identifies the lailaps in the dungeon
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param tRow: the pointer to mark the row of the obstacle
@param tCol: the pointer to mark the column of the obstacle
*/
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
/* This function verifies if the tile traversed to is a valid tile, by not going out of bounds
Precondition: Enter a dungeon in game 
@param dimension2D: the size of the dungeon in rows and columns
@param nRow: the number of columns in the layout
@param nCol: the number of columns in the layout
@param cRow: coordinates where the player is going to (row)
@param cCol: coordinates where the player is going to (column)
@param nDir: the direction that the player is headed to (ranges from 1 to 8)
@return the value of valid. 1 if valid, 0 if not 
*/
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
	}else if(nDir == 5){ 
		cRow--;
		cCol--;
		if(cRow >= 0 && cCol >= 0 && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}else if(nDir == 6){ 
		cRow--;
		cCol++;
		if(cRow >= 0 && cCol < nCol && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}else if(nDir == 7){ 
		cRow++;
		cCol--;
		if(cRow < nRow && cCol >= 0 && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}else if(nDir == 8){ 
		cRow++;
		cCol++;
		if(cRow < nRow && cCol < nCol && dimension2D[cRow][cCol] != 0)
			valid = 1;
	}
	return valid;
}
/* This function allows the player to obtain treasure in game based on the treasure tile
Precondition: Obtain a treasure in game depending where the dungeon tile is 
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void obtainTreasure(struct inventoryTag inventory[], struct gameTag game[]){
	
	srand(time(NULL));
	int random = rand() % 2;
	int goldRandom = (rand() % 90) + 10 + 1;
	if (random == 0){
		printf("Obtained: Noppo Bread (1)!\n");
		inventory[1].itemCount += 1;
	}
	else{
		printf("Obtained %d gold!\n", goldRandom);
		game->gold += goldRandom;	
	}
	
	system("pause");
}
/* This function allows the player to obtain gold from 
defeating bats depending on the level of the dungeon
Precondition: Defeat a bat and claim the gold dropped by it 
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void obtainGoldBat(struct gameTag *game){
	if (game->currentPlaythroughClear < game->hostagesSelected){
	if (game->currentPlaythroughClear == 0)
		game->gold += 5;
	if (game->currentPlaythroughClear == 1)
		game->gold += 10;
	if (game->currentPlaythroughClear == 2)
		game->gold += 15;
	}
}
/* This function moves the player around in a dungeon depending on users input 
Precondition: Enter a dungeon in game and press W, A, S, or D
@param dimension2D: the size of the dungeon in rows and columns
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param yRow: the current row of the player 
@param yCol: the current column of the player
@param targetRow: the target row that the player wants to go to, dependent on what key the user pressed
@param targetCol: the target column that the player wants to go to, dependent on what key the user pressed
@param verdict: the verdict that confirms if the player has won the dungeon yet or not 
@param currentTile: the current tile identifer that the player is currently standing on
*/
void movement(grid dimension2D, struct gameTag *game, struct inventoryTag inventory[], 
				int *yRow, int *yCol, int targetRow, int targetCol, int *verdict, int *currentTile){
	int currentRow = *yRow;
	int currentCol = *yCol;
	
	// THIS IS FOR PRESERVING TILES THAT HAVE BEEN PASSED THORUGH
	dimension2D[currentRow][currentCol] = *currentTile;
	
		if (dimension2D[currentRow][currentCol] == 9 && *currentTile == 5){
		    dimension2D[currentRow][currentCol] = 5;
		} 
		else if (dimension2D[currentRow][currentCol] == 9){
		    dimension2D[currentRow][currentCol] = 1;
		}

		if (dimension2D[targetRow][targetCol] == 2){ // Wall digging 
			dimension2D[targetRow][targetCol] = 1; // dig first  
			dimension2D[currentRow][currentCol] = 9;  // stay still     
		}
		else if (dimension2D[targetRow][targetCol] == 3){ // Spike 
			dimension2D[targetRow][targetCol] = 1; 
			dimension2D[currentRow][currentCol] = 9;  
			
			if (inventory[2].itemCount == 0){ 
				game->hp -= 0.5; 
				game->dmgTaken += 0.5;
			}	
				
			if (game->hp <= 0)
				strcpy(game->killed, "Spike");
		}
		else if (dimension2D[targetRow][targetCol] == 4){ // Water tile
		
			if (inventory[4].itemCount == 0) 
				dimension2D[currentRow][currentCol] = 9; 
			else{  
			*currentTile = 4;
		    dimension2D[targetRow][targetCol] = 9;
		    *yRow = targetRow;
		    *yCol = targetCol;
			}
		}
		else if (dimension2D[targetRow][targetCol] == 5){ // heat tile 
		    *currentTile = 5;
		    dimension2D[targetRow][targetCol] = 9;
		    *yRow = targetRow;
		    *yCol = targetCol;
		}

		else if (dimension2D[targetRow][targetCol] == 6){ // treasure 
		    *currentTile = 1; 
			dimension2D[targetRow][targetCol] = 9;
			*yRow = targetRow; 
			*yCol = targetCol; 
			
			obtainTreasure(inventory, game);
		}
		else if (dimension2D[targetRow][targetCol] == 1){ // FREE SPACE 
			*currentTile = 1; 
			dimension2D[targetRow][targetCol] = 9;
			*yRow = targetRow; 
			*yCol = targetCol; 
		}
		
		else if (dimension2D[targetRow][targetCol] == 8 || dimension2D[targetRow][targetCol] == 11){ // Yohane attacks bat
			dimension2D[targetRow][targetCol] = 10;  // Gold spotted!       
			dimension2D[currentRow][currentCol] = 9; // stay still
		}
		else if (dimension2D[targetRow][targetCol] == 10){ // gold tile	
			dimension2D[currentRow][currentCol] = 1; 
			dimension2D[targetRow][targetCol] = 9;
			*yRow = targetRow; 
			*yCol = targetCol; 
			
			obtainGoldBat(game);	
		}
		else if (dimension2D[targetRow][targetCol] == 7){ // Exit
			dimension2D[currentRow][currentCol] = 1; 
			dimension2D[targetRow][targetCol] = 9;
			*yRow = targetRow; 
			*yCol = targetCol;
			*verdict = 1;
		}
		
		else 
			dimension2D[currentRow][currentCol] = 9; 
}
/* This function allows the player to cycle their items to the right 
Precondition: Enter a dungeon in game and input "]", if the user has an item on hand from their inventory
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void cycleItemForward(struct inventoryTag inventory[], struct gameTag *game){
    int i;
    int currentPos = game->currentHandIndex;
    int found = 0;
    int invIdx, nextIdx;
    int availableCount = 0;
    
    for (i = 0; i < 3; i++){
        invIdx = game->handIndex[i];
        if (inventory[invIdx].itemCount > 0){
            availableCount++;
        }
    }

    if (availableCount > 0){
        for (i = 1; i <= 3; i++){
            nextIdx = (currentPos + i) % 3;
            invIdx = game->handIndex[nextIdx];
            if (inventory[invIdx].itemCount > 0 && found == 0){
                game->currentHandIndex = nextIdx;
                found = 1;
            }
        }
    }
	else
    	game->currentHandIndex = -1;
}
/* This function allows the player to cycle their items to the left
Precondition: Enter a dungeon in game and input "[", if the user has an item on hand from their inventory
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void cycleItemBackward(struct inventoryTag inventory[], struct gameTag *game){
    int i;
    int currentPos = game->currentHandIndex;
    int found = 0;
	int invIdx, nextIdx;
    int availableCount = 0;
    
    for (i = 0; i < 3; i++){
        invIdx = game->handIndex[i];
        if (inventory[invIdx].itemCount > 0){
            availableCount++;
        }
    }

    if (availableCount > 0){
        for (i = 1; i <= 3; i++){
            nextIdx = (currentPos - i + 3) % 3;
            invIdx = game->handIndex[nextIdx];
            if (inventory[invIdx].itemCount > 0 && found == 0){
                game->currentHandIndex = nextIdx;
                found = 1;
            }
        }
    }
	else
    	game->currentHandIndex = -1;
}
/* This function allows the player to consume an item in their inventory
Precondition: Enter a dungeon in game and input a SPACE BAR, if the user has an item in hand
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct gameTag *game: the structure containing the game statistics of the player
*/
void useItem(struct inventoryTag inventory[], struct gameTag *game){
	int invIdx = game->handIndex[game->currentHandIndex];
	
	if (inventory[invIdx].itemCount > 0 && invIdx != 8)
		inventory[invIdx].itemCount--;
		
	if (invIdx == 0 || invIdx == 1){ // Tears and Noppo
		if (game->hp < game->maxHP){
			game->hp += 0.5;
		}
		if (game->hp >= game->maxHP){
			game->hp = game->maxHP;
		}	
	}
}
/* This function resets certain statistics of the player when they get a game over
Precondition: Player's HP reaches 0, or Lailaps HP reaches 0 in the final boss
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
*/
void gameOver(struct gameTag *game, struct inventoryTag inventory[]){
    int i;

	game->maxHP = 3;
    game->hp = 3.0;	

    for (i = 2; i < MAX_INVENTORY - 1; i++)
    	inventory[i].hidden = 1;
	
	for (i = 2; i < MAX_INVENTORY; i++)
		inventory[i].itemCount = 0;
		
	game->currentFloorIndex = 0;
}

/* Base Logic Package (e.g., character moving, tile finding and validation, winning, quitting)
Precondition: Player enters a dungeon or enters the final boss
@param dimension2D: the size of the dungeon in rows and columns
@param struct gameTag *game: the structure containing the game statistics of the player
@param charIdx: the index of a character in idolDungeon structure
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param dungeonIndex: the index of the dungeon entered by the player (0, 1, 2)
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
@return the verdict depending on whether the player clears a dungeon or not (1 if win, 0 if lose)
*/
int yohaneBaseLogic(grid dimension2D, struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[])
{
	int row = MAX_ROW;
	int col = MAX_COL;
	int quit = 0, verdict = 0;
	int wlRow, wlCol, spikeRow, spikeCol, wtRow, wtCol, heatRow, heatCol, tRow, tCol, eRow, eCol, bRow, bCol, yRow, yCol, gRow, gCol, hitRow, hitCol, sirenRow, sirenCol, lRow, lCol;
	char move;
	
	int playerMoveCount = 0;
	int currentTile = 1;
	int yRowOld, yColOld;
	int moved;
	int invIdx;
	srand(time(NULL));
	
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

	game->dmgTaken = 0;
/*	
	this is moved to gameMenu
	if (game->currentPlaythroughClear < game->hostagesSelected){
	if (game->currentPlaythroughClear == 0){
		game->floorCount = 1;
	}
	else if (game->currentPlaythroughClear == 1){
		game->floorCount = (rand() % 2) + 2;
	}
	else if (game->currentPlaythroughClear == 2){
		game->floorCount = (rand() % 2) + 3;
	}
}
*/
	do{
		system("cls");
		
		if (game->currentPlaythroughClear < game->hostagesSelected){
			printf("Dungeon #%d: %s\n", dungeonIndex+1, idolDungeon[charIdx].dungeon);
			printf("Floor %d of %d\n", game->currentFloorIndex+1, game->floorCount);
		}
		else
			printf("Final Battle: Siren of the Mirror World!\n");
			
		printf("\n");
		printf("HP: %.1f / %d", game->hp, game->maxHP);
		
		if (game->currentPlaythroughClear == 3){
			printf("    Lailaps HP: %.1f / %d", game->lailapsHP, game->maxLailapsHP);
			printf("\t\t");
		}
		else
	    	printf("\t\t\t\t");
	    	
	    printf("Total Gold: %d GP\n", game->gold);
	    
	    if (game->currentHandIndex != -1){
	    invIdx = game->handIndex[game->currentHandIndex];
	    
		    if (inventory[invIdx].itemCount > 0){
		    	if (inventory[invIdx].itemCount == 1)
			    	printf("Item on hand: %s\n", inventory[invIdx].item);
			    else
			        printf("Item on hand: %s (%d)\n", inventory[invIdx].item, inventory[invIdx].itemCount);
			}
			else
				printf("Item on hand: N/A\n");
		} 
		else
	    	printf("Item on hand: N/A\n");


	    printf("\n");
	    
		dungeonIdentifier(dimension2D,row,col);
		printf("\n Game Controls \n"); //  | ゲームコントロール
		printf("[W] Up | [A] Left | [S] Down | [D] Right | [X] Freeze\n[[] Cycle Previous Item | []] Cycle Next Item | [SPACE] Use Item on Hand\n");
		// printf("[W] 上 | [A] 左 | [S] 下 | [D] 右 | [X] フリーズ \n");		
		move = getch();
		
		yRowOld = yRow;
		yColOld = yCol;
		moved = 0;
		
		switch(move){
			case 'W': case 'w':
				if(tileValidation(dimension2D,row,col,yRow,yCol,1))
					movement(dimension2D,game,inventory,&yRow,&yCol,yRow-1,yCol,&verdict,&currentTile);
					break;
			case 'A': case 'a':
				if(tileValidation(dimension2D,row,col,yRow,yCol,2))
					movement(dimension2D,game,inventory,&yRow,&yCol,yRow,yCol-1,&verdict,&currentTile);
					break;
			case 'S': case 's':
				if(tileValidation(dimension2D,row,col,yRow,yCol,3))
					movement(dimension2D,game,inventory,&yRow,&yCol,yRow+1,yCol,&verdict,&currentTile);
					break;
			case 'D': case 'd':
				if(tileValidation(dimension2D,row,col,yRow,yCol,4))
					movement(dimension2D,game,inventory,&yRow,&yCol,yRow,yCol+1,&verdict,&currentTile);
					break;
			case 'X': case 'x':
				playerMoveCount++;
				break;
			case '[': 
				cycleItemForward(inventory,game);
				break;
			case ']':
				cycleItemBackward(inventory,game);
				break;	
			case ' ': 
				useItem(inventory,game);
				break;
			default:
				printf("Error 7611111810176105118101: Your choice is invalid. Please try again.");
				system("pause");
				// printf("エラー 7611111810176105118101: 無効な選択肢です。もう一度やり直してください。");
		}
		
		if (yRow != yRowOld || yCol != yColOld)
		    moved = 1; 
		else 
		    moved = 0;
		
		playerMoveCount++;
		batAbilities(dimension2D, playerMoveCount, game, inventory);
		achievementUnlock(achievement, game, 0);
		if (currentTile == 5 && moved == 0 && inventory[4].itemCount == 0){
			game->hp -= 1;
			game->dmgTaken += 1;
			if (game->hp <= 0)
				strcpy(game->killed, "Heat Tile");
		}
		
		if (game->currentHandIndex == 2 && game->hp <= 0 && inventory[8].itemCount > 0){
				game->hp = game->maxHP;
				inventory[8].itemCount--;
				game->chocoMintUsageCount++;
		}
	
		else if (game->hp <= 0){
			printf("\t\t\t\t  You Died!\n");
			printf("\t\t\t\tKilled by: %s\n", game->killed);
			system("pause");
			
			gameOver(game, inventory);
	        achievementUnlock(achievement, game, 0);
			quit = 1;
		}
				
		
	}while(!quit && !verdict);
	
	printf("\n");
	if(verdict){
		printf("You have found the door to the exit. Congratulations!!!\n");
		system("pause");
		system("cls");
		// printf("あなたは出口への扉を見つけた。おめでとうございます!!!");
	}

	return verdict;
}

/* This function sets up the dungeon layout of dungeon index 0
Precondition: Player enters a dungeon
@param struct gameTag *game: the structure containing the game statistics of the player
@param charIdx: the index of a character in idolDungeon structure
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param dungeonIndex: the index of the dungeon entered by the player (0, 1, 2)
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
@return the verdict from yohaneBaseLogic
*/
int awashimaMarinePark(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]){
				
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,6,1,1,3,1,1,1,1,5,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,5,5,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,1,1,1,1,8,1,1,1,3,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,1,1,1,8,1,1,1,1,1,0},
				 	{0,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,1,3,3,1,1,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,8,1,1,3,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,3,1,1,1,3,1,1,1,1,3,1,1,1,1,1,1,1,2,3,1,1,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,3,1,1,9,3,1,1,1,1,3,1,1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,2,2,2,1,1,1,3,3,3,8,3,3,0},
				 	{0,1,1,3,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,4,4,1,1,1,1,1,1,1,1,3,3,1,5,1,1,1,1,1,2,2,1,1,1,1,1,0}, 
					{0,1,1,3,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,2,2,1,1,1,1,1,0},
					{0,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,8,1,1,1,1,1,5,1,1,1,1,1,2,2,1,8,1,1,7,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
				};
	
	return yohaneBaseLogic(dungeon, game, charIdx, idolDungeon, dungeonIndex, inventory, achievement);
}


/* This function sets up the dungeon layout of dungeon index 1
Precondition: Player enters a dungeon
@param struct gameTag *game: the structure containing the game statistics of the player
@param charIdx: the index of a character in idolDungeon structure
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param dungeonIndex: the index of the dungeon entered by the player (0, 1, 2)
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
@return the verdict from yohaneBaseLogic
*/
int izumitoSeaParadise(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]){
	
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,6,1,1,3,1,1,1,1,5,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,5,5,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,1,1,1,1,8,1,1,1,3,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,1,1,1,8,1,1,1,1,1,0},
				 	{0,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,1,3,3,1,1,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,8,1,1,3,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,3,1,1,1,3,1,1,1,1,3,1,1,1,1,1,1,1,2,3,1,1,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,3,1,1,9,3,1,1,1,1,3,1,1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,2,2,2,1,1,1,3,3,3,8,3,3,0},
				 	{0,1,1,3,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,4,4,1,1,1,1,1,1,1,1,3,3,1,5,1,1,1,1,1,2,2,1,1,1,1,1,0}, 
					{0,1,1,3,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,2,2,1,1,1,1,1,0},
					{0,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,8,1,1,1,1,1,5,1,1,1,1,1,2,2,1,8,1,1,7,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
				};

	return yohaneBaseLogic(dungeon, game, charIdx, idolDungeon, dungeonIndex, inventory, achievement);
}

/* This function sets up the dungeon layout of dungeon index 2 
Precondition: Player enters a dungeon
@param struct gameTag *game: the structure containing the game statistics of the player
@param charIdx: the index of a character in idolDungeon structure
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param dungeonIndex: the index of the dungeon entered by the player (0, 1, 2)
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
@return the verdict from yohaneBaseLogic
*/
int shougetsuConfectionary(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,6,1,1,3,1,1,1,1,5,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,5,5,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,3,1,1,1,1,1,1,1,1,8,1,1,1,3,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,1,1,1,8,1,1,1,1,1,0},
				 	{0,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,1,3,3,1,1,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,8,1,1,3,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,3,1,1,1,3,1,1,1,1,3,1,1,1,1,1,1,1,2,3,1,1,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,1,1,1,1,1,1,1,1,1,0},
				 	{0,1,3,1,1,9,3,1,1,1,1,3,1,1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,3,3,1,1,2,2,2,1,1,1,3,3,3,8,3,3,0},
				 	{0,1,1,3,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,4,4,1,1,1,1,1,1,1,1,3,3,1,5,1,1,1,1,1,2,2,1,1,1,1,1,0}, 
					{0,1,1,3,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,2,2,1,1,1,1,1,0},
					{0,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,8,1,1,1,1,1,5,1,1,1,1,1,2,2,1,8,1,1,7,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
				};

	return yohaneBaseLogic(dungeon, game, charIdx, idolDungeon, dungeonIndex, inventory, achievement);
}

/* Final Boss: Siren of the Mirror World!
Precondition: Player clears three dungeons in a single playthrough
@param struct gameTag *game: the structure containing the game statistics of the player
@param charIdx: the index of a character in idolDungeon structure
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param dungeonIndex: the index of the dungeon entered by the player (0, 1, 2)
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
@return the verdict from yohaneBaseLogic
*/
int sirenOfTheMirrorWorld(struct gameTag *game, int charIdx, struct idolDungeonTag idolDungeon[], 
					int dungeonIndex, struct inventoryTag inventory[], struct achievementTag achievement[]){
	grid dungeon = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,12,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
				 	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,13,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} 
				 	};

	// printf("Final Battle: Siren of the Mirror World!\n");
	// printf("最終決戦: 鏡の世界のセイレーン!\n");
	return yohaneBaseLogic(dungeon, game, charIdx, idolDungeon, dungeonIndex, inventory, achievement);
}

/* In game menu that allows the user to enter dungeons depending on input (1,2,3). If three dungeons are cleared
in a single playthrough, replace the three options with the singular option to face the final boss
Precondition: Player inputs "N" or "C" in the title screen (new game or continue)
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void gameMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	char choice;
	int index;
	int charIdx;
	int win = 0;
	int i;
	
	do{
	    printf("Choice: ");
	    scanf(" %c", &choice);
			
		if (choice >= '1' && choice < '1' + game->hostagesSelected && game->currentPlaythroughClear < game->hostagesSelected){ 
			index = choice - '1'; 
			charIdx = game->hostages[index]; 
			system("cls");
        	if (game->clearStatusTemp[index] == 1 || game->rescuedCount[charIdx] > 0)
        		printf("Dungeon is cleared. You can no longer enter\n");
        	else{
	        	printf("Entering dungeon %d\n\n", index+1);
	        	
	        	if (game->currentPlaythroughClear < game->hostagesSelected){
					if (game->currentPlaythroughClear == 0){
						game->floorCount = 1;
					}
					else if (game->currentPlaythroughClear == 1){
						game->floorCount = (rand() % 2) + 2;
					}
					else if (game->currentPlaythroughClear == 2){
						game->floorCount = (rand() % 2) + 3;
					}
				}
				
				/*
				for (game->currentFloorIndex = 0; game->currentFloorIndex < game->floorCount; game->currentFloorIndex++){
	        	win = 0;
	        	if (index == 0)
	        		win = awashimaMarinePark(game, charIdx, idolDungeon, index, inventory, achievement);
	        	if (index == 1)
	        		win = izumitoSeaParadise(game, charIdx, idolDungeon, index, inventory, achievement);
	        	if (index == 2)
	        		win = shougetsuConfectionary(game, charIdx, idolDungeon, index, inventory, achievement);
	        	}*/
	        	
	        	
				while (game->currentFloorIndex < game->floorCount && !(game->hp <= 0)){
	        	win = 0;
	        	if (index == 0)
	        		win = awashimaMarinePark(game, charIdx, idolDungeon, index, inventory, achievement);
	        	if (index == 1)
	        		win = izumitoSeaParadise(game, charIdx, idolDungeon, index, inventory, achievement);
	        	if (index == 2)
	        		win = shougetsuConfectionary(game, charIdx, idolDungeon, index, inventory, achievement);
	        	if (win == 1)
					game->currentFloorIndex++;
	        	}
	        	
	        	if (win == 1){
	        	printf("\n%s has been successfully rescued!\n", idolDungeon[charIdx].idol);
	        	game->rescuedCount[charIdx]++;
	        	game->clearStatus[charIdx] = 1;
	        	game->clearStatusTemp[index] = 1;
				game->currentPlaythroughClear++;	
	        	game->dungeonClears++; 
	        	game->currentFloorIndex = 0;
	        	itemUnlock(charIdx, hanamaru);
	        	achievementUnlock(achievement, game, 1);
			}
        	}
            system("cls");
			showDungeonMenu(idolDungeon, game, inventory);
		}
		
		else if (choice == '1' && game->currentPlaythroughClear == game->hostagesSelected){
			system("cls");
			win = sirenOfTheMirrorWorld(game, charIdx, idolDungeon, index, inventory, achievement);
			if (win == 1){
				printf("Win!\n");
				game->totalPlaythroughClear++;
				
				if (game->gold == 0)
					game->flawless = 1;
				
				itemUnlock(charIdx, hanamaru);
	        	achievementUnlock(achievement, game, 1);
	        	game->newGamePlus = 1;
            	system("cls");
	        	newGamePlusSetup(idolDungeon, game, inventory, hanamaru, achievement);
	        	titleScreen(idolDungeon,game,inventory,hanamaru,achievement);
			}
			
			system("pause");
			system("cls");
			showHostages(idolDungeon, game);
			showDungeonMenu(idolDungeon, game, inventory);
		}
		
		// Inventory
		else if (choice == 'I' || choice == 'i'){
			system("cls");
		    showInventory(idolDungeon, game, inventory);
		}
		
		// Save and quit 
		else if (choice == 'S' || choice == 's'){
			saveGame(idolDungeon, game, inventory, hanamaru, achievement);
			printf("Game Saved!\n\n");
			
			if (game->newGamePlus == 1)
	    			game->newGamePlus = 0;
			 
	        system("cls");
		}
		
		// hanamaru store
		else if (choice == 'H' || choice == 'h'){
        	if (game->rescuedCount[3] > 0){
        	system("cls");
            hanamaruStore(idolDungeon, game, inventory, hanamaru, achievement);
        }
        	else
        		printf("Totally nothing to see here!\n");
		}
		
		else
			printf("Invalid choice\n");    	
	} while (choice != 'S' && choice != 's');
}

/* Sets up new game plus in the event that the player manages to defeat
the final boss. Resets HP and maximum HP, as well as resets inventory count except for noppo bread
and Tears of a Fallen Angel. Selects three new hostages that have yet to be rescued
Precondition: Player defeats the final boss in a playthrough
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void newGamePlusSetup(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	int i;
	
	game->maxHP = 3;
	game->hp = 3;
	
	for (i = 2; i < MAX_INVENTORY; i++){
		inventory[i].itemCount = 0;
	}
	
	for (i = 2; i < MAX_INVENTORY - 1; i++){
		inventory[i].hidden = 1;
	}
	
	game->currentPlaythroughClear = 0;
	
	for (i = 0; i < MAX_HOSTAGES; i++){
		game->clearStatusTemp[i] = 0;
	}
}

/* Allows the player to continue their game based on the save file, if they have one 
Precondition: Player has an existing save file from pressing "Save and Quit"
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void continueGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	system("cls");
	
	loadGame(idolDungeon, game, inventory, hanamaru, achievement);	
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);
    gameMenu(idolDungeon, game, inventory, hanamaru, achievement);
}

/* Starts a new game if the player does not have an existing save file 
Precondition: Program is running 
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	system("cls");
	
	initializeGame(game);
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	initializeHanamaru(hanamaru);
	initializeAchievements(achievement);
	
	selectHostages(game);
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);
	
    gameMenu(idolDungeon, game, inventory, hanamaru, achievement);
}

/* Starts a new game plus after the player has successfully defeated the final boss 
Precondition: Defeat the final boss 
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void newGamePlus(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	system("cls");
	
	game->newGamePlus = 0;
	selectHostages(game);
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);
	
    gameMenu(idolDungeon, game, inventory, hanamaru, achievement);
}

/* Shows the title screen of the program 
Precondition: Program is running 
@param struct idolDungeonTag idolDungeon[]: the structure containing the pair of idols and dungeons associated
@param struct gameTag *game: the structure containing the game statistics of the player
@param struct inventoryTag inventory[]: the structure containing the player's inventory
@param struct hanamaruTag hanamaru[]: the structure containing the contents of the hanamaru shop
@param struct achievementTag achievement[]: the structure containing the details of the achievements in game
*/
void titleScreen(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
		char choice;
			
		do {
        printf("\t************************************************\n");
        printf("\t*            Yohane The Parhelion!             *\n");
        printf("\t*       The Siren in the Mirror World!         *\n");
        printf("\t************************************************\n");
		
		if (!game->running || game->newGamePlus == 1)
        	printf("\t\t  [N]ew Game\n");
        else	
        	printf("\t\t  [C]ontinue\n");
    	
        printf("\t\t  [V]iew Achievements\n");
        printf("\t\t  [Q]uit\n");
        printf("\nYour choice: ");
        scanf(" %c", &choice);

        switch (choice){
            case 'N': case 'n':
            	if (!game->running)
                	newGame(idolDungeon, game, inventory, hanamaru, achievement);
                else if (game->newGamePlus == 1)
                	newGamePlus(idolDungeon, game, inventory, hanamaru, achievement);
                else{
                	printf("Invalid choice!\n");
                	system("pause");
			    	system("cls");
			    }
                break;
            case 'C': case 'c':
            	if (game->running == 1){
                	continueGame(idolDungeon, game, inventory, hanamaru, achievement);
                	system("cls");
                }
                else{
                	printf("Invalid choice!\n");
                	system("pause");
			    	system("cls");   	
            	}
                break;
            case 'V': case 'v':
        		system("cls");
                viewAchievements(achievement);
                system("pause");
                system("cls");
                break;
            case 'Q': case 'q':
                printf("See you next time!\n");
                break;
            default:
                printf("Invalid choice!\n");
                system("pause");
			    system("cls");
        }
        	
    } while (choice != 'Q' && choice != 'q');	
}

int main(){
	srand(time(NULL));
    
	struct idolDungeonTag idolDungeon[MAX_IDOLS];
	struct gameTag game;
	struct inventoryTag inventory[MAX_INVENTORY];
	struct hanamaruTag hanamaru[MAX_HANAMARU];
	struct achievementTag achievement[MAX_ACHIEVEMENTS];

	initializeGame(&game);
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	initializeHanamaru(hanamaru);
	initializeAchievements(achievement);
	
	loadGame(idolDungeon, &game, inventory, hanamaru, achievement);	
	
	titleScreen(idolDungeon, &game, inventory, hanamaru, achievement);

    return 0; 
}
