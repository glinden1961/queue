/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "harness.h"
#include "queue.h"

/*
 Create empty queue.
 Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    
    /* What if malloc returned NULL? */
    if(!q)
        return NULL;
    
    q->head = NULL;
    q->tail=  NULL;
    q->len=0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    list_ele_t *to_be_freed, *cur;
    if(q==NULL)
        return;
    cur = q->head;
    while(cur) {
        /* free the string associated */
        free(cur->value);
        /* save the head so we can advance it */
        to_be_freed = cur;
        /* advance the head */
        cur = cur->next;
        /* free the old head now that we have advanced the head */
        free(to_be_freed);
    }
    
    /* Free queue structure */
    free(q);
}

/*
 Attempt to insert element at head of queue.
 Return true if successful.
 Return false if q is NULL or could not allocate space.
 Argument s points to the string to be stored.
 The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    int lengthOfs = strlen(s)+1;
    
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if(!newh)
        return false;
    newh->value=malloc(lengthOfs*sizeof(char));
    if(!newh->value)
    {
        free(newh);
        return false;
    }
    
    /* is strcpy unsafe here? we have already allocated all the space so can't have buffer overflow */
    strcpy(newh->value,s);
    
    /* add it to the front of the queue */
    newh->next = q->head;
    /* update the head ptr of the queue */
    q->head = newh;
    
    q->len++;
    /* if this is the first element we need to point the tail to this element */
    if(q->tail == NULL)
        q->tail=newh;
    
    return true;
}


/*
 Attempt to insert element at tail of queue.
 Return true if successful.
 Return false if q is NULL or could not allocate space.
 Argument s points to the string to be stored.
 The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    
    list_ele_t *newh;
    int lengthOfs = strlen(s)+1;
    if (!q)
        return false;
    if((newh=malloc(sizeof(list_ele_t)))==NULL)
        return false;
    newh->value=malloc(lengthOfs*sizeof(char));
    if(!newh->value)
    {
        free(newh);
        return false;
    }
    
    /* is strcpy unsafe here? we have already allocated all the space so can't have buffer overflow */
    strcpy(newh->value, s);
    
    /* does the queue already have some elements? */
    if(q->tail) {
        q->tail->next = newh;
        q->tail = newh;
        newh->next = NULL;
        q->len++;
    }
    /* if we are adding to the tail of an empty queue */
    else {
        q->head = newh;
        q->tail = newh;
        q->len++;
    }
    return true;
}

/*
 Attempt to remove element from head of queue.
 Return true if successful.
 Return false if queue is NULL or empty.
 If sp is non-NULL and an element is removed, copy the removed string to *sp
 (up to a maximum of bufsize-1 characters, plus a null terminator.)
 The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    int lengthOfsp, copylen;
    list_ele_t *oldhead;
    int i;
    
    if(!q)
        return false;
    
    if(!q->head)
        return false;
    
    /* strlen does not account for null termination char */
    lengthOfsp = strlen(q->head->value)+1;
    copylen    = (lengthOfsp > bufsize) ? bufsize:lengthOfsp;
    
    if(sp) {
        
        for(i=0;i<copylen-1;i++)
            sp[i]=q->head->value[i];
        
        sp[copylen-1]='\0';
        
    }
    
    /* Save old head to free so we can advance the head ptr. */
    oldhead = q->head;
    /* Advance the head ptr. */
    q->head = q->head->next;
    
    free(oldhead->value);
    free(oldhead);
    q->len--;
    
    return true;
}

/*
 Return number of elements in queue.
 Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q)
        return q->len;
    else
        return 0;
}

/*
 Reverse elements in queue
 No effect if q is NULL or empty
 This function should not allocate or free any list elements
 (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *start, *cur, *second, *tmp;
    
    if(!q || !q->head)
        return;
    
    /* save the starting head position so we can use it at the end */
    start=q->head;
    
    /*save the current element in the queue */
    cur=q->head;
    /*save the next element in the quwue */
    second=cur->next;
    
    while(second) {
        /* save the ptr to next to next element in the queue */
        tmp=second->next;
        /* reverse the next ptr for the (next element) */
        second->next=cur;
        /* next element becomes the current element */
        cur=second;
        /* next to next element becomes the next element */
        second=tmp;
    }
    q->head=cur;
    start->next = NULL;
    q->tail=start;
}

