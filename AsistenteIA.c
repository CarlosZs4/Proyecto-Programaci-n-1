#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    
 //   fprintf(arch, "%d %s %s\n", usuario.cedula, usuario.nombre, usuario.apellido);
    printf("Usuario registrado exitosamente!\n");
    fclose(arch);
    
    return usuario;
}
void conversacion(AsistenteIA *usuario) {
    char temp_mensaje[1024];
    char linea[1024]; 
    char *respuesta_leida;
    char *pregunta_leida;
    int coincidencia=0;

    printf("Escribe tu mensaje: ");
    
    if (fgets(temp_mensaje, sizeof(temp_mensaje), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return;
    }
    temp_mensaje[strcspn(temp_mensaje, "\n")] = '\0';

    char *mensaje = temp_mensaje; 

    size_t len = strlen(temp_mensaje);
    if (len > 0 && temp_mensaje[len - 1] == '?') {
        temp_mensaje[len - 1] = '\0';
    }

    FILE *archivo = fopen("BaseConocimiento.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de la base de datos");
        return;
    }
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = 0;
    
        pregunta_leida = strtok(linea, "?");
        if (pregunta_leida == NULL) {
            continue; 
        }

        respuesta_leida = strtok(NULL, "");
        if (respuesta_leida == NULL) {
            continue; 
        }

        while (*respuesta_leida == ' ') {
            respuesta_leida++;
        }
        if (strcmp(temp_mensaje, pregunta_leida) == 0) {
            printf("Respuesta: %s",respuesta_leida);
            insertarP(usuario->mensaje, mensaje);
            insertarP(usuario->respuestaIA,respuesta_leida);
            coincidencia = 1; 
            break;             
        }
    }
    if (coincidencia == 0) {
        printf("Lo siento, no tengo una respuesta para esa pregunta.\n");
    }
     fclose(archivo);
}
int main(){
    AsistenteIA usuario;
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

    conversacion(&usuario);
    return 0;
}