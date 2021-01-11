#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TAILLELIST 7

///////////////PROTOTYPES/////////////////
void AffichageMachine(char (*cTab)[5], int credits);
void printBarre(int p1, int p2, int p3, int espacement);
void AffichageBienvenue();
void AffichageDebut(int jetons);
void PrintSolde(int jetons);

void DoEspacement(int number);
int enoughtCredits(int *jetons);
void CheckVictoire(char (*cTab)[5], int *jetons, char listCarac[]);

void ChangementDeCouleur(char texte[100], int couleur, int value);

//////////////MAIN///////////////
int main(){
    //Smiley / Coeur / Carreau / Trefle / Pique / Musique / Signe
    char listCarac[TAILLELIST] = {2, 3, 4, 5, 6, 14, 190};
    char ligneCarac[3][5] = { {}, {}, {} };
    char cara;
    int credits = 100;
    srand (time (NULL));

    AffichageBienvenue();
    AffichageDebut(credits);
    getch();

    // Caractere 27 = echap
    while (cara != 'e' && cara!='E' && cara!=27 && enoughtCredits(&credits)) {
        system("cls");
        for (int j=0; j<3; j++) {
            for (int i=0; i<5; i++)
                ligneCarac[j][i] = listCarac[rand()%TAILLELIST];
        }
        AffichageBienvenue();
        AffichageMachine(ligneCarac, credits);
        CheckVictoire(ligneCarac, &credits, listCarac);
        printf("\n\nSi vous souhaitez rejouer, pressez n'importe quelle touche.");
        printf("\nSi vous souhaitez quitter, tapez e.");
        cara = getch();
    }
}

//////////////FONCTIONS AFFICHAGE//////////////

void AffichageBienvenue() {
    for(int i =0; i<50; i++)
        printf("#");
    puts("\n        Bienvenue sur la machine a sous !");
    for(int i =0; i<50; i++)
        printf("#");
}

void AffichageDebut(int jetons){
    printf("\n\nVous avez %d credits pour commencer. Pressez n'importe quelle touche pour commencer.", jetons);
}

void AffichageMachine(char (*cTab)[5], int credits) {
    int espacement = 17;

    printf("\n");
    printBarre(201, 205, 187, espacement);

    for (int j=0; j<3; j++) {
        printf("\n");
        DoEspacement(espacement);
        printf("%c ", 186);
        for(int i=0; i<5;i++)
            printf("%c ", cTab[j][i]);
        printf("%c", 186);
    }

    printBarre(200, 205, 188, espacement);

    PrintSolde(credits);
}

void printBarre(int p1, int p2, int p3, int espacement){
    printf("\n");
    DoEspacement(espacement);
    printf("%c", p1);
    for(int i=0; i<11;i++)
        printf("%c", p2);
    printf("%c", p3);
}

void PrintSolde(int jetons){
    int espacement = 42, i;
    printf("\n\n");

    DoEspacement(espacement);
    printf("%c%c%c%c%c%c%c%c\n", 201, 205,205,205,205,205,205, 187);

    DoEspacement(espacement-8);
    if (jetons<10)
        printf("Solde : %c  %d   %c\n", 186, jetons, 186);
    else if (jetons>=1000)
        printf("Solde : %c %d %c\n", 186, jetons, 186);
    else if (jetons>=100)
        printf("Solde : %c %d  %c\n", 186, jetons, 186);
    else
        printf("Solde : %c  %d  %c\n", 186, jetons, 186);

    DoEspacement(espacement);
    printf("%c%c%c%c%c%c%c%c\n", 200, 205,205,205,205,205,205, 188);

}

void DoEspacement(int number) {
    for (int i=0; i<number; i++)
        printf(" ");
}

/////////////FONCTIONS SECONDAIRES/////////////////
int enoughtCredits(int *jetons) {
    int simu = *jetons;
    if ( (simu -=5) <0 ) {
        printf("\n\nVous n'avez pas assez de jetons pour continuer, veuillez remplir votre solde.\n");
        return 0;
    }
    *jetons -=5;
    return 1;
}

void CheckVictoire(char (*cTab)[5], int *jetons, char listCarac[]) {
    int compteur=0, victory=0, totalJetons=0;

    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
            if (cTab[i][j] == cTab[i][j+1])
                compteur++;
        }
        if (compteur == 4) {
            printf("\nJACKPOT ! Vous remportez 500 jetons.");
            totalJetons +=500;
            victory=1;
        }

        if(!victory) {
            for (int j=0; j<TAILLELIST; j++) {
                compteur=1;
                for (int k=0; k<5; k++) {
                    if (cTab[i][k] == listCarac[j] && cTab[i][k+1] == listCarac[j])
                        compteur++;
                }
                if(compteur>=3) {
                    totalJetons += compteur*5;
                    printf("\nVous avez une ligne de %d", compteur);
                }
            }
        }
        compteur=0;
    }

    if (!totalJetons)
        ChangementDeCouleur("\nVous avez perdu dommage.", 12, 0);
    else {
        *jetons += totalJetons;
        ChangementDeCouleur("", 10, totalJetons);
    }
}

/////////////////////////DIVERS////////////////////////

void ChangementDeCouleur(char texte[100], int couleur, int value) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, couleur);
    if (value)
        printf("\nVous remportez %d jetons.", value);
    else
        printf("%s", texte);
    SetConsoleTextAttribute(hConsole, 7);
}
