#ifndef REGISTERDATA_H
#define REGISTERDATA_H

#include "LoginData.h"

struct RegisterData : public LoginData
{
    QString email;
};

#endif // REGISTERDATA_H
