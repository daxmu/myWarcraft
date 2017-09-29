#include <iostream>
#include <vector>
#include <iomanip>
#include "define.h"
using namespace std;
class Headquarter;
class Iceman;
class Weapon;

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

class Weapon{
	public:
		Weapon() = default;
		Weapon(int type){
			weapon_type = type;
			switch(type){
				case 0:
					weapon_name = "sword";
					break;
				case 1:
					weapon_name = "bomb";
					break;
				case 2:
					weapon_name	= "arrow";
					break;
				default:
					cout << "Error weapon type!" <<endl;
			}
		}
		string get_Weapon_name(){return weapon_name;}
	private:
		string weapon_name;
		int weapon_type;
};

class Iceman{
	public:
		Iceman() = default;
		Iceman(Headquarter* master, int warrior_life, int warrior_num){
			my_master	= master;
			life_value	= warrior_life;
			num_of_warrior	= warrior_num;
			Weapon	a(warrior_num%3);
			my_weapon	= a;
		}
		
		string 	get_Weapon_name(){ return my_weapon.get_Weapon_name();}
		int		get_Warrior_num(){ return num_of_warrior;}
		int 	get_Strength(){return life_value;}
	private:
		Headquarter *my_master;
		int	life_value;
		int num_of_warrior;
		Weapon my_weapon;
		
};

class Lion{
	public:
		Lion() = default;
		Lion(Headquarter* master, int warrior_life, int warrior_num, int lion_loyalty){
			my_master	= master;
			life_value	= warrior_life;
			num_of_warrior	= warrior_num;
			loyalty		= lion_loyalty;
			//lion has no weapon
			//Weapon	a(warrior_num%3);
			//my_weapon	= a;
		}
		
		//string 	get_Weapon_name(){ return my_weapon.get_Weapon_name();}
		int get_Warrior_num(){ return num_of_warrior;}
		int get_Strength(){return life_value;}
		int get_Loyalty(){return loyalty;}
	private:
		Headquarter *my_master;
		int	life_value;
		int num_of_warrior;
		//Weapon my_weapon;
		int loyalty;
};
class Wolf{
	public:
		Wolf() = default;
		Wolf(Headquarter* master, int warrior_life, int warrior_num){
			my_master	= master;
			life_value	= warrior_life;
			num_of_warrior	= warrior_num;
			//wolf has no weapon
			//Weapon	a(warrior_num%3);
			//my_weapon	= a;
		}
		
		//string 	get_Weapon_name(){ return my_weapon.get_Weapon_name();}
		int get_Warrior_num(){ return num_of_warrior;}
		int get_Strength(){return life_value;}
	private:
		Headquarter *my_master;
		int	life_value;
		int num_of_warrior;
		//Weapon my_weapon;
	
};
class Ninja{
	public:
		Ninja() = default;
		Ninja(Headquarter* master, int warrior_life, int warrior_num){
			my_master	= master;
			life_value	= warrior_life;
			num_of_warrior	= warrior_num;
			Weapon	a(warrior_num%3);
			Weapon	b((warrior_num+1)%3);
			my_weapon_1 = a;
			my_weapon_2 = b;
		}
		
		string 	get_Weapon1_name(){ return my_weapon_1.get_Weapon_name();}
		string 	get_Weapon2_name(){ return my_weapon_2.get_Weapon_name();}
		int get_Warrior_num(){ return num_of_warrior;}
		int get_Strength(){return life_value;}
	private:
		Headquarter *my_master;
		int	life_value;
		int num_of_warrior;
		Weapon my_weapon_1;
		Weapon my_weapon_2;
};
class Dragon{
	public:
		Dragon() = default;
		Dragon(Headquarter* master, int warrior_life, int warrior_num, double dragon_morale){
			my_master	= master;
			life_value	= warrior_life;
			num_of_warrior	= warrior_num;
			Weapon	a(warrior_num%3);
			my_weapon	= a;
			morale		= dragon_morale;
		}
		
		string 	get_Weapon_name(){ return my_weapon.get_Weapon_name();}
		int get_Warrior_num(){ return num_of_warrior;}
		int get_Strength(){return life_value;}
		double get_Morale(){return morale;}
	private:
		Headquarter *my_master;
		int	life_value;
		int num_of_warrior;
		double morale;
		Weapon my_weapon;
};


class Headquarter{
	public:
		Headquarter()	= default;
		Headquarter(string name, int base_life, int a, int b, int c, int d, int e, const vector <int> &order){
			my_name		 	= name; 
			life_enough		= true;
			life_value		= base_life;
			iceman_life		= a;
			lion_life		= b;
			wolf_life		= c;
			ninja_life		= d;
			dragon_life		= e;
			create_order	= order;
			next_create		= create_order.begin();
			next_num		= 1;
		}

