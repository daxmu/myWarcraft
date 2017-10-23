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
class Iceman;
class Lion;
class Wolf;
class Ninja;
class Dragon;

class Weapon{ // 武器基类
	public:
		Weapon(int type_): wpType(type_) {}
		virtual string get_wpMessage() const = 0; //获取武器信息
		virtual bool isInvalid() const = 0; //判断武器是否存在
		virtual string get_wpName() const = 0; //获得武器名称
		int get_wpType() const { return wpType;} //获得武器种类
		virtual ~Weapon() = default;
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
		int get_atk() const {return atk;}
		bool consume() {atk=atk*4/5; return atk==0;}
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
		bool consume(){num-=1; return num==0;}
		static int atk;
	private:
		const static string name;
		int num;
};
int Arrow::atk;

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
		Warrior(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_, int cityID_=0):
			master(master_), lifeValue(lifeValue_), warriorNum(warriorNum_), typeNum(typeNum_), atk(atk_), cityID(cityID_), dieArrow(0), dieFight(0), dieBomb(0), wonFlag(0), msName(msName_){}

		int get_warriorNum() const {return warriorNum;}
		int get_lifeValue() const {return lifeValue;}
		int get_typeNum() const {return typeNum;}
		int get_atk() const {return atk;}
		bool get_wonFlag() const {return wonFlag;}
		void life_add(int a){lifeValue+=a;}
		string get_msName() const {return msName;}
		void req_reward();
		bool use_bomb(Warrior*, bool, const myTime&);
		virtual void life_sub(int a){lifeValue-=a;}
		virtual int  get_lastLife() const{ return 0;}
		virtual void collect_lifeValue(int, const myTime&) const = 0;
		virtual void print_exMessage() const = 0;
		virtual void print_wpMessage(const myTime&) const = 0;
		virtual string get_warriorName() const = 0;
		virtual int  get_power(bool) const = 0;
				int get_power2(bool) const;
		virtual bool has_bomb() const = 0;
		virtual void march(int cityID_){cityID = cityID_;}
		virtual void shoot(Warrior*, const myTime&) = 0;
		virtual void attack(Warrior*, const myTime&) = 0;
		virtual void counter(Warrior*, const myTime&) = 0;
		virtual void killed(const myTime&) = 0;
		virtual void win(Warrior*,int,const myTime&) = 0;
		virtual void deuce(Warrior*,const myTime&) = 0;
		virtual Weapon* seizedWp() = 0;
		virtual void set_cheer() {}
		virtual ~Warrior() = default;
		Headquarter *master;

		friend class Iceman;
		friend class Lion;
		friend class Wolf;
		friend class Ninja;
		friend class Dragon;
	protected:
		int lifeValue;
		int	warriorNum;
		int typeNum;
		int atk;
		int cityID;
		bool dieArrow;
		bool dieFight;
		bool dieBomb;
		bool wonFlag;
		string msName;
};

