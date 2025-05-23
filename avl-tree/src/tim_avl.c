#include "../include/tim_avl.h"

static u32 max_(u32 a, u32 b) { return (a < b) ? b : a; }

static void check_alloc_(void *p) {
  if (NULL == p) {
    fprintf(stderr, "%s\n", "Tree bad allocation. Abort.");
    abort();
  }
}

static void check_null_node_(const Node *node) {
  if (NULL == node) {
    fprintf(stderr, "%s\n", "Node is NULL. Abort.");
    abort();
  }
}

static bool check_number_(int num, const char *token) {
  if (num == 0 && token[0] != '0') {
    fprintf(stderr, "Error converting string to numeric array.\n");
    return false;
  }
  return true;
}

static bool check_size_arr(u32 size) {
  if (size == 0) {
    fprintf(stderr, "Empty string. Can't convert to numeric array.\n");
    return false;
  }
  return true;
}

static void free_node_(Node *node) {
  if (NULL == node)
    return;
  free(node);
}

static bool cmp_avl_(Node *n1, Node *n2) {
  if (NULL == n1 && NULL == n2)
    return true;
  if (NULL == n1 || NULL == n2)
    return false;
  if (n1->key_ != n2->key_ || n1->num_key_ != n2->num_key_)
    return false;

  return cmp_avl_(n1->left_, n2->left_) && cmp_avl_(n1->right_, n2->right_);
}

static int get_balance_(const Node *node) {
  check_null_node_(node);
  return (get_height(node->left_) - get_height(node->right_));
}

static bool is_balanced_(Node *node) {
  int balance;

  if (NULL == node)
    return true;

  balance = get_balance_(node);
  if (balance < -1 || 1 < balance)
    return false;

  return is_balanced_(node->left_) && is_balanced_(node->right_);
}

/* traversing mechanism, should be used from wrappers */
static void traverse_inorder_(Node *node, predmodule *predmod) {
  if (NULL == node)
    return;

  traverse_inorder_(node->left_, predmod);
  switch (predmod->state) {
  case SIMPLE:
    (*(predfunc_simple)predmod->pred)(node);
    break;
  default:
    (*(predfunc)predmod->pred)(node, predmod);
  }
  traverse_inorder_(node->right_, predmod);
}

static void traverse_postorder_(Node *node, void (*predicate)(Node *)) {
  if (NULL == node)
    return;
  traverse_postorder_(node->left_, predicate);
  traverse_postorder_(node->right_, predicate);
  (*predicate)(node);
}

/* accumulating predicate */
static void count_keys_in_node_(Node *node, predmodule *predmod) {
  if (NULL == node)
    return;
  *(u32 *)predmod->accumulator += node->num_key_;
}

/* storage predicate */
static void copy_to_array_(Node *node, predmodule *predmod) {
  int **iter;
  if (NULL == node)
    return;
  iter = (int **)&predmod->sd.storage_current;
  for (u32 i = 0; i < node->num_key_; ++i, ++*iter)
    **iter = node->key_;
}

/* cmp predicate */
static void cmp_keys_(Node *node, predmodule *predmod) {
  int **iter, *end;
  u32 i;
  if (!predmod->cd.equals)
    return;
  iter = (int **)&predmod->sd.storage_current;
  end = (int *)predmod->sd.storage_end;
  for (i = 0; i < node->num_key_; ++i, ++*iter) {
    if (*iter == end || **iter != node->key_) {
      predmod->cd.equals = false;
      return;
    }
  }
}

static u32 get_recalc_height_(const Node *node) {
  check_null_node_(node);
#define THIS_NODE 1
  return THIS_NODE + max_(get_height(node->left_), get_height(node->right_));
}

