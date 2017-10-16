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
	int dragon_atk, ninja_atk, iceman_atk, lion_atk, wolf_atk;
	vector <int> wLife, wAtk;
	vector <int> order_red{1,2,3,4,5};
	vector <int> order_blue{2,5,4,1,3};
	cin >> num_of_case;
	for(int i=1; i <= num_of_case; i++){
		myTime time(0);
		cout << "Case:" << i << endl;
		cin >> base_life;
		cin >> dragon_life >> ninja_life >> iceman_life >> lion_life >> wolf_life;
		cin >> dragon_atk >> ninja_atk >> iceman_atk >> lion_atk >> wolf_atk;
		wLife.push_back(iceman_life);
		wLife.push_back(lion_life);
		wLife.push_back(wolf_life);
		wLife.push_back(ninja_life);
		wLife.push_back(dragon_life);
		wAtk.push_back(iceman_atk);
		wAtk.push_back(lion_atk);
		wAtk.push_back(wolf_atk);
		wAtk.push_back(ninja_atk);
		wAtk.push_back(dragon_atk);

		Headquarter red("red", base_life, wLife, wAtk, order_red);	
		Headquarter blue("blue", base_life, wLife, wAtk, order_blue);	

		while(1){
			time.set_min(0);
			bool loop_finish = true;
			if(red.get_lifeStatus()){
				red.create_warrior(time);
				loop_finish = false;
			}
			if(blue.get_lifeStatus()){
				blue.create_warrior(time);
				loop_finish = false;
			}

			time.set_min(55);
			red.print_curwpMessage(time);
			blue.print_curwpMessage(time);

			time.hour_inc();
			if (loop_finish)
				break;
		}
	}
	//system("pause");
	return 0;
}
	
