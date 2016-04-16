#include <iostream>
#include "StudentBayesianNetwork.hpp"

using namespace std;

/*
  5 VARIABLES:
  I-intelligence
  D-difficulty
  S-SAT
  G-grades
  L-letter
*/

int main(int argc, char *argv[])
{
      cout << "Implementing a Bayesian Network" << endl;
      StudentBayesianNetwork ntwrk;
      ntwrk.setSmartProb(0.3);
      ntwrk.printIntelPrior();

      ntwrk.setDiffProb(0.4);
      ntwrk.printDiffPrior();

      ntwrk.printSATs();
      ntwrk.printGrades();
      ntwrk.printLetters();

      ntwrk.compute_cpdSAT();
      ntwrk.compute_cpdGrades();
      ntwrk.compute_cpdLetter();

      cout << "\nProb that he's smart, "
           << "easy class, B grade, great SATs, "
	   << "bad letter of rec" << endl;
      ntwrk.calc_ProbState();
      return 0;
}
