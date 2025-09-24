#ifndef COLA_H
#define COLA_H
#include "nodo.h"
#include <stdio.h> // Necessary for size_t

// Forward declaration of Nodo to avoid circular dependencies
typedef struct Cola{
    int longitud;
    Nodo *ultimo, *primero;
}Cola;

// Public function declarations
void crearC(Cola *cola);
void insertarC(Cola *cola, void* num);
void eliminarC(Cola *cola);
void* consultarC(Cola cola);
size_t longitudC(Cola* cola);
void liberarC(Cola* cola);

#endif