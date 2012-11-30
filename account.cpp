/**
@file account.cpp

Enthält die Datenstrukturen und Klassen, um Transaktionen und Bankkonten abzubilden
**/

#include <sstream>
#include <iomanip>

using namespace std;

namespace Simulator {
  /**
    Enthält alle notwendigen Informationen über eine Transaktion
  **/
  struct Transfer {
    int origin;
    int target;
    double value;
    bool refused;
  };
  
  /**
  Bildet ein Bankkonto nach
  **/
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
    
    static string transferToString(const Transfer &transfer);
    
    friend ostream& operator<<(ostream &out, Account &account);
  };
  
  /**
  Konstruktor erstellt ein Bankkonto mit allen notwendigen Parametern
  
  @param accnbr Kontonummer des Kontos
  @param val Initiales Valuta des Kontos
  @param lim Überziehungslimit des Kontos
  **/
  Account::Account(int accnbr, double val, double lim) {
    accountnbr = accnbr;
    value = val;
    limit = lim;
    if (limit > 0)
      limit *= -1.0;
    instructed = 0.0;
  }
  
  /**
    Bereitet das Konto auf eine Überweisung vor 
    
    @param transferValue Überweisungshöhe
  **/
  Account& Account::send(double transferValue) {
    instructed = transferValue;
    return *this;
  }
  
  /**
    Empfängt die vorbereitete Transaktion eines Quell-Kontos
    
    @param origin Konto das für eine Transaktion vorbereitet wurde
    @return Liefert den Transaktionsbeleg zurück
  **/
  Transfer Account::receive(Account &origin) {
    Transfer currentTransfer = origin.booked(*this);
    if (!currentTransfer.refused)
      value += currentTransfer.value;
    return currentTransfer;
  }
  
  /**
    Buchungsfunktion verbucht die anstehende Transaktion tatsächlich
    
    Verbucht die vorbereitete Transaktion zwischen zwei Konten, falls das sendende
    Konto die Forderung erfüllen kann. Liefert den Transaktionsbeleg zurück.
    
    @return Liefert den Transaktionsbeleg bei fehlgeschlagender Buchung mit dem Status zurückgewiesen zurück
  **/
  Transfer Account::booked(Account &receiver) {
    Transfer currentTransfer = {accountnbr, receiver.getAccountNumber(), instructed, false};
    if (value - instructed < limit)
      currentTransfer.refused = true;
    else
      value -= instructed;
    return currentTransfer;
  }
  
  /**
  Liefert die Kontonummer des Kontos zurück.
  **/
  int Account::getAccountNumber() const {
    return accountnbr;
  }
  
  /**
  Liefert den aktuellen Kontostand des Kontos zurück.
  **/
  double Account::getValue() const {
    return value;
  }
  
  /**
    Hilfsfunktion zur formatierten Ausgabe des Kontos in einem Stream
  **/
  ostream& operator<<(ostream &out, Account &account) {
    out << setw(10) << right << account.accountnbr
        << setw(12) << right << fixed << setprecision(2) << account.value
        << setw(9) << right << account.limit;
    return out;
  }
  
  /**
  Hilfsfunktion zur formatierten Ausgabe eines Transferbelegs
  
  @param transfer Transferbeleg, der in einen String umgewandelt werden soll
  @result gibt den formatierten String zurück
  **/
  string Account::transferToString(const Transfer &transfer) {
    stringstream out;
    out << "#" << transfer.origin
      << " --("
      << setprecision(2) << fixed << transfer.value
      << " EUR)--> "
      << "#" << transfer.target;
    return out.str();
  }
}
