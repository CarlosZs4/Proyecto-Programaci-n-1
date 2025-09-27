#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "pila.h"
#include "AsistenteIA.h"

/*AsistenteIA registrarse(){
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
            if (cedulaLeida == usuario.cedula) {
                printf("\nError: La cedula ya se encuentra registrada.\n");
                fclose(arch);
                // En una aplicación completa, podrías devolver un código de estado
                exit(1);
            }
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
    
    return usuario */
int son_iguales_string(void *a,void *b){
    char* str1 = (char*)a;
    char* str2 = (char*)b;
    return(strcmp(str1, str2));
}
int son_iguales_preguntas(void *a,void *b){
    ConocimientoIA* str1 = (ConocimientoIA*)a;
    char* str2 = (char*)b;
    return(son_iguales_string(str1->preguntas, str2));
}
void imprimir_baseDatos(void *a){
    ConocimientoIA *Pardatos=(ConocimientoIA*)a;
    printf("%s  .",Pardatos->preguntas);
    printf("%s  .",Pardatos->respuesta);
}
void cargarBaseConocimiento(Lista *baseDatos,const char *nombreArchivo){
    char linea[1024]; 
    char *respuesta_leida;
    char *pregunta_leida;
    
    FILE *arch=fopen(nombreArchivo,"r");
    if (arch == NULL) {
        perror("Error al abrir el archivo de la base de datos");
        return;
    }
    while (fgets(linea, sizeof(linea), arch) != NULL) {
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
        ConocimientoIA *parDatos=(ConocimientoIA *)malloc(sizeof(ConocimientoIA));
        if(parDatos==NULL){
            printf("Error: No se pudo asignar memoria a la base de datos.\n");
            exit(1);
        }
        parDatos->preguntas=strdup(pregunta_leida);
        if (parDatos->preguntas == NULL) {
            fprintf(stderr, "Error: Falló strdup para la pregunta.\n");
            free(parDatos);
            fclose(arch);
            exit(1);
        }
        parDatos->respuesta=strdup(respuesta_leida);
        if (parDatos->respuesta == NULL) {
            fprintf(stderr, "Error: Falló strdup para la respuesta.\n");
            free(parDatos->preguntas);
            free(parDatos);
            fclose(arch);
            exit(1);
        }
        insertarL(baseDatos,1,parDatos);
    }
    fclose(arch);
}
int conversacion(AsistenteIA *usuario,Lista *baseDatos) {
    char temp_mensaje[1024];
    char *mensaje=NULL;
    char *auxbusqueda=NULL;
    int pos;
    printf("\nUsuario: ");
    
    if (fgets(temp_mensaje, sizeof(temp_mensaje), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return 1;
    }
    temp_mensaje[strcspn(temp_mensaje, "\n")] = '\0';

    char comando_temp[1024];
    size_t i;
    for (i = 0; temp_mensaje[i] && i < 1023; i++) {
        comando_temp[i] = tolower((unsigned char)temp_mensaje[i]);
    }

    comando_temp[i] = '\0';
    
    if (strcmp(comando_temp, "salir") == 0 || strcmp(comando_temp, "cerrar") == 0) {
        return 0; // Indica al main que debe salir del bucle
    }

    mensaje=strdup(temp_mensaje);
     if (!mensaje) { 
        fprintf(stderr, "Error: Falló strdup para el historial.\n"); 
        return 1; 
    }

    auxbusqueda=strdup(temp_mensaje);
     if (!auxbusqueda) {
        fprintf(stderr, "Error: Falló strdup para la búsqueda.\n");
        free(mensaje); // Limpieza
        return 1; 
    }
    size_t len = strlen(auxbusqueda);
    if (len > 0 && auxbusqueda[len - 1] == '?') {
        auxbusqueda[len - 1] = '\0';
    }
    pos=busquedaL(baseDatos,auxbusqueda,son_iguales_preguntas);
    if(pos!=-1){
        ConocimientoIA *parDatos = consultarL(baseDatos, pos);
        printf("Respuesta: %s",parDatos->respuesta);
        insertarP(usuario->mensaje,mensaje);
        insertarP(usuario->respuestaIA,parDatos->respuesta);
    }
    else{
        printf("Lo siento no tenemos esa respuesta");
    }
    free(auxbusqueda);
    return 1; 
}
int main() {
    AsistenteIA usuario;
    Lista baseDatos;
    int continuar_conversacion = 1;
    crearL(&baseDatos);
    cargarBaseConocimiento(&baseDatos, "BaseConocimiento.txt");
    
    usuario.mensaje = (Pila *)malloc(sizeof(Pila));
    usuario.respuestaIA = (Pila *)malloc(sizeof(Pila));
    
    if (usuario.mensaje == NULL || usuario.respuestaIA == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para las pilas.\n");
 
        if (usuario.mensaje) free(usuario.mensaje);
        if (usuario.respuestaIA) free(usuario.respuestaIA);
        exit(1);
    }
    crearP(usuario.mensaje);
    crearP(usuario.respuestaIA);
    printf("--- Asistente IA Iniciado ---\n");
    printf("Escribe 'salir' para terminar la conversación.\n\n");
    while (continuar_conversacion) {
        continuar_conversacion = conversacion(&usuario, &baseDatos);
    }
    printf("\n--- Conversación Finalizada ---\n");
    
    free(usuario.mensaje);
    free(usuario.respuestaIA);
    
    return 0;
}