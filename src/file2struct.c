#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"
#include "info.h"

void vacToStruct(record *inventory) {
    FILE *file = fopen("data/vaccine.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open vaccine.txt: %s\n", strerror(errno));
        exit(1);
    }

    char delim[] = ";";

    //strtok to split the records based on the specified delimiter
    char *buf = (char *)malloc(1024 * sizeof(char));
    char *token;
    int i = 0;
    while (fgets(buf, 1024, file)) {
        token = strtok(buf, delim);
        sscanf(token, "%[^\n]", (inventory+i)->name);

        token = strtok(NULL, delim);
        sscanf(token, "%[^\n]", (inventory+i)->code);

        token = strtok(NULL, delim);
        sscanf(token, "%[^\n]", (inventory+i)->country);

        token = strtok(NULL, delim);
        sscanf(token, "%d", &((inventory+i)->dosage));

        token = strtok(NULL, delim);
        sscanf(token, "%f", &((inventory+i)->population));

        token = strtok(NULL, delim);
        sscanf(token, "%lld", &((inventory+i)->qty));

        i++;
    }

    free(buf);

    fclose(file);

}

void structToVac (record *inventory) {
    int line = countLine("data/vaccine.txt");

    FILE *file = fopen("data/vaccine.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Unable to create vaccine.txt: %s.\n",
                strerror(errno));
        exit(1);
    }

    for (int i = 0; i < line; i++) {
        fprintf(file, "%s;%s;%s;%d;%.1f;%lld\n", (inventory+i)->name,
                (inventory+i)->code, (inventory+i)->country,
                (inventory+i)->dosage, (inventory+i)->population,
                (inventory+i)->qty);
    }

    fclose(file);
}

void compressed_distToStruct(distRec *dist, int *cnt) {
    FILE *file = fopen("data/dist.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open dist.txt: %s\n", strerror(errno));
        exit(1);
    }

    char delim[] = ";";

    char *buf = (char *)malloc(1024 * sizeof(char));
    char *token;
    int i = 0;
    int found = 0;
    ll temp = 0;
    while (fgets(buf, 1024, file)) {
        token = strtok(buf, delim);
        for (int j = 0; j < i; j++) {
            if (strcmp(token, (dist+j)->code) == 0) {
                token = strtok(NULL, delim);
                sscanf(token, "%lld", &temp);
                (dist+j)->qty += temp;
                found = 1;
            }
        }
        if (found == 0) {
            sscanf(token, "%[^\n]", (dist+(*cnt))->code);
            token = strtok(NULL, delim);
            sscanf(token, "%lld", &((dist+(*cnt))->qty));
            (*cnt)++;
        }
        found = 0; // reset found
        token = strtok(NULL, delim);
        i++;
    }
    free(buf);

    fclose(file);
}

void distToStruct(distRec *dist) {
    FILE *file = fopen("data/dist.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open dist.txt: %s\n", strerror(errno));
        exit(1);
    }

    char delim[] = ";";

    char *buf = (char *)malloc(1024 * sizeof(char));
    char *token;
    int i = 0;
    while (fgets(buf, 1024, file)) {
        token = strtok(buf, delim);
        sscanf(token, "%[^\n]", (dist+i)->code);
        token = strtok(NULL, delim);
        sscanf(token, "%lld", &((dist+i)->qty));
        token = strtok(NULL, delim);
        sscanf(token, "%[^\n]", (dist+i)->dest);
        i++;
    }

    free(buf);

    fclose(file);
}

void structToDist (distRec *dist, int line) {
    FILE *file = fopen("data/dist.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Unable to create dist.txt: %s.\n", strerror(errno));
        exit(1);
    }

    for (int i = 0; i < line; i++) {
        fprintf(file, "%s;%lld;%s\n", (dist+i)->code, (dist+i)->qty,
                (dist+i)->dest);
    }

    fclose(file);
}
