#ifndef USER_H
#define USER_H

#include "../inc/qdio.h"

bool allowStatMonitor;
string userName;
string pcName;
string password;

bool loggedIn;

void logout();
void login();

#endif
