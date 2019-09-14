/** \file */
#ifndef RBT_H
#define RBT_H

#include <stdio.h>

/** 
 * \brief Red-black tree.
 */
typedef struct {

    struct node *root;   /**< Pointer to root of the tree. */ 
    struct node *nil;    /**< Pointer to nil element. */

    size_t nmemb;        /**< Number of members in the tree. */
    
} RB_Tree;


/**
 * \brief The initializer function.
 *
 * \param T is pointer to red-black tree.
 */
void RBT_Init(RB_Tree *T);


/**
 * \brief The function of inserting an node with the specified key and value.
 *
 * \param T is pointer to red-black tree.
 * \param key is key of insertion node.
 * \param value is pointer to memory area with data.
 * \param size is size of value.
 *
 * \return 0.
 */
int RBT_Insert(RB_Tree *T, int key, void *value, size_t size);

/**
 * \brief Find function by key.
 *
 * This function finds node with specified key in red-black tree.
 *
 * \param T is pointer to red-black tree.
 * \param key is key of finding node.
 * \param value is pointer to memory area with data.
 * \param size is pointer to size of memory area with data.
 *
 * \return 0 if node with specified key is found.
 * \return -1 if node with specified key is not found.
 */
int RBT_Find(RB_Tree *T, int key, void **value, size_t *size);

/**
 * \brief The function of deleting node with specified key.
 *
 * This function finds and deletes node with specified key from red-black tree.
 *
 * \param T is pointer to red-black tree.
 * \param key is key of deletion node.
 *
 * \return 0 if node is found and remove.
 * \return -1 if node is not found.
 */
int RBT_Delete(RB_Tree *T, int key);

/**
 * \brief The print red-black three function.
 *
 * \param T is pointer to red-black tree.
 */
void RBT_Print(RB_Tree *T);

/**
 * \brief The delete red-black tree function.
 *
 * This function to free memory for red-black tree.
 *
 * \param T is pointer to red-black tree.
 */
void RBT_Free(RB_Tree *T);

#endif

