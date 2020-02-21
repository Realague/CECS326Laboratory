#include<sys/ipc.h>
#include<sys/msg.h>
#include<iostream>
#include<string>
#include"Message.h"

class MessageQueue
{
private:
    int qid;
public:
    MessageQueue(int);
    ~MessageQueue();
    bool sendMessage(std::string,int,int);
    bool recieveMessage(int,int);
};

MessageQueue::MessageQueue(int q) {
    qid = msgget(ftok(".",'r'),q);
}

MessageQueue::~MessageQueue() {
    //msgctl(qid,IPC_RMID,NULL);
}

bool MessageQueue::sendMessage(std::string msgbdy, int mtype ,int flag) {
    if (flag == 0 || flag == IPC_NOWAIT) {
        Message buf;
        strcpy(buf.greeting,msgbdy.c_str());
        buf.mtype = mtype;
        int size = sizeof(buf) - sizeof(long);
        int res = msgsnd(qid,(struct Message *)&buf,size,flag);
        if (res < 0) {
            if (errno == EAGAIN) {
                std::cout << "No space in queue for message..." << std::endl;
            } else if (errno == EIDRM) {
                std::cout << "Queue does not exist for qid: "<<qid<<std::endl;
            }
            return true;
        }
    }
    return false;
}

bool MessageQueue::recieveMessage(int mtype,int flag) {
    Message buf;
    int size = sizeof(buf) - sizeof(long);
    buf.greeting[0] = 0;
    int res = msgrcv(qid,(struct Message *)&buf,size, mtype, 0);
    std::cout << buf.mtype << std::endl;
    if (res <= 0) {
        switch (errno)
        {
        case ENOMSG:
            std::cout << "No message in queue " << std::endl;
            break;
        case EINVAL:
            std::cout << "msgqid was invalid, or msgsz was less than 0" << std::endl;
        default:
            std:: cout << "Unexpected Error occured" << std::endl;
            break;
        }





        // if (errno == ENOMSG) {
            
        // } else if (errno == EIDRM) {
        //     std::cout << "No QUEUE" << std::endl;
        // } else if (errno == EINTR) {
        //     std::cout << "caught signal" << std::endl;
        // } else if (errno == E2BIG) {
        //     std::cout << "Message is too large" << std::endl;
        // } else {
            
        // }
        // std::cout << "Error in recieved" << std::endl;
    } else {
        std::cout << "Recieving Message on " << buf.mtype<<": \n"<< buf.greeting << std::endl;
    }
    return size == -1;
}