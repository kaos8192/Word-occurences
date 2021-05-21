//Code by Geir Anderson for word occurance counter
//CMSC 318/GNED 495
//Lowercase method based on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case

#include <iostream>     //used for cerr/cout
#include <iomanip>      //used to format output
#include <fstream>      //used to access files
#include <string>       //allows for more string control 
#include <algorithm>    //used to access transform
#include <map>          //used to track word occurances

using namespace std;

//Function for printing out results to terminal
void print_term(map<string, int>& mapout)
{
    cout << "\033[38;5;10;48;5;0m" << left << setw(19) << "Word" << "| " << "Occurances" << "  \033[0m\n";
    cout << "\033[38;5;10;48;5;0m-------------------------------- \033[0m\n";

    for(auto& w: mapout)
    {
        cout << "\033[38;5;10;48;5;0m" << left << setw(19) << w.first << "| " << w.second << "           \033[0m\n";
    }

    return;
}

//Function for finding words and applying to map
void find_count(ifstream& reading, map<string, int>& mapin, string testmode)
{
    string current_word = "";

    int errornum = 0;

    while(reading >> current_word) //Read words from file and process
    {
        errornum ++;

        if(testmode == "full" or testmode == "1")
        {
            cerr << "\033[38;5;220;48;5;234m" << errornum << "\t\t" << current_word << endl;
            cerr << "\033[38;5;220;48;5;234m" << errornum << "\t\t" << current_word.size() << endl;
        }

        //New loop help received from Dr. Marmorstein

        string debugchecking = "";
        debugchecking = current_word;

        for(auto itr = current_word.begin(); itr != current_word.end(); ) //Look for punctuation.
        {
            if(ispunct(*itr))
            {
                itr = current_word.erase(itr);
            }
            else
            {
                itr++;
            }
        }

        /*      //Old loop
                for(int i = 0; i < current_word.size(); i++) //Look for punctuation
                {
                if(ispunct(current_word[i]))
                {
                current_word.erase(i, 1); //Remove punctuation
                i--;
                }
                }
                */
        if(current_word.size() > 0)
        {
            transform(current_word.begin(), current_word.end(), current_word.begin(), ::tolower); //Make all char lowercase

            if(testmode == "full" or testmode == "2")
            {
                cerr << "\033[38;5;220;48;5;234m" << errornum << "\t\t" << current_word << endl;
                cerr << "\033[38;5;220;48;5;234m" << errornum << "\t\t" << current_word.size() << endl;
            }

            if(current_word.size() > 17)
            {
                current_word.erase(current_word.begin()+13, current_word.end()); //Shorten long words to conserve screen space
                current_word += "...";
            }

            if(mapin.find(current_word) == mapin.end())
            {
                mapin[current_word] = 1; //Make new mapping if unique
            }

            else
            {
                mapin[current_word]++; //Count up if not unique
            }
        }
        else
        {
            if(testmode == "full" or testmode == "0")
            {
                cerr << "\033[38;5;220;48;5;234mThis word ( " << 
                    debugchecking << " ) appears to have been purely punctuation.\033[0m" << endl;
            }

        }
    }

    cout << "\033[0m";
    return;
}

//Main opens file and connects to count
int main(int argc, char** argv)
{
    ifstream toread;
    toread.open(argv[1]);

    if(!toread.is_open()) //Make sure that file opens correctly
    {
        cerr << "\033[38;5;15;1;48;5;160m" << "ERROR: File read in has failed.\033[0m" << endl;
        cerr << "\033[38;5;15;1;48;5;160m" << "Please, make sure that the name on the command line matches the file's name.\033[0m" << endl;
        return -1;
    }


    map<string, int> mapn;

    if(argc >= 3)
    {
        string s = argv[2];
        find_count(toread, mapn, s);
    }       

    else
    {
        find_count(toread, mapn, "norm");
    }

    print_term(mapn);

    //Ensure terminal format reset
    cout << "\033[0m";

    toread.close();

    return 0;
}
