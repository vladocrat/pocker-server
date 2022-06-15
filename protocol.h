#ifndef PROTOCOL_H
#define PROTOCOL_H

namespace Protocol
{
// CL side commands
namespace Client
{
static const int CL_HELLO = 0;
static const int CL_LOGIN = 2;
static const int CL_REGISTER = 4;
static const int CL_BET = 6;
static const int CL_FOLD = 8;
static const int CL_RAISE = 10;
static const int CL_ALLIN = 12;
static const int CL_CALL = 14;
static const int CL_CHECK = 16;
static const int CL_ROOM_CHOICE = 18;
}; // Client

// SV side commands
namespace Server
{
static const int SV_HELLO = 1;
static const int SV_LOGIN = 3;
static const int SV_BET = 5;
static const int SV_FOLD = 7;
static const int CL_RAISE = 9;
static const int CL_ALLIN = 11;
static const int CL_CALL = 13;
static const int CL_CHECK = 15;
static const int CL_ROOM_CHOICE = 17;
}; // Server

// error handling
namespace Errors
{
static const int SV_LOGIN_ERR = 18;
};
}

#endif // PROTOCOL_H
