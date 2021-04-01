#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT (1000)
#define NODE_POOL_SIZE (1000)
#define NODE_QUEUE_SIZE (NODE_POOL_SIZE + 1)

int input[MAX_INPUT];
int input_count;

enum color_enum {
    BLACK,
    RED
};

struct rb_node {
    struct rb_node *parent;
    struct rb_node *child[2];
    enum color_enum color;
    int key;
};

struct rb_tree {
    struct rb_node *root;
};

struct node_container {
    struct rb_node node;
    struct node_container *next;
};

struct node_queue {
    struct rb_node *q[NODE_QUEUE_SIZE];
    int head;
    int tail;
};

struct node_container node_pool[NODE_POOL_SIZE];
int next_node_pool_index = 0;
struct node_container *released_node_list = NULL;

struct node_queue node_q;

struct rb_node *allocate_node()
{
    struct rb_node *node;
    if (released_node_list != NULL) {
        node = &released_node_list->node;
        released_node_list = released_node_list->next;
    }
    else {
        if (next_node_pool_index >= NODE_POOL_SIZE)
            return NULL;
        node = &node_pool[next_node_pool_index].node;
        ++next_node_pool_index;
    }
    node->child[0] = node->child[1] = NULL;
    return node;
}

void release_node(struct rb_node *node)
{
    struct node_container *released_node;
    released_node = (struct node_container *)node;
    released_node->next = released_node_list;
    released_node_list = released_node;
}

void insert_from_node(struct rb_node *node, int key)
{
    int side;
    if (key < node->key)
        side = 0;
    else if (key == node->key)
        return;
    else
        side = 1;
    if (node->child[side] == NULL) {
        node->child[side] = allocate_node();
        node->child[side]->key = key;
        node->child[side]->parent = node;
    }
    else
        insert_from_node(node->child[side], key);
}

void insert(struct rb_tree *tree, int key)
{
    if (tree->root == NULL) {
        tree->root = allocate_node();
        tree->root->key = key;
        tree->root->parent = NULL;
        return;
    }
    insert_from_node(tree->root, key);
}

void print_tree_pre_order(struct rb_node *node)
{
    if (node == NULL)
        return;
    printf("%d\n", node->key);
    print_tree_pre_order(node->child[0]);
    print_tree_pre_order(node->child[1]);
}

void print_tree_in_order(struct rb_node *node)
{
    if (node == NULL)
        return;
    print_tree_in_order(node->child[0]);
    printf("%d\n", node->key);
    print_tree_in_order(node->child[1]);
}

void print_tree_post_order(struct rb_node *node)
{
    if (node == NULL)
        return;
    print_tree_post_order(node->child[0]);
    print_tree_post_order(node->child[1]);
    printf("%d\n", node->key);
}

void enqueue(struct node_queue *q, struct rb_node *node)
{
    int tail;
    tail = q->tail + 1;
    if (tail >= NODE_QUEUE_SIZE)
        tail = 0;
    if (tail == q->head) /* queue full */
        return;
    q->q[q->tail] = node;
    q->tail = tail;
}

struct rb_node *dequeue(struct node_queue *q)
{
    struct rb_node *node;
    if (q->head == q->tail) /* queue empty */
        return NULL;
    node = q->q[q->head];
    q->head = q->head + 1;
    if (q->head >= NODE_QUEUE_SIZE)
        q->head = 0;
    return node;
}

void print_tree_level_order(struct rb_node *node)
{
    struct rb_node *head_node;
    enqueue(&node_q, node);
    while ((head_node = dequeue(&node_q)) != NULL) {
        printf("%d\n", head_node->key);
        if (head_node->child[0] != NULL)
            enqueue(&node_q, head_node->child[0]);
        if (head_node->child[1] != NULL)
            enqueue(&node_q, head_node->child[1]);
    }
}

void print_tree_by_shape(struct rb_node *node)
{
}

void print_tree(struct rb_tree *tree)
{
    // print_tree_pre_order(tree->root);
    // print_tree_in_order(tree->root);
    // print_tree_post_order(tree->root);
    print_tree_level_order(tree->root);
}

int main(void)
{
    int i;
    struct rb_tree tree;

    input_count = 0;
    while (scanf("%d", &input[input_count]) == 1)
        ++input_count;

    tree.root = NULL;
    for (i = 0; i < input_count; ++i)
        insert(&tree, input[i]);

    print_tree(&tree);

    return 0;
}
