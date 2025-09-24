// nodo.h
#ifndef NODO_H
#define NODO_H

// Define la estructura Nodo compartida aquí solo una vez
typedef struct Nodo {
    void *info;
    struct Nodo *prox;
} Nodo;

#endif