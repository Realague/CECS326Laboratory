#include"MessageQueue.h"

using namespace std;

int main(int num, char * args[]) {
    int beta = 3990;
    int messagesSnt = 0;
    
	if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}
    MessageQueue probeB(0,args[1][0], false);
    
    while (messagesSnt < 50)
    {
        int num = probeB.genRandNum(0,100000);
        if (num%beta == 0 ) {
            cout << "sending message from ProbeB" << endl;
            if (probeB.sendMessage(to_string(num).c_str(),300,0)) {
                cout << "Error when sending message from ProbeB" << endl;
            }
            messagesSnt++;
        }

    }
    cout << "ProbB terminated" << endl;
}