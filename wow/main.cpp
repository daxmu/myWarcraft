#include <iostream>
#include <string>
#include "define.h"
#include "Headquarter.h"

#ifndef _incTOOLS_
#define _incTOOLS_
#include "tools.h"
#endif

using namespace std;

int main(){
	int num_of_case;
	int base_life;
	int dragon_life, ninja_life, iceman_life, lion_life, wolf_life;
	vector <int> order_red{1,2,3,4,5};
	vector <int> order_blue{2,5,4,1,3};
	cin >> num_of_case;
	for(int i=1; i <= num_of_case; i++){
		myTime time(0);
		cout << "Case:" << i << endl;
		cin >> base_life;
		cin >> dragon_life >> ninja_life >> iceman_life >> lion_life >> wolf_life;

		Headquarter red("red", base_life, iceman_life, lion_life, wolf_life, ninja_life, dragon_life, order_red);	
		Headquarter blue("blue", base_life, iceman_life, lion_life, wolf_life, ninja_life, dragon_life, order_blue);	

		while(1){
			bool loop_finish = true;
			if(red.get_lifeStatus()){
				red.create_warrior(time);
				loop_finish = false;
			}
			if(blue.get_lifeStatus()){
				blue.create_warrior(time);
				loop_finish = false;
			}
			time.time_inc();
			if (loop_finish)
				break;
		}
	}
	//system("pause");
	return 0;
}
	
