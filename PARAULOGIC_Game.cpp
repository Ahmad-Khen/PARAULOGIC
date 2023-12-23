#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <map>
#include <random>

using namespace std;

// Function to verify the letters
enum VerificationResult {
    ContainsCentralAndGivenLetters,
    ContainsCentralButGivenLettersNotThere,
    DoesNotContainCenterAndLettersGiven,
    DoesNotContainCenterAndGivenLettersNotThere
};
// Function to check if a character is a vowel
bool isVowel(char);
// This function receive two parameters one is Played letter string and second is user input string.
//It will return the four cases
VerificationResult Verify_letters(const string& , const string&);
bool Exists(const string& word, vector<string>& , int& );
bool hasSameSetOfLetters(const string& , const string&);
vector<string> findWordsWithSameLetters(const string& , const vector<string>& );
// map<string, int> findWordsWithSameLetters(const string& , const vector<string>& );

void displayCombinations(const vector<string>& , char , char , int );
string sortString(const string& );
bool isInDictionary(const string& , const vector<string>& );




// Vector to store words
vector<string> words;
vector<string> foundWords;
int subtractPoints = 0;
int limitAttempts = 0;

int main(int argc, char *argv[]) {
    // Default file name
    string fileName = "Palabras.txt";

    const int WORD_SIZE = 10;

    int score = 0;
    string exitProgram = "@exit";
    string help="@help";
    string hint = "@hint";
    string found = "@found";
    string show = "@show";
    string showScore = "@score";
    string shuffle = "@shuffle";
    string restart = "@restart";
    string recover = "@recover";
    string difficulty = "@difficulty";
    string attempts = "@attempts";
    string ranking = "@ranking";
    bool checkLimitAttempts = false;
    bool checkDifficult = false;

    // Check if a command-line argument is provided
    if (argc > 1) {
        fileName = argv[1];
    }

    // Open the text file
    ifstream inputFile(fileName);

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        cerr << "Unable to open the file: " << fileName << endl;
        return -1; // Return an error code
    }

    // Read the file line by line
    string line;
    while (getline(inputFile, line)) {
        // Use a stringstream to extract words from each line
        istringstream iss(line);
        string word;

        while (iss >> word) {
            // Check if the word has less than or equal to 7 letters
            if (word.length() <= WORD_SIZE) {
                // Store the word in the vector
                words.push_back(word);
            }
        }
    }

    // Close the file
    inputFile.close();

    // Choose a word randomly from the vector
    start_game: if (!words.empty()) {
        srand(static_cast<unsigned>(time(NULL)));
        int randomIndex = rand() % words.size();
        string chosenWord = words[randomIndex];
        // Display the chosen word
        // cout << "\n\nRandomly chosen word: " << chosenWord << endl;

        // Find the middle letter
        size_t middleIndex = chosenWord.length() / 2;
        char middleLetter = chosenWord[middleIndex];

        // middleLetter = 'c';

        // Keep all unique letters without repeating
        string uniqueLetters = "";
        for (char c : chosenWord) {
            if (isalpha(c) && uniqueLetters.find(c) == string::npos) {
                uniqueLetters += c;
            }
        }

        // Display unique letters
        // cout << "Unique letters: " << uniqueLetters << endl;

        // Save all unique letters to play in a string
        string lettersToPlay = uniqueLetters;

        // Ensure there are at least two vowels in the final string
        int vowelCount = 0;
        for (char c : lettersToPlay) {
            if (isVowel(c)) {
                vowelCount++;
            }
        }

        // Add more vowels if needed
        while (vowelCount < 2) {
            char randomVowel = "aeiou"[rand() % 5];
            if (lettersToPlay.find(randomVowel) == string::npos) {
                // Add the vowel to the string if it's not already present
                lettersToPlay += randomVowel;
                vowelCount++;
            }
        }

        // Generate the remaining letters randomly, if needed
        while (lettersToPlay.length() < 7) {
            char randomLetter = 'a' + rand() % 26;
            if (lettersToPlay.find(randomLetter) == string::npos) {
                // Add the letter to the string if it's not already present
                lettersToPlay += randomLetter;
            }
        }

        lettersToPlay = lettersToPlay.substr(0, 7);

        // Ensure the central letter is in the middle of the string
        size_t centralPosition = lettersToPlay.find(middleLetter);
        if (centralPosition != string::npos && centralPosition != lettersToPlay.size() / 2) {
            swap(lettersToPlay[centralPosition], lettersToPlay[lettersToPlay.size() / 2]);
        }

        // Display the final string of letters to play
        cout << endl << "Letters to play: " << lettersToPlay << endl << endl;

        // lettersToPlay = "groceiy";


        cout << "-----------------------------------------------------------------------------------------------" << endl << endl;
        int size = lettersToPlay.size() / 2 + 1;
        int stringIterator = 0;
        for (int i = 0; i < size / 2; i++) {
            for (int j = 0; j < size / 2 - i; j++)
                cout << "\t\t";
            for (int k = 0; k < 2 * i + 1; k++) {
                if (k == 0 || k == 2 * i)
                    cout << lettersToPlay[stringIterator++];
                else
                    cout << "\t\t\t\t";
            }
            cout << endl;
        }

        for (int i = 0; i <= size / 2; i++) {
            if ( i == size / 2) {
                cout << lettersToPlay[stringIterator++];
            }
            else {
                cout << "\t\t";
            }
        }
        cout << endl;

        // Lower part of the diamond
        for (int i = size / 2 - 1; i >= 0; i--) {
            for (int j = 0; j < size / 2 - i; j++)
                cout << "\t\t";
            for (int k = 0; k < 2 * i + 1; k++) {
                if (k == 0 || k == 2 * i)
                    cout << lettersToPlay[stringIterator++];
                else
                    cout << "\t\t\t\t";
            }
            cout << endl;
        }
        
        // cout << lettersToPlay
        // cout << "Middle letter: " << middleLetter << endl;

        cout << endl << "-----------------------------------------------------------------------------------------------" << endl << endl;

        string userEnteredLetters;

        while(userEnteredLetters != exitProgram) {
            // Prompt the user to enter their word
            cout << "Please Enter Your Word: ";
            cin >> userEnteredLetters;


            if (userEnteredLetters == hint) {
// find all matching words

            // Sort the user input string

                // Find words with the same set of letters
                vector<string> matchingWords = findWordsWithSameLetters(lettersToPlay, words);

                // Find all words in the dictionary with the same sorted characters

                    // Merge and count occurrences based on the first two letters
                map<string, int> mergedWordCounts;
            
                for (const string& word : matchingWords) {
                    string key = word.substr(0, 2);
                    mergedWordCounts[key]++;
                }

                // Display the matching words
                cout << "Matching words in the dictionary:" << endl;
                for (const auto& entry : mergedWordCounts) {
                    cout << "They begin with: " << entry.first  << "--> appears: " << entry.second << endl;
                }
            }
            else if (userEnteredLetters == help) {
                // possible help
            }

            else if (userEnteredLetters == found) {
                string sortedUserInput = sortString(lettersToPlay);
                
                vector<string> similarWords;
                for (const string& dictWord : words) {
                    if (sortString(dictWord) == sortedUserInput) {
                        similarWords.push_back(dictWord);
                    }
                }
                cout << "There are "<<similarWords.size() <<" Words found with set of letters. " << endl;
                for (const auto& foundWord : similarWords) {
                    cout<<"The word found with set of letters: " << foundWord << endl;
                }
            }
            else if (userEnteredLetters == showScore) {
                cout << "Score You Obtained: " << score << endl;
            }

            else if (userEnteredLetters == show) {
                string sortedUserInput = sortString(lettersToPlay);
                
                vector<string> similarWords;
                for (const string& dictWord : words) {
                    if (sortString(dictWord) == sortedUserInput) {
                        similarWords.push_back(dictWord);
                    }
                }

                for (const auto& foundWord : similarWords) {
                    if (foundWord[foundWord.size()/2] == middleLetter)
                        cout<<"The word found with set of letters that it will always contain the central letter\n " << foundWord << endl;
                }
            } 
            else if (userEnteredLetters == shuffle) {
                random_device rd;
                mt19937 g(rd());

                // Shuffle the characters of the string

                std::shuffle(lettersToPlay.begin(), lettersToPlay.begin() + middleIndex - 1, g);
                std::shuffle(lettersToPlay.begin() + middleIndex, lettersToPlay.end(), g);


                cout << "-----------------------------------------------------------------------------------------------" << endl << endl;
                int size = lettersToPlay.size() / 2 + 1;
                int stringIterator = 0;
                for (int i = 0; i < size / 2; i++) {
                    for (int j = 0; j < size / 2 - i; j++)
                        cout << "\t\t";
                    for (int k = 0; k < 2 * i + 1; k++) {
                        if (k == 0 || k == 2 * i)
                            cout << lettersToPlay[stringIterator++];
                        else
                            cout << "\t\t\t\t";
                    }
                    cout << endl;
                }

                for (int i = 0; i <= size / 2; i++) {
                    if ( i == size / 2) {
                        cout << lettersToPlay[stringIterator++];
                    }
                    else {
                        cout << "\t\t";
                    }
                }
                cout << endl;

                // Lower part of the diamond
                for (int i = size / 2 - 1; i >= 0; i--) {
                    for (int j = 0; j < size / 2 - i; j++)
                        cout << "\t\t";
                    for (int k = 0; k < 2 * i + 1; k++) {
                        if (k == 0 || k == 2 * i)
                            cout << lettersToPlay[stringIterator++];
                        else
                            cout << "\t\t\t\t";
                    }
                    cout << endl;
                }
                
                // cout << lettersToPlay
                // cout << "Middle letter: " << middleLetter << endl;

                cout << endl << "-----------------------------------------------------------------------------------------------" << endl << endl;
            }

            else if (userEnteredLetters == restart) {
                // Clear the screen before restarting on Windows
                #ifdef _WIN32
                system("cls");
                #else
                // On Unix/Linux, you might use "clear"
                system("clear");
                #endif

                goto start_game;
            }
            else if (userEnteredLetters == recover) {
                cout << endl << "Letters to play: " << lettersToPlay << endl << endl;
            }

            else if (userEnteredLetters == difficulty) {
                cout<<"Level Difficult!\nNow! When You Entered The Wrong Letter It Will Subract 2 Points From Your Score\n";
                subtractPoints = 2;
                checkDifficult = true;
            }

            else if (userEnteredLetters == attempts) {
                limitAttempts = 0;
                vector<string> matchingWords = findWordsWithSameLetters(lettersToPlay, words);

                // Find all words in the dictionary with the same sorted characters

                    // Merge and count occurrences based on the first two letters
                map<string, int> mergedWordCounts;
            
                for (const string& word : matchingWords) {
                    string key = word.substr(0, 2);
                    mergedWordCounts[key]++;
                }

                for (const auto& entry : mergedWordCounts) {
                    limitAttempts += entry.second;
                }

                checkLimitAttempts = true;

                cout << "Now! You have " << limitAttempts << " Attempts To Find The Word" << endl;
            }

            else if (ranking == userEnteredLetters) {
                
            }

            else {

                // Verify letters and display the result
                VerificationResult result = Verify_letters(lettersToPlay, userEnteredLetters);
                switch (result) {
                    case VerificationResult::ContainsCentralAndGivenLetters:
                        cout << "It contains central and there are the given letters" << endl;
                        break;
                    case VerificationResult::ContainsCentralButGivenLettersNotThere:
                        cout << "Contains central, but the given letters are not there" << endl;
                        if (checkDifficult) { score-=subtractPoints; } if(checkLimitAttempts) { limitAttempts--; }
                        break;
                    case VerificationResult::DoesNotContainCenterAndLettersGiven:
                        cout << "Does not contain a center, but the letters are given" << endl;
                        if(checkDifficult) { score-=subtractPoints; } if(checkLimitAttempts) { limitAttempts--;  }
                        break;
                    case VerificationResult::DoesNotContainCenterAndGivenLettersNotThere:
                        cout << "Does not contain a center, and the given letters are not there" << endl;
                        if(checkDifficult) { score-=subtractPoints; } if(checkLimitAttempts) { limitAttempts--; }
                        break;
                }

                if (Exists( userEnteredLetters, words, score)) {

                    vector<int> allScore;
                    cout << "Word Found" << endl;

                    vector<string> wordCounts = findWordsWithSameLetters(lettersToPlay, words);

                    if (wordCounts.size() == 0) {
                        cout << "Congratulation: All Words Have Been Found With The Set Of Letters\nThank You! Good Bye!\n";
                        cout << "Your Score" << endl;
                        
                        for (vector<int>::iterator it = allScore.begin(); it != allScore.end(); ++it) {
                            cout << "Previous Score: " << *it << endl;
                        }

                        // cout << ""
                        
                        
                        exit(EXIT_SUCCESS);
                    }
                }



                // if (wordCounts.size() == 0) {
                //     cout << "Congratulation: All Words Have Been Found With The Set Of Letters\nThank You! Good Bye!\n";
                //     exit(EXIT_SUCCESS);
                // }

            }

             

            // // Display matching words
            // for (const string& word : matchingWords) {
            //     cout << word << endl;
            // }

            

        }


    } else {
        cout << "\n\nNo words available in the vector.\n";
    }

    return 0; // Return success code
}


