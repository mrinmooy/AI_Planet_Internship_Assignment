#ifndef POSTOFFICE_HPP
#define POSTOFFICE_HPP
#include<mutex>
#include<queue>
#include<vector>
using namespace std;
struct Mail{
		string data; int source, destination;
		Mail(string dt="..No Messages..",int src=-1,int dst=-1): data(dt),source(src),destination(dst){}

};
class PostOffice{
public:
	mutex postman;
	struct MailComparator {
	    bool operator()(pair<int,Mail>& a, pair<int,Mail>& b){
	        return a.first>b.first;
	    }
	};
	priority_queue<pair<int,Mail>,vector<pair<int,Mail>>,MailComparator> PObox;
	void enqueue(string data, int sender, int receiver,int preference){
		lock_guard<mutex> gate(postman);
		Mail new_mail(data,sender,receiver);
		PObox.push({preference,new_mail});
	}
	pair<int,Mail> dequeue(){
		lock_guard<mutex> gate(postman);
		if(PObox.empty()) return {0,Mail()};
		auto Mail = PObox.top();
		PObox.pop();
		return Mail;
	}
	pair<int,Mail> peek(){
		lock_guard<mutex> gate(postman);
		if(PObox.empty()) return {0,Mail()};
		auto Mail = PObox.top();
		return Mail;
	}
	bool empty_check(){
		lock_guard<mutex> gate(postman);
		return PObox.empty();
	}
};
#endif 
