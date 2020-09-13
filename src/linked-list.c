#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node_s
{
    uint32_t data;
    struct Node_s *nxtNode;
}Node_st;

typedef struct List_s
{
    uint32_t length;
    struct Node_s *head;
    struct Node_s *tail;
}List_st;

Node_st *
NODE_Create()
{
    Node_st *newNode = (Node_st *)malloc(sizeof(Node_st));
    newNode->nxtNode = NULL;
    return(newNode); 
}

void
LIST_Create(List_st *self)
{
    self->length = 0;
    self->head = NULL;
    self->tail = NULL;
}


void
LIST_Push(List_st *self, uint32_t data)
{
    Node_st *newNode = NODE_Create();

    if(self->head == NULL)
    {
        self->head = newNode;
        self->tail = newNode;
    }
    else
    {
        self->tail->nxtNode = newNode;
        self->tail = newNode;
    }
    
    self->length++;

    newNode->data = data;
}

void
LIST_Pop(List_st *self)
{
    Node_st *prevTailNode = self->head;

    if(self->length > 0)
    {
        while(prevTailNode->nxtNode != self->tail)
        {
            prevTailNode = prevTailNode->nxtNode;
        }
        free(self->tail);
        self->tail = prevTailNode;
        self->tail->nxtNode = NULL;
        self->length--;
    }
}
void
LIST_Print(List_st *self)
{
    Node_st *node = self->head;
    
    printf("List -> ");
    while(node != NULL)
    {
        printf("%d ",node->data);
        node = node->nxtNode;
    }
    printf("\n");
}

void
LIST_Flush(List_st *self)
{
    Node_st *node = self->head;
    Node_st *prevNode;
    while(node != NULL)
    {
        prevNode = node->nxtNode;
        free(node);
        node = prevNode;
    }
    self->head = NULL;
    self->tail = NULL;
    self->length = 0;
}

int
main(void)
{
    List_st rankList;

    LIST_Create(&rankList);

    LIST_Push(&rankList, 10);
    LIST_Push(&rankList, 20);
    LIST_Push(&rankList, 30);
    LIST_Push(&rankList, 50);
    LIST_Push(&rankList, 300);
    LIST_Print(&rankList);

    LIST_Pop(&rankList);
    LIST_Pop(&rankList);
    LIST_Print(&rankList);

    LIST_Push(&rankList, 399);
    LIST_Print(&rankList);

    LIST_Flush(&rankList);
    return 0;
}