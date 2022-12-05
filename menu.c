/*********************************************
Határidőnapló projekt, menu.c fájl
A fájl a főmenüt és az almenüket vezérli, kezeli
a felhasználó válaszait.
Készítette: Saskó Máté
**********************************************/
#include <stdio.h>
#include "include/event.h"
#include "stdbool.h"
#include "include/econio.h"
#include "include/filehandler.h"
#include "include/io.h"
#include "string.h"

/*Visszatérési érték nélküli függvény, melynek feladata a konzol törlése, ASCII art kiíratása.
Globálisan használható.*/
void custom_clear()
{
    econio_clrscr();
    //   Egyedi ASCII art kirajzolása
    printf(" _   _         _                        _                              _          \n");
    printf("( ) ( )       ( )_               _     ( )                            (_ )        \n");
    printf("| |_| |   _ _ | ,_)   _ _  _ __ (_)   _| |   _     ___     _ _  _ _    | |    _   \n");
    printf("|  _  | /'_` )| |   /'_` )( '__)| | /'_` | /'_`\\ /' _ `\\ /'_` )( '_`\\  | |  /'_`\\ \n");
    printf("| | | |( (_| || |_ ( (_| || |   | |( (_| |( (_) )| ( ) |( (_| || (_) ) | | ( (_) )\n");
    printf("(_) (_)`\\__,_)`\\__)`\\__,_)(_)   (_)`\\__,_)`\\___/'(_) (_)`\\__,_)| ,__/'(___)`\\___/'\n");
    printf("                                                               | |                \n");
    printf("                                                               (_)                \n");
}

/*Visszatérési érték nélküli függvény, mely kiírja a paraméterként kapott esemény adatait.
Csak lokálisan elérhető.*/
void printEvent(event ev)
{
    printf("%d - \t%s \n", ev.id, ev.name);

    econio_textcolor(COL_DARKGRAY);
    /* printf("\t%d.%d.%d %d:%d\n", ev.eventDate.year, ev.eventDate.month, ev.eventDate.day, ev.eventTime.hour, ev.eventTime.minute); */
    printf("\t%d.", ev.eventDate.year);
    if (ev.eventDate.month < 10)
    {
        printf("0%d.", ev.eventDate.month);
    }
    else
    {
        printf("%d.", ev.eventDate.month);
    }
    if (ev.eventDate.day < 10)
    {
        printf("0%d.", ev.eventDate.day);
    }
    else
    {
        printf("%d. ", ev.eventDate.day);
    }
    if (ev.eventTime.hour < 10)
    {
        printf("0%d:", ev.eventTime.hour);
    }
    else
    {
        printf("%d:", ev.eventTime.hour);
    }
    if (ev.eventTime.minute < 10)
    {
        printf("0%d.\n", ev.eventTime.minute);
    }
    else
    {
        printf("%d\n", ev.eventTime.minute);
    }
    econio_textcolor(COL_WHITE);

    printf("\t%s\n", ev.place);
    printf("\t%s\n\n", ev.desc);
}

/*Függvény, mely kezeli az események id-ját. A lista sorrendje szerint ad nekik egyedi értéket.
Paraméterként kéri az első listaelemet és visszatér az új első listalemmel.
Csak lokálisan elérhető.*/
listItem *idHandler(listItem *first)
{
    int n = 1;
    listItem *moving = first;
    for (moving = first; moving != NULL; moving = moving->next)
    {
        moving->data.id = n;
        n++;
    }
    return first;
}

/* Függvény, mely kiíratja az összes eseményt.
Paraméterként kéri az első listaelem pointerét, nincs visszatérési értéke.
Csak lokálisan elérhető.*/
void printEventsAll(listItem *first)
{
    custom_clear();
    int n = 0;
    listItem *moving;
    for (moving = first; moving != NULL; moving = moving->next)
    {
        printEvent(moving->data);
        n++;
    }
    if (n == 0)
        printf("Nincs egyetlen elem sem!\n");
    printf("Nyomj meg egy gombot a tovabblepeshez!");
}

