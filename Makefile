#the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=c++17

#the build target executable:
TARGET = MessageQueue
all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) MessageContainer.cpp  MessageQueue.cpp  MessageQueueManager.cpp  SubscriptionContainer.cpp 
 
clean:
	$(RM) $(TARGET)
