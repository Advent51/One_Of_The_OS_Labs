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

char *fifo1="/root/temp4.txt";
pid_t pid2;
sem_t *sem1, *sem2, *sem3;
int ret;
float a,b,c,d,x1;

int main(int argc, char *argv[])
{
    unlink(fifo1);
    sem_unlink("/seeeeeem1");
    sem_unlink("/seeeeeem2");
    sem_unlink("/seeeeeem3");

    sem1 = sem_open ( "/seeeeeem1", O_CREAT, 0777, 1); //cout<<errno<<" PERVAYA sem1 created"<<endl; //ПОЧЕМУ?!?!?!? БЛ:!:!:!

    int fifa=mkfifo(fifo1, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH); //cout<<errno<<" PERVAYA fifo created"<<endl;

    switch (pid2=fork()) {
        case 0:
        execl("/root/build-untitled22-Desktop-Debug/untitled22",NULL);
        //execl("/root/untitled11/build-untitled33-Desktop-Debug/untitled33",NULL);
        break;
    default:
    {

        if ((fifa=open(fifo1, O_RDWR))<0) {cout<<"\nНевозможно open "; cout<<errno<<endl;}
        else
        {
            sleep(1);
            cout<<"\nVvedi a ";
            cin>>a;
            write(fifa,&a,4); //cout<<errno<<" write a"<<endl;
            close(fifa); //cout<<errno<<" close fifa"<<endl;
        }

        sem_post(sem1); //cout<<errno<<" PERVAYA sem1 post"<<endl;
        sem_getvalue(sem1,&ret);
        //cout<<ret<<" value DVA"<<endl;

        sem2 = sem_open ( "/seeeeeem2", 0); //cout<<errno<<" PERVAYA sem2 open"<<endl;
        sem3 = sem_open ( "/seeeeeem3", 0); //cout<<errno<<" PERVAYA sem3 open"<<endl;
        //sem_wait(sem2);
        //sem_wait(sem1);
        sem_wait(sem3); //cout<<errno<<" PERVAYA sem3 wait"<<endl;

        if ((fifa=open(fifo1, O_RDWR))<0) {cout<<"\nНевозможно open "; cout<<errno<<endl;}
        else
        {
            cout<<"\nVvedi b ";
            cin>>b;
            write(fifa,&b,4);
            //read(fifa,&c,4); cout<<errno<<" read b"<<endl;
            //cout<<c<<endl;
            close(fifa);
        }

        sem_post(sem1);
        //sem_wait(sem2);
        //sem_wait(sem1);
        sem_wait(sem3);

        /*if (pid1=fork()==0) execv("/root/Desktop/OS's Labs/Laba_3/Laba_3_NOTMAIN_1-build-desktop-Qt_4_8_2_in_PATH__System__Release/Laba_3_NOTMAIN_1",NULL);
    else if (pid1>0) cout<<"Fork failed";*/

        if ((fifa=open(fifo1, O_RDWR))<0) {cout<<"\nНевозможно open "; cout<<errno<<endl;}
        else
        {
            cout<<"\nVvedi c ";
            cin>>c;
            write(fifa,&c,4);
            //read(fifa,&c,4);
            //cout<<c<<endl;
            close(fifa);
        }

        sem_post(sem1);
        sem_wait(sem2);
        sem_wait(sem1);

        x1=(-b-sqrt((b*b)-(4*a*c)))/(2*a);
        cout<<"X1:Результат: x1="<<x1;
        cout<<"\nX1:Программа подсчёта х1 завершила работу\n";

        unlink(fifo1);
        sem_unlink("/sem1"); cout<<"deleting semaphores"<<endl;
        sem_unlink("/sem2");
        sem_unlink("/sem3");
        cout<<"\nFINISH!!!";
        break;}

    case -1: cout<<"Fork failed"; break;}

    return 0;
}
