#include <iostream>
#include <vector>
#include <cmath>
#include <string>

unsigned int gray_from_bin(unsigned int bin){
	return bin ^ (bin >> 1);
}

unsigned int bin_from_gray(unsigned int gray){
	unsigned int bin;
	for (bin = 0; gray; gray >>= 1){
		bin ^= gray;
	}
	return bin;
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
	int i = 0;
	for (const std::string& s : arr)
	{
		std::cout << i << " : " << s << '\n';
		i++;
	}
}

int main(){
	print_(gray_code(4));
	std::cout << "gray code from binary: \n";
	std::cout << gray_from_bin(5) << '\n';
	std::cout << "binary code from gray code: " << bin_from_gray(4) << '\n';
}