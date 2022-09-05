#include "MessageQueueManager.h"
#include <iostream>

bool
MessageQueueManager::CreateMessageQueue(const std::string& in_queueName)
{
    auto pExisitingQueue = _messageQueue.find(in_queueName);
    if(pExisitingQueue == _messageQueue.end())
    {
        _messageQueue[in_queueName];
        return true;
    }

    std::cerr << __FUNCTION__ << " Queue " << in_queueName << "already exists." << std::endl;
    return false;
}

bool
MessageQueueManager::PostMessage(const std::string& in_queueName, const std::string& in_message)
{
    if(in_message.empty())
    {
        std::cerr << __FUNCTION__ << " failed to add empty message in queue " << in_queueName << "." << std::endl;
        return false;
    }

    auto pSubscriptionQueue = _messageQueue.find(in_queueName);
    if(pSubscriptionQueue == _messageQueue.end())
    {
        std::cerr << __FUNCTION__ << " Queue " << in_queueName << " not found." << std::endl;
        return false;       
    }

    if(!pSubscriptionQueue->second.AddMessage(in_message))
    {
        std::cerr << __FUNCTION__ << " failed to add message in queue " << in_queueName << "." << std::endl;
        return false;
    }
    return true;
}

bool
MessageQueueManager::CreateSubscription(const std::string& in_queueName, SubscriptionHandle& out_handle)
{
    out_handle = 0;
    auto pSubscriptionQueue = _messageQueue.find(in_queueName);
    if(pSubscriptionQueue == _messageQueue.end())
    {
        std::cerr << __FUNCTION__ << " Queue " << in_queueName << " not found." << std::endl;
        return false;       
    }
    out_handle = pSubscriptionQueue->second.CreateHandle();
    _handleToQueueName[out_handle] = in_queueName;
    return out_handle;
}

bool
MessageQueueManager::GetSubscriptionCount(const std::string& in_queueName, int& out_queueSubscriberCount)
{
    auto pSubscriptionQueue = _messageQueue.find(in_queueName);
    if(pSubscriptionQueue == _messageQueue.end())
    {
        std::cerr << __FUNCTION__ << " Queue " << in_queueName << " not found." << std::endl;
        return false;       
    }
    out_queueSubscriberCount = pSubscriptionQueue->second.GetSubscriptionCount();
    return true;
}

bool
MessageQueueManager::GetNextMessage(SubscriptionHandle in_handle, std::string& out_message)
{
    auto pHandleToQueue = _handleToQueueName.find(in_handle);
    if(pHandleToQueue == _handleToQueueName.end())
    {
        std::cerr << __FUNCTION__ << " Could not fine queue for handle " << in_handle << "." << std::endl;
        return false;       
    }

    auto pSubscriptionQueue = _messageQueue.find(pHandleToQueue->second);
    if(pSubscriptionQueue == _messageQueue.end())
    {
        std::cerr << __FUNCTION__ << " Queue " << pHandleToQueue->second << " not found." << std::endl;
        return false;       
    }

    out_message = pSubscriptionQueue->second.GetNextMessage(in_handle);
    return true;
}
