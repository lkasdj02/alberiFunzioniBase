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
void print_simmetry(BTree *ptr);
void ordinsert_rec(BTree **ptrPtr, int val);
void delete_pos(BTree **ptrPtr, unsigned int pos);
BTree *ordinsert_rec_valore(BTree *ptr, int val);
unsigned int size(BTree *ptr); // trova quanti nodi ha l'albero.
int min(BTree *ptrPtr); // trova il valore minimo di tutto l'albero
 
// funzioni HELPER
int max(BTree *ptrPtr); // trova il valore minimo di tutto l'albero
BTree *adress_max(BTree *ptrPtr);

// opzioni globali.
char simmetrica[20]  = "simmetrica"; 
char pre_ordine[20]  = "pre_ordine"; // anche definita come anticipata.
char post_ordine[20] = "post_ordine"; // anche definita come posticipata.

int main() {

  BTree *albero;
  init(&albero);
  (isemtpy(albero)) ? printf("albero vuoto\n") : printf("albero NON vuoto\n");

  albero = ordinsert_rec_valore(albero, 4);
  (isemtpy(albero)) ? printf("albero vuoto\n") : printf("albero NON vuoto\n");

  // inserimento di un paio di nodi.

  albero = ordinsert_rec_valore(albero, 2);
  albero = ordinsert_rec_valore(albero, 1);
  albero = ordinsert_rec_valore(albero, 6);
  albero = ordinsert_rec_valore(albero, 3);

  // stampa ricorsiva dei nodi inseriti.
  print_simmetry(albero);
  printf("\n");

  int target = 7;
  printf("\nL'albero contiene %d? %d\n", target, search_rec(albero, target));
  printf("il numero di nodi che l'albero detiene: %d\n", size(albero));
  printf("il valore minimo che l'albero detiene: %d\n", min(albero));

  printf("il valore massimo che il sotto albero di sinistra detiene: %d. \n si trova all'indirizzo di heap: %p.\n", (adress_max(albero->leftPtr))->valore, adress_max(albero));

  // eliminazione di un nodo
  delete_pos(&albero, 3);
  print_simmetry(albero);
  printf("\n");

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

void print_simmetry(BTree *ptr) {
  if (ptr != NULL) {

    print_simmetry(ptr->leftPtr);
    printf("%d ", ptr->valore); // visita simmetrica
    print_simmetry(ptr->rightPtr);
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
    if (val <= ptr->valore)
      ptr->leftPtr  = ordinsert_rec_valore(ptr->leftPtr, val);
    else 
      ptr->rightPtr = ordinsert_rec_valore(ptr->rightPtr, val);
  }
  return ptr;
}

unsigned int size(BTree *ptr) {
  unsigned int number_of_nodes = 0; 
  if (ptr != NULL) { // potenzialmente caso base.
    number_of_nodes++; // la radice l'ho trovata.
    number_of_nodes += size(ptr->leftPtr);
    number_of_nodes += size(ptr->rightPtr);
  }
  return number_of_nodes;
}

int min(BTree *ptrPtr) {
  while(ptrPtr->leftPtr != NULL) {
    ptrPtr = ptrPtr->leftPtr; // questo vale per un'osservazione fatta.
  }
  return ptrPtr->valore;
}

int max(BTree *ptrPtr) {
  while(ptrPtr->rightPtr != NULL) {
    ptrPtr = ptrPtr->rightPtr; // questo vale per un'osservazione fatta.
  }
  return ptrPtr->valore;
}

BTree *adress_max(BTree *ptrPtr) {
  BTree *current = ptrPtr;
  while(current->rightPtr != NULL) {
    current = current->rightPtr; // questo vale per un'osservazione fatta.
  }
  return current;
}

/*
void delete_pos(BTree **ptrPtr, unsigned int pos) {
  if((*ptrPtr) == NULL) { // caso base... nodo non trovato
    return;
  } else {
    if (pos != (*ptrPtr)->valore) { // nodo non trovato momentaneamente.
      if (pos <= (*ptrPtr)->valore) {
        // andiamo a sinistra.
        delete_pos(&((*ptrPtr)->leftPtr), pos);
      } else {
        // andiamo a destra.
        delete_pos(&((*ptrPtr)->rightPtr), pos);
      }
    } else { // nodo trovato.
      // fare dal passo tre.
      // cercare tutti i nodi figli.
      int n_nodi_figli = size((*ptrPtr));
      printf("trovato il nodo da eliminare; questo ha %d nodi figli\n", n_nodi_figli - 1);
      int nodi_figli[n_nodi_figli];
      for (int i = 0; i < n_nodi_figli; i++) {
      }
    }
  }
}
*/

void delete_pos(BTree **ptrPtr, unsigned int pos) {
  if ((*ptrPtr) == NULL) { // caso in cui non abbia trovato il nodo desiderato.
    return; 
  } else if ((*ptrPtr)->valore == pos) { // caso base
    
    BTree *tmp_ntd = (*ptrPtr); // creazione nodo temporaneo.
    
    if ((*ptrPtr)->leftPtr != NULL && (*ptrPtr)->rightPtr != NULL) { // meccanismo massimo foglia.
      
      // meccanismo massimo -> foglia (basato su osservazioni sulla struttura dati).
      BTree *maxPtr = NULL;
      maxPtr = adress_max((*ptrPtr)->leftPtr); 
      maxPtr->rightPtr = tmp_ntd->rightPtr;
      printf("il nodo avente valore %d viene collegato al nodo avente valore %d.\n", maxPtr->valore, maxPtr->rightPtr->valore);

      // settare la nuova radice del sotto albero
      (*ptrPtr) = (*ptrPtr)->leftPtr;
      printf("nuova radice del sotto albero avente come radice il nodo da eliminare: %d\n", (*ptrPtr)->valore);
    } else {
      if ((*ptrPtr)->leftPtr != NULL)
        (*ptrPtr) = (*ptrPtr)->leftPtr;
      else
        (*ptrPtr) = (*ptrPtr)->rightPtr;
    }
    free(tmp_ntd);
    return; // ritorno al nodo precedente.
  } else { // visita in profondita del nodo desiderato
    if (pos <= (*ptrPtr)->valore) {
      // andiamo a sinistra.
      delete_pos(&((*ptrPtr)->leftPtr), pos);
    } else {
      // andiamo a destra.
      delete_pos(&((*ptrPtr)->rightPtr), pos);
    }
  }
}
