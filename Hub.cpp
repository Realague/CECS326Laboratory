#include"MessageQueue.h"
using namespace std;

int main() {
    MessageQueue Hub(IPC_EXCL|IPC_CREAT|0600);
    
    for (int i = 0; i < 10; i++)
    {
        bool error = false;
        /*error = Hub.recieveMessage(233+i,0);
        if (error != false) {
            cout << "Error recieving message in Hub" << endl;
        }*/

        error = Hub.recieveMessage(0,0);
        if (error == false) {
            cout << "Error recieving message in Hub" << endl;
        } else {
            error = Hub.sendMessage("hi", 133+i,0);
            if (error == false) {
                cout << "Error sending in HUB" << endl; 
            }
        }


    }

    return 0;
}