/* Függvény, mely kiíratja egy adott hónap eseményeit.
Paraméterként kéri az első listaelem pointerét, nincs visszatérési értéke.
Csak lokálisan elérhető.*/
void printEventsByMonth(listItem *first)
{
    printf("Adja meg melyik honap esemenyeit szeretne kiiratni!");
    econio_textcolor(COL_DARKGRAY);
    printf("[ev.honap.]\n");
    econio_textcolor(COL_WHITE);
    char dateChar[100];
    int year;
    int month;
    gets(dateChar);
    while (sscanf(dateChar, "%d.%d.", &year, &month) != 2)
    {
        custom_clear();
        printf("Adja meg melyik honap esemenyeit szeretne kiiratni!");
        econio_textcolor(COL_DARKGRAY);
        printf("[ev.honap.]\n");
        econio_textcolor(COL_WHITE);
        gets(dateChar);
    }
    custom_clear();
    listItem *moving;
    int db = 0;
    for (moving = first; moving != NULL; moving = moving->next)
    {
        if (moving->data.eventDate.year == year && moving->data.eventDate.month == month)
            db++;
    }
    if (db == 0)
    {
        printf("Nincs ilyen elem!\n");
    }
    else
    {
        for (moving = first; moving != NULL; moving = moving->next)
        {
            if (moving->data.eventDate.year == year && moving->data.eventDate.month == month)
                printEvent(moving->data);
        }
    }
    printf("Nyomj meg egy gombot a tovabblepeshez!");
    getchar();
}

/* Függvény, mely kiíratja egy adott nap eseményeit.
Paraméterként kéri az első listaelem pointerét, nincs visszatérési értéke.
Csak lokálisan elérhető.*/
void printEventsByDay(listItem *first)
{
    printf("Adja meg melyik nap esemenyeit szeretne kiiratni!");
    econio_textcolor(COL_DARKGRAY);
    printf("[ev.honap.nap.]\n");
    econio_textcolor(COL_WHITE);
    char dateChar[100];
    int year;
    int month;
    int day;
    gets(dateChar);
    while (sscanf(dateChar, "%d.%d.%d.", &year, &month, &day) != 3)
    {
        custom_clear();
        printf("Adja meg melyik nap esemenyeit szeretne kiiratni!");
        econio_textcolor(COL_DARKGRAY);
        printf("[ev.honap.nap.]\n");
        econio_textcolor(COL_WHITE);
        gets(dateChar);
    }
    custom_clear();
    listItem *moving;
    int db = 0;
    for (moving = first; moving != NULL; moving = moving->next)
    {
        if (moving->data.eventDate.year == year && moving->data.eventDate.month == month && moving->data.eventDate.day == day)
            db++;
    }
    if (db == 0)
    {
        printf("Nincs ilyen elem!\n");
    }
    else
    {
        for (moving = first; moving != NULL; moving = moving->next)
        {
            if (moving->data.eventDate.year == year && moving->data.eventDate.month == month && moving->data.eventDate.day == day)
                printEvent(moving->data);
        }
    }
    printf("Nyomj meg egy gombot a tovabblepeshez!");
    getchar();
}

/* Függvény, mely kiíratja egy adott hét eseményeit.
Paraméterként kéri az első listaelem pointerét, nincs visszatérési értéke.
Csak lokálisan elérhető.*/
void printEventsByWeek(listItem *first)
{
    printf("Adja meg melyik het esemenyeit szeretne kiiratni!");
    econio_textcolor(COL_DARKGRAY);
    printf("[ev.honap.sorszam.]\n");
    econio_textcolor(COL_WHITE);
    char dateChar[100];
    int year;
    int month;
    int week;
    gets(dateChar);
    while (sscanf(dateChar, "%d.%d.%d.", &year, &month, &week) != 3)
    {
        custom_clear();
        printf("Adja meg melyik het esemenyeit szeretne kiiratni!");
        econio_textcolor(COL_DARKGRAY);
        printf("[ev.honap.sorszam.]\n");
        econio_textcolor(COL_WHITE);
        gets(dateChar);
    }
    custom_clear();
    listItem *moving;
    int db = 0;
    if (week == 4)
    {
        week++;
    }
    for (moving = first; moving != NULL; moving = moving->next)
    {
        if (moving->data.eventDate.year == year && moving->data.eventDate.month == month && moving->data.eventDate.day <= (week * 7) && moving->data.eventDate.day > ((week - 1) * 7))
            db++;
    }
    if (db == 0)
    {
        printf("Nincs ilyen elem!\n");
    }
    else
    {
        for (moving = first; moving != NULL; moving = moving->next)
        {
            if (moving->data.eventDate.year == year && moving->data.eventDate.month == month && moving->data.eventDate.day < (week * 7))
                printEvent(moving->data);
        }
    }
    printf("Nyomj meg egy gombot a tovabblepeshez!");
    getchar();
}

