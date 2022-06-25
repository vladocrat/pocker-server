#include "usercontroller.h"

#include <algorithm>

#include "userconnection.h"
#include "../common/protocol.h"

void UserController::addUser(User* user)
{
    m_users.append(user);
}

//bool UserController::findUser(const User& user)
//{
//    return  m_users.indexOf(user) != -1;
//}

bool UserController::findUserByName(const QString& name)
{
    return std::find_if(m_users.begin(), m_users.end(), [&name](User* user)
    {
        return name == user->name();
    }) != m_users.end();
}

void UserController::onRoomChosen(int roomId)
{

}

void UserController::onRoomExited()
{

}

