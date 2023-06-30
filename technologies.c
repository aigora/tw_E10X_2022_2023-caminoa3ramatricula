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
