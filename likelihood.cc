#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

double poisson(double mu, int k) {
    double P = pow(mu, k) * exp(-mu)/(tgamma(k + 1));
    return P;
}

double prob(vector<int> daten, double mu){
    double L = 1;
    for(int i = 0; i < 234; ++i){
      L = L * poisson(mu, daten[i]);
    }
    return L;
}

int main() {
    using namespace std;
    ifstream fin("datensumme.txt");
    ifstream kin("uncertainty.txt");
    ofstream fout("likelihood.txt");
    ofstream gout("nll.txt");
    ofstream hout("deltanll.txt");
    ofstream kout("uncertainty.txt");
    ofstream eout("likelihoodratio.txt");

    vector<int> daten;

    int n_i;
    for(int i = 0 ; i < 234 ; ++i){
        fin >> n_i;
        daten.push_back(n_i);
    }

    double Lmax = 1;
    for(int i = 0; i < 234; i++)
    {
        Lmax = Lmax * poisson(daten[i], daten[i]);
    }

    for(double j = 0; j <= 6; j += 0.01){
        fout << j << " " << prob(daten, j) << endl;
        gout << j << " " << -2 * log(prob(daten, j)) << endl;
        hout << j << " " << -2 * log(prob(daten, j)) + 2 * log(prob(daten, 3.11538)) << endl;
        kout << j << " " << -2 * log(prob(daten, j)/prob(daten, 3.11538)) << endl;
        eout << j << " " << -2 * log(prob(daten, j)/Lmax) << endl;
    }

    cout << "Likelihood for the mean of the sample: " <<prob(daten, 3.11538) << endl;

    for(double k = 0; k <= 3.1; k += 0.01)
    {
        double ratio = -2 * log(prob(daten, k)/prob(daten, 3.11538));
        if (ratio < 1)
        {
          cout << "x1: " << k << endl;
          break;        
        }
    }

    for(double k = 3.2; k <= 6; k += 0.01)
    {
        double ratio = -2 * log(prob(daten, k)/prob(daten, 3.11538));
        if (ratio >= 1)
        {
          cout << "x2: " << k-0.01 << endl;
          break;        
        }
    }

    
    cout << "Interval uncertainty: " << (3.23-3.01)/2 << endl;
    cout << "Statistical uncertainty: "<< sqrt(3.11538/234) << endl;
    cout << "Likelihood ratio: " << prob(daten, 3.11538)/Lmax << endl;
    cout << "Log Likelihood ratio: " << -2 * log(prob(daten, 3.11538)/Lmax) << endl;
    cout << "z: " << (-2 * log(prob(daten, 3.11538)/Lmax) - 233)/sqrt(2*233) << endl;

    

    fin.close();
    fout.close();
    gout.close();
    hout.close();
    kout.close();
    eout.close();
}