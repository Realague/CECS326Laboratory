#include"MessageQueue.h"

using namespace std;

int main(int num, char * args[]) {
    MessageQueue probeB(0,args[1][0]);
    
    for (int i = 0; i < 10; i++)
    {
        bool error = probeB.sendMessage("Yo this is from ProbeB",233+i,0);
        if (error != false) {
            cout << "Error when sending message from ProbeB" << endl;
        }
    }
}