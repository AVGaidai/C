#include "singly_linked_list/sllist.h"



/**
 * \brief Structure of the queue by singly linked list.
 */
struct queue {

    struct sllist list;  /**< Singly linked list */

};


/**
 * \brief Function initialization queue.
 *
 * Computational complexity: T(n) = O(1).
 *
 * \param queue is pointer to the queue.
 *
 * \return no value.
 */
void queue_init(struct queue *queue)
{
    sllist_init(&(queue->list));
}


/**
 * \brief Function to free memory of the queue.
 *
 * Computational complexity: T(n) = O(n).
 *
 * \param queue is pointer to the queue.
 *
 * \return no value.
 */
void queue_free(struct queue *queue)
{
    sllist_free(&(queue->list));
}


/**
 * \brief Function addition node to the back of the queue.
 * 
 * Cumputational complexity: T(n) = O(1).
 *
 * \param queue is pointer to the queue.
 * \param payload is useful node value.
 * \param size is size of node payload.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int queue_push(struct queue *queue, const void *payload, size_t size)
{
    return sllist_insert_back(&(queue->list), payload, size);
}


/**
 * \brief Function extracts payload of first node in the queue.
 *
 * Computational complexity: T(n) = O(1).
 * 
 * \param queue is pointer to the queue.
 * \param size is size of the payload.
 *
 * \return the integer NULL upon failure and copy to 
 * node payload upon successful completion.
 */
void *queue_pop(struct queue *queue, size_t *size)
{
    return sllist_eject(&(queue->list), size);
}


/**
 * \brief Function of finding to the node of the queue by payload.
 *
 * Computational complexity: T(n) = O(n).
 * queue->list->curr points to found node. 
 *
 * \param queue is pointer to the queue.
 * \param pattern is pointer to pattern of finding payload.
 * \size is size of the payload.
 * \param compare is user's function to compare of the queue nodes.
 *
 * \return the integer -1 upon failure find and 0 upon successful find.
 */
int queue_search(struct queue *queue, const void *pattern, size_t size,
                 int (*compare)(void *, const void *, size_t))
{
    return sllist_search(&(queue->list), pattern, size, compare);
}


/**
 * \brief Function to removing to the element from the queue.
 * 
 * Computational complexity: T(n) = O(n).
 *
 * \param queue is pointer to the queue.
 * \param payload is pointer to pattern of removing payload.
 * \param size is size of the payload.
 *
 * \return the integer -1 upon failure and 0 upon successful completion.
 */
int queue_remove(struct queue *queue, const void *payload, size_t size)
{
    return sllist_remove(&(queue->list), payload, size);
}


/**
 * \brief Function to getting current number of queue members.
 * 
 * Computational complexity: T(n) = O(1).
 *
 * \param queue is pointer to the queue.
 *
 * \return the integer number of queue members.
 */
int queue_size(struct queue *queue)
{
    return queue->list.nmemb;
}
