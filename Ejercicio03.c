#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct publicacion {
    int ID;
    char usuario;
    char titulo;
    char imagenes;
    int num_imagenes;
    int me_gusta;
    int comentarios;
    struct publicacion* siguiente;
} publicacion;

publicacion* crearpublicacion(int ID, char usuario[], char titulo[], char imagenes[], int num_imagenes){
    publicacion* nueva = (publicacion*)malloc(sizeof(publicacion));
}