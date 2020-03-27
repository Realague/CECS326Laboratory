#include<sys/ipc.h>
#include<sys/msg.h>
#include<iostream>
#include<string>
#include<random>
#include<ctime>
#include<sys/types.h>
#include<unistd.h>
#include"Message.h"
#include "force_patch.h"
//Hub datatype -> could have been derived from MessageQueue
class Hub
{
private:
    //store queue,probeB,and probeC ids 
	int qid;
	int nbMsgReceived;
	int probeBPid;
	int probeCPid;
    //probe status variables -> would be better with a enum for probe status
	bool hasProbeAExit;
	bool hasProbeBExit;
	bool hasProbeCExit;
    //method to run force_patch
	void killProbeB();
public:
    Hub(int,char &);
    ~Hub();
    //wrapper methods for msgsnd and msgrcv
    bool sendMessage(std::string,int,int);
    bool recieveMessage(int,int,std::string&);
    int  genRandNum();
    int getNumberMessageReceived();
	bool shouldHubExit();
	bool hasProbeAExited();
	bool hasProbeBExited();
	bool hasProbeCExited();
	void setProbeAExit(bool);
	void setProbeBExit(bool);
	void setProbeCExit(bool);
};

Hub::Hub(int q,char & u)
: nbMsgReceived(0), hasProbeAExit(false), hasProbeBExit(false), hasProbeCExit(false) {
    srand(time(NULL));
    //init with argument project_id
    qid = msgget(ftok(".",u),q);
    std::string pid = "";

    if (this->recieveMessage(300,0,pid)) {
	    std::cout << "Error recieving message in Hub from ProbeB" << std::endl;
    }
    std::cout << "Pid of probe B is #" << pid << std::endl;
    this->probeBPid = stoi(pid);

    if (this->recieveMessage(400,0,pid)) {
    	std::cout << "Error recieving message in Hub from ProbeC" << std::endl;
    }
    std::cout << "pid of probe C  is #" << pid << std::endl;
    this->probeCPid = stoi(pid);
}

Hub::~Hub() {
	msgctl(qid,IPC_RMID,NULL);
}

//returns true if there is a error sending the message
bool Hub::sendMessage(std::string msgbdy, int mtype ,int flag) {
    if (flag == 0) {
        Message buf;
        msgbdy = std::to_string(getpid()) + ": " + msgbdy;
        strcpy(buf.greeting,msgbdy.c_str());
        buf.mtype = mtype;
        int size = sizeof(buf) - sizeof(long);
        int res = msgsnd(qid,(struct Message *)&buf,size,flag);
        //res will be -1 if there was an error
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

//returns true if error recieving message
bool Hub::recieveMessage(int mtype,int flag,std::string &pid) {
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
    } else {//increment # of messages get pid of sender
    	nbMsgReceived++;
        pid = std::string(buf.greeting,5);
        std::cout << "Message from pid# " << pid <<": \n"<< buf.greeting << std::endl;
    }
    if (nbMsgReceived >= 10000) {
	killProbeB();
    }
    return res == -1;
}

int Hub::genRandNum() {
    return rand();//per assignment requirements
}    

int Hub::getNumberMessageReceived() {
	return nbMsgReceived;
}

void Hub::killProbeB() {
	std::cout << force_patch(probeBPid) << std::endl;
}

bool Hub::shouldHubExit(){
    std::cout << this->hasProbeAExit && this->hasProbeBExit && this->hasProbeCExit << '\n';
	return this->hasProbeAExit && this->hasProbeBExit && this->hasProbeCExit;
}

bool Hub::hasProbeAExited() {
	return this->hasProbeAExit;
}

bool Hub::hasProbeBExited() {
	return this->hasProbeBExit;
}

bool Hub::hasProbeCExited() {
	return this->hasProbeCExit;
}

void Hub::setProbeAExit(bool boolean) {
	this->hasProbeAExit = boolean;
}

void Hub::setProbeBExit(bool boolean) {
	this->hasProbeBExit = boolean;
}

void Hub::setProbeCExit(bool boolean) {
	this->hasProbeCExit = boolean;
}