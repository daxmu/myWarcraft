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
#ifdef MYDEBUG
	cout << "0000000000000000" << endl;
#endif
	int num_of_case;
	int base_life, city_num, arrow_R, loyalty_K, max_time;
	int dragon_life, ninja_life, iceman_life, lion_life, wolf_life;
	int dragon_atk, ninja_atk, iceman_atk, lion_atk, wolf_atk;
	vector <int> order_red{1,2,3,4,5};
	vector <int> order_blue{2,5,4,1,3};
	cin >> num_of_case;
	for(int i=1; i <= num_of_case; i++){
//#ifdef MYDEBUG
//	cout << "1111111111111111" << endl;
//#endif
		myTime time(0);
		cout << "Case " << i << ":" << endl;
		cin >> base_life >> city_num >> arrow_R >> loyalty_K >> max_time;
		cin >> dragon_life >> ninja_life >> iceman_life >> lion_life >> wolf_life;
		cin >> dragon_atk >> ninja_atk >> iceman_atk >> lion_atk >> wolf_atk;
		
		//set life and atk vector
		vector <int> wLife, wAtk;
		wLife.push_back(iceman_life);wLife.push_back(lion_life);wLife.push_back(wolf_life);wLife.push_back(ninja_life);wLife.push_back(dragon_life);
		wAtk.push_back(iceman_atk);wAtk.push_back(lion_atk);wAtk.push_back(wolf_atk);wAtk.push_back(ninja_atk);wAtk.push_back(dragon_atk);
		
		//set special features
		Arrow::atk = arrow_R;
		Lion::k = loyalty_K;

		//set city vector;
		vector <City> citys;
		for (int j=0; j<city_num; ++j){
			City tmp(j+1);
			citys.push_back(tmp);
		}
		//set headquarters
		Headquarter red("red", base_life, wLife, wAtk, order_red);	
		Headquarter blue("blue", base_life, wLife, wAtk, order_blue);	

		//game start
		while(1){
//#ifdef MYDEBUG
//	cout << "2222222222222222" << endl;
//#endif
			// min 00 create warrior
			time.set_min(0);
			if(time.gthan(max_time)) break;

			red.create_warrior(time);
			blue.create_warrior(time);
			
			// min 05 lion run away
			time.set_min(5);
			if(time.gthan(max_time)) break;

			red.lion_escape(time);
			for(auto j = citys.begin(); j!=citys.end(); ++j)
				(*j).lion_escape(time);
			blue.lion_escape(time);

//#ifdef MYDEBUG
//	cout << "3333333333333333" << endl;
//#endif
			//min 10 warrior march
			time.set_min(10);
			if(time.gthan(max_time)) break;

			for(auto j = citys.begin(); j!=citys.end(); ++j)
				(*j).march_prepare();

			bool taken;
			red.march_fromCity(&(*citys.begin()), time);
			taken |= red.be_taken(time);
			for(auto j = citys.begin(); j!=citys.end(); ++j){
				if(j==citys.begin())
					(*j).march_fromSide(&red, time);
				else
					(*j).march_fromSide(&(*(j-1)),time);
				if((j+1)==citys.end())
					(*j).march_fromSide(&blue, time);
				else
					(*j).march_fromSide(&(*(j+1)),time);
			}
			blue.march_fromCity(&(*(citys.end()-1)), time);
			taken |= blue.be_taken(time);
			if(taken)
				break;
			
			//min 20 generate life
			time.set_min(20);
			if(time.gthan(max_time)) break;

			for(auto j=citys.begin(); j!=citys.end(); ++j)
				(*j).gen_life();

			//min 30 collect life
			time.set_min(30);
			if(time.gthan(max_time)) break;

			for(auto j=citys.begin(); j!=citys.end(); ++j)
				(*j).exclusive(time);
			red.set_fbValue();
			blue.set_fbValue();

			//min 35 warrior shoot
			time.set_min(35);
			if(time.gthan(max_time)) break;

			for(auto j=citys.begin(); j!=citys.end(); ++j){
				if(j!=citys.end()-1)
					(*j).shoot_toNext(&(*(j+1)),time);
				if(j!=citys.begin())
					(*j).shoot_toNext(&(*(j-1)),time);
			}

			//min 38 warrior shoot
			time.set_min(38);
			if(time.gthan(max_time)) break;
			for(auto j=citys.begin(); j!=citys.end(); ++j)
				(*j).use_bomb(time);

			//min 40 warrior fight
			time.set_min(40);
			if(time.gthan(max_time)) break;

			for(auto j=citys.begin(); j!=citys.end(); ++j){
				(*j).warrior_fight(time);
				(*j).fight_settle(time);
			}
			//reward warrior life
			for(auto j=citys.begin(); j!=citys.end(); ++j)
				(*j).reward_life();
			red.set_fbValue();
			blue.set_fbValue();

			//min 50 report headquarter lifeValue
			time.set_min(50);
			if(time.gthan(max_time)) break;
			red.report_lifeValue(time);
			blue.report_lifeValue(time);

//#ifdef MYDEBUG
//	cout << "4444444444444444" << endl;
//#endif
			//min 55 report weapon message
			time.set_min(55);
			if(time.gthan(max_time)) break;

			for(auto j=citys.begin(); j!=citys.end(); ++j)
				(*j).report_weapon(1,time);
			blue.report_weapon(time);
			red.report_weapon(time);
			for(auto j=citys.begin(); j!=citys.end(); ++j)
				(*j).report_weapon(2,time);

			time.hour_inc();
		}
	}
	//system("pause");
	return 0;
}
	
