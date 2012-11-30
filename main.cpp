#include "simulator.cpp"

int main(int argumentCounter, char* argumentValues[]) {
  Simulator::Simulator newSim = Simulator::Simulator(50);
  
  newSim.run();
}