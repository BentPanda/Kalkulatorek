#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 9999

int sprawdz_znaki(const char *tekst) {
    for (int i = 0; tekst[i]; i++) {
        if (!isdigit(tekst[i]) && !isspace(tekst[i])) {
            return 0;
        }
    }
    return 1;
}

int sprawdz_spacje(const char *tekst) {
    int licznik_spacji = 0;
    for (int i = 0; tekst[i]; i++) {
        if (tekst[i] == ' ') {
            licznik_spacji++;
        }
    }
    return licznik_spacji == 1;
}


int podziel_wejscie(const char *tekst, char *pierwsza, char *druga) {
    const char *pozycja_spacji = strchr(tekst, ' ');
    if (pozycja_spacji == NULL) {
        return 0;
    }
    strncpy(pierwsza, tekst, pozycja_spacji - tekst);
    pierwsza[pozycja_spacji - tekst] = '\0';
    strcpy(druga, pozycja_spacji + 1);
    return 1;
}

void mnozenie(const char *pierwsza, const char *druga, char *wynik) {
    int dlugosc1 = strlen(pierwsza), dlugosc2 = strlen(druga);
    int max_dlugosc = dlugosc1 + dlugosc2;

    memset(wynik, '0', max_dlugosc);
    wynik[max_dlugosc] = '\0';

    for (int i = dlugosc1 - 1; i >= 0; i--) {
        for (int j = dlugosc2 - 1; j >= 0; j--) {
            int cyfra1 = pierwsza[i] - '0', cyfra2 = druga[j] - '0';
            int idx = i + j + 1;

            int iloczyn = cyfra1 * cyfra2 + (wynik[idx] - '0');
            wynik[idx] = (iloczyn % 10) + '0';
            wynik[idx - 1] += iloczyn / 10;
        }
    }
}

int sprawdz_wejscie(const char *tekst) {
    if (!sprawdz_znaki(tekst)) {
        printf("Błąd: Niedozwolone znaki.\n");
        return 0;
    }
    if (!sprawdz_spacje(tekst)) {
        printf("Błąd: Podaj dokładnie dwie liczby oddzielone spacjom.\n");
        return 0;
    }
    return 1;
}


int sprawdz_zera(const char *liczba) {
    if (liczba[0] == '0' && strlen(liczba) > 1) {
        printf("Błąd: Liczba nie moze zaczynac sie od 0.\n");
        return 0;
    }
    if (strcmp(liczba, "0") == 0) {
        printf("Błąd: Liczba nie moze byc 0 (bo wyjdzie 0 i to bendzie marnotractwo prondu).\n");
        return 0;
    }
    return 1;
}

int main() {
    char wejscie[MAX_INPUT];
    char pierwsza[MAX_INPUT], druga[MAX_INPUT];
    char wynik[MAX_INPUT * 2];

    printf("Podaj dwie liczby oddzielone spacjom: ");
    if (!fgets(wejscie, MAX_INPUT, stdin)) {
        printf("Błąd odczytu danych.\n");
        return 1;
    }

    wejscie[strcspn(wejscie, "\n")] = '\0';

    if (!sprawdz_wejscie(wejscie)) {
        return 1;
    }

    if (!podziel_wejscie(wejscie, pierwsza, druga)) {
        printf("Błąd podczas przetwarzania wejscia.\n");
        return 1;
    }

    if (!sprawdz_zera(pierwsza) || !sprawdz_zera(druga)) {
        return 1;
    }
    mnozenie(pierwsza, druga, wynik);
    int indeks = 0;
    while (wynik[indeks] == '0' && wynik[indeks + 1]) {
        indeks++;
    }
    printf("Wynik: %s\n", wynik + indeks);

    return 0;
}
