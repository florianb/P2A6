#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class TabelleView {
private:
  
public:
  TabelleView();
  
  template<class T> void input(T &input);
  template<class T> void input(T &input, int size);
  
  string getDouble(double value, int digits);
  
  void printParams(int op, double start, double end, int step, int digits, string file);
  void printHelp();
};

TabelleView::TabelleView() {
  
};

template<class T> void TabelleView::input(T &input) {
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

template<class T> void TabelleView::input(T &input, int size) {
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

string TabelleView::getDouble(double value, int digits) {
  stringstream sstream;
  sstream << std::fixed << std::setprecision(digits) << value;
  return sstream.str();
}

void TabelleView::printParams(int op, double start, double end, int step, int digits, string file){
  string Operations[] = {"Unknown", "cos", "sin", "tan", "acos", "asin", "atan", "exp", "log", "log10", "pow", "sqrt"};
  
  cout << endl << "Operation:\t" << Operations[op] << endl;
  cout << "StartValue:\t" << start << endl;
  cout << "EndValue:\t" << end << endl;
  cout << "StepDigits:\t" << step << endl;
  cout << "DisplayDigits:\t" << digits << endl;
  cout << "Filename:\t" << file << endl << endl;
}

void TabelleView::printHelp() {
  cout << "Tabelle" << endl;
  cout << "---------------------------------------" << endl;
  cout << "tabelle <operation> <start> <end> <stepdigits> <displaydigits> <output-file>" << endl << endl;
  cout << "<operation>\tcos, sin, tan, acos, asin, atan, exp, log, log10, pow, sqrt" << endl;
  cout << "<start>\t\tStartwert für Wertetabelle" << endl;
  cout << "<end>\t\tEndwert für Wertetabelle" << endl;
  cout << "<stepdigits>\tAnzahl Nachkommastellen der durchzuführenden Schritte" << endl;
  cout << "<digits>\tAnzahl Nachkommastellen der darzustellenden Werte" << endl;
  cout << "<output-file>\tAusgabedatei" << endl;
}
