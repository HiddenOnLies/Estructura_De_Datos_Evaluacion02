#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Publicacion {
    int ID;
    char usuario;
    char titulo;
    char imagenes;
    int num_imagenes;
    int me_gusta;
    int comentarios;
    int compartidos;
    struct Publicacion* siguiente;
} Publicacion;

//Prototipo de funciones
Publicacion* crearpublicacion(int ID, char* usuario, char* titulo, char** imagenes, int num_imagenes, int me_gusta, int comentarios, int compartidos);
void insertarInicio(Publicacion** cabeza, Publicacion* nueva);
void insertarFinal(Publicacion** cabeza, Publicacion* nueva);
void eliminarInicio(Publicacion** cabeza);
void eliminarFinal(Publicacion** cabeza);
void insertarPorID(Publicacion** cabeza, Publicacion* nueva);
void eliminarPorID(Publicacion**cabeza, int ID);
void imprimirPublicacion(Publicacion* actual);
void imprimirLista(Publicacion* cabeza);
void ordenarLikes(Publicacion**cabeza);
void ordenarComentario(Publicacion** cabeza);
void ordenarCompartidos(Publicacion** cabeza);
void cargarArchivo(const char* nombreArchivo);
void liberarPublicacion(Publicacion* actual);
void liberarLista(Publicacion* cabeza);
void menu();

//Funcion para crear un nuevo nodo
Publicacion* crearpublicacion(int ID, char* usuario, char* titulo, char** imagenes, int num_imagenes, int me_gusta, int comentarios, int compartidos){
}

void insertarInicio(Publicacion** cabeza, Publicacion* nueva){

}

void insertarFinal(Publicacion** cabeza, Publicacion* nueva){

}

void eliminarInicio(Publicacion** cabeza){

}

void eliminarFinal(Publicacion** cabeza){

}

void insertarPorID(Publicacion** cabeza, Publicacion* nueva){

}

void eliminarPorID(Publicacion**cabeza, int ID){

}

void imprimirPublicacion(Publicacion* actual){

}

void imprimirLista(Publicacion* cabeza){
    
}

void ordenarLikes(Publicacion** cabeza){

}

void ordenarComentario(Publicacion** cabeza){

}

void ordenarCompartidos(Publicacion** cabeza){

}

void cargarArchivo(const char* nombreArchivo){

}

void liberarPublicacion(Publicacion* actual){
    for (int i = 0; i < actual->num_imagenes; i++) {
        free(actual->imagenes);
    }
    free(actual->imagenes);
    free(actual);
}

void liberarLista(Publicacion* cabeza){
    Publicacion* actual = cabeza;
    while (actual != NULL) {
        Publicacion* siguiente = actual->siguiente;
        liberarPublicacion(actual);
        actual = siguiente;
    }
}


void menu(){
    printf("\n--- MENU ---\n");
    printf("1. Insertar publicación al inicio\n");
    printf("2. Insertar publicación al final\n");
    printf("3. Insertar publicación ordenada por ID\n");
    printf("4. Eliminar primera publicación\n");
    printf("5. Eliminar última publicación\n");
    printf("6. Eliminar publicación por ID\n");
    printf("7. Mostrar publicaciones\n");
    printf("8. Ordenar por Me Gusta\n");
    printf("9. Ordenar por Comentarios\n");
    printf("10. Ordenar por Compartido\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

int main(){
    return 0;
}