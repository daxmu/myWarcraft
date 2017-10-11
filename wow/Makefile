
start: main.cpp Headquarter.h tools.h define.h
	g++ -Wall -std=c++11 Headquarter.h define.h tools.h main.cpp -o start

combine: combine.cpp
	g++ -Wall -std=c++11 combine.cpp -o combine

answer: answer.cpp
	g++ -Wall -std=c++11 answer.cpp -o answer

run: start
	./start < in > log

run_answer: answer
	./answer < in > result

run_diff: start answer
	./start < in > log
	./answer < in > result
	vimdiff log result
	
clean:
	rm -rf start log result answer combine
	
