#include "simulator.cpp"

int main(int argumentCounter, char* argumentValues[]) {
  int accountNumber = 50;
  
  if (argumentCounter == 2)
    accountNumber = atoi(argumentValues[1]);
  
  Simulator::Simulator newSim = Simulator::Simulator(accountNumber);
  
  newSim.run();
}