#include <stdexcept>
#include <string>


class Message {

    public:
        std::string GetSender() { return sender; };
        std::string GetRecipient() { return recipient; };
        std::string GetSubject() { return subject; };
        std::string GetMessage() { return message; };

        Message(std::string sender, std::string recipient, std::string subject, std::string message);
        ~Message();

        std::string ToString();
    private:
        void Validate();

        std::string sender;
        std::string recipient;
        std::string subject;
        std::string message;
};