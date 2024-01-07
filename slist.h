typedef struct Move {
    char player;
    int column;
    struct Move *next;
} Move;

void insertAtTail(Move **head, char player, int column);
void freeList(Move *head);
