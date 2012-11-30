/**

@file main.cpp

Datei zum Start des Programms, enthält die Hauptfunktion und die Hilfeausgabe, falls
eine falsche Parameterzahl eingegeben wurde.

**/

#include <cstdlib>
#include <iomanip>

#include "simulator.cpp"
  
using namespace std;

/**
Hauptfunktion überprüft, ob ein Kommandozeilenparameter übergeben wurde

Wurde ein Kommandozeilenparameter (n) übergeben, versucht die Routine den Wert
als Zahl einzulesen, schlägt dies fehl wird ein Standardert (50)
angenommen.
Startet außerdem die Hauptroutine zur Simulationsausführung.
**/
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