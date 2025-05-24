#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Publicacion {
    int ID;
    char* usuario;
    char* titulo;
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
    strcpy(nueva -> usuario, usuario);
    strcpy(nueva -> titulo, titulo);
    nueva -> num_imagenes = num_imagenes;
    nueva -> imagenes = malloc(num_imagenes * sizeof(char*));
    for (int i = 0; i < num_imagenes; i++) {
        strcpy(nueva -> imagenes[i], imagenes[i]);
    }
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
    printf("ID: \n%d", actual -> ID);
    printf("Usuario: \n%s", actual -> usuario);
    printf("Titulo: \n%s", actual -> titulo );
    printf("Imagenes: ");
    for(int i = 0; i < actual->num_imagenes; i++){
        printf("%s", actual->imagenes[i]);
    }
    printf("Like: \n%d", actual -> me_gusta);
    printf("Comentarios: \n%d", actual -> comentarios);
    printf("Compartidos: \n%d", actual -> compartidos);
}

void imprimirLista(Publicacion* cabeza){
    while(cabeza -> siguiente != NULL){
        printf(cabeza);
    }
    
}

void intercambiaDatos(Publicacion* a, Publicacion* b ){
    Publicacion temp = *a;
    
    // Intercambiar todos los campos excepto 'siguiente'
    a->ID = b->ID;
    strcpy(a->usuario, b->usuario);
    strcpy(a->titulo, b->titulo);
    
    // Intercambiar arreglo de imágenes
    char** temp_imagenes = a->imagenes;
    a->imagenes = b->imagenes;
    b->imagenes = temp_imagenes;
    
    // Intercambiar valores numéricos
    a->num_imagenes = b->num_imagenes;
    a->me_gusta = b->me_gusta;
    a->comentarios = b->comentarios;
    a->compartidos = b->compartidos;
    
    // Asignar los valores a b
    b->ID = temp.ID;
    strcpy(b->usuario, temp.usuario);
    strcpy(b->titulo, temp.titulo);
    b->imagenes = temp.imagenes;
    b->num_imagenes = temp.num_imagenes;
    b->me_gusta = temp.me_gusta;
    b->comentarios = temp.comentarios;
    b->compartidos = temp.compartidos;

}

void ordenarLikes(Publicacion** cabeza){
    if(*cabeza == NULL || (*cabeza)->siguiente == NULL){
        printf("Error: No se puede ordenar datos insuficientes");
        return;
    }
    //Intercambia actua como un bool 
    int intercambia = 0;
    Publicacion* ptr1;
    Publicacion* ptr2;
    do
    {
        ptr1 = *cabeza;
        while (ptr1->siguiente != ptr2)
        {
            if (ptr1->me_gusta < ptr1->siguiente->me_gusta){
                intercambiaDatos(ptr1, ptr1->siguiente);
                intercambia = 1;
            }
            ptr1 = ptr1->siguiente;
        }
        ptr2 = ptr1;
    }  
    while (intercambia);
    
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
    
    fclose(archivo);
}

// Liberamos la publicacion correspondiente asegurandonos que el arreglo de strings sean liberados igualmente
void liberarPublicacion(Publicacion* actual){
    free(actual->usuario);
    free(actual->titulo);
    for (int i = 0; i < actual->num_imagenes; i++) {
        free(actual->imagenes[i]);
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