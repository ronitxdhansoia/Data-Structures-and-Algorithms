#include<stdio.h>
#include<stdlib.h>

struct Student {
    int IDNO;
    char NAME[50];
    char DOB[15];
    float CGPA;
};

struct Stack {
    int top;
    int capacity;
    struct Student *array;
};

struct Stack* initializeStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Student*)malloc(capacity * sizeof(struct Student));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct Student student) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = student;
    printf("Record pushed onto the stack\n");
}

struct Student pop(struct Stack* stack) {
    struct Student emptyStudent = {0, "", "", 0.0};
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return emptyStudent;
    }
    return stack->array[stack->top--];
}

int main() {
    int N = 5;
    struct Stack* stack = initializeStack(N);

    FILE *inputFile = fopen("studentin.dat", "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        struct Student student;
        fscanf(inputFile, "%d %s %s %f", &student.IDNO, student.NAME, student.DOB, &student.CGPA);
        push(stack, student);
    }

    fclose(inputFile);

    FILE *outputFile = fopen("studentout.dat", "w");
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        return 1;
    }

    while (!isEmpty(stack)) {
        struct Student student = pop(stack);
        printf("%d %s %s %.2f\n", student.IDNO, student.NAME, student.DOB, student.CGPA);
        fprintf(outputFile, "%d %s %s %.2f\n", student.IDNO, student.NAME, student.DOB, student.CGPA);
    }

    fclose(outputFile);

    free(stack->array);
    free(stack);

    return 0;
}
