#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
using namespace std;


const string weapon[]={"sword","bomb","arrow"};

class warrior{
public:
  int num;
  int life;
  warrior(int n,int l):num(n),life(l){
    //cout << n << " " << l << endl;
  }
  virtual void show(){;};
};
class dragon:public warrior{
public:
  int wepn;
  float morale;
  dragon(int n,int l,float mor):warrior(n,l),morale(mor){
    wepn = n%3;
    show();
  }
  void show(){
    cout << "It has a " + weapon[wepn]+",and it's morale is " 
	 << fixed << setprecision(2) << morale << endl;
  }
};

class ninja:public warrior{
public:
  int wepn[2];
  ninja(int n,int l):warrior(n,l){
    wepn[0] = n%3;
    wepn[1] = (n+1)%3;
    //cout << wepn[1];
    show();
  }
  void show(){
    //cout << wepn[0] << endl;
    cout << "It has a " + weapon[wepn[0]] << " and a " + weapon[wepn[1]] << endl;
  }
};

class iceman:public warrior{
public:
  int wepn;
  iceman(int n,int l):warrior(n,l){
    wepn = n%3;
    show();
  }
  void show(){
    cout << "It has a " + weapon[wepn] << endl;
  }
};
class lion:public warrior{
public:
  int loyalty;
  lion(int n,int l,int loyal):warrior(n,l){
    loyalty = loyal;
    show();
  }
  void show(){
    cout << "It's loyalty is " << loyalty << endl;
  }
};
class wolf:public warrior{
public:
  wolf(int n,int l):warrior(n,l){};
  void show(){}
};


class head{
private:
  string head_colour;
  string sort[5];
  int num[5];//={0,0,0,0,0};
  int life[5];
  int total_life;
  int time;//=0;
  bool runout;// = false;
  int ind;// = 0;
  int count;// = 0;
public:
  head(string _head_co,string _sort[],int _life[], int _t_life)
  {
    //num={0,0,0,0,0};
    fill_n(num,5,0);
    time = 0;
    runout = 0;
    ind = 0;
    count = 0;
    total_life=_t_life;
    head_colour=_head_co;
    copy(_sort,_sort+5,sort);
    copy(_life,_life+5,life);
  }
  // ~head(){delete *p;}
  bool is_stoped(){return runout;}
  void produce();
private:
  warrior* make_warrior(int,int);
};

warrior* head::make_warrior(int ind,int left_life){
  //cout << "make_warrior" << ind << "  " << left_life << "  " << sort[ind] << endl;
  if(sort[ind]=="dragon"){
    return new dragon(count,life[ind],float(left_life)/life[ind]);
  }
  else if(sort[ind]=="ninja"){
    //cout << "ninjia " << count << "****" << life[ind] << endl;
    return new ninja(count,life[ind]);
  }
  else if(sort[ind]=="iceman"){
    return new iceman(count,life[ind]);
  }
  else if(sort[ind]=="lion"){
    return new lion(count,life[ind],left_life);
  }
  else if(sort[ind]=="wolf"){
    return new wolf(count,life[ind]);
  }
}


void head::produce(){
  //    time+=1;
  int real_ind = ind % 5;
    if(runout) return;
    int i = 0;
    for(;total_life < life[(real_ind+i)%5] && i < 5;i++);
    if(i == 5)
      {
	cout << setfill('0') << setw(3) << count << ' '
	     << head_colour << " headquarter stops making warriors"
	     << endl;
	runout = true;
	return;
      }
    real_ind = (real_ind + i)%5;
    if(total_life >= life[real_ind])
      {
	total_life -= life[real_ind];
	num[real_ind] +=1;
	count +=1;
	cout << setfill('0') << setw(3) << count-1 << ' '
	     << head_colour <<' ' << sort[real_ind] << ' ' << count 
	     << " born with strength "
	     << life[real_ind] <<',' <<  num[real_ind] 
	     << ' ' << sort[real_ind]
	     << " in " << head_colour << " headquarter" << endl;
	//cout << real_ind << " )))  " << total_life << endl;
	warrior* wp = make_warrior(real_ind,total_life);
	//warrior* wp = make_warrior(1,2);
	//(*wp).show();
	//delete wp;
	//cout << total_life << endl;
	ind = ind + i + 1;
      }
    return;
  }


int main(){

  //warrior* tp = new ninjia(1,2);

  int n_case;
  cin >> n_case;
  int lifes[n_case][5];
  int n_life[n_case];
  for(int i = 0;i<n_case;i++){
    cin >> n_life[i];
    for(int j = 0;j< 5;j++){
      cin >> lifes[i][j];
    }
  }
  for(int m = 0;m<n_case;m++){
    int life[5];
    //    copy(lifes[m][0],lifes[m][4],life);
    for(int t = 0;t<5;t++)
      life[t] = lifes[m][t];
    cout << "Case:" << m+1 << endl;
    string red_sort[] = {"iceman","lion","wolf","ninja","dragon"};
    string blue_sort[] = {"lion","dragon","ninja","iceman","wolf"};
    int red_life[] = {life[2],life[3],life[4],life[1],life[0]};
    int blue_life[] = {life[3],life[0],life[1],life[2],life[4]};
    head red("red",red_sort,red_life,n_life[m]);
    head blue("blue",blue_sort,blue_life,n_life[m]);
    while(!red.is_stoped() || !blue.is_stoped())
      {
	if(!red.is_stoped()) red.produce();
	if(!blue.is_stoped()) blue.produce();
      }
  }
  return 0;
}
