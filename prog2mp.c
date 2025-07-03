#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDOLS 8
#define MAX_NAME_LEN 30
#define MAX_HOSTAGES 3

typedef char Name[MAX_NAME_LEN];

struct idolDungeonTag{
    Name idol;
    Name dungeon;
};

struct gameTag{
	int hp;
	int gold;
	int hostages[MAX_HOSTAGES];
	int rescuedCount[MAX_IDOLS];
	int clearStatus[MAX_HOSTAGES];
	int running;
};

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

void showDungeonMenu(struct idolDungeonTag idolDungeon[], struct gameTag *game){
	
	int i, idx;
	
    printf("Lailaps: Yohane! Where should we go to now?\n\n");
    printf("HP: %d / 3", game->hp);
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
	printf("[S]ave and Quit\n");
   
}

void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game){
	
	system("cls");
	int i;
	char choice;
    game->hp = 3;
    game->gold = 0;
	game->running = 1;
	
	for (i = 0; i < MAX_HOSTAGES; i++) {
    	game->clearStatus[i] = 0;
	}
	
	selectHostages(game);
    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game);

    do{
    printf("Choice: ");
    scanf(" %c", &choice);

	    switch (choice){
	        case '1': case '2': case '3':
	        	system("cls");
	        	printf("Entering dungeon\n\n");
	        	system("pause");
	            system("cls");
	            showHostages(idolDungeon, game);
    			showDungeonMenu(idolDungeon, game);
	            break;
	        case 'I': case 'i':
	        	system("cls");
	            printf("Inventory\n\n");
	            system("pause");
	            system("cls");
	            showHostages(idolDungeon, game);
    			showDungeonMenu(idolDungeon, game);
	            break;
	        case 'S': case 's':
	            printf("Game Saved\n\n"); 
	            system("pause");
	            system("cls");
	            break;
	        default:
	            printf("Invalid choice\n\n");
	            system("pause");
	            system("cls");
	            showHostages(idolDungeon, game);
    			showDungeonMenu(idolDungeon, game);
	    	}
	    	
	} while (choice != 'S' && choice != 's');

}

int main(){
	
    char choice;
	
	struct idolDungeonTag idolDungeon[MAX_IDOLS] = {
			{"Chika", "Yasudaya Ryokan"},
			{"Riko", "Numazu Deep Sea Aquarium"},
			{"You", "Izu-Mito Sea Paradise"},
			{"Hanamaru", "Shougetsu Confectionary"},
			{"Ruby", "Nagahama Castle Ruins"},
			{"Dia", "Numazugoyotei"},
			{"Kanan", "Uchiura Bay Pier"},
			{"Mari", "Awashima Marine Park"}
			};	
	
	struct gameTag game;
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
                newGame(idolDungeon, &game);
                break;
            case 'C': case 'c':
                newGame(idolDungeon, &game); // fix later
                break;
            case 'V': case 'v':
                printf("Achievements\n");
                system("pause");
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
