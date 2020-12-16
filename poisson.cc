#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

double poisson(double mu, int k) {
  double P = (pow(mu, k) * exp(-mu))/(tgamma(k + 1));
  return P;
}

int main() {
    using namespace std;
    ifstream fin("datensumme.txt");
    ofstream fout("hist.txt");
    ofstream gout("histpoi.txt");
    vector<int>zaeler(11);
    int n_i;
    for(int i = 0; i < 234; ++i){
        fin >> n_i;
        zaeler[n_i] += 1;
    }
for(int j = 0; j < 11; ++j){
        fout << j << " " << zaeler[j] << endl;
        gout << j << " " << zaeler[j] << " " << poisson(3.11538, j) * 234 << endl;
    }
    fin.close();
    fout.close();
    gout.close();
}