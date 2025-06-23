#include <stdio.h>

int main(){
	
    char choice;
    int quit = 0;

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
                quit = 1;
                break;
            default:
                printf("Invalid input. Please choose N, V, or Q.\n");
        }
    } while (!quit);

    return 0;
}
