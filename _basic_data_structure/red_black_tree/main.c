#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

void rotate(struct rb_tree *tree, struct rb_node *root, int side)
{
    struct rb_node *new_root;
    new_root = root->child[side ^ 1];
    assert(new_root != NULL);
    if (root->parent == NULL)
        tree->root = new_root;
    else {
        if (root == root->parent->child[0])
            root->parent->child[0] = new_root;
        else
            root->parent->child[1] = new_root;
    }
    new_root->parent = root->parent;
    root->child[side ^ 1] = new_root->child[side];
    if (new_root->child[side] != NULL)
        new_root->child[side]->parent = root;
    new_root->child[side] = root;
    root->parent = new_root;
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
            rotate(tree, parent, side);
            node = parent;
            parent = node->parent;
        }
        /* Case 5: Rotate parent to grand parent and re-paint */
        /* Side ^ 1 rotation */
        rotate(tree, g_parent, side ^ 1);
        g_parent->color = RED;
        parent->color = BLACK;
        return;
    } while (node->parent != NULL);
    /* Case 2: make sure root is black */
    node->color = BLACK;
}

struct rb_node * find(struct rb_tree *tree, int key)
{
    struct rb_node *node;
    node = tree->root;
    while (node != NULL) {
        if (node->key == key)
            return node;
        if (key < node->key)
            node = node->child[0];
        else
            node = node->child[1];
    }
    return NULL;
}

void node_swap(struct rb_tree *tree, struct rb_node *node1, struct rb_node *node2)
{
    struct rb_node *temp;
    int side;
    int color_temp;
    if (node1 == node2)
        return;
    if (node1 == node2->parent) {
        temp = node1;
        node1 = node2;
        node2 = temp;
    }
    if (node1->parent == node2) {
        if (node1->child[0] != NULL)
            node1->child[0]->parent = node2;
        if (node1->child[1] != NULL)
            node1->child[1]->parent = node2;
        if (node1 == node2->child[0])
            side = 0;
        else
            side = 1;
        if (node2->child[side ^ 1] != NULL)
            node2->child[side ^ 1]->parent = node1;
        temp = node1->child[side ^ 1];
        node1->child[side ^ 1] = node2->child[side ^ 1];
        node2->child[side ^ 1] = temp;
        node2->child[side] = node1->child[side];
        node1->child[side] = node2;
        temp = node2->parent;
        if (temp != NULL) {
            if (node2 == temp->child[0])
                temp->child[0] = node1;
            else
                temp->child[1] = node1;
        }
        else
            tree->root = node1;
        node1->parent = temp;
        node2->parent = node1;
    }
    else {
        if (node1->child[0] != NULL)
            node1->child[0]->parent = node2;
        if (node2->child[0] != NULL)
            node2->child[0]->parent = node1;
        if (node1->child[1] != NULL)
            node1->child[1]->parent = node2;
        if (node2->child[1] != NULL)
            node2->child[1]->parent = node1;
        temp = node1->child[0];
        node1->child[0] = node2->child[0];
        node2->child[0] = temp;
        temp = node1->child[1];
        node1->child[1] = node2->child[1];
        node2->child[1] = temp;
        temp = node1->parent;
        if (temp != NULL) {
            if (node1 == temp->child[0])
                temp->child[0] = node2;
            else
                temp->child[1] = node2;
        }
        else
            tree->root = node2;
        temp = node2->parent;
        if (temp != NULL) {
            if (node2 == temp->child[0])
                temp->child[0] = node1;
            else
                temp->child[1] = node1;
        }
        else
            tree->root = node1;
        node2->parent = node1->parent;
        node1->parent = temp;
    }
    color_temp = node1->color;
    node1->color = node2->color;
    node2->color = color_temp;
}

void delete_black_leaf_node(struct rb_tree *tree, struct rb_node *node)
{
    int side;
    struct rb_node *parent;
    struct rb_node *sibling;
    struct rb_node *c_nephew; /* close nephew */
    struct rb_node *d_nephew; /* distant nephew */
    parent = node->parent;
    assert(parent != NULL);
    do {
        if (node == parent->child[0])
            side = 0;
        else
            side = 1;
        sibling = parent->child[side ^ 1];
        c_nephew = sibling->child[side];
        assert(sibling != NULL);
        if (sibling->color == RED) { /* case 3: sibling is red */
            rotate(tree, parent, side);
            sibling = c_nephew;
            parent->color = RED;
            parent->parent->color = BLACK;
            /* Fall through to case 4 */
        }
        else {
            d_nephew = sibling->child[side ^ 1];
            /* case 5: distant nephew is black, close nephew is red */
            if ((d_nephew== NULL || d_nephew->color == BLACK) && (c_nephew != NULL && c_nephew->color == RED)) {
                rotate(tree, sibling, side ^ 1);
                d_nephew = sibling;
                sibling = c_nephew;
                /*c_nephew = sibling->child[side];*/
                d_nephew->color = RED;
                sibling->color = BLACK;
                /* Fall through to case 6 */
            }
            /* case 6: distant nephew is red */
            if (d_nephew!= NULL && d_nephew->color == RED) {
                rotate(tree, parent, side);
                d_nephew->color = BLACK;
                sibling->color = parent->color;
                parent->color = BLACK;
                return;
            }
        }
        /* case 4: parent is red */
        if (parent->color == RED) {
            parent->color = BLACK;
            sibling->color = RED;
            return;
        }
        /* case 1: parent / sibling / nephews are all black */
        sibling->color = RED;
        node = parent;
        parent = node->parent;
    } while (parent != NULL);
    /* case 2: sibling from every level is repainted red */
}

void delete(struct rb_tree *tree, int key)
{
    struct rb_node *node;
    struct rb_node *temp;
    node = find(tree, key);
    if (node == NULL)
        return;
    /* Simple cases */
    /* Root has no children */
    if (tree->root->child[0] == NULL && tree->root->child[1] == NULL) {
        release_node(tree->root);
        tree->root = NULL;
        return;
    }
    /* Node has 2 non-NULL children */
    if (node->child[0] != NULL && node->child[1] != NULL) {
        temp = node->child[0];
        while (temp->child[1] != NULL)
            temp = temp->child[1];
        node_swap(tree, node, temp);
    }
    /* Node has one red child */
    if (node->child[0] != NULL) {
        node_swap(tree, node, node->child[0]);
        assert(node->color == RED);
    }
    if (node->child[1] != NULL) {
        node_swap(tree, node, node->child[1]);
        assert(node->color == RED);
    }
    assert(node->child[0] == NULL && node->child[1] == NULL);
    /* Red leaf node is directly removed */
    if (node->color == RED) {
        if (node == node->parent->child[0])
            node->parent->child[0] = NULL;
        else
            node->parent->child[1] = NULL;
        release_node(node);
        return;
    }
    /* Black leaf node: complicated case */
    delete_black_leaf_node(tree, node);
    if (node == node->parent->child[0])
        node->parent->child[0] = NULL;
    else
        node->parent->child[1] = NULL;
    release_node(node);
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
    if (node->color == BLACK)
        printf("%2dB", node->key);
    else
        printf("\033[0;31m%2dR\033[0m", node->key);
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

    delete(&tree, 8);
    insert(&tree, 8);

    print_tree(&tree);

    return 0;
}
