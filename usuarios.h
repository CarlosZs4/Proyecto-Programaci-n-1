#ifndef USUARIOS_H
#define USUARIOS_H
typedef struct usuario
{
     long cedula;
     char* nombre, *apellido;
}usuario;

void registrarUsuario();
#endif