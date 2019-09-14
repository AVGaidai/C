/** \file */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/ioctl.h>


#define MAX_VALUE ~(1 << (sizeof(int) * 8 - 1))

#define BLACK   0
#define RED     1
#define DEFAULT 2

char bg_color[][9] = {
    "\E[40;38m",     /* BLACK   */
    "\E[41;38m",     /* RED     */
    "\E[0m\0"        /* DEFAULT */
};

/* Dimensions of terminal window */
struct winsize w;


/**
 * \brief Node of red-black tree.
 */
struct node {

    struct node *parent; /**< Pointer to parent of the node. */ 
    struct node *left;   /**< Pointer to left child of the node. */
    struct node *right;  /**< Pointer to right child of the node. */
    
    int color;           /**< Color of the node. */
    int key;             /**< Key of the node. */

    size_t size;         /**< Size of value. */
    void *value;         /**< Pointer to value. */
    
};



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
 *
 * \return no value.
 */
void RBT_Init(RB_Tree *T)
{
    T->nil = (struct node *) malloc(sizeof(struct node));
    T->nil->color = BLACK;
    T->nil->parent = NULL;
    T->nil->left = NULL;
    T->nil->right = NULL;
    T->nil->key = MAX_VALUE;
    T->nil->value = NULL;

    T->root = T->nil;
    
    T->nmemb = 0;
}


/**
 * \brief The left-rotate function.
 *
 * This function to left-rotate around the specified node.
 * This support function is not available to user.
 * 
 * \param T is pointer to red-black tree.
 * \param z is pointer to node of the tree about which to rotate.
 * 
 * \return no value.
 */
void RBT_Left_Rotate(RB_Tree *T, struct node *z)
{
    struct node *x;

    x = z->right;
    
    z->right = x->left;
    if (x->left != T->nil)
	x->left->parent = z;

    x->left = z;
    x->parent = z->parent;
    if (z->parent->left == z)
	z->parent->left = x;
    else if (z->parent->right == z)
	z->parent->right = x;
    else
	T->root = x;
    
    z->parent = x;
}


/**
 * \brief The right-rotate function.
 *
 * This function to right-rotate around the specified node.
 * This support function is not available to user.
 *
 * \param T is pointer to red-black tree.
 * \param z is pointer to node about which to rotate.
 * 
 * \return no value.
 */
void RBT_Right_Rotate(RB_Tree *T, struct node *z)
{
    struct node *x;

    x = z->left;
    
    z->left = x->right;
    if (x->right != T->nil)
	x->right->parent = z;

    x->right = z;
    x->parent = z->parent;
    if (z->parent->left == z)
	z->parent->left = x;
    else if (z->parent->right == z)
	z->parent->right = x;
    else
	T->root = x;
    
    z->parent = x;
}


/**
 * \brief Red-black tree property recovery function after insert function.
 * 
 * This function fixup possible violations of red-black properties after insert function.
 * This support function is not available to user.
 *
 * \param T is pointer to red-black tree.
 * \param z is poiner to node that can vioalte red-black properties.
 * 
 * \return no value.
 */
void RBT_Insert_Fixup(RB_Tree *T, struct node *z)
{
    struct node *x, *y;

    while (z != T->root && z->parent->color == RED) {
	x = z->parent;
	if (z->parent->parent->left == z->parent) {
	    y = x->parent->right;
	    /* Case 1 */
	    if (y->color == RED) {
		x->color = BLACK;
		y->color = BLACK;
		x->parent->color = RED;
		z = x->parent;
	    } else if (y->color == BLACK) {
		/* Case 2 */
		if (x->right == z) {
		    RBT_Left_Rotate(T, x);
		    z = x;
		    x = z->parent;
		}
		/* Case 3 */
		x->color = BLACK;
		x->parent->color = RED;
		RBT_Right_Rotate(T, x->parent);
	    }
	} else {
	    y = x->parent->left;
	    /* Case 4 */
	    if (y->color == RED) {
		x->color = BLACK;
		y->color = BLACK;
		x->parent->color = RED;
		z = x->parent;
	    } else if (y->color == BLACK) {
		/* Case 5 */
		if (x->left == z) {
		    RBT_Right_Rotate(T, x);
		    z = x;
		    x = z->parent;
		}
		/* Case 6 */
		x->color = BLACK;
		x->parent->color = RED;
		RBT_Left_Rotate(T, x->parent);
	    }
	}
    }
    T->root->color = BLACK;
}
		
		
	    	

/**
 * \brief The function of inserting an node with the specified key and value.
 *
 * \param T is pointer to red-black tree.
 * \param key is key of insertion node.
 * \param value is pointer to memory area with data.
 * \param size is size of value.
 *
 * \return zero if success.
 */
