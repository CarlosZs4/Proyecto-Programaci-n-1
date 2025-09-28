#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

// Definición de las estructuras internas
/*typedef struct Nodo {   
    void *info;
    struct Nodo *prox;
} Nodo;
 
typedef struct Pila {
    int longitud;
    Nodo *apilar;
} Pila;*/

// Funciones para la gestión de nodos (uso interno, por eso 'static')
static Nodo* crear_nodo(void* dato) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.");
        exit(1);
    }
    nuevo_nodo->info = dato;
    nuevo_nodo->prox = NULL;
    return nuevo_nodo;
}

static void liberar_nodo(Nodo* nodo) {
    if (nodo != NULL) {
        free(nodo);
    }
}

// ----------------------------------------------------------------
// Funciones del TDA Pila
// ----------------------------------------------------------------

void crearP(Pila *p1) {
    p1->longitud = 0;
    p1->apilar = NULL;
}

void insertarP(Pila *p1, void* num) {
    Nodo *nuevo_nodo = crear_nodo(num);
    nuevo_nodo->prox = p1->apilar;
    p1->apilar = nuevo_nodo;
    p1->longitud++;
}

void eliminarP(Pila *p1) {
    if(p1->apilar != NULL) {
        Nodo *aux = p1->apilar;
        p1->apilar = aux->prox;
        liberar_nodo(aux); // Usamos la función de ayuda
        p1->longitud--;
    }
}

void* consultarP(Pila *p1) {
    if(p1->apilar != NULL) {
        return p1->apilar->info;
    }
    return NULL; // Devuelve NULL en lugar de -1000
}
size_t longitudP(Pila* pila) {
    if (pila == NULL) {
        return 0;
    }
    return pila->longitud;
}
void liberarP(Pila* pila) {
    if (pila == NULL) {
        return;
    }
    while (pila->apilar != NULL) {
        eliminarP(pila);
    }
    free(pila);
}