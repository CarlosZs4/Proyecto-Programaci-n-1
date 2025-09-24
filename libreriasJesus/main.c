#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pila.h"
#include "cola.h"
typedef struct Musica
{
    char nombre[30],artista[30];
    int duracion,extreno;
}Musica;

// Funciones de comparación para ordenar
int comparar_enteros(void* a, void* b) {
    int* num1 = (int*)a;
    int* num2 = (int*)b;
    return (*num1 - *num2);
}

// Función para comparar caracteres
int comparar_caracteres(void* a, void* b) {
    char* char1 = (char*)a;
    char* char2 = (char*)b;
    // Comparamos los valores ASCII
    return (*char1 - *char2);
}
int comparar_cadenas(void* a, void* b) {
    char* str1 = (char*)a;
    char* str2 = (char*)b;
    return strcmp(str1, str2); // strcmp ya devuelve un valor que sigue la convención
}
int comparar_musicaDuracion(void* a, void* b){
    Musica* musica1=(Musica*)a;
    Musica* musica2=(Musica*)b;
    return comparar_enteros(&musica1->duracion,&musica2->duracion);
}
int comparar_musicaExtreno(void* a, void* b){
    Musica* musica1=(Musica*)a;
    Musica* musica2=(Musica*)b;
    return comparar_enteros(&musica1->extreno,&musica2->extreno);
}
int comparar_musicaArtista(void* a, void* b){
    Musica* musica1=(Musica*)a;
    Musica* musica2=(Musica*)b;
    return comparar_cadenas(musica1->artista,musica2->artista);
}
int comparar_musicaNombre(void* a, void* b){
    Musica* musica1=(Musica*)a;
    Musica* musica2=(Musica*)b;
    return comparar_cadenas(musica1->nombre,musica2->nombre);
}

// Funciones para imprimir elementos de cada tipo
void imprimir_entero(void* dato) {
    printf("%d", *(int*)dato);
}

void imprimir_caracter(void* dato) {
    printf("%c", *(char*)dato);
}
void imprimir_cadenas(void* dato) {
    printf("%s", (char*)dato);
}
void imprimir_playlist(void *dato){
    Musica* musica = (Musica*)dato; // 1. Castear el puntero
    
    printf("Musica:\n");
    printf("  Nombre: ");
    imprimir_cadenas(musica->nombre); // Llamada a la función auxiliar
    printf("\n");
    
    printf("  Artista: ");
    imprimir_cadenas(musica->artista); // Llamada a la función auxiliar
    printf("\n");
    
    printf("  Duracion: ");
    imprimir_entero(&musica->duracion); // 2. Pasar la dirección
    printf("\n");
    
    printf("  Año de estreno: ");
    imprimir_entero(&musica->extreno); // 2. Pasar la dirección
    printf("\n");
}
//funciones de escritura
void escribir_musica(void* dato, FILE* archivo) {
    Musica* musica = (Musica*)dato;
    fprintf(archivo, "%s %s %d %d\n", musica->artista, musica->nombre, musica->duracion, musica->extreno);
}
//Funciones de igualdad
int son_iguales_enteros(void* a, void* b) {
    int* num1 = (int*)a;
    int* num2 = (int*)b;
    return (*num1 == *num2);
}

int son_iguales_caracteres(void* a, void* b) {
    char* c1 = (char*)a;
    char* c2 = (char*)b;
    return (*c1 == *c2);
}
int son_iguales_string(void *a,void *b){
    char* str1 = (char*)a;
    char* str2 = (char*)b;
    return(strcmp(str1, str2));
}
int son_iguales_musicaNombre(void *a,void *b){
    Musica *musica1=(Musica*)a;
    char* artista_buscado = (char*)b;
    return strcmp(musica1->nombre, artista_buscado) == 0;
}
int son_iguales_musicaArtista(void *a,void *b){
    Musica *musica1=(Musica*)a;
    char* artista_buscado = (char*)b;
    return strcmp(musica1->artista, artista_buscado) == 0;
}

