#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX 5
#define MIN 2

struct Node
{
  int values[MAX + 1];
  int count;
  struct Node *branch[MAX + 1];
};

struct Node *root;

struct Node *createNode(struct Node *child, int key)
{
  struct Node *newNode;
  newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->values[1] = key;
  newNode->count = 1;
  newNode->branch[0] = root;
  newNode->branch[1] = child;
  return newNode;
}

void insertNode(struct Node *node, struct Node *child, int key, int pos)
{
  int n = node->count;
  while(n > pos)
  {
    node->values[n + 1] = node->values[n];
    node->branch[n + 1] = node->branch[n];
    n--;
  }
  node->values[n + 1] = key;
  node->branch[n + 1] = child;
  node->count++;
}

void splitNode(struct Node *node, struct Node *child, struct Node **newNode, int key, int *pval, int pos)
{
  int median;
  int n;

  if(pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct Node *)malloc(sizeof(struct Node));
  n = median + 1;

  while(n <= MAX)
  {
    (*newNode)->values[n - median] = node->values[n];
    (*newNode)->branch[n - median] = node->branch[n];
    n++;
  }

  node->count = median;
  (*newNode)->count = MAX - median;

  if(pos <= MIN)
    insertNode(key, pos, node, child);
  else
    insertNode(key, pos - median, *newNode, child);

  *pval = node->values[node->count];
  (*newNode)->branch[0] = node->branch[node->count];
  node->count--;
}

int setValue(struct Node *node, struct Node **child, int key, int *pval)
{
  int pos;
  if(node == 0)
  {
    *pval = key;
    *child = NULL;
    return 1;
  }

  if(key < node->values[1])
  {
    pos = 0;
  }
  else
  {
    for(pos = node->count;
       (key < node->values[pos] && pos > 1); pos--);
    if(key == node->values[pos])
    {
      printf("Key already exists in tree\n");
      return 0;
    }
  }

  if(setValue(key, pval, node->branch[pos], child))
  {
    if(node->count < MAX)
    {
      insertNode(*pval, pos, node, *child);
    }
    else
    {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

void insert(int key)
{
  int flag;
  int i;
  struct Node *child;
  flag = setValue(key, &i, root, &child);
  if(flag)
    root = createNode(i, child);
}

void search(struct Node *myNode, int key, int *pos)
{
  if(myNode == 0)
    return;

  if(key < myNode->values[1])
    *pos = 0;
  else
  {
    for(*pos = myNode->count;
       (key < myNode->values[*pos] && *pos > 1); (*pos)--);
    if(key == myNode->values[*pos])
    {
      printf("%d found!\n", key);
      return;
    }
  }

  search(key, pos, myNode->branch[*pos]);
  return;
}

void traversal(struct Node *node)
{
  int i;
  if(node)
  {
    for(i = 0; i < node->count; i++)
    {
      traversal(node->branch[i]);
      printf("%d ", node->values[i + 1]);
    }

    traversal(node->branch[i]);
  }
}

int main()
{
	return 0;
}
