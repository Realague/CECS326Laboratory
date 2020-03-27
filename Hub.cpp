#include "Hub.h"

using namespace std;

int main(int num, char * args[]) {

    if (num < 2) {
    	std::cout << "Error: Wrong argument" << std::endl;
    	return 84;
    }
    string msg = "";
    Hub hub(IPC_EXCL|IPC_CREAT|0600,args[1][0]);

	cout << "Hub initialized" << std::endl;
    while(hub.shouldHubExit()) {
    	if (!hub.hasProbeAExited() && hub.recieveMessage(200,0,msg)) {
    		cout << "Error recieving message in Hub from ProbeA" << endl;
    	} else if (msg == "dead") {
		hub.setProbeAExit(true);
	} else {
    		cout << "send a message to probeA: " << msg << endl;
    		if (hub.sendMessage("Mhub", 100,0)) {
    			cout << "Error sending in HUB" << endl;
    		}
    	}

    	if (!hub.hasProbeBExited() && hub.recieveMessage(300,0,msg)) {
    		cout << "Error recieving message in Hub from ProbeB" << endl;
    	} else if (msg == "dead") {
		hub.setProbeBExit(true);
	} else {
		cout << "Message from Probe B: " << msg <<endl;
	}

        if (!hub.hasProbeCExited() && hub.recieveMessage(400,0,msg)) {
        	cout << "Error recieving message in Hub from ProbeC" << endl;
        } else if (msg == "dead") {
		hub.setProbeCExit(true);
	} else {
		cout << "Message from Probe C: " << msg << endl;
	}
        
    }
    cout << "Hub terminated" << endl;
    return 0;
}