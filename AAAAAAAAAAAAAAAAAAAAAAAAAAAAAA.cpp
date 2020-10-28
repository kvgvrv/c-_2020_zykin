#include <iostream>
#include <string>
#include <vector>
#include <list>


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
	uint64_t x = 13;
	uint64_t result = 0;
	uint64_t m = w.length() - 1;
	for (int64_t i = 0; i <= m; ++i) {
		result += w[i] * grade(x, m - i);
	}
	return result;
}

uint64_t reHash(const uint64_t& previous_hash, const char& c1, const char& c2, const uint64_t& m) {
	uint64_t x = 13;
	return (previous_hash - c1 * grade(x, m - 1)) * x + c2;
}

int main() {
	std::string text;
	std::cin >> text;
	uint64_t m = 10;
	uint64_t N = text.length();
	uint64_t size = 32;
	std::vector<std::list<std::string>> table(size);
	uint64_t q = 0;
	uint64_t xew = Hash(text.substr(0, m));
	uint64_t index = xew % size;
	table[index].push_back(text.substr(0, m));
	for (int i = 1; i <= N - m; ++i) {
		xew = reHash(xew, text[i - 1], text[i - 1 + m], m);
		index = xew % size;
		bool search = 0;
		for (auto element = table[index].begin(); element != table[index].end(); ++element) {
			if (*element == text.substr(i, m)) {
				std::cout << text.substr(i, m) << " ";
				search = 1;
				break;
			}
		}
		if (search == 0) {
			++q;
			table[index].push_back(text.substr(i, m));
			if (q >= size * 0.75) {
				uint64_t new_size = 2 * size;
				std::vector<std::list<std::string>> new_table(new_size);
				for (int i = 0; i < size; ++i) {
					for (auto element = table[i].begin(); element != table[i].end(); ++element) {
						index = Hash(*element) % new_size;
						new_table[index].push_back(*element);
					}
				}
				table = new_table;
				size = new_size;
			}
		}
	}
	return 0;
}