
start: main.cpp Headquarter.h tools.h define.h
	g++ -Wall -std=c++11 Headquarter.h define.h tools.h main.cpp -o start

debug: main.cpp Headquarter.h tools.h define.h
	g++ -Wall -std=c++11 Headquarter.h define.h tools.h main.cpp -o debug 2>debuglog

combine: combine.cpp
	g++ -Wall -std=c++11 combine.cpp -o combine

answer: answer.cpp
	g++ -Wall -std=c++11 answer.cpp -o answer

run: start in
	./start < in > log

run_nolog: start in
	./start < in

run_answer: answer
	./answer < in > result

run_diff: start answer
	./start < in > log
	./answer < in > result
	vimdiff log result
	
clean:
	rm -rf start log result answer combine debug debuglog
	
