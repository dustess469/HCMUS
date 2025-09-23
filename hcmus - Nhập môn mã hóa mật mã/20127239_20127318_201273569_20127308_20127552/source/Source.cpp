#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;

#define f(a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef double db;

// Lưu trữ và tính toán số nguyên lớn

class BigInt {
    string digits;
public:
    // Hàm khởi tạo
    BigInt(unsigned long long n = 0);
    BigInt(string&);
    BigInt(BigInt&);

    // Một số hàm hỗ trợ
    friend void divide_by_2(BigInt& a);
    friend bool Null(const BigInt&);
    friend int Length(const BigInt&);
    int operator[](const int)const;

    // Phép toán modulo
    friend BigInt operator%(const BigInt&, const BigInt&);
    friend BigInt& operator%=(BigInt&, const BigInt&);

    // Phép toán nhân
    friend BigInt& operator*=(BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);

    // Phép toán mũ
    friend BigInt& operator^=(BigInt&, const BigInt&);
    friend BigInt operator^(BigInt&, const BigInt&);

    friend ostream& operator<<(ostream&, const BigInt&);
    friend istream& operator>>(istream&, BigInt&);

    // Phép toán cộng trừ
    friend BigInt& operator+=(BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt& operator-=(BigInt&, const BigInt&);

    // So sánh
    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator==(const BigInt&, const BigInt&);

    BigInt& operator=(const BigInt&);
};


// Cài đặt một số hàm hỗ trợ
int BigInt::operator[](const int index)const {
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}

int Length(const BigInt& a) {
    return a.digits.size();
}

bool Null(const BigInt& a) {
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}

void divide_by_2(BigInt& a) {
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
}



// Cài đặt hàm khởi tạo

BigInt::BigInt(string& s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

BigInt::BigInt(unsigned long long nr) {
    do {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}

BigInt::BigInt(BigInt& a) {
    digits = a.digits;
}


istream& operator>>(istream& in, BigInt& a) {
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i];
    }
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        cout << (short)a.digits[i];
    return cout;
}


// Overload lại các phép toán

BigInt& operator*=(BigInt& a, const BigInt& b)
{
    if (Null(a) || Null(b)) {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            v[i + j] += (a.digits[i]) * (b.digits[j]);
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        a.digits.pop_back();
    return a;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}

BigInt& operator%=(BigInt& a, const BigInt& b) {
    if (Null(b)) {
        throw("Arithmetic Error: Division By 0");
    }
    if (a < b) {
        return a;
    }
    if (a == b) {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}

BigInt operator%(const BigInt& a, BigInt& b) {
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}

BigInt& operator+=(BigInt& a, const BigInt& b) {
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++) {
        if (i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

BigInt& operator-=(BigInt& a, const BigInt& b) {
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(),
        n--;
    return a;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

bool operator<(const BigInt& a, const BigInt& b) {
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}

bool operator>(const BigInt& a, const BigInt& b) {
    return b < a;
}

bool operator==(const BigInt& a, const BigInt& b) {
    return a.digits == b.digits;
}

BigInt& BigInt::operator=(const BigInt& a) {
    digits = a.digits;
    return *this;
}

BigInt& operator^=(BigInt& a, const BigInt& b) {
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent)) {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}

BigInt operator^(BigInt& a, BigInt& b) {
    BigInt temp(a);
    temp ^= b;
    return temp;
}



// Hàm tính A^(N - 1) mod N
BigInt binpow(BigInt a, BigInt b, BigInt m) {

    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    int i = 0;
    while (!Null(Exponent)) {
        cout << i << endl;
        if (Exponent[0] & 1)
            a *= Base % m;
        Base *= Base % m;
        divide_by_2(Exponent);
        ++i;
    }
    return a;
}



// Hàm chuyển chuỗi nhị phân sang BigInt
BigInt StringtoBigInt(string binary) {
    BigInt ans(0), two(2);
    f(0, binary.size()) {
        BigInt temp(binary[i] - 48);
        BigInt exp(binary.size() - i - 1);
        ans += (temp * (two ^ exp));
    }
    return ans;
}

// Hàm sinh chuỗi nhị phân với bit đầu và cuối = 1
string generateBinaryString(int N)
{
    srand(time(NULL));
    string S = "";
    S += '1';
    N -= 2;

    for (int i = 0; i < N; i++) {
        int x = ((int)rand() % 2);
        S += to_string(x);
    }

    S += '1';
    return S;
}

// fermat
bool fermat_testing(BigInt N) {
    BigInt temp;
    string s;
    s = generateBinaryString(Length(N) - 1);
    BigInt a;
    a = StringtoBigInt(s);

    temp = N - 1;
    if (binpow(a, temp, N) == 1)
        return true;
    else
        return false;
    return true;
}







int main() {
    int key_len;
    bool flag = false;

    cout << "Nhap do dai khoa: ";
    cin >> key_len;

    do {
        // sinh chuỗi bit
        string s;
        s = generateBinaryString(key_len);
        cout << "Chuoi bit dang test: ";
        f(0, s.length())
            cout << s[i];
        cout << endl;

        // tính toán số BigInt từ chuỗi bit
        BigInt N;
        N = StringtoBigInt(s);

        if (fermat_testing(N) == 1) {
            cout << "Ket qua: " << s << endl;
            flag == true;
        }
    } while (flag == false);
    return 0;
}