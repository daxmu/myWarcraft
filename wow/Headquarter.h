#include <iostream>
#include <vector>
#include <iomanip>
#include "define.h"

#ifndef _incTOOLS_
#define _incTOOLS_
#include "tools.h"
#endif

using namespace std;

class Headquarter;

class Weapon{
	public:
		Weapon() = default;
		Weapon(int type){
			weaponType = type;
			switch(type){
				case 0:
					weaponName = "sword";
					break;
				case 1:
					weaponName = "bomb";
					break;
				case 2:
					weaponName	= "arrow";
					break;
				default:
					cout << "Error weapon type!" <<endl;
			}
		}
		string get_weaponName() const {return weaponName;}
	private:
		string weaponName;
		int weaponType;
};

class Warrior{
	public:
		Warrior(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_):
			master(master_), lifeValue(lifeValue_), warriorNum(warriorNum_), typeNum(typeNum_){}

		int get_warriorNum() const {return warriorNum;}
		int get_lifeValue() const {return lifeValue;}
		int get_typeNum() const {return typeNum;}
		virtual void print_exMessage() const = 0;
		virtual string get_warriorName() const = 0;
	protected:
		Headquarter *master;
		int lifeValue;
		int	warriorNum;
		int typeNum;
};

class Iceman: public Warrior{
	public:
		Iceman(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_), weapon(warriorNum_%3){}
		string get_weaponName() const {return weapon.get_weaponName();}
		void print_exMessage() const {
			cout << "It has a " << get_weaponName() << endl;
		}
		string get_warriorName() const {return name;}
	private:
		Weapon weapon;	
		const static string name;
};

class Lion: public Warrior{
	public:
		Lion(Headquarter* master_, int lifeValue_, int warriorNum_, int loyalty_, int typeNum_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_), loyalty(loyalty_){}
		inline int get_loyalty() const {return loyalty;}
		void print_exMessage() const {
			cout << "It's loyalty is " << loyalty << endl;
		}
		string get_warriorName() const {return name;}
	private:
		int loyalty;
		const static string name;
};

class Wolf: public Warrior{
	public:
		Wolf(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_){}
		void print_exMessage() const {}
		string get_warriorName() const {return name;}
	private:
		const static string name;
};

class Ninja: public Warrior{
	public:
		Ninja(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_), weapon1(warriorNum_%3), weapon2((warriorNum_+1)%3){}
		string get_weapon1Name() const {return weapon1.get_weaponName();}
		string get_weapon2Name() const {return weapon2.get_weaponName();}
		void print_exMessage() const {
			cout << "It has a " << weapon1.get_weaponName() << " and a "
				 << weapon2.get_weaponName() << endl;
		}
		string get_warriorName() const {return name;}
	private:
		Weapon weapon1;
		Weapon weapon2;
		const static string name;
};

class Dragon: public Warrior{
	public:
		Dragon(Headquarter* master_, int lifeValue_, int warriorNum_, double morale_, int typeNum_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_), weapon(warriorNum_%3), morale(morale_){}
		string get_weaponName() const {return weapon.get_weaponName();}
		double get_morale(){return morale;}
		void print_exMessage() const {
			cout << "It has a " << weapon.get_weaponName() << ",and it's morale is ";
			cout << setiosflags(ios::fixed) << setprecision(2) << morale 
				 << endl;
		}
		string get_warriorName() const {return name;}
	private:
		Weapon weapon;	
		double morale;
		const static string name;
};

const string Iceman::name	= "iceman";
const string Lion::name 	= "lion";
const string Wolf::name 	= "wolf";
const string Ninja::name 	= "ninja";
const string Dragon::name 	= "dragon";

class Headquarter{
	public:
		Headquarter()	= default;
		Headquarter(string name_, int baseLife_, int a, int b, int c, int d, int e, const vector <int> &order):
		name(name_), lifeEnough(true), lifeValue(baseLife_), icemanLife(a), lionLife(b),
		wolfLife(c), ninjaLife(d), dragonLife(e), createOrder(order), 
		nextCreate(createOrder.begin()), nextNum(1){}

