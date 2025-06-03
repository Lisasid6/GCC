#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int joueur, ordi;

    srand(time(NULL));

    printf(" Pierre -  Papier - Ciseaux\n");
    printf("Fais ton choix :\n");
    printf("1 - Pierre\n");
    printf("2 - Papier\n");
    printf("3 - Ciseaux\n");
    printf("Ton choix : ");
    scanf("%d", &joueur);

    ordi = rand() % 3 + 1;

    char *options[] = {"", "Pierre", "Papier", "Ciseaux"};
    printf("Toi : %s\n", options[joueur]);
    printf("Ordinateur : %s\n", options[ordi]);

    if (joueur == ordi) {
        printf("galité !\n");
    } else if (
        (joueur == 1 && ordi == 3) ||
        (joueur == 2 && ordi == 1) ||
        (joueur == 3 && ordi == 2)
    ) {
        printf("Tu gagnes !\n");
    } else {
        printf("Tu perds !\n");
    }

    return 0;
}
