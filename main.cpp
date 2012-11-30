#include "simulator.cpp"

int main(int argumentCounter, char* argumentValues[]) {
  Simulator::Simulator newSim = Simulator::Simulator(1000);
  
  newSim.run();
}