#include <stdio.h>
#include <stdlib.h>
#include "var.h"
#include "input.h"
#include "creation.h"
#include "update.h"
#include "search.h"
#include "list.h"
#include "edit.h"

void displayMenu() {
    printf("Vaccine Inventory Management System\n");
    printf("***********************************\n");
	printf("1. Inventory Creation\n");
	printf("2. Update vaccine quantities\n");
	printf("3. Search vaccine\n");
	printf("4. List distributed vaccine\n");
	printf("5. Edit vaccine records\n");
	printf("6. Exit\n");
	printf("***********************************\n");

	int choice = option(1, 6);

	/* printf("\n"); */
    system("@cls||clear");
    switch (choice) {
    case 1:
        createInventory();
        break;
    case 2:
        updateQty();
        break;
    case 3:
        searchRecord();
        break;
    case 4:
        listDistRec();
        break;
    case 5:
        editRecords();
        break;
    case 6:
        printf("Thank you and good bye!\n");
        exit(0);
        break;
    }
    system("@cls||clear");
    /* printf("\n"); */
}
