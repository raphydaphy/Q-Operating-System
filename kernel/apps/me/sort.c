#include "sort.h"

// This enum holds all the main categories of words that can be returned from this function
//typedef enum {UNKNOWN,NOUN,VERB,ADJECTIVE,ADVERB,INTERJECTION,PREOPSITION,CONJUNCTION,PRONOUN} words;

char *words[] = {
    "UNKNOWN",
    "NOUN",
    "VERB",
    "ADJETIVE",
    "INTERJECTION",
    "PREPOSITION",
    "CONJUNCTION",
    "PRONOUN"
};

// These enum types hold the sub-categories for each main type of word
//typedef enum {ACT,ANIMAL,ARTIFACT,ATTRIBUTE,BODY,COGNITION,COMMUNICATION,EVENT,FEELING,FOOD,GROUP,LOCATION,MOTIVE,OBJECT,PERSON,QUANTITY,RELATION,SHAPE,STATE,SUBSTANCE,TIME,TOPS} noun;
//typedef enum {BODY,CHANGE,COGNITION,COMMUNICATION,COMPETITION,CONSUMPTION,CONTACT,CREATION,EMOTION,FRAMESTEXT,MOTION,PERCEPTION,POSSESSION,SOCIAL,STATIVE,WEATHER} verb;

string sort(char* word)
{

    // turn the word into uppercase for easier sorting
    word = toUpper(word);

    if (findInDictionary("me/noun/act.txt",word))
    {
        print(" Noun ",0x0B);
        print(" Act ",0x0C);
        return words[1];
    }

    if (findInDictionary("me/noun/animal.txt",word))
    {
        print(" Noun ",0x0B);
        print(" Animal ",0x0C);
        return words[1];
    }

    if (findInDictionary("me/noun/artifact.txt",word))
    {
        print(" Noun ",0x0B);
        print(" Artifact ",0x0C);
        return words[1];
    }

    if (findInDictionary("me/verb/verb.txt",word))
    {
        print(" Verb ",0x0B);
        return words[2];
    }


    return words[0];
}