VerificationResult Verify_letters(const string& lettersToPlay, const string& userEnteredLetters) {
    // Find the central letter
    char centralLetter = lettersToPlay[3];

    // Check if the central letter is in the user's entered letters
    size_t centralPositionInUserLetters = userEnteredLetters.find(centralLetter);


    if (centralPositionInUserLetters != string::npos) {
        // Case a: Contains central, and there are the given letters
        // return VerificationResult::ContainsCentralAndGivenLetters;
        bool allLettersPresent = true;
        for (char c : lettersToPlay) {
            size_t positionInUserLetters = userEnteredLetters.find(c);


        // If any character is not found, set allLettersPresent to false and break
            if (positionInUserLetters == string::npos) {
                allLettersPresent = false;
                return VerificationResult::ContainsCentralButGivenLettersNotThere;
            }
        }
        if (allLettersPresent) {
            return VerificationResult::ContainsCentralAndGivenLetters;
        }
    }
    else {
        // Case d: Does not contain a center, and the given letters are not there

        bool allLettersPresent = true;
        for (char c : lettersToPlay) {
            size_t positionInUserLetters = userEnteredLetters.find(c);
            // If any character is not found, set allLettersPresent to false and break
            if (positionInUserLetters == string::npos) {
                allLettersPresent = false;
                return VerificationResult::DoesNotContainCenterAndGivenLettersNotThere;
            }
            if (allLettersPresent) {
                return VerificationResult::DoesNotContainCenterAndLettersGiven;
            }
        }
    }
    return VerificationResult::DoesNotContainCenterAndGivenLettersNotThere;

}

