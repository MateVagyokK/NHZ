/*********************************************
Határidőnapló projekt, io.c fájl
A fájl célja, hogy eseményadatokat kérjen be
a felhasználótól.
Készítette: Saskó Máté
**********************************************/
#include <stdio.h>
#include "include/econio.h"
#include "include/event.h"
#include "include/menu.h"

/*Visszatérési érték nélküli függvény, mely bekéri a felhasználótól egy esemény nevét és elmenti azt a paraméterként bekért karaktertömbben. Globálisan elérhető.*/
void getName(char *name)
{
    custom_clear();
    printf("Esemeny neve:\n");
    getchar();
    gets(name);
}

/*Visszatérési érték nélküli függvény, mely bekéri a felhasználótól egy esemény helyszínét és elmenti azt a paraméterként bekért karaktertömbben. Globálisan elérhető.*/
void getPlace(char *place)
{
    custom_clear();
    printf("Esemeny helyszine:\n");
    gets(place);
}

/*Visszatérési érték nélküli függvény, mely bekéri a felhasználótól egy esemény dátumát és elmenti azt a paraméterként bekért dátum változóban. Globálisan elérhető.*/
void getDate(date *el)
{
    custom_clear();
    printf("Esemeny datuma: ");
    econio_textcolor(COL_DARKGRAY);
    printf("[ev.honap.nap.]\n");
    econio_textcolor(COL_WHITE);
    char dateChar[100];
    gets(dateChar);
    while (sscanf(dateChar, "%d.%d.%d.", &el->year, &el->month, &el->day) != 3 || el->month > 12 || el->month < 1 || el->day < 1 || el->day > 31)
    {
        custom_clear();
        printf("Hibas bemenet!\n");
        printf("Esemeny datuma: ");
        econio_textcolor(COL_DARKGRAY);
        printf("[ev.honap.nap.]\n");
        econio_textcolor(COL_WHITE);
        gets(dateChar);
    }
}

/*Visszatérési érték nélküli függvény, mely bekéri a felhasználótól egy esemény idejét és elmenti azt a paraméterként bekért idő változóban. Globálisan elérhető.*/
void getTime(time *el)
{
    custom_clear();
    printf("Esemeny ideje: ");
    econio_textcolor(COL_DARKGRAY);
    printf("[ora:perc]\n");
    econio_textcolor(COL_WHITE);
    char timeChar[100];
    gets(timeChar);
    time tmpTime;
    while (sscanf(timeChar, "%d:%d", &el->hour, &el->minute) != 2 || el->hour > 23 || el->hour < 0 || el->minute > 59 || el->minute < 0)
    {
        custom_clear();
        printf("Hibas bemenet!\n");
        printf("Esemeny ideje: ");
        econio_textcolor(COL_DARKGRAY);
        printf("[ora:perc]\n");
        econio_textcolor(COL_WHITE);
        gets(timeChar);
    }
}

/*Visszatérési érték nélküli függvény, mely bekéri a felhasználótól az eseményhez fűzött megjegyzést és elmenti azt a paraméterként bekért karaktertömbben. Globálisan elérhető.*/
void getDesc(char *desc)
{
    custom_clear();
    printf("Megjegyzes:\n");
    gets(desc);
}
