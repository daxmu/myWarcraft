
start: main.cpp Headquarter.h define.h
	g++ -Wall -std=c++11 Headquarter.h define.h main.cpp -o start

combine: combine.cpp
	g++ -Wall -std=c++11 combine.cpp -o start

answer: answer.cpp
	g++ -Wall -std=c++11 answer.cpp -o answer

run: start
	./start < in > log

clean:
	rm -rf start log result answer
	