int RBT_Insert(RB_Tree *T, int key, void *value, size_t size)
{
    struct node new;

    new.color = RED;
    new.parent = T->nil;
    new.left = T->nil;
    new.right = T->nil;
    new.key = key;
    new.size = size;
    new.value = malloc(size);
    memcpy(new.value, value, size);

    struct node **curr = &T->root;
    struct node **prev = &T->root;
    
    while (*curr != T->nil) {
	prev = curr;
	if (key > (*curr)->key)
	    curr = &(*curr)->right;
	else
	    curr = &(*curr)->left;
    }

    if (*curr == T->root) {
	prev = &T->nil;
    }
    *curr = (struct node *) malloc(sizeof(new));
    
    memcpy(*curr, &new, sizeof(new));
    (*curr)->parent = *prev;
      
    /* fixup */
    RBT_Insert_Fixup(T, *curr);
    
    T->nmemb++;

    return 0;
}


/**
 * \brief The find function by key.
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
int RBT_Find(RB_Tree *T, int key, void **value, size_t *size)
{
    struct node *curr = T->root;
    
    while (curr != T->nil) {
	if (key > curr->key) {
	    curr = curr->right;
	} else if (key < curr->key) {
	    curr = curr->left;
	} else {
	    *value = curr->value;
	    *size = curr->size;
	    break;
	}
    }

    if (curr == T->nil)
	return -1;
    else
	return 0;
}


/**
 * \brief The replacement functioт (a by b).
 * 
 * This function of replacing node 'a' by node 'b'.
 * This support function is not available to user.
 *
 * \param T is pointer to red-black tree.
 * \param a is pointer to first node.
 * \param b is pointer to second node.
 *
 * \return no value.
 */
void RBT_Transplant(RB_Tree *T, struct node *a, struct node *b)
{
    if (a->parent == T->nil) {
	T->root = b;
    } else if (a->parent->left == a) {
	a->parent->left = b;
    } else {
	a->parent->right = b;
    }
    b->parent = a->parent;
}


/**
 * \brief The function of finding node with minimum key.
 *
 * This function finds node with minimum key in red-black tree/subtree.
 * This support function is not available to user.
 *
 * \param T is pointer to red-black tree.
 * \param root is pointer to root of red-black tree/subtree.
 *
 * \return Pointer to node with minimal key in specified red-black tree/subtree.
 * \return T->nil if red-black tree/subtree is empty.
 */
struct node *RBT_Minimum(RB_Tree *T, struct node *root)
{
    struct node *curr = root;
    struct node *prev = root;
    
    while (curr != T->nil) {
	prev = curr;
	curr = curr->left;
    }
    
    if (prev == T->nil)
	return T->nil;
    else
	return prev;
}




/**
 * \brief Red-black tree property recovery function after delete function.
 * 
 * This function fixup possible violations of red-black properties after delete function.
 * This support function is not available to user.
 *
 * \param T is pointer to red-black tree.
 * \param x is poiner to node that can vioalte red-black properties.
 *
 * \return no value.
 */
void RBT_Delete_Fixup(RB_Tree *T, struct node *x)
{
    struct node *w;   /* Brathers of 'x' node */
    
    while (x->color == BLACK && x != T->root) {
	if (x->parent->left == x) {
	    w = x->parent->right;
	    /* Case 1 */
	    if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		RBT_Left_Rotate(T, x->parent);
		w = x->parent->right;
	    }
	    /* Case 2 */
	    if (w->left->color == BLACK && w->right->color == BLACK) {
	        w->color = RED;
		x = x->parent;
		continue;
	    /* Case 3 */
	    } else if (w->right->color == BLACK) {
		w->left->color = BLACK;
		w->color = RED;
		RBT_Right_Rotate(T, w);
		w = x->parent->right;
	    }
	    /* Case 4 */
	    w->color = x->parent->color;
	    x->parent->color = BLACK;
	    w->right->color = BLACK;
	    RBT_Left_Rotate(T, x->parent);
	    x = T->root;
	} else {
	    /* Case 5 */
	    w = x->parent->left;
	    if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		RBT_Right_Rotate(T, x->parent);
		w = x->parent->left;
	    }
	    /* Case 6 */
	    if (w->left->color == BLACK && w->right->color == BLACK) {
	        w->color = RED;
		x = x->parent;
		continue;
	    /* Case 7 */
	    } else if (w->left->color == BLACK) {
		w->right->color = BLACK;
		w->color = RED;
		RBT_Left_Rotate(T, w);
		w = x->parent->left;
	    }
	    /* Case 8 */
	    w->color = x->parent->color;
	    x->parent->color = BLACK;
	    w->left->color = BLACK;
	    RBT_Right_Rotate(T, x->parent);
	    x = T->root;
	}
    }
    x->color = BLACK;
}
	    
		

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
int RBT_Delete(RB_Tree *T, int key)
{
    struct node *curr = T->root;
    
    while (curr != T->nil) {
	if (key > curr->key) {
	    curr = curr->right;
	} else if (key < curr->key) {
	    curr = curr->left;
	} else {
	    break;
	}
    }

    struct node *z, *y, *x;
    int orig_color;
    
    z = curr;
    if (curr != T->nil) {
	free(curr->value);
	orig_color = z->color;
	if (z->left == T->nil) {
	    x = z->right;
	    RBT_Transplant(T, z, z->right);
	} else if (z->right == T->nil) {
	    x = z->left;
	    RBT_Transplant(T, z, z->left);
	} else {
	    y = RBT_Minimum(T, z->right);
	    x = y->right;
	    orig_color = y->color;
	    if (y->parent == z) {
		x->parent = y;
	    } else {
		RBT_Transplant(T, y, y->right);
		y->right = z->right;
		y->right->parent = y;
	    }
	    RBT_Transplant(T, z, y);
	    y->left = z->left;
	    y->left->parent = y;
	    y->color = z->color;
	}
	free(z);

  	/* delete-fixup */
	if (orig_color == BLACK) {
	    RBT_Delete_Fixup(T, x);
	}
	
	return 0;
    }

    return -1;
}
  
