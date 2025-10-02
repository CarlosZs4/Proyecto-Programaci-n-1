#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "pila.h"
#include "AsistenteIA.h"
int son_iguales_preguntas(void *parConocimiento, void *preguntaBusqueda) {
    ConocimientoIA* par = (ConocimientoIA*)parConocimiento;
    char* pregunta_usuario_sin_q = (char*)preguntaBusqueda; 

    if (pregunta_usuario_sin_q == NULL || *pregunta_usuario_sin_q == '\0') {
        return 0; // Falso (No son iguales)
    }
    size_t len_db_q = strlen(par->preguntas);
    if (len_db_q > 0 && par->preguntas[len_db_q - 1] == '?') {
        if (strlen(pregunta_usuario_sin_q) == len_db_q - 1) { 
            return (strncmp(pregunta_usuario_sin_q, par->preguntas, len_db_q - 1) == 0);
        }
        return 0; // Falso (No son iguales)
    }

    return (strcmp(par->preguntas, pregunta_usuario_sin_q) == 0);
}
void imprimir_baseDatos(void *a){
    ConocimientoIA *Pardatos=(ConocimientoIA*)a;
    printf("\n%s\n.",Pardatos->preguntas);
    printf("\n%s\n.",Pardatos->respuesta);
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
        size_t len_pregunta = strlen(pregunta_leida);
        parDatos->preguntas = (char*)malloc(len_pregunta + 2);
        if(parDatos==NULL){
            printf("Error: No se pudo asignar memoria a la base de datos.\n");
            exit(1);
        }
        strcpy(parDatos->preguntas, pregunta_leida);
        parDatos->preguntas[len_pregunta] = '?'; // Añade el delimitador
        parDatos->preguntas[len_pregunta + 1] = '\0';

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
int conversacion(AsistenteIA *asistente,Lista *baseDatos,usuario *Datousuario) {
    char temp_mensaje[1024];
    char *mensaje=NULL;
    char *auxbusqueda=NULL;
    int pos=-1;
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
        insertarP(asistente->mensaje,mensaje);
        insertarP(asistente->respuestaIA,parDatos->respuesta);
        Datousuario->cantidadConsultas++;
    }
    else{
        printf("Lo siento no tenemos esa respuesta");
        Datousuario->cantidadConsultasSinRespuesta++;
        insertarP(asistente->pendientes,mensaje);
    }
    free(auxbusqueda);
    return 1; 
}
void guardarHistorial(AsistenteIA *asistente, usuario *datosUsuario, const char *nombreArchivo) {
    if(longitudP(asistente->mensaje)==0&&longitudP(asistente->respuestaIA)==0){
        return;
    }
    FILE *arch = fopen(nombreArchivo, "a");
    if (arch == NULL) {
        perror("Error al abrir el archivo de conversación");
        return;
    }

    Pila pilaAuxMensajes, pilaAuxRespuestas;
    crearP(&pilaAuxMensajes);
    crearP(&pilaAuxRespuestas);

    char *mensaje, *respuesta;

    while (asistente->mensaje->apilar != NULL && asistente->respuestaIA->apilar != NULL) {
        mensaje = (char *)consultarP(asistente->mensaje);
        respuesta = (char *)consultarP(asistente->respuestaIA);
        
        insertarP(&pilaAuxMensajes, mensaje);
        insertarP(&pilaAuxRespuestas, respuesta);
        
        eliminarP(asistente->mensaje);
        eliminarP(asistente->respuestaIA);
    }
    
    fprintf(arch, "%ld|%s|%s|", 
            datosUsuario->cedula, 
            datosUsuario->nombre, 
            datosUsuario->apellido);

    while (pilaAuxMensajes.apilar != NULL && pilaAuxRespuestas.apilar != NULL) {
        mensaje = (char *)consultarP(&pilaAuxMensajes);
        respuesta = (char *)consultarP(&pilaAuxRespuestas);
        
        fprintf(arch, "%s|%s|", mensaje, respuesta); 
        
        insertarP(asistente->mensaje, mensaje);
        insertarP(asistente->respuestaIA, respuesta);

        eliminarP(&pilaAuxMensajes);
        eliminarP(&pilaAuxRespuestas);
    }
    
    fprintf(arch, "\n###FIN_SESION###\n"); 
    
    fclose(arch);
}
void mostrarHistorial(long cedulaUsuario, const char *nombreArchivo) {
    FILE *arch = fopen(nombreArchivo, "r");
    if (arch == NULL) {
        perror("Error al abrir el archivo de historial");
        return;
    }

    char linea[4096]; 
    bool encontrado = false;
    int sesion_count = 1;

    printf("\n--- Historial de Conversación (Usuario ID: %ld) ---\n", cedulaUsuario);

    while (fgets(linea, sizeof(linea), arch) != NULL) {
        linea[strcspn(linea, "\n")] = 0; 

        if (strstr(linea, "###FIN_SESION###")) {
            continue; 
        }
        char *datos_usuario = strdup(linea);
        if (!datos_usuario) continue;

        char *token = strtok(datos_usuario, "|"); 
        if (!token) { free(datos_usuario); continue; }

        long cedulaLeida = atol(token);
        if (cedulaLeida == cedulaUsuario) {
            encontrado = true;
            printf("\n--- SESIÓN %d ---\n", sesion_count++);
    
            token = strtok(NULL, "|"); 
            token = strtok(NULL, "|");
  
            char *dialogo = strtok(NULL, "");
            
            if (dialogo) {
                char *turno = strtok(dialogo, "|");
                int turno_dialogo = 1;
                
                while (turno) {
                    char *pregunta = turno;
                    turno = strtok(NULL, "|");

                    if (turno) {
                        char *respuesta = turno;
                        printf("  [Turno %d] Usuario: %s\n", turno_dialogo, pregunta);
                        printf("  [Turno %d] Asistente: %s\n", turno_dialogo, respuesta);
                        turno_dialogo++;
                        turno = strtok(NULL, "|"); 
                    } else {
                        break;
                    }
                }
            }
        }
        free(datos_usuario);
    }

    if (!encontrado) {
        printf("\nNo se encontraron sesiones de conversación para el usuario %ld.\n", cedulaUsuario);
    }
    printf("\n------------------------------------------------\n");
    
    fclose(arch);
}
void eliminarUltimaPeticion(AsistenteIA *asistente){
    if(asistente->mensaje->apilar!=NULL&&asistente->respuestaIA->apilar!=NULL){
        char *ultimo_mensaje = (char *)consultarP(asistente->mensaje);
        eliminarP(asistente->mensaje);
        eliminarP(asistente->respuestaIA);
        printf("Última petición deshecha: [%s]\n", ultimo_mensaje);
    }
    else{
        printf("No hay peticiones en la sesión actual para deshacer.\n");
    }
}
void actualizarBaseDatos(Lista *baseDatos){
    char temp_pregunta[1024];
    char temp_respuestas[1024];
    ConocimientoIA *parDatos=(ConocimientoIA *)malloc(sizeof(ConocimientoIA));
    if(parDatos==NULL){
            printf("Error: No se pudo asignar memoria a la base de datos.\n");
            exit(1);
        }
    printf("\nIngrese la pregunta: ");
    
    if (fgets(temp_pregunta, sizeof(temp_pregunta), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        free(parDatos);
        return ;
    }
    temp_pregunta[strcspn(temp_pregunta, "\n")] = '\0';
    if (strlen(temp_pregunta) == 0) {
        printf("La pregunta no puede estar vacía. Cancelando actualización.\n");
        return;
    }
    size_t len = strlen(temp_pregunta);
    if (temp_pregunta[len - 1] != '?') {
        // Si el string tiene espacio para el '?'
        if (len < sizeof(temp_pregunta) - 1) { 
            temp_pregunta[len] = '?';   // Añade el '?'
            temp_pregunta[len + 1] = '\0'; // Asegura que termina con nulo
            printf("Aviso: Se ha añadido un signo de interrogación al final de la pregunta.\n");
        } else {
            // El buffer está lleno, no se puede añadir el '?'
            printf("Advertencia: No se pudo añadir '?' debido a la longitud máxima.\n");
        }
    }
    parDatos->preguntas=strdup(temp_pregunta);
    if (parDatos->preguntas == NULL) { 
        printf("Error: No se pudo asignar memoria para la pregunta.\n");
        free(parDatos);
        return;
    }
    printf("\nIngrese su respuesta: ");
    if(fgets(temp_respuestas, sizeof(temp_respuestas), stdin) == NULL){
        printf("Error al leer la entrada.\n");
        free(parDatos->preguntas);
        free(parDatos);
        return ;
    }
    temp_respuestas[strcspn(temp_respuestas, "\n")] = '\0';
    if (strlen(temp_respuestas) == 0) {
        printf("La respuesta no puede estar vacía. Cancelando actualización.\n");
        return;
    }
    parDatos->respuesta=strdup(temp_respuestas);
    if (parDatos->respuesta == NULL) { // Verificar si strdup falló
        printf("Error: No se pudo asignar memoria para la respuesta.\n");
        free(parDatos->preguntas);
        free(parDatos);
        return;
    }
    insertarL(baseDatos,1,parDatos);

}
void guardarBaseConocimiento(Lista *baseDatos, const char *nombreArchivo) {
    FILE *arch = fopen(nombreArchivo, "w"); 
    if (arch == NULL) {
        perror("Error al abrir el archivo de conocimientos para escritura");
        return;
    }
    Nodo *actual = baseDatos->listar; 

    printf("Guardando %s...\n", nombreArchivo);

    while (actual != NULL) {
        ConocimientoIA *par = (ConocimientoIA *)actual->info; 

        if (par != NULL && par->preguntas != NULL && par->respuesta != NULL) {
            
            fprintf(arch, "%s %s\n", par->preguntas, par->respuesta);
        }

        actual = actual->prox;
    }
    fclose(arch);
    printf("Base de Conocimiento actualizada y guardada correctamente.\n");
}