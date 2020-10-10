
#ifndef MESSAGE
#define MESSAGE

#include <stdexcept>
#include "functions.h"
#include <string>

class Message {
    public:
        std::string GetSender() const { return sender; };
        std::string GetRecipient() const { return recipient; };
        std::string GetSubject() const { return subject; };
        std::string GetMessage() const { return message; };

        Message(std::string sender, std::string recipient, std::string subject, std::string message);
        Message(std::string text);
        ~Message();

        std::string ToString() const { return sender + '\n' + recipient + '\n' + subject + "\n" + message; };
        std::string ToNetworkString() const { return ToString() + "\n.\n"; };
        std::string ToEmailFormat() const;
    private:
        Message();

        void Validate();

        std::string sender;
        std::string recipient;
        std::string subject;
        std::string message;
};

#endif
