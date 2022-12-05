/*********************************************
Határidőnapló projekt, event.c fájl
A fájl célja, hogy definiálja az eseményt, és a
hozzá szükséges egyéb fogalmakat.
Készítette: Saskó Máté
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/econio.h"
#include "include/menu.h"
#include "include/debugmalloc.h"

/*Struktúra, mely definiál egy dátumot. Globálisan használható.*/
typedef struct date
{
    int year;  // év
    int month; // hónap
    int day;   // nap
} date;

/*Struktúra, mely definiál egy időpontot. Globálisan használható.*/
typedef struct time
{
    int hour;   // óra
    int minute; // perc
} time;

/*Struktúra, mely definiál egy eseményt. Globálisan használható.*/
typedef struct event
{
    int id;          // azonosító
    char name[101];  // név
    date eventDate;  // dátum
    time eventTime;  // időpont
    char place[101]; // helyszín
    char desc[101];  // megjegyzés
} event;

/*Struktúra a láncolt lista létrehozásához. Globálisan használható*/
typedef struct listItem
{
    event data;            // egy listaelem
    struct listItem *next; // következő listaelem
} listItem;

/*Esemény tipusú függvény, mely paraméterként kéri egy esemény adatait és visszaadja
a belőlük kreált esemény változót. Globálisan használható.*/
event createEvent(char *name, date evDate, time evTime, char *plc, char *desc)
{
    event tmp;
    strcpy(tmp.name, name);
    tmp.eventDate = evDate;
    tmp.eventTime = evTime;
    strcpy(tmp.place, plc);
    strcpy(tmp.desc, desc);
    return tmp;
}

/*Függvény, mely segítségével új elemet füzhetünk a láncolt listánkhoz.
Tipusa listaelem, paraméterként kéri az első listaelemet és a hozzáfűzendő eseményt.
Globálisan használható*/
listItem *addListItem(listItem *first, event a)
{
    listItem *new;
    new = (listItem *)malloc(sizeof(listItem));
    if (new == NULL)
        return NULL;
    new->data = a;
    new->next = NULL;

    if (first == NULL)
    {
        first = new;
    }
    else
    {
        listItem *moving = first;
        while (moving->next != NULL)
        {
            moving = moving->next;
        }
        moving->next = new;
    }
    return first;
}

/*Függvény, mely segítségével törölhetjük a listánk egy elemét. A törlendő elemet az id változó adja meg.
Tipusa listaelem, paraméterként kéri az első listaelemet és egy egész számot, mely kijelöli a törlendő elemet.
Globálisan használható*/
listItem *removeEvent(listItem *first, int id)
{
    listItem *sub = NULL;
    listItem *moving = first;
    while (moving != NULL && moving->data.id != id)
    {
        sub = moving;
        moving = moving->next;
    }
    if (moving == NULL)
    {
        printf("Nincs ilyen elem!\n Nyomj meg egy gombot a tovabblepeshez...\n");
        getchar();
        return first;
    }
    else if (sub == NULL)
    {
        listItem *new = moving->next;
        free(moving);
        first = new;
    }
    else
    {
        sub->next = moving->next;
        free(moving);
    }
    return first;
}