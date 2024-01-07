#include "slist.h"
#include <stdlib.h>

void insertAtTail(Move **head, char player, int column) {
    Move *newMove = malloc(sizeof(Move));
    newMove->player = player;
    newMove->column = column;
    newMove->next = NULL;

    if (!*head) {
        *head = newMove;
        return;
    }

    Move *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newMove;
}

void freeList(Move *head) {
    Move *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
