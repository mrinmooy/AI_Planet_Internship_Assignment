#ifndef WHATSAPP_HPP
#define WHATSAPP_HPP
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<vector>
#include"postoffice.hpp"
#define ss second
using namespace std;
class WhatsApp{
public:
	mutex stamp;
	PostOffice Telegram;
	condition_variable 	_op_;	
	vector<thread> transceivers;
	void _post(tuple<string,int,int> packet,int idx){	
		Telegram.enqueue(get<0>(packet),idx,get<2>(packet),get<1>(packet));
	}
	void _log(Mail myMail){
		cout<<myMail.source<<" said,'"<<myMail.data<<"',to "<<myMail.destination<<"\n";
	}
	void routine(vector<tuple<string,int,int>>&MailsFromMe,int MyNotifs,int _id){
		for(auto o: MailsFromMe){
			unique_lock<mutex> chain(stamp);
			if((Telegram.peek().ss).destination==_id){
				_log(Telegram.dequeue().ss);
				MyNotifs = MyNotifs - 1;
				_op_.notify_all();
			}
			_post(o,_id);
			_op_.notify_all();
			
		} 
		while(MyNotifs>0){
			unique_lock<mutex> chain(stamp);
			auto top_data = Telegram.peek();
			if((top_data.ss).destination==_id){
				_log(Telegram.dequeue().ss);
				MyNotifs = MyNotifs - 1;
				_op_.notify_all();
				
			}else{
				_op_.wait(chain);
			}
		}			
	}
	WhatsApp(vector<int>&notifications,vector<vector<tuple<string,int,int>>>&MailBag){
		for(int i=0;i<8;i++){
			transceivers.emplace_back(
				thread(
					&WhatsApp::routine,this,ref(MailBag[i]),notifications[i],i
					)
				);
		}
	}
	~WhatsApp(){
		for(auto& t: transceivers){
			t.join();
		}
	}
};
#endif
