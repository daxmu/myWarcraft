#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "define.h"

#ifndef _incTOOLS_
#define _incTOOLS_
#include "tools.h"
#endif

using namespace std;

class Headquarter;

class Weapon{ // 武器基类
	public:
		Weapon(int type_): wpType(type_) {}
		virtual string get_wpMessage() const = 0; //获取武器信息
		virtual bool isInvalid() const = 0; //判断武器是否存在
		virtual string get_wpName() const = 0; //获得武器名称
		int get_wpType() const { return wpType;} //获得武器种类
	protected:
		int wpType;
};
class Sword: public Weapon{
	public:
		Sword(int atk_): Weapon(0), atk(atk_){}
		string get_wpMessage() const override {
			string atk_s;
			stringstream ss;
			ss << atk;
			ss >> atk_s;
			return (name + "(" + atk_s + ")" );
		}
		bool isInvalid() const override { return (atk==0);}
		string get_wpName() const override { return name;}
	private:
		const static string name;
		int atk;
};
class Bomb: public Weapon{
	public:
		Bomb(): Weapon(1){}
		string get_wpMessage() const override {
			return name;
		}
		bool isInvalid() const override { return 0;}
		string get_wpName() const override { return name;}
	private:
		const static string name;
};
class Arrow: public Weapon{
	public:
		Arrow(int num_): Weapon(2), num(num_){}
		string get_wpMessage() const override {
			string num_s;
			stringstream ss;
			ss << num;
			ss >> num_s;
			return (name + "(" + num_s + ")" );
		}
		bool isInvalid() const override { return (num==0);}
		string get_wpName() const override { return name;}
	private:
		const static string name;
		int num;
};

class Idlewp: public Weapon{ // 无效武器类,用于没有武器
	public:
		Idlewp(): Weapon(-1){}
		string get_wpMessage() const override{ return "Idle";}
		bool isInvalid() const override { return 1;}
		string get_wpName() const override { return "Idle";}
};

const string Sword::name = "sword";
const string Bomb::name  = "bomb";
const string Arrow::name = "arrow";


class Warrior{
	public:
		Warrior(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			master(master_), lifeValue(lifeValue_), warriorNum(warriorNum_), typeNum(typeNum_), atk(atk_), msName(msName_){}

		int get_warriorNum() const {return warriorNum;}
		int get_lifeValue() const {return lifeValue;}
		int get_typeNum() const {return typeNum;}
		int get_atk() const {return atk;}
		virtual void print_exMessage() const = 0;
		virtual void print_wpMessage() const = 0;
		virtual string get_warriorName() const = 0;
		virtual void march(){}
		Headquarter *master;
	protected:
		int lifeValue;
		int	warriorNum;
		int typeNum;
		int atk;
		string msName;
};

class Iceman: public Warrior{
	public:
		Iceman(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_){
			switch(warriorNum_%3){
				case 0:
					weapon = new Sword(atk_/5);
					break;
				case 1:
					weapon = new Bomb;
					break;
				case 2:
					weapon = new Arrow(3);
					break;
				default:
					cout << "*********THE WEAPON TYPE IS ERROR**************"<<endl;
			}
		}

		string get_warriorName() const override {return name;}
		string get_wpName() const {return weapon->get_wpName();}
		void print_exMessage() const override {}
		void print_wpMessage() const override {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon->isInvalid())	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		void march() override{
			if(lifeValue > 9)
				lifeValue -= 9;
			else
				lifeValue = 1;
			atk += 20;
		}
	private:
		Weapon* weapon;	
		const static string name;
};

class Lion: public Warrior{
	public:
		Lion(Headquarter* master_, int lifeValue_, int warriorNum_, int loyalty_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_), loyalty(loyalty_){}

	 	int get_loyalty() const {return loyalty;}

		string get_warriorName() const {return name;}
		void print_exMessage() const {
			cout << "It's loyalty is " << loyalty << endl;
		}
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has "
				 << "no weapon" << endl;
		}
	private:
		int loyalty;
		const static string name;
};

class Wolf: public Warrior{
	public:
		Wolf(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_){
				weapon = new Idlewp();
			}

		string get_warriorName() const {return name;}

		void print_exMessage() const {}
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon->isInvalid())	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
	private:
		const static string name;
		Weapon *weapon;
};

