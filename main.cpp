#include <cstdlib>
#include <iomanip>

#include "simulator.cpp"

using namespace std;

int main(int argumentCounter, char* argumentValues[]) {
  int accountNumber = 50;
  
  if (argumentCounter == 2)
    accountNumber = atoi(argumentValues[1]);
  
  if (accountNumber < 1) {
    accountNumber = 50;
    cout << "simulator <AccountNumber>" << endl
      << "--------------------------------------------------" << endl
      << setw(20) << left << "AccountNumber"
      << "Anzahl der Konten, die für die Simulation" << endl
      << setw(20) << left << ""
      << "eingerichtet werden sollen. (1-10.000)"
      << endl << endl
      << "Der angegebene Parameter '" << argumentValues[1] << "' wurde nicht verarbeitet," << endl
      << "stattdessen findet nun der Standardwert " << accountNumber << " verwendung." << endl << endl;
  }
  
  Simulator::Simulator newSim = Simulator::Simulator(accountNumber);
  
  newSim.run();
}