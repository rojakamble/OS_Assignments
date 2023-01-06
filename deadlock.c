#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *fun1();
void *fun2();
void *fun3();
pthread_mutex_t resource1, resource2, resource3;

int main()
{
    pthread_mutex_init(&resource1, NULL);
    pthread_mutex_init(&resource2, NULL);
    pthread_mutex_init(&resource3, NULL);
    pthread_t T1, T2, T3;
    pthread_create(&T1, NULL, fun1(), NULL);
    pthread_create(&T2, NULL, fun2(), NULL);
    pthread_create(&T3, NULL, fun3(), NULL);
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);
    pthread_join(T3, NULL);
    printf("Thread joined\n");
    return 0;
}
void *fun1()
{
    printf("T1 trying to acquire resource1\n");
    pthread_mutex_lock(&resource1);
    printf("T1 acquired resource1\n");
    sleep(1);
    printf("T1 trying to acquire resource3\n");
    pthread_mutex_lock(&resource3);
    printf("T1 acquired resource3\n");
    pthread_mutex_unlock(&resource1);
    return 0;

}
void *fun2()
{
    printf("T2 trying to acquire resource2\n");
    pthread_mutex_lock(&resource2);
    printf("T2 acquired resource2\n");
    sleep(1);
    printf("T2 trying to acquire resource1\n");
    pthread_mutex_lock(&resource1);
    printf("T2 acquired resource1\n");
    pthread_mutex_unlock(&resource2);
    return 0;
}
void *fun3()
{
    printf("T3 trying to acquire resource3\n");
    pthread_mutex_lock(&resource3);
    printf("T3 acquired resource3\n");
    sleep(1);
    printf("T3 trying to acquire resource2\n");
    pthread_mutex_lock(&resource2);
    printf("T3 acquired resource1\n");
    pthread_mutex_unlock(&resource3);
    return 0;
}