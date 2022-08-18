#include <stdio.h>
#include <stdlib.h>

typedef struct btree {
  int valore;
  struct btree *leftPtr;
  struct btree *rightPtr;
} BTree;


void init(BTree **ptrPtr); // funzione che sfrutta l'allocazione dinamica della memoria.
int isemtpy(BTree *ptr);
int search_rec(BTree *ptr, int val);
int print_rec(BTree *ptr, char *opt);
void ordinsert_rec(BTree **ptrPtr, int val);

int main() {

  BTree *albero;
  init(&albero);
  (isemtpy(albero)) ? printf("albero vuoto\n") : printf("albero NON vuoto\n");

  ordinsert_rec(&albero, 3);
  (isemtpy(albero)) ? printf("albero vuoto\n") : printf("albero NON vuoto\n");
}

void init(BTree **ptrPtr) {
  *ptrPtr = NULL;
}

int isemtpy(BTree *ptr) {
  return (ptr == NULL);
}

void ordinsert_rec(BTree **ptrPtr, int val) {
  if (isemtpy(*ptrPtr)) { // in caso sia vuoto, il nodo da inserire = RADICE
    (*ptrPtr) = (BTree *)malloc(sizeof(BTree)); // allocare lo spazio nella heap per questo nodo.
    (*ptrPtr)->valore   = val;
    (*ptrPtr)->leftPtr  = NULL;
    (*ptrPtr)->rightPtr = NULL;
    return;
  } else {
    if (val <= (*ptrPtr)->valore) {
      ordinsert_rec(&((*ptrPtr)->leftPtr), val); // passiamo il riferimento al puntatore al nodo di sinistra.
    } else if (val > (*ptrPtr)->valore) {
      ordinsert_rec(&((*ptrPtr)->rightPtr), val); // idem per quello di destra.
    }
  }
}

