#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_CLASSES 200
#define MIN_ATTENDANCE 75.0

typedef struct
{
    long long sapid;
    char name[50];
    int attendance[MAX_CLASSES];
    int totalClasses;
    int presentClasses;
} Student;

Student students[MAX_STUDENTS];

int studentCount = 0;
int classCount = 0;

/* Function Prototypes */
void clearInput();
int findStudent(long long sapid);
void addStudent();
void markAttendance();
void displayStudents();
void calculateAttendance();
void showDefaulters();
void searchStudent();
void attendanceReport();
void classesNeeded();

/* Clear Input Buffer */
void clearInput()
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/* Find Student by SAP ID */
int findStudent(long long sapid)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].sapid == sapid)
        {
            return i;
        }
    }

    return -1;
}
void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("\nStudent limit reached!\n");
        return;
    }

    long long sapid;

    printf("\nEnter 9-Digit SAP ID: ");

    if (scanf("%lld", &sapid) != 1)
    {
        clearInput();
        printf("Invalid SAP ID!\n");
        return;
    }

    if (sapid < 100000000 || sapid > 999999999)
    {
        printf("SAP ID must be exactly 9 digits!\n");
        return;
    }

    if (findStudent(sapid) != -1)
    {
        printf("Duplicate SAP ID!\n");
        return;
    }

    Student *s = &students[studentCount];

    s->sapid = sapid;

    clearInput();

    printf("Enter Student Name: ");

    fgets(s->name, sizeof(s->name), stdin);

    s->name[strcspn(s->name, "\n")] = '\0'; // assiginng

    if (strlen(s->name) == 0 ||
        strspn(s->name, " ") == strlen(s->name))
    {
        printf("Invalid Name!\n");
        return;
    }

    s->totalClasses = 0;
    s->presentClasses = 0;

    studentCount++;

    printf("\nStudent added successfully!\n");
}
void markAttendance()
{
    if (studentCount == 0)
    {
        printf("\nPlease add students first!\n");
        return;
    }

    if (classCount >= MAX_CLASSES)
    {
        printf("\nMaximum class limit reached!\n");
        return;
    }

    int records[MAX_STUDENTS]; // temporary array

    printf("\n===== MARK ATTENDANCE =====\n");
    printf("Class Number: %d\n", classCount + 1);

    for (int i = 0; i < studentCount; i++)
    {
        int status;

        while (1)
        {
            printf("\n%lld - %s (1/0): ",
                   students[i].sapid,
                   students[i].name);

            if (scanf("%d", &status) != 1)
            {
                clearInput();
                printf("Invalid input! Enter 1 or 0.\n");
                continue;
            }

            if (status == 0 || status == 1)
            {
                records[i] = status;
                break;
            }

            printf("Invalid choice! Enter 1 or 0.\n");
        }
    }

    for (int i = 0; i < studentCount; i++)
    {
        students[i].attendance[classCount] = records[i];
        students[i].totalClasses++;

        if (records[i] == 1)
        {
            students[i].presentClasses++;
        }
    }

    classCount++;

    printf("\nAttendance marked successfully!\n");
}

void displayStudents()
{
    if (studentCount == 0)
    {
        printf("\nNo students registered!\n");
        return;
    }

    printf("\n========== STUDENT LIST ==========\n");
    printf("%-12s %-25s\n", "SAP ID", "Name");

    for (int i = 0; i < studentCount; i++)
    {
        printf("%-12lld %-25s\n",
               students[i].sapid,
               students[i].name);
    }
}
void calculateAttendance()
{
    long long sapid;

    printf("\nEnter SAP ID: ");

    if (scanf("%lld", &sapid) != 1)
    {
        clearInput();
        printf("Invalid input!\n");
        return;
    }

    int index = findStudent(sapid);

    if (index == -1)
    {
        printf("\nStudent not found!\n");
        return;
    }

    Student s = students[index];

    printf("\n===== ATTENDANCE DETAILS =====\n");
    printf("SAP ID: %lld\n", s.sapid);
    printf("Name: %s\n", s.name);
    printf("Total Classes: %d\n", s.totalClasses);
    printf("Classes Attended: %d\n", s.presentClasses);

    if (s.totalClasses == 0)
    {
        printf("Attendance: Not Available\n");
        return;
    }

    double percentage =
        (s.presentClasses * 100.0) / s.totalClasses;

    printf("Attendance: %.2f%%\n", percentage);

    if (percentage >= MIN_ATTENDANCE)
        printf("Status: Satisfactory Attendance\n");
    else
        printf("Status: SHORT ATTENDANCE!\n");
}

