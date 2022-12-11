#include <stdio.h>

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
#define KRESKA 45 // myslnik '-' w ASCII
#define JEDYNKA 49 // jedynka '1' w ASCII
#define KROPKA 46 // kropka '.' w ASCII

#define ZAKRES 2 * DLUGOSC - 1 
// zakres, w jakich musimy sprawdzac palindromy dla danego ruchu
// (szczegolowe wyjasnienie nizej)

void print_tab(char A[][KOLUMNY], int m) { 
    // printuje tablice dwuwymiarowa A razem z indeksami a,b,c,d... na dole
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < KOLUMNY; j++) {
            printf(" %c", A[i][j]);
        }
        printf("\n");
    }
    
    for (int j = 0; j < KOLUMNY; j++) {
        printf(" %c", MALE_A + j);
    }
    printf("\n");
}

void start(char A[][KOLUMNY], int m) { 
    // wypelnia tablice A kreskami (stan poczatkowy)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < KOLUMNY; j++) {
            A[i][j] = KRESKA;
        }
    }
}

void zerowanie(int A[], int n) { 
    // zeruje tablice A
    for (int i = 0; i < n; i++) {
        A[i] = 0;
    }
}

/* Ponizej znajduja sie cztery funkcje zczytujace fragmenty tablicy.
Idea polega na tym, ze kazda funkcja zczytuje tylko 'symetryczne sasiedztwo'
pozycji A[w][k], czyli tworzy taka tablice tab[ZAKRES], ze wyraz A[w][k]
znajduje sie dokladnie na srodku tej tablicy, a po lewej i prawej stronie
ma dokladnie DLUGOSC - 1 elementow. Taka tablica zawiera wszystkie podciagi
dlugosci DLUGOSC zawierajace A[w][k] i zostanie potem uzyta do sprawdzenia,
czy zawiera palindrom dlugosci DLUGOSC zawierajacy A[w][k]. Dla ulatwienia,
jesli przy tworzeniu takiej tablicy wyjdziemy poza zakres, bo np. A[w][k]
znajduje sie gdzies przy krancu tablicy, wpisujemy znak "-" do tablicy. */

void zczytaj_przekatna(
    char przekatna[], int n, char A[][KOLUMNY], int w, int k) { 
    // wpisuje fragment przekatnej przechodzacej przez A[w][k] do tablicy
    // 'przekatna' o rozmiarze n (= ZAKRES)
    int w_pocz = w - (DLUGOSC - 1);
    int k_pocz = k - (DLUGOSC - 1);
    for (int i = 0; i < n; i++) {
        if (w_pocz + i < 0 || w_pocz + i >= WIERSZE || 
            k_pocz + i < 0 || k_pocz + i >= KOLUMNY) {
            przekatna[i] = KRESKA;
        }
        else {
            przekatna[i] = A[w_pocz + i][k_pocz + i];
        }
    }
}

void zczytaj_antyprz(
    char antyprzekatna[], int n, char A[][KOLUMNY], int w, int k) { 
    // wpisuje fragment antyprzekatnej przechodzacej przez A[w][k] 
    // do tablicy 'antyprzekatna' o rozmiarze n (= ZAKRES)
    int w_pocz = w - (DLUGOSC - 1);
    int k_pocz = k + (DLUGOSC - 1);
    for (int i = 0; i < n; i++) {
        if (w_pocz + i < 0 || w_pocz + i >= WIERSZE || 
            k_pocz - i < 0 || k_pocz - i >= KOLUMNY) {
            antyprzekatna[i] = KRESKA;
        }
        else {
            antyprzekatna[i] = A[w_pocz + i][k_pocz - i];
        }
    }
}

void zczytaj_kolumne(char kolumna[], int n, char A[][KOLUMNY], int w, int k) { 
    // wpisuje fragment kolumny 'k' z tablicy A do tablicy 'kolumna' 
    // o rozmiarze n (= ZAKRES)
    int pocz = w - (DLUGOSC - 1);
    for (int i = 0; i < n; i++) {
        if (pocz + i < 0 || pocz + i >= WIERSZE) {
            kolumna[i] = KRESKA;
        }
        else {
            kolumna[i] = A[pocz + i][k];
        }
    }
}

