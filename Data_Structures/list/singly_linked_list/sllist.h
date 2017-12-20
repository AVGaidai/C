/** \file */
/*
 * Data structure 'singly linked list'
 * Implementation by Anatoly Gaidai
 */
#ifndef SLLIST_H
#define SLLIST_H

#include <stdlib.h>


/**
 * \brief Structure of the element of the singly linked list.
 */
struct slnode {

    struct slnode *next; /**< Pointer to next node of the list */

    size_t size;         /**< Size of payload */
    void *payload;       /**< Payload (ex. array of the data) */
    
};


/**
 * \brief Structure of the singly linked list.
 */
struct sllist {

    int nmemb;           /**< Number of the list members */

    struct slnode *curr; /**< Pointer to current node for navigate the list */
    struct slnode *head; /**< Pointer to first node in the list */
    struct slnode *tail; /**< Pointer to last node in the list */

};


/**
 * \brief Function initialization list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void sllist_init(struct sllist *);


/**
 * \brief Function addition of node to the front of the list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 * \param payload is useful node value.
 * \param size is size of node payload.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int sllist_insert(struct sllist *, const void *, size_t );


/**
 * \brief Function addition node to the back of the list.
 * 
 * Cumputational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 * \param payload is useful node value.
 * \param size is size of node payload.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int sllist_insert_back(struct sllist *, const void *, size_t);


/**
 * \brief Function to free memory of the list.
 *
 * Computational complexity: T(n) = O(n).
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void sllist_free(struct sllist *);


/**
 * \brief Function of finding to the node of the list by payload.
 *
 * Computational complexity: T(n) = O(n).
 * list->curr points to found node. 
 *
 * \param list is pointer to the list.
 * \param pattern is pointer to pattern of finding payload.
 * \size is size of the payload.
 * \param compare is user's function to compare of the list nodes.
 *
 * \return the integer -1 upon failure find and 0 upon successful find.
 */
int sllist_search(struct sllist *, const void *, size_t,
                  int (*)(void *, const void *, size_t));


/**
 * \brief Function to removing to the element from the list.
 * 
 * Computational complexity: T(n) = O(n).
 *
 * \param list is pointer to the list.
 * \param payload is pointer to pattern of removing payload.
 * \param size is size of the payload.
 *
 * \return the integer -1 upon failure and 0 upon successful completion.
 */
int sllist_remove(struct sllist *, const void *, size_t);


/**
 * \brief Function extracts payload of first node in the list.
 *
 * Computational complexity: T(n) = O(1).
 * 
 * \param list is pointer to the list.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *sllist_eject(struct sllist *, size_t *);


/**
 * \brief Function extracts payload of last node in the list.
 *
 * Computational complexity: T(n) = O(n).
 * 
 * \param list is pointer to the list.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *sllist_eject_back(struct sllist *, size_t *);


/**
 * \brief Function extracts payload of current node in the list.
 *
 * Computational complexity: T(n) = O(n).
 * 
 * \param list is pointer to the list.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *sllist_eject_curr(struct sllist *, size_t *);


/**
 * \brief Function getting payload of first node in the list.
 *
 * Computational complexity: T(n) = O(1).
 * 
 * \param list is pointer to the list.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *sllist_get(struct sllist *, size_t *);


/**
 * \brief Function getting payload of last node in the list.
 *
 * Computational complexity: T(n) = O(1).
 * 
 * \param list is pointer to the list.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *sllist_get_back(struct sllist *, size_t *);


/**
 * \brief Function getting payload of current node in the list.
 *
 * Computational complexity: T(n) = O(1).
 * 
 * \param list is pointer to the list.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *sllist_get_curr(struct sllist *, size_t *);


/**
 * \brief Function moves pointer 'curr' to next node of the list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 *
 * \return the integer 1 upon pointer to last node or list is empty
 *         and 0 upon moved pointer.
 */
int sllist_next_node(struct sllist *);


/**
 * \brief Function moves pointer 'curr' to prev node of the list.
 *
 * Computational complexity: T(n) = O(n).
 *
 * \param list is pointer to the list.
 *
 * \return the integer 1 upon pointer to first node or list is empty
 *         and 0 upon moved pointer.
 */
int sllist_prev_node(struct sllist *);
        

/**
 * \brief Function moves pointer 'curr' to head of the list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void sllist_drop_ptr(struct sllist *);


#endif
