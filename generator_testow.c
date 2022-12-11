#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef WIERSZE
#define WIERSZE 8
#endif

#ifndef KOLUMNY
#define KOLUMNY 8
#endif

#ifndef DLUGOSC
#define DLUGOSC 5
#endif

#define MALE_A 97 // mala litera 'a' w ASCII

int main(void) {

    srand((unsigned) time(NULL));

    int ile = WIERSZE * KOLUMNY;
    int x;
    char tab[ile];
    int i = 0;

    while(i < ile) {
        for(int j = 0; j < KOLUMNY; j++) {
            for(int k = 0; k < WIERSZE; k++) {
                tab[i] = MALE_A + j;
                i++;
            }
        }
    }

    for(int i = 0; i < ile; i++) {
        do
        {
            x = (int) (rand() / (RAND_MAX + 1.0) * ile);
        } while (tab[x] == 0);
        printf("%c\n", tab[x]);
        tab[x] = 0;
    }
    
    printf(".\n");

    return 0;
}