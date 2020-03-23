/**
* author: Andrew J. Kronser
* filename: kronser.cpp
* date: 10.08.2017
* description: A solution to the problem "Cities of Finland"
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
  * Note the intended solution (with precomputed std dev)
  * should have a runtime of O(n^3) (the time to precompute
  * the std dev) since c <= n
  *
  * The actual solution takes O(cn^2) time once the initial
  * computation is done
  *
  * This solution doesn't precompute and should take O(cn^3)
  */

double std_dev(vector<int>& pop, int i, int j){
    double std_dev = 0;
    double avg = 0;
    for(int k = i; k <= j; k++)
        avg += pop[k];
    avg /= (j - i + 1);
    for(int k = i; k <= j; k++)
        std_dev += pow(pop[k] - avg, 2);

    return sqrt(std_dev)/(j - i + 1);
}

int main(){
    const double INF = 4000000;
    int c, n;
    cin >> c >> n;

    vector<int> pop;

    // Read in all cities and their populations
    // You can discard the names, they're useless
    for(int i = 0; i < n; i++){
        string name;
        int p;

        cin >> name >> p;
        pop.push_back(p);
    }

    // Sort the populations
    sort(pop.begin(), pop.end());
    
    // Calculate the best breakpoints and take note of each
    // in the src array
    vector<vector<double> > d(n, vector<double>(c + 1, INF));
    vector<vector<int> > src(n, vector<int>(c + 1, -1));
    d[0][0] = 0;
    for(int k = 1; k <= c; k++){
        for(int j = 0; j < n; j++){
            for(int i = 0; i < j; i++){
                d[j][k] = min(d[j][k], d[i][k-1] + std_dev(pop, i+1, j));
                if(d[j][k] == d[i][k-1] + std_dev(pop, i+1, j))
                    src[j][k] = i;
            }
        }
    }

    // Trace the table backwards
    int cur = n - 1;
    vector<int> breakpoints;
    for(int k = c;  k > 1; k--){
        breakpoints.push_back(src[cur][k]);
        cur = src[cur][k];
    }
    sort(breakpoints.begin(), breakpoints.end());

    // Print the final results as ranges
    cout << "0-" << pop[breakpoints[0]] << endl;
    int bp;
    for(bp = 1; bp < breakpoints.size(); bp++){
        cout << pop[breakpoints[bp - 1]] + 1 << '-' << pop[breakpoints[bp]] << endl;
    }
    bp--;
    cout << pop[breakpoints[bp]] + 1 << '-' << pop[n - 1] << endl; 

    return 0;
}
