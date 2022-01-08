#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"

int numOfField(char *filename, char *delim) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", filename, strerror(errno));
        exit(1);
    }
    char *buf = malloc(1024 * sizeof(char));
    char *token;
    int cnt = 0;
    int temp = 0; // temporary variable to store the previous counted fields
    while (fgets(buf, 1024, file)) {
        for (token = strtok(buf, delim); token != NULL; token = strtok(NULL, delim)) {
                cnt++;
        }
        if (temp != cnt && temp != 0) {
            return -1;
        }
        temp = cnt;
        cnt = 0;
    }
    cnt = temp;
    free(buf);
    fclose(file);
    return cnt;
}

int countLine(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", filename, strerror(errno));
        exit(1);
    }
    int cnt = 0;
    char c;
    while ((c = fgetc(file)) && c != EOF) {
        if (c == '\n') cnt++;
    }
    fclose(file);
    return cnt;
}

int digit(ll x) {
    int digit = 1;
    while (x /= 10) digit++;
    return digit;
}

void enterContinue() {
    printf("\nPress enter to continue.");
    while(getchar() != '\n');
    /* printf("\n"); */
    /* system("@cls||clear"); */
}
