#include <stdio.h>

#define DIAS_SEMANA 5
#define NUM_VEHICULOS 3

typedef struct {
    char marca[20];
    char modelo[20];
    char patente[10];
    int kilometraje_actual;
    int kilometros_semanales[DIAS_SEMANA];
    int total_km_semana;
} Vehiculo;

void calcular_total_km_y_plata(Vehiculo *vehiculo, int *plata_generada) {
    // Desreferenciamos el puntero vehiculo para acceder a sus miembros
    Vehiculo temp = *vehiculo; // Creamos una copia de la estructura

    temp.total_km_semana = 0; // Usamos el operador . para acceder a total_km_semana
    for (int i = 0; i < DIAS_SEMANA; i++) {
        temp.total_km_semana += temp.kilometros_semanales[i]; // Accedemos usando .
    }
    *plata_generada = temp.total_km_semana * 1000; // $1000 por km
}

int main() {
    Vehiculo [NUM_VEHICULOS];

    // Ingreso de datos de los vehículos
    for (int i = 0; i < NUM_VEHICULOS; i++) {
        printf("Ingrese los datos del vehiculo %d:\n", i + 1);
        printf("Marca: ");
        scanf("%s", flota[i].marca);
        printf("Modelo: ");
        scanf("%s", flota[i].modelo);
        printf("Patente sin espacios: ");
        scanf("%s", flota[i].patente);
        printf("Kilometraje actual: ");
        scanf("%d", &flota[i].kilometraje_actual);
        
        // Ingreso de kilómetros recorridos por día
        for (int j = 0; j < DIAS_SEMANA; j++) {
            printf("Kilometros realizados el dia %d: ", j + 1);
            scanf("%d", &flota[i].kilometros_semanales[j]);
        }
    }

    int plata_generada[NUM_VEHICULOS];
    int total_general = 0;

    // Creación y escritura en el archivo
    FILE *archivo = fopen("reporte.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo crear el archivo.\n");
        return 1;
    }

    for (int i = 0; i < NUM_VEHICULOS; i++) {
        calcular_total_km_y_plata(&flota[i], &plata_generada[i]);
        total_general += plata_generada[i];
        fprintf(archivo, "Patente: %s - Total generado: $%d\n", flota[i].patente, plata_generada[i]);
    }

    fprintf(archivo, "Total general: $%d\n", total_general);
    fclose(archivo);

    // Lectura y visualización del archivo
    archivo = fopen("reporte.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo leer el archivo.\n");
        return 1;
    }

    char c;
    while ((c = fgetc(archivo)) != EOF) {
        putchar(c);
    }

    fclose(archivo);
    return 0;
}