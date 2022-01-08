#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"
#include "info.h"
#include "input.h"
#include "file2struct.h"

void createInventory() {
    char *filename = "data/vaccine.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", filename, strerror(errno));
        exit(1);
    }
    fclose(file);

    file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "Unable to append %s: %s\n", filename,
                strerror(errno)); exit(1);
    }

    printf("Add new inventory\n");
    printf("*****************\n");

    int line = countLine("data/vaccine.txt");
    record *current = (record *)malloc(sizeof(record) * line);
    vacToStruct(current);
    record *newEntry = (record *)malloc(sizeof(record));

    int duplicate = 0;
    do {
        getInput("Name: ", newEntry->name, 64);
        for (int i = 0; i < line; i++) {
            if (strcmp(newEntry->name, (current+i)->name) == 0) {
                duplicate = 1;
                printf("%s is already used in existing record.\n",
                        newEntry->name);
                enterContinue();
                break;
            }
            else duplicate = 0;
        }
    } while (duplicate);

    do {
        getInput("Code: ", newEntry->code, 64);
        for (int i = 0; i < line; i++) {
            if (strcmp(newEntry->code, (current+i)->code) == 0) {
                duplicate = 1;
                printf("%s is already used in existing record.\n",
                        newEntry->code);
                enterContinue();
                break;
            }
            else duplicate = 0;
        }
    } while (duplicate);

    getInput("Country: ", newEntry->country, 64);

    getDosage(&(newEntry->dosage));

    float coverage = 0;
    for (int i = 0; i < line; i++) {
        coverage += (current+i)->population;
    }

    getPopulation(&(newEntry->population), coverage);

    getQty(&(newEntry->qty));

    fprintf(file, "%s;%s;%s;%d;%.1f;%lld\n", newEntry->name, newEntry->code,
            newEntry->country, (newEntry->dosage), (newEntry->population),
            (newEntry->qty)); free(newEntry);
    free(current);
    fclose(file);
    printf("Inventory creation successful.\n");
    enterContinue();
}
