#include "Service.h"
#include <mutex>
using namespace std;

mutex mtx;
vector<int> control;

Service::Service() {}

Service::Service(std::shared_ptr<ip::tcp::socket> _sock) : m_sock(_sock) {}

void Service::InitHandling() {
	string str ="";
	int NumOfTask; 
	cout << "OK" <<endl;
	mtx.lock();
	for (int i =0; i< control.size(); ++i){
		if (control[i] == 0){
			string row(mpz_get_str(NULL,10,tasks[0][i].second.get_mpz_t()));
			string ch(mpz_get_str(NULL,10,tasks[0][i].first.get_mpz_t()));
			str = ch + row+ "\n";
			cout <<str <<endl;
			control[i] = 2; //в процессе выполнения
			NumOfTask = i;
			break;
		}
	}
	mtx.unlock();
	if (str == ""){
		for (int i =0; i< control.size(); ++i){
			if (control[i]!= 1)
				str = "Все задачи распределены или решены,спасибо\n";
		}
	}
	if (str == ""){
		stopHandling();
	}
	async_write(*m_sock, buffer(str), [=](const boost::system::error_code& ec, size_t bytesTransf) {
		this->OnSend(ec, bytesTransf,NumOfTask);
	});			
}

void Service::OnSend(const boost::system::error_code& ec, size_t bytesTransf,int NumOfTask) {
	cout << bytesTransf <<endl;
	if (ec) {
		std::cout << "OnSend Error" <<endl;
		if (NumOfTask != -1)
			control[NumOfTask] = 0;
		stopHandling();
		return;
	}
	std::cout << "sent" << std::endl;
	StartRecieving(NumOfTask);
}

void Service::StartRecieving(int NumOfTask) {
	auto buf = make_shared<boost::asio::streambuf>();
	async_read_until(*m_sock, *buf, '\n', [=](const boost::system::error_code& ec,
		size_t bytesTransf) {
		this->OnRecieved(ec, bytesTransf, buf, NumOfTask);
	});
}

void Service::OnRecieved(const boost::system::error_code& ec, size_t bytesTransf,
	std::shared_ptr<boost::asio::streambuf> buf, int NumOfTask) {
	if (ec) {
		cout << "onRecievedError" <<endl;
		if (NumOfTask != -1)
			control[NumOfTask] = 0;
		stopHandling();
		return;
	}
	istream stream(buf.get());
	string answer;
	stream >> answer;
	cout << "Data recieve  " << answer << std::endl;
	control[NumOfTask] =1;
	InitHandling();
}

void Service::stopHandling() {
	m_sock->close();
	delete this;
}