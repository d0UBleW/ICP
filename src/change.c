#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

int changeWorkDir() {
    char pBuf[256];
    size_t len = sizeof(pBuf);
    int bytes = readlink("/proc/self/exe", pBuf, len);
    if(bytes >= 0) {
        pBuf[bytes] = '\0';
        /* printf("%s\n", pBuf); */
        char cmd[512];
        sprintf(cmd, "dirname %s", pBuf);
        char buf[512];
        FILE *fp;

        if ((fp = popen(cmd, "r")) == NULL) {
            printf("Error opening pipe!\n");
        }

        while (fgets(buf, 512, fp) != NULL) {
            // Do whatever you want here...
            /* printf("OUTPUT: %s", buf); */
            buf[strlen(buf)-1] = '\0';
            if (chdir(buf) != 0) {
                puts("Failed");
                return 1;
            }
            if (chdir("../") != 0) {
                puts("Failed");
                return 1;
            }
            /* char s[100]; */
            /* printf("%s\n", getcwd(s, 100)); */
        }

        if(pclose(fp))  {
            printf("Command not found or exited with error status\n");
            return 1;
        }
    }
    return 0;
}
