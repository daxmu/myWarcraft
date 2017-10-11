#include <iostream>
#include <vector>
#include <iomanip>
#include "define.h"
using namespace std;

class myTime{
	public:
		myTime() = default;
		myTime(int time){
			hour[0] = time % 10;
			time /= 10;
			hour[1] = time % 10;
			time /= 10;
			hour[2] = time % 10;
			time /=10;
#ifndef NDEBUG
			if (time != 0)
				cout << "time is out of limited" << endl;
#endif
		}
		void time_inc(){
			hour[0]++;
			if(hour[0] == 10){
				hour[1]++; hour[0] = 0;}
			if(hour[1] == 10){
				hour[2]++; hour[1] = 0;}
			if(hour[2] == 10){
			//	hour[2] = 0;
#ifndef NDEBUG
				cout << "time add out of limited" << endl;
#endif
			}
			return;
		}
		void print_time(){
			cout << hour[2] << hour[1] << hour[0];
			return;
		}
	private:
		int hour[3];
};
