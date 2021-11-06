#include <stdio.h>
#include <string.h>
#include "readfile.h"
#define MAXNAME 64

extern FILE *file; 
struct employee  
{
    char FName[MAXNAME];
    char LName[MAXNAME];
    int empID;
    int salary;
};
struct employee db[1000]; 
int counter = 0; 
char term; 

//print the DB         
void PrintDB (struct employee arr[], int arr_size)
{
    int i = 0;

    printf("\nName\t\t\t\tSALARY\tID\n");
    printf("---------------------------------------------------------------\n");
    while(i < arr_size)
    {
        printf("%-10s\t%-10s\t%d\t%d\n", arr[i].FName,arr[i].LName,arr[i].salary, arr[i].empID);
        i+=1;
    }
    printf("---------------------------------------------------------------\n");
    printf(" Number of Employees (%d)\n", arr_size);
}


//lookip employee by ID

int searchID (struct employee arr[], int num, int key)
{
    for (int i = 0; i < num; i++)
    {
        if (arr[i].empID == key)
        {
            return i;
        }
    }
    return -1;
}



//lookup employee by last name
int searchLName (struct employee arr[], int num, char* ln)
{
    
    for (int i = 0; i < num; i++)
    {
        if (strcmp(arr[i].LName, ln) == 0)
        {
            return i;
        }
    }
    return -1;
}

//add an employee
int addem(struct employee arr[])
{
    char newFName[MAXNAME];
    char newLName[MAXNAME];
    int newSalary;
    int select;

    printf("\nEnter the first name of the employee: ");
    scanf("%s", newFName);
    if (strlen(newFName) > 64)
    {
        printf("Out of range.\n");
        return 0;
    }
    printf("Enter the last name of the employee: ");
    scanf("%s", newLName);
    if (strlen(newFName) > 64)
    {
        printf("Out of range.\n");
        return 0;
    }
    printf("Enter employee's salary between $30000 and $150000: ");
    scanf("%d", &newSalary);
    printf("\nDo you want to add the following employee to the DB?\n");
    printf("\t%s %s, \tSalary: %d\n", newFName, newLName, newSalary);
    printf("\nEnter 1 for yes, 0 for no: ");
    scanf("%d", &select);
    

    if (select == 1)
    {
        if ((newSalary >= 30000) && (newSalary <= 150000)){

        strcpy(db[counter].FName, newFName);
        strcpy(db[counter].LName, newLName);
        db[counter].salary = newSalary;
        db[counter].empID = db[counter -1].empID + 1;
        counter++;
        printf("employee add complete\n");
    }
    else
    {
        printf("Salary is out of range, please check it.\n");
    }
    }
    else if (select == 0)
    {
        printf("Adding canceled.\n");
    }

    return 1;
}


void createDB(char* targetfile)
{
    if (open_file(targetfile) == 0)
    {
        char buffer[135];
        int a;
        while (fgets(buffer, sizeof(buffer), file)) 
        {
            a = read_int(buffer, 1, &db[counter].empID);
            a = read_int(buffer, 2, &db[counter].salary);
            a = read_string(buffer, 1, &db[counter].FName);
            a = read_string(buffer, 2, &db[counter].LName);
            counter += 1; 
        }

        if (feof(file)) 
        {
            close_file(file);
        } 
    }
}



void sort(struct employee arr[], int n) 
{ 
    int i, j, min; 
  
     
    for (i = 0; i < n - 1; i++) { 
  
        
        min = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j].empID < arr[min].empID) 
                min = j; 


        struct employee temp = arr[min]; 
        arr[min]= arr[i]; 
        arr[i] = temp; 
        
    } 
} 

int main(int argc, char *argv[])
{
    if ( argc != 2 ) 
    {
        
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        createDB(argv[1]);        
        sort(db, counter); 

        int enter; 
        int x = 0; 
        
        while (1) {
            printf("\nEmployee DB Menu:\n");
            printf("----------------------------------\n");
            printf("\t(1) Print the Database\n");
            printf("\t(2) Lookup by ID\n");
            printf("\t(3) Lookup by Last Name\n");
            printf("\t(4) Add an Employee\n");
            printf("\t(5) Quit\n");
            printf("----------------------------------\n");
            printf("Enter your choice: ");

            scanf("%d", &enter); 

        
            if(enter == 1){

                PrintDB(db, counter);

            }

            else if(enter == 2){

                int lookforID; 
                    printf("\nEnter a 6 digit employee id: ");
                    scanf("%d", & lookforID);
                    x = searchID(db, counter, lookforID);
                    if (x == -1)
                    {
                        printf("\nEmployee with ID '%d' not found\n",lookforID);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("---------------------------------------------------------------\n");
                        printf("%-10s\t%-10s\t%d\t%d\n", db[x].FName,db[x].LName,db[x].salary, db[x].empID);
                        printf("---------------------------------------------------------------\n");
                    }

            }
            
            else if(enter == 3){

                char name_search[MAXNAME];                
                    printf("\nEnter Employee's last name (no extra spaces): ");
                    scanf("%s", name_search); 
                    x = searchLName(db, counter, name_search);
                    if (x == -1)
                    {
                        printf("\nEmployee with last name '%s' not found\n", name_search);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("---------------------------------------------------------------\n");
                        printf("%-10s\t%-10s\t%d\t%d\n", db[x].FName,db[x].LName,db[x].salary, db[x].empID);
                        printf("---------------------------------------------------------------\n");
                    }  

            }

            else if(enter == 4){

                addem(db);

            }

            else if(enter == 5){

                printf("\n goodbye! \n");      
                return 0;

            }
            else{

                printf( "\n Error.\n" );
                continue;


            }
                
            }
        }
    }
