/*********************************************
Határidőnapló projekt, filehandler.c fájl
A fájl a program fájlkezeléséhez szükséges
függvényeit tartalmazza.
Készítette: Saskó Máté
**********************************************/
#include <stdio.h>
#include "include/event.h"
#include <stdbool.h>
#include <string.h>

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
        fprintf(fptr, "[name]:%s \n", a.name);
        fprintf(fptr, "[date]:%d.%d.%d.\n", a.eventDate.year, a.eventDate.month, a.eventDate.day);
        fprintf(fptr, "[time]:%d:%d\n", a.eventTime.hour, a.eventTime.minute);
        fprintf(fptr, "[place]:%s \n", a.place);
        fprintf(fptr, "[desc]:%s \n", a.desc);
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
        perror("Fájl megnyitása sikertelen!\n A program letrehozza az uj mentesfajlt!");
        getchar();
        return NULL;
    }
    event tmp;
    char buffer[200];
    fgets(buffer, 200, fptr);
    int n = 0;
    bool error = false;
    bool asked = false;
    sscanf(buffer, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fgets(buffer, 200, fptr);
        if (sscanf(buffer, "[name]:%[^\n]", tmp.name) != 1)
        {
            error = true;
            strcpy(tmp.name, "");
        }
        fgets(buffer, 200, fptr);
        if (sscanf(buffer, "[date]:%d.%d.%d.", &tmp.eventDate.year, &tmp.eventDate.month, &tmp.eventDate.day) != 3)
        {
            error = true;
            tmp.eventDate.year = -1;
            tmp.eventDate.month = -1;
            tmp.eventDate.day = -1;
        }
        fgets(buffer, 200, fptr);
        if (sscanf(buffer, "[time]:%d:%d", &tmp.eventTime.hour, &tmp.eventTime.minute) != 2)
        {
            error = true;
            tmp.eventTime.hour = -1;
            tmp.eventTime.minute = -1;
        }
        fgets(buffer, 200, fptr);
        if (sscanf(buffer, "[place]:%[^\n]", tmp.place) != 1)
        {
            error = true;
            strcpy(tmp.place, "");
        }
        fgets(buffer, 200, fptr);
        if (sscanf(buffer, "[desc]:%[^\n]", tmp.desc) != 1)
        {
            error = true;
            strcpy(tmp.desc, "");
        }
        if (error && !asked)
        {
            bool running = true;
            while (running)
            {
                printf("Hibas mentesfajl!\nA betoltendo adatok kozt valoszinuleg hiba szerepel.\nKivanja igy is betolteni es manualisan javitani az esemenyeket?\n");
                printf("1. Betoltes mellozese\n");
                printf("2. Betoltes folytatasa\n");
                int input;
                scanf("%d", &input);
                getchar();
                switch (input)
                {
                case 1:
                    fclose(fptr);
                    return NULL;
                    break;
                case 2:
                    asked = true;
                    running = false;
                    break;
                default:
                    break;
                }
            }
        }
        first = addListItem(first, tmp);
    }
    fclose(fptr);
    return first;
}