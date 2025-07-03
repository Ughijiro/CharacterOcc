This program scans a binary file full of 32‑bit unsigned integers and builds a frequency table:

Input format – raw little‑endian unsigned int values, packed one after another.

Processing – it walks the file once, storing each distinct number in a sorted singly linked list.

Output – for every distinct value, it prints a line to the specified text file:

<number> : <occurrences> : <percentage>%
Percentages are shown with four decimals, and the list is in ascending numeric order.

Usage:
./program input.bin output.txt

