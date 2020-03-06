build	:
	g++ *.h -std=c++11 && g++ Hub.cpp -std=c++11 -o hub.out && g++ ProbeA.cpp -std=c++11 -std=c++11 -o probeA.out && g++ ProbeB.cpp -std=c++11 -o probeB.out

clean	:
	rm -rf *.txt
	rm -rf *.out
	rm -rf *.gch

re	:	clean build