#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COULEURS 8
#define ESSAIS_MAX 10

void verif_guess(const int guess[], const int secret[], int bienpasbien[]) {
    int temp_secret[4];
    int temp_guess[4];
    
    for (int i = 0; i < 4; i++) {
        temp_secret[i] = 0;
        temp_guess[i] = 0;
    }
    
    bienpasbien[0]=0;
    bienpasbien[1]=0;
    
    for (int i = 0; i < 4; i++) {
        if (guess[i] == secret[i]) {
            bienpasbien[0]++;
            temp_secret[i] = 1;
            temp_guess[i] = 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (!temp_guess[i]) {
            for (int j = 0; j < 4; j++) {
                if (!temp_secret[j] && guess[i] == secret[j]) {
                    bienpasbien[1]++;
                    temp_secret[j] = 1;
                    temp_guess[i] = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    int secret[4];
    int choix[4];
    
    for (int i = 0; i < 4; i++) {
        secret[i] = rand() % COULEURS;
    }
    
    printf("Bienvenue au jeu du MASTERMIND\n");
    // printf("le secret est %d %d %d %d\n",secret[0],secret[1],secret[2],secret[3]);
    printf("Trouve les 4 chiffres corrects en moins de %d essais, les chiffres varient entre 0 et %d", ESSAIS_MAX, COULEURS - 1);
    
    int win = 0;
    for (int attempt = 1; attempt <= ESSAIS_MAX; attempt++) {
        int bienpasbien[2]; // [0] = bien et [1] = pas bon endroit
        bienpasbien[0]=0;
        bienpasbien[1]=0;
        
        printf("Essai n°%d - Format: X X X X\n", attempt);
        scanf("%d %d %d %d", &choix[0], &choix[1], &choix[2], &choix[3]);
        
        verif_guess(choix, secret, bienpasbien);
        
        printf("\nBien: %d\nMal: %d\n\n", bienpasbien[0], bienpasbien[1]);
        
        if (bienpasbien[0] == 4) { // si 4 bien
            win = 1;
            if(attempt==1){
                printf("GG t'as gagné en %d essai! 1 chance sur 2401\n", attempt);
            }else{
                printf("GG t'as gagné en %d essais!\n", attempt);
            }
            break;
        }
    }
    
    if (!win) {
        printf("À court d'essais :(\n");
        printf("Le code secret etait: %d %d %d %d\n", secret[0], secret[1], secret[2], secret[3]);
    }
    
    return 0;
}