class Iceman: public Warrior{
	public:
		Iceman(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_), stepCount(0){
			switch(warriorNum_%3){
				case 0:
					if(atk_/5==0)
						weapon = NULL;
					else
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
		void print_wpMessage(const myTime &time) const override {
			time.print_time();		
			cout << " " << msName << " " << name << " " << warriorNum << " has ";
			if(weapon==NULL)	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		void march(int cityID_) override{	
			stepCount++;
			if(stepCount == 2){
				if(lifeValue > 9)
					lifeValue -= 9;
				else
					lifeValue = 1;
				atk += 20;
				stepCount = 0;
			}else if(stepCount > 2){
				cout << "************error stepCount in march(>2)***********" << endl;
			}
			cityID = cityID_;
		}
		int  get_power(bool) const override;
		void shoot(Warrior*, const myTime&) override ;
		bool has_bomb() const override;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		void killed(const myTime&) override;
		void win(Warrior*,int,const myTime&) override;
		void deuce(Warrior*,const myTime&) override;
		void collect_lifeValue(int, const myTime&) const override;
		Weapon *seizedWp() override {Weapon* tmp = weapon; weapon = NULL; return tmp;}
	private:
		int stepCount;
		Weapon* weapon;	
		const static string name;
};

class Lion: public Warrior{
	public:
		Lion(Headquarter* master_, int lifeValue_, int warriorNum_, int loyalty_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_), loyalty(loyalty_), lastLife(lifeValue_){}

	 	int get_loyalty() const {return loyalty;}
		string get_warriorName() const {return name;}

		void print_exMessage() const {
			cout << "Its loyalty is " << loyalty << endl;
		}
		void print_wpMessage(const myTime &time) const {
			time.print_time();		
			cout << " " << msName << " " << name << " " << warriorNum << " has "
				 << "no weapon" << endl;
		}
		bool escape(const myTime &time) const {
			if(loyalty <= 0){
				time.print_time();
				cout << " " << msName << " " << name << " " << warriorNum << " ran away" << endl;
				return true;
			}
			return false;
		}
		int  get_power(bool) const override;
		void shoot(Warrior*, const myTime&) override ;
		bool has_bomb() const override;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		void killed(const myTime&) override;
		void win(Warrior*,int,const myTime&) override;
		void deuce(Warrior*,const myTime&) override;
		void collect_lifeValue(int, const myTime&) const override;
		void life_sub(int a) override {lastLife = lifeValue; lifeValue-=a;}
		int  get_lastLife() const override {return lastLife;}
		Weapon *seizedWp() override {return NULL;}
		static int k;
	private:
		int loyalty;
		int lastLife;
		const static string name;
};
int Lion::k;

class Wolf: public Warrior{
	public:
		Wolf(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_){
				weapon = NULL;
			}

		string get_warriorName() const {return name;}

		void print_exMessage() const {}
		void print_wpMessage(const myTime &time) const {
			time.print_time();		
			cout << " " << msName << " " << name << " " << warriorNum << " has ";
			if(weapon==NULL)	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		int  get_power(bool) const override;
		void shoot(Warrior*, const myTime&) override ;
		bool has_bomb() const override;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		void killed(const myTime&) override;
		void win(Warrior*,int,const myTime&) override;
		void deuce(Warrior*,const myTime&) override;
		void collect_lifeValue(int, const myTime&) const override;
		Weapon *seizedWp() override {Weapon* tmp = weapon; weapon = NULL; return tmp;}
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
					weapon1 = new Bomb();
					if(atk_/5==0)
						weapon1 = NULL;
					else
						weapon2 = new Sword(atk_/5);
					break;
				case 1:
					weapon1 = new Arrow(3);
					weapon2 = new Bomb;
					break;
				case 2:
					weapon1 = new Arrow(3);
					if(atk_/5==0)
						weapon2 = NULL;
					else
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
		void print_wpMessage(const myTime &time) const {
			time.print_time();		
			cout << " " << msName << " " << name << " " << warriorNum << " has ";
			if(weapon1==NULL)	
				if(weapon2==NULL)
					cout << "no weapon" << endl;
				else
					cout << weapon2->get_wpMessage() << endl;
			else{
				cout << weapon1->get_wpMessage();
				if(weapon2==NULL)
					cout << endl;
				else
					cout << "," << weapon2->get_wpMessage() << endl;
			}
		}
		Weapon *seizedWp() override {
			Weapon* tmp;
			if(weapon1 != NULL){
				tmp = weapon1;
				weapon1 = NULL;
				return tmp;
			}else if(weapon2 != NULL){
				tmp = weapon2;
				weapon2 = NULL;
				return tmp;
			}
			return NULL;
		}
		int  get_power(bool) const override;
		void shoot(Warrior*, const myTime&) override ;
		bool has_bomb() const override;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		void killed(const myTime&) override;
		void win(Warrior*,int,const myTime&) override;
		void deuce(Warrior*,const myTime&) override;
		void collect_lifeValue(int, const myTime&) const override;
	private:
		Weapon *weapon1;
		Weapon *weapon2;
		const static string name;
};

class Dragon: public Warrior{
	public:
		Dragon(Headquarter* master_, int lifeValue_, int warriorNum_, double morale_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_), morale(morale_), cheer(false){
			switch(warriorNum_%3){
				case 0:
					if(atk_/5==0)
						weapon = NULL;
					else
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
			cout << "Its morale is " << setiosflags(ios::fixed) << setprecision(2) 
				 << morale << endl;
		}
		void print_wpMessage(const myTime &time) const {
			time.print_time();		
			cout << " " << msName << " " << name << " " << warriorNum << " has ";
			if(weapon==NULL)	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		string get_warriorName() const {return name;}

		int  get_power(bool) const override;
		void shoot(Warrior*, const myTime&) override ;
		bool has_bomb() const override;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		void killed(const myTime&) override;
		void win(Warrior*,int,const myTime&) override;
		void deuce(Warrior*,const myTime&) override;
		void collect_lifeValue(int, const myTime&) const override;
		void set_cheer() override;
		Weapon *seizedWp() override {Weapon* tmp = weapon; weapon = NULL; return tmp;}
	private:
		Weapon *weapon;	
		double morale;
		bool cheer;
		const static string name;
};

const string Iceman::name	= "iceman";
const string Lion::name 	= "lion";
const string Wolf::name 	= "wolf";
const string Ninja::name 	= "ninja";
const string Dragon::name 	= "dragon";



class City{
	public:
		City(int ID_, int lifeValue_):cityID(ID_), lifeValue(lifeValue_), flagID(0), red(NULL), blue(NULL), lastRed(NULL), lastBlue(NULL){flagCount[1]=0;flagCount[2]=0;}
		City(int ID_):cityID(ID_), lifeValue(0), flagID(0), red(NULL), blue(NULL), lastRed(NULL), lastBlue(NULL){flagCount[1]=0;flagCount[2]=0;}

		void march_fromSide(City* ,const myTime&);
		void march_fromSide(Headquarter*, const myTime&);
		void march_prepare();
		void lion_escape(const myTime&);
		void gen_life(int life = 10){lifeValue+=10;}
		void exclusive(const myTime&);
		void shoot_toNext(City*, const myTime&);
		void use_bomb(const myTime&);
		void warrior_fight(const myTime&);
		void fight_settle(const myTime&);
		void raise_flag(const myTime&);
		void reward_life();
		void report_weapon(int msID, const myTime &time);

		friend class Headquarter;
	private:
		int cityID;
		int lifeValue;
		int flagCount[3];
		int flagID;
		Warrior *red;
		Warrior *blue;
		Warrior *lastRed;
		Warrior *lastBlue;

};

class Headquarter{
	public:
		Headquarter()	= default;
		Headquarter(string name_, int baseLife_, vector <int> wLife_, vector <int> wAtk_, vector <int> order):
			name(name_), lifeEnough(true), lifeValue(baseLife_), warriorLife(wLife_), warriorAtk(wAtk_), createOrder(order), nextCreate(createOrder.begin()), nextNum(1), taken(false), fbValue(0), takenCount(0), curWarrior(NULL), enemyWarrior(NULL){}

		bool get_lifeStatus(){return lifeEnough;}
		string get_name(){return name;}
		//void print_curwpMessage(myTime time) const { if(curWarrior!=NULL){time.print_time(); cout << " "; curWarrior->print_wpMessage();}}
		bool be_taken(const myTime&) const ;
		bool create_warrior(myTime);
		void print_bornMessage(myTime, const Warrior&);
		void march_fromCity(City *, const myTime&);
		void lion_escape(const myTime&);
		void get_fbValue(int fbValue_){fbValue += fbValue_;}
		void set_fbValue(){lifeValue += fbValue; fbValue = 0;}
		void reward_life(Warrior* a){if(lifeValue>=8){a->life_add(8); lifeValue-=8;}}
		void report_lifeValue(const myTime&);
		void report_weapon(const myTime &time);

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
		int fbValue;
		int takenCount;
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


void Iceman::shoot(Warrior* enemy, const myTime& time) {
	if(weapon!=NULL)
		if(weapon->get_wpType() == 2){
			Arrow* tmp = dynamic_cast<Arrow*>(weapon);
			enemy->lifeValue -= tmp->atk;
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
			time.print_time();
			cout << " " << msName << " " << name << " " << warriorNum << " shot"; 			
			if(enemy->lifeValue <= 0){
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << enemy->warriorNum;
				enemy->dieArrow = true;
			}
			cout << endl;
		}
}

void Lion::shoot(Warrior* enemy, const myTime& time) {
}

void Wolf::shoot(Warrior* enemy, const myTime& time) {
	if(weapon!=NULL)
		if(weapon->get_wpType() == 2){
			Arrow* tmp = dynamic_cast<Arrow*>(weapon);
			enemy->lifeValue -= tmp->atk;
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
			time.print_time();
			cout << " " << msName << " " << name << " " << warriorNum << " shot"; 			
			if(enemy->lifeValue <= 0){
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << enemy->warriorNum;
				enemy->dieArrow = true;
			}
			cout << endl;
		}
}
void Ninja::shoot(Warrior* enemy, const myTime& time) {
	if(weapon1!=NULL)
		if(weapon1->get_wpType() == 2){
			Arrow* tmp = dynamic_cast<Arrow*>(weapon1);
			enemy->lifeValue -= tmp->atk;
			if(tmp->consume()){
				delete tmp;
				weapon1 = NULL;
			}
			time.print_time();
			cout << " " << msName << " " << name << " " << warriorNum << " shot"; 			
			if(enemy->lifeValue <= 0){
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << enemy->warriorNum;
				enemy->dieArrow = true;
			}
			cout << endl;
		}
	if(weapon2!=NULL)
		if(weapon2->get_wpType() == 2){
			Arrow* tmp = dynamic_cast<Arrow*>(weapon2);
			enemy->lifeValue -= tmp->atk;
			if(tmp->consume()){
				delete tmp;
				weapon2 = NULL;
			}
			time.print_time();
			cout << " " << msName << " " << name << " " << warriorNum << " shot"; 			
			if(enemy->lifeValue <= 0){
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << enemy->warriorNum;
				enemy->dieArrow = true;
			}
			cout << endl;
		}
}
void Dragon::shoot(Warrior* enemy, const myTime& time) {
	if(weapon!=NULL)
		if(weapon->get_wpType() == 2){
			Arrow* tmp = dynamic_cast<Arrow*>(weapon);
			enemy->lifeValue -= tmp->atk;
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
			time.print_time();
			cout << " " << msName << " " << name << " " << warriorNum << " shot"; 

			if(enemy->lifeValue <= 0){
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << enemy->warriorNum;
				enemy->dieArrow = true;
			}
			cout << endl;
		}
}

int Iceman::get_power(bool half=false) const{
	int damage = atk;
	if(half) damage/=2;

	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			}
	return damage;
}
int Lion::get_power(bool half=false) const{
	int damage = atk;
	if(half) damage/=2;
	return damage;
}
int Wolf::get_power(bool half=false) const{
	int damage = atk;
	if(half) damage/=2;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			}
	return damage;
}
int Ninja::get_power(bool half=false) const{
	int damage = atk;
	if(half) damage/=2;
	if(weapon1!=NULL)
		if(weapon1->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon1);
			damage += tmp->get_atk();
		}
	if(weapon2!=NULL)
		if(weapon2->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon2);
			damage += tmp->get_atk();
		}
	return damage;
}
int Dragon::get_power(bool half=false) const{
	int damage = atk;
	if(half) damage/=2;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			}
	return damage;
}

int Warrior::get_power2(bool half=false) const{
	int damage = atk;
	if(half) 
		damage/=2;
	return damage;
}

bool Iceman::has_bomb() const {
	if(weapon!=NULL)
		if (weapon->get_wpType()==1)
			return true;
	return false;
}
bool Lion::has_bomb() const {
	return false;
}
bool Wolf::has_bomb() const {
	if(weapon!=NULL)
		if (weapon->get_wpType()==1)
			return true;
	return false;
}
bool Ninja::has_bomb() const {
	if(weapon1!=NULL)
		if (weapon1->get_wpType()==1)
			return true;
	if(weapon2!=NULL)
		if (weapon2->get_wpType()==1)
			return true;
	return false;
}
bool Dragon::has_bomb() const {
	if(weapon!=NULL)
		if (weapon->get_wpType()==1)
			return true;
	return false;
}
bool Warrior::use_bomb(Warrior* enemy, bool attack, const myTime& time){
if(has_bomb()){
	if(attack){
		if(enemy->get_lifeValue() > get_power(false))
			if(lifeValue <= enemy->get_power(true)&&enemy->get_warriorName()!="ninja"){
				time.print_time();
				cout << " " << get_msName() << " " << get_warriorName() << " " << get_warriorNum() << " used a bomb and killed " << enemy->get_msName() << " " << enemy->get_warriorName() << " " << enemy->get_warriorNum() << endl;
				return true;
			}
	}else if(lifeValue <= enemy->get_power(false)){
		time.print_time();
		cout << " " << get_msName() << " " << get_warriorName() << " " 
			 << get_warriorNum() <<" used a bomb and killed " << enemy->get_msName()
			 << " " << enemy->get_warriorName() << " " << enemy->get_warriorNum()
			 << endl;
		return true;
	}
}
	return false;
}

void Iceman::attack(Warrior* enemy, const myTime& time) {
	int damage = atk;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
}

void Lion::attack(Warrior* enemy, const myTime& time) {
	int damage = atk;
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
}

void Wolf::attack(Warrior* enemy, const myTime& time) {
	int damage = atk;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
}

void Ninja::attack(Warrior* enemy, const myTime& time) {
	int damage = atk;
	if(weapon1!=NULL)
		if(weapon1->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon1);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon1 = NULL;
			}
		}
	if(weapon2!=NULL)
		if(weapon2->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon2);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon2 = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
}

