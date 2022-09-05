#pragma once
#include <string>

struct MessageInfo
{
    public:
    MessageInfo(const std::string& message, int handlesMessageToBeDispatched):
                _message(message),
                _handlesMessageToBeDispatched(handlesMessageToBeDispatched){}

    const std::string GetMessageForSubscriber()
    {
        --_handlesMessageToBeDispatched;
        return _message;
    }

    std::string _message;
    uint64_t _handlesMessageToBeDispatched;
    MessageInfo* _pNext = nullptr;
    MessageInfo* _pPrev = nullptr;
};

