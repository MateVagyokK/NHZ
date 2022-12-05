/*********************************************
Határidőnapló projekt, filehandler.c fájl
A fájl a program fájlkezeléséhez szükséges
függvényeit tartalmazza.
Készítette: Saskó Máté
**********************************************/
#include <stdio.h>
#include "include/event.h"

/*Visszatérési érték nélküli függvény, mely elmenti a mentést tartalmazó txt-be a lista eseményeit.
Paraméterként kéri a lista első elemét.
Globálisan használható.*/
void writeToFile(listItem *first)
{
    FILE *fptr;
    fptr = fopen("save.txt", "w");
    if (fptr == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return;
    }
    listItem *moving;
    int n = 0;
    for (moving = first; moving != NULL; moving = moving->next)
    {
        event a = moving->data;
        n++;
    }
    fprintf(fptr, "%d\n", n);
    for (moving = first; moving != NULL; moving = moving->next)
    {
        event a = moving->data;
        fprintf(fptr, "%s\n", a.name);
        fprintf(fptr, "%d.%d.%d.\n", a.eventDate.year, a.eventDate.month, a.eventDate.day);
        fprintf(fptr, "%d:%d\n", a.eventTime.hour, a.eventTime.minute);
        fprintf(fptr, "%s\n", a.place);
        fprintf(fptr, "%s\n", a.desc);
    }

    fclose(fptr);
}

/*Függvény, mely beolvassa a mentést tartalmazó txt fájl tartalmát és hozzáfűzi a benne lévő eseményeket
a láncolt listához. Paraméterként kéri a lista első elemét és visszaadja az új első elemet.
Globálisan használható.*/
listItem *readFromFile(listItem *first)
{
    FILE *fptr;
    fptr = fopen("save.txt", "r");
    if (fptr == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return NULL;
    }
    event tmp;
    char buffer[200];
    fgets(buffer, 200, fptr);
    int n = 0;
    sscanf(buffer, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fgets(buffer, 200, fptr);
        sscanf(buffer, "%[^\n]", tmp.name);
        fgets(buffer, 200, fptr);
        sscanf(buffer, "%d.%d.%d.", &tmp.eventDate.year, &tmp.eventDate.month, &tmp.eventDate.day);
        fgets(buffer, 200, fptr);
        sscanf(buffer, "%d:%d", &tmp.eventTime.hour, &tmp.eventTime.minute);
        fgets(buffer, 200, fptr);
        sscanf(buffer, "%[^\n]", tmp.place);
        fgets(buffer, 200, fptr);
        sscanf(buffer, "%[^\n]", tmp.desc);
        first = addListItem(first, tmp);
    }
    fclose(fptr);
    return first;
}