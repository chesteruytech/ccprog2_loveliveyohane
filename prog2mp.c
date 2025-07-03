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
	int running;
};

void showHostages(struct idolDungeonTag idolDungeon[], struct gameTag *game){

	int i, idx;
	
	printf("Hostages: \n");
    for (i = 0; i < 3; i++){
        idx = game->hostages[i];
        printf("%s in %s\n", idolDungeon[idx].idol, idolDungeon[idx].dungeon);
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
        printf("[%d] Visit %s\n", i+1, idolDungeon[idx].dungeon); // [X] if already cleared
    }

    printf("\n[I]nventory");
    printf("\t\t");
	printf("[S]ave and Quit\n");
   
}

void newGame(struct idolDungeonTag idolDungeon[], struct gameTag *game){
	
    game->hp = 3;
    game->gold = 0;

    int used[MAX_IDOLS] = {0};
    int selected = 0;
	char choice;
	
    while (selected < MAX_HOSTAGES){
        int index = rand() % MAX_IDOLS;
        if (used[index] == 0){
            used[index] = 1;
            game->hostages[selected] = index;	// randomly selected indexes go to hostage array
            selected++;
        }
    }

    showHostages(idolDungeon, game);
    showDungeonMenu(idolDungeon, game);

    do{
    printf("Choice: ");
    scanf(" %c", &choice);

	    switch (choice){
	        case '1': case '2': case '3':
	            printf("Entering Dungeon %c\n", choice);
	            break;
	        case 'I': case 'i':
	            printf("Inventory\n");
	            break;
	        case 'S': case 's':
	            printf("Game Saved\n"); // save to file afterwards
	            break;
	        default:
	            printf("Invalid choice\n");
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
		
		if (game.running == 0)
        	printf("\t\t  [N]ew Game\n");
        else
        	printf("\t\t  [C]ontinue\n");
        printf("\t\t  [V]iew Achievements\n");
        printf("\t\t  [Q]uit\n");
        printf("\nYour choice: ");
        scanf(" %c", &choice);

        switch (choice){
            case 'N': case 'n':
            	game.running = 1;
                newGame(idolDungeon, &game);
                break;
            case 'C': case 'c':
                newGame(idolDungeon, &game); // fix later
                break;
            case 'V': case 'v':
                printf("Achievements\n");
                break;
            case 'Q': case 'q':
                printf("Quit\n");
                return 0;
            default:
                printf("Invalid input. Please choose N, V, or Q only.\n");
                system("pause");
			    system("cls");
        }
    } while (choice != 3);
}