/* Függvény, mely az eseménykiíratás menüjét vezérli..
Paraméterként kéri az első listaelem pointerét, nincs visszatérési értéke.
Csak lokálisan elérhető.*/
void printEvents_menu(listItem *first)
{
    bool running = true;
    while (running)
    {
        // Menü szövegének kiírása
        // Jelenleg hiányos
        custom_clear();
        printf("Listazas\n");
        printf("1. Osszes\n");
        printf("2. Honap szerint\n");
        printf("3. Het szerint\n");
        printf("4. Nap szerint\n");
        printf("9. Vissza\n");

        // Választás-switch

        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            printEventsAll(first);
            getchar();
            getchar();
            break;
        case 2:
            printEventsByMonth(first);
            break;
        case 3:
            printEventsByWeek(first);
            break;
        case 4:
            printEventsByDay(first);
        case 9:
            return;
            break;
        default:
            break;
        }
    }
}

/*Függvény, mely az eseménykeresést vezérli.
Paraméterként kéri az első listaelem pointerét, nincs visszatérési értéke.
Csak lokálisan elérhető.*/
void findEvents(listItem *first)
{
    custom_clear();
    char inp[50];
    printf("Adja meg a kereso kulcsszot!\n");
    getchar();
    scanf("%s", &inp);
    listItem *moving;
    int n = 0;
    custom_clear();
    for (moving = first; moving != NULL; moving = moving->next)
    {
        if (strstr(moving->data.name, inp) != NULL || strstr(moving->data.desc, inp) != NULL || strstr(moving->data.place, inp) != NULL)
        {
            n++;
        }
    }
    if (n == 0)
    {
        printf("Nincs talalat! Nyomjon meg egy gombot a folytatashoz...\n");
    }
    else
    {
        for (moving = first; moving != NULL; moving = moving->next)
        {
            if (strstr(moving->data.name, inp) != NULL || strstr(moving->data.desc, inp) != NULL || strstr(moving->data.place, inp) != NULL)
            {
                printEvent(moving->data);
            }
        }
    }
    printf("Nyomj meg egy gombot a tovabblepeshez!");
    getchar();
    getchar();
}

/*Függvény, mely az új esemény hozzáadásának menüjét vezérli.
Paraméterként kéri az első listaelem pointerét és visszaadja az új első elemet.
Csak lokálisan elérhető.*/
listItem *addEvent_menu(listItem *first)
{
    // név
    char name[100];
    getName(name);
    // dátum
    date tmpDate;
    getDate(&tmpDate);
    // idő
    time tmpTime;
    getTime(&tmpTime);

    // helszín
    char place[100];
    getPlace(place);

    // megjegyzés
    char desc[100];
    getDesc(desc);

    event tmp = createEvent(name, tmpDate, tmpTime, place, desc);

    // ellenőrző kérdés
    bool running = true;
    while (running)
    {
        printf("Esemeny felvetele\nNEV: %s\n", name);
        printf("DATUM: [%d.%d.%d.]\nIDOPONT: [%d:%d]\n", tmpDate.year, tmpDate.month, tmpDate.day, tmpTime.hour, tmpTime.minute);
        printf("1. Esemeny felvetele\n");
        printf("2. Megse\n");
        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            first = addListItem(first, tmp);
            first = idHandler(first);
            return first;
        case 2:
            running = false;
            break;
        }
    }
}

