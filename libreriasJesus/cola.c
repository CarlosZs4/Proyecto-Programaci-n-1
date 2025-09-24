#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

/*typedef struct Nodo Nodo;
typedef struct Nodo
{
    void *info;
    Nodo *prox;
}Nodo;
typedef struct Cola{
    int longitud;
    Nodo *ultimo, *primero;
}Cola;*/
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

void crearC(Cola *cola){
    cola->longitud=0;
    cola->ultimo=NULL;
    cola->primero=NULL;
}
void insertarC(Cola *cola,void* num){
    Nodo *nuevo_nodo;
    nuevo_nodo = crear_nodo(num);
    nuevo_nodo->prox = NULL;
    if(cola->ultimo==NULL){
        cola->primero=nuevo_nodo;
        cola->ultimo=nuevo_nodo;
    }
    else{
        cola->ultimo->prox = nuevo_nodo;
        cola->ultimo = nuevo_nodo;
    }
    cola->longitud++;
}
void eliminarC(Cola *cola){
    Nodo *aux;
    if(cola->primero!=NULL){
        aux=cola->primero;
        cola->primero=aux->prox;
        liberar_nodo(aux);
        cola->longitud--;
        if (cola->primero == NULL) {
            cola->ultimo = NULL;
        }
    }
}
void* consultarC(Cola cola){
    if(cola.primero!=NULL){
        return cola.primero->info;
    }
    return NULL;;
}
size_t longitudC(Cola* cola) {
    if (cola == NULL) {
        return 0;
    }
    return cola->longitud;
}
void liberarC(Cola* cola) {
    if (cola == NULL) {
        return;
    }
    while (cola->primero != NULL) {
        eliminarC(cola);
    }
    free(cola);
}
