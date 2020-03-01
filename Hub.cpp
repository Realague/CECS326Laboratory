#include"MessageQueue.h"
using namespace std;

int main(int num, char * args[]) {
    srand(time(NULL));

    if (num < 2) {
    	std::cout << "Error: Wrong argument" << std::endl;
    	return 84;
    }
    MessageQueue Hub(IPC_EXCL|IPC_CREAT|0600,args[1][0], true);

	cout << "Hub initialized" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        if (Hub.recieveMessage(300,0)) {
            cout << "Error recieving message in Hub from ProbeB" << endl;
        }

        if (Hub.recieveMessage(200,0)) {
            cout << "Error recieving message in Hub from ProbeA" << endl;
        } else {
            if (Hub.sendMessage("Mhub", 100,0)) {
                cout << "Error sending in HUB" << endl;
            }
        }
    }
    return 0;
}