class Ninja: public Warrior{
	public:
		Ninja(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_){
			switch(warriorNum_%3){
				case 0:
					weapon1 = new Sword(atk_/5);
					weapon2 = new Bomb();
					break;
				case 1:
					weapon1 = new Bomb;
					weapon2 = new Arrow(3);
					break;
				case 2:
					weapon1 = new Arrow(3);
					weapon2 = new Sword(atk_/5);
					break;
				default:
					cout << "*********THE WEAPON TYPE IS ERROR**************"<<endl;
			}
		}

		string get_weapon1Name() const {return weapon1->get_wpName();}
		string get_weapon2Name() const {return weapon2->get_wpName();}
		string get_warriorName() const {return name;}

		void print_exMessage() const {}
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon1->isInvalid())	
				if(weapon2->isInvalid())
					cout << "no weapon" << endl;
				else
					cout << weapon2->get_wpMessage() << endl;
			else{
				cout << weapon1->get_wpMessage();
				if(weapon2->isInvalid())
					cout << endl;
				else
					cout << "," << weapon2->get_wpMessage() << endl;
			}
		}
	private:
		Weapon *weapon1;
		Weapon *weapon2;
		const static string name;
};

class Dragon: public Warrior{
	public:
		Dragon(Headquarter* master_, int lifeValue_, int warriorNum_, double morale_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_), morale(morale_){
			switch(warriorNum_%3){
				case 0:
					weapon = new Sword(atk_/5);
					break;
				case 1:
					weapon = new Bomb;
					break;
				case 2:
					weapon = new Arrow(3);
					break;
				default:
					cout << "*********THE WEAPON TYPE IS ERROR**************"<<endl;
			}	
		}
		string get_wpName() const {return weapon->get_wpName();}
		double get_morale(){return morale;}
		void print_exMessage() const {
			cout << "it's morale is " << setiosflags(ios::fixed) << setprecision(2) 
				 << morale << endl;
		}
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon->isInvalid())	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		
		string get_warriorName() const {return name;}
	private:
		Weapon *weapon;	
		double morale;
		const static string name;
};

const string Iceman::name	= "iceman";
const string Lion::name 	= "lion";
const string Wolf::name 	= "wolf";
const string Ninja::name 	= "ninja";
const string Dragon::name 	= "dragon";

class City{
	public:
		City(int ID_, int lifeValue_):cityID(ID_), lifeValue(lifeValue_), flagName(""), red(NULL), blue(NULL), lastRed(NULL), lastBlue(NULL){}
		City(int ID_):cityID(ID_), lifeValue(0), flagName(""), red(NULL), blue(NULL), lastRed(NULL), lastBlue(NULL){}

		void warrior_fight();
		void march_fromSide(City* ,const myTime&);
		void march_fromSide(Headquarter*, const myTime&);
		void march_prepare();

		friend class Headquarter;
	private:
		int cityID;
		int lifeValue;
		string flagName;
		Warrior *red;
		Warrior *blue;
		Warrior *lastRed;
		Warrior *lastBlue;

};

class Headquarter{
	public:
		Headquarter()	= default;
		Headquarter(string name_, int baseLife_, vector <int> wLife_, vector <int> wAtk_, vector <int> order):
			name(name_), lifeEnough(true), lifeValue(baseLife_), warriorLife(wLife_), warriorAtk(wAtk_), createOrder(order), nextCreate(createOrder.begin()), nextNum(1), taken(false), curWarrior(NULL), enemyWarrior(NULL){}

		bool get_lifeStatus(){return lifeEnough;}
		string get_name(){return name;}
		void print_curwpMessage(myTime time) const { if(curWarrior!=NULL){time.print_time(); cout << " "; curWarrior->print_wpMessage();}}
		bool be_taken(const myTime&) const ;
		bool create_warrior(myTime);
		void print_bornMessage(myTime, const Warrior&);
		void march_fromCity(City *, const myTime&);

		friend class City;
	private:
		string name;
		bool lifeEnough;
		int lifeValue;
		vector <int> warriorLife; //iceman, lion, wolf, ninja, dragon
		vector <int> warriorAtk; //iceman, lion, wolf, ninja, dragon
		vector <int> createOrder;
		vector <int> ::	iterator nextCreate;
		int nextNum;
		bool taken;
		Warrior *curWarrior;
		Warrior *enemyWarrior;
		vector <Iceman*>	icemanQueue;
		vector <Lion*> 		lionQueue;
		vector <Wolf*> 		wolfQueue;
		vector <Ninja*> 	ninjaQueue;
		vector <Dragon*> 	dragonQueue;

