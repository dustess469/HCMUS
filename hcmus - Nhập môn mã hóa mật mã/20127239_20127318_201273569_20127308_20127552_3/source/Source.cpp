#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <bitset>
#include <math.h>
#include <cmath>
using namespace std;

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    int64_t res = 0;

    while (a != 0) {
        if (a & 1) {

            res = (res + b) % m;
        }
        a >>= 1;
        b = (b << 1) % m;
    }
    return res;
}

uint64_t powMod(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t x = 1;

    a %= n;

    while (b > 0) {
        if (b % 2 == 1) {
            x = mulmod(x, a, n);
        }
        a = mulmod(a, a, n);
        b >>= 1;
    }
    return x % n;
}

std::vector<int> first_primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                    31, 37, 41, 43, 47, 53, 59, 61, 67,
                                    71, 73, 79, 83, 89, 97, 101, 103,
                                    107, 109, 113, 127, 131, 137, 139,
                                    149, 151, 157, 163, 167, 173, 179,
                                    181, 191, 193, 197, 199, 211, 223,
                                    227, 229, 233, 239, 241, 251, 257,
                                    263, 269, 271, 277, 281, 283, 293,
                                    307, 311, 313, 317, 331, 337, 347, 349 };

uint64_t getRandom64() {
    constexpr int bits = 63;
    std::bitset<bits> a;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<short> distr(0, 1);

    for (int i = 0; i < bits; i++) {
        a[i] = distr(gen);
    }

    a[0] = 1;
    a[bits - 1] = 1;

    return a.to_ullong();
}

uint64_t getLowLevelPrime() {
    while (true) {
        uint64_t candidate = getRandom64();
        bool is_prime = true;
        for (int i = 0; i < first_primes.size(); i++) {
            if (candidate == first_primes[i])
                return candidate;

            if (candidate % first_primes[i] == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
            return candidate;
    }
}

bool trialComposite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2) {
    if (powMod(a, evenC, to_test) == 1)
        return false;

    for (int i = 0; i < max_div_2; i++) {
        uint64_t temp = static_cast<uint64_t>(1) << i;
        if (powMod(a, temp * evenC, to_test) == to_test - 1)
            return false;
    }

    return true;
}

bool MillerRabinTest(uint64_t to_test) {
    constexpr int accuracy = 20;

    int max_div_2 = 0;
    uint64_t evenC = to_test - 1;
    while (evenC % 2 == 0) {
        evenC >>= 1;
        max_div_2++;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(2, to_test);

    for (int i = 0; i < accuracy; i++) {
        uint64_t a = distr(gen);

        if (trialComposite(a, evenC, to_test, max_div_2)) {
            return false;
        }
    }

    return true;
}

uint64_t getBigPrime() {
    while (true) {
        uint64_t candidate = getLowLevelPrime();
        if (MillerRabinTest(candidate))
            return candidate;
    }
}

uint64_t gcd(int a, int b) {
    int t;
    while (1) {
        t = a % b;
        if (t == 0)
            return b;
        a = b;
        b = t;
    }
}

int check_real_integer_number(float n) {
    //flag = 1 => số nguyên
    //flag = 0 => số thực

    int flag = 1;
    if (ceil(n) != floor(n)) flag = 0;
    return flag;
}

uint64_t publicKey(uint64_t d, uint64_t phi){
    uint64_t e;
    int x = 1;
    do
    {
        e = (x * phi + 1) / d;
        x++;
    } while (!check_real_integer_number(e));

    return e;
}



uint64_t add_mod(uint64_t a, uint64_t b, uint64_t m) {
    return (a + b) % m;
}

uint64_t mul_mod(uint64_t x, uint64_t y, uint64_t n) {
    uint64_t p = 0;
    x %= n;

    while (y > 0) {
        if (y & 1)
            p = add_mod(p, x, n);

        x = (x << 1) % n;

        y = y >> 1;
    }
    return p;
        
}

uint64_t pow_mod(uint64_t x, uint64_t p, uint64_t n) {
    uint64_t y = 1;

    x %= n;

    if (p == 0)
        return y;

    while (p > 0) {
        if (p & 1)
            y = mul_mod(y, x, n);

        p = p >> 1;;

        x = mul_mod(x, x, n);
    }
    return y;
}



int main() {
    cout << "Nhap khoa bi mat d: ";
    uint64_t d;
    cin >> d;
    
    //2 random prime numbers
    uint64_t p;
    uint64_t q;
    uint64_t phi;

    do
    {
        p = getBigPrime();
        q = getBigPrime();
        phi = (p - 1) * (q - 1);
            
    } while (gcd(d, phi) == 1);

    uint64_t n = p * q;
    //public key
    uint64_t e = publicKey(d, phi);

    int message = 65;
    //cout << "Nhap message: ";
    //cin >> message;

    int c = pow_mod(message, e, n);
    int m = pow_mod(c, d, n);

    cout << "Original Message = " << message;
    cout << "\n" << "p = " << p;
    cout << "\n" << "q = " << q;
    cout << "\n" << "n = pq = " << n;
    cout << "\n" << "phi = " << phi;
    cout << "\n" << "e = " << e;
    cout << "\n" << "d = " << d;
    cout << "\n" << "Encrypted message = " << c;
    cout << "\n" << "Decrypted message = " << m;
    return 0;
}