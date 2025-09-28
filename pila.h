#ifndef PILA_H
#define PILA_H
#include "nodo.h"
#include <stdio.h> // Necessary for size_t

// Forward declaration of the Nodo structure

// Declaration of the Pila structure
typedef struct Pila {
    int longitud;
    Nodo *apilar;
} Pila;

// Public function declarations
void crearP(Pila *p1);
void insertarP(Pila *p1, void* num);
void eliminarP(Pila *p1);
void* consultarP(Pila *p1);
size_t longitudP(Pila* pila);
void liberarP(Pila* pila);

#endif