inline void Dragon::set_cheer(){
	cheer = true;
}
void Dragon::attack(Warrior* enemy, const myTime& time) {
	cheer = true;

	int damage = atk;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
}

inline void Warrior::req_reward(){
	if(wonFlag == true){
		master->reward_life(this);
		wonFlag = false;
	}
}

void Iceman::counter(Warrior* enemy, const myTime &time){
	if(lifeValue <= 0) 
		return;
	int damage = atk/2;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum <<" fought back against "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << endl;
}

void Lion::counter(Warrior* enemy, const myTime &time){
	if(lifeValue <= 0) 
		return;
	int damage = atk/2;
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum <<" fought back against "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << endl;
}

void Wolf::counter(Warrior* enemy, const myTime &time){
	if(lifeValue <= 0) 
		return;
	int damage = atk/2;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum <<" fought back against "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << endl;
}

void Ninja::counter(Warrior* enemy, const myTime &time){}

void Dragon::counter(Warrior* enemy, const myTime &time){
	if(lifeValue <= 0) 
		return;
	int damage = atk/2;
	if(weapon!=NULL)
		if(weapon->get_wpType() == 0){
			Sword *tmp = dynamic_cast<Sword*>(weapon);
			damage += tmp->get_atk();
			if(tmp->consume()){
				delete tmp;
				weapon = NULL;
			}
		}
	enemy->life_sub(damage);
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum <<" fought back against "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << endl;
}
void Iceman::killed(const myTime &time){
	if(lifeValue <= 0 && dieFight){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum << " was killed in "
			 << "city " << cityID << endl;
	}
}
void Lion::killed(const myTime &time){
	if(lifeValue <= 0 && dieFight){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum << " was killed in "
			 << "city " << cityID << endl;
	}
}
void Wolf::killed(const myTime &time){
	if(lifeValue <= 0 && dieFight){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum << " was killed in "
			 << "city " << cityID << endl;
	}
}
void Ninja::killed(const myTime &time){
	if(lifeValue <= 0 && dieFight){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum << " was killed in "
			 << "city " << cityID << endl;
	}
}
void Dragon::killed(const myTime &time){
	if(lifeValue <= 0 && dieFight){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum << " was killed in "
			 << "city " << cityID << endl;
	}
}

