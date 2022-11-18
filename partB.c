#include <stdio.h>    // printf function
#include <stdlib.h>   // exit function
#include <errno.h>    // error handling
#include <fcntl.h>    // file control
#include <unistd.h>   // read, write, close
#include <sys/wait.h> // wait function
#include <sys/shm.h>  // shared memory functions
#include <sys/stat.h> // constraints for file permissions
#include <string.h>   // char array manipulation

typedef struct student_marks // structure definition for student marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

typedef struct analize_marks // structure definition for analize_marks
{
    float min;
    float max;
    float average;
    int numofstudent_below;
} analize_marks;

int getAllDataWithLength();

student_marks *marksPtr;

void main()
{
    int length = getAllDataWithLength(); // get all records and length of records from file

    key_t ky = ftok("file.txt", 78); // create a key for shared memory
    if (ky == -1)
    {
        perror("ftok error: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }

    int SMID = shmget(ky, 4096, IPC_CREAT | 0666); // create shared memory
    if (SMID == -1)
    {
        perror("shmget error: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }

    pid_t PID1 = fork(); // create child process 1
    if (PID1 == -1)
    {
        perror("fork error: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }
    else if (PID1 == 0)
    { // Child Process C1
    }
    else
    {

        pid_t PID2 = fork(); // create child process 2

        if (PID2 == -1)
        {
            perror("fork error: ");
            printf("Error No: %d\n", errno);
            exit(1);
        }
        else if (PID2 == 0)
        { // Child Process C2
        }
        else
        {
            pid_t PID3 = fork(); // create child process 3

            if (PID3 == -1)
            {
                perror("fork error: ");
                printf("Error No: %d \n", errno);
                exit(1);
            }
            else if (PID3 == 0)
            { // Child Process C3
            }
            else
            {

                pid_t PID4 = fork(); // create child process 4

                if (PID4 == -1)
                {
                    perror("fork error: ");
                    printf("Error No: %d \n", errno);
                    exit(1);
                }
                else if (PID4 == 0)
                { // Child Process C4
                }
                else
                { // Parent Process
                }
            }
        }
    }
}

int getAllDataWithLength() // function to get the number of records in the file
{
    student_marks output;
    FILE *file;
    int count = 0;

    marksPtr = (student_marks *)malloc(count * sizeof(struct student_marks)); // allocate memory for the structure

    file = fopen("student_marks.dat", "r"); // open file for writing and reading
    if (file == NULL)                       // error handling
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    printf("\n");
    while (fread(&output, sizeof(struct student_marks), 1, file)) // read each record from file with error handling
    {
        count++;
        marksPtr = (student_marks *)realloc(marksPtr, count * sizeof(struct student_marks)); // reallocate memory for the structure
        strcpy((marksPtr + count - 1)->student_index, output.student_index);                 // copy data to the structure
        (marksPtr + count - 1)->assignmt01_marks = output.assignmt01_marks;
        (marksPtr + count - 1)->assignmt02_marks = output.assignmt02_marks;
        (marksPtr + count - 1)->project_marks = output.project_marks;
        (marksPtr + count - 1)->finalExam_marks = output.finalExam_marks;
    }

    fclose(file); //  close file
    return count;   // return the number of records
}