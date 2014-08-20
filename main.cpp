#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>

std::vector<std::string> open_read_from_file(const char* input_file, char delimiter)
{
    std::vector<std::string> parsed_data;
    std::string extracted_data;

    std::ifstream read_from_file (input_file);

    if(read_from_file.is_open())
    {

        while(getline(read_from_file, extracted_data, delimiter))
        {
            parsed_data.push_back(extracted_data);

        }
        read_from_file.close();

    }
    else
    {
    }

    return parsed_data;
}

int random_gen( int max_possible )
{
    int roll_the_dice = 0;

    roll_the_dice = rand() % max_possible;

    return roll_the_dice;
}

void show_words_left(std::vector<std::string> list_words)
{
    std::cout << "================================" << std::endl;
    for( unsigned int i=0; i<list_words.size(); i++)
    {
        std::cout << "[" << i << "] ..... " << list_words[i] << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::string> gen_list_of_words ( int difficulty )
{
    unsigned int word_length = (difficulty * 2) + random_gen(3);
    int number_of_words = (difficulty * 2) + random_gen(5);

    if (word_length < 4)
    {
        word_length = 4;
    }

    if (number_of_words < 6)
    {
        number_of_words = 6;
    }

    std::vector<std::string> list_of_words;
    std::vector<std::string> list_of_chosen_words;
    std::vector<std::string> list_of_words_final;

    list_of_words = open_read_from_file("words.txt", ',');

    for( unsigned int i=0; i<list_of_words.size(); i++)
    {
        if( list_of_words[i].size() == word_length )
        {
            list_of_chosen_words.push_back(list_of_words[i]);
        }
    }

    int rnum = random_gen(list_of_chosen_words.size());

    for( int j=0; j<number_of_words; j++)
    {
        list_of_words_final.push_back(list_of_chosen_words[rnum+(j*3)]);
    }

    return list_of_words_final;
}

bool check_input( std::string correct_word, std::string guess )
{
    if( guess == correct_word)
    {
        return true;
    }

    return false;
}

int which_input( std::vector<std::string> list_words, std::string guess )
{
    for( unsigned int i=0; i<list_words.size();i++)
    {
        if( guess == list_words[i])
        {
            return i;
        }
    }
    return -1;
}

int check_num_differences( std::string correct_word, std::string guess )
{
    int number_of_correct_chars = 0;

    for( unsigned int i=0; i<guess.size();i++)
    {
        if( correct_word[i] == guess [i] )
        {
            number_of_correct_chars++;
        }
    }

    return number_of_correct_chars;

}

int pick_difficulty()
{
    int diff;

    std::cout << "Pick the difficulty level(1-5):";
    std::cin >> diff;

    return diff;
}

int main()
{
    srand(time(NULL));

    std::vector<std::string> list_of_all_words;
    int number_of_tries = 4;

    std::cout << "Fallout 3 :: Hacking minigame" << std::endl << std::endl;

    int difficulty = pick_difficulty();

    std::cout << std::endl <<"BurnsyCo. computer terimal v17.1a" << std::endl;
    std::cout << "Attempting to login as: root" << std::endl;
    std::cout << "Enter password ..." << std::endl << std::endl;

    list_of_all_words = gen_list_of_words ( difficulty );
    std::string correct_word = list_of_all_words[random_gen(list_of_all_words.size())];

    while( number_of_tries >= 0)
    {
        show_words_left(list_of_all_words);
        std::cout << number_of_tries << " attempts left." << std::endl;

        unsigned int guess_number;
        std::cin >> guess_number;

        std::string guessed_word;

        int number_correct;

        //see if the user put a number in instead
        if((guess_number <= list_of_all_words.size())&&(guess_number >= 0))
        {

            guessed_word = list_of_all_words[guess_number];

        }

        if(!check_input(correct_word, guessed_word))
        {
            number_of_tries--;
            number_correct = check_num_differences( correct_word, guessed_word );
            int your_guess = which_input(list_of_all_words, guessed_word);
            if(your_guess != -1)
            {
                list_of_all_words[your_guess].append(" ... [X]");
                std::cout << "Incorrect password (" << number_correct << "/" << correct_word.size() << ")" << std::endl << std::endl;
            }
            else
            {
                std::cout << guess_number << " is out of range, -1 attempts" << std::endl << std::endl;
            }
        }
        else
        {
            std::cout << "Access granted :: TERMINAL UNLOCKED" << std::endl;
            break;
        }

        if( number_of_tries == 0)
        {
            std::cout << "Access denied :: TERMINAL LOCKED" << std::endl;
            break;
        }
    }

    return 0;
}
