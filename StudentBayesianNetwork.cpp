#include "StudentBayesianNetwork.hpp"


StudentBayesianNetwork :: StudentBayesianNetwork(){
      vector<prob> intelligence{0 , 0};
      vector<prob> difficulty{0, 0};
      vector<string> satScores {"low", "high"};
      vector<string> grades{"A", "B", "C"};
      vector<string> letter{"weak", "strong"};
}

void StudentBayesianNetwork :: setSmartProb(prob p)
{
      intelligence.push_back(1.0 - p);
      intelligence.push_back(p);
}

void StudentBayesianNetwork :: printIntelPrior()
{
      cout << "\nPrior on Intelligence" << endl;
      for (auto itr: intelligence)
	    cout << itr << " ";
      cout << endl;
}

void StudentBayesianNetwork :: setDiffProb(prob p)
{
      difficulty.push_back(1.0 - p);
      difficulty.push_back(p);
}

void StudentBayesianNetwork :: printDiffPrior()
{
      cout << "\nPrior on Class Difficulty" << endl;
      for (auto iter : difficulty)
	    cout << iter << " ";
      cout << endl;
}


void StudentBayesianNetwork :: printSATs()
{
      cout << "\nSAT states" << endl;
      for (auto iter : satScores)
	    cout  << iter << " ";
      cout << endl;
}

void StudentBayesianNetwork :: printGrades()
{
      cout << "\nGrades" << endl;
      for (auto iter : grades)
	    cout << iter << " ";
      cout << endl;
}

void StudentBayesianNetwork :: printLetters()
{
      cout << "\nLetter of Rec" << endl;
      for (auto iter : letter)
	    cout << iter << " ";
      cout << endl;
}


void StudentBayesianNetwork :: compute_cpdSAT()
{
      // CPD for satScores: P(S | I)
      //map<pair<prob, string>, prob> cpd_SAT;
      pair<prob, string> keyCPD_1(intelligence[0], satScores[0]);
      pair<prob, string> keyCPD_2(intelligence[0], satScores[1]);
      pair<prob, string> keyCPD_3(intelligence[1], satScores[0]);
      pair<prob, string> keyCPD_4(intelligence[1], satScores[1]);

      cpd_SAT.insert(std::make_pair(keyCPD_1, 0.95));
      cpd_SAT.insert(std::make_pair(keyCPD_2, 0.05));
      cpd_SAT.insert(std::make_pair(keyCPD_3, 0.20));
      cpd_SAT.insert(std::make_pair(keyCPD_4, 0.80));

      cout << "\nCPD for SAT and Intelligence" << endl;
      cout << cpd_SAT[make_pair(0.7, "low")] << endl;
    
}

void StudentBayesianNetwork :: compute_cpdGrades()
{
      unsigned int intel_state = 1;
      unsigned int diff_state = 0;
      unsigned int sat_state = 1;
      unsigned int grade_state = 1;


      // CPD for grades: P(G | I,D)
      //map<tuple <prob, prob, string>, prob> cpd_Grades;
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[0], difficulty[0], grades[0]) , 0.30) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[0], difficulty[0], grades[1]) , 0.40) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[0], difficulty[0], grades[2]) , 0.30) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[0], difficulty[1], grades[0]) , 0.05) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[0], difficulty[1], grades[1]) , 0.25) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[0], difficulty[1], grades[2]) , 0.70) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[1], difficulty[0], grades[0]) , 0.90) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[1], difficulty[0], grades[1]) , 0.08) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[1], difficulty[0], grades[2]) , 0.02) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[1], difficulty[1], grades[0]) , 0.50) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[1], difficulty[1], grades[1]) , 0.30) );
      cpd_Grades.insert(make_pair(tuple<prob, prob, string> (intelligence[1], difficulty[1], grades[2]) , 0.20) );


      cout << "\nCPD for Grades, Intelligence and Difficulty" << endl;
      cout << cpd_Grades[make_tuple(intelligence[intel_state],difficulty[diff_state], grades[grade_state])]  << endl;
      //cout << cpd_Grades[make_tuple(intelligence[0], difficulty[0], grades[0])] << endl;
      //cout << cpd_Grades[make_tuple(intelligence[1], difficulty[1], grades[0])] << endl;

}

void StudentBayesianNetwork :: compute_cpdLetter()
{
      // CPD for letters: P(L | G)
      //map<pair<string, string>, double> cpd_Let;
      cpd_Let.insert(make_pair(pair<string, string> (grades[0], letter[0]) ,0.1) );
      cpd_Let.insert(make_pair(pair<string, string> (grades[0], letter[1]) ,0.9) );
      cpd_Let.insert(make_pair(pair<string, string> (grades[1], letter[0]) ,0.4) );
      cpd_Let.insert(make_pair(pair<string, string> (grades[1], letter[1]) ,0.6) );
      cpd_Let.insert(make_pair(pair<string, string> (grades[2], letter[0]) ,0.99) );
      cpd_Let.insert(make_pair(pair<string, string> (grades[2], letter[1]) ,0.01) );

      cout << "\nCPD for Letters and Grades" << endl;
      cout << cpd_Let[make_pair("A", "weak")] << endl;

}

void StudentBayesianNetwork :: calc_ProbState()
{
      unsigned int intel_state = 1;
      unsigned int diff_state = 0;
      unsigned int sat_state = 1;
      unsigned int grade_state = 1;
      unsigned int let_state = 0;

      prob p = intelligence[intel_state] * difficulty[diff_state] 
	              * cpd_Grades[make_tuple(intelligence[intel_state],difficulty[diff_state], grades[grade_state])] 
	              * cpd_SAT[make_pair(intelligence[intel_state], satScores[sat_state])] 
	              * cpd_Let[make_pair(grades[grade_state], letter[let_state])];

      cout << p << endl;
}

