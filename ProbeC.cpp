#include"MessageQueue.h"
using namespace std;
int main(int num, char * args[]) {
    int rho = 3000;
    int messageSnt = 0;

    if (num < 2) {
		std::cout << "Error: Wrong argument" << std::endl;
		return 84;
	}
    MessageQueue probeC(0,args[1][0], false);

    while (messageSnt < 5)
    {
        int gen = probeC.genRandNum(0,300000)
        if (gen%rho == 0)
        {
            
        }
        
    }
    
}