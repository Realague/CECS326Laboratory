#include"MessageQueue.h"

using namespace std;

int main(int num, char *args[]) {
	if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}

    MessageQueue probeA(0,args[1][0], false);
    
    for (int i = 0; i < 5; i++)
    {
        if (probeA.sendMessage("MprobeA", 200,0)) {
            cout << "Error when sending message from ProbeA" << endl;
        }

        if (probeA.recieveMessage(100, 0)) {
            cout << "error recieving message in ProbeA" << endl;
        }
    }
    

   

    return 0;
}