		Warrior* create_iceman(){
			if(lifeValue >= warriorLife[0]){
				int typeNum = icemanQueue.size() + 1;
				Iceman *a = new Iceman(this, warriorLife[0], nextNum, typeNum, warriorAtk[0], name);
				icemanQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create iceman failed" << endl;
#endif
			return NULL;
			}
		}

		Warrior* create_lion(){
			if(lifeValue >= warriorLife[1]){
				int typeNum = lionQueue.size() + 1;
				int loyalty = lifeValue - warriorLife[1];
				Lion *a = new Lion(this, warriorLife[1], nextNum, loyalty, typeNum, warriorAtk[1], name);
				lionQueue.push_back(a);
				return a;
			} 
			else {
#ifdef NDEBUG
				cout << "create lion failed" << endl;
#endif
			return NULL;
			}
		}

		Warrior* create_wolf(){
			if(lifeValue >= warriorLife[2]){
				int typeNum = wolfQueue.size() + 1;
				Wolf *a = new Wolf(this, warriorLife[2], nextNum, typeNum, warriorAtk[2], name);
				wolfQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create wolf failed" << endl;
#endif
			return NULL;
			}
		}

		Warrior* create_ninja(){
			if(lifeValue >= warriorLife[3]){
				int typeNum = ninjaQueue.size() + 1;
				Ninja *a = new Ninja(this, warriorLife[3], nextNum, typeNum, warriorAtk[3], name);
				ninjaQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create ninja failed" << endl;
#endif
			return NULL;
			}
		}

		Warrior* create_dragon(){
			if(lifeValue >= warriorLife[4]){
				int typeNum = dragonQueue.size() + 1;
				double morale = (double) (lifeValue - warriorLife[4]) / warriorLife[4];
				Dragon *a = new Dragon(this, warriorLife[4], nextNum, morale, typeNum, warriorAtk[4], name);
				dragonQueue.push_back(a);
				return a;
			} else {
#ifdef NDEBUG
				cout << "create dragon failed" << endl;
#endif
			return NULL;
			}
		}

};

void City::warrior_fight(){
	//if(red!=NULL && blue!=NULL){
	//	if(flagName=="")
	//		if(cityID%2==0)
	//			//blue->
	//}
}

void City::march_prepare(){
	lastRed = red;
	lastBlue = blue;
	red = NULL;
	blue = NULL;
}
void City::march_fromSide(City *side, const myTime &time){
	if(side->cityID < this->cityID){
		if(this->red!=NULL)
			cout << "***************" << "city " << this->cityID 
				 << "red warrior has not been moved" << "*************" << endl;
		if(side->lastRed!=NULL){
			this->red = side->lastRed;
			side->lastRed = NULL;
			this->red->march();
			time.print_time();
			cout << " " << red->master->get_name() << " " << red->get_warriorName() 
				 << " " << red->get_warriorNum() << " marched to city " << cityID
				 << " with " << red->get_lifeValue() << " elements and force "
				 << red->get_atk() << endl;
		}
	} else if(side->cityID > this->cityID){
		if(this->blue!=NULL)
			cout << "***************" << "city " << this->cityID 
				 << "blue warrior has not been moved" << "*************" << endl;
		if(side->lastBlue!=NULL){
			this->blue = side->lastBlue;
			side->lastBlue = NULL;
			this->blue->march();
			time.print_time();
			cout << " " << blue->master->get_name() << " " << blue->get_warriorName() 
				 << " " << blue->get_warriorNum() << " marched to city " << cityID
				 << " with " << blue->get_lifeValue() << " elements and force "
				 << blue->get_atk() << endl;
		}
	} else
		cout << "*********error city num for march!**************" << endl;
}

