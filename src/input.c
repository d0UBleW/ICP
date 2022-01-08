#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"
#include "info.h"

void getInput(char *prompt, char *var, int n) {
    char *buf = calloc(n, sizeof(char));
    int retry = 0;
    do {
        printf("%s", prompt);
        if (fgets(buf, n, stdin)) {

            /*
             * Let n = 8. If the user inputs "1234567890" and press enter,
             * then the inside buf will be { '1', '2', '3', '4', '5', '6', '7', '\0' },
             * and "890" will be left in input buffer.
             * 
             * This is because fgets only read (n-1) long character.
             * Therefore, to check if the user does not input too long such that
             * fgets is not able to read all and resulting in some input left in
             * input buffer, we need to check if the user has input a new line character
             * in the first (n-2) bytes/characters.
             * 
             * This is because the maximum value of strlen(buf) can return is only (n-1)
             * since the last character is always a null byte.
             */

            if (buf[strlen(buf) - 1] != '\n') {
                printf("Input must be less than %d characters.\n", (n-2));
                retry = 1;
                while(getchar() != '\n');
                enterContinue();
                continue;
            }

            if ((sscanf(buf, "%[^\n]", var)) != 1) {
                printf("Invalid input format.\n");
                retry = 1;
                enterContinue();
                continue;
            }

            char *ptr = var;
            while (*(ptr++) != '\0') {
                if (
                        (*(ptr-1) < 'A' || *(ptr-1) > 'Z')
                         && (*(ptr-1) < 'a' || *(ptr-1) > 'z')
                   ) {
                    if (
                            *(ptr-1) != '.'
                            && *(ptr-1) != '-'
                            && *(ptr-1) != '\''
                            && *(ptr-1) != ' '
                            && (*(ptr-1) < '0' || *(ptr-1) > '9')
                       ) {
                        printf("Bad character detected: \" %c \"\n", *(ptr-1));
                        retry = 1;
                        enterContinue();
                        break;
                    } else retry = 0;
                } else retry = 0;
            }
        }
    } while (retry);
    free(buf);
}

int option(int lo, int hi) {
    char buf[64];
    int choice;
    int retry = 0;
    do {
        printf("[%d-%d]: ", lo, hi);
        if (fgets(buf, 64, stdin) != NULL) {
            if (buf[strlen(buf) - 1] != '\n') {
                printf("Input must be less than 62 characters.\n");
                retry = 1;
                while(getchar() != '\n');
                enterContinue();
                continue;
            }
            else {
                for (int i = 0; i < strlen(buf); i++) {
                    if (
                            (buf[i] < '0' || buf[i] > '9')
                            && buf[i] != '\n'
                            && buf[i] != '-'
                       ) {
                        retry = 1;
                        printf("\nInvalid input.\n");
                        enterContinue();
                        break;
                    } else retry = 0;
                }
                if (retry != 1) {
                    sscanf(buf, "%d", &choice);
                    if (choice < lo || choice > hi) {
                        printf("\nInput should be between %d and %d\n", lo,
                                hi);
                        retry = 1;
                        enterContinue();
                    } else retry = 0;
                }
            }
        }
        else {
            fprintf(stderr, "Error reading from stdin: %s\n", strerror(errno));
            exit(1);
        }
    } while (retry);

    return choice;
}

void getDosage(int *ptr) {
    char *buf = malloc(64 * sizeof(char));
    int retry = 0;

    while (1) {
        printf("Dosage: ");
        if (fgets(buf, 64, stdin)) {
            if (buf[strlen(buf) - 1] != '\n') {
                printf("Input must be less than 62 characters.\n");
                while(getchar() != '\n');
                enterContinue();
                continue;
            }

            for (int i = 0; i < strlen(buf); i++) {
                if (
                        (buf[i] < '0' || buf[i] > '9')
                        && buf[i] != '\n'
                        && buf[i] != '-'
                   ) {
                    printf("Invalid input.\n");
                    retry = 1;
                    enterContinue();
                    break;
                } else retry = 0;
            }
            if (retry == 1) continue;

            sscanf(buf, "%d", ptr);

            if (*(ptr) < 1) {
                printf("Input should be greater than 0.\n");
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
    free(buf);
}

void getPopulation(float *ptr, float coverage) {
    char *buf = malloc(64 * sizeof(char));
    int retry = 0;

    while (1) {
        printf("Current total coverage: %.1f\n", coverage);
        printf("Population: ");
        if (fgets(buf, 64, stdin)) {
            if (buf[strlen(buf) - 1] != '\n') {
                printf("Input must be less than 62 characters.\n");
                while(getchar() != '\n');
                continue;
            }

            int dotCount = 0;

            for (int i = 0; i < strlen(buf); i++) {
                if (
                        (buf[i] < '0' || buf[i] > '9')
                        && buf[i] != '\n'
                        && buf[i] != '-'
                   ) {
                    if (buf[i] == '.') {
                        dotCount++;
                    }
                    else {
                        printf("Invalid input.\n");
                        retry = 1;
                        enterContinue();
                        break;
                    }
                    if (dotCount < 2) {
                        retry = 0;
                        continue;
                    }
                    else {
                        printf("Invalid input.\n");
                        retry = 1;
                        enterContinue();
                        break;
                    }
                } else retry = 0;
            }
            if (retry == 1) continue;

            sscanf(buf, "%f", ptr);

            if (*ptr < 0 || *ptr > (100.0 - coverage)) {
                printf("Input should be between 0 and %.1f\n",
                        (100.0 - coverage));
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
    free(buf);
}

void getQty(ll *ptr) {
    char *buf = malloc(64 * sizeof(char));
    int retry = 0;

    while (1) {
        printf("Quantities: ");
        if (fgets(buf, 64, stdin)) {
            if (buf[strlen(buf) - 1] != '\n') {
                printf("Input must be less than 62 characters.\n");
                while(getchar() != '\n');
                continue;
            }

            for (int i = 0; i < strlen(buf); i++) {
                if (
                        (buf[i] < '0' || buf[i] > '9')
                        && buf[i] != '\n'
                        && buf[i] != '-'
                   ) {
                    printf("Invalid input.\n");
                    retry = 1;
                    enterContinue();
                    break;
                } else retry = 0;
            }
            if (retry == 1) continue;

            sscanf(buf, "%lld", ptr);

            if (*ptr < 0) {
                printf("Input should not be negative.\n");
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
    free(buf);
}
