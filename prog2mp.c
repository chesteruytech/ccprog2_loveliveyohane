#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDOLS 8
#define MAX_NAME_LEN 30
#define MAX_HOSTAGES 3
#define MAX_ITEM_CHAR 50
#define MAX_INVENTORY 10

typedef char Name[MAX_NAME_LEN];

struct idolDungeonTag{
    Name idol;
    Name dungeon;
};

struct inventoryTag{
	Name item;
	int itemCount;
};

struct gameTag{
	int maxHP;
	int hp;
	int gold;
	int hostages[MAX_HOSTAGES];
	int rescuedCount[MAX_IDOLS];
	int clearStatus[MAX_HOSTAGES];
	int running;
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
	
	strcpy(inventory[1].item, "Noppo bread");
	inventory[1].itemCount = 0;
	
	strcpy(inventory[2].item, "Choco-mint ice cream");
	inventory[2].itemCount = 0;
	
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
    printf("Item on hand: N/A\n");	// ??? ("More on this later" according to specs)
    printf("\n");

    for (i = 0; i < 3; i++) {
        idx = game->hostages[i];
        
        if (game->clearStatus[i] == 1)
        	printf("[X] Visit %s\n", idolDungeon[idx].dungeon);
        else
        	printf("[%d] Visit %s\n", i+1, idolDungeon[idx].dungeon);
    }

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
	
	printf("Lailaps: These are the items you have, Yohane!\n\n");
	printf("HP: %d / %d", game->hp, game->maxHP);
	printf("\t\t\t\t");
    printf("Total Gold: %d GP\n", game->gold);
	printf("Items available\n\n");
	
	for (i = 0; i < 3; i++)
		printf("%d. %-30s \t x \t %d\n", i+1,inventory[i].item, inventory[i].itemCount);
	
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

void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[]){
	
	system("cls");
	int i;
	char choice;
	int index;
	int charIdx;
    game->hp = 3;
    game->maxHP = 3;
    game->gold = 0;
	game->running = 1;
	
	for (i = 0; i < MAX_HOSTAGES; i++) {
    	game->clearStatus[i] = 0;
	}
	
	for (i = 0; i < MAX_IDOLS; i++){
		game->rescuedCount[i] = 0;
	}
	
	selectHostages(game);
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);

    do{
    printf("Choice: ");
    scanf(" %c", &choice);
	index = choice - 49;	// for entering dungeon only, this converts '1' that is currently a char into 0, '2' into 1, etc.
	    switch (choice){
	        case '1': case '2': case '3':
	        	system("cls");
	        	if (game->clearStatus[index] == 1)
	        		printf("Dungeon is cleared. You can no longer enter\n");
	        	else{
		        	printf("Entering dungeon %d\n\n", index+1);
		        	
		        	// finish dungeon first before this
		        	charIdx = game->hostages[index]; 
		        	printf("Idol %s is rescued!\n", idolDungeon[charIdx].idol);
		        	game->rescuedCount[charIdx]++;
		        	game->clearStatus[index] = 1;
		        	
	        	}
	        	system("pause");
	            system("cls");
	            showHostages(idolDungeon, game);
    			showDungeonMenu(idolDungeon, game, inventory);
	            break;
	        case 'I': case 'i':
	        	system("cls");
	            showInventory(idolDungeon, game, inventory);
	            break;
	        case 'S': case 's':
	            printf("Game Saved\n\n"); 
	            system("pause");
	            system("cls");
	            break;
	        case 'H': case 'h':
	        	system("cls");
	            printf("Hanamaru Store\n");
	            break;
	        default:
	            printf("Invalid choice\n");
	    	}
	    	
	} while (choice != 'S' && choice != 's');

}

int main(){
	
    char choice;
	struct idolDungeonTag idolDungeon[MAX_IDOLS];
	struct gameTag game;
	struct inventoryTag inventory[MAX_INVENTORY];
	
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	
	game.running = 0;
	
    do {
        printf("\t************************************************\n");
        printf("\t*            Yohane The Parhelion!             *\n");
        printf("\t*       The Siren in the Mirror World!         *\n");
        printf("\t************************************************\n");
		
		if (!game.running)
        	printf("\t\t  [N]ew Game\n");
        else
        	printf("\t\t  [C]ontinue\n"); // NOT YET WORKING
        	
        printf("\t\t  [V]iew Achievements\n");
        printf("\t\t  [Q]uit\n");
        printf("\nYour choice: ");
        scanf(" %c", &choice);

        switch (choice){
            case 'N': case 'n':
                newGame(idolDungeon, &game, inventory);
                break;
            case 'C': case 'c':
                newGame(idolDungeon, &game, inventory); // fix later
                break;
            case 'V': case 'v':
        		system("cls");
                printf("Achievements\n");
                system("pause");
                system("cls");
                break;
            case 'Q': case 'q':
                printf("Thanks for playing!\n");
                break;
            default:
                printf("Invalid input. Please choose N, V, or Q only.\n");
                system("pause");
			    system("cls");
        }
    } while (choice != 'Q' && choice != 'q');
    
    
    return 0; 
}
