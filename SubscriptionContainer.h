#pragma once
/* The container holds message queue and handles next message pointer*/

#include<unordered_map>
#include<memory>

struct MessageInfo;
class MessageContainer;

class SubscriptionContainer
{
    private:
    std::unordered_map<uint64_t, const MessageInfo*> _subscriberList; //subscriptions & their next message pointer
    std::unique_ptr<MessageContainer> _messageQueue; //container qhich holds messages
    static uint64_t _LastCreatedHandle;

    public:
    SubscriptionContainer();
    /* Creates new handle and return the handle*/
    uint64_t CreateHandle();

    /*Gets Message based on the Handle*/
    const std::string GetNextMessage(uint64_t handle);

    /*Adds Message to the message queue*/
    bool AddMessage(const std::string& message);

    /*Gets Subscription count*/
    uint64_t GetSubscriptionCount();
};