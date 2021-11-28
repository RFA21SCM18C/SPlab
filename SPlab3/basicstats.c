#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>




void sort(float arr[], int n) 
{ 
    int i, j, min; 
         
    for (i = 0; i < n - 1; i++) { 
        min = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min]) 
                min = j; 
                    
    float temp = arr[min]; 
    arr[min] = arr[i]; 
    arr[i] = temp; 
                 
    } 
} 

double cpt_mean(float arr[], int size)
{
    double sum = 0;
    int i = 0;

    while(i < size){
        
        sum = sum + arr[i];
        i++;
    }
   
    double mean = sum/size;
    return mean;
}


double cpt_median(float arr[], int size)
{
    double cpt_median = 0;
    
    if(size % 2 == 1)
    {       
        cpt_median = arr[size/2];
    }

    else
    {
        cpt_median = (arr[(size-1)/2] + arr[size/2])/2.0;
    }

    return cpt_median;
}


double stddev(float arr[], int size)
{
    int counter;
    float sum;
    double avg; 
    double stddev;

    counter = 0;
    avg = cpt_mean(arr, size); 
   
    while(counter < size) 
    {
      sum = sum + ((arr[counter] - avg) * (arr[counter] - avg));
      counter++;
    }
   
    stddev = (double) sqrt(sum / size);
    return stddev;

}

float * loaddata(char* targetfile, int* count, int* size)
{
    int n = 20;
      
    float* arr = (float*)malloc(n * sizeof(float)); 
    
    if (arr == NULL) { 
        printf("Error\n"); 
        exit(0); 
    } 
    
    int counter = 0;
    float data = 0;
    FILE *file;
    file = fopen(targetfile, "r"); 

    char Max[100];   
    while (fgets(Max, sizeof(Max), file))  
    {
        data = strtof(Max, NULL);
        arr[counter] = data;
        counter++; 
        

        if (counter == n)
        {
            
            n = n*2;
            float* temp = (float*)malloc(n * sizeof(float)); 

            if (temp == NULL) { 
                printf("Error\n"); 
                exit(0); 
            }


            memcpy(temp, arr, n * sizeof(float));
            free(arr);
            arr = (float*)malloc(n * sizeof(float)); 
            memcpy(arr, temp, n * sizeof(float));
            free(temp);
        }
    }
    if (feof(file))
    {
        fclose(file);
    } 
    *size = n;
    *count = counter;
    return arr;
}

int main(int argc, char *argv[])
{
    if ( argc == 2 ) 
    {
        int count = 0;
        int size = 20;
        float* arr;

        arr = loaddata(argv[1], &count, &size); 
        sort(arr, count); 

        printf("\nResults:\n");
        printf("--------\n");
        printf("Num Values:\t\t%d\n", count);
        printf("Mean:\t\t\t%lf\n", cpt_mean(arr, count));
        printf("Median:\t\t\t%f\n", cpt_median(arr, count));
        printf("stddev:\t\t\t%lf\n", stddev(arr, count));
        printf("Unused array capacity:\t%d\n\n", (size - count)); 
        
    }
    else
    {   
        printf("Enter the file name\n");
        return 0;
    }
}

