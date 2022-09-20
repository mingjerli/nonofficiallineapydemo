// g++ -fPIC -shared -o libTest.so lib.cpp

#include <iostream>
#include <cmath>
#include <algorithm>    // Needed for the "max" function

int Function(int num) 
{
    std::cout << "Num = " << num << std::endl;
    return num;
}

double gaussian_box_muller() {
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;

    // Continue generating two uniform random variables
    // until the square of their "euclidean distance" 
    // is less than unity
    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        euclid_sq = x*x + y*y;
    } while (euclid_sq >= 1.0);

    return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

double monte_carlo_call_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T) {
    double S_adjust = S * exp(T*(r-0.5*v*v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    for (int i=0; i<num_sims; i++) {
        double gauss_bm = gaussian_box_muller();
        S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
        payoff_sum += std::max(S_cur - K, 0.0);
    }
    double result = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
    std::cout << "payoff_sum = " << payoff_sum << std::endl;
    std::cout << "r = " << r << std::endl;
    std::cout << "T = " << T << std::endl;
    std::cout << "result" << result << std::endl;
    
    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

double monte_carlo_put_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T) {
    double S_adjust = S * exp(T*(r-0.5*v*v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    for (int i=0; i<num_sims; i++) {
        double gauss_bm = gaussian_box_muller();
        S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
        payoff_sum += std::max(K - S_cur, 0.0);
    }

    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

extern "C" {
    int My_Function(int a)
    {
        return Function(a);
    }
}

extern "C" {
    double My_gaussian_box_muller()
    {
        return gaussian_box_muller();
    }
}

extern "C" {
    // double My_mc_call(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
    double My_mc_call(int num_sims, double S, double K, double r, double v, double T)
    {
        return monte_carlo_call_price(num_sims, S, K, r, v, T);
    }
}

extern "C" {
    // double My_mc_call(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
    double My_mc_put(int num_sims, double S, double K, double r, double v, double T)
    {
        return monte_carlo_put_price(num_sims, S, K, r, v, T);
    }
}