//Copyright 2016 <Shunji Lin>

#include "HuffmanCoding.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "steadyClockTimer.hpp"

using namespace huffmancoding;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../huffman.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::string line;
    int n_characters;
    
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_characters;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }

    std::vector<Entry<int>> entries;

    for (int i = 0; i < n_characters; ++i) {
	std::istringstream iss(line);
	int weight;
	iss >> weight;
	entries.emplace_back(Entry<int>(i, weight));
    }

    SteadyClockTimer timer;
    timer.start();
    
    HuffmanCoding<int> encoding(entries);
    std::cout << "Maximum length of codeword is : " << encoding.maxLength() << std::endl;
    std::cout << "Minimum length of codeword is : " << encoding.minLength() << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}
