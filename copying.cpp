#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

using namespace std;

int main(int argc, char**)
{
    int fd1, fd2;
    char buf[1];
    int n;
    int i;
    int size = 1024;
    int count = 0;
    

    struct timeval start, end;
    double time_taken;

    ofstream MyFile("file1.txt");


    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_WRONLY | O_CREAT, 0644);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("open");
        exit(1);
    }

    while (size <= 134217728)
    {
        gettimeofday(&start, NULL);
        while ((n = read(fd1, buf, 1)) > 0)
        {
            write(fd2, buf, n);
            count++;
            if (count == size)
            {
                break;
            }
        }
        gettimeofday(&end, NULL);
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        cout << "Time taken for " << size << " bytes: " << time_taken << " seconds" << endl;
        size = size * 2;
        count = 0;
    }

    close(fd1);
    close(fd2);
    return 0;
}