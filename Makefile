build:
	g++ *.h && g++ Hub.cpp -o hub.out && g++ ProbeA.cpp -o probeA.out && g++ ProbeB.cpp -o probeB.out

clean:
	rm -rf *.out
	rm -rf *.gch

re:
	clean
	build
