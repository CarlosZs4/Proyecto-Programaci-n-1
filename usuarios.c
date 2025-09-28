#include "usuarios.h"
#include <unistd.h>
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
    system("clear");
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
                sleep(1);
                existeUsuario = true;
                return;
            }
        }
    }

    if (usuarioValido && !existeUsuario)
    {
        fprintf(usuarios, "\n%ld %s %s", nuevoUsuario->cedula, nuevoUsuario->nombre, nuevoUsuario->apellido);
        printf("Usuario registrado con éxito!.\n");
        sleep(1);
    }
    else
    {
        printf("Error: El nombre o apellido contienen caracteres no válidos.\n");
        sleep(1);
    }

    free(nuevoUsuario);
    free(nombre);
    free(apellido);
    fclose(usuarios);
}
usuario* iniciarSesion()
{
    FILE *listaUsuarios = fopen("Usuarios.txt", "r");
    long int cedula;
    char *nombre = (char *)malloc(100 * sizeof(char)), *apellido = (char *)malloc(100 * sizeof(char));
    bool nombreEncontrado = false, apellidoEncontrado = false, cedulaEncontrada = false;

    usuario *nuevoUsuario = (usuario*)malloc(sizeof(usuario));
    system("clear");
    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);

    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);

    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;
    

    while (fscanf(listaUsuarios, "%ld %s %s", &cedula, nombre, apellido) == 3)
    {
        if (nuevoUsuario->cedula == cedula)
        {
            cedulaEncontrada = true;
        }
        if (strcmp(nombre, nuevoUsuario->nombre) == 0)
        {
            nombreEncontrado = true;
        }
        if (strcmp(apellido, nuevoUsuario->apellido) == 0)
        {
            apellidoEncontrado = true;
        }
    }

    free(nombre);
    free(apellido);
    fclose(listaUsuarios);

    nuevoUsuario->sesionActiva = nombreEncontrado && apellidoEncontrado && cedulaEncontrada;
    if (nuevoUsuario->sesionActiva)
    {
        return nuevoUsuario;
    }
    return NULL;
}
