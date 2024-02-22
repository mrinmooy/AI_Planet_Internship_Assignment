#include<iostream>
#include<tuple>
#include<vector>
#include"whatsapp.hpp"
using namespace std;
struct Envelope {
	string text; int order,sender,receiver;
	Envelope(string t,int o,int s,int r): text(t),order(o),sender(s),receiver(r){}
};   

void readInput(vector<Envelope>&DataBase){
	int tnof_mssgs; cin>>tnof_mssgs;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for(int i=0;i<tnof_mssgs;i++){
		string stuff; int rank,mouth,ear;
		 getline(cin >> ws, stuff);
		cin>>rank>>mouth>>ear;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		DataBase.emplace_back(stuff,rank,mouth,ear);
	}
}

int main(){
	vector<Envelope> DataBase{
		//{"hello",1,1,0},
		//{"mister/miss",1,1,0},
		//{"how's your day been??",1,1,0}
	};

	readInput(DataBase);
	
	vector<int> notifications(8);
	vector<vector<tuple<string,int,int>>>MailBag(8);  
	for(auto &o: DataBase){
		notifications[o.receiver] = notifications[o.receiver] + 1;
		MailBag[o.sender].emplace_back(o.text,o.order,o.receiver);
	}
	WhatsApp myPool(notifications,MailBag);

	return 0;
}

