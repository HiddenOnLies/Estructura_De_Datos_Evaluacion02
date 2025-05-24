#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Publicacion {
    int ID;
    char usuario;
    char titulo;
    char** imagenes;
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
Publicacion * cargarArchivo(const char* nombreArchivo);
void liberarPublicacion(Publicacion* actual);
void liberarLista(Publicacion* cabeza);
void menu();

// Creamos una nueva publicacion
Publicacion* crearpublicacion(int ID, char* usuario, char* titulo, char** imagenes, int num_imagenes, int me_gusta, int comentarios, int compartidos){
    Publicacion * nueva = (Publicacion *)malloc(sizeof(Publicacion));
    if (nueva == NULL) {
        printf("Error: Memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    nueva -> ID = ID;
    nueva -> usuario = usuario;
    nueva -> titulo = titulo;
    nueva -> imagenes = * imagenes;
    nueva -> num_imagenes = num_imagenes;
    nueva -> me_gusta = me_gusta;
    nueva -> comentarios = comentarios;
    nueva -> compartidos = compartidos;
    return nueva;
}

// Insertamos una publicacion al inicio de la lista
void insertarInicio(Publicacion** cabeza, Publicacion* nueva){
    nueva -> siguiente = * cabeza;
    * cabeza = nueva;
}

// Insertamos una publicacion al final de la lista
void insertarFinal(Publicacion** cabeza, Publicacion* nueva){
    if (* cabeza == NULL) {
        * cabeza = nueva;
        nueva -> siguiente = NULL;
        return;
    }
    Publicacion * actual = * cabeza;
    while (actual -> siguiente != NULL) {
        actual = actual -> siguiente;
    }
    actual -> siguiente = nueva;
    nueva -> siguiente = NULL;
}

// Eliminamos el inicio de la lista
void eliminarInicio(Publicacion** cabeza){
    if (* cabeza == NULL) {
        printf("Error: No hay publicaciones en lista\n");
        return;
    }
    Publicacion * actual = * cabeza;
    * cabeza = actual -> siguiente;
    liberarPublicacion(actual);
}

// Eliminamos el final de la lista
void eliminarFinal(Publicacion** cabeza){
    if (* cabeza == NULL) {
        printf("Error: No hay publicaciones en lista\n");
        return;
    }
    if ((* cabeza) -> siguiente == NULL) {
        liberarPublicacion(* cabeza);
        * cabeza = NULL;
        return;
    }
    Publicacion * actual = * cabeza;
    while (actual -> siguiente -> siguiente != NULL) {
        actual = actual -> siguiente;
    }
    liberarPublicacion(actual -> siguiente);
    actual -> siguiente = NULL;
}

void insertarPorID(Publicacion** cabeza, Publicacion* nueva){
    //Si la cabeza esta vacia o la publicacion nueva es menor a la cabeza insertamos en el inicio
    if(*cabeza == NULL || nueva-> ID < (*cabeza)->ID){
        insertarInicio(cabeza, nueva);
        return;
    }
    //En caso de que la nueva publicacion sea mayor que la cabeza 
    else{
        Publicacion* actual = *cabeza;
        while(actual->siguiente != NULL && actual->siguiente->ID < nueva->ID){
            actual = actual->siguiente;
        }
        nueva->siguiente = actual->siguiente;
        actual->siguiente = nueva;
    }
}

void eliminarPorID(Publicacion**cabeza, int ID){
    if (* cabeza == NULL) {
        printf("Error: No hay publicaciones en lista\n");
        return;
    }
    Publicacion* actual = *cabeza;
    //Recorremos la lista hasta dar con el ID ingresado
    while(actual->siguiente != NULL && actual->siguiente->ID != ID){
            actual = actual->siguiente;
    }
    //Liberamos la publicacion solo si es la que necesitamos
    if(actual->siguiente != NULL){
        Publicacion* temp = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        liberarPublicacion(temp);
    }
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

Publicacion * cargarArchivo(const char* nombreArchivo){
    FILE * archivo;
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }
}

// Liberamos la publicacion correspondiente asegurandonos que el arreglo de strings de las imagenes sea liberado igualmente
void liberarPublicacion(Publicacion* actual){
    for (int i = 0; i < actual->num_imagenes; i++) {
        free(actual->imagenes);
    }
    free(actual->imagenes);
    free(actual);
}

// Liberamos la lista de publicaciones completa liberando cada publicacion una a una
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