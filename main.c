#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
} Name;

int compareNames(const void *a, const void *b) {
    return strcmp(((Name *)a)->name, ((Name *)b)->name);
}

int main() {
    FILE *file;
    char filename[100];
    char key[MAX_NAME_LENGTH];
    Name *names = NULL;
    int numNames = 0;

    printf("Dosya adini girin: ");
    scanf("%s", filename);
    printf("Aranacak ismi girin: ");
    scanf("%s", key);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Dosya acilirken hata olustu");
        return 1;
    }

    while (!feof(file)) {
        names = (Name *)realloc(names, (numNames + 1) * sizeof(Name));
        fscanf(file, "%s\n", names[numNames].name);
        numNames++;
    }

    qsort(names, numNames, sizeof(Name), compareNames);

    int left = 0;
    int right = numNames - 1;
    int found = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(key, names[mid].name);
        if (cmp == 0) {
            found = 1;
            printf("Isim '%s' dosyada bulundu.\n", key);
            break;
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (!found) {
        printf("Isim '%s' dosyada bulunamadi.\n", key);
    }

    free(names);

    fclose(file);

    return 0;
}
