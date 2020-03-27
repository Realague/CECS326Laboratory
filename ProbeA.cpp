#include"MessageQueue.h"

using namespace std;

int main(int num, char *args[]) {
    int alpha = 11997;

	if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}

    MessageQueue probeA(0,args[1][0]);
	string msg = "";
    
    while (true)
    {
        int gen = probeA.genRandNum(0,10000000);
        if (gen%alpha == 0 ) {
            if (probeA.sendMessage(to_string(gen).c_str(), 200,0)) {
                cout << "Error when sending message from ProbeA" << endl;
            }
            if (probeA.recieveMessage(100, 0,msg)) {
                cout << "error recieving message in ProbeA" << endl;
            }
        } else if (gen < 50)
        {
        	cout << "ProbA terminated" << endl;
            break;
        }
        
        //cout << "A rand Num: " << probeA.genRandNum(0,1000000) << endl;

    }
    if (probeA.sendMessage("dead", 200,0)) {
    	cout << "Error when sending message from ProbeA" << endl;
    }
    cout << "Probe A terminated" << endl;
   

    return 0;
}