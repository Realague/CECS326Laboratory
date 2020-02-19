#include<sys/ipc.h>
#include<sys/msg.h>
#include<iostream>
#include"Message.h"
using namespace std;

int main() {
    int qid = msgget(ftok(".",'u'),IPC_EXCL|IPC_CREAT|0600);
    Message buf;
    int size = sizeof(buf) - sizeof(long);
    msgrcv(qid,(struct Message *)&buf,size, 117, 0);
    cout << "Hub has recieved message"<<endl;
    cout << "message: "<< buf.greeting << endl;
    strcpy(buf.greeting,"Audios");
    cout << "Hub sends reply" << endl;
    msgsnd(qid,(struct Message *)&buf,size,0);
    cout << "Hub shutting down ..." << endl;
    
    msgrcv(qid,(struct Message *)&buf, size, -112, 0);
    msgrcv(qid,(struct Message *)&buf,size,0,0);

    msgrcv(qid,(struct Message *)&buf, size, 117, 0);
    
    msgctl(qid,IPC_RMID,NULL);
    exit(0);
}