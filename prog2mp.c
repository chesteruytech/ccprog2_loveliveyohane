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

// IDOLS TO HANAMARU SHOP RATIO. DO NOT TOUCH!!!
#define SHOVEL_UP 2
#define BAT_TAMER 3
#define AIR_SHOES 4
#define STEWSHINE 5
#define MIKAN_MOCHI 6
#define KURO_MACHA 7 
#define ICE_CREAM 8

typedef char Name[MAX_NAME_LEN];

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
			
			// this converts '1' that is currently a char into integer 0, '2' into integer 1, etc.
			index = choice - '1'; 
			
			// Noppo Bread bc unlimited
		    if (index == 1){  
		        if (game->gold >= hanamaru[index].price){
					game->gold -= hanamaru[index].price;
					inventory[index].itemCount++;
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
			
			// For all other items not named Noppo Bread (since everything else is a one-time purchase) (index 0 and 2-8)
			else{ 
		        if (game->gold >= hanamaru[index].price && hanamaru[index].availability == 1){
		            game->gold -= hanamaru[index].price;
		            inventory[index].itemCount++;
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

void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game, struct inventoryTag inventory[], struct hanamaruTag hanamaru[]){
	
	system("cls");
	
	// feel free to change these around if you want to test something, but make sure to revert it back when done testing
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
	
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	initializeHanamaru(hanamaru);
	
	selectHostages(game);
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game, inventory);

    do{
    	
	    printf("Choice: ");
	    scanf(" %c", &choice);
		
		// I put "index = choice - '1'" inside bc the index is only needed for numerical inputs	
		if (choice >= '1' && choice <= '3'){
		
			// for entering dungeon only, this converts '1' that is currently a char into 0, '2' into 1, etc. 
			index = choice - '1';	
			
			system("cls");
        	if (game->clearStatus[index] == 1)
        		printf("Dungeon is cleared. You can no longer enter\n");
        	else{
	        	printf("Entering dungeon %d\n\n", index+1);
	        	
	        	// finish dungeon first before this
	        	charIdx = game->hostages[index]; 
	        	printf("%s has been successfully rescued!\n", idolDungeon[charIdx].idol);
	        	game->rescuedCount[charIdx]++;
	        	game->clearStatus[index] = 1;
	        	
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
			printf("Game Saved\n\n"); 
			system("pause");
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

int main(){
	
	srand(time(NULL));
    char choice;
	struct idolDungeonTag idolDungeon[MAX_IDOLS];
	struct gameTag game;
	struct inventoryTag inventory[MAX_INVENTORY];
	struct hanamaruTag hanamaru[MAX_HANAMARU];
	
	initializeIdolDungeon(idolDungeon);	
	initializeInventory(inventory);
	initializeHanamaru(hanamaru);
	
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
                newGame(idolDungeon, &game, inventory, hanamaru);
                break;
            case 'C': case 'c':
                newGame(idolDungeon, &game, inventory, hanamaru); // fix later
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

