#include "Okteta/GlobalConfigStorage.hpp"

Okteta::GlobalConfigStorage& Okteta::GlobalConfigStorage::Instance()
{
    static GlobalConfigStorage m_instance;
    return m_instance;
}

void Okteta::GlobalConfigStorage::config(QJsonObject& config) const
{
    config = m_config;
}

void Okteta::GlobalConfigStorage::setConfig(const QJsonObject& config)
{
    if (config != m_config) {
        m_config = config;
        emit sConfigChanged();
    }
}
