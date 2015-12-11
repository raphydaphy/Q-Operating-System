#ifndef USER_H
#define USER_H

#include "../inc/stringUtils.h"
#include "../inc/consoleUI.h"

bool allowStatMonitor;
string userName;
string pcName;
string password;

bool loggedIn;

void logout();
void login();

#endif
