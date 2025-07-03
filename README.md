This C program analyzes the frequency of alphabetic characters in a text file and outputs the percentage of each letter's occurrence, along with a summary of non-alphabetic characters.

What It Does
- Input: A plain text file containing words and symbols.
- Processing:
- Reads the file line by line.
- Counts how many times each alphabetic character (A–Z, a–z) appears.
- Tracks all other characters (digits, punctuation, symbols, etc.) under a general "other" category.
- Stores letters in a sorted singly linked list by character.
- Output: A text file listing each letter and its percentage of the total characters processed, followed by the percentage of non-letter characters.

Each line in the output file looks like:
a - 7.143%
b - 3.571%
...
other - 21.429%


Usage:
./program input.txt output.txt


