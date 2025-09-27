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
typedef struct ConocimientoIA
{
    char *preguntas;
    char *respuesta;
}ConocimientoIA;

AsistenteIA registrarse();
int conversacion(AsistenteIA *usuario,Lista *baseDatos);
void cargarBaseConocimiento(Lista *baseDatos,const char *nombreArchivo);
AsistenteIA iniciarSesion();


#endif // ASISTENTEIA_H
