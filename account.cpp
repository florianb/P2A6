#include <iomanip>

using namespace std;

namespace Simulator {
  struct Transfer {
    int origin;
    int target;
    double value;
    bool refused;
  };
  
  class Account {
  private:
    int accountnbr;
    double value;
    double limit;
    double instructed;
  protected:
    Transfer booked(Account &receiver);
  public:
    Account(int accnbr, double val = 0.0, double lim = 0.0);
    Account& send(double transferValue);
    Transfer receive(Account &origin);
    int getAccountNumber() const;
    double getValue() const;
    
    friend ostream& operator<<(ostream &out, Account &account);
  };
  
  Account::Account(int accnbr, double val, double lim) {
    accountnbr = accnbr;
    value = val;
    limit = lim;
    instructed = 0.0;
  }
  
  Account& Account::send(double transferValue) {
    instructed = transferValue;
    return *this;
  }
  
  Transfer Account::receive(Account &origin) {
    Transfer currentTransfer = origin.booked(*this);
    if (!currentTransfer.refused)
      value += currentTransfer.value;
    return currentTransfer;
  }
  
  Transfer Account::booked(Account &receiver) {
    Transfer currentTransfer = {accountnbr, receiver.getAccountNumber(), instructed, false};
    if (value - instructed < limit)
      currentTransfer.refused = true;
    return currentTransfer;
  }
  
  int Account::getAccountNumber() const {
    return accountnbr;
  }
  double Account::getValue() const {
    return value;
  }
  
  ostream& operator<<(ostream &out, Account &account) {
    out << setw(10) << right << account.accountnbr
        << setw(12) << right << fixed << setprecision(2) << account.value
        << setw(9) << right << account.limit;
    return out;
  }
}
