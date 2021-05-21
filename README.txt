Counts the occurances of each unique word. Makes all words lowercase and removes punctuation.
Code by Geir Anderson for word occurance counter
CMSC 318 / GNED 495
Lowercase method based on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case

How it works:
A text file is read in, the file is specified on the command line.
A map is made using, where the key value is a string (a word from the file) and an associated int value (the count)
Each word is stripped of punctuation and made lowercase before being counted (this improves counter accuracy)
Then the map is read to the terminal.

Compile:

compile jan22.cpp -o jan22hw

Test:

./jan22hw test1.txt
./jan22hw test2.txt
./jan22hw test3.txt
./jan22hw README.txt
