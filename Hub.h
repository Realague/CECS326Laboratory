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
	int nbMsgReceived;
	int probeBPid;
	int probeCPid;
	bool hasProbeAExit;
	bool hasProbeBExit;
	bool hasProbeCExit;
	void killProbeB();
public:
    MessageQueue(int,char &);
    ~MessageQueue();
    bool sendMessage(std::string,int,int);
    bool recieveMessage(int,int,std::string&);
    int  genRandNum(int,int);
    int getNumberMessageReceived();
	bool shouldHubExit();
	bool hasProbeAExit();
	bool hasProbeBExit();
	bool hasProbeCExit();
	void setProbeAExit(bool);
	void setProbeBExit(bool);
	void setProbeCExit(bool);
};

MessageQueue::MessageQueue(int q,char & u)
: nbMsgReceived(0), hasProbeAExit(false), hasProbeBExit(false), hasProbeCExit(false) {
    srand(time(NULL));
    qid = msgget(ftok(".",u),q);

    if (hub.recieveMessage(300,0,pid)) {
	    cout << "Error recieving message in Hub from ProbeB" << endl;
    }
    cout << "Pid of probe B is #" << pid <<endl;
    this->probeBPid = stoi(pid);

    if ( hub.recieveMessage(400,0,pid)) {
    	cout << "Error recieving message in Hub from ProbeC" << endl;
    }
    cout << "pid of probe C  is #" << pid << endl;
    this->probeCPid = stoi(pid);
}

MessageQueue::~MessageQueue() {
	msgctl(qid,IPC_RMID,NULL);
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
    if (nbMsgReceived >= 10000) {
	killProbeB();
    }
    return res == -1;
}

int MessageQueue::genRandNum(int min, int max) {
    return rand();//per assignment requirements
}    

int MessageQueue::getNumberMessageReceived() {
	return nbMsgReceived;
}

void MessageQueue::killProbeB() {
	cout << force_patch(pid);
}

void MessageQueue::shouldHubExit(){
	return this->hasProbeAExit && this->hasProbeBExit && this->hasProbeCExit;
}

void MessageQueue::hasProbeAExit() {
	this->hasProbeAExit
}

void MessageQueue::hasProbeBExit() {
	this->hasProbeBExit
}

void MessageQueue::hasProbeCExit() {
	this->hasProbeCExit
}

void MessageQueue::setProbeAExit(bool boolean) {
	this->hasProbeAExit = boolean;
}

void MessageQueue::setProbeBExit(bool boolean) {
	this->hasProbeBExit = boolean;
}

void MessageQueue::setProbeCExit(bool boolean) {
	this->hasProbeCExit = boolean;
}