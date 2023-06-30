#define MAX_TECHNOLOGY_NAME_LENGTH 80
#define YEARS_NUMBER 2
#define ROWS_NUMBER 17


typedef struct {
  char name[MAX_TECHNOLOGY_NAME_LENGTH];
  Year years[YEARS_NUMBER];
} Technology;

void readCsvFileToTechnologiesArray(Technology techs[ROWS_NUMBER]);


