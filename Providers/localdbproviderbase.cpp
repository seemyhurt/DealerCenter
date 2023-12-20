#include "localdbproviderbase.h"
#include <QFile>

namespace DatabaseCommon {

QString localDBStatusToStr(LocalDBStatus status)
{
    const quint32 errCode = static_cast<quint32>(status);
    QString errStr = "LDBERR " + QString::number(errCode) + ": ";
    switch(status)
    {
    case LocalDBStatus::Unknown:            errStr += "Unknown error";                  break;
    case LocalDBStatus::Connected:          errStr += "Database connected";             break;
    case LocalDBStatus::FailedConnection:   errStr += "Failed to connect to database";  break;
    case LocalDBStatus::Unconnected:        errStr += "Database not connected";         break;
    default:                                errStr += "Error not documented";           break;
    }
    return errStr;
}

LocalDBProviderBase::LocalDBProviderBase(QObject* parent) :
    IProvider{parent}
{
    qRegisterMetaType<DatabaseCommon::LocalDBStatus>("DatabaseCommon::LocalDBStatus");
}

LocalDBProviderBase::~LocalDBProviderBase()
{
    _db = QSqlDatabase();

    QSqlDatabase::removeDatabase(_connection);
}

void LocalDBProviderBase::setDatabaseName(const QString& dbname, const QString& path)
{
    _name = path + dbname;
    updateDatabases();
}

LocalDBStatus LocalDBProviderBase::status() const
{
    return _status;
}

void LocalDBProviderBase::setContext(const QString& table,
                                     const QStringList &columns,
                                     const QString& dbFilename,
                                     const QString& dbFilepath,
                                     const QString& connectionName)
{
    QSqlDatabase::removeDatabase(_connection);

    _table = table;
    _connection = connectionName;
    _columns = columns;

    setDatabaseName(dbFilename, dbFilepath);
}

void LocalDBProviderBase::updateDatabases()
{
    QFile file(_name);

    file.exists() ? _status = readDataFromTable()
                  : _status = createNewTable();

    emit dbConnectionChanged(_status);
}

LocalDBStatus LocalDBProviderBase::createNewTable()
{
    _db = QSqlDatabase::addDatabase("QSQLITE", _connection);
    _db.setDatabaseName(_name);
    if (_db.open())
    {
        // construct columns
        QString columnInfos = "";
        for (const auto &p : qAsConst(_columns))
        {
            columnInfos += ',' + p;
            if (p == "id")
                columnInfos += " INTEGER PRIMARY KEY AUTOINCREMENT";
        }
        columnInfos[0] = '(';
        columnInfos.push_back(')');

        const auto query = _db.exec("CREATE TABLE IF NOT EXISTS " + _table + ' ' + columnInfos);
        if (query.lastError().type() == QSqlError::ErrorType::NoError)
            return LocalDBStatus::Connected;
    }
    return LocalDBStatus::FailedConnection;
}

LocalDBStatus LocalDBProviderBase::readDataFromTable()
{
    _db = QSqlDatabase::addDatabase("QSQLITE", _connection);
    _db.setDatabaseName(_name);
    if (_db.open())
    {
        QSqlQuery query{_db};

        query.exec("SELECT * FROM " + _table);
        const auto record = query.record();

        const bool validTable = record.count() == _columns.size() && record.contains("id");
        return validTable ? LocalDBStatus::Connected : LocalDBStatus::FailedConnection;
    }
    else
        return LocalDBStatus::FailedConnection;
}

QSqlError LocalDBProviderBase::addElement(const QVariantMap& values)
{
    // prepare query str
    QString placeholderNames = "";
    QString columnFields = "";
    if (values.size() != 0)
    {
        for (auto p = values.cbegin(); p != values.cend(); ++p)
        {
            placeholderNames += ",?";
            columnFields += ',' + p.key();
        }
        columnFields[0] = ' ';
        placeholderNames[0] = ' ';
    }

    QSqlQuery query{_db};
    query.prepare("INSERT INTO " + _table + " (" + columnFields + ") " +
                  " VALUES (" + placeholderNames + ')');
    for (const auto& value : values)
        query.addBindValue(value);

    query.exec();
    return query.lastError();
}

QSqlError LocalDBProviderBase::removeElement(quint64 id) const
{
    QSqlQuery query{_db};
    query.prepare("DELETE FROM " + _table + " WHERE id = \'" + QString::number(id) + '\'');

    query.exec();
    return query.lastError();
}

QSqlError LocalDBProviderBase::modifyElement(quint64 id, const QVariantMap& values) const
{
    // prepare query str
    QString placeholderNames = "";
    QString columnFields = "";
    if (values.size() != 0)
    {
        for (auto p = values.cbegin(); p != values.cend(); ++p)
        {
            placeholderNames += ",?";
            columnFields += ',' + p.key();
        }
        columnFields[0] = ' ';
        placeholderNames[0] = ' ';
    }

    QSqlQuery query{_db};
    query.prepare("UPDATE " + _table + " SET (" + columnFields + ") = (" +
                  placeholderNames + ") WHERE id = " + QString::number(id));
    for (const auto& value : values)
        query.addBindValue(value);

    query.exec();
    return query.lastError();
}

}
