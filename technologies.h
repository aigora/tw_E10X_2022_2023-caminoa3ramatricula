#define MAX_TECHNOLOGY_NAME_LENGTH 80
#define YEARS_NUMBER 2
#define MONTHS_BY_YEAR 12
#define ROWS_NUMBER 17
#define OPTION_EXIT_NUMBER 4

typedef struct {
  int monthNumber;
  double dataValue;
} Month;

typedef struct {
  int yearNumber;
  Month months[MONTHS_BY_YEAR];
} Year;

typedef struct {
  char name[MAX_TECHNOLOGY_NAME_LENGTH];
  Year years[YEARS_NUMBER];
} Technology;

void readCsvFileToTechnologiesArray(Technology techs[ROWS_NUMBER]);
void searchAndPrintToFileTechnologyData(Technology techs[ROWS_NUMBER], char* technologyName, char* fileName);
void calculateStatisticsAndPrintToFile(Technology techs[ROWS_NUMBER], char* fileName);
void graphicsAndPrintToFile(Technology techs[ROWS_NUMBER], char* fileName);