void Iceman::win(Warrior* enemy, int cityValue, const myTime &time){
	wonFlag = true;
	master->get_fbValue(cityValue);	
	if(enemy->get_warriorName() == "lion" && enemy->dieFight)
		lifeValue += enemy->get_lastLife();
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}
void Lion::win(Warrior* enemy, int cityValue, const myTime &time){
	wonFlag = true;
	master->get_fbValue(cityValue);	
	if(enemy->get_warriorName() == "lion" && enemy->dieFight)
		lifeValue += enemy->get_lastLife();
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}
void Wolf::win(Warrior* enemy, int cityValue, const myTime &time){
	wonFlag = true;
	if(weapon==NULL)
		weapon = enemy->seizedWp();
	if(enemy->get_warriorName() == "lion" && enemy->dieFight)
		lifeValue += enemy->get_lastLife();
	master->get_fbValue(cityValue);	
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}
void Ninja::win(Warrior* enemy, int cityValue, const myTime &time){
	wonFlag = true;
	master->get_fbValue(cityValue);	
	if(enemy->get_warriorName() == "lion" && enemy->dieFight)
		lifeValue += enemy->get_lastLife();
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}
void Dragon::win(Warrior* enemy, int cityValue, const myTime &time){
	wonFlag = true;
	master->get_fbValue(cityValue);	
	if(enemy->get_warriorName() == "lion" && enemy->dieFight)
		lifeValue += enemy->get_lastLife();
	morale -= 0.2;
	if(morale > 0.8 && cheer){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum <<" yelled in city "
			 << cityID << endl;
		cheer = false;
	}
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}

