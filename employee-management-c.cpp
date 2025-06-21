#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Angajat {
    char nume[50];
    int cod;
    float salariu;
};

void adaugaAngajat();
void afiseazaAngajati();
void cautaAngajat();
void actualizeazaAngajat();
void actualizeazaAngajatiPeSalariu();
void stergeAngajat();
void reseteazaBazaDeDate();
void genereazaRaportAngajati();
void genereazaRaportSalariu();
void afiseazaAngajatSalariu();
void curataBuffer();
void afiseazaMeniu();

int main() {
    afiseazaMeniu();
    return 0;
}

void curataBuffer() {
    while (getchar() != '\n');
}
// functia principala care afiseaza meniul si dirijeaza executia pe baza optiunii introduse de utilizator
void afiseazaMeniu() {
    int optiune;
    printf("\n--- MENIU ---\n");
    printf("1. Adauga angajat nou\n");
    printf("2. Afiseaza toti angajatii\n");
    printf("3. Cauta un angajat\n");
    printf("4. Actualizeaza date angajat\n");
    printf("5. Aplica marire de 10%% la salariile sub un prag\n");
    printf("6. Sterge angajat\n");
    printf("7. Genereaza raport cu toti angajatii\n");
    printf("8. Genereaza raport cu angajatii care au salariul peste un prag\n");
    printf("9. Afiseaza un angajat cu salariu peste un prag\n");
    printf("10. Iesire\n");
    printf("11. Reseteaza baza de date\n");
    printf("Introduceti optiunea: ");
    if (scanf("%d", &optiune) != 1) {
        printf("Eroare la citirea optiunii!\n");
        curataBuffer();
        return;
    }
    curataBuffer();

    switch (optiune) {
    case 1: adaugaAngajat(); break;
    case 2: afiseazaAngajati(); break;
    case 3: cautaAngajat(); break;
    case 4: actualizeazaAngajat(); break;
    case 5: actualizeazaAngajatiPeSalariu(); break;
    case 6: stergeAngajat(); break;
    case 7: genereazaRaportAngajati(); break;
    case 8: genereazaRaportSalariu(); break;
    case 9: afiseazaAngajatSalariu(); break;
    case 10:
        printf("\nVa multumim ca ati folosit aplicatia!\n");
        return;
    case 11: reseteazaBazaDeDate(); break;
    default:
        printf("Optiune invalida! Incercati din nou.\n");
    }
    afiseazaMeniu();
}
// functie pt adaugarea unui angajat nou in fisierul binar
void adaugaAngajat() {
    FILE* f;          //pointer catre un fisier//
    struct Angajat a;                                            //Creezi o variabila a de tipul Angajat (cu 3 campuri: nume, cod, salariu)
    f = fopen("angajati.dat", "ab"); //deschide/creeaza fisierul angajati.dat si scrie la final nu il suprascrie

    if (!f) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    printf("\n--- Adaugare Angajat ---\n");

    while (1) { //loop infinit din care se iese doar la break
        printf("Introduceti numele angajatului: ");
        if (fgets(a.nume, sizeof(a.nume), stdin) == NULL) {
            printf("Eroare la citirea numelui!\n");
            fclose(f);
            return;
        }
        a.nume[strcspn(a.nume, "\n")] = 0; //scot enter ul de la finalul numelui

        printf("Introduceti codul angajatului: ");
        while (scanf("%d", &a.cod) != 1) {
            printf("Eroare la citirea codului! Introduceti un numar valid: ");
            curataBuffer();
        }

        printf("Introduceti salariul angajatului: ");
        while (scanf("%f", &a.salariu) != 1) {
            printf("Eroare la citirea salariului! Introduceti un numar valid: ");
            curataBuffer();
        }

        fwrite(&a, sizeof(a), 1, f);
        printf("Angajat adaugat cu succes!\n");

        printf("Doriti sa adaugati un alt angajat? (y/n): ");
        char raspuns;
        if (scanf("%f", &a.salariu) != 1) {                                                     //AICI AM O GRESEALA ==> IN LOC DE "%f" ar trebui sa am " %c" si in loc de "salariu" sa fie "raspuns"
            printf("Eroare la citirea salariului!\n"); // si aici la fel, ar trebui sa scrie "raspunsului"
            curataBuffer();
            return;
        }
        curataBuffer();
        if (raspuns != 'y' && raspuns != 'Y') {
            break;
        }
    }

    fclose(f); //se salveaza tot ce am scris si se elibereaza fisierul
}
// functie pt afisarea tuturor angajatilor existenti
void afiseazaAngajati() {  //declar o functie care nu primeste parametrii si nu declara nimic
    FILE* f;    //Creez un pointer de tip FILE, adică o legătură cu un fișier de pe disc
    struct Angajat a;
    f = fopen("angajati.dat", "rb");

    if (!f) {
        perror("Eroare la deschiderea fisierului"); //perror inseamna motivul esuarii de la sistem
        return;
    }

    printf("\n--- Lista Angajati ---\n");
    int contor = 0; //variabila folosita pentru a afisa cati anagajati sunt in disier iar la inceput e 0, daca nu exista angajati, aceasta ramane 0
    while (fread(&a, sizeof(a), 1, f) == 1) {
        printf("\nNume: %s", a.nume);
        printf("\nCod: %d", a.cod);
        printf("\nSalariu: %.2f\n", a.salariu); //2f adica se afiseaza cu 2 zecimale
        contor++; //asta inseamna ca dupa ce ai afisat un angajat, maresti contorul cu 1
    }

    if (contor == 0)
        printf("Nu exista angajati inregistrati momentan.\n");

    fclose(f);
}
// functie pt cautarea unui angajat dupa cod
void cautaAngajat() {
    FILE* f;
    struct Angajat a; //a este variabila in car vom citi fiecare angajat
    int codCautat, gasit = 0;
    f = fopen("angajati.dat", "rb");

    if (!f) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    printf("\n--- Cautare Angajat ---\n");
    printf("Introduceti codul angajatului cautat: ");
    while (scanf("%d", &codCautat) != 1) {
        printf("Eroare la citirea codului! Introduceti un numar valid: ");
        curataBuffer();
    }

    while (fread(&a, sizeof(a), 1, f) == 1) {
        if (a.cod == codCautat) {
            printf("\nAngajat gasit!\n");
            printf("Nume: %s\n", a.nume);
            printf("Cod: %d\n", a.cod);
            printf("Salariu: %.2f\n", a.salariu);
            gasit = 1;
            break;
        }
    }

    if (!gasit)
        printf("Angajatul cautat nu a fost gasit in baza de date.\n");

    fclose(f);
}
// functie pentru actualizarea datelor unui angajat existent
void actualizeazaAngajat() {
    FILE* f;
    struct Angajat a; //in variabila a citești fiecare angajat, îl modifici, apoi îl rescrii.
    int codActualizat, gasit = 0;
    f = fopen("angajati.dat", "rb+"); // rb+ inseamna read + write - asta inseamna ca pot citi si apoi scrie/modifica fara sa inchid fisierul

    if (!f) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    printf("\n--- Actualizare Angajat ---\n");
    printf("Introduceti codul angajatului de actualizat: ");
    while (scanf("%d", &codActualizat) != 1) {
        printf("Eroare la citirea codului! Introduceti un numar valid: ");
        curataBuffer();
    }
    int ch = getchar(); //este la fel ca curataBuffer 
    if (ch == EOF) {
        printf("Eroare la citirea caracterului!\n");
        return;
    }
    int ch = getchar(); //este la fel ca curataBuffer
    if (ch == EOF) {
        printf("Eroare la citirea caracterului!\n");
        return;
    }
    while (fread(&a, sizeof(a), 1, f) == 1) {
        if (a.cod == codActualizat) {
            printf("Introduceti numele nou: ");
            if (fgets(a.nume, sizeof(a.nume), stdin) == NULL) {
                printf("Eroare la citirea numelui!\n");
                fclose(f);
                return;
            }
            a.nume[strcspn(a.nume, "\n")] = 0;

            printf("Introduceti noul salariu: ");
            while (scanf("%f", &a.salariu) != 1) {
                printf("Eroare la citirea salariului! Introduceti un numar valid: ");
                curataBuffer();
            }

            if (fseek(f, -(long)sizeof(a), SEEK_CUR) != 0) {   // fseek -->Te întorci cu cursorul în fișier exact unde era angajatul pe care tocmai l-ai citit. ==> SEEK_CUR = pozitia curenta
                //-(long)sizeof(a) mergi inapoi exact o structura pt ca vrei să rescrii angajatul exact la locul lui, nu să adaugi la final.
                printf("Eroare la pozitionarea fisierului!\n");
                fclose(f);
                return;
            }
            fwrite(&a, sizeof(a), 1, f);
            printf("Datele angajatului au fost actualizate cu succes!\n");
            gasit = 1;
            break;
        }
    }

    if (!gasit)
        printf("Angajatul nu a fost gasit in baza de date.\n");

    fclose(f);
}
// functie pentru actualizarea datelor unui angajat existent, aplica marire de 10% la salariile sub un prag
void actualizeazaAngajatiPeSalariu() {
    FILE* f, * temp;
    struct Angajat a;
    float prag;
    int gasit = 0;

    f = fopen("angajati.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (!f || !temp) { //Verifici dacă oricare dintre fișiere nu s-a deschis
        perror("Eroare la deschiderea fisierului");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    printf("\n--- Actualizare Angajati cu salariu sub prag ---\n");
    printf("Introduceti pragul salariului: ");
    while (scanf("%f", &prag) != 1) {
        printf("Valoare invalida! Introduceti un numar valid: ");
        curataBuffer();
    }
    curataBuffer();

    while (fread(&a, sizeof(a), 1, f) == 1) {
        if (a.salariu < prag) {
            a.salariu *= 1.10f; // creste salariul cu 10%
            printf("Salariul angajatului %s (cod %d) a fost actualizat la %.2f\n",
                a.nume, a.cod, a.salariu);
            gasit = 1;
        }
        fwrite(&a, sizeof(a), 1, temp);
    }

    fclose(f);
    fclose(temp);

    if (remove("angajati.dat") != 0 || rename("temp.dat", "angajati.dat") != 0) {
        perror("Eroare la actualizarea fisierului");
        return;
    }

    if (gasit)
        printf("Salariile au fost actualizate cu succes!\n");
    else
        printf("Nu exista angajati cu salariul sub pragul stabilit.\n");
}
// functie care sterge un angajat din baza de date dupa cod
void stergeAngajat() {
    FILE* f, * temp;
    struct Angajat a;
    int codSters, gasit = 0;

    f = fopen("angajati.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (!f || !temp) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    printf("\n--- Stergere Angajat ---\n");
    printf("Introduceti codul angajatului de sters: ");
    while (scanf("%d", &codSters) != 1) {
        printf("Eroare la citirea codului! Introduceti un numar valid: ");
        curataBuffer();
    }

    while (fread(&a, sizeof(a), 1, f) == 1) {
        if (a.cod != codSters)
            fwrite(&a, sizeof(a), 1, temp);
        else
            gasit = 1;
    }

    fclose(f);
    fclose(temp);

    if (remove("angajati.dat") != 0 || rename("temp.dat", "angajati.dat") != 0) {
        perror("Eroare la actualizarea fisierului");
        return;
    }

    if (gasit)
        printf("Angajat sters cu succes!\n");
    else
        printf("Angajatul nu a fost gasit.\n");
}
// functie care sterge complet fisierul cu angajati (resetare baza de date)
void reseteazaBazaDeDate() {
    char confirmare;
    printf("Sunteti sigur ca doriti sa resetati baza de date? (y/n): ");
    confirmare = getchar();
    int ch = getchar();
    if (ch == EOF) {
        printf("Eroare la citirea caracterului!\n");
        return;
    }
    if (confirmare == 'y' || confirmare == 'Y') {
        if (remove("angajati.dat") == 0)
            printf("Baza de date a fost resetata cu succes.\n");
        else
            perror("Eroare la resetarea bazei de date");
    }
    else {
        printf("Resetarea bazei de date a fost anulata.\n");
    }
}
// functie care genereaza un raport text cu toti angajatii
void genereazaRaportAngajati() {
    FILE* f = fopen("angajati.dat", "rb");
    FILE* raport = fopen("raport_angajati.txt", "w");
    struct Angajat a;
    int total = 0;

    if (!f || !raport) {
        perror("Eroare la deschiderea fisierului");
        if (f) fclose(f);
        if (raport) fclose(raport);
        return;
    }

    while (fread(&a, sizeof(a), 1, f) == 1) {
        fprintf(raport, "Nume: %s\nCod: %d\nSalariu: %.2f\n\n", a.nume, a.cod, a.salariu);
        total++;
    }

    fclose(f);
    fclose(raport);

    FILE* verificare = fopen("raport_angajati.txt", "r");
    if (verificare != NULL) {
        fclose(verificare);
        if (total > 0)
            printf("Raport generat cu succes in 'raport_angajati.txt'. Total angajati: %d\n", total);
        else
            printf("Raportul a fost creat, dar nu s-au gasit angajati in baza de date.\n");
    }
    else {
        printf("Eroare: fisierul 'raport_angajati.txt' nu a fost creat.\n");
    }
}
// functie care genereaza un raport text doar cu angajatii care au salariul peste un prag
void genereazaRaportSalariu() {
    FILE* f = fopen("angajati.dat", "rb");
    struct Angajat a;
    float pragSalariu;
    int total = 0;

    if (!f) {
        perror("Eroare la deschiderea fisierului angajati.dat");
        return;
    }

    printf("Introduceti pragul salariului pentru raport: ");
    while (scanf("%f", &pragSalariu) != 1) {
        printf("Valoare invalida! Introduceti un numar valid: ");
        curataBuffer();
    }
    curataBuffer();

    FILE* raport = fopen("raport_salariu.txt", "w");
    if (!raport) {
        perror("Eroare la crearea fisierului de raport");
        fclose(f);
        return;
    }

    while (fread(&a, sizeof(a), 1, f) == 1) {
        if (a.salariu > pragSalariu) {
            fprintf(raport, "Nume: %s\nCod: %d\nSalariu: %.2f\n\n", a.nume, a.cod, a.salariu);
            total++;
        }
    }

    fclose(f);
    fclose(raport);

    FILE* verificare = fopen("raport_salariu.txt", "r");
    if (verificare != NULL) {
        fclose(verificare);
        if (total > 0)
            printf("Raport generat cu succes in 'raport_salariu.txt'. Total angajati peste %.2f: %d\n", pragSalariu, total);
        else
            printf("Nu exista angajati cu salariul peste %.2f.\n", pragSalariu);
    }
    else {
        printf("Eroare: fisierul 'raport_salariu.txt' nu a fost creat.\n");
    }
}

// functie care afiseaza angajatii cu salariu mai mare decat o valoare introdusa
void afiseazaAngajatSalariu() {
    FILE* f = fopen("angajati.dat", "rb");
    struct Angajat a;
    float prag;

    printf("Introduceti pragul salariului: ");
    while (scanf("%f", &prag) != 1) {
        printf("Valoare invalida! Introduceti un numar: ");
        curataBuffer();
    }
    curataBuffer();

    int gasit = 0;
    while (fread(&a, sizeof(a), 1, f) == 1) {
        if (a.salariu > prag) {
            printf("Angajat gasit:\n");
            printf("Nume: %s\nCod: %d\nSalariu: %.2f\n", a.nume, a.cod, a.salariu);
            gasit = 1;
        }
    }

    if (!gasit)
        printf("Nu exista angajati care sa indeplineasca aceasta conditie.\n");

    fclose(f);
}



















































