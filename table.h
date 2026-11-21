#ifndef TABLE_H 
#define TABLE_H 

typedef struct Row {
    int id;
    char* value;
    struct Row* left;
    struct Row* right;
    int height;
} Row;

Row* create_row(int id, const char* value);
void insert_row(Row* node, int id, const char* value);
int at(int day, int hour, int minute);
void print_time(int time);
Row* select_on_id(Row* node, int id);
void select_order_by(const Row* node);
Row* select_min(Row* node);
Row* select_max(Row* node);
Row* select_next(Row* node, int id);
Row* delete_row(Row* node, int id);
void drop_table(Row* node);
int node_height(const Row* node); // la hauteur stockée, ou 0 pour un arbre vide
void update_height(Row* node); // recalcule la hauteur à partir de celle des enfants
Row* rotate_left(Row* node);
Row* rotate_right(Row* node);
Row* rebalance(Row* node);
Row* insert_balanced(Row* node, int id, const char* value);


#endif