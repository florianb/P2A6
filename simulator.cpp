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
    void printTransactionSummary();
    void run();
    
    template<class T> static void input(T &input);
    template<class T> static void input(T &input, int size);
  };
  
  double Simulator::random(double lo, double hi) {
    return lo + (double) rand() / ((double) RAND_MAX / (hi - lo));
  }
  
  Simulator::Simulator(int initialN) {
    cout << " simulator - Kontensimulation" << endl << endl;
    
    day = 0;
    n = initialN;
    srand(time(0));
    
    for (int i = 111111; i < n + 111111; i++) {
      accounts.push_back(Account(i, ((int) random(1, 10000000)) * 0.01, (int)random(100,5000) * -1));
      //cout << " + Konto " << accounts.back() << endl;
    }
    cout << accounts.size() << " Konten erstellt." << endl << endl;
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
      
      /*cout << " # " << lastTransfer.origin << " --("
          << setprecision(2) << fixed << lastTransfer.value
          << " EUR)--> " << lastTransfer.target << endl;*/
      
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
      if (it->getValue() > highestAccount->getValue())
        highestAccount = &*it;
      if (it->getValue() < lowestAccount->getValue())
        lowestAccount = &*it;
      accountSummary += it->getValue();
    }
    
    cout << " Tag " << day << endl << "----------------------------------------------------------------------" << endl
      << " # Gesamtbestand:\t\t\t"
      << setprecision(2) << fixed
      << setw(30) << right << accountSummary << " EUR" << endl
      << " + Höchster Kontostand (#" << highestAccount->getAccountNumber() << "): \t"
      << setw(30) << right << highestAccount->getValue() << " EUR" << endl
      << " - Niedrigster Kontostand (#" << lowestAccount->getAccountNumber() << "): \t"
      << setw(30) << right << lowestAccount->getValue() << " EUR" << endl << endl;   
  }
  
  void Simulator::printTransactionSummary() {
    cout << " ### Überweisungen:" << endl
      << setw(30) << left << "   - Anzahl:"
      << setw(30) << right << transfers << " Stück" << endl
      << setw(30) << left << "   - Gesamtvolumen:"
      << setw(30) << right << transferAmount << " EUR" << endl
      << setw(30) << left << "   - Durchschnittsvolumen:"
      << setw(30) << right << transferAmount / transfers << " EUR" << endl
      << endl
      << setw(35) << left << "   + Größte Transaktion:"
      << setw(40) << right << Account::transferToString(biggestTransfer) << endl
      << setw(35) << left << "   - Geringste Transaktion:"
      << setw(40) << right << Account::transferToString(smallestTransfer)
      << endl << endl;
  }
  
  void Simulator::run() {
    char userInput = '\0';
    do {
      printDaySummary();
      initDay();
      calculateDay();
      printTransactionSummary();
      printDaySummary();
      
      cout << endl << " Einen weiteren Tag berechnen (Mit 'j' fortfahren und mit 'n' beenden)?" << endl << flush;
      input(userInput);
      cout << endl << endl;
    } while (userInput == 'j' || userInput == 'J');
    cout << endl << " Adieu.. " << endl << flush;
  }
  
  template<class T> void Simulator::input(T &input) {
    bool cin_good = false;
      
    cout.flush();
    cin.clear();
    do {
      cin_good = cin >> input;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      if (!cin_good) {
        cout << "Die Eingabe konnte nicht verarbeitet werden. Bitte erneut versuchen\n";
        cout.flush();
      }
    } while (!cin_good);
  }

  template<class T> void Simulator::input(T &input, int size) {
    bool cin_good = false;
      
    cout.flush();
    cin.clear();
    do {
      cin >> input;
      cin.clear();
      cin.ignore(size, '\n');
      if (!cin_good) {
        cout << "Die Eingabe konnte nicht verarbeitet werden. Bitte erneut versuchen\n";
        cout.flush();
      }
    } while (!cin_good);
  }
}