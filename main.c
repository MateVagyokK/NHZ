/*********************************************
Határidőnapló projekt, main.c fájl
A fájl a program főfájlja.
Készítette: Saskó Máté
**********************************************/

#include <stdlib.h>
#include <stdio.h>
#include "include/event.h"
#include "include/menu.h"
#include "include/debugmalloc.h"

/* Visszatérési érték nélküli függvény, mely paraméterként kéri a felszabadítandó lista első elemét és felszabadítja az összes listaelemet. Csak lokálisan elérhető.*/
void free_memory(listItem *first)
{
    listItem *iter = first;
    while (iter != NULL)
    {
        listItem *next = iter->next;
        free(iter);
        iter = next;
    }
}

int main()
{
    listItem *first = NULL;
    first = main_menu(first);
    free_memory(first);
    return 0;
}