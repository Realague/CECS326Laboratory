#include"MessageQueue.h"
#include"force_patch.h"

using namespace std;

int main(int num, char * args[]) {

    if (num < 2) {
    	std::cout << "Error: Wrong argument" << std::endl;
    	return 84;
    }
    MessageQueue Hub(IPC_EXCL|IPC_CREAT|0600,args[1][0], true);
    string pid = "";
    bool biskill = false;

	cout << "Hub initialized" << std::endl;
    while(true)
    {
        if (!biskill) {
            if (Hub.recieveMessage(300,0,pid)) {
                cout << "Error recieving message in Hub from ProbeB" << endl;
            }
            cout << "Pid of probe B is #" << pid <<endl;
            cout << "killing probe B" << endl;
            cout << force_patch(stoi(pid));
            biskill = true;
        }

        if (Hub.recieveMessage(400,0,pid)) {
        	cout << "Error recieving message in Hub from ProbeC" << endl;
        }
        cout << "pid of probe C  is #" << pid << endl;
        if (Hub.recieveMessage(200,0,pid)) {
            cout << "Error recieving message in Hub from ProbeA" << endl;
        } else {
            cout << "pid of probe A is #" << pid << endl;
            if (Hub.sendMessage("Mhub", 100,0)) {
                cout << "Error sending in HUB" << endl;
            }
        }


        if (Hub.getNumberMessageReceived() >= 11)
        {
            break;
        }
        
    }
    cout << "Hub terminated" << endl;
    return 0;
}