/*Függvény, mely az események törlésének menüjét vezérli.
Paraméterként kéri az első listaelem pointerét és visszaadja az új első elemet.*/
listItem *removeEvent_menu(listItem *first)
{
    custom_clear();
    printEventsAll(first);
    printf("Adja meg a torolni kivant elem azonositojat vagy (-1)-et a visszalepeshez!\n");

    int input;
    scanf("%d", &input);
    if (input == -1)
    {
        return first;
    }
    first = removeEvent(first, input);
    first = idHandler(first);
    return first;
}

/*Függvény, mely segítségével módosíthatjuk a listánk egy elemét. A módosítandó elemet az id változó adja meg.
Tipusa listaelem, paraméterként kéri az első listaelemet és egy egész számot, mely kijelöli a módosítandó elemet.
Csak lokálisan használható.*/
listItem *modifyEvent(listItem *first, int id)
{
    listItem *moving = first;
    while (moving != NULL && moving->data.id != id)
    {
        moving = moving->next;
    }
    getchar();
    if (moving == NULL)
    {
        printf("Nincs ilyen elem!\n Nyomj meg egy gombot a tovabblepeshez...\n");
        getchar();
        return first;
    }
    // név
    char name[100];
    custom_clear();
    printf("Esemeny neve:\n");
    gets(name);
    // dátum
    date tmpDate;
    getDate(&tmpDate);
    // idő
    time tmpTime;
    getTime(&tmpTime);

    // helszín
    char place[100];
    getPlace(place);

    // megjegyzés
    char desc[100];
    getDesc(desc);

    event tmp = createEvent(name, tmpDate, tmpTime, place, desc); // esemény létrehozása

    // ellenőrző kérdés
    bool running = true;
    while (running)
    {
        printf("Esemeny felvetele\nNEV: %s\n", name);
        printf("DATUM: [%d.%d.%d.]\nIDOPONT: [%d:%d]\n", tmpDate.year, tmpDate.month, tmpDate.day, tmpTime.hour, tmpTime.minute);
        printf("1. Esemeny felvetele\n");
        printf("2. Megse\n");
        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            moving->data = tmp;
            return first;
        case 2:
            running = false;
            break;
        }
    }
}

/*Függvény, mely az új esemény hozzáadásának menüjét vezérli.
Paraméterként kéri az első listaelem pointerét és visszaadja az új első elemet.
Csak lokálisan elérhető.*/
listItem *modifyEvent_menu(listItem *first)
{
    custom_clear();
    printEventsAll(first);
    printf("Adja meg a modositani kivant elem azonositojat vagy (-1)-et a visszalepeshez!\n");
    int input;
    scanf("%d", &input);
    if (input == -1)
    {
        return first;
    }
    first = modifyEvent(first, input);
    first = idHandler(first);
    return first;
}

/*Függvény, mely a főmenü kezeléséért és a felhasználói interakcióért felelős.
Paraméterként kéri az első listaelem pointerét, visszatérési értéket az első listaelem.
Globálisan elérhető.*/
listItem *main_menu(listItem *first)
{
    first = readFromFile(first);
    first = idHandler(first);
    bool running = true;
    while (running)
    {
        // Menü szövegének kiírása
        custom_clear();
        printf("1. Esemeny felvetele\n");
        printf("2. Esemeny torlese\n");
        printf("3. Esemeny modositasa\n");
        printf("4. Esemenyek listazasa\n");
        printf("5. Kereses az esemenyek kozt\n");
        printf("9. Mentes es kilepes \n");

        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            first = addEvent_menu(first);
            break;
        case 2:
            first = removeEvent_menu(first);
            break;
        case 3:
            first = modifyEvent_menu(first);
            break;
        case 4:
            printEvents_menu(first);
            break;
        case 5:
            findEvents(first);
            break;
        case 9:
            writeToFile(first);
            return first;
            running = false;
            break;
        default:
            printf("Az alábbi menüből válasszon!!");
            break;
        }
    }
}