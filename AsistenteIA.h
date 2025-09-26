#ifndef ASISTENTEIA_H
#define ASISTENTEIA_H
#include "lista.h"
#include "pila.h"
#include <stdbool.h>

typedef struct AsistenteIA
{
    bool sesionActiva;
    Pila *mensaje;
    Pila *respuestaIA;
}AsistenteIA;

AsistenteIA registrarse();
AsistenteIA iniciarSesion();


#endif // ASISTENTEIA_H
