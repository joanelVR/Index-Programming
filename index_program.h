#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Count_character
{
public:
	Count_character();
	friend void count_number_of_char_occurances(ifstream& fin, ostream& fout, Count_character& character, vector<Count_character>& character_container);
	void output_number_of_lines(const vector<Count_character>& character_container);
	friend bool operator<(const Count_character& left, const Count_character& right);

private:
	int number_of_occurrences;
	char data;
};

class Count_word
{
public:
	Count_word();
	friend void count_number_of_words(ifstream& fin, ostream& fout, Count_word& word, map<string, Count_word>& word_container);
	int get_total_words() {return total_words;}
	vector<int> line_numbers;

private:
	int unique_words_count;
	int total_words;
};

void open_files(ifstream& fin, ofstream& fout1, ofstream& fout2, string input_file);
void close_files(ifstream& fin, ofstream& fout1, ofstream& fout2);
void display_lines_for_user_word(Count_word word, const map<string, Count_word>& word_container);
bool found_user_input_word(const string& input, const map<string, Count_word>& word_container);
void clear_keyboard_buffer(istream& in = cin);
bool user_wishes_to_continue();