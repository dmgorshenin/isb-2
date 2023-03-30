#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
using namespace std;

double frequency_bitwise_test(const vector<unsigned short>& seq) {
	double Sn=0;
	for (size_t i = 0; i < seq.size(); i++) {
		if (seq[i] == 1) {
			Sn += 1;
		}
		else {
			Sn -= 1;
		}
	}
	Sn /= sqrt(seq.size());
	cout << "Sn = " << Sn << endl;

	double P = erfc(fabs(Sn / sqrt(2)));
	cout << "P = " << P << endl;
	return P;
}

double identical_consecutive_bits(const vector<unsigned short>& seq) {
	double ETTA = 0;
	for (auto i : seq) {
		ETTA += i;
	}
	ETTA /= seq.size();
	cout << "ETTA = " << ETTA << endl;

	if (fabs(ETTA - 0.5) > (2 / sqrt(seq.size()))) {
		return 0;
	}
	
	double V = 0;
	for (size_t i = 0; i < seq.size() - 1; ++i) {
		if (seq[i] != seq[i + 1])
		{
			V += 1;
		}
	}
	cout << "Vn = " << V << endl;

	double P = erfc(fabs(V - 2 * seq.size() * ETTA * (1 - ETTA)) / (2 * sqrt(2 * seq.size()) * ETTA * (1 - ETTA)));
	cout << "P = " << P << endl;
	return P;
}

double the_longest_sequence_of_units_in_a_block(const vector<unsigned short>& seq) {
	vector<unsigned short> amount_of_units;
	size_t index = 0;
	while (true) {
		if (index == 128) {
			break;
		}

		vector<unsigned short> tmp;
		for (size_t i = index; i < index+8; i++)
		{
			tmp.push_back(seq[i]);
		}
		
		size_t max = 0, current = 0;

		for (auto i : tmp) {
			if (i == 1) {
				++current;
			}
			else {
				if (current > max) {
					max = current;
					current = 0;
				}
			}
		}
		amount_of_units.push_back(max);
		index += 8;
	}

	int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
	for (auto i : amount_of_units) {
		if (i <= 1) { v1++; }
		if (i == 2) { v2++; }
		if (i == 3) { v3++; }
		if (i >= 4) { v4++; }
	}

	vector <int> v_array = { v1, v2 ,v3 ,v4 };
	vector<double> pi_array = { 0.2148 ,0.3672, 0.2305 ,0.1875 };
	double X = 0;
	for (int i = 0; i < 4; ++i) {
		X += (pow(v_array[i] - 16 * pi_array[i], 2)) / (16 * pi_array[i]);
	}

	cout <<"X = " << X << endl;
	return X;
}

int main() {
	vector<unsigned short> sequence(128);
	srand(time(NULL));

	for (int i = 0; i < 128; i++)
	{
		sequence[i] = rand() % 2;
		cout << sequence[i] <<"\t";
	}
	frequency_bitwise_test(sequence);
	identical_consecutive_bits(sequence);
	the_longest_sequence_of_units_in_a_block(sequence);
}