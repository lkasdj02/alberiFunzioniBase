#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct btree {
  int valore;
  struct btree *leftPtr;
  struct btree *rightPtr;
} BTree;


void init(BTree **ptrPtr); // funzione che sfrutta l'allocazione dinamica della memoria.
int isemtpy(BTree *ptr);
int search_rec(BTree *ptr, int val);
void print_rec(BTree *ptr, char *opt);
void ordinsert_rec(BTree **ptrPtr, int val);
BTree *ordinsert_rec_valore(BTree *ptr, int val);

// opzioni globali.
char simmetrica[20]  = "simmetrica"; 
char pre_ordine[20]  = "pre_ordine"; // anche definita come anticipata.
char post_ordine[20] = "post_ordine"; // anche definita come posticipata.

int main() {

  BTree *albero;
  init(&albero);
  (isemtpy(albero)) ? printf("albero vuoto\n") : printf("albero NON vuoto\n");

  albero = ordinsert_rec_valore(albero, 2);
  (isemtpy(albero)) ? printf("albero vuoto\n") : printf("albero NON vuoto\n");

  // inserimento di un paio di nodi.
  ordinsert_rec_valore(albero, 1);
  
  ordinsert_rec_valore(albero, 6);
  ordinsert_rec_valore(albero, 0);

  // stampa ricorsiva dei nodi inseriti.
  print_rec(albero, simmetrica);
  /*
  printf("indirizzo heap radice: %p.\n", albero);
  printf("indirizzo heap radice->left: %p.\n", albero->leftPtr);
  printf("indirizzo heap radice->right: %p.\n", albero->rightPtr);
  print_rec(albero, post_ordine);
  printf("\n");

  int target = 7;
  printf("\nL'albero contiene %d? %d\n", target, search_rec(albero, target));
    */
}

void init(BTree **ptrPtr) {
  *ptrPtr = NULL;
}

int isemtpy(BTree *ptr) {
  return (ptr == NULL);
}

int search_rec(BTree *ptr, int val) {
  if (isemtpy(ptr)) { // caso base: sotto albero vuoto = radice NULLA.
      return -1;
  } else {
    if (ptr->valore == val)
      return 1;
    else {     
      if (ptr->valore < val)
        return search_rec(ptr->rightPtr, val);
      if (ptr->valore > val)
        return search_rec(ptr->leftPtr, val);
    }
  } 
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

void print_rec(BTree *ptr, char *opt) {
  if (ptr != NULL) {
    if (strcmp("pre_ordine", opt) == 0)
      printf("valore: %d \t indirizzo di ptr: %p \t indirizzo contenuto in ptr: %p\n", ptr->valore, &ptr, ptr);

    print_rec(ptr->leftPtr, opt);

    if (strcmp("simmetrica", opt) == 0)
      printf("valore: %d \t indirizzo di ptr: %p \t indirizzo contenuto in ptr: %p\n", ptr->valore, &ptr, ptr);

    print_rec(ptr->rightPtr, opt);

    if (strcmp("post_ordine", opt) == 0)
      printf("valore: %d \t indirizzo di ptr: %p \t indirizzo contenuto in ptr: %p\n", ptr->valore, &ptr, ptr);
  }
}

BTree *ordinsert_rec_valore(BTree *ptr, int val) {
  if (ptr == NULL) {
    // allocare dinamicamente un nuovo puntatore.
    ptr = (BTree *)malloc(sizeof(BTree));
    ptr->valore   = val;
    ptr->leftPtr  = NULL;
    ptr->rightPtr = NULL;
  } else {
    if (val <= ptr->valore) {
      ptr->leftPtr  = ordinsert_rec_valore(ptr->leftPtr, val);
    } else {
      ptr->rightPtr = ordinsert_rec_valore(ptr->rightPtr, val);
    }
  }
  return ptr;
}
