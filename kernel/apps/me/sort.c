#include "sort.h"

double sort(char* word)
{
    // Here are the basic category numbers, for more information look on the Q OS Wiki for Me
    // Link: https://github.com/raphydaphy/Q-Operating-System/wiki/Me

    // 0 = unknown                      The kind of this word is unknown or unspecified
    // 1 = noun                         A noun is a person, place, thing, quality or act word
    // 2 = verb                         Verbs are action/existence words that say what a noun does
    // 3 = adjective                    An adjective is a word that describes a noun
    // 4 = Adverb                       An adverb descries a verb, adjective or adverb. It often ends in 'ly'
    // 5 = Interjection                 An interjection is an outcry/ sudden utterance. Usally the start of a sentence
    // 6 = Preposition                  A preposition describes the relationship between a noun and another noun (can also be verb/adverb)
    // 7 = Conjunction                  A conjunction is a word that joins together multiple thoughts
    // 8 = Pronoun                      A pronoun replaces a noun/noun phase that is understood from context

    double type = 0;

    // turn the word into uppercase for easier sorting
    word = toUpper(word);

    if (findInDictionary("me/noun/act.txt",word))
    {
        print(" Noun ",0x0B);
        print(" Act ",0x0C);
        type = 1.1;
        return 1.1;
    }

    if (findInDictionary("me/noun/animal.txt",word))
    {
        print(" Noun ",0x0B);
        print(" Animal ",0x0C);
        type = 1.2;
        return 1.2;
    }

    if (findInDictionary("me/noun/artifact.txt",word))
    {
        print(" Noun ",0x0B);
        print(" Artifact ",0x0C);
        type = 1.3;
        return 1.3;
    }

    if (findInDictionary("me/verb/verb.txt",word))
    {
        print(" Verb ",0x0B);
        type = 2.0;
        return 2.0;
    }


    return type;
}