/* turn x clockwise */
static Node *right_rotate_(Node *x) {
  Node *y, *z;

  /* check valid form */
  check_null_node_(x);
  if (NULL == x->left_)
    return x;

  y = x->left_;  /* save subtree */
  z = y->right_; /* save subtree */

  /* rotate */
  y->right_ = x;
  x->left_ = z;

  /* change parents */
  x->parent_ = y;
  y->parent_ = NULL; /* if y will become a root */
  if (NULL != z)
    z->parent_ = x;

  /* recalc height: x - first, y - second */
  x->height_ = get_recalc_height_(x);
  y->height_ = get_recalc_height_(y);

  return y;
}

/* turn x counter clockwise */
static Node *left_rotate_(Node *x) {
  Node *y, *z;

  /* check valid form */
  check_null_node_(x);
  if (NULL == x->right_)
    return x;

  y = x->right_; /* save subtree */
  z = y->left_;  /* save subtree */

  y->left_ = x;
  x->right_ = z;

  /* change parents */
  x->parent_ = y;
  y->parent_ = NULL; /* if y will become a root */
  if (NULL != z)
    z->parent_ = x;

  /* recalc height: x - first, y - second */
  x->height_ = get_recalc_height_(x);
  y->height_ = get_recalc_height_(y);

  return y;
}

static Node *create_node_(int key) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  check_alloc_(new_node);

  new_node->left_ = NULL;
  new_node->right_ = NULL;
  new_node->parent_ = NULL;
  new_node->key_ = key;
  new_node->num_key_ = 1;
  new_node->height_ = 1;

  return new_node;
}

static Node *process_insert_rotation_(Node *node, int node_balance, int key) {
#if AUTO_BALANCE_

#define MAX_BALANCE_TRESHOLD 1
#define MIN_BALANCE_TRESHOLD -1

  /* LL-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the left subtree
   * of the left child of our node.
   *
   */
  if (node_balance > MAX_BALANCE_TRESHOLD && node->left_ != NULL &&
      key < node->left_->key_)
    return right_rotate_(node); /* parent will be fixed after nearest return */

  /* RR-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the right subtree
   * of the right child of our node.
   *
   */
  if (node_balance < MIN_BALANCE_TRESHOLD && node->right_ != NULL &&
      key > node->right_->key_)
    return left_rotate_(node); /* parent will be fixed after nearest return */

  /* LR-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the right subtree
   * of the left child of our node.
   *
   */
  if (node_balance > MAX_BALANCE_TRESHOLD && node->left_ != NULL &&
      key > node->left_->key_) {
    node->left_ = left_rotate_(node->left_);
    node->left_->parent_ = node;
    return right_rotate_(node); /* after return parent will be fixed,
                                   or will be null if caller is root */
  }

  /* RL-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the left subtree
   * of the right child of our node.
   *
   */
  if (node_balance < MIN_BALANCE_TRESHOLD && node->right_ != NULL &&
      key < node->right_->key_) {
    node->right_ = right_rotate_(node->right_);
    node->right_->parent_ = node;
    return left_rotate_(node); /* after return parent will be fixed,
                                 or will be null if caller is root */
  }

#endif

  return node;
}

static Node *process_delete_rotation_(Node *node, int node_balance) {
#if AUTO_BALANCE_

#define MAX_BALANCE_TRESHOLD 1
#define MIN_BALANCE_TRESHOLD -1
  if (node_balance > MAX_BALANCE_TRESHOLD && node->left_ != NULL &&
      get_balance_(node->left_) >= 0)
    return right_rotate_(node);

  if (node_balance < MIN_BALANCE_TRESHOLD && node->right_ != NULL &&
      get_balance_(node->right_) <= 0)
    return left_rotate_(node);

  if (node_balance > MAX_BALANCE_TRESHOLD && node->left_ != NULL &&
      get_balance_(node->left_) < 0) {
    node->left_ = left_rotate_(node->left_);
    node->left_->parent_ = node;
    return right_rotate_(node);
  }

  if (node_balance < MIN_BALANCE_TRESHOLD && node->right_ != NULL &&
      get_balance_(node->right_) > 0) {
    node->right_ = right_rotate_(node->right_);
    node->right_->parent_ = node;
    return left_rotate_(node);
  }

#endif
  return node;
}

