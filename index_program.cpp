#include "index_program.h"

/*******************************************FUNCTIONS FOR Count_character*****************************************************/
Count_character::Count_character()
{
	number_of_occurrences = 1;
	data = '0';
}

bool operator<(const Count_character& left, const Count_character& right)
{
	return left.data < right.data;
}

void count_number_of_char_occurances(ifstream& fin, ostream& fout, Count_character& character, vector<Count_character>& character_container)
{
	char c;
	bool is_character_stored;
	int number_of_unique_chars_found = 0;

	while (fin.get(c))
	{
		is_character_stored = false;

		character.data = c;
		for (int i = 0; i < number_of_unique_chars_found; i++)
		{
			if (c == character_container[i].data)
			{
				character_container[i].number_of_occurrences++;
				is_character_stored = true;
				break;
			}
		}
		if (!is_character_stored)
		{
			character_container.push_back(character);
			number_of_unique_chars_found++;
		}
	}

	sort(character_container.begin(), character_container.end());

	fout << "-------------------------" << endl;
	fout << "CHARACTERS  |" << "  CHAR COUNT" << endl;
	fout << "-------------------------" << endl;
	for (int index = 0; index < character_container.size(); index++)
	{
		fout << "    " << setw(12) << left << character_container[index].data << character_container[index].number_of_occurrences << endl;
	}
}

void Count_character::output_number_of_lines(const vector<Count_character>& character_container)
{
	cout << "Number of lines in the file is: " << character_container[0].number_of_occurrences + 1 << endl;
}

/*******************************************FUNCTIONS FOR Count_word*****************************************************/
Count_word::Count_word()
{
	unique_words_count = 0;
	total_words = 0;
}

void count_number_of_words(ifstream& fin, ostream& fout, Count_word& word, map<string, Count_word>& word_container)
{
	char c;
	int line_position = 1;
	string temp;
	int word_count = 0;

	fin.get(c);
	while (!fin.eof())
	{	
		if (!isalpha(c))
		{
			if (c == '\n')
			{
				line_position++;
			}
			fin.get(c);
		}

		while (isalpha(c))
		{
			c = tolower(c);
			temp.push_back(c);
			fin.get(c);

			while (c == '-')
			{
				temp.push_back(c);
				fin.get(c);
			}
		}

		if (!temp.empty())
		{
			word_container[temp].line_numbers.push_back(line_position);
			word_container[temp].unique_words_count++;
			word.total_words++;
			temp.clear();
		}
	}

	fout << "-----------------------------------------------" << endl;
	fout << "|   UNIQUE WORDS  " << "                WORD COUNT  |" << endl;
	fout << "-----------------------------------------------" << endl;
	for (auto p = word_container.begin(); p != word_container.end(); p++)
	{
		//setw(20) sets the width to 20 and "left" left justify the words. Located in library #include <iomanip>
		fout << "   " << setw(35) << left << p->first << p->second.unique_words_count << endl;
	}
}

/*******************************************NON-CLASS FUNCTIONS*****************************************************/
void open_files(ifstream& fin, ofstream& fout1, ofstream& fout2, string input_file)
{
	string output_file1 = "character_count.txt";
	string output_file2 = "word_count.txt";

	fin.open(input_file);
	if (fin.fail())
	{
		cout << "Failed to open the file " << input_file << endl;
		exit(1);
	}

	fout1.open(output_file1);
	if (fout1.fail())
	{
		cout << "Failed to open the file " << output_file1 << endl;
		exit(1);
	}

	fout2.open(output_file2);
	if (fout2.fail())
	{
		cout << "Failed to open the file " << output_file2 << endl;
		exit(1);
	}
}

void close_files(ifstream& fin, ofstream& fout1, ofstream& fout2)
{
	fin.close();
	fout1.close();
	fout2.close();
}

void display_lines_for_user_word(Count_word word, const map<string, Count_word>& word_container)
{
	string get_input_word;
	int number = 0;

	cout << "Total number of words in the file is: " << word.get_total_words() << endl;
	cout << "Total number of unique words in the file is: " << word_container.size() << endl;
	cout << "\nWhat word would you like to search for: ";
	cin >> get_input_word;
	clear_keyboard_buffer();

	while (!found_user_input_word(get_input_word, word_container))
	{
		cout << "Sorry, but the word you have provided is not in the file" << endl;
		cout << "Please provide another word that you would like to search for: ";
		cin >> get_input_word;
		clear_keyboard_buffer();
	}

	for (auto p = word_container.begin(); p != word_container.end(); p++)
	{
		if (get_input_word == p->first)
		{
			cout << p->first << " is located at lines: " << endl;
			for (int i = 0; i < p->second.line_numbers.size(); i++)
			{
				if (number == 6)
				{
					cout << endl;
					number = 0;
				}
				cout << setw(10) << left << p->second.line_numbers[i];
				number++;
			}
			cout << endl << endl;
			break;
		}
	}
}

bool found_user_input_word(const string& input, const map<string, Count_word>& word_container)
{
	bool found_word = false;

	for (auto p = word_container.begin(); p != word_container.end(); p++)
	{
		if (input == p->first)
		{
			found_word = true;
		}
	}

	return found_word;
}

//C++: Saved Program "Clear Keyboard Buffer" 
//Will eat up anything up to the new line character.
//In order to use it: 1- put in the declaration "void clear_keyboard_buffer(istream& in = cin);"
//					  2- Make the function call clear_keyboard_buffer();
void clear_keyboard_buffer(istream& in)
{
	if (in.fail())
	{
		in.clear(); //gets him out of the fail state
	}
	in.ignore(numeric_limits<streamsize>::max(), '\n');
}

//C++: Saved Program "User_Wishes_to_Continue()"
// Will prompt the user if he wants to continue running the program
bool user_wishes_to_continue()
{
	char answer;

	//-------------------------------------------------------//
	cout << "Do you wish to continue? (y/n): ";
	cin >> answer;
	clear_keyboard_buffer();

	while (answer != 'y' && answer != 'Y' &&
		answer != 'n' && answer != 'N')
	{
		cout << "I'm sorry but that input is not valid" << endl;
		cout << "Do you wish to continue? (y/n): ";
		cin >> answer;
		clear_keyboard_buffer();
	}
	// only returns if the character y or Y were inputted
	return answer == 'y' || answer == 'Y';
}