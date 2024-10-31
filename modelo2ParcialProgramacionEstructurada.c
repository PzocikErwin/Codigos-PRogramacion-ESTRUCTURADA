#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EMPLEADOS 5

// Estructura para almacenar datos de empleados
typedef struct {
    char nombre[50];
    char apellido[50];
    int dni;
    int diaNacimiento;
    int mesNacimiento;
    int anioIngreso;
    char cargo[50];
    float sueldo;
} Empleado;

// Prototipos de funciones
void cargarEmpleados(Empleado empleados[], int cantidad);
void actualizarBonificacion(Empleado empleados[], int cantidad, int mesActual, int *bonificados, float *totalBonificaciones);
void guardarArchivo(int bonificados, float totalBonificaciones);
void leerArchivo();

int main() {
    Empleado empleados[MAX_EMPLEADOS];
    int mesActual;
    int bonificados = 0;
    float totalBonificaciones = 0.0;

    // Cargar empleados
    cargarEmpleados(empleados, MAX_EMPLEADOS);

    // Obtener el mes actual
    printf("Ingrese el mes actual (1-12): ");
    scanf("%d", &mesActual);

    // Actualizar bonificaciones
    actualizarBonificacion(empleados, MAX_EMPLEADOS, mesActual, &bonificados, &totalBonificaciones);

    // Guardar en archivo
    guardarArchivo(bonificados, totalBonificaciones);

    // Leer y mostrar el archivo
    leerArchivo();

    return 0;
}

// Función para cargar datos de empleados
void cargarEmpleados(Empleado empleados[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("Ingrese el nombre del empleado %d: ", i + 1);
        scanf("%s", empleados[i].nombre);
        printf("Ingrese el apellido del empleado %d: ", i + 1);
        scanf("%s", empleados[i].apellido);
        printf("Ingrese el DNI del empleado %d: ", i + 1);
        scanf("%d", &empleados[i].dni);
        printf("Ingrese el día de nacimiento del empleado %d: ", i + 1);
        scanf("%d", &empleados[i].diaNacimiento);
        printf("Ingrese el mes de nacimiento del empleado %d: ", i + 1);
        scanf("%d", &empleados[i].mesNacimiento);
        printf("Ingrese el año de ingreso del empleado %d: ", i + 1);
        scanf("%d", &empleados[i].anioIngreso);
        printf("Ingrese el cargo del empleado %d: ", i + 1);
        scanf("%s", empleados[i].cargo);
        printf("Ingrese el sueldo del empleado %d: ", i + 1);
        scanf("%f", &empleados[i].sueldo);
        printf("\n");
    }
}

// Función para actualizar la bonificación de empleados que cumplen años en el mes actual
void actualizarBonificacion(Empleado empleados[], int cantidad, int mesActual, int *bonificados, float *totalBonificaciones) {
    time_t t = time(NULL);
    struct tm *fechaActual = localtime(&t);
    int anioActual = fechaActual->tm_year + 1900;

    for (int i = 0; i < cantidad; i++) {
        if (empleados[i].mesNacimiento == mesActual) {
            int antiguedad = anioActual - empleados[i].anioIngreso;
            float porcentajeBonificacion;

            if (antiguedad < 10)
                porcentajeBonificacion = 0.15;
            else if (antiguedad < 20)
                porcentajeBonificacion = 0.30;
            else
                porcentajeBonificacion = 0.50;

            float bonificacion = empleados[i].sueldo * porcentajeBonificacion;
            empleados[i].sueldo += bonificacion;

            (*bonificados)++;
            *totalBonificaciones += bonificacion;
        }
    }
}

// Función para guardar en un archivo la cantidad de empleados que recibieron bonificación y el total de bonificaciones
void guardarArchivo(int bonificados, float totalBonificaciones) {
    FILE *archivo = fopen("bonificaciones.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Empleados que recibieron bonificación: %d\n", bonificados);
    fprintf(archivo, "Total de bonificaciones abonadas: %.2f\n", totalBonificaciones);

    fclose(archivo);
}

// Función para leer y mostrar el contenido del archivo
void leerArchivo() {
    FILE *archivo = fopen("bonificaciones.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    fclose(archivo);
}