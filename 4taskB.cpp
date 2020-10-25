#include <iostream>
#include <string>
#include <cmath>


uint64_t grade(const uint64_t& x, const uint64_t& n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2 == 0) {
		return grade(x * x, n / 2);
	}
	return x * grade(x * x, n / 2);
}

uint64_t Hash(const std::string& w) {
	uint64_t result = 0;
	uint64_t x = 101;
//	int64_t q = grade(2, 61) - 1;
	uint64_t m = w.length() - 1;
	for (int64_t i = 0; i <= m; ++i) {
		result += w[i] * grade(x, m - i);
	}
	return result;
}

uint64_t reHash(const uint64_t& previous_hash, const char& c1, const char& c2, const uint64_t& m) {
	uint64_t x = 101;
//	int64_t q = grade(2, 61) - 1;
	return (previous_hash - c1 * grade(x, m - 1)) * x + c2;
}

int main() {
	std::string word;
	std::string text;
	std::cin >> word;
	std::cin >> text;
	uint64_t m = word.length();
	uint64_t hs = Hash(word);
	uint64_t N = text.length();
	uint64_t xew = Hash(text.substr(0, m));
	bool exist = 0;
	if (hs == xew) {
		std::cout << 0 << " ";
		exist = 1;
	}
	for (uint64_t i = 1; i <= N - m; ++i) {
		xew = reHash(xew, text[i - 1], text[i - 1 + m], m);
		if (hs == xew) {
			if (m < 2500) {
				if (word == text.substr(i, m)) {
					std::cout << i << " ";
					exist = 1;
				}
			}
			else {
				if (word == text.substr(i, 2500)) {
					std::cout << i << " ";
					exist = 1;
				}
			}
		}
	}
	if (exist == 0) {
		std::cout << -1;
	}
	return 0;
}
