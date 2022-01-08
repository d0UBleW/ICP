#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "var.h"
#include "info.h"

void filesCheck() {
	FILE *fileHandler = fopen("data/vaccine.txt", "r");
	if (fileHandler == NULL) {
		fprintf(stderr, "vaccine.txt: %s\n", strerror(errno));
		fileHandler = fopen("data/vaccine.txt", "w");
		if (fileHandler == NULL) {
			fprintf(stderr, "Unable to create vaccine.txt file.\n");
			exit(1);
		}
		puts("vaccine.txt: File has been created.\n");
	}
	else {
        int line = countLine("data/vaccine.txt");
        if (line > 0) {
            int field = numOfField("data/vaccine.txt", ";");
            if (field == -1) {
                fprintf(stderr, "Inconsistent number of fields in\
                        vaccine.txt\n");
                exit(1);
            }
            if (field != 6) {
                fprintf(stderr, "Incorrect number of fields in vaccine.txt,\
                        expected 6 fields, found %d field(s).\n", field);
                exit(1);
            }
        }
	}
	fclose(fileHandler);

	fileHandler = fopen("data/dist.txt", "r");
	if (fileHandler == NULL) {
		fprintf(stderr, "dist.txt: %s\n", strerror(errno));
		fileHandler = fopen("data/dist.txt", "w");
		if (fileHandler == NULL) {
			fprintf(stderr, "Unable to create dist.txt file.\n");
			exit(1);
		}
		puts("dist.txt: File has been created.\n");
	}
	else {
        int line = countLine("data/dist.txt");
        if (line > 0) {
            int field = numOfField("data/dist.txt", ";");
            if (field == -1) {
                fprintf(stderr, "Inconsistent number of fields in dist.txt\n");
                exit(1);
            }
            if (field != 3) {
                fprintf(stderr, "Incorrect number of fields in dist.txt,\
                        expected 2 fields, found %d field(s).\n", field);
                exit(1);
            }
        }
	}
	fclose(fileHandler);
}
