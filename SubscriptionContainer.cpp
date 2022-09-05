#include "SubscriptionContainer.h"
#include "MessageContainer.h"
#include "MessageInfo.h"
#include <iostream>

uint64_t SubscriptionContainer::_LastCreatedHandle=0;

SubscriptionContainer::SubscriptionContainer():
                        _messageQueue(std::make_unique<MessageContainer>()){}

uint64_t 
SubscriptionContainer::CreateHandle()
{
    ++_LastCreatedHandle;
    _subscriberList[_LastCreatedHandle] = _messageQueue->GetTail();
    return _LastCreatedHandle;
}

const std::string
SubscriptionContainer::GetNextMessage(uint64_t handle)
{
    const MessageInfo* pNextMessage = nullptr;
    const auto &message = _messageQueue->GetMessage(_subscriberList[handle], pNextMessage);
    if(pNextMessage == nullptr) 
        return "";
    _subscriberList[handle] = pNextMessage;
    return message;
}

bool
SubscriptionContainer::AddMessage(const std::string& message)
{
    if(_subscriberList.size() == 0)
        return true;
    
    _messageQueue->AddMessage(message, _subscriberList.size());
    return true;
}

  uint64_t
  SubscriptionContainer::GetSubscriptionCount()
  {
    return _subscriberList.size();
  }