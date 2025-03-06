#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char character;
    int count;
    struct Node* next;
} Node;


Node* hashTable[256] = { NULL };


void insertNode(Node** head, char ch) {

    Node* found = hashTable[(unsigned char)ch];
    
    if (found) {
        found->count++;  
    } else {
       
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->character = ch;
        newNode->count = 1;
        newNode->next = *head;
        *head = newNode;

      
        hashTable[(unsigned char)ch] = newNode;
    }
}


void freeList(Node* head) {
    Node* temp;
    while (head) {
        hashTable[(unsigned char)head->character] = NULL;  
        temp = head;
        head = head->next;
        free(temp);
    }
}


void printList(Node* head) {
    Node* current = head;
    while (current) {
        unsigned char ch = (unsigned char)current->character;
        if (ch == 32) {
            printf("SPACE : %d\n", current->count);
        }
        else if (ch == '\t') {
            printf("TAB : %d\n", current->count);
        }
        else if (ch == '\n') {
            printf("NEWLINE : %d\n", current->count);
        }
        else if (ch == '\r') {
            printf("CARRIAGE_RETURN : %d\n", current->count);
        }
        else if (ch < 32) {
            printf("ASCII[%02X] : %d\n", ch, current->count);
        }
        else if (ch < 127) {
            printf("%c : %d\n", ch, current->count);
        }
        else {
            printf("ASCII[%02X] : %d\n", ch, current->count);
        }
        current = current->next;
    }
}


int main() {
    FILE* file = fopen("main.c", "r");
    if (!file) {
        printf("Unable to open file!\n");
        return 1;
    }

    Node* head = NULL;  
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        insertNode(&head, ch);  
    }
    fclose(file);

    printList(head); 
    freeList(head);   
    return 0;
}
