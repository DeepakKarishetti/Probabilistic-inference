// Deepak Rajasekhar Karishetti
// 10846936
// CSCI - 404

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib> 
#include <cstring>
#include <string>
#include <cctype> 
#include <cmath>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    // Check the input
    if (argc > 2){
        cout << "The program takes one argument, Q, which is the sequence of ";
        cout << "observations (i.e. CLLCCCLCLL)\n";
        cout << "Example, if Q = CLLCCCLCLL\n";
        cout << argv[0] << " CLLCCCLCLL\n";
        exit(1);
    }

    string Q = "";
    int Q_len = 0;
    int n_c = 0;
    int n_l = 0;

    // If no input is provided Q is left blank, otherwise parse Q for content.
    if (argc == 2){
        // Store the observation sequence
        Q = argv[1];
        // Get the observation length
        Q_len = strlen(argv[1]);
        n_c = 0; // number of cherries
        n_l = 0; // number of limes
        for (int i = 0; i < Q_len; ++i){
            if (tolower(Q[i]) == 'c'){
                n_c++;
            }
            else if (tolower(Q[i]) == 'l'){
                n_l++;
            }
        }
        // Check that the input contains only C's and L's
        if ((n_c + n_l) != Q_len){
            cout << "Your observations include values that are not 'C' or 'L', which is not valid." << endl;
            exit(1);
        }
    }

    // Store known probabilities about the world
    vector<double> P_h = {0.10, 0.20, 0.40, 0.20, 0.10}; // probability of bags 1 - 5
    vector<double> P_c_h = {1.0, 0.75, 0.50, 0.25, 0.0}; // probability of cherry given bags 1 - 5
    vector<double> P_l_h = {0.0, 0.25, 0.50, 0.75, 1.0}; // probability of lime given bags 1 - 5

    // Calculate probability of the observation given the bag
    vector<double> P_Q_h(5); // probability of Q given bag i
    for (int i = 0; i < P_Q_h.size(); ++i){
        P_Q_h[i] = pow(P_c_h[i], n_c)*pow(P_l_h[i], n_l);
    }

    // Calculate the probability of Q
    double P_Q = 0;
    for (int i = 0; i < P_Q_h.size(); ++i){
        P_Q += (P_Q_h[i]*P_h[i]);
    }

    // Calculate each bag probability given the observation
    vector<double> P_h_Q(P_Q_h.size());
    for (int i = 0; i < P_h_Q.size(); ++i){
        P_h_Q[i] = (P_Q_h[i]*P_h[i])/P_Q;
    }

    // Calculate the probability of C and L given the observation
    // Probability of C
    int n_QC = n_c + 1;
    vector<double> P_QC_h(5); // probability of Q given bag i
    for (int i = 0; i < P_QC_h.size(); ++i){
        P_QC_h[i] = pow(P_c_h[i], n_QC)*pow(P_l_h[i], n_l);
    }
    double P_QC = 0;
    for (int i = 0; i < P_QC_h.size(); ++i){
        P_QC += (P_QC_h[i]*P_h[i]);
    }
    double P_C_Q = (P_QC/P_Q);

    // Probability of L
    int n_QL = n_l + 1;
    vector<double> P_QL_h(5); // probability of Q given bag i
    for (int i = 0; i < P_QL_h.size(); ++i){
        P_QL_h[i] = pow(P_c_h[i], n_c)*pow(P_l_h[i], n_QL);
    }
    double P_QL = 0;
    for (int i = 0; i < P_QL_h.size(); ++i){
        P_QL += (P_QL_h[i]*P_h[i]);
    }
    double P_L_Q = (P_QL/P_Q);

    // Print Output to "result.txt"
    // Open output file with name 'result.txt'
    ofstream output_file;
    output_file.open("result.txt",ofstream::out);

    // Check that the file was opened correctly for writing
    if (!output_file){
        cerr << "The file 'result.txt' could not be opened for writing.\n";
        exit(1);
    }

    output_file << "Observation sequence Q: " << Q << endl;
    output_file << "Length of Q: " << Q_len << endl;
    output_file << "\n";
    output_file << fixed;
    output_file << setprecision(5);
    for (int i = 0; i < P_h_Q.size(); ++i){
        output_file << "P(h" << (i+1) << "|Q) = " << P_h_Q[i] << "\n";
    }
    output_file << endl;
    output_file << "Probability that the next candy we pick will be C, given Q: " << P_C_Q << endl;
    output_file << "Probability that the next candy we pick will be L, given Q: " << P_L_Q << endl;

    return 0;
}
