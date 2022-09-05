#pragma once
#include "IMessageQueueManager.h"
#include "SubscriptionContainer.h"
#include "MessageContainer.h"
#include <unordered_map>

class MessageQueueManager : public IMessageQueueManager
{
public:
	virtual ~MessageQueueManager() noexcept override{}

	virtual bool CreateMessageQueue(const std::string& in_queueName) final;
	virtual bool PostMessage(const std::string& in_queueName, const std::string& in_message) final;
	virtual bool CreateSubscription(const std::string& in_queueName, SubscriptionHandle& out_handle) final;
	virtual bool GetSubscriptionCount(const std::string& in_queueName, int& out_queueSubscriberCount) final;
	virtual bool GetNextMessage(SubscriptionHandle in_handle, std::string& out_message) final;
private:
    std::unordered_map<std::string, SubscriptionContainer> _messageQueue; //<queueName,Subscription>
    std::unordered_map<SubscriptionHandle, std::string> _handleToQueueName; //<queueName,Subscription>
};
