#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/io.h>
#include <fcntl.h>
#include <errno.h>
#include "semaphore.h"
#include "math.h"

using namespace std;

float a,b,c,d;
sem_t *sem1, *sem2, *sem3, *sem21, *sem22;
pid_t pid1;
char *fifo1="/root/temp4.txt";
char *fifo2="/root/temp5.txt";
int fifa, ret;
float x2;

int main(int argc, char *argv[])
{
    unlink(fifo2);
    //sem_unlink("/seeeeeem21");
    //sleep(1);
    sem1 = sem_open ( "/seeeeeem1", 0); //cout<<errno<<" VTORAYA sem1 opened"<<endl;
    //sem_getvalue(sem1,&ret); //ПОЧЕМУУУУУУУУУУУУУУУУУУУУУУУУУ
    //cout<<ret<<" VTORAYA value sem1"<<endl;
    sem2 = sem_open ( "/seeeeeem2", O_CREAT, 0777, 0);//cout<<errno<<" VTORAYA sem2 created"<<endl;
    //sem_getvalue(sem2,&ret); //ПОЧЕМУУУУУУУУУУУУУУУУУУУУУУУУУ
    //cout<<ret<<" VTORAYA value sem2"<<endl;
    sem3 = sem_open ( "/seeeeeem3", O_CREAT, 0777, 0); //cout<<errno<<" VTORAYA sem3 created"<<endl;
    {

    fprintf(stdout,"\nProgram-helper 1 started\n");
    fflush(stdout);
    sem_wait(sem1); //cout<<errno<<" VTORAYA sem1 wait"<<endl;

    cout<<"\nHello! It's a Program-helper 1!";
    if ((fifa=open(fifo1, O_RDONLY))<0) cout<<"\nNEVOZMOJNO OTKRIT";
    else
    {
        read(fifa,&a,4); //cout<<endl; cout<<errno<<"Program-helper 1 otkrila fifu"<<endl;
        cout<<"\nProgram-helper 1 SCHITALA a=";
        cout<<a<<endl;
        close(fifa);
    }

    sem_post(sem3);
    sem_wait(sem1);

    if ((fifa=open(fifo1, O_RDONLY))<0) cout<<"\nNEVOZMOJNO OTKRIT";
    else
    {
        read(fifa,&b,4);
        cout<<"\nProgram-helper 1 SCHITALA b=";
        cout<<b<<endl;
        close(fifa);
    }

    //sem_post(sem21);
    //sem_wait(sem22);
    sem_post(sem3);
    sem_post(sem1);
    //sem_post(sem2);

    sem_wait(sem1);

    if ((fifa=open(fifo1, O_RDONLY))<0) cout<<"\nNEVOZMOJNO OTKRIT";
    else
    {
        read(fifa,&c,4);
        cout<<"\nProgram-helper 1 SCHITALA c=";
        cout<<c<<endl;
        close(fifa);
    }

    x2=(-b+sqrt((b*b)-(4*a*c)))/(2*a);
    cout<<"X2:Результат: x2="<<x2;
    cout<<"\nX2:Программа подсчёта х1 завершила работу\n";

    sem_post(sem1);
    sem_post(sem2);

    }

    return 0;
}
