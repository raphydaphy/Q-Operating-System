#include "sort.h"

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

string sort(char* word)
{
    // turn the word into uppercase for easier sorting
    word = toUpper(word);

    // try to find the sub-category of the word assuming it is a noun
    if (findInDictionary("me/noun/act.txt",word))               { return words[1][1];   }
    if (findInDictionary("me/noun/animal.txt",word))            { return words[1][2];   }
    if (findInDictionary("me/noun/artifact.txt",word))          { return words[1][3];   }
    if (findInDictionary("me/noun/attribute.txt",word))         { return words[1][4];   }
    if (findInDictionary("me/noun/body.txt",word))              { return words[1][5];   }
    if (findInDictionary("me/noun/cognition.txt",word))         { return words[1][6];   }
    if (findInDictionary("me/noun/communication.txt",word))     { return words[1][7];   }
    if (findInDictionary("me/noun/event.txt",word))             { return words[1][8];   }
    if (findInDictionary("me/noun/feeling.txt",word))           { return words[1][9];   }
    if (findInDictionary("me/noun/food.txt",word))              { return words[1][10];  }
    if (findInDictionary("me/noun/group.txt",word))             { return words[1][11];  }
    if (findInDictionary("me/noun/location.txt",word))          { return words[1][12];  }
    if (findInDictionary("me/noun/motive.txt",word))            { return words[1][13];  }
    if (findInDictionary("me/noun/object.txt",word))            { return words[1][14];  }
    if (findInDictionary("me/noun/person.txt",word))            { return words[1][15];  }
    if (findInDictionary("me/noun/quantity.txt",word))          { return words[1][16];  }
    if (findInDictionary("me/noun/relation.txt",word))          { return words[1][17];  }
    if (findInDictionary("me/noun/shape.txt",word))             { return words[1][18];  }
    if (findInDictionary("me/noun/state.txt",word))             { return words[1][19];  }
    if (findInDictionary("me/noun/substance.txt",word))         { return words[1][20];  }
    if (findInDictionary("me/noun/tops.txt",word))              { return words[1][21];  }

    // failing to find the word in any noun sub-categories, look in the main nouns list
    if (findInDictionary("me/noun/noun.txt",word))              { return words[1][0];   }

    // try to find the sub-category of the word if we assume it to be a verb
    if (findInDictionary("me/verb/body.txt",word))              { return words[2][1];   }
    if (findInDictionary("me/verb/change.txt",word))            { return words[2][2];   }
    if (findInDictionary("me/verb/cognition.txt",word))         { return words[2][3];   }
    if (findInDictionary("me/verb/communication.txt",word))     { return words[2][4];   }
    if (findInDictionary("me/verb/competition.txt",word))       { return words[2][5];   }
    if (findInDictionary("me/verb/consumption.txt",word))       { return words[2][6];   }
    if (findInDictionary("me/verb/contact.txt",word))           { return words[2][7];   }
    if (findInDictionary("me/verb/creation.txt",word))          { return words[2][8];   }
    if (findInDictionary("me/verb/emotion.txt",word))           { return words[2][9];   }
    if (findInDictionary("me/verb/framestext.txt",word))        { return words[2][10];  }
    if (findInDictionary("me/verb/motion.txt",word))            { return words[2][11];  }
    if (findInDictionary("me/verb/perception.txt",word))        { return words[2][12];  }
    if (findInDictionary("me/verb/possession.txt",word))        { return words[2][13];  }
    if (findInDictionary("me/verb/social.txt",word))            { return words[2][14];  }
    if (findInDictionary("me/verb/stative.txt",word))           { return words[2][15];  }
    if (findInDictionary("me/verb/weather.txt",word))           { return words[2][16];  }

    // failing to find the word in the verb sub-categories, look in the main verbs list
    if (findInDictionary("me/verb/verb.txt",word))              { return words[2][0];   }


    return words[0][0];
}
