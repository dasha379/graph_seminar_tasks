#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cmath>

// how to implement an universum??
const int UNIVERSUM_SIZE = 16;
std::vector<int> UNIVERSUM(UNIVERSUM_SIZE);

void transfer_to_bit_scale(const std::set<int>& arr, std::string& output)
{
	output.resize(UNIVERSUM_SIZE);
	for (int i = 0; i < UNIVERSUM_SIZE; ++i) UNIVERSUM[i] = i + 1;
	for (int i = 0; i < UNIVERSUM_SIZE; ++i){
		if (arr.find(UNIVERSUM[i]) != arr.end()){
			output[i] = '1';
		} else output[i] = '0';
	}
}

std::string union_bit_scales(const std::string& bit1, const std::string& bit2)
{
	std::string res;
	res.resize(UNIVERSUM_SIZE);
	for (int i = 0; i < UNIVERSUM_SIZE; ++i)
	{
		if (bit1[i] == '1' || bit2[i] == '1') res[i] = '1';
		else res[i] = '0';
	}
	return res;
}

std::string intersection_bit_scales(const std::string& bit1, const std::string& bit2)
{
	std::string res;
	res.resize(UNIVERSUM_SIZE);
	for (int i = 0; i < UNIVERSUM_SIZE; ++i)
	{
		if (bit1[i] == '1' && bit2[i] == '1') res[i] = '1';
		else res[i] = '0';
	}
	return res;
}

std::string addition_bit_scale(const std::string& bit)
{
	std::string res;
	res.resize(UNIVERSUM_SIZE);
	for (int i = 0; i < UNIVERSUM_SIZE; ++i)
	{
		char c = bit[i];
		if (c == '1') res[i] = '0';
		else res[i] = '1';
	}
	return res;
}

std::string diff_bit_scales(const std::string& bit1, const std::string& bit2)
{
	std::string res;
	res.resize(UNIVERSUM_SIZE);
	for(int i = 0; i < UNIVERSUM_SIZE; ++i)
	{
		if (bit1[i] == '1' && bit2[i] == '1' || bit1[i] == '0') res[i] = '0';
		else if (bit1[i] == '1' && bit2[i] == '0') res[i] = '1';
	}
	return res;
}

std::string int_to_bit(int n, int size)
{
	std::string s(size, '0');
	for (int i = size - 1; i >= 0; --i)
	{
		if (n > 0)
		{
			s[i] = (n % 2) ? '1' : '0';
			n/=2;
		}
	}
	return s;
}

std::vector<std::string> gen_all_subsets(const int n)
{
	int m = pow(2, n);
	std::vector<std::string> res;
	for (int i = 0; i < m; ++i)
	{
		std::string s;
		s += int_to_bit(i, n);
		res.push_back(s);
	}
	return res;
}

int main()
{
	std::set<int> arr = {1, 2, 3, 5, 8, 12};
	std::string bit1 = "1001010101101101";
	std::string bit2 = "1000110101010011";
	std::cout << union_bit_scales(bit1, bit2) << '\n';
	std::cout << intersection_bit_scales(bit1, bit2) << '\n';
	std::cout << addition_bit_scale(bit1) << '\n';
	std::cout << diff_bit_scales(bit1, bit2) << '\n';
	std::string s;
	transfer_to_bit_scale(arr, s);
	std::cout << s << '\n';

	int n = 3;
	std::vector<std::string> a = gen_all_subsets(n);
	for (int i = 0; i < 8; ++i) std::cout << a[i] << '\n';
	return 0;
}