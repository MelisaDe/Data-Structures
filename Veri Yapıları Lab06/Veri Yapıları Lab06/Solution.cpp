//Ozge Katirci
//Melisa Demirhan
#include<iostream>
#include <vector>
#include <string>
#include<algorithm>
#include<fstream>
#include "WordFreq.h"
///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
bool compareAlphabet(WordFreq&, WordFreq&);
bool compareFreqValue(WordFreq&, WordFreq&);
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
	vector<WordFreq> result;
	vector<WordFreq>p;
	string word;
	
	ifstream file(filename);
	if (!file)
	{
		std::cout << "ERROR! File can not open.";
		exit(0);
	}

	while (file >> word) {
		for (int i = 0; i < word.size(); i++)
		{
			if (word[i] == ',' || word[i] == '.') {
				word = word.substr(0, word.length() - 1);
			}
		}
		if (word.size() > 2)
		{
			vector<WordFreq>::iterator i = p.begin();
			vector<WordFreq>::iterator j = p.end();
			int temp = 0;
			int temp2 = 0;
			for (; i < j; i++)
			{
				temp2++;
				if ((*i).word == word) {
					i->freq++;
					temp = 1;
					break;
				}
			}
			if (temp == 0) {
				p.push_back(word);
				p[temp2].freq = 1;
			}
		}
	}
	sort(p.begin(), p.end(), compareAlphabet);
	sort(p.begin(), p.end(), compareFreqValue);
	result = p;
	return result;
} //end-GetMostFrequentKWords
bool compareAlphabet(WordFreq& x, WordFreq& y)
{
	return x.word < y.word;
}
bool compareFreqValue(WordFreq& x, WordFreq& y)
{
	return x.freq > y.freq;
}