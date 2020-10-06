
#ifndef MESSAGE
#define MESSAGE

#include <stdexcept>
#include <string>

class Message {
    public:
        std::string GetSender() const { return sender; };
        std::string GetRecipient() const { return recipient; };
        std::string GetSubject() const { return subject; };
        std::string GetMessage() const { return message; };

        Message(std::string sender, std::string recipient, std::string subject, std::string message);
        ~Message();

        std::string ToString() const { return sender + '\n' + recipient + '\n' + subject + "\n" + message + "\n.\n"; };
    private:
        Message();

        void Validate();

        std::string sender;
        std::string recipient;
        std::string subject;
        std::string message;
};

#endif
