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

struct node_queue_item {
    struct rb_node *node;
    int level;
};

struct node_queue {
    struct node_queue_item q[NODE_QUEUE_SIZE];
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

struct rb_node * insert_from_node(struct rb_node *node, int key)
{
    int side;
    if (key < node->key)
        side = 0;
    else if (key == node->key)
        return NULL;
    else
        side = 1;
    if (node->child[side] == NULL) {
        node->child[side] = allocate_node();
        node->child[side]->key = key;
        node->child[side]->parent = node;
        return node->child[side];
    }
    else
        return insert_from_node(node->child[side], key);
}

void insert(struct rb_tree *tree, int key)
{
    struct rb_node *node;
    struct rb_node *parent;
    struct rb_node *g_parent;
    struct rb_node *uncle;
    struct rb_node *gg_parent;
    int side;

    /* Normal insertion */
    if (tree->root == NULL) {
        tree->root = allocate_node();
        tree->root->key = key;
        tree->root->parent = NULL;
        tree->root->color = BLACK;
        return;
    }
    node = insert_from_node(tree->root, key);
    if (node == NULL)
        return;

    /* re-paint the tree */
    node->color = RED;
    do {
        parent = node->parent;
        /* Case 3: parent black */
        if (parent->color == BLACK)
            return;
        g_parent = parent->parent;
        /* Case 6: make sure root is black */
        if (g_parent == NULL) {
            parent->color = BLACK;
            return;
        }
        side = (parent == g_parent->child[0]) ? 0 : 1;
        uncle = g_parent->child[side ^ 1];
        /* Case 1: Recursion from grand parent */
        if (uncle != NULL && uncle->color == RED) {
            parent->color = BLACK;
            uncle->color = BLACK;
            g_parent->color = RED;
            node = g_parent;
            continue;
        }
        /* Case 4: Current node and parent at different side */
        if (node == parent->child[side ^ 1]) {
            /* Side rotation */
            g_parent->child[side] = node;
            node->parent = g_parent;
            parent->child[side ^ 1] = node->child[side];
            if (node->child[side] != NULL)
                node->child[side]->parent = parent;
            node->child[side] = parent;
            parent->parent = node;
            node = parent;
            parent = node->parent;
        }
        /* Case 5: Rotate parent to grand parent and re-paint */
        /* Side ^ 1 rotation */
        gg_parent = g_parent->parent;
        if (gg_parent == NULL)
            tree->root = parent;
        else {
            if (g_parent == gg_parent->child[0])
                gg_parent->child[0] = parent;
            else
                gg_parent->child[1] = parent;
        }
        parent->parent = gg_parent;
        g_parent->child[side] = parent->child[side ^ 1];
        if (parent->child[side ^ 1] != NULL)
            parent->child[side ^ 1]->parent = g_parent;
        parent->child[side ^ 1] = g_parent;
        g_parent->parent = parent;
        g_parent->color = RED;
        parent->color = BLACK;
        return;
    } while (node->parent != NULL);
    /* Case 2: make sure root is black */
    node->color = BLACK;
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

void enqueue(struct node_queue *q, struct rb_node *node, int level)
{
    int tail;
    tail = q->tail + 1;
    if (tail >= NODE_QUEUE_SIZE)
        tail = 0;
    if (tail == q->head) /* queue full */
        return;
    q->q[q->tail].node = node;
    q->q[q->tail].level = level;
    q->tail = tail;
}

struct node_queue_item *dequeue(struct node_queue *q)
{
    struct node_queue_item *item;
    if (q->head == q->tail) /* queue empty */
        return NULL;
    item = &q->q[q->head];
    q->head = q->head + 1;
    if (q->head >= NODE_QUEUE_SIZE)
        q->head = 0;
    return item;
}

void print_tree_level_order(struct rb_node *node)
{
    struct node_queue_item *head_item;
    int level;
    enqueue(&node_q, node, 0);
    level = 0;
    while ((head_item = dequeue(&node_q)) != NULL) {
        if (level != head_item->level) {
            level = head_item->level;
            printf("\n");
        }
        printf("%d ", head_item->node->key);
        if (head_item->node->child[0] != NULL)
            enqueue(&node_q, head_item->node->child[0], head_item->level + 1);
        if (head_item->node->child[1] != NULL)
            enqueue(&node_q, head_item->node->child[1], head_item->level + 1);
    }
}

/*
*     2
*     ├── 1
*     └── 14
*         ├── 8
*         │   ├── 6
*         │   │   ├── 3
*         │   │   │   └── 4
*         │   │   │       └── 5
*         │   │   └── 7
*         │   └── 11
*         │       ├── 9
*         │       │   └── 10
*         │       └── 12
*         │           └── 13
*         └── 16
*             ├── 15
*             └── 20
*                 └── 19
*                     └── 17
*                         └── 18
**/

void print_parent_connector_pre_order(struct rb_node *node, int last_level)
{
    if (node->parent == NULL)
        return;
    print_parent_connector_pre_order(node->parent, 0);
    if (node == node->parent->child[0] && node->parent->child[1] != NULL) {
        if (last_level)
            printf("├── ");
        else
            printf("│   ");
    }
    else {
        if (last_level)
            printf("└── ");
        else
            printf("    ");
    }
}

void print_tree_by_shape_fallen_pre_order(struct rb_node *node)
{
    if (node == NULL)
        return;
    print_parent_connector_pre_order(node, 1);
    printf("%d\n", node->key);
    print_tree_by_shape_fallen_pre_order(node->child[0]);
    print_tree_by_shape_fallen_pre_order(node->child[1]);
}

/*
 *      ┌─ 1
 *    2─┤
 *      │              ┌─ 3─┐
 *      │              │    └─ 4─┐
 *      │              │         └─ 5
 *      │         ┌─ 6─┤
 *      │         │    └─ 7
 *      │    ┌─ 8─┤
 *      │    │    │         ┌─10
 *      │    │    │    ┌─ 9─┘
 *      │    │    └─11─┤
 *      │    │         └─12─┐
 *      │    │              └─13
 *      └─14─┤
 *           │    ┌─15
 *           └─16─┤
 *                │         ┌─17─┐
 *                │         │    └─18
 *                │    ┌─19─┘
 *                └─20─┘
**/

void print_parent_connector_in_order(struct rb_node *node, struct rb_node *child)
{
    if (node->parent == NULL)
        return;
    print_parent_connector_in_order(node->parent, node);
    if (node == node->parent->child[0]) {
        if (child == NULL)
            printf("    ┌─");
        else {
            if (child == node->child[1])
                printf("    │ ");
            else
                printf("      ");
        }
    }
    else {
        if (child == NULL)
            printf("    └─");
        else {
            if (child == node->child[0])
                printf("    │ ");
            else
                printf("      ");
        }
    }
}

void print_tree_by_shape_fallen_in_order(struct rb_node *node)
{
    if (node == NULL)
        return;
    print_tree_by_shape_fallen_in_order(node->child[0]);
    print_parent_connector_in_order(node, NULL);
    printf("%2d%c", node->key, node->color == BLACK ? 'B' : 'R');
    if (node->child[0] != NULL) {
        if (node->child[1] != NULL)
            printf("─┤");
        else
            printf("─┘");
    }
    else {
        if (node->child[1] != NULL)
            printf("─┐");
    }
    printf("\n");
    print_tree_by_shape_fallen_in_order(node->child[1]);
}

void print_tree(struct rb_tree *tree)
{
    // print_tree_pre_order(tree->root);
    // print_tree_in_order(tree->root);
    // print_tree_post_order(tree->root);
    // print_tree_level_order(tree->root);
    // print_tree_by_shape_fallen_pre_order(tree->root);
    print_tree_by_shape_fallen_in_order(tree->root);
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
