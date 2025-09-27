#ifndef USUARIOS_H
#define USUARIOS_H
#include <stdbool.h>
typedef struct usuario
{
     int cantidadConsultas;
     int cantidadConsultasSinRespuesta;
     long cedula;
     char nombre[100], apellido[100];
}usuario;

void registrarUsuario();
bool iniciarSesion(usuario* usuario);
#endif