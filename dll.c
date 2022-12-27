#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

list_t *create_list() // return a newly created empty doubly linked list
{
    // DO NOT MODIFY!!!
    list_t *l = (list_t *)malloc(sizeof(list_t));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void insert_front(list_t *list, int data) // TODO: inserts data to the beginning of the linked list
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    if (list->size == 0)
    {
        list->head = new;
        list->tail = new;
    }
    else
    {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
    (list->size)++;
}

void insert_back(list_t *list, int data) // TODO: inserts data to the end of the linked list
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    if (list->size == 0)
    {
        list->head = new;
        list->tail = new;
    }
    else
    {
        new->prev = list->tail;
        list->tail->next = new;
        list->tail = new;
    }
    (list->size)++;
}

void insert_after(list_t *list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    if (list->size != 0)
    {
        node_t *temp = list->head;
        while (temp != NULL && temp->data != prev)
            temp = temp->next;
        if (temp->data == prev)
        {
            new->prev = temp;
            new->next = temp->next;
            temp->next->prev = new;
            temp->next = new;
            if (temp == list->tail)
                list->tail = new;
            (list->size)++;
        }
        else
        {
            free(new);
        }
    }
}

void delete_front(list_t *list) // TODO: delete the start node from the linked list.
{
    if (list->size != 0)
    {
        node_t *temp = list->head;
        list->head = list->head->next;
        if (list->tail == temp)
            list->tail = NULL;
        if (list->head != NULL)
            list->head->prev = NULL;
        free(temp);
        (list->size)--;
    }
}

void delete_back(list_t *list) // TODO: delete the end node from the linked list.
{
    if (list->size != 0)
    {
        node_t *temp = list->tail;
        list->tail = list->tail->prev;
        if (list->head == temp)
            list->head = NULL;
        if (list->tail != NULL)
            list->tail->next = NULL;
        free(temp);
        (list->size)--;
    }
}

void delete_node(list_t *list, int data) // TODO: delete the node with “data” from the linked list.
{
    if (list->size != 0)
    {
        node_t *temp = list->head;
        while (temp != NULL && temp->data != data)
            temp = temp->next;
        if (temp->data == data)
        {
            if (temp->prev == NULL)
                delete_front(list);
            else if (temp->next == NULL)
                delete_back(list);
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free(temp);
                (list->size)--;
            }
        }
    }
}

node_t *search(list_t *list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{
    node_t *temp = list->head;
    while (temp != NULL && temp->data != data)
        temp = temp->next;
    return temp;
}

int is_empty(list_t *list) // return true or 1 if the list is empty; else returns false or 0
{
    // DO NOT MODIFY!!!
    return list->size == 0;
}

int size(list_t *list) // returns the number of nodes in the linked list.
{
    // DO NOT MODIFY!!!
    return list->size;
}

void delete_nodes(node_t *head) // helper
{
    // DO NOT MODIFY!!!
    if (head == NULL)
        return;
    delete_nodes(head->next);
    free(head);
}

void delete_list(list_t *list) // free all the contents of the linked list
{
    // DO NOT MODIFY!!!
    delete_nodes(list->head);
    free(list);
}

void display_list(list_t *list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
    // DO NOT MODIFY!!!
    node_t *it = list->head;
    while (it != NULL)
    {
        printf("%d ", it->data);
        it = it->next;
    }
    printf("\n");
}
