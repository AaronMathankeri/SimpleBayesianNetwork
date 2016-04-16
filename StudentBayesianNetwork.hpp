//#ifndef "StudentBayesianNetwork.hpp"
//#define "StudentBayesianNetwork.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <tuple>
#include <string>
#include <unordered_map>


using namespace std;

typedef double prob;

class StudentBayesianNetwork{

public:
      StudentBayesianNetwork();

      void setSmartProb(prob p);
      void printIntelPrior();
      void setDiffProb(prob p);
      void printDiffPrior();

      void printSATs();
      void printGrades();
      void printLetters();

      void compute_cpdSAT();
      void compute_cpdGrades();
      void compute_cpdLetter();
      void calc_ProbState();
private:
      vector<prob> intelligence;
      vector<prob> difficulty;
      vector<string> satScores {"low", "high"};
      vector<string> grades{"A", "B", "C"};
      vector<string> letter{"weak", "strong"};

      map<pair  <prob, string>, prob> cpd_SAT;
      map<pair  <string, string>, prob> cpd_Let;
      map<tuple <prob, prob, string>, prob> cpd_Grades;

};

//#endif
