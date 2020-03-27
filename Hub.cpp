#include"MessageQueue.h"
#include"force_patch.h"

using namespace std;

int main(int num, char * args[]) {

    if (num < 2) {
    	std::cout << "Error: Wrong argument" << std::endl;
    	return 84;
    }
    Hub hub(IPC_EXCL|IPC_CREAT|0600,args[1][0], true);

	cout << "Hub initialized" << std::endl;
    while(hub.shouldHubExit())
    {
    	if (!hub.hasProbeAExit() && hub.recieveMessage(200,0,msg)) {
    		cout << "Error recieving message in Hub from ProbeA" << endl;
    	} else if (msg == "dead") {
		hub.setHubAExit(true);
	} else {
    		cout << "send a message to probeA: " << msg << endl;
    		if (hub.sendMessage("Mhub", 100,0)) {
    			cout << "Error sending in HUB" << endl;
    		}
    	}
    	}

    	if (!hub.hasProbeBExit() && hub.recieveMessage(300,0,msg)) {
    		cout << "Error recieving message in Hub from ProbeB" << endl;
    	} else if (msg == "dead") {
		hub.setHubBExit(true);
	} else {
		cout << "Message from Probe B: " << msg <<endl;
	}

        if (!hub.hasProbeCkExit && hub.recieveMessage(400,0,msg)) {
        	cout << "Error recieving message in Hub from ProbeC" << endl;
        } else if (msg == "dead") {
		hub.setHubCExit(true);
	} else {
		cout << "Message from Probe C: " << msg << endl;
	}
        
    }
    cout << "Hub terminated" << endl;
    return 0;
}