#include <stdio.h>
#include <stdlib.h>

int main(){
    char choice;

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
