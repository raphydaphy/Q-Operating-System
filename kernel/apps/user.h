#ifndef USER_H
#define USER_H

#include "../inc/qdio.h"

bool useQDC;

string userName;
string pcName;

string password;
string email;

bool loggedIn;

void logout();
void login();

#endif
