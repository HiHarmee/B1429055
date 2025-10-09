#include <stdio.h>

int main(void) {
    FILE *fp = fopen("a.bin", "rb");
    if (!fp) {
        perror("Cannot open file");
        return 1;
    }

    int arr[5];

    printf("=== Reading array 1 ===\n");
    fread(arr, sizeof(int), 5, fp);
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("=== Reading array 2 ===\n");
    fread(arr, sizeof(int), 5, fp);
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("=== Reading array 3 ===\n");
    fread(arr, sizeof(int), 5, fp);
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    fclose(fp);
    return 0;
}