static Node *insert_key_(Node *node, int key, u32 *num_node) {
  int node_balance;

  /* 1. Going down.
   *
   * We will recursively go down the tree,
   * until we find a correct place for a new node.
   *
   */

  if (NULL == node) { /* found place for new node */
    ++*num_node;
    return create_node_(key);
  }

  /* if the same key was found in an existing node,
   * then the tree structure should remain the same
   */
  if (key == node->key_) {
    assert(node->num_key_ > 0);
    ++node->num_key_;
    return node;
  }

  if (key < node->key_) {
    /* Let's try to find a place for a new node in the left subtree */
    node->left_ = insert_key_(node->left_, key, num_node);

    /* Fix parent of returned node, perfectly works with balance */
    node->left_->parent_ = node;

  } else if (key > node->key_) {
    /* Let's try to find a place for a new node in the right subtree */
    node->right_ = insert_key_(node->right_, key, num_node);

    /* Fix parent of returned node, perfectly works with balance */
    node->right_->parent_ = node;
  }

  /* 2. Going up.
   *
   * From this moment we have found a place for the new node,
   * and now we begin to climb up the recursion and gradually
   * correct the balance in the nodes until we reach the root.
   *
   */

  /* Recalculate new height of given node */
  node->height_ = get_recalc_height_(node);

  /* Update the balance variable of current node */
  node_balance = get_balance_(node);

  return process_insert_rotation_(node, node_balance, key);
}

static void transplant_(AVL *tree, Node *u, Node *v) {
  if (NULL == u->parent_)
    tree->root_ = v;
  else if (u == u->parent_->left_)
    u->parent_->left_ = v;
  else
    u->parent_->right_ = v;
  if (NULL != v)
    v->parent_ = u->parent_;
}

static Node *delete_node_(AVL *tree, Node *del_node) {
  Node *unbalanced_node = NULL;

  --tree->num_node_;

  if (NULL == del_node->left_) {
    unbalanced_node = del_node->parent_;
    transplant_(tree, del_node, del_node->right_);
    free(del_node);
    return unbalanced_node;
  }

  if (NULL == del_node->right_) {
    unbalanced_node = del_node->parent_;
    transplant_(tree, del_node, del_node->left_);
    free(del_node);
    return unbalanced_node;
  }

  Node *rotate_node = get_min(del_node->right_);
  unbalanced_node = rotate_node;

  if (rotate_node->parent_ != del_node) {
    unbalanced_node = rotate_node->parent_;
    transplant_(tree, rotate_node, rotate_node->right_);
    rotate_node->right_ = del_node->right_;
    rotate_node->right_->parent_ = rotate_node;
  }

  transplant_(tree, del_node, rotate_node);
  rotate_node->left_ = del_node->left_;
  rotate_node->left_->parent_ = rotate_node;
  free(del_node);

  return unbalanced_node;
}

static Node *rebalance_up_(Node *unbalanced_node) {
  Node *prev_node = unbalanced_node;
  bool left_child = false;
  int node_balance;

  for (;;) {
    prev_node = unbalanced_node->parent_;
    if (prev_node)
      left_child = (prev_node->left_ == unbalanced_node);

    unbalanced_node->height_ = get_recalc_height_(unbalanced_node);
    node_balance = get_balance_(unbalanced_node);

    unbalanced_node = process_delete_rotation_(unbalanced_node, node_balance);
    unbalanced_node->parent_ = prev_node;

    if (!prev_node)
      return unbalanced_node;

    if (left_child)
      prev_node->left_ = unbalanced_node;
    else
      prev_node->right_ = unbalanced_node;

    unbalanced_node = prev_node;
  }
}

static Node *delete_key_(AVL *tree, Node *del_node) {
  Node *unbalanced_node;

  if (NULL == del_node)
    return NULL;

  unbalanced_node = delete_node_(tree, del_node);

  if (NULL == unbalanced_node)
    return tree->root_;

  return (tree->root_ = rebalance_up_(unbalanced_node));
}

