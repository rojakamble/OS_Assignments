#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<cstdlib>
#include<cstring>
#include<sys/wait.h>
#include <signal.h>

using namespace std;


int main()

{
int id;
id = fork(); //a) Fork sysrtem call
pid_t cpid;

    if (id == 0)
{
        cout<<"\nHello parent your process id is : "<<getpid(); //b) getpid system call
        cout<<"\nHello child  your proecess id is : "<<getppid(); //c) getppid system call
	    sleep(5);
	    kill( getpid(),SIGSEGV ); //d) kill system call
	    exit(0); //e) exit system call
	    cout<<"\n"<<endl;
	
}
    else
    {
        cpid = wait(NULL);//f) wait system
	cout<<"\nAfter waiting parent process id is : "<<getpid();
        cout<<"\nAfter waiting child proecess id is : "<<id;
	
    }
 
    execl("/bin/echo","echo","Hello all this program is using all system calls",NULL);//g) exec system call
    return 0;
}
