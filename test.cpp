// Evgeny Bobkunov
// e.bobkunov@innopolis.university
// CS-03

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#ifdef WIN32
#define GNUPLOT_NAME "D:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif

int main() {

#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif

    // input variables
    double v_0, k_0, alpha_1, beta_1, alpha_2, beta_2, T;
    int N;

    // read input
    cin >> v_0 >> k_0 >> alpha_1 >> beta_1 >> alpha_2 >> beta_2 >> T >> N;

    // initialize time and step size
    vector<double> t(N+1);
    double dt = T/N;
    for (int i=0; i<=N; i++) {
        t[i] = i*dt;
    }

    // initialize arrays for v and k
    vector<double> v(N+1), k(N+1);
    v[0] = v_0;
    k[0] = k_0;

    double deltaOne = alpha_1/beta_1;
    double deltaTwo = alpha_2/beta_2;
    double sqrtAlphas = sqrt(alpha_1*alpha_2);
    for (int i=1; i<=N; i++) {
        double time = t[i];
        double v_i = (v_0 - deltaTwo) * cos(sqrtAlphas * time) - (sqrt(alpha_2) * beta_1 * (k_0 - deltaOne))/(beta_2 * sqrt(alpha_1)) * sin(sqrtAlphas * time) + deltaTwo;
        double k_i = (v_0 - deltaTwo) * ((sqrt(alpha_1) * beta_2)/(beta_1 * sqrt(alpha_2))) * sin(sqrtAlphas * time) + (k_0 - deltaOne) * cos(sqrtAlphas * time) + deltaOne;
        v[i] = v_i;
        k[i] = k_i;
    }

    // output results
    cout << fixed << setprecision(2);
    cout << "t:\n";
    for (int i=0; i<=N; i++) {
        cout << t[i] << " ";
    }
    cout << "\n";

    cout << "v:\n";
    for (int i=0; i<=N; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";

    cout << "k:\n";
    for (int i=0; i<=N; i++) {
        cout << k[i] << " ";
    }
    cout << "\n";


    fprintf(pipe, "plot [0 : 1] [0 : 1] '-' using 1:2 with lines\n");

    // plot for victims: v(t)
    for (int i = 0; i < N; i++) {
        fprintf(pipe, "%f\t%f\n", t[i], v[i]);
    }
    // plot for killers k(t)
    for (int i = 0; i < N; i++) {
        fprintf(pipe, "%f\t%f\n", t[i], k[i]);
    }
    // plot for v(k)
//    for (int i = 0; i < N; i++) {
//        fprintf(pipe, "%f\t%f\n", v[i], k[i]);
//    }
    fprintf(pipe, "e\n");
    fflush(pipe);

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    return 0;
}
