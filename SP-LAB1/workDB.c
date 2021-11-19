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
void swap(struct employee* xp, struct employee* yp) 
{ 
    struct employee temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
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
void delem(int t)
{
    int i;
    int target_ID;

    printf("\nPlease enter an employee ID: ");
    scanf("%d", &target_ID);          
    t = searchID(db, counter, target_ID);
    if (t == -1)
        {
            printf("\nUser with employee ID '%d' not found\n", target_ID);
        }
    else
        {
            i = counter - 1;
            swap(&db[t], &db[i]);
            counter = counter - 1;
            sort(db,counter);
            }
    
};
   
int upemp(struct employee arr[], int x)
{
    int target_ID;

    printf("\nPlease enter an employee ID: ");
    scanf("%d", &target_ID);          
    x = searchID(db, counter, target_ID);
    if (x == -1){
        printf("\nUser with employee ID '%d' not found\n", target_ID);
    }
    else{
        
    int enter;
    char fname[MAXNAME];
    char lname[MAXNAME];
    int Newsalary;
    int Newid;
    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    printf("%-10s\t%-10s\t%d\t%d\n", arr[x].FName, arr[x].LName, arr[x].salary, arr[x].empID);
    printf("----------------------------------------------\n");
    printf("\nWhat data would you like to change?\n");
    printf("\t(1) First Name\n");
    printf("\t(2) Last Name\n");
    printf("\t(3) Salary\n");
    printf("\t(4) Employee ID\n");
    printf("\t(5) All of Data\n");
    printf("Enter your choice: ");
    scanf("%d", &enter); 

    if (enter == 1)
    {
        printf("\n Please enter the new first name: "); 
        scanf("%s", fname);      

        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        printf("%-10s\t%-10s\t%d\t%d\n", fname, arr[x].LName, arr[x].salary, arr[x].empID);
        printf("----------------------------------------------\n");
        printf("\nUpdate Complete.\n");
        strcpy(arr[x].FName, fname);
    }
    
    else if (enter == 2)
    {
        printf("\n Please enter the updated last name: "); 
        scanf("%s", lname);      

        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        printf("%-10s\t%-10s\t%d\t%d\n", arr[x].FName, lname, arr[x].salary, arr[x].empID);
        printf("----------------------------------------------\n");
        printf("\nUpdate Complete.\n");
        strcpy(arr[x].LName, lname);
    }

    else if (enter == 3)
    {
        printf("\n Please enter the updated salary: "); 
        scanf("%d", &Newsalary);      

        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        printf("%-10s\t%-10s\t%d\t%d\n", arr[x].FName, arr[x].LName, Newsalary, arr[x].empID);
        printf("----------------------------------------------\n");
        printf("\nUpdate Complete.\n");
        arr[x].salary = Newsalary;
    }

    else if (enter == 4)
    {
        printf("\n Please enter the updated employee ID: "); 
        scanf("%d", &Newid);      

        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        printf("%-10s\t%-10s\t%d\t%d\n", arr[x].FName, arr[x].LName, arr[x].salary, Newid);
        printf("----------------------------------------------\n");
        printf("\nUpdate Complete.\n");
        arr[x].empID = Newid;
        sort(arr, counter);      
                
    }
    else if (enter == 5)
    {
        printf("\n Please enter the updated first name: "); 
        scanf("%s", fname);      
        printf("\n Please enter the updated last name: "); 
        scanf("%s", lname);
        printf("\n Please enter the updated salary: "); 
        scanf("%d", &Newsalary);
        printf("\n Please enter the updated employee ID: "); 
        scanf("%d", &Newid); 
        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        printf("%-10s\t%-10s\t%d\t%d\n", fname, lname, Newsalary, Newid);
        printf("----------------------------------------------\n");


        printf("\nUpdate Complete.\n");
        strcpy(arr[x].FName, fname);
        strcpy(arr[x].LName, lname);
        arr[x].salary = Newsalary;
        arr[x].empID = Newid;
        sort(arr, counter);       
                
    }
    else{

        printf( "\n Error.\n" );   
    }

    }
};
    
void highsal(int m) 
{
    struct employee sal[1000];
    int i;
    int j;
    int min;

    printf("\nEnter a value M: ");
    scanf("%d", &m);

    memcpy(&sal, &db, sizeof(sal));
    for (i = 0; i < counter - 1; i++) {   
        min = i; 

        for (j = i + 1; j < counter; j++) 
            if (sal[j].salary < sal[min].salary) 
                min = j; 

        struct employee temp = sal[min]; 
        sal[min]= sal[i]; 
        sal[i] = temp;
    };
    PrintDB(sal, m);
};

void LNameSearch(struct employee arr[], int m, char* lname) {

    struct employee ln[1000];
    int n = 0;
    int i = 0;
    printf("\nPlease enter  last name: ");
    scanf("%s", lname);
    while (i < m)
    {
        if (strcasecmp(arr[i].LName, lname) == 0)
        {
            strcpy(ln[n].FName, arr[i].FName);
            strcpy(ln[n].LName, arr[i].LName);
            ln[n].salary = arr[i].salary;
            ln[n].empID = arr[i].empID;
            n++;
        }
        i++;
    }

    PrintDB(ln, n);
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
            printf("\t(6) Remove an Employee\n");
            printf("\t(7) Update an employee's Information\n");
            printf("\t(8) Print the M employees with the highest salaries\n");
            printf("\t(9) Find all employees with matching last name\n");
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
             else if(enter == 6){

                int n;

                delem(n);

            }
            else if(enter == 7){

                int n;

                upemp(db,n);

            }
            else if(enter == 8){

                int m;

                highsal(m);

            }
            else if(enter == 9){

                char target_name[MAXNAME];

                LNameSearch(db,counter,target_name);

            }                   
            else{

                printf( "\n Error.\n" );
                continue;


            }
                
            }
        }
    }
