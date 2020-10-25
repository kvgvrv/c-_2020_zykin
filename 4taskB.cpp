#include <iostream>
#include <string>


int64_t grade(int64_t x, int64_t n) {
	if (n == 0) {
		return 1;
	}
	else {
		n -= 1;
		return x * grade(x, n);
	}
}

int64_t Hash(const std::string& w) {
	int64_t result = 0;
	int64_t x = 101;
	int64_t q = grade(2,61) - 1;
	int64_t m = w.length() - 1;
	for (int64_t i = 0; i <= m; ++i) {
		result += w[i] * grade(x, m - i) % q;
	}
	return result;
}

int64_t reHash(const int64_t& previous_hash, const char& c1, const char& c2, const int64_t& m) {
	int64_t x = 101;
	int64_t q = grade(2,61) - 1;
	return ((previous_hash - c1 * grade(x, m - 1)) * x + c2) % q;
}

int main() {
	std::string word;
	std::string text;
	std::cin >> word;
	std::cin >> text;
	int64_t m = word.length();
	int64_t hs = Hash(word);
	int N = text.length();
	int64_t xew = Hash(text.substr(0, m));
	bool exist = 0;
	if (hs == xew) {
		std::cout << 0 << " ";
		exist = 1;
	}
	for (int i = 1; i <= N - m; ++i) {
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