/* USER METHODS ========================================================== */

void init_avl(AVL *tree) {
  tree->root_ = NULL;
  tree->num_node_ = 0;
}

Node *insert_key(AVL *tree, int key) {
  if (NULL == tree)
    return NULL;
  return (tree->root_ = insert_key_(tree->root_, key, &tree->num_node_));
}

Node *find_key(AVL *tree, int key) {
  if (NULL == tree)
    return NULL;
  Node *walk_node = tree->root_;
  while (NULL != walk_node && key != walk_node->key_) {
    walk_node = (key < walk_node->key_) ? walk_node->left_ : walk_node->right_;
  }
  return walk_node;
}

Node *delete_key(AVL *tree, int key) {
  if (NULL == tree)
    return NULL;

  Node *found_node = find_key(tree, key);
  if (NULL == found_node)
    return tree->root_;

  assert(found_node->num_key_ >= 1);
  if (found_node->num_key_ > 1) {
    --found_node->num_key_;
    return tree->root_;
  }

  return (tree->root_ = delete_key_(tree, found_node));
}

Node *create_avl_from_array(AVL *tree, int arr[], u32 size) {
  if (size < 1)
    return tree->root_;
  for (u32 i = 0; i < size; ++i)
    insert_key(tree, arr[i]);
  return tree->root_;
}

/* slow */
int *create_arr_from_avl(AVL *tree) {
  predmodule predmod;
  int *arr;
  u32 size;

  if (is_avl_empty(tree)) {
    puts("Warning: attempt to create an array from a null tree.");
    puts("returned NULL");
    return NULL;
  }

  size = get_avl_num_elems(tree); /* O(n) */
  arr = (int *)malloc(sizeof(int) * size);
  check_alloc_(arr);

  init_predmod(&predmod, STORE);
  set_predicate(&predmod, copy_to_array_);
  set_storage(&predmod, arr, arr + size);

  traverse_inorder_(tree->root_, &predmod);

  return arr; /* should be deallocated */
}

bool cmp_avl(AVL *t1, AVL *t2) {
  if (NULL == t1 && NULL == t2)
    return true;
  if (NULL == t1 || NULL == t2)
    return false;

  return cmp_avl_(t1->root_, t2->root_);
}

bool cmp_avl_with_arr(AVL *tree, int *arr, u32 size) {
  predmodule predmod;

  if (NULL == tree || size == 0)
    return false;

  init_predmod(&predmod, COMPARE);
  set_predicate(&predmod, cmp_keys_);
  set_storage(&predmod, arr, arr + size);

  traverse_inorder_(tree->root_, &predmod);

  return predmod.cd.equals;
}

bool cmp_avl_with_string(AVL *tree, const char *source) {
  char *token;
  int *arr = NULL;
  u32 size = 0;
  int num = 0;
  bool res;
  char *str;

  /* copy string */
  str = (char *)malloc(sizeof(char) * (strlen(source) + 1));
  memcpy(str, source, strlen(source) + 1);
  str[strlen(source)] = '\0';

  /* count elements in string and check correctness */
  token = strtok(str, " ,");
  while (NULL != token) {
    num = atoi(token);
    if (!check_number_(num, token))
      return false;
    token = strtok(NULL, " ,");
    ++size;
  }

  if (!check_size_arr(size))
    return false;

  arr = (int *)malloc(sizeof(int) * size);
  memcpy(str, source, strlen(source) + 1);
  str[strlen(source)] = '\0';

  /* fill array */
  token = strtok(str, " ,");
  for (u32 i = 0; i < size; ++i, token = strtok(NULL, " ,"))
    arr[i] = atoi(token);

  /* compare array with tree */
  res = cmp_avl_with_arr(tree, arr, size);

  free(arr);
  free(str);

  return res;
}

