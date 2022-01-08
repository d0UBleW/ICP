#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "var.h"
#include "info.h"
#include "file2struct.h"

void vacSpacing(int *width, record *rec, int line) {
    int maxName = strlen("Name");
    int maxCode = strlen("Code");
    int maxCountry = strlen("Country");
    int maxDosage = strlen("Dosage");
    int maxPopulation = strlen("Population (%)");
    int maxQty = strlen("Quantity");
    for (int i = 0; i < line; i++) {
        if (strlen((rec+i)->name) > maxName)
            maxName = strlen((rec+i)->name);

        if (strlen((rec+i)->code) > maxCode)
            maxCode = strlen((rec+i)->code);

        if (strlen((rec+i)->country) > maxCountry)
            maxCountry = strlen((rec+i)->country);

        if (digit((rec+i)->dosage) > maxDosage)
            maxDosage = digit((rec+i)->dosage);

        if (digit((int)(rec+i)->population)+2 > maxPopulation)
            maxPopulation = digit((int)(rec+i)->population)+2;

        if (digit((rec+i)->qty) > maxQty)
            maxQty = digit((rec+i)->qty);
    }


    if (digit(line) < 2) {
        *width = 2;
    }
    else
        *width = digit(line);

    *(width+1) = maxName;
    *(width+2) = maxCode;
    *(width+3) = maxCountry;
    *(width+4) = maxDosage;
    *(width+5) = maxPopulation;
    *(width+6) = maxQty;

}

void vacAttr(char **attr) {
    *(attr) = (char *)malloc((strlen("No")+1) * sizeof(char));
    strcpy(*(attr+0), "No");
    *(attr+1) = (char *)malloc((strlen("Name")+1) * sizeof(char));
    strcpy(*(attr+1), "Name");
    *(attr+2) = (char *)malloc((strlen("Code")+1) * sizeof(char));
    strcpy(*(attr+2), "Code");
    *(attr+3) = (char *)malloc((strlen("Country")+1) * sizeof(char));
    strcpy(*(attr+3), "Country");
    *(attr+4) = (char *)malloc((strlen("Dosage")+1) * sizeof(char));
    strcpy(*(attr+4), "Dosage");
    *(attr+5) = (char *)malloc((strlen("Population (%)")+1) * sizeof(char));
    strcpy(*(attr+5), "Population (%)");
    *(attr+6) = (char *)malloc((strlen("Quantity")+1) * sizeof(char));
    strcpy(*(attr+6), "Quantity");
}

void vacTable(int col, int row, record *content) {
    int *width = malloc((col) * sizeof *width);
    vacSpacing(width, content, row);

    char **attr = (char **)malloc((col) * sizeof (char *));
    vacAttr(attr);

    int *ptr;
    int tempCol;
    record *ind = content;

    for (int j = 0; j < row+4; j++) {
        ptr = width;
        tempCol = col;

        if (j == 0 || j == 2 || j == row+3) {
            for (int i = 0; tempCol > 0; i++) {
                if (i == (*ptr + 2 + 1) || i == 0) {
                    printf("+");
                    if (i != 0) {
                        ptr++;
                        tempCol--;
                    }
                    i = 0;
                }
                else printf("-");
            }
        }
        else {
            for (int i = 0; tempCol > 0; i++) {
                if (i == (*ptr + 2 + 1) || i == 0) {
                    printf("|");
                    if (i != 0) {
                        ptr++;
                        tempCol--;
                    }
                    i = 0;
                }
                else {
                    if (i == 1)
                        printf(" ");
                    else {
                        if (j == 1) {
                            printf("%s", *(attr+col-tempCol));
                            for (int k = 0; k < (*ptr - strlen(*(attr+col-tempCol))+1); k++)
                                printf(" ");
                        }
                        else {
                            if (col - tempCol == 1) {
                                printf("%s", ind->name);
                                for (int k = 0; k < (*ptr - strlen(ind->name)+1); k++)
                                    printf(" ");
                            }
                            else if (col - tempCol == 2) {
                                printf("%s", ind->code);
                                for (int k = 0; k < (*ptr - strlen(ind->code)+1); k++)
                                    printf(" ");
                            }
                            else if (col - tempCol == 3) {
                                printf("%s", ind->country);
                                for (int k = 0; k < (*ptr - strlen(ind->country)+1); k++)
                                    printf(" ");
                            }
                            else if (col - tempCol == 4) {
                                for (int k = 0; k < (*ptr - digit(ind->dosage)); k++)
                                    printf(" ");
                                printf("%d ", ind->dosage);
                            }
                            else if (col - tempCol == 5) {
                                for (int k = 0; k < (*ptr - digit((int)ind->population)-2); k++)
                                    printf(" ");
                                printf("%.1f ", ind->population);
                            }
                            else if (col - tempCol == 6) {
                                for (int k = 0; k < (*ptr - digit(ind->qty)); k++)
                                    printf(" ");
                                printf("%lld ", ind->qty);
                            }
                            else {
                                for (int k = 0; k < (*ptr - digit(j-2)); k++)
                                    printf(" ");
                                printf("%d ", (j-2));
                            }
                        }
                        i += *ptr;
                    }
                }
            }
            if (j != 1) ind++;
        }
        printf("\n");
    }
    for (int i = 0; i < (col); i++) {
        free(*(attr+i));
    }
    free(attr);
    free(width);
}

