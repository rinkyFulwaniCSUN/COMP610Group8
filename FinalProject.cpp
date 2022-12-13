#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
#include<algorithm>
#include <chrono>
using namespace std;
# define NO_OF_CHARS 256


int binarySearchIterative(vector<string> words, int beg, int end, string key) {
    while (beg <= end) {
        int middleIndex = (beg + end) / 2;
        if (words[middleIndex] == key) {
            return 1;
        }
        else if (words[middleIndex] < key)
            beg = middleIndex + 1;
        else if (words[middleIndex] > key)
            end = middleIndex - 1;
    }
    return 0;
}

void binarySearch(vector<string> words, int size,string targetWord)
{
    sort(words.begin(), words.end());
    int output = binarySearchIterative(words, 0, size-1, targetWord);
    if (output == 1)
        cout << "\nWord Found\n";
    else
        cout << "\nWord not Found\n";
}

int countwords(string filename)
{
	ifstream fin;
	fin.open(filename+".txt");
	char word[30];
	int count=0;
	while(!fin.eof())
	{
		fin>>word;
		count++;
	}
	fin.close();
    return count;
}
void badCharHeuristic( string str, int size, int badchar[NO_OF_CHARS])
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

int boyerMooreSearch( string txt, string pat)
{
    int patternSize = pat.size();
    int textSize = txt.size();
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, patternSize, badchar);
    int s = 0;
    while(s <= (textSize - patternSize))
    {
        int j = patternSize - 1;
        while(j >= 0 && pat[j] == txt[s + j])
            j--;
        if (j < 0)
        {
            s += (s + patternSize < textSize)? patternSize-badchar[txt[s + patternSize]] : 1;
            return 1;
        }
        else
            s += max(1, j - badchar[txt[s + j]]);
    }
    return 2;
}
void wordCheck(string filename,string targetWord,int algorithm) {
    if(algorithm == 1) {
        auto start = std::chrono::system_clock::now();
        int size = countwords(filename);
        vector<string> words(size);
        string inFileName = filename+".txt";
        ifstream inputFile;
        inputFile.open(inFileName.c_str());
        if (inputFile.is_open())
        {
            for (int i = 0; i <size; i++)
            {
                inputFile >> words[i];
            }
            inputFile.close(); 
        }
        else {
        cout << "Can't find input file " << inFileName << endl;
        }
        int n = words.size();
        binarySearch(words,n,targetWord);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "Total Time Elapsed: " << elapsed_seconds.count() << " seconds";
    }
    else if(algorithm == 2) {
        auto start = std::chrono::system_clock::now();
        std::ifstream ifs(filename+".txt");
        std::string content( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>()));
        string pat = targetWord;
        int result = boyerMooreSearch(content, pat);
        if(result == 1){
            cout<<"Word Found";
        }
        else{
            cout<<"Word Not Found";
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "Total Time Elapsed: " << elapsed_seconds.count() << " seconds";
    }
    else{
        cout << "Please select a valid Algorithm";
    }
}

int main()
{
    string targetWord;
    string filename;
    int algorithm;
    cout<<"Enter the file name:";
    cin>>filename;
    cout<<endl;
    cout <<"Type the word you want to find: ";
    cin>>targetWord;
    cout<<endl;
    cout<<"Press 1 : To Use Binary Search Algorithm"<<endl;
    cout<<"Press 2 : To Use Boyer Moore Algorithm"<<endl;
    cin>>algorithm;
    wordCheck(filename,targetWord, algorithm);
    return 0;
}
