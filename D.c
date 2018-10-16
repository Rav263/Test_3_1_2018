#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


int
main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    DIR *dr = opendir(argv[1]);
    long long max_sum_size = strtoll(argv[2], NULL, 10);

    char name[PATH_MAX + 3];
    long long max_size = 0;
    long long sum_size = 0;

    while (1) {
        struct dirent *dir = readdir(dr);

        if (dir == NULL) {
            break;
        }

        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) {
            continue;
        }

        struct stat st = {};

        char path[PATH_MAX + 2];

        sprintf(path, "%s/%s", argv[1], dir->d_name);

        lstat(path, &st);

        if (S_ISREG(st.st_mode)) {
            if (st.st_size == max_size) {
                if (strcmp(name, dir->d_name) > 0) {
                    strcpy(name, dir->d_name);
                }
            }
            if (st.st_size > max_size) {
                max_size = st.st_size;
                strcpy(name, dir->d_name);
            }

            sum_size += st.st_size;
        }
    }

    if (sum_size > max_sum_size) {
        printf("%s\n", name);
    }


    return 0;
}
