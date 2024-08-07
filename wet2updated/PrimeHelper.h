#ifndef PRIMEHELPER_H_
#define PRIMEHELPER_H_

class PrimeHelper {
public:
    static int next_prime(int n);
private:
    static bool is_prime(int n);
};

#endif // PRIMEHELPER_H_