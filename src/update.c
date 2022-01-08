#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"
#include "info.h"
#include "input.h"
#include "file2struct.h"
#include "table.h"

void updateQty() {
    FILE *file = fopen("data/vaccine.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Unable to open vaccine.txt: %s\n", strerror(errno));
        exit(1);
    }

    fclose(file);

    int line = countLine("data/vaccine.txt");
    int field = numOfField("data/vaccine.txt", ";");

    record *vaccine = (record *)malloc(line * sizeof(record));
    vacToStruct(vaccine);

    printf("Update Quantity\n");
    printf("***************\n");

    if (line > 0) {
        vacTable(field+1, line, vaccine);

        printf("\nSelect the number you wish to update or 0 to go back.\n");

        int vacChoice = option(0, line);

        if (vacChoice == 0) {
            system("@cls||clear");
            return;
        }

        printf("\nSelect the option number.\n");
        printf("1. Add to stock\n");
        printf("2. Deduct from stock (Distribute)\n");

        int opt = option(1, 2);
        char *buf = malloc(64 * sizeof(char));
        ll upQty;

        while (1) {
            switch (opt) {
                case 1:
                    printf("\nInsert the quantity to be added: ");
                    break;
                case 2:
                    printf("\nInsert the quantity to be distributed: ");
                    break;
            }
            if (fgets(buf, 64, stdin)) {
                if (buf[strlen(buf) - 1] != '\n') {
                    printf("Input must be less than 62 characters.\n");
                    while(getchar() != '\n');
                    enterContinue();
                    continue;
                }
                if ((sscanf(buf, "%lld", &upQty)) != 1) {
                    printf("\nInvalid input format.\n");
                    enterContinue();
                    continue;
                }
                if (upQty < 0) {
                    printf("\nInput should not be negative\n");
                    enterContinue();
                    continue;
                }
                if (opt == 2 && upQty > (vaccine+vacChoice-1)->qty) {
                    printf("\nThe value to distribute is larger than available\
                            stock.\n");
                    enterContinue();
                    continue;
                }
                break;
            }
            else {
                fprintf(stderr, "Unable to read from stdin.\n");
                enterContinue();
            }
        }


        switch (opt) {
        case 1:
            (vaccine+vacChoice-1)->qty += upQty;
            break;
        case 2:
            getInput("Where to distribute? ", buf, 64);
            (vaccine+vacChoice-1)->qty -= upQty;
            FILE *distFile = fopen("data/dist.txt", "a");
            fprintf(distFile, "%s;%lld;%s\n", (vaccine+vacChoice-1)->code,
                    upQty, buf);
            fclose(distFile);
        }

        structToVac(vaccine);

        printf("\nUpdate successful.\n");

        vacTable(field+1, line, vaccine);

        free(buf);
        free(vaccine);
    }
    else {
        printf("\nCurrently there is no vaccine to be updated.\n");
    }
    enterContinue();
}
