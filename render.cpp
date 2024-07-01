#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;


bool lastCharSpecial(char* word) {
    char c = word[strlen(word) - 1];
    return (c == '.' || c == ':' || c == '!' || c == '?');
}

//return new capacity
void dealWithWordBeg(int capacity, int lineLength, char* lastWord, ostream& outf) {
    if (capacity == lineLength) {
        return;
    }
    if (lastCharSpecial(lastWord)) {
        outf << "  ";
    }
    else {
        outf << " ";
    }
}

//return -1 if not found
int findHypenPosFromBack(char* word, int start) {
    while (start >= 0) {
        if (word[start] == '-') {
            return start;
        }
        else {
            start--;
        }
    }
    return start;
}

int gotAWord(char* word, char* nextWord, char* lastWord, int capacity, int lineLength, ostream& outf, int* wordPortionBreak) {
    if (capacity <= 0) {
        outf << "\n";
        capacity = lineLength;
    }
    int wlen = strlen(word);
    if (lastCharSpecial(word)) {
        wlen = strlen(word);
    }
    if (wlen <= capacity) {
        dealWithWordBeg(capacity, lineLength, lastWord, outf);
        outf << word;
        capacity -= wlen;
        if (lastCharSpecial(word)) {
            capacity -= 2;
        }
        else {
            capacity -= 1;
        }
    }
    else {//cannot fit current line
        char w1[180] = {};
        char w2[180] = {};
        int hypenPos = findHypenPosFromBack(word, capacity - 1);
        if (hypenPos >= 0) {
            //separate to two words
            memcpy(w1, word, hypenPos + 1);
            w1[hypenPos + 1] = 0;
            memcpy(w2, word + hypenPos + 1, wlen - hypenPos - 1);
            w2[wlen - hypenPos - 1] = 0;
            capacity = gotAWord(w1, nextWord, lastWord, capacity, lineLength, outf, wordPortionBreak);
            capacity = gotAWord(w2, nextWord, lastWord, capacity, lineLength, outf, wordPortionBreak);
        }
        else {
            if (capacity == lineLength) {//new line need to break
                memcpy(w1, word, capacity);
                w1[capacity] = 0;
                memcpy(w2, word + capacity, wlen - capacity);
                w2[wlen - capacity] = 0;
                *wordPortionBreak = 1;
                capacity = gotAWord(w1, nextWord, lastWord, capacity, lineLength, outf, wordPortionBreak);
                capacity = gotAWord(w2, nextWord, lastWord, capacity, lineLength, outf, wordPortionBreak);
            }
            else {
                outf << "\n";
                capacity = gotAWord(word, nextWord, lastWord, lineLength, lineLength, outf, wordPortionBreak);
            }
        }
    }
    return capacity;
}

int render(int lineLength, istream& inf, ostream& outf) {
    if (lineLength < 1) {
        return 2;
    }
    if (inf.peek() == EOF) {
        return 0;
    }
    char word[180] = {};
    char nextWord[180] = {};
    char lastWord[180] = {};
    int capacity = lineLength;
    bool newParagraph = true;
    int wordPortionBreak = 0;

    inf >> ws >> word;
    if (word[0] == '\0') {return 0;}
    while (!inf.eof()) {
        inf >> ws >> nextWord;
        if (strcmp(word, "@P@") == 0) {
            if (!newParagraph) {
                outf << '\n' << '\n';
                capacity = lineLength;
            }
            newParagraph = true;
            strcpy(word, nextWord);
            continue;
        }
        newParagraph = false;
       
        capacity = gotAWord(word, nextWord, lastWord, capacity, lineLength, outf, &wordPortionBreak);
        strcpy(lastWord, word);
        strcpy(word, nextWord);
    }

    outf << "\n";
    return wordPortionBreak;
}



