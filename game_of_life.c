#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void AllocateMemory(char*** matrix, int hieght, int width);
void ArrayFulling(char** matrix, int height, int width);
void Add(char** matrix, int hieght, int width);
void init(char*** matrix, int height, int width, int* generation, int* speed);
void output(char** matrix, int height, int width, int generation);
int check(char** matrix, int cord_y, int cord_x);
void update(char** matrix1, char*** matrix2, int height, int width, int* flag);
void match(char** matrix1, char** matrix2, int height, int width, int* flag);
void Swap(char*** mx1, char*** mx2);
void changeSpeed(int* speed);
char getKey();
void FreeMemory(char*** matrix);

int main() {
    int flag = 0;
    int generation;
    int height = 25, width = 80;
    char** matrix1;
    char** matrix2;
    int speed;

    init(&matrix1, height, width, &generation, &speed);
    AllocateMemory(&matrix2, height, width);
    while (1) {
        generation++;
        usleep(speed);
        update(matrix1, &matrix2, height, width, &flag);
        match(matrix1, matrix2, height, width, &flag);
        output(matrix2, height, width, generation);
        Swap(&matrix2, &matrix1);
        if (flag == 1) {
            printf("____________________________________The End.____________________________________");
            break;
        }
    }
    FreeMemory(&matrix1);
    FreeMemory(&matrix2);
    return 0;
}

void AllocateMemory(char*** matrix, int hieght, int width) {
    *matrix = (char**)malloc(hieght * sizeof(char*));
    char* tmp = (char*)malloc(hieght * width * sizeof(char));
    for (int i = 0; i < hieght; i++) {
        (*matrix)[i] = tmp + i * width;
    }
}

void ArrayFulling(char** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = ' ';
        }
    }
}

void Add(char** matrix, int hieght, int width) {
    char c;
    scanf("%c", &c);
    switch (c) {
        case '1':
            FILE* file1;
            file1 = fopen("/home/loganmar/projects/P02D13-1/src/eat.txt", "r");
            for (int i = 0; i < hieght; i++) {
                for (int j = 0; j < width; j++) {
                    int ch = fgetc(file1);
                    if (ch != 10) {
                        matrix[i][j] = (char)ch;
                    } else {
                        j--;
                    }
                }
            }
            fclose(file1);
            break;
        case '2':
            FILE* file2;
            file2 = fopen("/home/loganmar/projects/P02D13-1/src/gun.txt", "r");
            for (int i = 0; i < hieght; i++) {
                for (int j = 0; j < width; j++) {
                    int ch = fgetc(file2);
                    if (ch != 10) {
                        matrix[i][j] = (char)ch;
                    } else {
                        j--;
                    }
                }
            }
            fclose(file2);
            break;
        case '3':
            FILE* file3;
            file3 = fopen("/home/loganmar/projects/P02D13-1/src/longlife.txt", "r");
            for (int i = 0; i < hieght; i++) {
                for (int j = 0; j < width; j++) {
                    int ch = fgetc(file3);
                    if (ch != 10) {
                        matrix[i][j] = (char)ch;
                    } else {
                        j--;
                    }
                }
            }
            fclose(file3);
            break;
        case '4':
            FILE* file4;
            file4 = fopen("/home/loganmar/projects/P02D13-1/src/movefig.txt", "r");
            for (int i = 0; i < hieght; i++) {
                for (int j = 0; j < width; j++) {
                    int ch = fgetc(file4);
                    if (ch != 10) {
                        matrix[i][j] = (char)ch;
                    } else {
                        j--;
                    }
                }
            }
            fclose(file4);
            break;
        case '5':
            FILE* file5;
            file5 = fopen("/home/loganmar/projects/P02D13-1/src/state_fig.txt", "r");
            for (int i = 0; i < hieght; i++) {
                for (int j = 0; j < width; j++) {
                    int ch = fgetc(file5);
                    if (ch != 10) {
                        matrix[i][j] = (char)ch;
                    } else {
                        j--;
                    }
                }
            }
            fclose(file5);
            break;
    }
}

void init(char*** matrix, int height, int width, int* generation, int* speed) {
    *generation = 0;
    AllocateMemory(matrix, height, width);
    ArrayFulling(*matrix, height, width);
    Add(*matrix, height, width);
    changeSpeed(speed);
    output(*matrix, height, width, *generation);
}

void output(char** matrix, int height, int width, int generation) {
    printf("\033c");
    printf("|Generation: %d|\n", generation);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

int check(char** matrix, int cord_y, int cord_x) {
    int counter = 0;
    for (int i = cord_y - 1; i <= cord_y + 1; i++) {
        for (int j = cord_x - 1; j <= cord_x; j++) {
            int cord_i = i, cord_j = j;
            if (cord_i == -1) cord_i = 24;
            if (cord_i == 25) cord_i = 0;
            if (cord_j == -1) cord_j = 79;
            if (cord_j == 80) cord_j = 0;
            if ((matrix[cord_i][cord_j] == '1') && ((cord_i != cord_y) || (cord_j != cord_x))) counter++;
        }
    }
    return counter;
}

void update(char** matrix1, char*** matrix2, int height, int width, int* flag) {
    int counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            (*matrix2)[i][j] = '0';
            int s = check(matrix1, i, j);
            counter += s;
            if (s > 0)
                if (((matrix1[i][j] == '1') && (s == 2 || s == 3)) || ((matrix1[i][j] == '0') && (s == 3)))
                    (*matrix2)[i][j] = '1';
        }
    }
    if (counter == 0) *flag = 0;
}

void match(char** matrix1, char** matrix2, int height, int width, int* flag) {
    *flag = 1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix2[i][j] != matrix1[i][j]) {
                *flag = 0;
                return;
            }
        }
    }
}

void Swap(char*** mx1, char*** mx2) {
    char** tmp = *mx1;
    *mx1 = *mx2;
    *mx2 = tmp;
}

void changeSpeed(int* speed) {
    printf("Choose game speed from 1 to 5:\n");
    char key = getKey();
    switch (key) {
        case '1':
            *speed = 0.5;
            break;
        case '2':
            *speed = 500000;
            break;
        case '3':
            *speed = 250000;
            break;
        case '4':
            *speed = 100000;
            break;
        case '5':
            *speed = 50000;
            break;
    }
}

char getKey() {
    char key;
    while (1) {
        if (scanf("%c", &key) == -1) {
            printf("GOTCHA");
        }
        if ((key >= '1') && (key <= '5')) break;
    }
    return key;
}

void FreeMemory(char*** matrix) {
    if (*matrix) {
        if ((*matrix)[0]) {
            free((*matrix)[0]);
        }
        free(*matrix);
    }
}
