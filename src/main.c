#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "change.h"
#include "filecheck.h"

int main() {
    system("@cls||clear");
    changeWorkDir();
    filesCheck();
    while (1) {
        displayMenu();
    }
    return 0;
}
