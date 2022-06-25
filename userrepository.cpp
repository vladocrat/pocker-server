#include "userrepository.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QByteArray>

UserRepository::UserRepository()
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(DATABASE_HOSTNAME);
    m_db.setPort(5432);
    m_db.setDatabaseName(DATABASE_NAME);
    m_db.setUserName(DATABASE_USERNAME);
    m_db.setPassword(DATABASE_PASSWORD);

    if (open()) {
        qDebug() << "connection with database established";
    }
}

UserRepository::~UserRepository()
{
    m_db.close();
}

bool UserRepository::removeUser(const User&)
{
    //TODO
    return false;
}

bool UserRepository::registerUser(const RegisterData& data)
{
    bool ok = true;

    if (userExists(data, &ok)) {
        return false;
    }

    if (!ok) {
        return false;
    }

    auto passwordHash = QCryptographicHash::hash(data.password.toUtf8(),
                                                 QCryptographicHash::Algorithm::Sha256);

    QSqlQuery query;
    query.prepare("INSERT INTO \"Users\" (name, password, email) VALUES(?, ?, ?)");
    query.bindValue(0, data.login);
    query.bindValue(1, passwordHash);
    query.bindValue(2, data.email);

    if (!m_db.isOpen()) {
        qDebug() << "no connection to db";
        return false;
    }

    if (!executeQuery(query)) {
        return false;
    }

    return true;
}

bool UserRepository::login(const LoginData& data, Profile& profile)
{   
    if (!userExists(data)) {
        qDebug() << "user doesn't exist";
        return false;
    }

    auto passwordHash = QCryptographicHash::hash(data.password.toUtf8(),
                                                 QCryptographicHash::Algorithm::Sha256);
    QSqlQuery query;
    query.prepare("SELECT name, pfp, email FROM \"Users\" WHERE name=:uname AND password=:upassword");
    query.bindValue(":uname", data.login);
    query.bindValue(":upassword", passwordHash);

    if (!executeQuery(query)) {
        return false;
    }

    if (query.size() == 0) {
        return false;
    }

    QString name;
    QString email;
    QString pfpLink;

    auto usernameIx = query.record().indexOf("name");
    auto emailIx = query.record().indexOf("email");
    auto pfpLinkIx = query.record().indexOf("pfp");

    while (query.next()) {
        name = query.value(usernameIx).toString();
        email = query.value(emailIx).toString();
        pfpLink = query.value(pfpLinkIx).toString();
    }


    profile.name = name;
    profile.email = email;
    profile.pfpLink = pfpLink;

    return true;
}

bool UserRepository::userExists(const RegisterData& userData, bool* ok)
{
    //TODO make one query
    if (!m_db.isOpen()) {

        if (!ok) {
            return false;
        }

        *ok = false;

        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT name FROM \"Users\" WHERE name=:uname");
    query.bindValue(":uname", userData.login, QSql::Out);

    if (!executeQuery(query)) {

        if (!ok) {
            return false;
        }

        *ok = false;

        return false;
    }

    if (query.size() > 0) {
        qDebug() << "user already exists";

        return true;
    }

    query.prepare("SELECT email FROM \"Users\" WHERE email=:uemail");
    query.bindValue(":uemail", userData.email, QSql::Out);

    if (!executeQuery(query)) {

        if (!ok) {
            return false;
        }

        *ok = false;

        return false;
    }

    if (query.size() > 0) {
        qDebug() << "user already exists";

        return true;
    }

    return false;
}

bool UserRepository::userExists(const LoginData& userData,  bool* ok)
{
    if (!m_db.isOpen()) {
        return true;
    }

    QSqlQuery query;
    query.prepare("SELECT name FROM \"Users\" WHERE name=:uname");
    query.bindValue(":uname", userData.login, QSql::Out);

    if (!executeQuery(query)) {
        return true;
    }

    if (query.size() > 0) {
        qDebug() << "User exsists";

        return true;
    }

    return false;
}

bool UserRepository::findUserByName(const QString& name, User& user)
{
    //add ok param
    if (!m_db.isOpen()) {
        return false;
    }

    //not tested;
    QSqlQuery query;
    query.prepare("SELECT * FROM \"Users\" WHERE name=" + name);

    auto usernameIx = query.record().indexOf("name");
    auto emailIx = query.record().indexOf("email");

    if (!executeQuery(query)) {
        return false;
    }

    QString username;
    QString email;

    while (query.next()) {
        username = query.value(usernameIx).toString();
        email = query.value(emailIx).toString();
    }

    Profile profile;
    profile.name = username;
    profile.email = email;
    user.setProfile(profile);

    return true;
}

bool UserRepository::findUserByEmail(const QString& email, User& user)
{
    //add ok param

    if (!m_db.isOpen()) {
        return false;
    }

    //not tested;
    QSqlQuery query;
    query.prepare("SELECT * FROM \"Users\" WHERE email=" + email);

    auto usernameIx = query.record().indexOf("name");
    auto emailIx = query.record().indexOf("email");

    if (!executeQuery(query)) {
        return false;
    }

    QString username;
    QString userEmail;

    while (query.next()) {
        username = query.value(usernameIx).toString();
        userEmail = query.value(emailIx).toString();
    }

    Profile profile;
    profile.name = username;
    profile.email = email;
    user.setProfile(profile);

    return true;
}

bool UserRepository::executeQuery(QSqlQuery& query)
{
    if (!query.exec()) {
        qDebug() << m_db.lastError();
        qDebug() << "last query: " + query.executedQuery();
        return false;
    }

    return true;
}

bool UserRepository::open()
{
    if (!m_db.isOpen()) {
        if (m_db.open()) {
            return true;
        }
        qDebug() << m_db.lastError();
        return false;
    }

    return true;
}

