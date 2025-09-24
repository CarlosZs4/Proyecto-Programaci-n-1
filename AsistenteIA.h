#ifndef ASISNTENTEIA_H
#define ASISNTENTEIA_H
#include "lista.h"
#include "pila.h"

typedef struct AsistenteIA
{
    char nombre,apellido;
    int cedula;
    Pila *mensaje;
    Pila *respuestaIA;
}AsistenteIA;

AsistenteIA registrarse();


#endif // ASISNTENTEIA_H
