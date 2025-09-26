#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
void registrarUsuario()
{
    FILE *usuarios = fopen("Usuarios.txt", "a");
    bool usuarioValido = true;
    usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
    if (nuevoUsuario == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }

    printf("Ingrese el nombre: ");
    scanf("%s", nuevoUsuario->nombre);

    printf("Ingrese el apellido: ");
    scanf("%s", nuevoUsuario->apellido);
    
    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    int i = 0;
    while (nuevoUsuario->nombre[i] != '\0') {
        if (!isalpha(nuevoUsuario->nombre[i])) {
            usuarioValido = false;
            break; 
        }
        i++;
    }

    if (usuarioValido) {
        i = 0; 
        while (nuevoUsuario->apellido[i] != '\0') {
            if (!isalpha(nuevoUsuario->apellido[i])) {
                usuarioValido = false;
                break;
            }
            i++;
        }
    }

    if (usuarioValido) {
        fprintf(usuarios,"%ld %s %s", nuevoUsuario->cedula, nuevoUsuario->nombre, nuevoUsuario->apellido);
    } else {
        printf("Error: El nombre o apellido contienen caracteres no válidos.\n");
    }
    
    free(nuevoUsuario); 
}
