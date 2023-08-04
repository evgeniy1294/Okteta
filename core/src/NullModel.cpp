#include "Okteta/NullModel.hpp"

namespace Okteta {

NullModel::NullModel() = default;
NullModel::~NullModel() = default;

Byte NullModel::byte(Address offset) const { Q_UNUSED(offset) return 0; }
Size NullModel::size() const { return 0; }
bool NullModel::isModified() const { return false; }
Size NullModel::replace(const AddressRange& removeSection, const Byte* insertData, int insertLength)
{
    Q_UNUSED(removeSection) Q_UNUSED(insertData) Q_UNUSED(insertLength)
    return 0;
}
bool NullModel::swap(Address firstStart, const AddressRange& secondRange)
{
    Q_UNUSED(firstStart) Q_UNUSED(secondRange)
    return false;
}
Size NullModel::fill(Byte fillByte, Address offset, Size fillLength)
{
    Q_UNUSED(fillByte) Q_UNUSED(offset) Q_UNUSED(fillLength)
    return 0;
}
void NullModel::setByte(Address offset, Byte byte)
{
    Q_UNUSED(offset) Q_UNUSED(byte)
}
void NullModel::setModified(bool modified)
{
    Q_UNUSED(modified)
}

} // namespace Okteta
