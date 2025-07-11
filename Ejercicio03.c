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
void intercambiaDatos(Publicacion* a, Publicacion* b);
void ordenarPorID(Publicacion ** cabeza);
void ordenarLikes(Publicacion**cabeza);
void ordenarComentario(Publicacion** cabeza);
void ordenarCompartidos(Publicacion** cabeza);
void liberarPublicacion(Publicacion* actual);
void liberarLista(Publicacion* cabeza);
Publicacion * cargarArchivo(const char* nombreArchivo);
void menu();

// Creamos una nueva publicacion
Publicacion* crearpublicacion(int ID, char* usuario, char* titulo, char** imagenes, int num_imagenes, int me_gusta, int comentarios, int compartidos) {
    Publicacion* nueva = (Publicacion*)malloc(sizeof(Publicacion));
    if (nueva == NULL) {
        printf("Error: Memoria insuficiente\n");
        return NULL;
    }

    nueva->ID = ID;
    
    // Asignar memoria para usuario y copiar
    nueva->usuario = (char*)malloc(strlen(usuario) + 1);
    if (nueva->usuario == NULL) {
        free(nueva);
        return NULL;
    }
    strcpy(nueva->usuario, usuario);
    
    // Asignar memoria para título y copiar
    nueva->titulo = (char*)malloc(strlen(titulo) + 1);
    if (nueva->titulo == NULL) {
        free(nueva->usuario);
        free(nueva);
        return NULL;
    }
    strcpy(nueva->titulo, titulo);
    
    // Asignar memoria para imágenes
    nueva->num_imagenes = num_imagenes;
    nueva->imagenes = (char**)malloc(num_imagenes * sizeof(char*));
    if (nueva->imagenes == NULL) {
        free(nueva->usuario);
        free(nueva->titulo);
        free(nueva);
        return NULL;
    }
    
    // Copiar cada imagen
    for (int i = 0; i < num_imagenes; i++) {
        nueva->imagenes[i] = (char*)malloc(strlen(imagenes[i]) + 1);
        if (nueva->imagenes[i] == NULL) {
            // Liberar memoria ya asignada
            for (int j = 0; j < i; j++) {
                free(nueva->imagenes[j]);
            }
            free(nueva->imagenes);
            free(nueva->usuario);
            free(nueva->titulo);
            free(nueva);
            return NULL;
        }
        strcpy(nueva->imagenes[i], imagenes[i]);
    }
    
    nueva->me_gusta = me_gusta;
    nueva->comentarios = comentarios;
    nueva->compartidos = compartidos;
    nueva->siguiente = NULL;
    
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
        printf("Error: No hay publicaciones en la lista\n");
        return;
    }
    Publicacion * actual = * cabeza;
    * cabeza = actual -> siguiente;
    liberarPublicacion(actual);
}