void Iceman::collect_lifeValue(int cityValue, const myTime& time) const {
	master->get_fbValue(cityValue);	
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}

void Lion::collect_lifeValue(int cityValue, const myTime& time) const {
	master->get_fbValue(cityValue);	
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}

void Wolf::collect_lifeValue(int cityValue, const myTime& time) const {
	master->get_fbValue(cityValue);	
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}

void Ninja::collect_lifeValue(int cityValue, const myTime& time) const {
	master->get_fbValue(cityValue);	
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}

void Dragon::collect_lifeValue(int cityValue, const myTime& time) const {
	master->get_fbValue(cityValue);	
	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " earned "
		 << cityValue << " elements for his headquarter" << endl;
}

void Iceman::deuce(Warrior* enemy, const myTime &time){wonFlag = false;}
void Lion::deuce(Warrior* enemy, const myTime &time){
	loyalty -= k;
	wonFlag = false;
}
void Wolf::deuce(Warrior* enemy, const myTime &time){wonFlag = false;}
void Ninja::deuce(Warrior* enemy, const myTime &time){wonFlag = false;}
void Dragon::deuce(Warrior* enemy, const myTime &time){
	wonFlag = false;
	morale -= 0.2;
	if(morale >= 0.8 && cheer){
		time.print_time();
		cout << " " << msName << " " << name << " " << warriorNum <<" yelled in city "
			 << cityID << endl;
		cheer = false;
	}
}

