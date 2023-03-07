#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("Error opening directory %s\n", argv[1]);
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char path[1024];
            sprintf(path, "%s/%s", argv[1], entry->d_name);

            struct stat st;
            if (stat(path, &st) == 0) {
                printf("%s: %lld bytes\n", entry->d_name, (long long) st.st_size);
            } else {
                printf("Error getting file size for %s\n", path);
            }
        }
    }

    closedir(dir);

    return 0;
}
