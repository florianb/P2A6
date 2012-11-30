#include <iostream>
#include <vector>

#include "account.cpp"

using namespace std;

namespace Simulator {

  class Simulator {
  private:
    vector<Account> accounts;
    Transfer biggestTransfer;
    Transfer smallestTransfer;
    int transfers;
    int day;
    int n;
    
    double random(double lo, double hi);
  public:
    Simulator(int initialN = 10);
    void initDay();
    void calculateDay();
    void run();
  };
  
  double Simulator::random(double lo, double hi) {
    return lo + (double) rand() / ((double) RAND_MAX / (hi - lo));
  }
  
  Simulator::Simulator(int initialN) {
    day = 0;
    n = initialN;
    srand(time(0));
    
    for (int i = 111111; i < n + 111111; i++) {
      accounts.push_back(Account(i, ((int)random(1, 10000000)) * 0.01, (int)random(100,5000) * -1));
      cout << " + Konto " << accounts.back() << endl;
    }
  }
  
  void Simulator::initDay() {
    biggestTransfer.value = INT_MIN;
    smallestTransfer.value = INT_MAX;
    day++;
    transfers = 0;
    srand(time(0));
  }
  
  void Simulator::calculateDay() {
    Transfer lastTransfer;
    Account *origin = NULL;
    Account *target = NULL;
    int m = random(7 * n, 12 * n);
    
    for (int i = 0; i < m; i++) {
      do {
        origin = **(accounts.begin() + ((int) random(0, accounts.size() - 1)));
        do {
          
        } while (origin == target);
      } while (lastTransfer.refused);
    }
  }
  
  void Simulator::run() {
    
  }
}