void zczytaj_wiersz(char wiersz[], int n, char A[][KOLUMNY], int w, int k) { 
    // wpisuje fragment wiersza 'w' z tablicy A do tablicy 'wiersz' 
    // o rozmiarze n (= ZAKRES)
    int pocz = k - (DLUGOSC - 1);
    for (int i = 0; i < n; i++) {
        if (pocz + i < 0 || pocz + i >= KOLUMNY) {
            wiersz[i] = KRESKA;
        }
        else {
            wiersz[i] = A[w][pocz + i];
        }
    }
}

/* Zamiast funkcji boolowskich uzywam funkcji int, gdzie wartosc '0' oznacza
falsz, a wartosc '1' oznacza prawde. */

int spr_palindrom(char tab[]) { 
    // sprawdza, czy w tablicy 'tab' o dlugosci ZAKRES (= 2*DLUGOSC-1)
    // znajduje sie palindrom dlugosci DLUGOSC
     int pocz, koniec;
     for (int i = 0; i < DLUGOSC; i++) {
        pocz = i; 
        // palindrom musi zaczynac sie w przedziale od 0 do DLUGOSC - 1
        koniec = i + DLUGOSC - 1;
        // a konczyc w przedziale od DLUGOSC - 1 do 2*DLUGOSC - 2
        while (pocz < koniec && 
               tab[pocz] == tab[koniec] && tab[pocz] != KRESKA) {
            // jestesmy w petli dopoki nie mamy pewnosci czy w przedziale
            // od 'i' do 'i + DLUGOSC - 1' znajduje sie palindrom (czy nie)
            pocz++;
            koniec--;
        }
        if (pocz >= koniec && tab[pocz] != KRESKA) {
            // to znaczy ze w przedziale od 'i' do 'i + DLUGOSC - 1' faktycznie
            // jest palindrom
            return 1;
        }
     }

     return 0;
}

int czy_wygrana(char A[][KOLUMNY], int w, int k) { 
    // sprawdza czy nastepuje wygrana
    char tab[ZAKRES];
    
    zczytaj_kolumne(tab, ZAKRES, A, w, k);
    if (spr_palindrom(tab)) return 1;
    
    zczytaj_wiersz(tab, ZAKRES, A, w, k);
    if (spr_palindrom(tab)) return 1;
    
    zczytaj_przekatna(tab, ZAKRES, A, w, k);
    if (spr_palindrom(tab)) return 1;

    zczytaj_antyprz(tab, ZAKRES, A, w, k);
    if (spr_palindrom(tab)) return 1;

    return 0;
}

int main(void) {

    char A[WIERSZE][KOLUMNY]; // plansza
    int licznik[KOLUMNY]; 
    // liczy ile miejsc juz jest zajetych w poszczegolnych kolumnach

    zerowanie(licznik, KOLUMNY);
    start(A, WIERSZE);

    char czyj_ruch = JEDYNKA + 1;
    char jaki_ruch;
    int kolumna; // kolumna w ktorej nalezy wykonac ruch
    int wiersz; // wiersz w ktorym nalezy wykonac ruch

    do {
        czyj_ruch = (char) (2 * JEDYNKA - czyj_ruch + 1); 
        // na przemian JEDYNKA i JEDYNKA + 1, czyli '1' i '2' w ASCII
        print_tab(A, WIERSZE);
        printf("%c:", czyj_ruch);
        scanf(" %c", &jaki_ruch);
        printf("\n");
        if (jaki_ruch != KROPKA) {
            kolumna = jaki_ruch - MALE_A;
            wiersz = WIERSZE - 1 - licznik[kolumna];
            A[wiersz][kolumna] = czyj_ruch;
            licznik[kolumna]++;
        }
    } while (jaki_ruch != KROPKA && !czy_wygrana(A, wiersz, kolumna));

    if(jaki_ruch != KROPKA) { // jesli nastapila wygrana
        print_tab(A, WIERSZE);
        printf("%c!\n", czyj_ruch);
    }

    return 0;
}
