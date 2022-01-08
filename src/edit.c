#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "var.h"
#include "info.h"
#include "input.h"
#include "file2struct.h"
#include "table.h"

void editRecords() {
    FILE *file = fopen("data/vaccine.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Unable to open vaccine.txt: %s\n", strerror(errno));
        exit(1);
    }
    fclose(file);

    int line = countLine("data/vaccine.txt");
    int field = numOfField("data/vaccine.txt", ";");
    if (line > 0) {
        record *vaccine = (record *)malloc(line * sizeof(record));
        vacToStruct(vaccine); // convert from file to struct

        printf("Edit Inventory Records\n");
        printf("**********************\n");
        vacTable(field+1, line, vaccine);

        printf("\nSelect the number you wish to update or 0 to go back.\n");
        int choice = option(0, line) - 1;

        if (choice == -1) {
            system("@cls||clear");
            return;
        }

        printf("\nChoose attributes\n");
        printf("*****************\n");
        printf("0. Back\n");
        printf("1. Name\n");
        printf("2. Code\n");
        printf("3. Country\n");
        printf("4. Dosage\n");
        printf("5. Population Percentage\n");
        printf("6. Quantity\n");
        printf("*****************\n");

        int attrNo = option(0, 6);

        if (attrNo == 0) {
            system("@cls||clear");
            return;
        }

        printf("\n");

        // buf to temporarily store the input data before storing it to desired
        // variable
        char *buf = malloc(64 * sizeof(char));
        // duplicate variable used when editting Name and Code, 0 indicates no
        // duplicate, 1 indicates found duplicate
        int duplicate = 0;

        switch (attrNo) {
        // semi-colon added to resolve "a label can only be part of a statement
        // and a declaration is not a statement" error, source:
        // https://www.educative.io/edpresso/resolving-the-a-label-can-only-be-part-of-a-statement-error
        case 1: ;
            do {
                getInput("Name: ", buf, 64);
                for (int i = 0; i < line; i++) {
                    if (strcmp(buf, (vaccine+i)->name) == 0 && i != choice) {
                        duplicate = 1;
                        printf("%s is already used in existing records.\n",
                                buf);
                        enterContinue();
                        break;
                    }
                    else duplicate = 0;
                }
            } while (duplicate);
            strcpy((vaccine+choice)->name, buf);
            break;
        case 2: ;
            int distLine = countLine("data/dist.txt");

            distRec *dist = (distRec *)malloc(distLine * sizeof(distRec));
            distToStruct(dist);

            do {
                getInput("Code: ", buf, 64);
                for (int i = 0; i < line; i++) {
                    if (strcmp(buf, (vaccine+i)->code) == 0 && i != choice) {
                        duplicate = 1;
                        printf("%s is already used in existing records.\n",
                                buf);
                        enterContinue();
                        break;
                    }
                    else duplicate = 0;
                }
            } while (duplicate);

            for (int i = 0; i < distLine; i++) {
                if ((strcmp((dist+i)->code, (vaccine+choice)->code)) == 0) {
                    strcpy((dist+i)->code, buf);
                }
            }
            strcpy((vaccine+choice)->code, buf);

            structToDist(dist, distLine);
            free(dist);
            break;
        case 3:
            getInput("Country: ", (vaccine+choice)->country, 64);
            break;
        case 4: ;
            int intTemp;
            getDosage(&intTemp);

            (vaccine+choice)->dosage = intTemp;
            break;
        case 5: ;
            float floatTemp;
            float coverage = 0;
            for (int i = 0; i < line; i++) {
                if (i == choice) continue;
                coverage += (vaccine+i)->population;
            }
            getPopulation(&floatTemp, coverage);

            (vaccine+choice)->population = floatTemp;
            break;
        case 6: ;
            ll llTemp;
            getQty(&llTemp);

            (vaccine+choice)->qty = llTemp;
            break;
        }

        free(buf);
        structToVac(vaccine);

        printf("\nEdit successful.\n");
        vacTable(field+1, line, vaccine);

        free(vaccine);
    }
    else {
        printf("\nCurrently there is no vaccine record to be edited.\n");
    }
    enterContinue();
}
