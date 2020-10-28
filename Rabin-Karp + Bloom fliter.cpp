#include <iostream>
#include <string>
#include <vector>


uint64_t grade(const uint64_t& x, const uint64_t& n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2 == 0) {
		return grade(x * x, n / 2);
	}
	return x * grade(x * x, n / 2);
}

uint64_t Hash(const std::string& w, const uint64_t& x) {
	uint64_t result = 0;
	uint64_t m = w.length() - 1;
	for (int64_t i = 0; i <= m; ++i) {
		result += w[i] * grade(x, m - i);
	}
	return result;
}

uint64_t reHash(const uint64_t& previous_hash, const char& c1, const char& c2, const uint64_t& m, const uint64_t& x) {
	return (previous_hash - c1 * grade(x, m - 1)) * x + c2;
}

int main() {
	std::string text;
	std::cin >> text;
	std::vector<uint64_t> X = { 7, 13, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
	std::uint64_t n = X.size();
	std::vector<uint64_t> hashes(3);
	uint64_t size = 67108864;
	std::vector<bool> table(size);
	uint64_t m = 10;
	uint64_t N = text.length();
	for (int i = 0; i < n; ++i) {
		hashes[i] = Hash(text.substr(0, m), X[i]);
		table[hashes[i] & (size - 1)] = 1;
	}
	for (uint64_t i = 1; i < N - m; ++i) {
		bool search = 1;
		for (int j = 0; j < n; ++j) {
			hashes[j] = reHash(hashes[j], text[i - 1], text[i - 1 + m], m, X[j]);
			if (table[hashes[j] & (size - 1)] == 0) {
				search = 0;
			}
			table[hashes[j] & (size - 1)] = 1;
		}
		if (search == 1) {
			std::cout << text.substr(i, m) << " ";
		}
	}
	return 0;
}
