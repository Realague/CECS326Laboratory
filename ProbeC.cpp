#include"MessageQueue.h"
using namespace std;
int main(int num, char * args[]) {
    int rho = 3990;
    int messageSnt = 0;

    if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}
    MessageQueue probeC(0,args[1][0], false);

    while (messageSnt < 5)
    {
        int gen = probeC.genRandNum(0,300000);
        if (gen < rho)
        {
		cout << "sending message from ProbeC" << endl;
		if (probeC.sendMessage(to_string(gen).c_str(),400,0)) {
			cout << "Error when sending message from ProbeC" << endl;
		}
		messageSnt++;
        }
        
    }
    cout << "ProbB terminated" << endl;

}