/**
 * \brief The print node of the tree function.
 * 
 * This function is auxiliary to the 'RBT_Print_Tree' function
 * and is hidden to the user.
 *
 * \param node is pointer to node of the tree.
 * \param lvl is level/depth of current node in the tree.
 * \param max_lvl is maximum level/depth of the tree.
 * \param pos is pointer to auxiliary massive.
 *
 * \return no value.
 */ 
void
RBT_Print_Node(struct node *node, int lvl, int max_lvl, int *pos)
{
   /*
    * 'start' is starting print position for current level/depth.
    * 'step' is distance between nodes for current level/depth.
    * 'x' is horizontal starting position for current node.
    * 'y' is vertical starting position for corrent node.
    */  
    int start, step, x, y;

    step = 14;
    for (int i = 0; i < (max_lvl - lvl); ++i)
	step *= 2;
    
    start = 12;
    for (int i = 1; i < (max_lvl - lvl); ++i)
	start *= 2;
    
    if (max_lvl - lvl) {
	start += (max_lvl - lvl - 1) * 2 - 5;
    } else {
	start = 0;
    }
    
    x = start + pos[lvl] * step;
    y = (lvl + 1) * 2;

    printf("\E[%d;%dH", y, x);
    printf("%s %10d %s\n",
	   bg_color[node->color], node->key, bg_color[DEFAULT]);
}



/**
 * \brief The function of finding depth of red-black tree.
 *
 * This function is auxiliary to the 'RBT_Print_Tree' function
 * and is hidden to the user.
 *
 * \param T is pointer to red-black tree.
 * \param root is pointer to root of red-black tree.
 *
 * \return no value. 
 */
int RBT_Depth(RB_Tree *T, struct node *root)
{
    static int lvl = -1;
    static int max_lvl = -1;

    ++lvl;
    if(lvl > max_lvl)
	max_lvl = lvl;
    if (root != T->nil) {
	RBT_Depth(T, root->left);
	RBT_Depth(T, root->right);
    }
    --lvl;

    return max_lvl;
}

/**
 * \brief The print red-black tree function.
 *
 * \param T is pointer to red-black tree.
 *
 * \return no value.
 */
void RBT_Print(RB_Tree *T)
{
    static int lvl = 0;
    static int max_lvl = 0;
    static int max_length = 1;
    static int *pos;
    static int cnt;
    static struct node *curr, *prev;
    
    if (lvl == 0) {
	curr = T->root;
	max_lvl = RBT_Depth(T, curr);
	max_length = 1;
	cnt = 0;
	pos = (int *) calloc(max_lvl + 1, sizeof(int));
	for (int i = 0; i < max_lvl - 1; ++i)
	    max_length *= 2;
	max_length *= 14;
        /* Clear screen */
	printf("\E[H\E[2J\E[0m");
	/* Determine size of terminal window */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (max_length > w.ws_col || (max_lvl + 1) * 2 > w.ws_row) {
	    printf("The dimensions of the terminal "
		   "window are too small for print three\n");
	    return;
	}
    }
    
    ++lvl;
    if (curr != T->nil) {
	prev = curr;
	curr = curr->left;
	RBT_Print(T);
	curr = prev;
	curr = curr->right;
       	RBT_Print(T);
	curr = prev;
	RBT_Print_Node(curr, lvl, max_lvl, pos);
	prev = prev->parent;
	++cnt;
    }
    ++pos[lvl];
    --lvl;

    if (cnt == T->nmemb) free(pos);
    printf("\E[%d;0H\n\n\n", (max_lvl + 1) * 2);
}


/**
 * \brief The delete red-black tree function.
 *
 * This function to free memory for red-black tree.
 *
 * \param T is pointer to red-black tree.
 */
void RBT_Free(RB_Tree *T)
{
    static struct node *prev, *curr;
    static int flg = 0;
    
    if (!flg) {
	curr = T->root;
	flg = 1;
    }
        
    if (curr != T->nil) {
	prev = curr;
	curr = curr->left;
	RBT_Free(T);
	curr = prev;
	curr = curr->right;
	RBT_Free(T);
	curr = prev;
	prev = prev->parent;
	free(curr->value);
	free(curr);
	T->nmemb--;
    }

    if (T->nmemb == 0) {
	free(T->nil);
    }
}
