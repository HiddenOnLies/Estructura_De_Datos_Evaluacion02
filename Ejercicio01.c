#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_NOMBRE 100
#define PRIORIDADES 5
#ifdef _WIN32
  #include<windows.h>
#endif  

// Estructura para definir los datos del paciente
typedef struct Paciente
{
    char nombre[MAX_NOMBRE];
    int prioridad;
    struct Paciente* siguiente;
} Paciente;

// Definimos la cola
typedef struct Cola
{
    Paciente* frente;
    Paciente* final;
} Cola;

// Prototipos de funciones
void inicializar_Colas(Cola* colas);
void ingresar_Paciente(Cola* colas, char* nombre, int prioridad);
void atender_Paciente(Cola* colas);
void mostrar_Estado(Cola* colas);
void liberar_Colas(Cola* colas);
void procesar_Archivo(Cola* colas, const char* nombreArchivo);
bool cola_Vacia(Cola* cola);

// Funcion para inicializar las colas de prioridades C1, C2, C3, C4, C5
void inicializar_Colas(Cola* colas){
    for(int i = 0; i < PRIORIDADES; i++){
        colas[i].frente = NULL;
        colas[i].final = NULL;
    }
}

// Ingresamos el paciente considerando su nombre y la prioridad
void ingresar_Paciente(Cola* colas, char* nombre, int prioridad){
    int indice;
    if(prioridad < 1 || prioridad > 5){
        printf("Error: La prioridad debe ser entre 1(C1) y 5(C5)\n");
        return;
    }
    
    Paciente* nuevo = (Paciente*)malloc(sizeof(Paciente));
    if (nuevo == NULL){
        printf("Error: Memoria insuficiente\n");
        return;
    }
    
    strcpy(nuevo->nombre, nombre);
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;
    
    indice = prioridad - 1;
    Cola* cola = &colas[indice];
    
    if (cola_Vacia(cola)){
        cola->frente = nuevo;
        cola->final = nuevo;
    }
    else{
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }

    printf("Paciente %s agregado a cola C%d\n", nombre, prioridad);
}

void atender_Paciente(Cola* colas){
    Paciente* paciente = NULL;
    int prioridad = -1;
    for (int i = 0; i < PRIORIDADES; i++) {
        if (!cola_Vacia(&colas[i])) {
            paciente = colas[i].frente;
            prioridad = i + 1;
            colas[i].frente = colas[i].frente->siguiente;

            if (colas[i].frente == NULL) {
                colas[i].final = NULL;
            }
            break;
        }
    }
    if (paciente == NULL) {
        printf("No hay pacientes en espera\n");
    } else {
        printf("Atendiendo a %s (Prioridad C%d)\n", paciente->nombre, prioridad);
        free(paciente);
    }
}

void mostrar_Estado(Cola* colas){
    printf("\nEstado de las colas:\n");
    printf("--------------------\n");
    for (int i = 0; i < PRIORIDADES; i++) {
        printf("Cola C%d: ", i+1);
        if (cola_Vacia(&colas[i])) {
            printf("Vacia\n");
        } else {
            Paciente* actual = colas[i].frente;
            while (actual != NULL) {
                printf("%s", actual->nombre);
                if (actual->siguiente != NULL) {
                    printf(" -> ");
                }
                actual = actual->siguiente;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void liberar_Colas(Cola* colas){
    for(int i = 0; i < PRIORIDADES; i++){
        while (!cola_Vacia(&colas[i]))
        {
            Paciente* temp = colas[i].frente;
            colas[i].frente = colas[i].frente->siguiente;
            free(temp);
        }
    }
}

void procesar_Archivo(Cola* colas, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char linea[256];
    while(fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = '\0';

        if (strncmp(linea, "AGREGAR", 7) == 0) {
            char nombre[MAX_NOMBRE];
            char* token = strtok(linea, ";");
            if(token == NULL) continue;

            token = strtok(NULL, ";"); // Nombre
            if(token == NULL) continue;
            strncpy(nombre, token, MAX_NOMBRE-1);
            nombre[MAX_NOMBRE-1] = '\0';

            // Ignorar edad y RUT
            strtok(NULL, ";");
            strtok(NULL, ";");

            token = strtok(NULL, ";"); // Prioridad
            if(token == NULL) continue;

            int prioridad = atoi(token + 1); // Saltar el 'C'
            ingresar_Paciente(colas, nombre, prioridad);
        } 
        else if (strcmp(linea, "VER") == 0) {
            mostrar_Estado(colas);
        }
    }
    fclose(archivo);
}

bool cola_Vacia(Cola* cola){
    return cola->frente == NULL;
}

void mostrarMenu() {
    printf("\nSistema de Atencion de Urgencias\n");
    printf("1. Agregar paciente\n");
    printf("2. Atender paciente\n");
    printf("3. Mostrar colas\n");
    printf("4. Cargar archivo\n");
    printf("5. Salir\n");
    printf("Seleccione opcion: ");
}

int main(){
    Cola colas[PRIORIDADES];
    inicializar_Colas(colas);

    int opcion;
    char nombre[MAX_NOMBRE];
    int prioridad;
    char nombreArchivo[100];

    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        // Limpiar el buffer de entrada después de scanf
        while(getchar() != '\n');

        switch (opcion) {
            case 1:
                printf("Nombre del paciente: ");
                scanf("%99[^\n]", nombre); // Lee hasta 99 caracteres o un newline
                while(getchar() != '\n'); // Limpiar buffer
                
                printf("Prioridad (1-5, donde 1 es C1 y 5 es C5): ");
                scanf("%d", &prioridad);
                while(getchar() != '\n'); // Limpiar buffer
                
                ingresar_Paciente(colas, nombre, prioridad);
                break;

            case 2:
                atender_Paciente(colas);
                break;

            case 3:
                mostrar_Estado(colas);
                break;

            case 4:
                printf("Nombre del archivo: ");
                scanf("%99s", nombreArchivo);
                while(getchar() != '\n'); // Limpiar buffer
                
                procesar_Archivo(colas, nombreArchivo);
                break;

            case 5:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opción inválida\n");
                while(getchar() != '\n'); // Limpiar buffer
        }
    } while (opcion != 5);

    liberar_Colas(colas);
    return 0;
}