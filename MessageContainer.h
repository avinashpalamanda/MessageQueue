#pragma once
/*
The class MessageContainer will hold all the messages in a linked list. 
Head->M1->M2->Tail.
*/
#include <string>

struct MessageInfo;

class MessageContainer
{
    private:
    MessageInfo* _pHead = nullptr;
    MessageInfo* _pTail = nullptr;

    public:
    MessageContainer();
    ~MessageContainer();

    /*The function will return if there is a message if not return empty string
    The functions also provides the pointer to next message which can be used to retrieve next message.
    If the message is dispatched to all subscribed user, it is deleted from the container.
    */
    const std::string GetMessage(const MessageInfo* pMessagePtr,const MessageInfo* &pNextMessagePtr);

    /* Updates the tail contents to message contents and creates a new tail.*/
    bool AddMessage(const std::string& message, int handlesMessageToBeDispatched);

    const MessageInfo* GetTail() {return _pTail;}
};