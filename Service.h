#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <string>
#include <cstdlib>
#include <vector>
#include "Factor.h"

using namespace boost::asio;
using namespace std;
extern vector<int> control;

class Service {
public:
    Service();
    Service(std::shared_ptr<ip::tcp::socket> _sock);

    void InitHandling();
    void OnSend(const boost::system::error_code& , size_t ,int);

    void StartRecieving(int) ;

    void OnRecieved(const boost::system::error_code&, size_t,
        std::shared_ptr<boost::asio::streambuf>,int);


    void stopHandling() ;

private:
    std::shared_ptr <ip::tcp::socket> m_sock;
};