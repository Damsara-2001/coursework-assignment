#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ROLL_NUMBER_LENGTH 10
#define DATABASE_FILE "student_database.txt"

struct Student {
    char name[MAX_NAME_LENGTH];
    char roll_number[MAX_ROLL_NUMBER_LENGTH];
    char age[3];
    char city[100];
    char gender[10];
    char email[50];
    char pno[10];
};

void displayMenu();
void addStudent();
void updateStudent();
void deleteStudent();
void viewStudents();

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                updateStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                viewStudents();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        while (getchar() != '\n'); // Clear the input buffer to avoid issues with scanf
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\nStudent Registration System\n");
    printf("1. Add Student\n");
    printf("2. Update Student\n");
    printf("3. Delete Student\n");
    printf("4. View Students\n");
    printf("5. Exit\n");
}

void addStudent() {
    struct Student newStudent;
    FILE *file = fopen(DATABASE_FILE, "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the student's name: ");
    scanf(" %[^\n]", newStudent.name);

    printf("Enter the student's Age: ");
    scanf(" %[^\n]", newStudent.age);

    printf("Enter the student's City: ");
    scanf(" %[^\n]", newStudent.city);

    printf("Enter the student's Gender: ");
    scanf(" %[^\n]", newStudent.gender);

    printf("Enter the student's E-mail: ");
    scanf(" %[^\n]", newStudent.email);

    printf("Enter the student's Phone Number: ");
    scanf(" %[^\n]", newStudent.pno);

    printf("Enter the student's roll number: ");
    scanf(" %[^\n]", newStudent.roll_number);

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", newStudent.name, newStudent.age, newStudent.city,
             newStudent.gender, newStudent.email, newStudent.pno, newStudent.roll_number);
    fclose(file);

    printf("Student added successfully.\n");
}

void updateStudent() {
    char rollNumber[MAX_ROLL_NUMBER_LENGTH];
    printf("Enter the roll number of the student to update: ");
    scanf(" %[^\n]", rollNumber);

    FILE *file = fopen(DATABASE_FILE, "r");
    FILE *tempFile = fopen("temp_file.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Student student;
    int found = 0;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", student.name, student.age, student.city, student.gender,
                   student.email, student.pno, student.roll_number) != EOF) {

        if (strcmp(student.roll_number, rollNumber) == 0) {
            found = 1;
            printf("Enter the updated name of the student: ");
            scanf(" %[^\n]", student.name);
            printf("Enter the updated age of the student: ");
            scanf(" %[^\n]", student.age);
            printf("Enter the updated city of the student: ");
            scanf(" %[^\n]", student.city);
            printf("Enter the updated gender of the student: ");
            scanf(" %[^\n]", student.gender);
            printf("Enter the updated e-mail of the student: ");
            scanf(" %[^\n]", student.email);
            printf("Enter the updated phone number of the student: ");
            scanf(" %[^\n]", student.pno);
        }

        fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s\n", student.name, student.age, student.city, student.gender,
                 student.email, student.pno, student.roll_number);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Student with roll number '%s' not found.\n", rollNumber);
        remove("temp_file.txt");
        return;
    }

    remove(DATABASE_FILE);
    rename("temp_file.txt", DATABASE_FILE);

    printf("Student information updated successfully.\n");
}

void deleteStudent() {
    char rollNumber[MAX_ROLL_NUMBER_LENGTH];
    printf("Enter the roll number of the student to delete: ");
    scanf(" %[^\n]", rollNumber);

    FILE *file = fopen(DATABASE_FILE, "r");
    FILE *tempFile = fopen("temp_file.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Student student;
    int found = 0;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", student.name, student.age, student.city, student.gender,
                   student.email, student.pno, student.roll_number) != EOF) {

        if (strcmp(student.roll_number, rollNumber) == 0) {
            found = 1;
            continue;
        }

        fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s\n", student.name, student.age, student.city, student.gender, student.email,
                student.pno, student.roll_number);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Student with roll number '%s' not found.\n", rollNumber);
        remove("temp_file.txt");
        return;
    }

    remove(DATABASE_FILE);
    rename("temp_file.txt", DATABASE_FILE);

    printf("Student record deleted successfully.\n");
}

void viewStudents() {
    FILE *file = fopen(DATABASE_FILE, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Student student;

    printf("\n--- Student Records ---\n\n");
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", student.name, student.age, student.city, student.gender,
                  student.email, student.pno, student.roll_number) != EOF) {
        printf("Name: %s\n", student.name);
        printf("Age: %s\n", student.age);
        printf("City: %s\n", student.city);
        printf("Gender: %s\n", student.gender);
        printf("E-mail: %s\n", student.email);
        printf("Phone Number: %s\n", student.pno);
        printf("Roll Number: %s\n", student.roll_number);
        printf("-----------------------\n");
    }

    fclose(file);
}
