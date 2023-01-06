#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int arr[] = {90, 81, 78, 95, 79, 72, 85};
int numCount = sizeof(arr) / sizeof(arr[0]);
float avg, max, min, median, std_dev;

void *avg_runner(void *arg)
{

    int sum = 0;
    for (int i = 0; i < numCount; i++)
    {
        sum += arr[i];
    }
    avg = (float)sum / (float)numCount;

    printf("The sum is: %d\n", sum);
    printf("The average is: %2f\n", avg);
}

void *min_runner(void *arg)
{

    for (int i = 0; i < numCount; i++)
    {
        if (i == 0)
        {
            min = arr[i];
        }
        else if (min > arr[i])
        {
            min = arr[i];
        }
    }

    printf("The minimum is: %f\n", min);
}

void *max_runner(void *arg)
{

    for (int i = 0; i < numCount; i++)
    {
        if (i == 0)
        {
            max = arr[i];
        }
        else if (max < arr[i])
        {
            max = arr[i];
        }
    }

    printf("The maximum is: %f\n", max);
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void *median_runner(void *arg)
{

    qsort(arr, numCount, sizeof(int), cmpfunc);

    for (int i = 0; i < numCount; i++)
    {
        printf("\n The sorted is: %d\n", arr[i]);
    }

    printf("\n num count is: %d", numCount);

    if (numCount % 2 == 0)
    {

        // even inputs
        printf("\n even \n");
        int mid_i = numCount / 2;
        int mid_sec = mid_i - 1;
        int med = (arr[mid_i] + arr[mid_sec]) / 2;
        printf("\n The median is: %d \n", med);
    }

    else if (numCount % 2 != 0)
    {
        // odd inputs
        int mid_i = numCount / 2;
        printf("\n Median is: %d", arr[mid_i]);
    }
    return 0;
}

void *std_dev_runner(void *arg)
{

    float mean, deviation, sumsqr, variance, stddeviation;

    int sum = 0;
    for (int i = 0; i < numCount; i++)
    {
        printf("\n num is: %d", arr[i]);
        sum += arr[i];
    }
    printf("\n Sum is: %d", sum);
    mean = (float)sum / (float)numCount;
    printf("\n Mean is: %f", mean);

    for (int i = 0; i < numCount; i++)
    {

        deviation = arr[i] - mean;
        printf("\n deviation is: %f", deviation);
        sumsqr += deviation * deviation;
        printf("\n sumsqr is: %f", sumsqr);
    }

    variance = (float)sumsqr / (float)numCount;
    printf("\n variance is: %f", variance);
    stddeviation = sqrt(variance);

    printf("\n The std_dev is: %f", stddeviation);
    printf("\n");
}

int main(int argc, char **argv)
{
    printf("Start of program\n");

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;

    pthread_create(&thread1, NULL, &avg_runner, NULL);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, &min_runner, NULL);
    pthread_join(thread2, NULL);
    pthread_create(&thread3, NULL, &max_runner, NULL);
    pthread_join(thread3, NULL);
    pthread_create(&thread4, NULL, &median_runner, NULL);
    pthread_join(thread4, NULL);
    pthread_create(&thread5, NULL, &std_dev_runner, NULL);
    pthread_join(thread5, NULL);

    return 0;
}