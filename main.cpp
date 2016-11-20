#include "Factor.h"
#include "server.h"
#include <gmpxx.h>
#include <gmp.h>
#include <stdio.h>

int main() {
	vector<int> rezult;
	mpz_class N;
	mpz_init(N.get_mpz_t());
	cout <<"Write N = ";
	cin >> N;
	try {
		Factor(N);
		for (int i =0; i<tasks.size();++i){
			for(int j=0; j<tasks[i].size();++j){
		    cout << tasks[i][j].first <<" " <<tasks[i][j].second <<endl;
	        }
	    }
		Server S;
		S.Start();
		 std::this_thread::sleep_for(std::chrono::seconds(30));
		S.Stop();
		std::cout << "Hello, World!" << std::endl;
	}
	catch(...){
		cout <<"error!";
	}
	return 0;
}


