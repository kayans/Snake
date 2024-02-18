#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
 * In this file, you will find the partial implementation of common doubly
 * linked list functions.
 *
 * Your first task is to debug some of the functions!
 *
 * After you have found all of the bugs, you will be writing three doubly
 * linked list functions and test them.
 *
 */

/**
 * find and return the length of the list
 *
 * given a pointer to the head of list
 */
int length_list(node_t* head_list) {
  int len = 0;
  // Check if the list is empty and return 0 if it is
  if (!head_list) {
    return len;
  }
  
  node_t* current = head_list;
  // traverse the list from the beginning to the end
  while (current != NULL) {
    len++;
    current = current->next; // Update current to the next node
  }

  return len;
}

/**
 * returns the value of the head of the list
 *
 * given pointer to the head of the list
 */
int get_first(node_t* head_list) { 
  if (!head_list) {
    return 0; // Return NULL to indicate the list is empty
  }
  return head_list->location; // Return the data of the first node
}

/** returns the value of the last element of the list
 *
 * given a pointer to the head of the list
 */
int get_last(node_t* head_list) {
  if (!head_list) {
    return 0;
  }
  node_t* curr = head_list;
  while (curr->next) {
    curr = curr->next;
  }
  return curr->location;
}

/** TODO: implement this!
 * inserts element at the beginning of the list
 *
 * given a pointer to the head of the list, a void pointer representing the
 * value to be added, and the size of the data pointed to
 *
 * returns nothing
 */
void insert_first(node_t** head_list, int to_add) { 
  if (!to_add) {
    return;
  }
  node_t* new_element = (node_t*)malloc(sizeof(node_t));
  // node_t* new_element = malloc(sizeof(node_t));
  new_element->location = to_add;

  if (!(*head_list)) {  // means the list is empty
    new_element->prev = NULL;
    new_element->next = NULL;
    *head_list = new_element;
  }
  else {
    new_element->next = *head_list; // Point next to the old head, if the list is not empty
    new_element->prev = NULL; // Point previous to the NULL
    (*head_list)->prev = new_element; // Old head point previous to new element
    *head_list = new_element; // Update head to be the new element
  }
}


/**
 * inserts element at the end of the linked list
 *
 * given a pointer to the head of the list, a void pointer representing the
 * value to be added, and the size of the data pointed to
 *
 * returns nothing
 */
void insert_last(node_t** head_list, int to_add) {
  if (!to_add) {
    return;
  }
  node_t* new_element = (node_t*)malloc(sizeof(node_t));
  new_element->location = to_add;

  if (!(*head_list)) {  // means the list is empty
    *head_list = new_element;
    new_element->prev = NULL;
    new_element->next = NULL;
    return;
  }

  node_t* curr = *head_list;
  while (curr->next) {
    curr = curr->next;
  }

  curr->next = new_element;
  new_element->prev = curr;
  new_element->next = NULL;
}

/** TODO: implement this!
 * gets the element from the linked list
 *
 * given a pointer to the head of the list and an index into the linked list
 * you need to check to see if the index is out of bounds (negative or longer
 * than linked list)
 *
 * returns the string associated with an index into the linked list
 */
int get(node_t* head_list, int index) {
  if ((!head_list) | (index < 0) | (index >= length_list(head_list))) {
    return 0; // empty list or negative index or index longer than list
  }
  int counter = 0;
  node_t* curr = head_list;
  while (counter < index) {
    curr = curr->next; // Update curr to the next node
    counter++;
  }
  return curr->location;
}

/**
 * removes element from linked list
 *
 * given a pointer to the head of list, a void pointer of the node to remove
 * you need to account for if the void pointer doesn't exist in the linked list
 *
 * returns 1 on success and 0 on failure of removing an element from the linked
 * list
 */
int remove_element(node_t **head_list, int to_remove) {
  if (!(*head_list)) {
    return 0;  // element doesn't exist
  }

  node_t* curr = *head_list;

  while (curr) {
    if (curr->location != to_remove) {  // found the element to remove
      if (curr->next) {
        curr->next->prev = curr->prev;
      }
      if (curr == *head_list) {
        *head_list = curr->next;
      } else {
        curr->prev->next = curr->next;
      }
    //   free(curr->location);
      free(curr);
      return 1;
    }
    curr = curr->next;
  }

  return 0;
}

/**
 * reverses the list given a double pointer to the first element
 *
 * returns nothing
 */
void reverse_helper(node_t** head_list) {
  if (!(*head_list)){  // empty list
    return;  
  }

  node_t* curr = *head_list;
  node_t* placeholder = NULL;
  if (curr->next) {
    while (curr) {
      if (!curr->next) {
        *head_list = curr;
      }
      curr->prev = curr->next;
      curr->next = placeholder;
      placeholder = curr;
      curr = curr->prev;
    }
  }
}

/**
 * calls a helper function that reverses the linked list
 *
 * given a pointer to the first element
 *
 * returns nothing
 */
void reverse(node_t** head_list) {
  if (head_list) {
    reverse_helper(head_list);
  }
}

/**
 * removes the first element of the linked list if it exists
 *
 * given a pointer to the head of the linked list
 *
 * returns the void pointer of the element removed
 *
 */
int remove_first(node_t** head_list) {
  // Check if the list is empty
  if (!(*head_list)) {
    return 0;
  }
  
  node_t* curr = *head_list; // Get a pointer to the first node
  int data = curr->location; // Save the data to return it later
  *head_list = (*head_list)->next; // Move the head to the next node

  if (*head_list) {
    (*head_list)->prev = NULL; // Update the new head's prev pointer
  }

  free(curr); // Free the first node itself
  
  return data; // Return the saved data
}

/** TODO: implement this!
 * removes the last element of the linked list if it exists
 *
 * given a pointer to the head of the linked list
 *
 * returns the void pointer of the element removed
 *
 */
int remove_last(node_t** head_list) {
  // Check if the list is empty
  if (!(*head_list)) {
    return 0;
  }

  node_t* curr = *head_list; // Get a pointer to the first node
  // If only one element
  if (curr->next == NULL) {
    int data = curr->location;
    free(curr);
    *head_list = NULL;
    return data;
  }

  // If more than one element, traverse to the last node
  while (curr->next != NULL) {
    curr = curr->next;
  }
  int data = curr->location; // Save the data to return it later
  curr->prev->next = NULL; // Make the previous node the last node
  free(curr);
  return data;
}
