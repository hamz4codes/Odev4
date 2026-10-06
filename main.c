/// Örnek1: Çift bağlı liste ile bir müzik çalar.

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

void addSongToEnd(Song** head, const char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
}

void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Song* temp = *head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song not found.\n");
        return;
    }

    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    printf("Song removed successfully.\n");
}

void playNext(Song** current) {
    if (*current == NULL || (*current)->next == NULL) {
        printf("List is empty or no next song to play.\n");
        return;
    }

    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Now playing: %s\n", (*current)->name);
    } else {
        printf("You are at the last song. No next song to play.\n");
    }
}

void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("List is empty.\n");
        return;
    }
    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Now playing: %s\n", (*current)->name);
    } else {
        printf("You are at the first song. No previous song to play.\n");
    }
}

void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Song* temp = head;
    printf("\n--- Playlist ---\n");
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}

int main() {
    Song* head = NULL;
    Song* current = NULL;
    int choice;
    char songName[50];

    while(1) {
        printf("\n1- Add Song\n2- Remove Song\n3- Play Next\n4- Play Previous\n5- Display Playlist\n6- Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter song name: ");
            scanf(" %[^\n]", songName);
            addSongToEnd(&head, songName);
            if (current == NULL) {
                current = head;
            }
        } else if (choice == 2) {
            printf("Enter song name to remove: ");
            scanf(" %[^\n]", songName);

            if (current != NULL && strcmp(current->name, songName) == 0) {
                if (current->next != NULL) {
                    current = current->next;
                } else current = current->prev;
            }
            removeSong(&head, songName);
        } else if (choice == 3) {
            playNext(&current);
        } else if (choice == 4) {
            playPrevious(&current);
        } else if (choice == 5) {
            displayPlaylist(head);
        } else if (choice == 6) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
*/


///Örnek2: Undo(Geri alma) Özelliği ile Stack Kullanımı.

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    strcpy(newWord->text, text);
    newWord->next = *top;
    *top = newWord;
}

void popWord(Word** top) {
    if (*top == NULL) {
        printf("No words to undo.\n");
        return;
    }

    Word* temp = *top;
    *top = (*top)->next;
    free(temp);
}

void showRecursive(Word* node) {
    if (node == NULL) return;
    showRecursive(node->next);
    printf("%s\n", node->text);
}

void showWords(Word* top) {
    if (top == NULL) {
        printf("Text is empty.\n");
        return;
    }
    printf("Show -> ");
    showRecursive(top);
    printf("\n");
}

int main() {
    Word* top = NULL;
    char input[20];
    char word[50];

    printf("Enter words (type 'undo' to remove last word, 'show' to display words, 'exit' to quit):\n");
    
    while (1) {
        printf("> ");
        scanf("%s", input);

        if (strcmp(input, "add") == 0) {
            scanf(" %[^\n]", word);
            pushWord(&top, word);
        } else if (strcmp(input, "undo") == 0) {
            popWord(&top);
        } else if (strcmp(input, "show") == 0) {
            showWords(top);
        } else if (strcmp(input, "exit") == 0) {
            break;
        } else {
            printf("Invalid command. Use 'add', 'undo', 'show', or 'exit'.\n");
        }
    }

    return 0;
}
*/


///Örnek3: Yazıcı kuyruğu (Queue) ile yazdırma işlemi.

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char documentName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct PrintQueue {
    PrintJob* front;
    PrintJob* rear;
} PrintQueue;

void enqueue(PrintQueue* q, char* documentName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    strcpy(newJob->documentName, documentName);
    newJob->next = NULL;

    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }
    printf("'%s' added to the print queue.\n", documentName);
}

void processNextJob(PrintQueue* q) {
    if (q->front == NULL) {
        printf("Print queue is empty.\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("Printing '%s'...\n", temp->documentName);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void showQueue(PrintQueue* q) {
    if (q->front == NULL) {
        printf("Print queue is empty.\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("Current print queue:\n");
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s\n", i++, temp->documentName);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    PrintQueue q;
    q.front = NULL;
    q.rear = NULL;

    int choice;
    char documentName[50];

    while (1) {
        printf("\n1) Add\n2) Print\n3) Show Queue\n0) Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("File name: ");
            scanf("%s", documentName);
            enqueue(&q, documentName);
        } else if (choice == 2) {
            processNextJob(&q);
        } else if (choice == 3) {
            showQueue(&q);
        } else if (choice == 0) {
            break;
        }
    }

    return 0;
}
*/