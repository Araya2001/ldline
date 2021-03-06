#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libldline.h"

#define CHAR_MAX 1000

struct linebuffer {
  char *pres; /*Primer Resultado, pres*/
  char *rpas; /*Resultado Pasado, rpas*/
  char *subpres;
  char *subrpas;
  char *subcline; /*Current Line; Línea actual (Substring)*/
};

/*
 * TODO: Check why do the strncpy and getsubstr substrings aren't equal
 * when compared with strcmp
 */
void getsubstr(char *str, char *replace, size_t charpos, size_t charsize) {
  for (int i = charpos; i < charsize; ++i) {
    replace[i] = str[i];
  }
}

void readlineerased(const char *filename, int optfrom, int optto) {
  FILE *file;
  ssize_t read;
  size_t len = 0;
  int i = 0;
  char *line = NULL;
  struct linebuffer *lbp = malloc(sizeof(struct linebuffer));
  file = fopen(filename, "r");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }
  if (lbp == NULL) {
    exit(EXIT_FAILURE);
  }
  if (optfrom != 0 && optto != 0) {
    while ((read = getline(&line, &len, file) != -1)) {
      lbp[0].subcline = malloc(CHAR_MAX * sizeof(char));
      getsubstr(line, lbp[0].subcline, optfrom - 1, optto);
      switch (i) {
      case 0:
        lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subrpas = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].rpas, line);
        getsubstr(lbp[0].rpas, lbp[0].subrpas, optfrom - 1, optto);
        break;
      case 1:
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subpres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, lbp[0].rpas);
        getsubstr(lbp[0].pres, lbp[0].subpres, optfrom - 1, optto);
        free(lbp[0].rpas);
        free(lbp[0].subrpas);
        lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subrpas = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].rpas, line);
        getsubstr(lbp[0].rpas, lbp[0].subrpas, optfrom - 1, optto);
        break;
      default:
        if (strcmp(lbp[0].subpres, lbp[0].subrpas) == 0) {
          printf("%s", lbp[0].pres);
        }
        free(lbp[0].pres);
        free(lbp[0].subpres);
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subpres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, lbp[0].rpas);
        getsubstr(lbp[0].pres, lbp[0].subpres, optfrom - 1, optto);
        free(lbp[0].rpas);
        free(lbp[0].subrpas);
        lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subrpas = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].rpas, line);
        getsubstr(lbp[0].rpas, lbp[0].subrpas, optfrom - 1, optto);
      }
      free(lbp[0].subcline);
      ++i;
    }
  } else {
    while ((read = getline(&line, &len, file) != -1)) {
      switch (i) {
      case 0:
        lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].rpas, line);
        break;
      case 1:
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, lbp[0].rpas);
        free(lbp[0].rpas);
        lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].rpas, line);
        break;
      default:
        if (strcmp(lbp[0].pres, lbp[0].rpas) == 0) {
          printf("%s", lbp[0].pres);
        }
        free(lbp[0].pres);
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, lbp[0].rpas);
        free(lbp[0].rpas);
        lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].rpas, line);
      }
      free(lbp[0].subcline);
      ++i;
    }
  }

  printf("%s\n", lbp->pres);
  fclose(file);
  if (line) {
    free(line);
  }
  free(lbp[0].pres);
  free(lbp[0].rpas);
  free(lbp[0].subpres);
  free(lbp[0].subrpas);
  free(lbp);
  exit(EXIT_SUCCESS);
}

void readlinesaved(const char *filename, int optfrom, int optto) {
  FILE *file;
  ssize_t read;
  size_t len = 0;
  int i = 0;
  char *line = NULL;
  struct linebuffer *lbp = malloc(sizeof(struct linebuffer));
  file = fopen(filename, "r");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }
  if (lbp == NULL) {
    exit(EXIT_FAILURE);
  }
  if (optfrom != 0 && optto != 0) {
    while ((read = getline(&line, &len, file) != -1)) {
      lbp[0].subcline = malloc(CHAR_MAX * sizeof(char));
      getsubstr(line, lbp[0].subcline, optfrom - 1, optto);
      if (i == 0) {
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subpres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, line);
        getsubstr(lbp[0].pres, lbp[0].subpres, optfrom - 1, optto);
      }
      switch (i) {
      case 0:
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        lbp[0].subpres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, line);
        getsubstr(lbp[0].pres, lbp[0].subpres, optfrom - 1, optto);
        break;
      default:
        if (strcmp(lbp[0].subpres, lbp->subcline) != 0) {
          printf("%s", lbp[0].rpas);
          free(lbp[0].pres);
          free(lbp[0].rpas);
          free(lbp[0].subpres);
          lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
          lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
          lbp[0].subpres = malloc(CHAR_MAX * sizeof(char));
          strcpy(lbp[0].pres, line);
          strcpy(lbp[0].rpas, line);
          getsubstr(lbp[0].pres, lbp[0].subpres, optfrom - 1, optto);
        } else {
          if (lbp[0].rpas) {
            free(lbp[0].rpas);
          }
          lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
          strcpy(lbp[0].rpas, line);
        }
        break;
      }
      ++i;
      free(lbp[0].subcline);
    }
  } else {
    while ((read = getline(&line, &len, file) != -1)) {
      switch (i) {
      case 0:
        lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
        strcpy(lbp[0].pres, line);
        break;
      default:
        if (strcmp(lbp[0].pres, line) != 0) {
          printf("%s", lbp[0].rpas);
          free(lbp[0].pres);
          free(lbp[0].rpas);
          lbp[0].pres = malloc(CHAR_MAX * sizeof(char));
          lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
          strcpy(lbp[0].pres, line);
          strcpy(lbp[0].rpas, line);
        } else {
          if (lbp[0].rpas) {
            free(lbp[0].rpas);
          }
          lbp[0].rpas = malloc(CHAR_MAX * sizeof(char));
          strcpy(lbp[0].rpas, line);
        }
        break;
      }
      ++i;
    }
  }
  printf("%s\n", lbp[0].rpas);
  fclose(file);
  if (line) {
    free(line);
  }
  free(lbp[0].pres);
  free(lbp[0].rpas);
  free(lbp[0].subpres);
  free(lbp[0].subrpas);
  free(lbp);
  exit(EXIT_SUCCESS);
}