void City::lion_escape(const myTime& time){
	Lion *tmp;
	tmp = dynamic_cast<Lion*>(red);
	if(tmp != NULL)
		if(tmp->escape(time)){
			delete tmp;
			red = NULL;
		}

	tmp = dynamic_cast<Lion*>(blue);
	if(tmp != NULL)
		if(tmp->escape(time)){
			delete tmp;
			red = NULL;
		}
	
}

void City::exclusive(const myTime &time){
	if(red!=NULL && blue==NULL){
		red->collect_lifeValue(lifeValue,time);	
		lifeValue = 0;
	}else if(red==NULL && blue!=NULL){
		blue->collect_lifeValue(lifeValue,time);
		lifeValue = 0;
	}
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
			this->red->march(cityID);
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
			this->blue->march(cityID);
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
			this->red->march(cityID);
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
			this->blue->march(cityID);
			time.print_time();
			cout << " " << blue->master->get_name() << " " << blue->get_warriorName() 
				 << " " << blue->get_warriorNum() << " marched to city " << cityID
				 << " with " << blue->get_lifeValue() << " elements and force "
				 << blue->get_atk() << endl;
		}
	}
}
void City::use_bomb(const myTime &time){
	if(red!=NULL && blue!=NULL){
		if(red->get_lifeValue() > 0 && blue->get_lifeValue() > 0){
			if(flagID == 0){
				if(cityID%2 == 1){
					if(red->use_bomb(blue, 1, time)){
						delete red;
						delete blue;
						red = NULL;
						blue = NULL;
					}else if(blue->use_bomb(red, 0, time)){
						delete red;
						delete blue;
						red = NULL;
						blue = NULL;
					}
				}else {
					if(blue->use_bomb(red, 1, time)){
						delete red;
						delete blue;
						red = NULL;
						blue = NULL;
					}else if(red->use_bomb(blue, 0, time)){
						delete red;
						delete blue;
						red = NULL;
						blue = NULL;
					}
				}
			}else if(flagID == 1){
				if(red->use_bomb(blue, 1, time)){
					delete red;
					delete blue;
					red = NULL;
					blue = NULL;
				}else if(blue->use_bomb(red, 0, time)){
					delete red;
					delete blue;
					red = NULL;
					blue = NULL;
				}
			}else if(flagID == 2){
				if(blue->use_bomb(red, 1, time)){
					delete red;
					delete blue;
					red = NULL;
					blue = NULL;
				}else if(red->use_bomb(blue, 0, time)){
					delete red;
					delete blue;
					red = NULL;
					blue = NULL;
				}
			}else {
				cout << "********error flagID********" << endl;
			}
		}
	}
	
}

