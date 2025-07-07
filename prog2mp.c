/* 
to do by priority: 
- core gameplay 
- dungeons itself 
- game over mechanics (game->hp <= 0)
- final boss
- new game+ after clear
	Carried over:
	- idols rescued
	- gold 
	- achievements
	- noppo bread and tears of fallen angel
	not carried over:
	- any other shop items
	- max hp (go back to 3 hp)
	
- item on hand (specs did not specify lmao)
- continue game on main menu if file exists

Complete:
- Main menu
- achievements
- dungeon menu
- hostage selection
- inventory
- hanamaru shop
- save file
- load file

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
	int hp;
	int gold;
	int hostages[MAX_HOSTAGES];
	int rescuedCount[MAX_IDOLS];
	int clearStatus[MAX_IDOLS];
	int clearStatusTemp[MAX_HOSTAGES];
	int running;
	int dungeonClears;
	int goldSpent;
	int dmgTaken;
	int currentPlaythroughClear;
};

struct achievementTag{
	Name achievement;
	int earned;
	Description description;
	char dateEarned[20];
};

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
	
	strcpy(achievement[12].achievement, "Beginner’s Sailing!");
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
	strcpy(achievement[25].description, "Accumulate a total of 5000G spent on Hanamaru’s stores across multiple playthroughs");
	
	strcpy(achievement[26].achievement, "Ruby-chan! Hai? Nani ga suki?");
	achievement[26].earned = 0;
	strcpy(achievement[26].description, "Get saved by a fatal blow from Ruby’s choco-mint ice cream item.");
	
	strcpy(achievement[27].achievement, "Step! ZERO to ONE!");
	achievement[27].earned = 0;
	strcpy(achievement[27].description, "Complete a playthrough with 0G on-hand at the end");
}

void viewAchievementsCount(struct achievementTag achievement[], int achievementCount){
	
	system("cls");
    printf("************************************************************\n");
    printf("                    Achievements module                     \n");
    printf("                      Obtained: %d / %d                     \n", achievementCount, MAX_ACHIEVEMENTS);
    printf("************************************************************\n");
}

// confirms that a char inputted is a number
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

int strToInt(char choice[]){
    int count = 0;
    int num = 0;

    while (choice[count] != '\0') {
        num = num * 10 + (choice[count] - '0');
        count++;
    }

    return num;
}

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

// copied my old MP from previous take for this
void getCurrentDate(char *output){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char mm[3], dd[3], yyyy[5], hh[3], min[3];

    intToStr(t->tm_mon + 1, mm, 2);       // month
    intToStr(t->tm_mday, dd, 2);          // day
    intToStr(t->tm_year + 1900, yyyy, 4); // year
    intToStr(t->tm_hour, hh, 2);          // hour
    intToStr(t->tm_min, min, 2);          // minutes

 
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

void achievementUnlock(struct achievementTag achievement[], struct gameTag *game){
				
		// index 9 (missing) (beat final boss once)
		// index 18 (missing) (beat final boss twice)
		// index 26 (missing) (get saved by ruby item) 
			
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
		}
		
		// achievement rescue for first time, index 1 to 8 
		for (i = 0; i < MAX_IDOLS; i++) 
			if (game->rescuedCount[i] > 0 && achievement[i+1].earned == 0){
			achievement[i+1].earned = 1;
			getCurrentDate(achievement[i+1].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[i+1].achievement);	
		}
		
		// index 9 (missing) (beat final boss once)
		
		// achievement rescue twice, index 10 to 17 
		for (i = 0; i < MAX_IDOLS; i++) 
			if (game->rescuedCount[i] > 1 && achievement[i+10].earned == 0){
			achievement[i+10].earned = 1;
			getCurrentDate(achievement[i+10].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[i+10].achievement);	
		}
		
		// index 18 (missing) (beat final boss twice)
		
		// clear 10 dungeons (index 19)
		if (game->dungeonClears >= 10 && achievement[19].earned == 0){
			achievement[19].earned = 1;
			getCurrentDate(achievement[19].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[19].achievement);
		}
		
		// rescue chika, you, ruby (index 20)
		if (game->rescuedCount[0] > 0 && game->rescuedCount[2] > 0 && game->rescuedCount[4] > 0 && achievement[20].earned == 0){
			achievement[20].earned = 1;
			getCurrentDate(achievement[20].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[20].achievement);
		}
		
		// rescue hanamaru, dia, kanan (index 21)
		if (game->rescuedCount[3] > 0 && game->rescuedCount[5] > 0 && game->rescuedCount[6] > 0 && achievement[21].earned == 0){
			achievement[21].earned = 1;
			getCurrentDate(achievement[21].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[21].achievement);
		}
		
		// rescue riko, mari (index 22)
		if (game->rescuedCount[1] > 0 && game->rescuedCount[7] > 0 && achievement[22].earned == 0){
			achievement[22].earned = 1;
			getCurrentDate(achievement[22].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[22].achievement);
		}
		
		// Have Yohane rescue all Aqours members for the first time (index 23)
		if (rescueCounter == 8 && achievement[23].earned == 0){
			achievement[23].earned = 1;
			getCurrentDate(achievement[23].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[23].achievement);
		}
		
		// no damage taken (index 24)
		if (game->dmgTaken == 0 && achievement[24].earned == 0){
			achievement[24].earned = 1;
			getCurrentDate(achievement[24].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[24].achievement);
		}
		
		// 5000g spent across all playthroughs (index 25)
		if (game->goldSpent >= 5000 && achievement[25].earned == 0){
			achievement[25].earned = 1;
			getCurrentDate(achievement[25].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[25].achievement);
		}
		
		// index 26 (get saved by ruby) missing
		
		// finish game with no gold (index 27)
		if (game->gold == 0 && achievement[27].earned == 0){
			achievement[27].earned = 1;
			getCurrentDate(achievement[27].dateEarned);
			printf("Achievement unlocked: %s\n", achievement[27].achievement);
		}
}

void viewAchievementDetails(char choice[], struct achievementTag achievement[], int achievementCount){
	
	int index;
    	
		do{
			
			index = strToInt(choice) - 1;
		    system("cls");
		    viewAchievementsCount(achievement, achievementCount);
		    
		    if (index >= 0 && index < 28){
			    printf("Achievement Name: %s\n", achievement[index].achievement);
				printf("\n");
				printf("Status: ");
				
				if (achievement[index].earned == 1){
					printf("EARNED!\n\n");
					printf("Date Earned: %s\n\n", achievement[index].dateEarned);
				}
				else
					printf("NOT EARNED!\n\n");	
					
				printf("Description: \n");
				printf("%s\n\n", achievement[index].description);
			}
			
			else
				printf("Invalid choice!\n\n");
							
			printf("[R]eturn to Achievements Module\n\n");
		    printf("Choice: ");
		    scanf("%s", choice);
			
			
	} while (!(choice[0] == 'R' || choice[0] == 'r') && choice[1] == '\0');
	
	choice[0] = '\0';
	
}

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

void selectHostages(struct gameTag *game){
	int index;
    int selected = 0;
    int used[MAX_IDOLS] = {0};
    
    while (selected < MAX_HOSTAGES){
        index = rand() % MAX_IDOLS;
        if (used[index] == 0){
            used[index] = 1;
            game->hostages[selected] = index;	// randomly selected indexes go to hostage array
            selected++;
        }
    }
}

void showHostages(struct idolDungeonTag idolDungeon[], struct gameTag *game){

	int i, idx;

	printf("Hostages: \n");
    for (i = 0; i < 3; i++){
        idx = game->hostages[i];
        printf("- %s in %s\n", idolDungeon[idx].idol, idolDungeon[idx].dungeon);
    }
    
    printf("\n\n");
}

void showDungeonMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]){
	
	int i, idx;
	
    printf("Lailaps: Yohane! Where should we go to now?\n\n");
    
    printf("HP: %d / %d", game->hp, game->maxHP);
    printf("\t\t\t\t");
    printf("Total Gold: %d GP\n", game->gold);
    printf("Item on hand: N/A\n");	// placeholder, fix later
    printf("\n");
    
	if (game->currentPlaythroughClear < 3){
	    for (i = 0; i < 3; i++){
	        idx = game->hostages[i];
	        if (game->clearStatusTemp[i] == 1)
	        	printf("[X] Visit %s\n", idolDungeon[idx].dungeon);
	        else
	        	printf("[%d] Visit %s\n", i+1, idolDungeon[idx].dungeon);
		}
	}
	else
	    printf("[1] Face the Siren of Numazu\n");
			
    printf("\n[I]nventory");
    printf("\t\t");
	printf("[S]ave and Quit");
	printf("\t\t");
	
	if (game->rescuedCount[3] > 0)
		printf("[H]anamaru Store");
		
	printf("\n\n");
   
}

void showInventory(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]){
	
	char choice;
	int i;
	int count = 1;
	printf("Lailaps: These are the items you have, Yohane!\n\n");
	printf("HP: %d / %d", game->hp, game->maxHP);
	printf("\t\t\t\t");
    printf("Total Gold: %d GP\n", game->gold);
	printf("Items available\n\n");
	
	// Show only non-hidden items
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
			    showHostages(idolDungeon, game);
		    	showDungeonMenu(idolDungeon, game, inventory);
		    	break;
		    default:
		    	printf("Invalid choice\n");
			}
	} while (choice != 'R' && choice != 'r');
}


void hanamaruStore(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], struct hanamaruTag hanamaru[]){
	
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
			index = choice - '1'; // char to number
			
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
		    showHostages(idolDungeon, game);
		    showDungeonMenu(idolDungeon, game, inventory);
		}
		
		// Anything else
		else{
		    printf("Invalid choice!\n");
		    system("pause");
		    system("cls");
		}	
			
	} while (choice != 'R' && choice != 'r');
		
}

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

void saveGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	
	int i;
	FILE *ptr;
	
	ptr = fopen("gameData.txt", "w");
	
	fprintf(ptr, "Max HP: %d\n", game->maxHP);
	fprintf(ptr, "Current HP: %d\n", game->hp);
	fprintf(ptr, "Gold: %d\n", game->gold);
	fprintf(ptr, "Total Dungeon Clears: %d\n", game->dungeonClears);
	fprintf(ptr, "Total Gold Spent: %d\n", game->goldSpent);
	fprintf(ptr, "Total Damage Taken: %d\n", game->dmgTaken);
	fprintf(ptr, "Running Status: %d\n", game->running);
	fprintf(ptr, "Dungeon Clears in Current Playthrough: %d\n", game->currentPlaythroughClear);
	
	for (i = 0; i < MAX_HOSTAGES; i++)
        fprintf(ptr, "Hostage: %s\n", idolDungeon[game->hostages[i]].idol);

    for (i = 0; i < MAX_IDOLS; i++)
        fprintf(ptr, "Dungeon %s: %d\n", idolDungeon[i].dungeon, game->clearStatus[i]);
        
    for (i = 0; i < MAX_HOSTAGES; i++)
        fprintf(ptr, "Dungeon Cleared this Playthrough: %d\n", game->clearStatusTemp[i]);    
	
    for (i = 0; i < MAX_IDOLS; i++)
        fprintf(ptr, "%s rescues: %d\n", idolDungeon[i].idol, game->rescuedCount[i]);
        
    for (i = 0; i < MAX_INVENTORY; i++)
        fprintf(ptr, "%s: %d\n", inventory[i].item, inventory[i].itemCount);
        
    for (i = 0; i < MAX_ACHIEVEMENTS; i++)
    	if (achievement[i].earned == 1)
        	fprintf(ptr, "%s: %d %s\n", achievement[i].achievement, achievement[i].earned, achievement[i].dateEarned);
        else
        	fprintf(ptr, "%s: %d %s\n", achievement[i].achievement, 0, "-");

	for (i = 0; i < MAX_HANAMARU; i++)
		fprintf(ptr, "%s stock: %d\n", hanamaru[i].item, hanamaru[i].availability);

	
	fclose(ptr);
	
}

void loadGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){

	int i, j;
	char tempName[30];
	FILE *ptr;
	
	ptr = fopen("gameData.txt", "r");
	
	if (ptr == NULL){
		printf("Error opening file.\n");
		system("pause");
	}
	else{
		fscanf(ptr, "Max HP: %d\n", &game->maxHP);
		fscanf(ptr, "Current HP: %d\n", &game->hp);
		fscanf(ptr, "Gold: %d\n", &game->gold);
		fscanf(ptr, "Total Dungeon Clears: %d\n", &game->dungeonClears);
		fscanf(ptr, "Total Gold Spent: %d\n", &game->goldSpent);
		fscanf(ptr, "Total Damage Taken: %d\n", &game->dmgTaken);
		fscanf(ptr, "Running Status: %d\n", &game->running);
		fscanf(ptr, "Dungeon Clears in Current Playthrough: %d\n", &game->currentPlaythroughClear);
		
		for (i = 0; i < MAX_HOSTAGES; i++){
	      	fscanf(ptr, "Hostage: %s\n", tempName);
	      	for (j = 0; j < MAX_IDOLS; j++){
	       		if (strcmp(tempName, idolDungeon[j].idol) == 0)
	       			game->hostages[i] = j;
	       		}
	    }
	    	 
		for (i = 0; i < MAX_IDOLS; i++)
		    fscanf(ptr, "%*[^:]: %d\n", &game->clearStatus[i]);
		
		for (i = 0; i < MAX_HOSTAGES; i++)
    		fscanf(ptr, "%*[^:]: %d\n", &game->clearStatusTemp[i]);
		
		for (i = 0; i < MAX_IDOLS; i++)
		    fscanf(ptr, "%*[^:]: %d\n", &game->rescuedCount[i]);

		for (i = 0; i < MAX_INVENTORY; i++)
		    fscanf(ptr, "%*[^:]: %d\n", &inventory[i].itemCount);

		for (i = 0; i < MAX_ACHIEVEMENTS; i++){
		    fscanf(ptr, "%*[^:]: %d", &achievement[i].earned);
		    if (achievement[i].earned == 1)
		        fscanf(ptr, " %[^\n]\n", achievement[i].dateEarned);
		    else
		        fscanf(ptr, " %*s\n"); 
		}

		for (i = 0; i < MAX_HANAMARU; i++)
		    fscanf(ptr, "%*[^:]: %d\n", &hanamaru[i].availability);
			}
			
		fclose(ptr);
			
}

void gameMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	
	char choice;
	int index;
	int charIdx;

	do{
    	
	    printf("Choice: ");
	    scanf(" %c", &choice);
		
		// I put "index = choice - '1'" inside bc the index is only needed for numerical inputs	
		if (choice >= '1' && choice <= '3' && game->currentPlaythroughClear < 3){ 
			index = choice - '1'; // char to number
			
			system("cls");
        	if (game->clearStatusTemp[index] == 1)
        		printf("Dungeon is cleared. You can no longer enter\n");
        	else{
	        	printf("Entering dungeon %d\n\n", index+1);
	        	
	        	// this auto clears right now as placeholder, might move this to a diff func
	        	// finish dungeon first before this
	        	charIdx = game->hostages[index]; 
	        	printf("%s has been successfully rescued!\n", idolDungeon[charIdx].idol);
	        	game->rescuedCount[charIdx]++;
	        	game->clearStatus[charIdx] = 1;
	        	game->clearStatusTemp[index] = 1;
				game->currentPlaythroughClear++;	// when this goes to 3, final boss time
	        	game->dungeonClears++; 
	        	
	        	itemUnlock(charIdx, hanamaru);
	        	achievementUnlock(achievement, game);					
        	}
        	system("pause");
            system("cls");
            showHostages(idolDungeon, game);
			showDungeonMenu(idolDungeon, game, inventory);
		}
		
		else if (choice == '1' && game->currentPlaythroughClear == 3){
			system("cls");
			printf("Final boss placeholder\n (PLS FINISH DUNGEONS FIRST)\n");
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
	        system("cls");
		}
		
		// hanamaru store
		else if (choice == 'H' || choice == 'h'){
        	if (game->rescuedCount[3] > 0){
        	system("cls");
            hanamaruStore(idolDungeon, game, inventory, hanamaru);
        }
        	else
        		printf("Totally nothing to see here!\n");
		}
		
		else
			printf("Invalid choice\n");
			    	
	} while (choice != 'S' && choice != 's');
}

void continueGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
		
	system("cls");
	
	loadGame(idolDungeon, game, inventory, hanamaru, achievement);	
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);

    gameMenu(idolDungeon, game, inventory, hanamaru, achievement);
				
}

void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], 
			struct hanamaruTag hanamaru[], struct achievementTag achievement[]){
	
	system("cls");
	
	// feel free to change these around if you want to test something, but make sure to revert it back when done testing
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
	
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	initializeHanamaru(hanamaru);
	initializeAchievements(achievement);
	
	selectHostages(game);
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);
	
    gameMenu(idolDungeon, game, inventory, hanamaru, achievement);

}

int main(){
	
	srand(time(NULL));
    char choice;
	struct idolDungeonTag idolDungeon[MAX_IDOLS];
	struct gameTag game;
	struct inventoryTag inventory[MAX_INVENTORY];
	struct hanamaruTag hanamaru[MAX_HANAMARU];
	struct achievementTag achievement[MAX_ACHIEVEMENTS];
	
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	initializeHanamaru(hanamaru);
	initializeAchievements(achievement);
	
	game.running = 0;
	
    do {
        printf("\t************************************************\n");
        printf("\t*            Yohane The Parhelion!             *\n");
        printf("\t*       The Siren in the Mirror World!         *\n");
        printf("\t************************************************\n");
		
		if (!game.running)
        	printf("\t\t  [N]ew Game\n");
        else
        	printf("\t\t  [C]ontinue\n");
        	
        printf("\t\t  [V]iew Achievements\n");
        printf("\t\t  [Q]uit\n");
        printf("\nYour choice: ");
        scanf(" %c", &choice);

        switch (choice){
            case 'N': case 'n':
            	if (!game.running)
                	newGame(idolDungeon, &game, inventory, hanamaru, achievement);
                else
                	printf("Invalid choice!\n");
                	system("pause");
			    	system("cls");
                break;
            case 'C': case 'c':
            	if (game.running == 1){
                	continueGame(idolDungeon, &game, inventory, hanamaru, achievement);
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
    
    return 0; 
}

