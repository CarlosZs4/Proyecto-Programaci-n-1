#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
void registrarUsuario()
{
    FILE *usuarios = fopen("Usuarios.txt", "a+");
    char *nombre = (char *)malloc(100 * sizeof(char)), *apellido = (char *)malloc(100 * sizeof(char));
    long int cedula;
    usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
    if (nuevoUsuario == NULL)
    {
        printf("Error: No se pudo asignar memoria.\n");
        free(nuevoUsuario);
        free(nombre);
        free(apellido);
        fclose(usuarios);
        return;
    }

    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);

    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);

    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;

    int i = 0;
    bool usuarioValido = true;
    while (nuevoUsuario->nombre[i] != '\0' && usuarioValido)
    {
        if (!isalpha(nuevoUsuario->nombre[i]))
        {
            usuarioValido = false;
        }
        i++;
    }

    if (usuarioValido)
    {
        i = 0;
        while (nuevoUsuario->apellido[i] != '\0' && usuarioValido)
        {
            if (!isalpha(nuevoUsuario->apellido[i]))
            {
                usuarioValido = false;
            }
            i++;
        }
    }
    bool existeUsuario = false;
    if (usuarioValido)
    {
        rewind(usuarios);
        while (fscanf(usuarios, "%ld %s %s", &cedula, nombre, apellido) == 3 && !existeUsuario)
        {
            if (cedula == nuevoUsuario->cedula && strcmp(nombre, nuevoUsuario->nombre) == 0 && strcmp(apellido, nuevoUsuario->apellido) == 0)
            {
                printf("El usuario ya está registrado.\n");
                existeUsuario = true;
            }
        }
    }

    if (usuarioValido && !existeUsuario)
    {
        fprintf(usuarios, "%ld %s %s\n", nuevoUsuario->cedula, nuevoUsuario->nombre, nuevoUsuario->apellido);
    }
    else
    {
        printf("Error: El nombre o apellido contienen caracteres no válidos.\n");
    }

    free(nuevoUsuario);
    free(nombre);
    free(apellido);
    fclose(usuarios);
}
bool iniciarSesion(usuario *usuario)
{
    FILE *listaUsuarios = fopen("Usuarios.txt", "r");
    long int cedula;
    char *nombre = (char *)malloc(100 * sizeof(char)), *apellido = (char *)malloc(100 * sizeof(char));
    bool nombreEncontrado = false, apellidoEncontrado = false, cedulaEncontrada = false, sesionValida = true;
    while (fscanf(listaUsuarios, "%ld %s %s", &cedula, nombre, apellido) == 3)
    {
        if (usuario->cedula == cedula)
        {
            cedulaEncontrada = true;
        }
        if (strcmp(nombre, usuario->nombre) == 0)
        {
            nombreEncontrado = true;
        }
        if (strcmp(apellido, usuario->apellido) == 0)
        {
            apellidoEncontrado = true;
        }
    }

    free(nombre);
    free(apellido);
    fclose(listaUsuarios);
    return sesionValida == cedulaEncontrada && nombreEncontrado && apellidoEncontrado;
}
