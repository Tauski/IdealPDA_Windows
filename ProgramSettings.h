#ifndef PROGRAMSETTINGS_H
#define PROGRAMSETTINGS_H

#include <QtGlobal>

// ALL THE GLOBAL DECLARATIONS

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

///Global QString that holds username of the current user.
extern QString g_username;

///Global QString that holds email of the current user.
extern QString g_userEmail;

///Global QString that holds current location of user.
extern QString g_userLocation;

#endif // PROGRAMSETTINGS_H


