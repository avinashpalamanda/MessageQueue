#include "MessageContainer.h"
#include "MessageInfo.h"

namespace
{
	constexpr const char* HEADSTR = "HEAD";
	constexpr const char* TAILSTR = "TAIL";
}

MessageContainer::MessageContainer()
{
	_pHead = new MessageInfo(HEADSTR,0);
	_pTail = new MessageInfo(TAILSTR,0);

	_pHead->_pNext = _pTail;
	_pTail->_pPrev = _pHead;
}

MessageContainer::~MessageContainer()
{
	auto pMessage = _pHead;
	while(pMessage)
	{
		auto pNext = pMessage->_pNext;
		delete pMessage;
		pMessage = pNext;
	}

	_pHead = nullptr;
	_pTail = nullptr;
}

const std::string
MessageContainer::GetMessage(const MessageInfo* pMessagePtr,const MessageInfo* &pNextMessage)
{
	if(pMessagePtr->_message == ::HEADSTR || pMessagePtr->_message == ::TAILSTR)
		return "";

	const auto& message = const_cast<MessageInfo*>(pMessagePtr)->GetMessageForSubscriber();
	pNextMessage = pMessagePtr->_pNext;
	if(pMessagePtr->_handlesMessageToBeDispatched == 0) //Delete Message from Container
	{
		pMessagePtr->_pPrev->_pNext = pMessagePtr->_pNext;
		pMessagePtr->_pNext->_pPrev = pMessagePtr->_pPrev;
		delete pMessagePtr;
	}
	return message;
}

bool
MessageContainer::AddMessage(const std::string& message, int handlesMessageToBeDispatched)
{
	auto pNewTail = new MessageInfo(TAILSTR,0);

	auto pMessage = _pTail;
	pMessage->_message = message;
	pMessage->_handlesMessageToBeDispatched = handlesMessageToBeDispatched;

	pMessage->_pNext = pNewTail;
	pNewTail->_pPrev = pMessage;
	_pTail = pNewTail;
	return true;
}