/*
CIS22B
Lab 1: Sorts and searches an input text file and outputs the results to the screen and to an output text file
Name: Michelle Maidana

Pseudocode:
	Prompt user for input file path
	Validate input
	Prompt user for output file path
	Validate input
	Open output file
	If file can't open
		Output error message to screen and terminate the program
	Open input file
	If file can't open
		Output error message to output file and terminate the program
	If max size of array is not reached and end of file is not reached
		Read a word from the input file
		If word length is greater than 1
			Place the word into the array at elements in ascending order
	Sort the array in ascending order using selection sort
	Print sorted array to screen and to output file
	Prompt the user to enter a word to search
	Searches for the word in the array using binary search
	While the user chooses not to quit searching by entering a quit program command
		If word exists in the array
			Return the first instance of the word's position in the array to screen and output file
		If word does not exist in the array
			Return an error message to screen and output file
	Terminate program
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main();

// function prototypes
void selectionSort(string[], int);
int binarySearch(string[], int, string);
void output(ofstream&, string);
string input(ifstream&, ofstream&, string);

const int MAXSIZE = 1024;

int main() {
	string inFilePath, outFilePath;

	cout << "Please enter the entire input file path including name: " << endl;
	cin >> inFilePath;
	cout << "\nPlease enter the entire output file path including name: " << endl;
	cin >> outFilePath;

	ifstream inputFile;
	ofstream outputFile;

	// tests if the output file is able to be opened
	outputFile.open(outFilePath);
	if (!outputFile.is_open()) {
		cout << "Error: Unable to open file" << endl;
		return 1;
	}

	// tests if the input file is able to be opened
	inputFile.open(inFilePath);
	if (!inputFile.is_open()) {
		output(outputFile, "Error: Unable to open file");
		return 2;
	}

	// name block in program output
	cout << "CIS22B" << endl;
	cout << "Lab 1: Sorts and searches an input text file and outputs the results to the screen and to an output text file" << endl;
	cout << "Name: Michelle Maidana\n" << endl;

	string words[MAXSIZE];
	int wordCount = 0;

	while (wordCount != MAXSIZE && !inputFile.eof()) {
		string word;
		inputFile >> word;
		if (word.length() > 1) {
			words[wordCount] = word;
			wordCount++;
		}
	}

	selectionSort(words, wordCount);

	// lists the sorted array to the screen and to the output file
	for (int i = 0; i < wordCount; i++) {
		output(outputFile, words[i] + "\n");
	}

	output(outputFile, "\n");

	while (true) {
		// prompts the user to search for a word in the sorted array
		string wordToSearch = input(inputFile, outputFile, "Enter a word to search for or 'q' to quit: ");
		// program terminates if the quit command q is entered
		if (wordToSearch == "q") {
			break;
		}
		// searches the word in the sorted array using binary search
		int index = binarySearch(words, wordCount, wordToSearch);
		// outputs error message if word is not found in the array
		if (index == -1) {
			output(outputFile, "Word not found!\n");
		}
		// outputs position of first instance of the word in the array to user
		else {
			output(outputFile, "Word " + wordToSearch + " found at position " + to_string(index) + "\n");
		}
	}

	system("pause");
	return 0;
}

/*
Pseudocode:
	Compares the first character of two words
	If both characters are lowercase
		Word 1 is compared to word 2 with ASCII ordering
	If the first character of word 1 is lowercase and the first character of word 2 is uppercase
		Then word 1 is less than word 2
	If word 1 starts with a lowercase letter and word 2 starts with a number
		Then word 1 is less than word 2
	Else
		Word 1 is less than word 2
*/
bool isLessThan(string word1, string word2) {
	int char1 = word1[0];
	int char2 = word2[0];

	if (97 <= char1 && char1 <= 122) { // lowercase 
		if (97 <= char2 && char2 <= 122) {
			return word1 < word2;
		}
		else if (65 <= char2 && char2 <= 90) {
			return true;
		}
		else if (48 <= char2 && char2 <= 57) {
			return true;
		} else {
			return word1 < word2;
		}
	}
	else if (65 <= char1 && char1 <= 90) { // uppercase
		if (97 <= char2 && char2 <= 122) {
			return false;
		}
		else if (65 <= char2 && char2 <= 90) {
			return word1 < word2;
		}
		else if (48 <= char2 && char2 <= 57) {
			return true;
		}
		else {
			return word1 < word2;
		}
	}
	else if (48 <= char1 && char1 <= 57) { // numbers
		if (97 <= char2 && char2 <= 122) {
			return false;
		}
		else if (65 <= char2 && char2 <= 90) {
			return false;
		}
		else if (48 <= char2 && char2 <= 57) {
			return word1 < word2;
		}
		else {
			return word1 < word2;
		}
	}
	else {
		return word1 < word2;
	}
}

/*
Pseudocode: (Selection sort algorithm)
	Compare the first element to other elements in the array
	If there is an element that is smaller than the first element
		Swap them so the first element is now the smallest element in the array
	Else
		Keep the first element the same
	Compare the second element to all the higher elements in the array
	If there is an element that is smaller than the second element
		Swap them so the second element is now the second-smallest element in the array
	Else
		Keep the second element the same
	Continue until the whole array is sorted in ascending order
*/
void selectionSort(string myArray[], int size) {
	int i, j, minIndex;
	int numCount = 0, lowerCount = 0, upperCount = 0;
	string temp;

	for (i = 0; i < size - 1; i++) {
		minIndex = i;

		for (j = i + 1; j < size; j++) {
			if (isLessThan(myArray[j], myArray[minIndex])) {
				minIndex = j;
			}
		}

		temp = myArray[minIndex];
		myArray[minIndex] = myArray[i];
		myArray[i] = temp;
	}
}

/*
Pseudocode: (Binary search algorithm)
	Assign low value to 0
	Assign high value to size of array minus 1
	While word to be searched has not been found
		Find the middle element in the sorted array by adding the low value and high value and dividing by 2
		If the word to be searched is the middle element
			Return the middle element
		If the word to be searched is less than the middle element
			Subtract the middle element by one and assign to high value
		If the word to be searched is more than the middle element
			Add the middle element by one and assign to low value
*/
int binarySearch(string myArray[], int size, string searchKey)
{
	int low = 0;
	int high = size - 1;

	while (low <= high) {
		int midpoint = (low + high) / 2;
		string value = myArray[midpoint];

		if (value == searchKey) {
			return midpoint;
		}
		else if (isLessThan(value, searchKey)) {
			low = midpoint + 1; 
		}
		else {
			high = midpoint - 1;
		}
	}

	return -1;
}

/*
Pseudocode:
	Prints output to screen
	Prints output to output text file
*/
void output(ofstream &outputFile, string output) {
	cout << output;
	outputFile << output;
}

/*
Pseudocode:
	Prompts user to end a word to search
	Validates input
	Outputs user interaction to output file
	Returns the word to be searched or the quit command
*/
string input(ifstream &inputFile, ofstream &outputFile, string question) {
	output(outputFile, question + " ");
	string answer;
	cin >> answer;
	outputFile << answer << endl;
	return answer;
}