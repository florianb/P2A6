#include <iostream>
#include <iomanip>
#include <vector>

#include "account.cpp"

using namespace std;

namespace Simulator {

  class Simulator {
  private:
    vector<Account> accounts;
    Transfer biggestTransfer;
    Transfer smallestTransfer;
    double transferAmount;
    int transfers;
    int day;
    int n;
    
    double random(double lo, double hi);
  public:
    Simulator(int initialN = 10);
    void initDay();
    void calculateDay();
    void printDaySummary();
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
      accounts.push_back(Account(i, ((int) random(1, 10000000)) * 0.01, (int)random(100,5000) * -1));
      cout << " + Konto " << accounts.back() << endl;
    }
  }
  
  void Simulator::initDay() {
    biggestTransfer.value = INT_MIN;
    biggestTransfer.refused = false;
    smallestTransfer.value = INT_MAX;
    smallestTransfer.refused = false;
    transferAmount = 0.0;
    day++;
    transfers = 0;
    srand(time(NULL));
  }
  
  void Simulator::calculateDay() {
    Transfer lastTransfer;
    Account *origin = 0;
    Account *target = 0;
    int m = random(7 * n, 12 * n);
    
    for (int i = 0; i < m; i++) {
      do {
        origin = &*(accounts.begin() + ((int) random(0, accounts.size() - 1)));
        do {
          target = &*(accounts.begin() + ((int) random(0, accounts.size() - 1)));
        } while (origin == target);
        lastTransfer = target->receive(origin->send(((int) random(1, 10000000) * 0.01)));
      } while (lastTransfer.refused);
      
      cout << " # " << lastTransfer.origin << " --("
          << setprecision(2) << fixed << lastTransfer.value
          << " Euro)--> " << lastTransfer.target << endl;
      
      transferAmount += lastTransfer.value;
      transfers++;
      
      if (lastTransfer.value > biggestTransfer.value) {
        biggestTransfer.origin = lastTransfer.origin;
        biggestTransfer.target = lastTransfer.target;
        biggestTransfer.value = lastTransfer.value;
      }
      if (lastTransfer.value < smallestTransfer.value) {
        smallestTransfer.origin = lastTransfer.origin;
        smallestTransfer.target = lastTransfer.target;
        smallestTransfer.value = lastTransfer.value;
      }
    }
  }
  
  void Simulator::printDaySummary() {
    Account *highestAccount = NULL;
    Account *lowestAccount = NULL;
    double accountSummary = 0.0;
    
    highestAccount = &*accounts.begin();
    lowestAccount = &*accounts.begin();
    
    for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
      
    }
  }
  
  void Simulator::run() {
    for (int i = 0; i < 1; i++) {
      initDay();
      calculateDay();
    }
    
    cout.flush();
  }
}