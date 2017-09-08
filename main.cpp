#include "index_program.h"

int main()
{
	//Character count class
	Count_character character;
	vector<Count_character> character_container;
	//Word count class
	Count_word word;
	map<string,Count_word> word_container;

	string input_file = { "War_And_Peace.txt" };
	string get_word;
	ifstream fin;
	ofstream fout1, fout2;
	
	open_files(fin, fout1, fout2, input_file);

	count_number_of_char_occurances(fin, fout1, character, character_container);
	fin.clear(); //Clears the input file
	fin.seekg(0, fin.beg); //Gets the information again to the input file so it can be read again
	count_number_of_words(fin, fout2, word, word_container);

	do
	{
		character.output_number_of_lines(character_container);
		display_lines_for_user_word(word,word_container);
	} while (user_wishes_to_continue());

	close_files(fin, fout1, fout2);
	return 0;
}