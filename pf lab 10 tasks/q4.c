#include <stdio.h>
#include <string.h>

struct Movie {
    char title[50];
    char genre[30];
    char director[50];
    int releaseYear;
    float rating;
};

void addMovie(struct Movie movies[], int *count, int maxMovies) {
    if (*count >= maxMovies) {
        printf("Movie list is full.\n");
        return;
    }

    printf("Enter title: ");
    scanf(" %[^\n]", movies[*count].title);
    printf("Enter genre: ");
    scanf(" %[^\n]", movies[*count].genre);
    printf("Enter director: ");
    scanf(" %[^\n]", movies[*count].director);
    printf("Enter release year: ");
    scanf("%d", &movies[*count].releaseYear);
    printf("Enter rating (0.0 to 10.0): ");
    scanf("%f", &movies[*count].rating);

    (*count)++;
    printf("Movie added successfully!\n");
}

void searchByGenre(struct Movie movies[], int count, char genre[]) {
    printf("\nMovies in genre '%s':\n", genre);
    for (int i = 0; i < count; i++) {
        if (strcmp(movies[i].genre, genre) == 0) {
            printf("Title: %s\n", movies[i].title);
            printf("Director: %s\n", movies[i].director);
            printf("Release Year: %d\n", movies[i].releaseYear);
            printf("Rating: %.1f\n\n", movies[i].rating);
        }
    }
}

void displayAllMovies(struct Movie movies[], int count) {
    printf("\nAll Movies:\n");
    for (int i = 0; i < count; i++) {
        printf("Title: %s\n", movies[i].title);
        printf("Genre: %s\n", movies[i].genre);
        printf("Director: %s\n", movies[i].director);
        printf("Release Year: %d\n", movies[i].releaseYear);
        printf("Rating: %.1f\n\n", movies[i].rating);
    }
}

int main() {
    struct Movie movies[10];
    int movieCount = 0;
    int choice;
    char searchGenre[30];

    while (1) {
        printf("1. Add Movie\n");
        printf("2. Search by Genre\n");
        printf("3. Display All Movies\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        switch (choice) {
            case 1:
                addMovie(movies, &movieCount, 10);
                break;
            case 2:
                printf("Enter genre to search: ");
                scanf(" %[^\n]", searchGenre);
                searchByGenre(movies, movieCount, searchGenre);
                break;
            case 3:
                displayAllMovies(movies, movieCount);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