bool is_balanced(AVL *tree) {
  if (tree == NULL)
    return true;
  return is_balanced_(tree->root_);
}

u32 get_avl_num_elems(AVL *tree) {
  predmodule predmod;
  u32 sum = 0;

  if (NULL == tree)
    return sum;

  init_predmod(&predmod, ACCUMULATE);
  set_predicate(&predmod, count_keys_in_node_);
  set_accumulator(&predmod, &sum);

  traverse_inorder_(tree->root_, &predmod);

  return sum;
}

void delete_avl(AVL *tree) {
  traverse_postorder_(tree->root_, free_node_);
  tree->root_ = NULL;
  tree->num_node_ = 0;
}

Node *get_min(Node *node) {
  if (node == NULL)
    return NULL;
  while (node->left_ != NULL)
    node = node->left_;
  return node;
}

Node *get_max(Node *node) {
  if (node == NULL)
    return NULL;
  while (node->right_ != NULL)
    node = node->right_;
  return node;
}

Node *lower_bound(Node *node) {
  if (NULL == node)
    return NULL;
  if (NULL != node->left_)
    return get_max(node->left_);
  Node *prev_node = node->parent_;
  while (prev_node != NULL && node == prev_node->left_) {
    node = prev_node;
    prev_node = prev_node->parent_;
  }
  return prev_node;
}

Node *upper_bound(Node *node) {
  if (NULL == node)
    return NULL;
  if (NULL != node->right_)
    return get_min(node->right_);
  Node *prev_node = node->parent_;
  while (prev_node != NULL && node == prev_node->right_) {
    node = prev_node;
    prev_node = prev_node->parent_;
  }
  return prev_node;
}

void avl_sort(int arr[], u32 size) {
  AVL tree;
  predmodule predmod;

  init_avl(&tree);
  create_avl_from_array(&tree, arr, size);

  init_predmod(&predmod, STORE);
  set_predicate(&predmod, copy_to_array_);
  set_storage(&predmod, arr, arr + size);

  traverse_inorder_(tree.root_, &predmod); /* will sort array */

  delete_avl(&tree);
}

u32 get_avl_size(AVL *tree) {
  if (NULL == tree)
    return 0;
  return tree->num_node_;
}

u32 get_height(const Node *node) { return (NULL != node) ? node->height_ : 0; }

bool is_avl_empty(AVL *tree) { return (tree->num_node_ == 0); }

void print_avl_nodes(AVL *tree) {
  predmodule predmod;
  if (NULL == tree)
    return;

  init_predmod(&predmod, SIMPLE);
  set_predicate(&predmod, print_node);

  print_root(tree);
  traverse_inorder_(tree->root_, &predmod);
}

void print_avl(AVL *tree) {
  predmodule predmod;

  if (NULL == tree)
    return;

  init_predmod(&predmod, SIMPLE);
  set_predicate(&predmod, print_key);

  traverse_inorder_(tree->root_, &predmod);

  putchar('\n');
}

void print_root(AVL *tree) {
  if (NULL == tree)
    return;
  printf("root      : %p \n", tree->root_);
  printf("num nodes : %u \n", tree->num_node_);
  putchar('\n');
}

void print_node(Node *node) {
  if (NULL == node)
    return;
  printf("=============================\n");
  printf("|Node      : %-14p |\n", (void *)node);
  printf("|---------------------------|\n");
  printf("|--left    : %-14p |\n", (void *)node->left_);
  printf("|--right   : %-14p |\n", (void *)node->right_);
  printf("|--parent  : %-14p |\n", (void *)node->parent_);
  printf("|---------------------------|\n");
  printf("|--key     : %-14d |\n", node->key_);
  printf("|--num_key : %-14u |\n", node->num_key_);
  printf("|--height  : %-14u |\n", node->height_);
  printf("=============================\n");
  putchar('\n');
}

void print_key(Node *node) {
  if (node == NULL)
    return;
  printf("%d ", node->key_);
}
