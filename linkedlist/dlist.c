#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    // Initialize the list
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void dlist_destroy(DList *list)
{
    void *data;

    // Remove each element
    while (dlist_size(list) > 0)
    {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destroy != NULL)
        {
            // Call a user defined function to free dynamically allocated data
            list->destroy(data);
        }
    }

    // Clea the list
    memset(list, 0, sizeof(DList));
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    if (element == NULL && dlist_size(list) != 0)
    {
        return -1;
    }

    // Allocate storage for the element
    DListElmt *new_element;
    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
    {
        return -1;
    }
    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail->next = NULL;
    }
    else
    {
        new_element->next = element->next;
        element->prev = element;
        if (element->next == NULL) // Inserting at the tail
        {
            list->tail = new_element;
        }
        else // Inserting in the middle
        {
            element->next->prev = new_element;
        }
        element->next = new_element;
    }

    // Adjust the size
    list->size++;

    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    // Do not allow a null element or removal from an emptylist
    if (element == NULL || dlist_size(list) == 0)
    {
        return -1;
    }

    // remove the element from the list
    *data = element->data;
    if (element == list->head)
    {
        // Handle removal from the head of the list
        list->head = element->next;
        if (list->head == NULL)
            list->tail = NULL;
        else
            element->next->prev = NULL;
    }
    else
    {
        // Handle removal from other than the head of the list

        element->prev->next = element->next;
        if (element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }

    // Free the storage allocated by the abstarct data type
    free(element);

    // Adjust the size of the list to account for removed element
    list->size--;

    return 0;
}