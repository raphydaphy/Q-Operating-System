#ifndef CAT_H
#define CAT_H

#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"
#include "../inc/kernelFunctions.h"
#include "../inc/fs.h"

void cat(fs_node_t*);
bool findInDictionary(fs_node_t*,int,string);

#endif
