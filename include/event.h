#ifndef EVENT_H
#define EVENT_H

typedef struct date
{
    int year;
    int month;
    int day;
} date;
typedef struct time
{
    int hour;
    int minute;
} time;
typedef struct event
{
    int id;
    char name[101];
    date eventDate;
    time eventTime;
    char place[101];
    char desc[101];

} event;
typedef struct listItem
{
    event data;
    struct listItem *next;
} listItem;
listItem *addListItem(listItem *first, event a);
event *allEvents;
int latestEvent;
void addEvent(event a);
event createEvent(char *name, date evDate, time evTime, char *plc, char *desc);
listItem *removeEvent(listItem *first, int id);
#endif
