#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "technologies.h"

void readCsvFileToTechnologiesArray(Technology techs[ROWS_NUMBER]) {
  FILE* csvFile = fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv", "r");
  if (csvFile == NULL) {
    perror("Error abriendo fichero generacion_por_tecnologias_21_22_puntos_simplificado.csv\n");
    exit(EXIT_FAILURE);
  }

  char headers[700];
  // saltar lineas de encabezado
  fgets(headers, sizeof(headers), csvFile);

  // procesa todas las lineas hasta el final del fichero
  int row = 0;
  while(!feof(csvFile)) {
    techs[row].years[0].yearNumber = 2021;
    techs[row].years[1].yearNumber = 2022;
    int month = 0;
    while (month < MONTHS_BY_YEAR) {
      techs[row].years[0].months[month].monthNumber = month + 1;
      techs[row].years[1].months[month].monthNumber = month + 1;
      month++;
    }

    fscanf(csvFile, "%80[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
      techs[row].name,
      &techs[row].years[0].months[0].dataValue,
      &techs[row].years[0].months[1].dataValue,
      &techs[row].years[0].months[2].dataValue,
      &techs[row].years[0].months[3].dataValue,
      &techs[row].years[0].months[4].dataValue,
      &techs[row].years[0].months[5].dataValue,
      &techs[row].years[0].months[6].dataValue,
      &techs[row].years[0].months[7].dataValue,
      &techs[row].years[0].months[8].dataValue,
      &techs[row].years[0].months[9].dataValue,
      &techs[row].years[0].months[10].dataValue,
      &techs[row].years[0].months[11].dataValue,
      &techs[row].years[1].months[0].dataValue,
      &techs[row].years[1].months[1].dataValue,
      &techs[row].years[1].months[2].dataValue,
      &techs[row].years[1].months[3].dataValue,
      &techs[row].years[1].months[4].dataValue,
      &techs[row].years[1].months[5].dataValue,
      &techs[row].years[1].months[6].dataValue,
      &techs[row].years[1].months[7].dataValue,
      &techs[row].years[1].months[8].dataValue,
      &techs[row].years[1].months[9].dataValue,
      &techs[row].years[1].months[10].dataValue,
      &techs[row].years[1].months[11].dataValue
    );

    row++;
  };

  fclose(csvFile);
}



void calculateStatisticsAndPrintToFile(Technology techs[ROWS_NUMBER], char* fileName) {
  FILE* outputFile = fopen(fileName, "w");
  if (outputFile == NULL) {
    perror("Error abriendo fichero de salida\n");
    exit(EXIT_FAILURE);
  }

  fprintf(outputFile, "Estadisticas por tecnologia:\n\n");

  for (int i = 0; i < ROWS_NUMBER; i++) {
    fprintf(outputFile, "Tecnologia: %s\n", techs[i].name);

    for (int j = 0; j < YEARS_NUMBER; j++) {
      fprintf(outputFile, "\tAnio %d:\n", techs[i].years[j].yearNumber);

      double data[MONTHS_BY_YEAR];

      // almacena los atos por año
      for (int k = 0; k < MONTHS_BY_YEAR; k++) {
        data[k] = techs[i].years[j].months[k].dataValue;
      }

      // calcula estdísticas por año
      int n = MONTHS_BY_YEAR;
      double sum = 0.0;
      double min = data[0];
      double max = data[0];

      for (int k = 0; k < n; k++) {
        sum += data[k];

        if (data[k] < min) {
          min = data[k];
        }

        if (data[k] > max) {
          max = data[k];
        }
      }

      double mean = sum / n;

      // clasifica los datos en orden ascendente
      for (int k = 0; k < n - 1; k++) {
        for (int l = 0; l < n - k - 1; l++) {
          if (data[l] > data[l + 1]) {
            double temp = data[l];
            data[l] = data[l + 1];
            data[l + 1] = temp;
          }
        }
      }

      double median;
      if (n % 2 == 0) {
        median = (data[n / 2 - 1] + data[n / 2]) / 2.0;
      } else {
        median = data[n / 2];
      }

      double total = sum;

      fprintf(outputFile, "\t\tMedia: %.2lf\n", mean);
      fprintf(outputFile, "\t\tMediana: %.2lf\n", median);
      fprintf(outputFile, "\t\tMinimo: %.2lf\n", min);
      fprintf(outputFile, "\t\tMaximo: %.2lf\n", max);
      fprintf(outputFile, "\t\tTotal: %.2lf\n", total);
      fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "\n");
  }

  fclose(outputFile);
  printf("Estadisticas por tecnologia volcadas al archivo %s\n", fileName);
}
