#include"MessageQueue.h"

using namespace std;

int main(int num, char * args[]) {
    int beta = 21000;

	if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}
    MessageQueue probeB(0,args[1][0]);
	if (probeB.sendMessage(to_string(getpid()).c_str(),300,0)) {
		cout << "Error when sending pid from ProbeB" << endl;
	}
	string msg = "";
    
    while (true)
    {
        int gen = probeB.genRandNum(0,100000);
        if (gen%beta == 0) {
            cout << "sending message from ProbeB" << endl;
            if (probeB.sendMessage(to_string(gen).c_str(),300,0)) {
                cout << "Error when sending message from ProbeB" << endl;
            }
        }

    }
    if (probeB.sendMessage("dead",300,0)) {
    	cout << "Error when sending message from ProbeB" << endl;
    }
    cout << "ProbB terminated" << endl;
}