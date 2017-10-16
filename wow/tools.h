#include <iostream>
#include <vector>
#include <iomanip>
#include "define.h"
using namespace std;

class myTime{
	public:
		myTime() = default;
		myTime(int hour_){
			hour[0] = hour_ % 10;
			hour_ /= 10;
			hour[1] = hour_ % 10;
			hour_ /= 10;
			hour[2] = hour_ % 10;
			hour_ /=10;
			min[0] = 0;
			min[1] = 0;
#ifndef NDEBUG
			if (hour_ != 0)
				cout << "time is out of limited" << endl;
#endif
		}
		void set_min(int min_){
			min[0] = min_ % 10;
			min_ /= 10;
			min[1] = min_ % 6;
			min_ /= 6;
#ifndef NDEBUG
			if(min_ !=0)
				cout << "min set is out of limited" << endl;
#endif
		}
		void hour_inc(){
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
			cout << hour[2] << hour[1] << hour[0] << ":" << min[1] << min[0];
			return;
		}
	private:
		int hour[3];
		int min[2];
};
