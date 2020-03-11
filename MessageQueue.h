#include<sys/ipc.h>
#include<sys/msg.h>
#include<iostream>
#include<string>
#include<random>
#include<ctime>
#include<sys/types.h>
#include<unistd.h>
#include"Message.h"

class MessageQueue
{
private:
    int qid;
    bool	isHub;
    int nbMsgReceived;
public:
    MessageQueue(int,char &, bool);
    ~MessageQueue();
    bool sendMessage(std::string,int,int);
    bool recieveMessage(int,int,std::string&);
    int  genRandNum(int,int);
    int getNumberMessageReceived();
};

MessageQueue::MessageQueue(int q,char & u, bool isHub)
: isHub(isHub), nbMsgReceived(0) {
    srand(time(NULL));
    qid = msgget(ftok(".",u),q);
}

MessageQueue::~MessageQueue() {
	if (isHub) {
		msgctl(qid,IPC_RMID,NULL);
	}
}

//returns true if there is a error sending the message
bool MessageQueue::sendMessage(std::string msgbdy, int mtype ,int flag) {
    if (flag == 0) {
        Message buf;
        msgbdy = std::to_string(getpid()) + ": " + msgbdy;
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

bool MessageQueue::recieveMessage(int mtype,int flag,std::string &pid) {
    Message buf;
    int size = sizeof(buf) - sizeof(long);
    buf.greeting[0] = 0;
    int res = msgrcv(qid,(struct Message *)&buf,size, mtype, 0);
    //std::cout << buf.mtype << std::endl;
    if (res <= 0) {
        switch (errno)
        {
        case ENOMSG:
            std::cout << "No message in queue " << std::endl;
            break;
        case EINVAL:
            std::cout << "msgqid was invalid, or msgsz was less than 0" << std::endl;
        case EIDRM:
            std::cout << "No QUEUE" << std::endl;
            break;
        case EINTR:
            std::cout << "caught signal" << std::endl;
        default:
            std:: cout << "Unexpected Error occured" << std::endl;
            break;
        }
    } else {
    	nbMsgReceived++;
        pid = std::string(buf.greeting,4);
        std::cout << "Message from pid# " << pid <<": \n"<< buf.greeting << std::endl;
    }
    return res == -1;
}

int MessageQueue::genRandNum(int min, int max) {
    return rand();//per assignment requirements
}    

int MessageQueue::getNumberMessageReceived() {
	return nbMsgReceived;
}