void City::shoot_toNext(City* next, const myTime &time){
	if(next == NULL)
		cout << "*******the next* is invalid!!********" << endl;
	if(next->cityID > this->cityID){	
		if(red!=NULL && next->blue!=NULL)
			red->shoot(next->blue, time);
	}else if(next->cityID < this->cityID){
		if(blue!=NULL && next->red!=NULL)
			blue->shoot(next->red, time);
	}else
		cout << "******error city input(same) for shoot***********" << endl;
		
}

void City::warrior_fight(const myTime &time){
	if(red!=NULL && blue!=NULL){
		if(red->get_lifeValue() > 0 && blue->get_lifeValue() > 0){
			if(flagID == 0){
				if(cityID%2 == 1){
					red->attack(blue, time);
					blue->counter(red, time);
					red->killed(time);
					blue->killed(time);
				}else {
					blue->attack(red, time);
					red->counter(blue, time);
					red->killed(time);
					blue->killed(time);
				}
			}else if(flagID == 1){
				red->attack(blue, time);
				blue->counter(red, time);
				red->killed(time);
				blue->killed(time);
			}else if(flagID == 2){
				blue->attack(red, time);
				red->counter(blue, time);
				red->killed(time);
				blue->killed(time);
			}else {
				cout << "********error flagID********" << endl;
			}
		}else {
			if(flagID == 0){
				if(cityID%2 == 1){
					red->set_cheer();
				}else {
					blue->set_cheer();
				}
			}else if(flagID == 1){
				red->set_cheer();
			}else if(flagID == 2){
				blue->set_cheer();
			}
		}
	}
}

