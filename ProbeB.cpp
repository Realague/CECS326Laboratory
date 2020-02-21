#include"MessageQueue.h"

using namespace std;

int main() {
    MessageQueue probeB(0);
    
    for (int i = 0; i < 10; i++)
    {
        bool error = probeB.sendMessage("Ham's",233+i,0);
        if (error != false) {
            cout << "Error when sending message from ProbeA" << endl;
        }
    }
}