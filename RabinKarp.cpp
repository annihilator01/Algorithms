#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector < unsigned long long > Power;
vector < unsigned long long > PrefixHash;
vector < int > InIndex;
string Pattern, Main;
unsigned long long PatternHash = 0;
int PrimeNumber = 103;

void InputStrings() {
	cin >> Pattern >> Main;

	if (Main.size() < Pattern.size()) {
		cout << 0;
		exit(0);
	}

}

void PrefixHashCalculation() {
	Power.resize(Main.size());
	PrefixHash.resize(Main.size());
	Power[0] = 1;
	PrefixHash[0] = Main[0] - 'A' + 1;

	for (int i = 1; i < Main.size(); i++) {
		Power[i] = Power[i - 1] * PrimeNumber;
		PrefixHash[i] = (Main[i] - 'A' + 1) * Power[i];
		PrefixHash[i] += PrefixHash[i - 1];
	}

}

void PatternHashCalculation() {

	for (int i = 0; i < Pattern.size(); i++) {
		PatternHash += (Pattern[i] - 'A' + 1) * Power[i];
	}

}

void SubStringComparison() {

	for (int i = 0; i <= Main.size() - Pattern.size(); i++) {
		unsigned long long tmp_pref_hash = PrefixHash[i + Pattern.size() - 1];

		if (i) {
			tmp_pref_hash -= PrefixHash[i - 1];
		}

		if (tmp_pref_hash == PatternHash * Power[i]) {
			InIndex.push_back(i + 1);
		}

	}
}

void RabinKarp() {
	PrefixHashCalculation();
	PatternHashCalculation();
	SubStringComparison();
}

void Output() {
	cout << InIndex.size() << '\n';

	if (InIndex.size()) {

		for (auto i : InIndex) {
			cout << i << ' ';
		}

	}
}

int main() {
	InputStrings();
	RabinKarp();
	Output();
	return 0;
}