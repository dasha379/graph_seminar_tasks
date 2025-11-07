#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cmath>

const int UNIVERSUM_SIZE = 16;
std::vector<int> UNIVERSUM(UNIVERSUM_SIZE);


std::string transfer_to_bit_scale(const std::set<int>& arr)
{
	std::string output(UNIVERSUM_SIZE, '0');
	for (int i = 0; i < UNIVERSUM_SIZE; ++i) UNIVERSUM[i] = i + 1;
	for (int i = 0; i < UNIVERSUM_SIZE; ++i){
		if (arr.find(UNIVERSUM[i]) != arr.end()){
			output[i] = '1';
		} else output[i] = '0';
	}
	return output;
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

std::vector<std::string> gray_code(const int n) // n - size of a set
{
	if (n <= 0) return {"0"};
	if (n == 1) return {"0", "1"};
	std::vector<std::string> prev = gray_code(n - 1);
	std::vector<std::string> res;
	for (const std::string& s : prev)
	{
		res.push_back("0" + s);
	}
	for (auto i = prev.rbegin(); i != prev.rend(); ++i)
	{
		res.push_back("1" + *i);
	}
	return res;
}

void print_(const std::vector<std::string>& arr)
{
	for (const std::string& s : arr)
	{
		std::cout << s << '\n';
	}
}

int main()
{
	// Инициализируем универсум один раз
    std::set<int> arr = {1, 2, 3, 5, 8, 12};
    
    // Тестируем преобразование в битовую шкалу
    std::string bit1 = transfer_to_bit_scale(arr);
    std::cout << "Set to bit scale: " << bit1 << '\n';
    
    // Создаем второй тестовый набор
    std::set<int> arr2 = {2, 4, 6, 8, 10, 12, 14, 16};
    std::string bit2 = transfer_to_bit_scale(arr2);
    std::cout << "Second set to bit scale: " << bit2 << '\n';
    
    // Тестируем операции
    std::cout << "Union: " << union_bit_scales(bit1, bit2) << '\n';
    std::cout << "Intersection: " << intersection_bit_scales(bit1, bit2) << '\n';
    std::cout << "Complement of first: " << addition_bit_scale(bit1) << '\n';
    std::cout << "Difference (first - second): " << diff_bit_scales(bit1, bit2) << '\n';
    
    // Тестируем генерацию подмножеств
    int n = 4;
    std::vector<std::string> subsets = gen_all_subsets(n);
    std::cout << "\nAll subsets of size " << n << ":\n";
    for (size_t i = 0; i < subsets.size(); ++i) {
        std::cout << subsets[i] << '\n';
    }
    std::cout << '\n';
    std::cout << "gray code: \n";
    print_(gray_code(3));
    return 0;
}