#include <stdio.h>

int main() {
    int opcion;
  printf("Bienvenido! si quiere saber mas acerca de la forma de generacion de energia electrica en Espanha:.\n");
   do {

        printf("Elige una opcion:\n\n");
        printf("1. Busqueda de datos\n");
        printf("2. Ordenar\n");
        printf("3. Graficas\n");
        printf("4. Prediccion\n");
        printf("5. Salir\n");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Seleccionaste la Opci�n busqueda de datos.\n");
                // L�gica de la Opci�n 1


                break;
            case 2:
                printf("Seleccionaste la Opcion ordenar.\n");
                // L�gica de la Opci�n 2

                break;
            case 3:
                printf("Seleccionaste la Opcion gr�ficas.\n");
                // L�gica de la Opci�n 3

                break;
            case 4:
                printf("Seleccionaste la Opcion predicciones a futuro.\n");
                // L�gica de la Opci�n 3

                break;
            case 5:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion invalida. Por favor, elige nuevamente.\n");
        }
    }
    while (opcion!=5);

    return 0;
}