		bool create_warrior(myTime time){
#ifdef MYDEBUG
			cout << lifeValue << endl;
#endif
			bool create_success = false;
			vector <int> :: iterator last = nextCreate;
			Warrior *newWarrior;
			while(!create_success){
				switch(*nextCreate){
					case 1:
						if(lifeValue >= icemanLife){
							newWarrior = create_iceman();
							create_success = true;
						}
						break;
					case 2:
						if(lifeValue >= lionLife){
							newWarrior = create_lion();
							create_success = true;
						}
						break;
					case 3:
						if(lifeValue >= wolfLife){
							newWarrior = create_wolf();
							create_success = true;
						}
						break;
					case 4:
						if(lifeValue >= ninjaLife){
							newWarrior = create_ninja();
							create_success = true;
						}
						break;
					case 5:
						if(lifeValue >= dragonLife){
							newWarrior = create_dragon();
							create_success = true;
						}
						break;
					default:
						cout << "Error num of warrior type : " << *nextCreate <<endl;
				}
				if(!create_success){
					nextCreate++;
					if(nextCreate == createOrder.end())
						nextCreate = createOrder.begin();
				} else {
					curWarrior = newWarrior;
					print_bornMessage(time, *newWarrior);
					lifeValue -= (*newWarrior).get_lifeValue();
					nextNum++;
				}	
				if(nextCreate==last)
					break;
			}

			if (!create_success){
				time.print_time();
				cout << " " << name << " headquarter stops making warriors"
					 << endl;
				lifeEnough = false;
				return false;
			}
			nextCreate++;
			if(nextCreate == createOrder.end())
				nextCreate = createOrder.begin();
			lifeEnough = true;
			return true;
		}

		void print_bornMessage(myTime time, const Warrior& bornWarrior){
			time.print_time();
			cout << " " << name << " " << bornWarrior.get_warriorName() << " "
				 << bornWarrior.get_warriorNum() << " born with strength "  
				 << bornWarrior.get_lifeValue() << "," << bornWarrior.get_typeNum() 
				 << " " << bornWarrior.get_warriorName() << " in " << name
				 << " headquarter" << endl;
			bornWarrior.print_exMessage();
		}
		bool get_lifeStatus(){return lifeEnough;}
		string get_name(){return name;}
	private:
		string name;
		bool lifeEnough;
		int lifeValue;
		int icemanLife;
		int lionLife;
		int wolfLife;
		int ninjaLife;
		int dragonLife;
		vector <int>	createOrder;
		vector <int> ::	iterator nextCreate;
		int nextNum;
		Warrior *curWarrior;
		vector <Iceman*>	icemanQueue;
		vector <Lion*> 		lionQueue;
		vector <Wolf*> 		wolfQueue;
		vector <Ninja*> 	ninjaQueue;
		vector <Dragon*> 	dragonQueue;

		Warrior* create_iceman(){
			if(lifeValue >= icemanLife){
				int typeNum = icemanQueue.size() + 1;
				Iceman *a = new Iceman(this, icemanLife, nextNum, typeNum);
				icemanQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create iceman failed" << endl;
#endif
			}
		}

		Warrior* create_lion(){
			if(lifeValue >= lionLife){
				int typeNum = lionQueue.size() + 1;
				int loyalty = lifeValue - lionLife;
				Lion *a = new Lion(this, lionLife, nextNum, loyalty, typeNum);
				lionQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create lion failed" << endl;
#endif
			}
		}

		Warrior* create_wolf(){
			if(lifeValue >= wolfLife){
				int typeNum = wolfQueue.size() + 1;
				Wolf *a = new Wolf(this, wolfLife, nextNum, typeNum);
				wolfQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create wolf failed" << endl;
#endif
			}
		}

		Warrior* create_ninja(){
			if(lifeValue >= ninjaLife){
				int typeNum = ninjaQueue.size() + 1;
				Ninja *a = new Ninja(this, ninjaLife, nextNum, typeNum);
				ninjaQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create ninja failed" << endl;
#endif
			}
		}

		Warrior* create_dragon(){
			if(lifeValue >= dragonLife){
				int typeNum = dragonQueue.size() + 1;
				double morale = (double) (lifeValue - dragonLife) / dragonLife;
				Dragon *a = new Dragon(this, dragonLife, nextNum, morale, typeNum);
				dragonQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create dragon failed" << endl;
#endif
			}
		}

};

