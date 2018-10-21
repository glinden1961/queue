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
  list_ele_t *to_be_removed, *cur;

  if(q==NULL)
    return;
  
  cur = q->head;

  while(cur) {
      /* free the string associated */
    free(cur->value);
      /* save the head so we can advance it */
    to_be_removed = cur;
      /* advance the head */
    cur = cur->next;
      /* free the old head now that we have advanced the head */
    free(to_be_removed);
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
    //int i;
    
    /* What should you do if the q is NULL? */
    if (!q)
      return false;
    
    newh = malloc(sizeof(list_ele_t));

    if(!newh)
      return false;

    /* Don't forget to allocate space for the string and copy it */

    newh->value=malloc(lengthOfs*sizeof(char));
    /* What if either call to malloc returns NULL? */

    if(!newh->value)
    {
      free(newh);
      return false;
    }

    strcpy(newh->value,s);
    
    newh->next = q->head;
    q->head = newh;
    q->len++;
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
    /* You need to write the complete code for this function */
//  list_ele_t *last;
  list_ele_t *newh;
  int lengthOfs = strlen(s)+1;
  //int i;

  if (!q)
    return false;

  if((newh=malloc(sizeof(list_ele_t)))==NULL)
    return false;

  newh->value=malloc(lengthOfs*sizeof(char));
  /* What if either call to malloc returns NULL? */

  if(!newh->value)
    {
      free(newh);
      return false;
    }

  //  for(i=0;i<lengthOfs;i++)
  //  newh->value[i]=s[i];

  // newh->value[lengthOfs]='\0';

  strcpy(newh->value, s);
    
    q->tail->next = newh;
    q->tail = newh;
    newh->next = NULL;
    q->len++;

  /* Remember: It should operate in O(1) time */

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

  lengthOfsp = strlen(q->head->value)+1;
  copylen    = (lengthOfsp > bufsize) ? bufsize:lengthOfsp;

  if(sp) {

    for(i=0;i<copylen-1;i++)
      sp[i]=q->head->value[i];

    sp[copylen-1]='\0';

  }

    /* You need to fix up this code. */
  oldhead = q->head;
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
  
  
    /* You need to write the code for this function */
  if(!q || !q->head)
    return;
    
    start=q->head;
    cur=q->head;
    second=cur->next;
    
    while(second) {
        tmp=second->next;
        second->next=cur;
        cur=second;
        second=tmp;
    }
    q->head=cur;
    start->next = NULL;
    q->tail=start;
}

