#include"MessageQueue.h"

using namespace std;

int main(int num, char * args[]) {
	if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}
    MessageQueue probeB(0,args[1][0], false);
    
    for (int i = 0; i < 5; i++)
    {
	    cout << "sending message from ProbeB" << endl;
        if (probeB.sendMessage("MProbeB",300,0)) {
		cout << "Error when sending message from ProbeB" << endl;
        }
    }
}