// Eliminamos el final de la lista
void eliminarFinal(Publicacion** cabeza){
    if (* cabeza == NULL) {
        printf("Error: No hay publicaciones en la lista\n");
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
    ordenarPorID(cabeza);
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

void eliminarPorID(Publicacion** cabeza, int ID) {
    if (*cabeza == NULL) {
        printf("Error: No hay publicaciones en la lista\n");
        return;
    }
    Publicacion* actual = *cabeza;
    Publicacion* anterior = NULL;
    // Caso que pasa si la publicacion a eliminar es la cabeza
    if (actual != NULL && actual->ID == ID) {
        *cabeza = actual->siguiente; // Cambia la cabeza
        liberarPublicacion(actual);
        printf("Publicacion con ID %d eliminada\n", ID);
        return;
    }
    // Recorreremos las publicaciones hasta encontrar el ID
    while (actual != NULL && actual->ID != ID) {
        anterior = actual;
        actual = actual->siguiente;
    }
    // Caso que pasa si no se encontró el ID
    if (actual == NULL) {
        printf("Error: No se encontro publicacion con ID %d\n", ID);
        return;
    }
    // Desenlazamos la publicacion actual de la lista y enlazamos la publicacion anterior como corresponde
    anterior->siguiente = actual->siguiente;
    // Liberamos memoria
    liberarPublicacion(actual);
    printf("Publicacion con ID %d eliminada\n", ID);
}

void imprimirPublicacion(Publicacion* actual){
    printf("ID: %d\n", actual -> ID);
    printf("Usuario: %s\n", actual -> usuario);
    printf("Titulo: %s\n", actual -> titulo );
    printf("Imagenes: ");
    for(int i = 0; i < actual->num_imagenes; i++){
        printf("%s, ", actual->imagenes[i]);
    }
    printf("\nLikes: %d\n", actual -> me_gusta);
    printf("Comentarios: %d\n", actual -> comentarios);
    printf("Compartidos: %d\n", actual -> compartidos);
}

void imprimirLista(Publicacion* cabeza) {
    if (cabeza == NULL) {
        printf("Error: No hay publicaciones en la lista\n");
        return;
    }
    Publicacion* actual = cabeza;
    int i = 1;
    while (actual != NULL) {
        printf("\n--- Publicacion %d ---\n", i++);
        imprimirPublicacion(actual);
        actual = actual->siguiente;
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

void ordenarPorID(Publicacion** cabeza) {
    // Verificacion de que la lista no este vacia
    if(*cabeza == NULL || (*cabeza)->siguiente == NULL) {
        printf("Error: No se puede ordenar, datos insuficientes\n");
        return;
    }
    
    int intercambia = 1;
    Publicacion* ptr1;
    Publicacion* ptr2 = NULL;
    
    do {
        intercambia = 0;
        ptr1 = *cabeza;
        
        while (ptr1->siguiente != ptr2) {
            if (ptr1->ID > ptr1->siguiente->ID) {
                intercambiaDatos(ptr1, ptr1->siguiente);
                intercambia = 1;
            }
            ptr1 = ptr1->siguiente;
        }
        ptr2 = ptr1;
    } while (intercambia);
}

void ordenarLikes(Publicacion** cabeza){
    if(*cabeza == NULL || (*cabeza)->siguiente == NULL){
        printf("Error: No se puede ordenar, datos insuficientes");
        return;
    }
    //Intercambia actua como un bool 
    int intercambia = 1;
    Publicacion* ptr1;
    Publicacion* ptr2 = NULL;
    do
    {   
        intercambia = 0;
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
    if(*cabeza == NULL || (*cabeza)->siguiente == NULL){
        printf("Error: No se puede ordenar, datos insuficientes");
        return;
    }
    //Intercambia actua como un bool 
    int intercambia = 1;
    Publicacion* ptr1;
    Publicacion* ptr2 = NULL;
    do
    {   
        intercambia = 0;
        ptr1 = *cabeza;
        while (ptr1->siguiente != ptr2)
        {
            if (ptr1->comentarios < ptr1->siguiente->comentarios){
                intercambiaDatos(ptr1, ptr1->siguiente);
                intercambia = 1;
            }
            ptr1 = ptr1->siguiente;
        }
        ptr2 = ptr1;
    }  
    while (intercambia);
    
}

void ordenarCompartidos(Publicacion** cabeza){
    if(*cabeza == NULL || (*cabeza)->siguiente == NULL){
        printf("Error: No se puede ordenar, datos insuficientes");
        return;
    }
    //Intercambia actua como un bool 
    int intercambia = 1;
    Publicacion* ptr1;
    Publicacion* ptr2 = NULL;
    do
    {   
        intercambia = 0;
        ptr1 = *cabeza;
        while (ptr1->siguiente != ptr2)
        {
            if (ptr1->compartidos < ptr1->siguiente->compartidos){
                intercambiaDatos(ptr1, ptr1->siguiente);
                intercambia = 1;
            }
            ptr1 = ptr1->siguiente;
        }
        ptr2 = ptr1;
    }  
    while (intercambia);

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

Publicacion* cargarArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: Archivo no encontrado. Se creará una lista vacía.\n");
        return NULL;
    }
    
    Publicacion* lista = NULL;
    // Cantidad maxima de caracteres por lineas
    char linea[2048];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        // Eliminar salto de línea
        linea[strcspn(linea, "\n")] = '\0';
        
        // Variables temporales
        int ID;
        char usuario[100], titulo[200];
        char imagenes_str[500], metricas_str[100];
        
        // Parsear la línea
        if (sscanf(linea, "%d; %99[^;]; %199[^;]; %499[^;]; %99[^;];", &ID, usuario, titulo, imagenes_str, metricas_str) != 5) {
            printf("Formato incorrecto en línea: %s\n", linea);
            continue;
        }
        
        // Procesar imágenes
        char* imagenes[20] = {NULL};
        int num_imagenes = 0;
        
        // Eliminar corchetes de las imágenes
        char* img_inicio = strchr(imagenes_str, '[');
        char* img_final = strchr(imagenes_str, ']');
        if (img_inicio && img_final) {
            *img_final = '\0';
            char* separado = strtok(img_inicio + 1, ",");
            while (separado != NULL && num_imagenes < 20) {
                // Eliminar espacios en blanco
                while (*separado == ' ') {
                    separado++;
                }
                char* final = separado + strlen(separado) - 1;
                while (final > separado && *final == ' ') final--;
                *(final + 1) = '\0';
                
                if (*separado != '\0') {
                    imagenes[num_imagenes] = (char*)malloc(strlen(separado) + 1);
                    if (imagenes[num_imagenes] != NULL) {
                        strcpy(imagenes[num_imagenes], separado);
                        num_imagenes++;
                    }
                }
                separado = strtok(NULL, ",");
            }
        }
        
        // Procesar métricas
        int me_gusta = 0, comentarios = 0, compartidos = 0;
        sscanf(metricas_str, "[%d, %d, %d]", &me_gusta, &comentarios, &compartidos);
        
        // Crear publicación
        Publicacion* nueva = crearpublicacion(ID, usuario, titulo, imagenes, num_imagenes, me_gusta, comentarios, compartidos);
        if (nueva != NULL) {
            insertarFinal(&lista, nueva);
        }
        
        // Liberar memoria temporal
        for (int i = 0; i < num_imagenes; i++) {
            free(imagenes[i]);
        }
    }

    
    fclose(archivo);
    return lista;
}

void menu(){
    printf("\n----- MENU -----\n");
    printf("1). Insertar publicacion al inicio\n");  
    printf("2). Insertar publicacion al final\n");
    printf("3). Insertar publicacion ordenada por ID\n");
    printf("4). Eliminar primera publicacion\n");
    printf("5). Eliminar ultima publicacion\n");
    printf("6). Eliminar publicacion por ID\n");
    printf("7). Mostrar publicaciones\n");
    printf("8). Ordenar por Me Gusta\n");
    printf("9). Ordenar por Comentarios\n");
    printf("10). Ordenar por Compartido\n");
    printf("11). Ordenar por ID\n");
    printf("0). Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Publicacion* lista = cargarArchivo("status_ini_social_net.txt");
    int opcion;
    int ID;
    char usuario[100];
    char titulo[200];
    int num_imagenes;
    char** imagenes;
    int me_gusta;
    int comentarios;
    int compartidos;
    char img[100];
    Publicacion* nueva;
    
    do {
        menu();
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1: { // Insertar al inicio
                printf("Ingrese ID: ");
                scanf("%d", &ID);
                
                printf("Ingrese usuario: ");
                scanf(" %[^\n]", usuario);
                
                printf("Ingrese titulo: ");
                scanf(" %[^\n]", titulo);
                
                printf("Numero de imagenes: ");
                scanf("%d", &num_imagenes);
                
                imagenes = (char**)malloc(num_imagenes * sizeof(char*));
                for (int i = 0; i < num_imagenes; i++) {
                    printf("Imagen %d: ", i+1);
                    scanf(" %[^\n]", img);
                    imagenes[i] = (char*)malloc(strlen(img) + 1);
                    strcpy(imagenes[i], img);
                }
                
                printf("Me gusta: ");
                scanf("%d", &me_gusta);
                
                printf("Comentarios: ");
                scanf("%d", &comentarios);
                
                printf("Compartidos: ");
                scanf("%d", &compartidos);
                
                nueva = crearpublicacion(ID, usuario, titulo, imagenes, num_imagenes, me_gusta, comentarios, compartidos);
                insertarInicio(&lista, nueva);
                
                // Liberar memoria temporal
                for (int i = 0; i < num_imagenes; i++) {
                    free(imagenes[i]);
                }
                free(imagenes);
                break;
            }
            case 2: { // Insertar al final
                printf("Ingrese ID: ");
                scanf("%d", &ID);
                
                printf("Ingrese usuario: ");
                scanf(" %[^\n]", usuario);
                
                printf("Ingrese titulo: ");
                scanf(" %[^\n]", titulo);
                
                printf("Numero de imagenes: ");
                scanf("%d", &num_imagenes);
                
                imagenes = (char**)malloc(num_imagenes * sizeof(char*));
                for (int i = 0; i < num_imagenes; i++) {
                    printf("Imagen %d: ", i+1);
                    scanf(" %[^\n]", img);
                    imagenes[i] = (char*)malloc(strlen(img) + 1);
                    strcpy(imagenes[i], img);
                }
                
                printf("Me gusta: ");
                scanf("%d", &me_gusta);
                
                printf("Comentarios: ");
                scanf("%d", &comentarios);
                
                printf("Compartidos: ");
                scanf("%d", &compartidos);
                
                nueva = crearpublicacion(ID, usuario, titulo, imagenes, num_imagenes, me_gusta, comentarios, compartidos);
                insertarFinal(&lista, nueva);
                
                // Liberar memoria temporal
                for (int i = 0; i < num_imagenes; i++) {
                    free(imagenes[i]);
                }
                free(imagenes);
                break;
            }
            case 3: { // Insertar ordenado por ID
            
                printf("Ingrese ID: ");
                scanf("%d", &ID);
                
                printf("Ingrese usuario: ");
                scanf(" %[^\n]", usuario);
                
                printf("Ingrese titulo: ");
                scanf(" %[^\n]", titulo);
                
                printf("Numero de imagenes: ");
                scanf("%d", &num_imagenes);
                
                imagenes = (char**)malloc(num_imagenes * sizeof(char*));
                for (int i = 0; i < num_imagenes; i++) {
                    printf("Imagen %d: ", i+1);
                    scanf(" %[^\n]", img);
                    imagenes[i] = (char*)malloc(strlen(img) + 1);
                    strcpy(imagenes[i], img);
                }
                
                printf("Me gusta: ");
                scanf("%d", &me_gusta);
                
                printf("Comentarios: ");
                scanf("%d", &comentarios);
                
                printf("Compartidos: ");
                scanf("%d", &compartidos);
                
                nueva = crearpublicacion(ID, usuario, titulo, imagenes, num_imagenes, me_gusta, comentarios, compartidos);
                insertarPorID(&lista, nueva);
                
                // Liberar memoria temporal
                for (int i = 0; i < num_imagenes; i++) {
                    free(imagenes[i]);
                }
                free(imagenes);
                break;
            }
            case 4: // Eliminar inicio
                eliminarInicio(&lista);
                break;
                
            case 5: // Eliminar final
                eliminarFinal(&lista);
                break;
                
            case 6: // Eliminar por ID
                printf("Ingrese el ID de la publicacion que desea eliminar: ");
                scanf("%d", &ID);
                eliminarPorID(&lista, ID);
                break;
                
            case 7: // Mostrar publicaciones
                imprimirLista(lista);
                break;
                
            case 8: // Ordenar por likes
                ordenarLikes(&lista);
                printf("Publicaciones ordenadas por likes\n");
                break;
                
            case 9: // Ordenar por comentarios
                ordenarComentario(&lista);
                printf("Publicaciones ordenadas por comentarios\n");
                break;
                
            case 10: // Ordenar por compartidos
                ordenarCompartidos(&lista);
                printf("Publicaciones ordenadas por compartidos\n");
                break;

            case 11: // Ordenar por ID
                ordenarPorID(&lista);
                printf("Publicaciones ordenadas por ID\n");
                break;
                
            case 0: // Salir
                printf("Saliendo...\n");
                break;
                
            default:
                printf("Opción no valida\n");
        }
    } while(opcion != 0);
    
    liberarLista(lista);
    return 0;
}