#include <stdio.h>
#include <string.h>

// Definimos la estructura para representar un ejemplar
typedef struct {
    char isbn[20];
    char titulo[100];
    char nombreAutor[50];
    char apellidoAutor[50];
    char editorial[50];
    char clase[10]; // "libro" o "revista"
    int numeroEdicion; // Solo para libros
    int anioPublicacion; // Solo para libros
    char nombreRevista[50]; // Solo para revistas
} Ejemplar;

#define MAX_EJEMPLARES 100

// Función para cargar los datos de los ejemplares
void cargarEjemplares(Ejemplar ejemplares[], int *numEjemplares) {
    printf("¿Cuántos ejemplares quieres cargar? ");
    scanf("%d", numEjemplares);
    getchar(); // Limpiar el buffer de entrada

    for (int i = 0; i < *numEjemplares; i++) {
        printf("\nEjemplar %d:\n", i + 1);

        printf("ISBN: ");
        fgets(ejemplares[i].isbn, sizeof(ejemplares[i].isbn), stdin);
        ejemplares[i].isbn[strcspn(ejemplares[i].isbn, "\n")] = '\0';

        printf("Título: ");
        fgets(ejemplares[i].titulo, sizeof(ejemplares[i].titulo), stdin);
        ejemplares[i].titulo[strcspn(ejemplares[i].titulo, "\n")] = '\0';

        printf("Nombre del autor: ");
        fgets(ejemplares[i].nombreAutor, sizeof(ejemplares[i].nombreAutor), stdin);
        ejemplares[i].nombreAutor[strcspn(ejemplares[i].nombreAutor, "\n")] = '\0';

        printf("Apellido del autor: ");
        fgets(ejemplares[i].apellidoAutor, sizeof(ejemplares[i].apellidoAutor), stdin);
        ejemplares[i].apellidoAutor[strcspn(ejemplares[i].apellidoAutor, "\n")] = '\0';

        printf("Editorial: ");
        fgets(ejemplares[i].editorial, sizeof(ejemplares[i].editorial), stdin);
        ejemplares[i].editorial[strcspn(ejemplares[i].editorial, "\n")] = '\0';

        printf("Clase de publicación (libro o revista): ");
        fgets(ejemplares[i].clase, sizeof(ejemplares[i].clase), stdin);
        ejemplares[i].clase[strcspn(ejemplares[i].clase, "\n")] = '\0';

        // Si es un libro, pedimos número de edición y año de publicación
        if (strcmp(ejemplares[i].clase, "libro") == 0) {
            printf("Número de edición: ");
            scanf("%d", &ejemplares[i].numeroEdicion);
            printf("Año de publicación: ");
            scanf("%d", &ejemplares[i].anioPublicacion);
            getchar(); // Limpiar el buffer de entrada
        }
        // Si es una revista, pedimos el nombre de la revista
        else if (strcmp(ejemplares[i].clase, "revista") == 0) {
            printf("Nombre de la revista: ");
            fgets(ejemplares[i].nombreRevista, sizeof(ejemplares[i].nombreRevista), stdin);
            ejemplares[i].nombreRevista[strcspn(ejemplares[i].nombreRevista, "\n")] = '\0';
        }
    }
}

// Función para buscar libros de un autor específico y guardar resultados en un archivo
void buscarPorAutor(Ejemplar ejemplares[], int numEjemplares, const char *apellidoAutor) {
    // Abrimos el archivo para guardar los resultados de búsqueda
    FILE *archivo = fopen("libros_autor.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    int encontrados = 0; // Contador de libros encontrados
    for (int i = 0; i < numEjemplares; i++) {
        // Verificamos si el ejemplar es un libro y coincide con el autor
        if (strcmp(ejemplares[i].apellidoAutor, apellidoAutor) == 0 && strcmp(ejemplares[i].clase, "libro") == 0) {
            // Mostramos y guardamos el título y año de publicación
            printf("Título: %s, Año de publicación: %d\n", ejemplares[i].titulo, ejemplares[i].anioPublicacion);
            fprintf(archivo, "Título: %s, Año de publicación: %d\n", ejemplares[i].titulo, ejemplares[i].anioPublicacion);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron libros del autor %s.\n", apellidoAutor);
    } else {
        printf("Resultados guardados en 'libros_autor.txt'.\n");
    }

    fclose(archivo); // Cerramos el archivo
}

int main() {
    Ejemplar ejemplares[MAX_EJEMPLARES];
    int numEjemplares = 0;

    // Cargar ejemplares
    cargarEjemplares(ejemplares, &numEjemplares);

    // Buscar libros de un autor específico
    char apellidoAutor[50];
    printf("Ingrese el apellido del autor a buscar: ");
    fgets(apellidoAutor, sizeof(apellidoAutor), stdin);
    apellidoAutor[strcspn(apellidoAutor, "\n")] = '\0';

    buscarPorAutor(ejemplares, numEjemplares, apellidoAutor);

    return 0;
}