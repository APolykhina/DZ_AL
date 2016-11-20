#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <cstdlib>
#include <vector>
#include "Service.h"

using namespace boost::asio;
using namespace std;

class Acceptor {
public:
	Acceptor(io_service &ios);

	short PortNum();

	void onAccept(const boost::system::error_code&ec,
		std::shared_ptr<ip::tcp::socket> sock) ;

	void InitAccept();
private:
	io_service& m_ios;
	ip::tcp::acceptor m_acceptor;
	ip::tcp::endpoint m_port;
};
