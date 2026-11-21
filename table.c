#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "table.h"

int comparisons = 0;
int rotations = 0;


void print_time(int time) {
    const char* days[] = {"Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim"};
    printf("%s %02d:%02d \n", days[time / (24 * 60)], (time % (24 * 60)) / 60, time % 60);
}

Row* create_row(int id, const char* value) {
    Row* node = malloc(sizeof(Row));

    if(node == NULL) {
        fprintf(stderr, "Error: failed to allocate memory for Row\n");
        exit(1);
    }
    
    node->id = id;

    node->value = value != NULL ? str_dup(value) : NULL;
    if (value != NULL && node->value == NULL) {
        fprintf(stderr, "Error: failed to duplicate value\n");
        exit(1);
    }

    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

void insert_row(Row* node, int id, const char* value) {
    if (id == node->id) {
        printf("Duplicate entry \n");
        return;
    }

    if (id < node->id) {
        if (node->left == NULL) {
            node->left = create_row(id, value);
        } else {
            insert_row(node->left, id, value);
        }
    } else if (id > node->id) {
        if (node->right == NULL) {
            node->right = create_row(id, value);
        } else {
            insert_row(node->right, id, value);
        }
    }
     
}

int at(int day, int hour, int minute) { // day : 0 = lundi ... 6 = dimanche
    return day * 24 * 60 + hour * 60 + minute;
}

Row* select_on_id(Row* node, int id) {
    if (node == NULL) return NULL; // arbre vide : absente

    comparisons++;


    if (id == node->id) return node; // trouvée
    if (id < node->id) return select_on_id(node->left, id);
    return select_on_id(node->right, id);
}

void select_order_by(const Row* node) {
    if (node == NULL) {
        return;
    }

    select_order_by(node->left);
    print_time(node->id);
    printf(" %s\n", node->value);
    select_order_by(node->right);   
}

Row* select_min(Row* node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->left != NULL) {
        return select_min(node->left);
    } else {
        return node;
    }
}

Row* select_max(Row* node) {
    if (node == NULL) {
        return NULL;
    }

    if(node->right != NULL) {
        return select_max(node->right);
    } else {
         return node;
    }
}
Row* select_next(Row* node, int id) {
    if (node == NULL) {
        return NULL;
    }

    if (id == node->id)
    {
        return node;
    }
    
    if (id < node->id )
    {
        Row* result = select_next(node->left, id);
        if (result != NULL)
        {
            return result;
            // pas de resut valable donc on return la racine
        } else {
            return node;
        }
        
    } else if(id > node->id) {
        Row* result = select_next(node->right, id);
        if (result != NULL)
        {
            return result;  
        } 
    }
    return NULL;
}

Row* delete_row(Row* node, int id) {
    if (node == NULL) {
        return NULL;
    }

    if (id < node->id) {
        node->left = delete_row(node->left, id);
    } else if (id > node->id) {
        node->right = delete_row(node->right, id);
    } else {
        // pas d enfant on supprime le noeud courant
        if (node->left == NULL && node->right == NULL) {
            free(node->value);
            free(node);
            return NULL;
        }
        // libère a gauche
        else if (node->left != NULL && node->right == NULL) {
            Row* child = node->left;
            free(node->value);
            free(node);
            return child;
        }
        //libere a droite
        else if (node->left == NULL && node->right != NULL) {
            Row* child = node->right;
            free(node->value);
            free(node);
            return child;
        }
        // copie l enfant le plus petit du cote droit a la place du courant
        // et libere son ancien noeud  
        else {
            Row* successor = select_min(node->right);

            free(node->value);

            node->id = successor->id;
            node->value = successor->value != NULL
                ? str_dup(successor->value)
                : NULL;

            if (successor->value != NULL && node->value == NULL) {
                fprintf(stderr, "Error: failed to duplicate value\n");
                exit(1);
            }

            node->right = delete_row(node->right, successor->id);
        }

    }
    return node;
}

void drop_table(Row* node) {
    if (node == NULL) {
        return;
    }

    drop_table(node->left);
    drop_table(node->right);
    free(node->value);
    free(node);
}

int node_height(const Row* node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;  
}

void update_height(Row* node) {
    if (node == NULL) {
        return;
    }
    
    int leftHeight = node_height(node->left);
    int rightHeight = node_height(node->right);
    
    if(leftHeight > rightHeight) {
        node->height = 1 + leftHeight;
    } else {
        node->height = 1 + rightHeight;
    }
}

Row* rotate_left(Row* node) {
    Row* x = node;
    Row* y = x->right;
    rotations++;

    x->right = y->left;
    y->left = x;

    update_height(x);
    update_height(y);

    return y;
}

Row* rotate_right(Row* node) {
    Row* x = node;
    Row* y = x->left;
    rotations++;

    x->left = y->right;
    y->right = x;

    update_height(x);
    update_height(y);

    return y;
}


Row* rebalance(Row* node) {
    if (node == NULL) {
        return NULL;
    }

    update_height(node);

    int leftHeight = node_height(node->left);
    int rightHeight = node_height(node->right);
    int balance = leftHeight - rightHeight;

    // left left / left right
    if (balance > 1)
    {
        int leftBalance = node_height(node->left->left)
                        - node_height(node->left->right);

        if (leftBalance >= 0) {
            return rotate_right(node);
        } else {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
    }
    // right right / right left
    else if (balance < -1)
    {
        int rightBalance = node_height(node->right->left)
                         - node_height(node->right->right);

        if (rightBalance <= 0) {
            return rotate_left(node);
        } else {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
    }

   return node;
}


Row* insert_balanced(Row* node, int id, const char* value) {
    if (node == NULL) {
        Row* newNode = create_row(id, value);
        return newNode;
    }

    if (id < node->id) {
       node->left = insert_balanced(node->left, id, value);
    } else if (id > node->id) {
        node->right = insert_balanced(node->right, id, value);
    } else if(id == node->id) {
        return node;
    }

    return rebalance(node);
    
}