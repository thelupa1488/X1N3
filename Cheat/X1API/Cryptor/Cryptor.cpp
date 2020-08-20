#include "Cryptor.h"

std::string CCrypt::I(std::string str) {
	std::string ret;

	for (int i(0); i < (int)str.length(); i++) {
		for (int k(0); k < (int)alphabet.length(); k++) {
			if (str[i] == crypt[k]) {
				ret += alphabet[k];
			}
		}
	}
	return ret;
}

std::string CCrypt::O(std::string str) {
	std::string ret;

	for (int i(0); i < (int)str.length(); i++) {
		for (int k(0); k < (int)alphabet.length(); k++) {
			if (str[i] == alphabet[k]) {
				ret += crypt[k];
			}
		}
	}
	return ret;
}

std::string CCrypt::IEx(std::string &str) {

	for (size_t i(0); i < str.length(); i++) {
		for (size_t k(0); k < alphabet.length(); k++) {
			if (str[i] == crypt[k]) {
				str[i] = alphabet[k];
			}
		}
	}
	return str;
}

std::string CCrypt::OEx(std::string &str) {

	for (size_t i(0); i < str.length(); i++) {
		for (size_t k(0); k < alphabet.length(); k++) {
			if (str[i] == alphabet[k]) {
				str[i] = crypt[k];
			}
		}
	}
	return str;
}

std::vector<int> CCrypt::VO(std::string str, int ob)
{
	std::vector<int> out;
	for (int i(0); i < ob; i++)
		str = O(str);

	for (int i(0); i < (int)str.length(); i++)
		for (int k(0); k < (int)crypt.length(); k++)
			if (str[i] == crypt[k])
				out.insert(out.end(), k);

	return out;
}

std::string CCrypt::VI(std::vector<int> vec, int ob) {

	std::string ret;

	for (int i(0); i < (int)vec.size(); i++)
		for (int k(0); k < (int)crypt.length(); k++)
			if (vec[i] == k)
				ret += crypt[k];

	for (int i(0); i < ob; i++)
		ret = I(ret);

	return ret;
}