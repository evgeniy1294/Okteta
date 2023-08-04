#ifndef GLOBALCONFIGSTORAGE_HPP
#define GLOBALCONFIGSTORAGE_HPP

#include <QObject>
#include <QJsonObject>

namespace Okteta
{

class GlobalConfigStorage final: public QObject
{
    Q_OBJECT

public:
    static GlobalConfigStorage& Instance();

    void config(QJsonObject& config) const;
    void setConfig(const QJsonObject& config);

Q_SIGNALS:
    void sConfigChanged();

private:
    GlobalConfigStorage(QObject* parent = nullptr): QObject(parent), m_config() {  }
   ~GlobalConfigStorage() = default;

    QJsonObject m_config;
};

} // namespace Okteta


#endif // GLOBALCONFIGSTORAGE_HPP
