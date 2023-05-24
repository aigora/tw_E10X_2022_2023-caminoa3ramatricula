#include <stdio.h>
#define COLUMNAS 25
#define FILAS 17

int main(){
    float matriz[FILAS][COLUMNAS];
    FILE *pf;
    pf = fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv", "w");

    if (pf == NULL){
        printf("Error al abrir el fichero.\n");
        return -1;
    }
    else{
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                aux = fgtc(f);
                printf("%s\t", matriz[i][j]);
            }
        printf("\n");
        }

    }

    return 0;
}
