#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"
#include "input.h"
#include "info.h"
#include "file2struct.h"
#include "table.h"

void searchRecord() {
    FILE *file = fopen("data/vaccine.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Unable to open vaccine.txt: %s\n", strerror(errno));
        exit(1);
    }

    fclose(file);

    printf("Search vaccine\n");
    printf("**************\n");
    printf("0. Back\n");
    printf("1. Code\n");
    printf("2. Country\n");
    printf("**************\n");
    printf("Search by?\n");

    int choice = option(0, 2);
    
    if (choice == 0) {
        system("@cls||clear");
        return;
    }

    printf("\n");

    int line = countLine("data/vaccine.txt");
    int field = numOfField("data/vaccine.txt", ";");

    // existing vaccine records
    record *vaccine = (record *)malloc(line * sizeof(record));
    vacToStruct(vaccine);

    // to store the matching vaccine
    // worse-case scenario is the query match every vaccine. Therefore, we need
    // to allocate as many as the existing vaccine.
    record *result = (record *)malloc(line * sizeof(record));

    // to store the user query
    char *query = (char *)malloc(64 * sizeof(char));

    getInput("Query: ", query, 64);

    int cnt = 0; // to get the number of query result

    for (int i = 0; i < line; i++) {
        switch (choice) {
        case 1:
            if ((strcasecmp(query, (vaccine+i)->code)) == 0) {
                strcpy((result+cnt)->name, (vaccine+i)->name);
                strcpy((result+cnt)->code, (vaccine+i)->code);
                strcpy((result+cnt)->country, (vaccine+i)->country);
                (result+cnt)->dosage = (vaccine+i)->dosage;
                (result+cnt)->population = (vaccine+i)->population;
                (result+cnt)->qty = (vaccine+i)->qty;
                cnt++;
            }
            break;
        case 2:
            if ((strcasecmp(query, (vaccine+i)->country)) == 0) {
                strcpy((result+cnt)->name, (vaccine+i)->name);
                strcpy((result+cnt)->code, (vaccine+i)->code);
                strcpy((result+cnt)->country, (vaccine+i)->country);
                (result+cnt)->dosage = (vaccine+i)->dosage;
                (result+cnt)->population = (vaccine+i)->population;
                (result+cnt)->qty = (vaccine+i)->qty;
                cnt++;
            }
            break;
        default:
            printf("Default.\n");
        }
    }

    // reallocate to the number of matching query
    result = (record *)realloc(result, cnt * sizeof(record));

    if (cnt > 0) {
        puts("\nQuery result:");
        vacTable(field+1, cnt, result);
    }
    else {
        printf("\nQuery not found.\n");
    }

    free(query);

    free(vaccine);
    free(result);

    enterContinue();
}
