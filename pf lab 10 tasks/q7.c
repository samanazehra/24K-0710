#include <stdio.h>

void compareTemperature(int temp, int maxTemp) {
    static int count = 0;
    if (temp > maxTemp) {
        count++;
    }
    printf("Count of exceeded temperatures: %d\n", count);
}

int main() {
    int maxTemp;
    printf("Enter the maximum allowable temperature: ");
    scanf("%d", &maxTemp);

    int n;
    printf("Enter the number of temperatures to compare: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int temp;
        printf("Enter temperature %d: ", i + 1);
        scanf("%d", &temp);
        compareTemperature(temp, maxTemp);
    }
    return 0;
}