void City::fight_settle(const myTime& time){
	if(red!=NULL && blue!=NULL){
		if(red->get_lifeValue() >0 && blue->get_lifeValue() >0){
			red->deuce(blue, time);
			blue->deuce(red, time);
			flagCount[1] = 0;
			flagCount[2] = 0;
			raise_flag(time);
		} else if(red->get_lifeValue() <=0 && blue->get_lifeValue() >0){
			blue->win(red, lifeValue, time);
			lifeValue = 0;
			delete red;
			red = NULL;

			flagCount[2] ++;
			flagCount[1] = 0;
			raise_flag(time);
		} else if(red->get_lifeValue() >0 && blue->get_lifeValue() <=0){
			red->win(blue, lifeValue, time);
			lifeValue = 0;
			delete blue;
			blue = NULL;

			flagCount[1] ++;
			flagCount[2] = 0;
			raise_flag(time);
		} else {
			cout << "********error fight settle(all die)*********" << endl;
		}
	}else if(red!=NULL && red->get_lifeValue() <= 0){
		delete red;
		red = NULL;
	}else if(blue!=NULL && blue->get_lifeValue() <= 0){
		delete blue;
		blue = NULL;
	}
}

void City::raise_flag(const myTime &time){
	if(flagCount[1] == 2){
		if(flagID!=1){
			flagID = 1;
			time.print_time();
			cout << " red flag raised in city " << cityID << endl; 
		}
	}
	if(flagCount[2] == 2){
		if(flagID!=2){
			flagID = 2;
			time.print_time();
			cout << " blue flag raised in city " << cityID << endl; 
		}
	}
	//if(flagCount[1] < 2 && flagCount[2] < 2)
	//	flagID = 0;
	if(flagCount[1] >= 2 && flagCount[2] >= 2)
		cout << "*********erro flagCount in raise_flag(all gt 2)********" << endl;
}

void City::reward_life(){
	if(red!=NULL)
		red->req_reward();
	if(blue!=NULL)
		blue->req_reward();
}

void City::report_weapon(int msID, const myTime &time){
	if(msID==1){
		if(red!=NULL)
			red->print_wpMessage(time);
	}else if(msID==2){
		if(blue!=NULL)
			blue->print_wpMessage(time);
	}else{
		cout << "**************error msID in report_weapon**********" << endl;
	}
}

void Headquarter::lion_escape(const myTime &time){
	Lion *tmp;
	tmp = dynamic_cast<Lion*>(curWarrior);
	if(tmp != NULL)
		if(tmp->escape(time)){
			delete tmp;
			curWarrior = NULL;
		}
}

void Headquarter::march_fromCity(City *side, const myTime &time){
	if(this->get_name() == "red"){
		//if(this->enemyWarrior!=NULL)
		//	cout << "************red enemyWarrior is not NULL!!************" << endl;
		if(side->lastBlue!=NULL){
			this->enemyWarrior = side->lastBlue;
			side->lastBlue = NULL;
			this->enemyWarrior->march(0);
			time.print_time();
			cout << " " << enemyWarrior->get_msName() << " " 
				 << enemyWarrior->get_warriorName()
				 << " " << enemyWarrior->get_warriorNum() << " reached " << name 
				 << " headquarter with " << enemyWarrior->get_lifeValue()
				 << " elements and force " << enemyWarrior->get_atk() << endl;
			takenCount ++;
			if(takenCount >= 2)
				taken = true;
		}
	}
	if(this->get_name() == "blue"){
		//if(this->enemyWarrior!=NULL)
		//	cout << "************blue enemyWarrior is not NULL!!************" << endl;
		if(side->lastRed!=NULL){
			this->enemyWarrior = side->lastRed;
			side->lastRed = NULL;
			this->enemyWarrior->march(0);
			time.print_time();
			cout << " " << enemyWarrior->get_msName() << " " 
				 << enemyWarrior->get_warriorName()
				 << " " << enemyWarrior->get_warriorNum() << " reached " << name 
				 << " headquarter with " << enemyWarrior->get_lifeValue()
				 << " elements and force " << enemyWarrior->get_atk() << endl;
			takenCount ++;
			if(takenCount >= 2)
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
inline void Headquarter::report_lifeValue(const myTime &time){
	time.print_time();
	cout << " " << lifeValue << " elements in " << name << " headquarter" << endl;
}

inline void Headquarter::report_weapon(const myTime &time){
	if(enemyWarrior!=NULL)
		enemyWarrior->print_wpMessage(time);
}

