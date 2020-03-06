#include"MessageQueue.h"
using namespace std;

int main(int num, char * args[]) {
    int messages = 0;

    if (num < 2) {
    	std::cout << "Error: Wrong argument" << std::endl;
    	return 84;
    }
    MessageQueue Hub(IPC_EXCL|IPC_CREAT|0600,args[1][0], true);

	cout << "Hub initialized" << std::endl;
    while(true)
    {
        if (Hub.recieveMessage(300,0)) {
            cout << "Error recieving message in Hub from ProbeB" << endl;
        }
        messages++;

        if (Hub.recieveMessage(200,0)) {
            cout << "Error recieving message in Hub from ProbeA" << endl;
        } else {
            messages++;
            if (Hub.sendMessage("Mhub", 100,0)) {
                cout << "Error sending in HUB" << endl;
            }
        }
        if (messages >= 10)
        {
            break;
        }
        
    }
    cout << "Hub terminated" << endl;
    return 0;
}