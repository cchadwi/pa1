#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_list.h"

typedef struct List_ {
    Node* head;
    struct List_ *next;
} List;

static Node * buildNode(long value){
    Node * newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->value = value;
    return newNode;
}

static void push(Node** head, Node * newNode)
{
    newNode->next = (*head);
    (*head) = newNode;
}

Node *List_Load_From_File(char *filename)
{
    long value;
    Node * head;
    Node * new = NULL;

    FILE * fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return NULL;
    }
    
    while (!feof(fp))
    {
        fread(&value, sizeof(long), 1, fp);
        head = buildNode(value);
        head -> next = new;
        new = head;
    }
    Node * exit = head;
    head = exit->next;
    free(exit);
    Node * reverse = NULL;
    Node * second;
    while (head != NULL)
    {
        second = head->next;
        head->next = reverse;
        reverse = head;
        head = second;
    }
    fclose(fp);
    return reverse;
}

static long insertion(Node** head, Node* newNode)
{
    Node* current;
    long rVal = 0;
    rVal++;
    if (*head == NULL || (*head)->value <= newNode->value)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        current = *head;
        rVal++;
        while (current->next!=NULL && current->next->value > newNode->value)
        {
            rVal++;
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return rVal;
}

static Node* pop(Node** head)
{
    if (*head == NULL)
        return NULL;
    else
    {
        Node* temp = *head;
        Node * rem = temp;
        (*head) = (*head)->next;
        rem -> next = NULL;
        return rem;
    }
}

static void reverse(List ** Head)
{
    List* prev = NULL;
    List* current = *Head;
    List* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *Head = prev;
}

int List_Save_To_File(char *filename, Node *list){
    FILE * f = fopen(filename, "wb");
    if (f == NULL){
        return 0;
    }
    Node * loader = list;
    int num = 0;
    while (loader != NULL){
        fwrite(&loader->value, sizeof(long), 1, f);
        loader = loader->next;
        num++;
    }
    fclose(f);
    return num;
}

Node *List_Shellsort(Node *list, long *n_comp) {
    if (list == NULL) {
        return NULL;
    }
    //find list size
    int size = 0;
    Node *count = list;
    while (count != NULL) {
        size++;
        count = count->next;
    }
    // Knuth's sequence
    long sequenceGen = 1;
    long preNum = 1;
    long postNum = 1;
    while(sequenceGen <= size)
    {
        preNum = sequenceGen;
        sequenceGen =  sequenceGen*3+1;
        postNum = sequenceGen;
    }
    sequenceGen = sequenceGen - (postNum-preNum);
    // Shellsort
    while(sequenceGen > 0)
    {
        Node * travNode = list;
        List * Head = NULL;
        List * HPR = NULL;
        Node * newList = NULL;
        for(int i = 0; i < sequenceGen; i++)
        {
            Head = malloc(sizeof(List));
            Head -> head = pop(&travNode);
            Head -> next = HPR;
            HPR = Head;
        }
        reverse(&Head);
        List * travList = Head;
        while(travNode != NULL)
        {
            *n_comp = *n_comp + insertion(&travList -> head, pop(&travNode));
            if(travList ->next != NULL)
                travList = travList -> next;
            else
                travList = Head;
        }
        travList = Head;
        for(int i = 0; i < size; i++)
        {
            if(travList -> head -> next != NULL)
            {
                Node * tempNode = travList -> head -> next;
                push(&newList, travList->head);
                travList -> head = tempNode;
            }
            else if(travList -> head != NULL)
            {
                push(&newList, travList->head);
            }

            if(travList ->next != NULL)
                travList = travList -> next;
            else
                travList = Head;
        }
        list = newList;
        for(int i = 0; i < sequenceGen; i++)
        {
            travList = Head ->next;
            free(Head);
            Head = travList;
        }
        sequenceGen /=3;
    }
    return list;
}