#include <iostream>



class Fraction {

private:

	uint64_t gd(int64_t a, uint64_t b) {
		a = abs(a);							//если че мб надо помен€ть uin64_t на инт и добавить
		if (a >= b) {					   // вз€тие модул€
			if (a % b == 0) {
				return b;
			}
			else {
				a = a % b;
				return gd(a, b);
			}
		}
		else {
			int64_t tmp;
			tmp = a;
			a = b;
			b = tmp;
			return gd(a, b);
		}
	}
	uint64_t gcd(const int64_t& a,const uint64_t& b) {
		return (a * b) / gd(a, b);
	}

	void Reduct(Fraction& X) {
		int64_t g = gd(X.numerator, X.denominator);
		X.numerator /= g;
		X.denominator /= g;
		}

	template < class T >
	friend bool operator ==(const Fraction& lhs, const T& rhs);


public:
	int64_t numerator;
	uint64_t denominator;
	Fraction() = delete;
	Fraction(const Fraction& rhs) {
		numerator = rhs.numerator;
		denominator = rhs.denominator;
	}

	Fraction& operator=(const Fraction& rhs) {
		numerator = rhs.numerator;
		denominator = rhs.denominator;
		int64_t g = gd(numerator, denominator);
		numerator /= g;
		denominator /= g;
		return *this;
	}

	Fraction(int64_t a, uint64_t b) {
		if (b != 0) {
		numerator = a;
		denominator = b;
		int64_t g = gd(numerator, denominator);
		numerator /= g;
		denominator /= g;
		}
	}

	Fraction operator+(Fraction rhs) {
		Fraction timev = *this;
		if (timev.denominator == rhs.denominator) {
			timev.numerator += rhs.numerator;
		}
		else {
			uint64_t tmp = gcd(timev.denominator, rhs.denominator);
				timev.numerator *= tmp / denominator;
				rhs.numerator *= tmp / rhs.denominator;
				timev.numerator += rhs.numerator;
				timev.denominator = tmp;
			}
		Reduct(timev);
		return timev;
	}

	Fraction operator-(Fraction rhs) {
		Fraction timev = *this;
		if (timev.denominator == rhs.denominator) {
			timev.numerator -= rhs.numerator;
		}
		else {
			uint64_t tmp = gcd(timev.denominator, rhs.denominator);
				timev.numerator *= tmp / denominator;
				rhs.numerator *= tmp / rhs.denominator;
				timev.numerator -= rhs.numerator;
				timev.denominator = tmp;
			}
		Reduct(timev);
		return timev;
	}

	Fraction operator*(Fraction rhs) {
		Fraction timev = *this;
		timev.numerator *= rhs.numerator;
		timev.denominator *= rhs.denominator;
		Reduct(timev);
		return timev;
	}

//	Fraction operator/(Fraction rhs) {
//		if (rhs.numerator != 0) {
//			Fraction timev = *this;
//			if (rhs.numerator < 0) {
//				timev.numerator *= (-1) * rhs.denominator;
//				timev.denominator *= (-1) * rhs.numerator;
//			}
//			else {
//				timev.numerator *= rhs.denominator;
//				timev.denominator *= rhs.numerator;
//			}
//			Reduct(timev);
//			return timev;
//		}
//	}

	Fraction operator-() {
		Fraction timev = *this;
		timev.numerator *= -1;
		return timev;
	}
	~Fraction() {
		delete &numerator;
		delete &denominator;
	}

};

int main() {
	Fraction x(5, 1), y(5, 4), c(1, 1);
	x += y;
	std::cout << "x is " << x.numerator << ":" << x.denominator << ", y is " << y.numerator <<":" << y.denominator
			<< ", c is " << c.numerator << ":" << c.denominator << "\n";
return 0;
}
