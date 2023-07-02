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

void searchAndPrintToFileTechnologyData(Technology techs[ROWS_NUMBER], char* technologyName, char* fileName) {
  FILE* outputFile = fopen(fileName, "w");
  if (outputFile == NULL) {
    perror("Error abriendo fichero de salida\n");
    exit(EXIT_FAILURE);
  }

  fprintf(outputFile, "Resultado para la busqueda %s\n", technologyName);

  int found = -1;
  for (int i = 0; i < ROWS_NUMBER && found == -1; i++) {
    if (strcasecmp(techs[i].name, technologyName) == 0) {
      fprintf(outputFile, "Tecnologia: %s\n", techs[i].name);
      for (int j = 0; j < YEARS_NUMBER; j++) {
        fprintf(outputFile, "\tAnio %d:\n", techs[i].years[j].yearNumber);
        for (int k = 0; k < MONTHS_BY_YEAR; k++) {
          fprintf(outputFile,
            "\t\tMes %d: %.2lf\n",
            techs[i].years[j].months[k].monthNumber,
            techs[i].years[j].months[k].dataValue
          );
        }
      }

      found = i;
    }
  }

  if (found == -1) {
    fprintf(outputFile, "Tecnologia no encontrada\n");
  }

  fclose(outputFile);
  printf("Resultados de la busqueda %s, volcados al fichero resultado_busqueda.txt\n", technologyName);
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

void graphicsAndPrintToFile(Technology techs[ROWS_NUMBER], char* fileName) {
  FILE* outputFile = fopen(fileName, "w");
  if (outputFile == NULL) {
    perror("Error abriendo fichero de salida\n");
    exit(EXIT_FAILURE);
  }

  fprintf(outputFile, "Graficos por tecnologia y anio:\n\n");

  int maxAsterisks = 45;

  // buscamos el valor máximo para realizar los gráficos
  double max2021 = 0;
  // -1 para eliminar "Generacion Total"
  for (int i = 0; i < ROWS_NUMBER - 1; i++) {
    for (int j = 0; j < MONTHS_BY_YEAR; j++) {
      if (techs[i].years[0].months[j].dataValue > max2021) {
        max2021 = techs[i].years[0].months[j].dataValue;
      }
    }
  }
  double max2022 = 0;
  for (int i = 0; i < ROWS_NUMBER; i++) {
    for (int j = 0; j < MONTHS_BY_YEAR; j++) {
      if (techs[i].years[1].months[j].dataValue > max2022) {
        max2022 = techs[i].years[1].months[j].dataValue;
      }
    }
  }

  // diseñamos los graficas con el valor máximo
  fprintf(outputFile, "\nAnio 2021\n\n");
  for (int i = 0; i < ROWS_NUMBER; i++) {
    fprintf(outputFile, "%s\n", techs[i].name);
    for (int j = 0; j < MONTHS_BY_YEAR; j++) {
      fprintf(outputFile, "\tMes");
      if (j < 9) {
        fprintf(outputFile, " 0%d: ", j+1);
      }
      else {
        fprintf(outputFile, " %d: ", j+1);
      }

      int asteriskNumber = (int) ((maxAsterisks * techs[i].years[0].months[j].dataValue) / max2021);

      for (int k = 0; k < asteriskNumber; k++) {
        fprintf(outputFile, "*");
      }

      fprintf(outputFile, " %lf\n", techs[i].years[0].months[j].dataValue);
    }
  }

  fprintf(outputFile, "\n\n\n\n\nAnio 2022\n\n");
  for (int i = 0; i < ROWS_NUMBER; i++) {
    fprintf(outputFile, "%s\n", techs[i].name);
    for (int j = 0; j < MONTHS_BY_YEAR; j++) {
      fprintf(outputFile, "\tMes");
      if (j < 9) {
        fprintf(outputFile, " 0%d: ", j+1);
      }
      else {
        fprintf(outputFile, " %d: ", j+1);
      }

      int asteriskNumber = (int) ((maxAsterisks * techs[i].years[0].months[j].dataValue) / max2022);

      for (int k = 0; k < asteriskNumber; k++) {
        fprintf(outputFile, "*");
      }

      fprintf(outputFile, " %lf\n", techs[i].years[1].months[j].dataValue);
    }
  }

  fclose(outputFile);
  printf("Graficos por tecnologia y anio volcadas al archivo %s\n", fileName);
}





