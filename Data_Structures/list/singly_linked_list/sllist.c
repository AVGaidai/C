/** \file */
/*
 * Data structure 'singly linked list' 
 * Implementation by Anatoly Gaidai
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
void sllist_init(struct sllist *list)
{
    /* List is empty */
    list->nmemb = 0;
    list->head = NULL;
    list->tail = NULL;
    list->curr = NULL;

}


/**
 * \brief Function addition of node to the top of the list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 * \param payload is useful node value.
 * \param size is size of node payload.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int sllist_insert(struct sllist *list, const void *payload, size_t size)
{
    struct slnode *node;
    
    node = (void *) malloc(sizeof(struct slnode));
    if (!node) {
        fprintf(stderr, "ERROR: sllist_insert()...\n");
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

    if (list->curr == NULL)
        list->curr = list->head;
    
    return 0;
}


/**
 * \brief Function addition node to the end of the list.
 * 
 * Cumputational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 * \param payload is useful node value.
 * \param size is size of node payload.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int sllist_insert_back(struct sllist *list, const void *payload, size_t size)
{
    struct slnode *node;
    
    node = (void *) malloc(sizeof(struct slnode));
    if (!node) {
        fprintf(stderr, "ERROR: sllist_insert()...\n");
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

    if (list->curr == NULL)
        list->curr = list->head;
    
    return 0;
}


/**
 * \brief Function to free memory of the list.
 *
 * Computational complexity: T(n) = O(n).
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void sllist_free(struct sllist *list)
{
    struct slnode *node;

    for (node = list->head; node != NULL; node = list->head) {
        list->head = node->next;
        free(node->payload);
        free(node);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->curr = NULL;
    list->nmemb = 0;
}


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
int sllist_search(struct sllist *list, const void *pattern, size_t size,
                  int (*compare)(void *, const void *, size_t))
{
    struct slnode *node;

    if (compare == NULL) {
        for (node = list->head; node != NULL; node = node->next) {
            if (node->size == size &&
                memcmp((const void *) node->payload, pattern, size) == 0) {
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
            if (node->size == size &&
                compare(node->payload, pattern, size) == 0) {
                /* Found element */
                break;
            }
        }
        if (node == NULL) {
            /* Don't found element */
            return -1;
        }
    }
    
    list->curr = node;

    return 0;
}


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
int sllist_remove(struct sllist *list, const void *payload, size_t size)
{
    struct slnode *node, *node_prev;

    for (node = list->head, node_prev = NULL; node != NULL; node = node->next) {
        if (node->size == size &&
            memcmp(payload, (const void *) node->payload, size) == 0) {
            if (node_prev == NULL) {
                if (node == list->tail) {
                    list->tail = NULL;
                }
                list->head = node->next; 
                if (node == list->curr)
                    list->curr = list->head;
                free(node->payload);
                free(node);
                --list->nmemb;
                return 0;
            } else {
                if (node == list->tail) {
                    list->tail = node_prev;
                }
                node_prev->next = node->next;
                if (node == list->curr)
                    list->curr = node_prev;
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
void *sllist_eject(struct sllist *list, size_t *size)
{
    struct slnode *node;
    void *payload;

    if (!list->nmemb) {
        fprintf(stdout, "List is empty!\n");
        *size = 0;
        return NULL;
    }

    node = list->head;
    list->head = node->next;
    if (list->nmemb == 1) {
        list->tail = NULL;
    }
    if (node == list->curr)
        list->curr = list->head;
    --list->nmemb;

    *size = node->size;

    payload = malloc(*size);
    memcpy(payload, node->payload, *size);
    free(node->payload);
    free(node);
    
    return payload;
}


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
void *sllist_eject_back(struct sllist *list, size_t *size)
{
    struct slnode *node, *node_prev;
    void *payload;
    
    if (!list->nmemb) {
        fprintf(stdout, "List is empty!\n");
        *size = 0;
        return NULL;
    }
    
    for (node = list->head, node_prev = NULL;
         node->next != NULL; node = node->next)
        node_prev = node;
    
    --list->nmemb;
    
    if (node_prev == NULL) {
        list->head = NULL;
    }
    
    list->tail = node_prev;
    if (node == list->curr)
        list->curr = node_prev;

    *size = node->size;
    
    payload = malloc(*size);
    memcpy(payload, node->payload, *size);
    free(node->payload);
    free(node);
    
    return payload;
}


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
void *sllist_eject_curr(struct sllist *list, size_t *size)
{
    void *payload;
    
    if (!list->nmemb) {
        fprintf(stdout, "List is empty!\n");
        *size = 0;
        return NULL;
    }

    *size = list->curr->size;

    payload = malloc(*size); 
    memcpy(payload, list->curr->payload, *size);
    sllist_remove(list, (const void *) payload, *size);

    return payload;    
}


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
void *sllist_get(struct sllist *list, size_t *size)
{
    void *payload;
    
    if (!list->nmemb) {
        fprintf(stdout, "List is empty!\n");
        return NULL;
    }
    
    *size = list->head->size;

    payload = malloc(*size);
    memcpy(payload, list->head->payload, *size);
    
    return payload;
}

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
void *sllist_get_back(struct sllist *list, size_t *size)
{
    void *payload;
    
    if (!list->nmemb) {
        fprintf(stdout, "List is empty!\n");
        return NULL;
    }
    
    *size = list->tail->size;

    payload = malloc(*size);
    memcpy(payload, list->tail->payload, *size);
    
    return payload;
}


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
void *sllist_get_curr(struct sllist *list, size_t *size)
{
    void *payload;
    
    if (!list->nmemb) {
        fprintf(stdout, "List is empty!\n");
        return NULL;
    }
    
    *size = list->curr->size;

    payload = malloc(*size);
    memcpy(payload, list->curr->payload, *size);
    
    return payload;
}


/**
 * \brief Function moves pointer 'curr' to next node of the list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 *
 * \return the integer 1 upon end pointer and 0 upon moved pointer.
 */
int sllist_next_ptr(struct sllist *list)
{
    if (list->curr != NULL) {
        if (list->curr == list->tail)
            return 1;
        list->curr = list->curr->next;
    }

    return 0;
}


/**
 * \brief Function moves pointer 'curr' to head of the list.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param list is pointer to the list.
 *
 * \return no value.
 */
void sllist_drop_ptr(struct sllist *list)
{
    list->curr = list->head;
}