		bool create_warrior(myTime time){
#ifndef NDEBUG
			cout << life_value << endl;
#endif
			bool create_success = false;
			vector <int> :: iterator last = next_create;
			//if (last == create_order.begin())
			//	last = create_order.end();
			//else
			//	last--;

			while(!create_success){
				switch(*next_create){
					case 1:
						if(life_value >= iceman_life){
							create_iceman(time);
							create_success = true;
						}
						break;
					case 2:
						if(life_value >= lion_life){
							create_lion(time);
							create_success = true;
						}
						break;
					case 3:
						if(life_value >= wolf_life){
							create_wolf(time);
							create_success = true;
						}
						break;
					case 4:
						if(life_value >= ninja_life){
							create_ninja(time);
							create_success = true;
						}
						break;
					case 5:
						if(life_value >= dragon_life){
							create_dragon(time);
							create_success = true;
						}
						break;
					default:
						cout << "Error num of warrior type : " << *next_create <<endl;
				}
				if(!create_success){
					next_create++;
					if(next_create == create_order.end())
						next_create = create_order.begin();
				}
				if(next_create==last)
					break;
			}

			if (!create_success){
				time.print_time();
				cout << " " << my_name << " headquarter stops making warriors"
					 << endl;
				life_enough = false;
				return false;
			}
			next_create++;
			if(next_create == create_order.end())
				next_create = create_order.begin();
			life_enough = true;
			return true;
		}

		bool get_life_status(){return life_enough;}
	private:
		string my_name;
		bool life_enough;
		int life_value;
		int iceman_life;
		int lion_life;
		int wolf_life;
		int ninja_life;
		int dragon_life;
		int next_num;
		vector <int>	create_order;
		vector <int> ::	iterator next_create;
		vector <Iceman> my_iceman;
		vector <Lion> 	my_lion;
		vector <Wolf> 	my_wolf;
		vector <Ninja> 	my_ninja;
		vector <Dragon> my_dragon;

		bool create_iceman(myTime time){
			if(life_value >= iceman_life){
				Iceman a(this, iceman_life, next_num);
				my_iceman.push_back(a);
				life_value -= iceman_life;
				next_num ++;
				time.print_time();
				cout << " " << my_name << " iceman " << a.get_Warrior_num() 
					 << " born with strength " << a.get_Strength() << ","
					 << my_iceman.size() << " iceman in " <<  my_name << " headquarter"
					 << endl;
				cout << "It has a " << a.get_Weapon_name() << endl;
				return true;
			}
#ifdef NDEBUG
			cout << "life is not enough for Iceman!" << endl;
#endif
			return false;
		}

		bool create_lion(myTime time){
			if(life_value >= lion_life){
				int lion_loyalty = life_value - lion_life;
				Lion a(this, lion_life, next_num, lion_loyalty);
				my_lion.push_back(a);
				life_value -= lion_life;
				next_num ++;
				time.print_time();
				cout << " " << my_name << " lion " << a.get_Warrior_num() 
					 << " born with strength " << a.get_Strength() << ","
					 << my_lion.size() << " lion in " <<  my_name << " headquarter"
					 << endl;
				cout << "It's loyalty is " << a.get_Loyalty() << endl;
				return true;
			}
#ifdef NDEBUG
			cout << "life is not enough for Lion!" << endl;
#endif
			return false;
		}
		bool create_wolf(myTime time){
			if(life_value >= wolf_life){
				Wolf a(this, wolf_life, next_num);
				my_wolf.push_back(a);
				life_value -= wolf_life;
				next_num ++;
				time.print_time();
				cout << " " << my_name << " wolf " << a.get_Warrior_num() 
					 << " born with strength " << a.get_Strength() << ","
					 << my_wolf.size() << " wolf in " <<  my_name << " headquarter"
					 << endl;
				//cout << "It has a " << a.get_Weapon_name() << endl;
				return true;
			}
#ifdef NDEBUG
			cout << "life is not enough for Wolf!" << endl;
#endif
			return false;
		}
		bool create_ninja(myTime time){
			if(life_value >= ninja_life){
				Ninja a(this, ninja_life, next_num);
				my_ninja.push_back(a);
				life_value -= ninja_life;
				next_num ++;
				time.print_time();
				cout << " " << my_name << " ninja " << a.get_Warrior_num() 
					 << " born with strength " << a.get_Strength() << ","
					 << my_ninja.size() << " ninja in " <<  my_name << " headquarter"
					 << endl;
				cout << "It has a " << a.get_Weapon1_name() << " and a "
					 << a.get_Weapon2_name() << endl;
				return true;
			}
#ifdef NDEBUG
			cout << "life is not enough for Ninja!" << endl;
#endif
			return false;
		}


		bool create_dragon(myTime time){
			if(life_value >= dragon_life){
				double dragon_morale = (double)(life_value - dragon_life) / dragon_life;
				Dragon a(this, dragon_life, next_num, dragon_morale);
				my_dragon.push_back(a);
				life_value -= dragon_life;
				next_num ++;
				time.print_time();
				cout << " " << my_name << " dragon " << a.get_Warrior_num() 
					 << " born with strength " << a.get_Strength() << ","
					 << my_dragon.size() << " dragon in " <<  my_name << " headquarter"
					 << endl;
				cout << "It has a " << a.get_Weapon_name() << ",and it's morale is ";
				cout << setiosflags(ios::fixed) << setprecision(2) << a.get_Morale() 
					 << endl;
				//cout << "************" << a.get_Morale() << endl;
				return true;
			}
#ifdef NDEBUG
			cout << "life is not enough for Dragon!" << endl;
#endif
			return false;
		}
};








