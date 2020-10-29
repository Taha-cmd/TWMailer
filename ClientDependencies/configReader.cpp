#include "configReader.h"

ConfigReader::ConfigReader(std::istream& inputStream)
    : inputStream(inputStream)
{
}

ConfigReader::~ConfigReader()
{
}

void ConfigReader::ReadLineParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength)
{
    if(maxLength == 0)
        throw std::invalid_argument("maxLength must be larger than 0.");

    PrintReadParameterInfo(parameterName, maxLength);

    std::getline(this->inputStream, target);
    
    if(target.length() > maxLength)
        throw ConfigReaderException("Invalid Length of Parameter: " + parameterName);
}

void ConfigReader::ReadPassword(std::string& target, const std::size_t maxLength)
{
    if(maxLength == 0)
        throw std::invalid_argument("maxLength must be larger than 0.");

    PrintReadParameterInfo("Password", maxLength);
    
    std::string password = getpass();

    if(password.length() < 1 || password.length() > maxLength)
        throw std::invalid_argument("Password length must be between 1 and " + std::to_string(maxLength));

    target = password;

}

void ConfigReader::ReadTextParameter(const std::string& parameterName, std::string& target, const std::size_t maxLength)
{
    if(maxLength == 0)
        throw std::invalid_argument("maxLength must be larger than 0.");
    
    PrintReadParameterInfo(parameterName, maxLength);
    std::cout << "Type :wq to save." << std::endl;

    std::size_t index;
    std::string temp;
    
    while((index = temp.find(":wq")) == std::string::npos)
    {
        std::string line;
        std::getline(this->inputStream, line);
        temp += line + '\n';
    }

    temp.erase(index);

    if(temp.length() > maxLength)
        throw ConfigReaderException("Invalid Length of Parameter: " + parameterName);

    target = temp;
}

void ConfigReader::PrintReadParameterInfo(const std::string& parameterName, const std::size_t maxLength)
{
    if(maxLength == std::numeric_limits<std::size_t>::max())
        std::cout << "Enter " << parameterName <<  ": " << std::endl;
    else
        std::cout << "Enter " << parameterName << "(max characters: " << maxLength << ") : ";
}

int ConfigReader::getch()
{
    int ch;
    // https://man7.org/linux/man-pages/man3/termios.3.html
    struct termios t_old, t_new;

    // https://man7.org/linux/man-pages/man3/termios.3.html
    // tcgetattr() gets the parameters associated with the object referred
    //   by fd and stores them in the termios structure referenced by
    //   termios_p
    tcgetattr(STDIN_FILENO, &t_old);
    
    // copy old to new to have a base for setting c_lflags
    t_new = t_old;

    // https://man7.org/linux/man-pages/man3/termios.3.html
    //
    // ICANON Enable canonical mode (described below).
    //   * Input is made available line by line (max 4096 chars).
    //   * In noncanonical mode input is available immediately.
    //
    // ECHO   Echo input characters.
    t_new.c_lflag &= ~(ICANON | ECHO);
    
    // sets the attributes
    // TCSANOW: the change occurs immediately.
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    // reset stored attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);

    return ch;
}

std::string ConfigReader::getpass()
{
    bool show_asterisk = true;

    const char BACKSPACE = 127;
    const char RETURN = 10;

    unsigned char ch = 0;
    std::string password;

    while ((ch = getch()) != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                if (show_asterisk)
                {
                    printf("\b \b"); // backslash: \b
                }
                password.resize(password.length() - 1);
            }
        }
        else
        {
            password += ch;
            if (show_asterisk)
            {
                printf("*");
            }
        }
    }
    printf("\n");
    return password;
}