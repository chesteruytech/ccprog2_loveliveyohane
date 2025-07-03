#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDOLS 8
#define MAX_NAME_LEN 30

typedef char Name[MAX_NAME_LEN];

struct idolDungeonTag{
    Name idol;
    Name dungeon;
};

typedef struct idolDungeonTag idolDungeon[MAX_IDOLS];

int main(){
    char choice;

idolDungeon dataList = {
		{"Chika", "Yasudaya Ryokan"},
		{"Riko", "Numazu Deep Sea Aquarium"},
		{"You", "Flame Temple"},
		{"Hanamaru", "Mirror Lake"},
		{"Ruby", "Starfall Ruins"},
		{"Dia", "Frozen Vault"},
		{"Kanan", "Thunder Keep"},
		{"Mari", "Dark Mirror Core"}
		};	
	
    do {
        printf("\t************************************************\n");
        printf("\t*            Yohane The Parhelion!             *\n");
        printf("\t*       The Siren in the Mirror World!         *\n");
        printf("\t************************************************\n");

        printf("\t\t  [N]ew Game\n");	
        printf("\t\t  [V]iew Achievements\n");
        printf("\t\t  [Q]uit\n");
        printf("\nYour choice: ");
        scanf(" %c", &choice);

        switch (choice){
            case 'N': case 'n':
                printf("New game\n");
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