void City::march_fromSide(Headquarter* head, const myTime &time){
	if(head->get_name() == "red"){
		if(this->red!=NULL)
			cout << "***************" << "city " << this->cityID 
				 << "red warrior has not been moved" << "*************" << endl;
		if(head->curWarrior!=NULL){
			this->red = head->curWarrior;
			head->curWarrior = NULL;
			this->red->march();
			time.print_time();
			cout << " " << red->master->get_name() << " " << red->get_warriorName() 
				 << " " << red->get_warriorNum() << " marched to city " << cityID
				 << " with " << red->get_lifeValue() << " elements and force "
				 << red->get_atk() << endl;
		}
	} else if(head->get_name() == "blue"){
		if(this->blue!=NULL)
			cout << "***************" << "city " << this->cityID 
				 << "blue warrior has not been moved" << "*************" << endl;
		if(head->curWarrior!=NULL){
			this->blue = head->curWarrior;
			head->curWarrior = NULL;
			this->blue->march();
			time.print_time();
			cout << " " << blue->master->get_name() << " " << blue->get_warriorName() 
				 << " " << blue->get_warriorNum() << " marched to city " << cityID
				 << " with " << blue->get_lifeValue() << " elements and force "
				 << blue->get_atk() << endl;
		}
	}
}

void Headquarter::march_fromCity(City *side, const myTime &time){
	if(this->get_name() == "red"){
		if(this->enemyWarrior!=NULL)
			cout << "************red enemyWarrior is not NULL!!************" << endl;
		if(side->lastBlue!=NULL){
			this->enemyWarrior = side->lastBlue;
			side->lastBlue = NULL;
			this->enemyWarrior->march();
			time.print_time();
			cout << " " << name << " " << enemyWarrior->get_warriorName()
				 << " " << enemyWarrior->get_warriorNum() << " reached " << name 
				 << " headquarter with " << enemyWarrior->get_lifeValue()
				 << " elements and force " << enemyWarrior->get_atk() << endl;
			taken = true;
		}
	}
	if(this->get_name() == "blue"){
		if(this->enemyWarrior!=NULL)
			cout << "************blue enemyWarrior is not NULL!!************" << endl;
		if(side->lastRed!=NULL){
			this->enemyWarrior = side->lastRed;
			side->lastRed = NULL;
			this->enemyWarrior->march();
			time.print_time();
			cout << " " << name << " " << enemyWarrior->get_warriorName()
				 << " " << enemyWarrior->get_warriorNum() << " reached " << name 
				 << " headquarter with " << enemyWarrior->get_lifeValue()
				 << " elements and force " << enemyWarrior->get_atk() << endl;
			taken = true;
		}
	}
}

inline bool Headquarter::be_taken(const myTime &time) const {
	if(!taken)
		return false;
	else{
		time.print_time();
		cout << " " << name << " headquarter was taken" << endl;
		return true;
	}
}
bool Headquarter::create_warrior(myTime time){
#ifdef MYDEBUG
	cout << "***create warrior" << endl;
#endif
	bool create_success = false;
	Warrior *newWarrior;
	switch(*nextCreate){
		case 1:
			if(lifeValue >= warriorLife[0]){
				newWarrior = create_iceman();
				create_success = true;
			}
			break;
		case 2:
			if(lifeValue >= warriorLife[1]){
				newWarrior = create_lion();
				create_success = true;
			}
			break;
		case 3:
			if(lifeValue >= warriorLife[2]){
				newWarrior = create_wolf();
				create_success = true;
			}
			break;
		case 4:
			if(lifeValue >= warriorLife[3]){
				newWarrior = create_ninja();
				create_success = true;
			}
			break;
		case 5:
			if(lifeValue >= warriorLife[4]){
				newWarrior = create_dragon();
				create_success = true;
			}
			break;
		default:
			cout << "Error num of warrior type : " << *nextCreate <<endl;
	}
	if(create_success){
		curWarrior = newWarrior;
		print_bornMessage(time, *newWarrior);
		lifeValue -= (*newWarrior).get_lifeValue();
		nextNum++;
		nextCreate++;
		if(nextCreate == createOrder.end())
			nextCreate = createOrder.begin();
	}
	lifeEnough = true;
	return true;
}

void Headquarter::print_bornMessage(myTime time, const Warrior& bornWarrior){
			time.print_time();
			//cout << " " << name << " " << bornWarrior.get_warriorName() << " "
			//	 << bornWarrior.get_warriorNum() << " born with strength "  
			//	 << bornWarrior.get_lifeValue() << "," << bornWarrior.get_typeNum() 
			//	 << " " << bornWarrior.get_warriorName() << " in " << name
			//	 << " headquarter" << endl;
			cout << " " << name << " " << bornWarrior.get_warriorName() << " "
				 << bornWarrior.get_warriorNum() << " born" << endl;
			bornWarrior.print_exMessage();
}
