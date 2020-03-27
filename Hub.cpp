#include "Hub.h"

using namespace std;

//Main function for hub program
int main(int num, char * args[]) {

	//verify user has given a key for queue
    if (num < 2) {
    	std::cout << "Error: Wrong argument" << std::endl;
    	return 84;
    }

    string msg = "";
    Hub hub(IPC_EXCL|IPC_CREAT|0600,args[1][0]);

	
	cout << "Hub initialized" << std::endl;
    while(hub.shouldHubExit()) {
		cout << "run" << endl;
		//check if A still exists then recieve message from probeA and check flag
    	if (!hub.hasProbeAExited() && hub.recieveMessage(200,0,msg)) {
    		cout << "Error recieving message in Hub from ProbeA" << endl;
    	} else if (msg == "dead") {//if message reads dead
			cout << msg << endl;
			hub.setProbeAExit(true);
		} else {//send return message
    		cout << "send a message to probeA: " << msg << endl;
    		if (hub.sendMessage("Mhub", 100,0)) {
    			cout << "Error sending in HUB" << endl;
    		}
    	}

		//repeat for probe B and C; no reply message is sent
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