void distSpacing(int *width, distRec *dist, int line) {
    int maxName = strlen("Name");
    int maxCode = strlen("Code");
    int maxCountry = strlen("Country");
    int maxDist = strlen("Distributed");
    int vacLine = countLine("data/vaccine.txt");
    record *vaccine = (record *)malloc(vacLine * sizeof(record));
    vacToStruct(vaccine);

    for (int i = 0; i < line; i++) {
        for (int j = 0; j < vacLine; j++) {
            if (strcmp((vaccine+j)->code, (dist+i)->code) == 0) {
                if (strlen((vaccine+j)->name) > maxName)
                    maxName = strlen((vaccine+j)->name);

                if (strlen((vaccine+j)->code) > maxCode)
                    maxCode = strlen((vaccine+j)->code);

                if (strlen((vaccine+j)->country) > maxCountry)
                    maxCountry = strlen((vaccine+j)->country);

                break;
            }
        }
        if (digit((dist+i)->qty) > maxDist)
            maxDist = digit((dist+i)->qty);
    }

    if (digit(line) < 2) {
        *width = 2;
    }
    else
        *width = digit(line);

    *(width+1) = maxName;
    *(width+2) = maxCode;
    *(width+3) = maxCountry;
    *(width+4) = maxDist;

    free(vaccine);
}

void distAttr(char **attr) {
    *(attr) = (char *)malloc((strlen("No")+1) * sizeof(char));
    strcpy(*(attr+0), "No");
    *(attr+1) = (char *)malloc((strlen("Name")+1) * sizeof(char));
    strcpy(*(attr+1), "Name");
    *(attr+2) = (char *)malloc((strlen("Code")+1) * sizeof(char));
    strcpy(*(attr+2), "Code");
    *(attr+3) = (char *)malloc((strlen("Country")+1) * sizeof(char));
    strcpy(*(attr+3), "Country");
    *(attr+4) = (char *)malloc((strlen("Distributed")+1) * sizeof(char));
    strcpy(*(attr+4), "Distributed");
}

void distTable(int col, int row, distRec *content) {
    int *width = (int *)malloc(col * sizeof(int));
    distSpacing(width, content, row);

    char **attr = (char **)malloc(col * sizeof(char *));
    distAttr(attr);

    int *ptr;
    int tempCol;
    distRec *ind = content;
    int vacLine = countLine("data/vaccine.txt");
    record *vaccine = (record *)malloc(vacLine * sizeof(record));
    vacToStruct(vaccine);

    for (int j = 0; j < row+4; j++) {
        ptr = width;
        tempCol = col;

        if (j == 0 || j == 2 || j == row+3) {
            for (int i = 0; tempCol > 0; i++) {
                if (i == (*ptr + 2 + 1) || i == 0) {
                    printf("+");
                    if (i != 0) {
                        ptr++;
                        tempCol--;
                    }
                    i = 0;
                }
                else printf("-");
            }
        }
        else {
            for (int i = 0; tempCol > 0; i++) {
                if (i == (*ptr + 2 + 1) || i == 0) {
                    printf("|");
                    if (i != 0) {
                        ptr++;
                        tempCol--;
                    }
                    i = 0;
                }
                else {
                    if (i == 1)
                        printf(" ");
                    else {
                        if (j == 1) {
                            printf("%s", *(attr+col-tempCol));
                            for (int k = 0; k < (*ptr - strlen(*(attr+col-tempCol))+1); k++)
                                printf(" ");
                        }
                        else {
                            if (col - tempCol == 1) {
                                for (int l = 0; l < vacLine; l++) {
                                    if (strcmp((vaccine+l)->code, ind->code) == 0) {
                                        printf("%s", (vaccine+l)->name);
                                        for (int k = 0; k < (*ptr - strlen((vaccine+l)->name)+1); k++)
                                            printf(" ");
                                        break;
                                    }
                                }
                            }
                            else if (col - tempCol == 2) {
                                printf("%s", ind->code);
                                for (int k = 0; k < (*ptr - strlen(ind->code)+1); k++)
                                    printf(" ");
                            }
                            else if (col - tempCol == 3) {
                                for (int l = 0; l < vacLine; l++) {
                                    if (strcmp((vaccine+l)->code, ind->code) == 0) {
                                        printf("%s", (vaccine+l)->country);
                                        for (int k = 0; k < (*ptr - strlen((vaccine+l)->country)+1); k++)
                                            printf(" ");
                                        break;
                                    }
                                }
                            }
                            else if (col - tempCol == 4) {
                                for (int k = 0; k < (*ptr - digit(ind->qty)); k++)
                                    printf(" ");

                                printf("%lld ", ind->qty);
                            }
                            else {
                                for (int k = 0; k < (*ptr - digit(j-2)); k++)
                                    printf(" ");
                                printf("%d ", (j-2));
                            }
                        }
                        i += *ptr;
                    }
                }
            }
            if (j != 1) ind++;
        }
        printf("\n");
    }

    free(vaccine);

    for (int i = 0; i < 5; i++) {
        free(*(attr+i));
    }
    free(attr);
    free(width);
}
