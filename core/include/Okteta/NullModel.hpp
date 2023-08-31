#ifndef NULL_MODEL_HPP
#define NULL_MODEL_HPP

#include <Okteta/ByteArrayModel.hpp>

namespace Okteta {

class OKTETACORE_EXPORT NullModel : public AbstractByteArrayModel
{
    Q_OBJECT

public:
    NullModel();
    ~NullModel() override;

public: // data access API
    Byte byte(Address offset) const override;
    Size size() const override;

public: // state read API
    bool isModified() const override;

public: // modification API
    Size replace(const AddressRange& removeSection, const Byte* insertData, int insertLength) override;
    bool swap(Address firstStart, const AddressRange& secondRange) override;
    Size fill(Byte fillByte, Address offset = 0, Size fillLength = -1) override;
    void setByte(Address offset, Byte byte) override;
    void setModified(bool modified) override;
};

} // namespace Okteta

#endif