void extraerDoc(Lista *playlist){
    FILE *arch=fopen("playlist.txt","r");
    if (arch == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    int n;
    fscanf(arch,"%d",&n);
    for (int i = 1; i <= n; i++)
    {
        Musica* musica=malloc(sizeof(Musica));
        if (musica == NULL) {
            printf("Error: No se pudo asignar memoria para la musica.");
            break; // Sal del bucle si falla la asignación
        }
        fscanf(arch,"%s %s %d %d",musica->artista,musica->nombre,&musica->duracion,&musica->extreno);
        insertarL(playlist,i,musica);
    }
    fclose(arch);
}
void anadirMusica(Lista *playlist){
    Musica *musica=malloc(sizeof(Musica));
    if (musica == NULL) {
        printf("Error: No se pudo asignar memoria para la musica.\n");
        return;
    }
    printf("\nIngrese el nombre de la musica:\n");
    scanf("%s",musica->nombre);
    printf("\nIngrese el nombre del cantante:\n");
    scanf("%s",musica->artista);
    printf("\nIngrese la duracion de la musica:\n");
    scanf("%d",&musica->duracion);
    printf("\nIngrese cuando se extreno la musica:\n");
    scanf("%d",&musica->extreno);
    insertarL(playlist,1,musica);

}
void ordenarTipo(Lista *playlist){
    int opcion;
    printf("---Ingrese un numero para la opcion que quiere hacer---\n1)Por Nombre\n2)Por Artista\n3)Por Duracion\n4)Por su fecha de Extreno");
    scanf("%d",&opcion);
    printf("\n");
    switch (opcion)
    {
    case 1:
        ordenarL(playlist,comparar_musicaNombre);
        break;
    case 2:
        ordenarL(playlist,comparar_musicaArtista);
        break;
    case 3:
        ordenarL(playlist,comparar_musicaDuracion);
        break;
    case 4:
        ordenarL(playlist,comparar_musicaExtreno);
        break;    
    default:
        break;
    }
}
void buscarTipo(Lista *playlist){
    char *buscar=malloc(sizeof(char)*20);
     int opcion;
     Lista *resultado=NULL;

     if (buscar == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }

    printf("---Ingrese un numero para la opcion que quiere hacer---\n1)Por Nombre\n2)Por Artista\n");
    scanf("%d",&opcion);
    printf("Ingrese el nombre:");
    scanf("%s",buscar);
    printf("\n");
    switch (opcion)
    {
    case 1:
        resultado=busquedaTodasL(playlist,buscar,son_iguales_musicaNombre);
        break;
    case 2:
        resultado=busquedaTodasL(playlist,buscar,son_iguales_musicaArtista);
        break;
    default:
        printf("Opcion invalida");
        break;
    }
    if(resultado!=NULL){
        imprimirL(resultado,imprimir_playlist);
        liberarL(resultado);
    }
    else{
        printf("No se ha encuentrado");
    }
    free(buscar);
}

int main() {
    int opcion,pos;
    char nombreArch[20];
    Lista playlist;
    int band=1;
    crearL(&playlist);
    extraerDoc(&playlist);
    do{
        printf("---Ingrese un numero para la opcion que quiere hacer---\n1)Ingresar\n2)Eliminar\n3)Mostrar\n4)Ordenar\n5)Buscar\n6)Guardar y salir\nNumero: ");
        scanf("%d",&opcion);
        printf("\n---------------\n");
        switch (opcion)
        {
        case 1:
            anadirMusica(&playlist);
            break;
        case 2:
            printf("\nIngrese el numero de la musica\n");
            scanf("%d",&pos);
            eliminarL(&playlist,pos);
            break;
        case 3:
            imprimirL(&playlist,imprimir_playlist);
            break;
        case 4:
            ordenarTipo(&playlist);
            break;
        case 5:
            buscarTipo(&playlist);
            break;
        case 6:
            printf("\nEscriba el nombre del archivo:\n");
            scanf("%s",nombreArch);
            imprimirArchL(&playlist,nombreArch,escribir_musica);
            band=0;
            break;
        default:
            printf("\nIngrese una opcion valida\n");
            break;
        }
    }while(band==1);
    return 0;
}