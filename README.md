# OOPS-OEP
# A spell check program implemented in C++.

INPUT: A plain-text file.
OUTPUT: The list of incorrectly spelled words in the file along with proper alternatives.

Makes use of the Levenshtein Distance formula to calculate edit distance for a word with respect to other words from a dictionary. Appropriate words are suggested as alternatives to incorrect words.
It can be found here https://en.wikipedia.org/wiki/Levenshtein_distance.

The dictionary in use has been taken from Ubuntu's usr/share/dict/american-english text file.
