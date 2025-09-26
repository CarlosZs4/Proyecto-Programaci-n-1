#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "pila.h"
#include "AsistenteIA.h"

AsistenteIA registrarse(){
    
    AsistenteIA usuario;
    FILE *arch;
    printf("\n---------------------------\n");
    printf("REGISTRO");
    printf("\n---------------------------\n");
    printf("*Ingrese su nombre:\n");
   // scanf("%s",usuario.nombre);
    printf("\n*Ingrese su apellido:\n");
   // scanf("%s",usuario.apellido);
    printf("\n*Ingrese su cedula:\n");
   // scanf("%d",&usuario.cedula);
    printf("\n------------------------------\n");
    arch = fopen("Usuarios.txt", "r");
    if (arch != NULL) {
        int cedulaLeida;
        // "%*s" le indica a fscanf que lea y descarte las cadenas (nombre y apellido)
        while (fscanf(arch, "%d %*s %*s\n", &cedulaLeida) != EOF) {
         /*   if (cedulaLeida == usuario.cedula) {
                printf("\nError: La cedula ya se encuentra registrada.\n");
                fclose(arch);
                // En una aplicación completa, podrías devolver un código de estado
                exit(1);
            }*/
        }
        fclose(arch);
    }
    arch = fopen("Usuarios.txt", "a");
    if(arch==NULL){
        perror("Error al abrir el archivo");
         exit(1);
    }
    
    usuario.mensaje = (Pila *)malloc(sizeof(Pila));
    usuario.respuestaIA = (Pila *)malloc(sizeof(Pila));

    if (usuario.mensaje == NULL || usuario.respuestaIA == NULL) {
        printf("Error: No se pudo asignar memoria para las pilas.\n");
        free(usuario.mensaje);
        free(usuario.respuestaIA);
        exit(1);
    }
    
    crearP(usuario.mensaje);
    crearP(usuario.respuestaIA);

 //   fprintf(arch, "%d %s %s\n", usuario.cedula, usuario.nombre, usuario.apellido);
    printf("Usuario registrado exitosamente!\n");
    fclose(arch);
    
    return usuario;
}
