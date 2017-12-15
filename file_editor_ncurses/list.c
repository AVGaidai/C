/** \file */
/*
 * Data structure 'linked list' 
 * Implementation by Anatoly Gaidai
 */
#include <stdlib.h>
#include <string.h>


/**
 * \brief Structure of the element of the linked list.
 */
struct node {

    struct node *next; /**< Pointer to next element */

    size_t size;       /**< Size of payload */
    void *payload;     /**< Payload (ex. array of the data) */
    
};


/**
 * \brief Structure of the linked list.
 */
struct llist {

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
void llist_init(struct llist *list)
{
    /* List is empty */
    list->nmemb = 0;
    list->head = NULL;
    list->tail = NULL;
}


/**
 * \brief Function addition of element to the top of the list.
 *
 * \param list is pointer to the list.
 * \param payload is adition element.
 * \param size is size of element.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int llist_push_front(struct llist *list, const void *payload, size_t size)
{
    struct node *node;
    
    node = (void *) malloc(sizeof(struct node));
    if (!node) {
        fprintf(stderr, "ERROR: list_elem_add()...\n");
        return 1;
    }

    node->size = size;
    node->payload = (void *) malloc(size);
    memcpy(node->payload, payload, size);

    if (list->head == NULL) {
        list->tail = node;
    }

    node->next = list->head;
    list->head = node;
    ++list->nmemb;   

    return 0;
}


/**
 * \brief Function addition element to the end of the list.
 * 
 * \param list is pointer to the list.
 * \param payload is addition element.
 * \param size is size of the element.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int llist_push_back(struct llist *list, const void *payload, size_t size)
{
    struct node *node;
    
    node = (void *) malloc(sizeof(struct node));
    if (!node) {
        fprintf(stderr, "ERROR: list_elem_add()");
        return 1;
    }

    node->size = size;
    node->payload = (void *) malloc(size);
    memcpy(node->payload, payload, size);
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    ++list->nmemb;
    
    return 0;
}


/**
 * \brief Function to free memory of the list.
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void llist_free(struct llist *list)
{
    struct node *node;

    for (node = list->head; node != NULL; node = list->head) {
        list->head = node->next;
        free(node->payload);
        free(node);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->nmemb = 0;
}


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
int llist_search(struct llist *list, void *dest, const void *src,
                 size_t size, int (*compare)(void *, const void *, size_t))
{
    struct node *node;

    if (compare == NULL) {
        for (node = list->head; node != NULL; node = node->next) {
            if (node->size == size &&
                memcmp((const void *) node->payload, src, size) == 0) {
                /* Found element */
                break;
            }
        }
        if (node == NULL) {
            /* Don't found element */
            return -1;
        }
    } else {
        for (node = list->head; node != NULL; node = node->next) {
            if (node->size == size && compare(node->payload, src, size) == 0) {
                /* Found element */
                break;
            }
        }
        if (node == NULL) {
            /* Don't found element */
            return -1;
        }
    }
   
    memcpy(dest, (const void *) node->payload, size);

    return 0;
}


/**
 * \brief Function to removing to the element from the list.
 * 
 * \param list is pointer to the list.
 * \param payload is removing element.
 * \param size is size of the element.
 *
 * \return the integer -1 upon failure and 0 upon successful completion.
 */
int llist_remove(struct llist *list, const void *payload, size_t size)
{
    struct node *node, *node_prev;

    for (node = list->head, node_prev = NULL; node != NULL; node = node->next) {
        if (node->size == size &&
            memcmp(payload, (const void *) node->payload, size) == 0) {
            if (node_prev == NULL) {
                if (node == list->tail) {
                    list->tail = NULL;
                }
                list->head = node->next;
                free(node->payload);
                free(node);
                --list->nmemb;
                return 0;
            } else {
                if (node == list->tail) {
                    list->tail = node_prev;
                }
                node_prev->next = node->next;
                free(node->payload);
                free(node);
                --list->nmemb;
                return 0;
            }
        } else {
            node_prev = node;
        }
    }

    return -1;
}


/**
 * \brief Function popping out first element in the list.
 *
 * \param list is pointer to the list.
 * \param size is size of the element.
 *
 * \return the integer NULL upon failure and pointer to 
 * element upon successful completion.
 */
void *llist_pop_front(struct llist *list, size_t *size)
{
    struct node *node;

    if (!list->nmemb) {
        fprintf(stdout, "List is empty!");
        return NULL;
    }

    node = list->head;
    list->head = node->next;
    if (list->nmemb == 1) {
        list->tail = NULL;
    }
        
    --list->nmemb;

    *size = node->size;
    
    return node->payload;
}

