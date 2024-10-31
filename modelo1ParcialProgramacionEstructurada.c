#include <stdio.h>
#include <string.h>

// Definición de la estructura para almacenar los datos de los candidatos
typedef struct {
    char nombre[50];
    char apellido[50];
    int edad;
    int distancia;
    char nivel_estudio;
    char experiencia;
    int calificacion;
} Candidato;

// Declaración de funciones
int calcular_calificacion(Candidato *c);
void guardar_candidato_ganador(Candidato *c);

int main() {
    Candidato candidatos[3];
    int i, max_calificacion = 0;
    Candidato *ganador = NULL; // Puntero para almacenar el candidato ganador
    
    // Ingreso de los datos de los candidatos
    for (i = 0; i < 3; i++) {
        printf("Ingrese el nombre del candidato %d: ", i + 1);
        scanf("%s", candidatos[i].nombre);
        printf("Ingrese el apellido del candidato %d: ", i + 1);
        scanf("%s", candidatos[i].apellido);
        printf("Ingrese la edad del candidato %d (18-65): ", i + 1);
        scanf("%d", &candidatos[i].edad);
        printf("Ingrese la distancia del domicilio a la empresa del candidato %d (0-100 km): ", i + 1);
        scanf("%d", &candidatos[i].distancia);
        printf("Ingrese el nivel de estudio del candidato %d (s: Secundario, t: Terciario, u: Universitario): ", i + 1);
        scanf(" %c", &candidatos[i].nivel_estudio);
        printf("¿Tiene experiencia en un cargo similar? (s/n): ");
        scanf(" %c", &candidatos[i].experiencia);
        
        // Calcular la calificación del candidato
        candidatos[i].calificacion = calcular_calificacion(&candidatos[i]);
        printf("Calificación del candidato %d: %d\n", i + 1, candidatos[i].calificacion);
        
        // Verificar si el candidato actual tiene la mayor calificación
        if (candidatos[i].calificacion > max_calificacion) {
            max_calificacion = candidatos[i].calificacion;
            ganador = &candidatos[i];
        }
    }

    // Guardar y mostrar el candidato ganador
    if (ganador != NULL) {
        guardar_candidato_ganador(ganador);
    } else {
        printf("No se encontró un candidato ganador.\n");
    }

    return 0;
}

// Función para calcular la calificación del candidato
int calcular_calificacion(Candidato *c) {
    int calificacion = 0;

    // Calificación por edad
    if (c->edad >= 18 && c->edad <= 25) calificacion += 2;
    else if (c->edad >= 26 && c->edad <= 35) calificacion += 3;
    else if (c->edad >= 36 && c->edad <= 55) calificacion += 5;

    // Calificación por distancia
    if (c->distancia < 20) calificacion += 5;
    else if (c->distancia <= 50) calificacion += 3;
    else calificacion += 2;

    // Calificación por nivel de estudio
    if (c->nivel_estudio == 's') calificacion += 1;
    else if (c->nivel_estudio == 't') calificacion += 3;
    else if (c->nivel_estudio == 'u') calificacion += 6;

    // Calificación por experiencia
    if (c->experiencia == 's') calificacion += 5;

    return calificacion;
}

// Función para guardar el nombre y apellido del candidato ganador en un archivo
void guardar_candidato_ganador(Candidato *c) {
    FILE *archivo = fopen("jefe_it.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Nombre: %s\nApellido: %s\n", c->nombre, c->apellido);
    fclose(archivo);

    printf("El candidato ganador es: %s %s\n", c->nombre, c->apellido);
}