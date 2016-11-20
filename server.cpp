#include "server.h"

Server::Server() {
	for (int i =0; i<tasks[0].size();++i){
		control.push_back(0);
	}
	acc.reset(new Acceptor(m_ios));
};

void Server::Start(){
	auto f = [this]() {
		m_ios.run();
	};
	acc->InitAccept();
	thread t(f);
	m_thread.reset(new thread(move(t)));
}; 

void Server::Stop(){
	m_ios.stop();
	m_thread->join();
}; 