void showDefaulters()
{
    int found = 0;

    printf("\n===== STUDENTS BELOW 75%% =====\n");

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].totalClasses == 0)
            continue;

        double percentage =
            students[i].presentClasses * 100.0 /
            students[i].totalClasses;

        if (percentage < MIN_ATTENDANCE)
        {
            printf("\nSAP ID: %lld\n",
                   students[i].sapid);
            printf("Name: %s\n",
                   students[i].name);
            printf("Attendance: %.2f%%\n",
                   percentage);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No students below 75%% attendance.\n");
    }
}
void searchStudent()
{
    long long sapid;

    printf("\nEnter SAP ID To Search: ");

    if (scanf("%lld", &sapid) != 1)
    {
        clearInput();
        printf("Invalid Input!\n");
        return;
    }

    int index = findStudent(sapid);

    if (index == -1)
    {
        printf("\nStudent not found!\n");
        return;
    }

    printf("\nStudent Found!\n");
    printf("SAP ID: %lld\n", students[index].sapid);
    printf("Name: %s\n", students[index].name);
}

void attendanceReport()
{
    printf("\n========== ATTENDANCE REPORT ==========\n");

    printf("%-12s %-20s %-10s %-10s %-10s\n",
           "SAP ID", "Name", "Total",
           "Present", "Percent");

    for (int i = 0; i < studentCount; i++)
    {
        double percentage = 0;

        if (students[i].totalClasses > 0)
        {
            percentage =
                students[i].presentClasses * 100.0 /
                students[i].totalClasses;
        }

        printf("%-12lld %-20.20s %-10d %-10d %.2f%%\n",
               students[i].sapid,
               students[i].name,
               students[i].totalClasses,
               students[i].presentClasses,
               percentage);
    }
}

void classesNeeded()
{
    long long sapid;

    printf("\nEnter SAP ID: ");

    if (scanf("%lld", &sapid) != 1)
    {
        clearInput();
        printf("Invalid Input!\n");
        return;
    }

    int index = findStudent(sapid);

    if (index == -1)
    {
        printf("\nStudent not found!\n");
        return;
    }

    Student s = students[index];

    if (s.totalClasses == 0)
    {
        printf("\nNo classes conducted yet!\n");
        return;
    }

    double percentage =
        s.presentClasses * 100.0 / s.totalClasses;

    if (percentage >= MIN_ATTENDANCE)
    {
        printf("\nAttendance is already 75%% or above.\n");
        return;
    }

    int needed = 0;

    while (((s.presentClasses + needed) * 100.0) /
           (s.totalClasses + needed) < MIN_ATTENDANCE)
    {
        needed++;
    }

    printf("\nStudent: %s\n", s.name);
    printf("Current Attendance: %.2f%%\n", percentage);
    printf("Consecutive Classes Needed: %d\n", needed);
}

int main()
{
    int choice;

    do
    {
        printf("\n1.Add Student\n");
        printf("2.Mark Attendance\n");
        printf("3.Display Students\n");
        printf("4.Calculate Attendance\n");
        printf("5.Show Defaulters\n");
        printf("6.Search Student\n");
        printf("7.Attendance Report\n");
        printf("8.Classes Needed\n");
        printf("9.Exit\n");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1: addStudent(); break;
            case 2: markAttendance(); break;
            case 3: displayStudents(); break;
            case 4: calculateAttendance(); break;
            case 5: showDefaulters(); break;
            case 6: searchStudent(); break;
            case 7: attendanceReport(); break;
            case 8: classesNeeded(); break;
            case 9: printf("Thank You!\n"); break;
            default: printf("Invalid Choice!\n");
        }

    } while(choice != 9);

    return 0;
}