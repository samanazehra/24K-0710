#include <stdio.h>
#include <math.h>

struct Point {
    int x;
    int y;
};

double calculateDistance(struct Point p1, struct Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

int isPointInRectangle(struct Point p, struct Point bottomLeft, struct Point topRight) {
    return p.x >= bottomLeft.x && p.x <= topRight.x && p.y >= bottomLeft.y && p.y <= topRight.y;
}

int main() {
    struct Point p1, p2, bottomLeft, topRight;

    printf("Enter coordinates of Point 1 (x y): ");
    scanf("%d %d", &p1.x, &p1.y);

    printf("Enter coordinates of Point 2 (x y): ");
    scanf("%d %d", &p2.x, &p2.y);

    printf("Enter bottom-left corner of rectangle (x y): ");
    scanf("%d %d", &bottomLeft.x, &bottomLeft.y);

    printf("Enter top-right corner of rectangle (x y): ");
    scanf("%d %d", &topRight.x, &topRight.y);

    printf("Distance: %.2f\n", calculateDistance(p1, p2));
    printf("Point inside rectangle: %d\n", isPointInRectangle(p1, bottomLeft, topRight));
    return 0;
}
