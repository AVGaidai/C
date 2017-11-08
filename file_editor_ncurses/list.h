/** \file */
/*
 * Data structure 'List'
 * Implementation by Anatoly Gaidai
 */
#ifndef LIST_H
#define LIST_H


/**
 * \brief Structure of the list
 */
struct list {

    int nmemb;         /**< Number of the list members */
    
    struct node *head; /**< Pointer to first element in the list */
    struct node *tail; /**< Pointer to last element in the list */

};


/**
 * \brief Function initialization list.
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void list_init(struct list *);


/**
 * \brief Function addition of element to the top of the list.
 *
 * \param list is pointer to the list.
 * \param payload is adition element.
 * \param size is size of element.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int list_push_front(struct list *, const void *, size_t);


/**
 * \brief Function addition element to the end of the list.
 * 
 * \param list is pointer to the list.
 * \param payload is addition element.
 * \param size is size of the element.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int list_push_back(struct list *, const void *, size_t);


/**
 * \brief Function to free memory of the list.
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void list_free(struct list *);


/**
 * \brief Function of finding to the element of the list.
 *
 * \param list is pointer to the list.
 * \param dest is pointer to found element.
 * \param src is pointer to image finding element.
 * \size is size of the element.
 * \param compare is user's function to compare of the list elements.
 *
 * \return the integer -1 upon failure find and 0 upon successful find.
 */
int list_elem_find(struct list *, void *, const void *, size_t,
                   int (*)(void *, const void *, size_t));

/**
 * \brief Function to removing to the element from the list.
 * 
 * \param list is pointer to the list.
 * \param payload is removing element.
 * \param size is size of the element.
 *
 * \return the integer -1 upon failure and 0 upon successful completion.
 */
int list_elem_remove(struct list *, const void *, size_t);


/**
 * \brief Function popping out first element in the list.
 *
 * \param list is pointer to the list.
 * \param dest is pointer to popping out element.
 * \param size is size of the element.
 *
 * \return the integer NULL upon failure and pointer to
 * element upon successful completion.
 */
void *list_elem_pop_front(struct list *, size_t *);


#endif
