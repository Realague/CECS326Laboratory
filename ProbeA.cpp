#include"MessageQueue.h"

using namespace std;

int main() {
    MessageQueue probeA(0);
    
    for (int i = 0; i < 10; i++)
    {
        bool error = probeA.sendMessage("Hey",333+i,0);
        if (error != false) {
            cout << "Error when sending message from ProbeA" << endl;
        }

        error = probeA.recieveMessage(133+i,0);
        if (error != false) {
            cout << "error recieving message in ProbeA" << endl;
        }
    }
    

   

    return 0;
}