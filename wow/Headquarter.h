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
			master(master_), lifeValue(lifeValue_), warriorNum(warriorNum_), typeNum(typeNum_), atk(atk_), cityID(cityID_), dieArrow(0), dieFight(0), dieBomb(0), msName(msName_){}

		int get_warriorNum() const {return warriorNum;}
		int get_lifeValue() const {return lifeValue;}
		int get_typeNum() const {return typeNum;}
		int get_atk() const {return atk;}
		void life_dec(int a){lifeValue-=a;}
		string get_msName() const {return msName;}
		virtual void print_exMessage() const = 0;
		virtual void print_wpMessage() const = 0;
		virtual string get_warriorName() const = 0;
		virtual void march(int cityID_){cityID = cityID_;}
		virtual void shoot(Warrior*, const myTime&) = 0;
		virtual void attack(Warrior*, const myTime&) = 0;
		virtual void counter(Warrior*, const myTime&) = 0;
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
		string msName;
};

class Iceman: public Warrior{
	public:
		Iceman(Headquarter* master_, int lifeValue_, int warriorNum_, int typeNum_, int atk_, string msName_):
			Warrior(master_, lifeValue_, warriorNum_, typeNum_, atk_, msName_){
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
		void print_wpMessage() const override {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon==NULL)	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		void march(int cityID_) override{
			if(lifeValue > 9)
				lifeValue -= 9;
			else
				lifeValue = 1;
			atk += 20;
			cityID = cityID_;
		}
		void shoot(Warrior*, const myTime&) override ;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
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
		bool escape(const myTime &time) const {
			if(loyalty <= 0){
				time.print_time();
				cout << " " << msName << " " << name << " " << warriorNum << " ran away" << endl;
				return true;
			}
			return false;
		}
		void shoot(Warrior*, const myTime&) override ;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		static int k;
	private:
		int loyalty;
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
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon==NULL)	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		void shoot(Warrior*, const myTime&) override ;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
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
					if(atk_/5==0)
						weapon1 = NULL;
					else
						weapon1 = new Sword(atk_/5);
					weapon2 = new Bomb();
					break;
				case 1:
					weapon1 = new Bomb;
					weapon2 = new Arrow(3);
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
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has ";
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
		void shoot(Warrior*, const myTime&) override ;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
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
			cout << "it's morale is " << setiosflags(ios::fixed) << setprecision(2) 
				 << morale << endl;
		}
		void print_wpMessage() const {
			cout << msName << " " << name << " " << warriorNum << " has ";
			if(weapon==NULL)	
				cout << "no weapon" << endl;
			else
				cout << weapon->get_wpMessage() << endl;
		}
		void shoot(Warrior*, const myTime&) override ;
		void attack(Warrior*, const myTime&) override;
		void counter(Warrior*, const myTime&) override;
		
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

//void Iceman::killed(const myTime &time){
//	if(lifeValue <= 0)
//		cout << " " << msName << " " << name << " " << warriorNum << " was killed in "
//			 << "city " << cityID << endl;
//	
//}

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
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << warriorNum;
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
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << warriorNum;
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
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << warriorNum;
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
				cout << " and killed " << enemy->msName << " " << enemy->get_warriorName() << " " << warriorNum;
				enemy->dieArrow = true;
			}
			cout << endl;
		}
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
	enemy->lifeValue -= damage;
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
	enemy->lifeValue -= damage;
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
	enemy->lifeValue -= damage;
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
	enemy->lifeValue -= damage;
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
}

void Dragon::attack(Warrior* enemy, const myTime& time) {
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
	enemy->lifeValue -= damage;
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum << " attacked "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << " with " << lifeValue
		 << " elements and force " << atk << endl;
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
	enemy->lifeValue -= damage;
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
	enemy->lifeValue -= damage;
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
	enemy->lifeValue -= damage;
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
	enemy->lifeValue -= damage;
	if(enemy->lifeValue <= 0 )
		enemy->dieFight = true;

	time.print_time();
	cout << " " << msName << " " << name << " " << warriorNum <<" fought back against "
		 << enemy->get_msName() << " " << enemy->get_warriorName() << " " 
		 << enemy->warriorNum << " in city " << cityID << endl;
}

class City{
	public:
		City(int ID_, int lifeValue_):cityID(ID_), lifeValue(lifeValue_), flagID(0), red(NULL), blue(NULL), lastRed(NULL), lastBlue(NULL){flagCount[1]=0;flagCount[2]=0;}
		City(int ID_):cityID(ID_), lifeValue(0), flagID(0), red(NULL), blue(NULL), lastRed(NULL), lastBlue(NULL){flagCount[1]=0;flagCount[2]=0;}

		void warrior_fight(myTime &);
		void march_fromSide(City* ,const myTime&);
		void march_fromSide(Headquarter*, const myTime&);
		void march_prepare();
		void lion_escape(const myTime&);
		void shoot_toNext(City*, const myTime&);

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
			name(name_), lifeEnough(true), lifeValue(baseLife_), warriorLife(wLife_), warriorAtk(wAtk_), createOrder(order), nextCreate(createOrder.begin()), nextNum(1), taken(false), curWarrior(NULL), enemyWarrior(NULL){}

		bool get_lifeStatus(){return lifeEnough;}
		string get_name(){return name;}
		void print_curwpMessage(myTime time) const { if(curWarrior!=NULL){time.print_time(); cout << " "; curWarrior->print_wpMessage();}}
		bool be_taken(const myTime&) const ;
		bool create_warrior(myTime);
		void print_bornMessage(myTime, const Warrior&);
		void march_fromCity(City *, const myTime&);
		void lion_escape(const myTime&);

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

void City::warrior_fight(myTime &time){
	if(red!=NULL && blue!=NULL){
		if(red->get_lifeValue() > 0 && blue->get_lifeValue() > 0){
			if(flagID == 0){
				if(cityID%2 == 1){
					red->attack(blue, time);
					blue->counter(red, time);
				}else {
					blue->attack(red, time);
					red->counter(blue, time);
				}
			}else if(flagID == 1){
				red->attack(blue, time);
				blue->counter(red, time);
			}else if(flagID == 2){
				blue->attack(red, time);
				red->counter(blue, time);
			}else {
				cout << "********error flagID********" << endl;
			}
		}
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
		if(this->enemyWarrior!=NULL)
			cout << "************red enemyWarrior is not NULL!!************" << endl;
		if(side->lastBlue!=NULL){
			this->enemyWarrior = side->lastBlue;
			side->lastBlue = NULL;
			this->enemyWarrior->march(0);
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
			this->enemyWarrior->march(0);
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
