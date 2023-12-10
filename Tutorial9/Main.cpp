#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <cctype>

bool vector_contains_word(const std::vector< std::string> & vec, std::string target)
{
    for (const std::string & s : vec)
    {
        if (s == target)
        {
            return true;
        }
    }

    return false;
}

std::vector<int> fill_buckets(const std::string& word)
{
    std::vector<int> buckets(26, 0); // 26 length, initialize all to 0
    for (char c : word)
    {
        buckets[c - 'a']++;
    }
    return buckets;
}

int get_points(const std::string& guess, const std::string& target)
{
    
    const auto guess_buck = fill_buckets(guess);
    const auto target_buck = fill_buckets(target);

    int score = 0;
    for (int i{ 0 }; i < guess_buck.size(); ++i)
    {
        score += std::min(guess_buck[i], target_buck[i]);
    }

    for (int i = 0; i < 5; ++i)
    {
        score += (guess[i] == target[i]);
    }

    return score;
}


int main()
{

    std::vector<std::string> five_letter_words;


    // this extra scope operator means file will be closed when done with it.
    {
        std::ifstream five_letter_file("sgb-words.txt");
        for (std::string line; std::getline(five_letter_file, line);)
        {
            if (line.empty())
            {
                continue;
            }

            five_letter_words.emplace_back(line);
        }
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, five_letter_words.size() - 1);
    const std::string target = five_letter_words[dist(rng)];

    while (true)
    {
        std::cout << "Guess a five letter word" << std::endl;
        std::string guess;

        // using cin as a stream object, cool
        std::getline(std::cin, guess);

        if (guess.size() != 5)
        {
            std::cout << "not a five letter word" << std::endl;
            continue;
        }

        for (char &c : guess)
        {
            c = std::tolower(c);
        }

        if (!vector_contains_word(five_letter_words, guess))
        {
            std::cout << "not a word silly" << std::endl;
            continue;
        }

        const int score = get_points(guess, target);
        std::cout << "Score is " << score << std::endl;
        if (score == 10)
        {
            std::cout << "you winnnnnnnnnnn" << std::endl;
            break;
        }
    }



    std::cin.get();
    return 0;
}