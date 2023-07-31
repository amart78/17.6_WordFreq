/***************************************************************************************
17.6 WORD FREQUENCY

This program processes a file of the user's choice from a menu of options,
displaying the number of times each word appears in that file via the console 
as well as through a newly created text file.
****************************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void displayFileMenu();

int main(){
    fstream fin;
    string file;
    string line;
    int freq;
    map<string, int> wordFreqList;
    ofstream wordFreqFile;

    cout << "This program will show you how often each word appears in a file of your choosing.\n ";
    displayFileMenu();

    // Gets file name from user.
    cout << "\nEnter the name of the file you'd like to process: ";
    getline(cin, file);

    // Converts user input to `.txt` file format & opens corresponding file.
    file =  file + ".txt";      
    fin.open(file, ios::in);

    while (!fin.eof() ){
        // Loops through file for each line.
        for (int i = 1; !fin.eof(); i++){
            getline(fin, line);
            string word = "";

            // Loops through each line to get each character.
            for (int i = 0; i < line.length(); i++) {

                // Holds/gets current character.
                char curChar = line[i];

                // Checks if the char is alphabetic.
                if (!isalpha(curChar)) {

                    // Does actions until it reaches the end of a word.
                    if (word != "") {       

                        // Lowercases each char in the word.
                        for (int i = 0; i < word.length(); i++) {
                            word[i] = tolower(word[i]);
                        }

                        // Initializes the number of times the word appears to 0.
                        int count = 0;

                        // Checks the `wordFreqList` to find out if the word
                        // has been seen before and get its last recorded frequency.
                        try {
                            count = wordFreqList[word];
                        } catch (exception e) {

                        }

                        // Increments `freq` for the word by 1.
                        wordFreqList[word] = count + 1;
                    }

                    // Reassigns `word` to be an empty string 
                    // to prepare to process the next word.
                    word = "";
                    continue;    
                }

                // Adds each char to form the word.
                word += curChar;
            }
        }
        fin.close();

        // Displays the `wordFreqList` map values and outputs them to a new file.
        wordFreqFile.open("Word Frequency: "+ file);

        for(const auto& elem : wordFreqList) {
            std::cout << elem.first << " " << elem.second << "\n";
            wordFreqFile  << elem.first << " " << elem.second << "\n";
        }

        wordFreqFile.close();
    }

    return 0;
}

// displayFileMenu ------------------------------------------------------------
// This function outputs file names the user can choose
void displayFileMenu(){
    cout << "\nFiles Available:\n\n"
         << "A Tale of Two Cities\n"
         << "Adventures of Sherlock Holmes\n"
         << "Count of Monte Cristo\n"
         << "Moby Dick\n"
         << "The Time Machine\n";
}