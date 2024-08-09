#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int reg_no;
    int roll;
    char name[50];
    float marks1;
    float marks2;
    float marks3;
    float final;
    
};

void add_record() {
    struct student s;
    FILE *fp;
    fp = fopen("students.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }
    printf("Enter reg. number: ");
    scanf("%d", &s.reg_no);
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter CA1 marks: ");
    scanf("%f", &s.marks1);
    printf("Enter CA2 marks: ");
    scanf("%f", &s.marks2);
    printf("Enter CA3 marks: ");
    scanf("%f", &s.marks3);
    fwrite(&s, sizeof(s), 1, fp);
    printf("Record added successfully");
    fclose(fp);
}

void modify_record() {
    int roll;
    struct student s;
    FILE *fp;
    fp = fopen("students.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }
    printf("\nEnter roll number to modify: ");
    scanf("%d", &roll);
    while (fread(&s,sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new CA1 marks: ");
            scanf("%f", &s.marks1);
            printf("Enter new CA2 marks: ");
            scanf("%f", &s.marks2);
            printf("Enter new CA3 marks: ");
            scanf("%f", &s.marks3); 
            fseek(fp,-sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Record modified successfully");
            fclose(fp);
            return;
        }
    }
    printf("Record not found");
    fclose(fp);
}

void delete_record() {
    int roll;
    struct student s;
    FILE *fp, *temp;
    fp = fopen("students.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }
    temp = fopen("temp.txt", "wb");
    if (temp == NULL) {
        printf("Error opening file");
        fclose(fp);
        return;
    }
    printf("\nEnter roll number to delete: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");
    printf("Record deleted successfully");
}

void search_record() {
    int roll;
    struct student s;
    FILE *fp;
    fp = fopen("students.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }
    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
        	printf("\nReg. number: %d", s.reg_no);
            printf("\nRoll number: %d", s.roll);
            printf("\nName: %s", s.name);
            printf("\nCA1 Marks: %.2f", s.marks1);
            printf("\nCA2 Marks: %.2f", s.marks2);
            printf("\nCA3 Marks: %.2f", s.marks3);
            fclose(fp);
            return;
        }
    }
    printf("Record not found");
    fclose(fp);
}

void display_records() {
    struct student s;
    //float average;
    FILE *fp;
    fp = fopen("students.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }
printf("\n*************** CSE101 C Language Subject Marks Record of Section K22DA *****************\n");
printf("%-10s%-10s%-20s%-10s%-13s%-13s%-10s\n","reg.no", "Roll","Name", "CA1_Marks","CA2_Marks","CA3_Marks","Average of Best of two CA ");
while (fread(&s, sizeof(s), 1, fp) == 1) {
	if (s.marks1 >= s.marks2 && s.marks1 >= s.marks3) {
    s.final = (s.marks1 + (s.marks2 > s.marks3 ? s.marks2 : s.marks3)) / 2;
  } else if (s.marks2  >= s.marks1 && s.marks2 >=s.marks3) {
    s.final = (s.marks2 + (s.marks1 > s.marks3 ? s.marks1 : s.marks3)) / 2;
  } else {
    s.final = (s.marks3 + (s.marks1 > s.marks2 ? s.marks1 : s.marks2)) / 2;
  }
  
printf("%-10d%-10d%-20s%-10.2f%-13.2f%-13.2f%-10.2f\n",s.reg_no, s.roll, s.name, s.marks1,s.marks2,s.marks3,s.final);
}
fclose(fp);
}

int main() {
int choice;
do {
printf("\n***********************Welcome to CA Evaluator System *************************:\n");
printf("1. Add record\n");
printf("2. Modify record\n");
printf("3. Delete record\n");
printf("4. Search record\n");
printf("5. Display records\n");
printf("6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:	
add_record();
break;
case 2:
modify_record();
break;
case 3:
delete_record();
break;
case 4:
search_record();
break;
case 5:
display_records();
break;
case 6:
printf("Exiting...");
break;
default:
printf("Invalid choice");
}
} while (choice != 6);
return 0;
}