bool isVowel(char c) {
    c = tolower(c); // Convert to lowercase for case-insensitive check
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Function to check if a word exists in the vector and handle scoring logic
bool Exists(const string& word, vector<string>& wordVector, int& score) {
    // Check if the word exists in the vector
    auto it = find(wordVector.begin(), wordVector.end(), word);

    
    auto checkWord = find(foundWords.begin(), foundWords.end(), word);

    if (checkWord != foundWords.end()) {   

        cout << "The word is repeated. Score not increased." << endl;  
    
    }
    
    
    if (it != wordVector.end()) {
        // Word exists in the vector
        cout << "Yeah! Word Found." << endl;

        score += 5;
        cout << "Score increased by 5 points." << endl;
        foundWords.push_back(word);
        wordVector.erase(it);

        // vector<string> wordCounts = findWordsWithSameLetters(lettersToPlay, words);

        // if (wordCounts.size() == 0) {
        //     cout << "Congratulation: All Words Have Been Found With The Set Of Letters\nThank You! Good Bye!\n";
        //     cout << "Your Score" << endl;
            
        //     for (vector<int>::iterator it = allScore.begin(); it != allScore.end(); ++it) {
        //         cout << "Previous Score: " << *it << endl;
        
        //     // cout << ""
            
            
        //     exit(EXIT_SUCCESS);
        // }


        return true;
    } else if (it == wordVector.end() && checkWord == foundWords.end()) {
        // Word does not exist in the vector
        cout << "OOPs! Word Not found." << endl;
        
        return false;
    }
    else {
        return false;
    }
}

// Function to check if two strings contain the same set of letters
bool hasSameSetOfLetters(const string& str1, const string& str2) {
    string sortedStr1 = str1;
    string sortedStr2 = str2;

    // Sort the characters in each string
    sort(sortedStr1.begin(), sortedStr1.end());
    sort(sortedStr2.begin(), sortedStr2.end());

    // Compare the sorted strings
    return sortedStr1 == sortedStr2;
}

// Function to find words with the same set of letters in the vector
vector<string> findWordsWithSameLetters(const string& userInput, const vector<string>& wordVector) {
    vector<string> matchingWords;

    for (const string& word : wordVector) {
        if (hasSameSetOfLetters(word, userInput)) {
            matchingWords.push_back(word);
        }
    }

    return matchingWords;
}


// Function to find words with the same set of letters in the vector
// map<string, int> findWordsWithSameLetters(const string& userInput, const vector<string>& wordVector) {
//     map<string, int> wordCounts;

//     for (const std::string& word : wordVector) {
//         if (hasSameSetOfLetters(word, userInput)) {
//             // Extract the first two letters
//             string key = word.substr(0, 2);

//             // Increment the count if the key is already present, otherwise, add a new entry
//             wordCounts[key]++;
//         }
//     }

//     return wordCounts;
// }
// Function to display combinations and their occurrences
void displayCombinations(const vector<string>& dictionary, char firstLetter, char secondLetter, int maxWordSize) {
    // Map to store combinations and their occurrences
    map<string, int> combinations;

    // Iterate through the dictionary
    for (const string& word : dictionary) {
        // Check if the word is within the maximum size
        if (word.length() <= maxWordSize) {
            // Extract the first two letters
            string combination = word.substr(0, 2);

            // Check if the first two letters match the provided letters
            if (combination[0] == firstLetter && combination[1] == secondLetter) {
                // Update the occurrences in the map
                combinations[combination]++;
            }
        }
    }

    // Display the combinations and their occurrences
    for (const auto& entry : combinations) {
        cout << "Starts with: " << entry.first << " --> Appears: " << entry.second << " times" << endl;
    }
}
// Function to sort a string
string sortString(const string& s) {
    string sortedString = s;
    sort(sortedString.begin(), sortedString.end());
    return sortedString;
}

// Function to check if a sorted word is in the dictionary
bool isInDictionary(const string& sortedWord, const vector<string>& dictionary) {
    return binary_search(dictionary.begin(), dictionary.end(), sortedWord);
}
