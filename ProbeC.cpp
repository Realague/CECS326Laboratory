#include"MessageQueue.h"
using namespace std;
int main(int num, char * args[]) {
    int rho = 3990;

    if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}
    MessageQueue probeC(0,args[1][0]);
	if (probeC.sendMessage(to_string(getpid()).c_str(),400,0)) {
		cout << "Error when sending pid from ProbeC" << endl;
	}
	string msg = "";

    while (true)
    {
        int gen = probeC.genRandNum(0,300000);
        if (gen < rho)
        {
		cout << "sending message from ProbeC" << endl;
		if (probeC.sendMessage(to_string(gen).c_str(),400,0)) {
			cout << "Error when sending message from ProbeC" << endl;
		}
        }
    }
    if (probeC.sendMessage("dead",400,0)) {
    	cout << "Error when sending message from ProbeC" << endl;
    }
    cout << "ProbC terminated" << endl;

}