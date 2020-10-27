#include <iostream>
#include <list>
#include <vector>


int hash(const int& x, const int& n) {
	if (x >= 0) {
		return (x % n);
	}
	else {
		return ((-x) % n);
	}
}

class Hash_table {
private:
	int size;
	std::vector<std::list<std::pair<int, int>>> table;
	int q;
public:
	Hash_table() {
		size = 0;
		q = 0;
		table.resize(size);
	}

	Hash_table(const int& n) {
		size = n;
		q = 0;
		table.resize(size);
	}

	~Hash_table() {}

	void push(const int& key, const int& value) {
		++q;
		int index = hash(key, size);
		bool search = 0;
		for (auto element = table[index].begin(); element != table[index].end();) {
			if (element->first == key) {
				element->second = value;
				search = 1;
				break;
			}
		}
		if (search == 0) {
			table[index].push_back({ key, value });
		}
		if (q >= size * 0.75) {
			int new_size = 2 * size;
			std::vector<std::list<std::pair<int, int>>> new_table(new_size);
			for (int i = 0; i < size; ++i) {
				for (auto element = table[i].begin(); element != table[i].end(); {
					int index = hash(element->first, new_size);
					new_table[index].push_back(*element);
				}
			}
			table = new_table;
			size = new_size;
		}
	}
	void pop(const int& key) {
		--q;
		int index = hash(key, size);
		for (auto element = table[index].begin(); element != table[index].end();) {
			if (element->first == key) {
				table[index].erase(element);
				break;
			}
		}
	}
	void get_value(const int& key, const int& value) {
		int index = hash(key, size);
		bool search = 0;
		for (auto element = table[index].begin(); element != table[index].end();) {
			if (element->first == key) {
				std::cout << element->second << "\n";
				search = 1;
				break;
			}
		}
		if (search == 0) {
			std::cout << value << "\n";
		}
	}
};

int main() {
	int N, M;
	std::cin >> N >> M;
	std::vector<Hash_table> data;
	for (int i = 0; i < N; ++i) {
		Hash_table table(32);
		data.push_back(table);
	}
	int index, key, value;
	char op;
	for (int i = 0; i < M; ++i) {
		std::cin >> index >> op >> key >> value;
		if (op == '+') {
			data[index].push(key, value);
		}
		if (op == '-') {
			data[index].pop(key);
		}
		if (op == '?') {
			data[index].get_value(key, value);
		}
	}
return 0;
}