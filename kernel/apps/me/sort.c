#include "sort.h"

// This enum holds all the main categories of words that can be returned from this function
//typedef enum {UNKNOWN,NOUN,VERB,ADJECTIVE,ADVERB,INTERJECTION,PREOPSITION,CONJUNCTION,PRONOUN} words;

char *words[10][50] = {
    {   // Unknown Words
        "UNKNOWN UNKNOWN"
    },
    {   // Nouns
        "NOUN UNKNOWN",
        "NOUN ACT",
        "NOUN ANIMAL",
        "NOUN ARTIFACT",
        "NOUN ATTRIBUTE",
        "NOUN BODY",
        "NOUN COGNITION",
        "NOUN COMMUNICATION",
        "NOUN EVENT",
        "NOUN FEELING",
        "NOUN FOOD",
        "NOUN GROUP",
        "NOUN LOCATION",
        "NOUN MOTIVE",
        "NOUN OBJECT",
        "NOUN PERSON",
        "NOUN QUANTITY",
        "NOUN RELATION",
        "NOUN SHAPE",
        "NOUN STATE",
        "NOUN SUBSTANCE",
        "NOUN TOPS",
    },
    {   // Verbs
        "VERB UNKNOWN",
        "VERB BODY",
        "VERB CHANGE",
        "VERB COGNITION",
        "VERB COMMUNICATION",
        "VERB COMPETITION",
        "VERB CONSUMPTION",
        "VERB CONTACT",
        "VERB CREATION",
        "VERB EMOTION",
        "VERB FRAMESTEXT",
        "VERB MOTION",
        "VERB PERCEPTION",
        "VERB POSSESSION",
        "VERB SOCIAL",
        "VERB STATIVE",
        "VERB WEATHER",
    },
    {   // Adjectives
        "ADJECTIVE UNKNOWN"
    },
    {   // Interjections
        "INTERJECTION UNKNOWN"
    },
    {   // Prepositions
        "PREPOSITION UNKNOWN"
    },
    {   // Conjunctions
        "CONJUNCTION UNKNOWN"
    },
    {   // Pronouns
        "PRONOUN UNKNOWN"
    }
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
        return words[1][1];
    }

    if (findInDictionary("me/noun/animal.txt",word))
    {
        return words[1][2];
    }

    if (findInDictionary("me/noun/artifact.txt",word))
    {
        return words[1][3];
    }

    if (findInDictionary("me/noun/attribute.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/body.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/cognition.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/communication.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/event.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/feeling.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/food.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/group.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/location.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/motive.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/object.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/person.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/quantity.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/relation.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/shape.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/state.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/substance.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/noun/tops.txt",word))
    {
        return words[1][0];
    }

    if (findInDictionary("me/verb/verb.txt",word))
    {
        return words[2][0];
    }


    return words[0][0];
}
