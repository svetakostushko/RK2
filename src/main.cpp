#include <iostream>
#include <memory>
#include <string>

class MessageHandler
{
public:
    void HandleMessage(std::string const& message)
    {
        auto newState = state_->HandleMessage(message);

        if (newState)
        {
            state_ = std::move(newState);
        }
    }

private:
    class State
    {
    public:
        virtual ~State() = default;

        virtual std::unique_ptr<State> HandleMessage(std::string const& message) = 0;
    };

    class DefaultState : public State
    {
    public:
        std::unique_ptr<State> HandleMessage(std::string const& message) override;
    };

    class SessionState : public State
    {
    public:
        explicit SessionState(std::string sessionName)
            : sessionName_(std::move(sessionName))
        {}

        std::unique_ptr<State> HandleMessage(std::string const& message) override;

    private:
        std::string sessionName_;
    };

    ////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<State> state_{ std::make_unique<DefaultState>() };
};

std::unique_ptr<MessageHandler::State>
MessageHandler::DefaultState::HandleMessage(std::string const& message)
{
    std::string const kStartSessionCommand("start_session ");

    if (message.compare(0, kStartSessionCommand.size(), kStartSessionCommand) == 0)
    {
        auto it = std::next(std::begin(message), kStartSessionCommand.size());
        std::string sessionName(it, std::end(message));

        std::cout << "[Start Session] Session Name : " << sessionName << std::endl;
        return std::make_unique<SessionState>(std::move(sessionName));
    }
    else
    {
        std::cout << "\"" << message << "\" is invalid message." << std::endl;
        return nullptr;
    }
}

std::unique_ptr<MessageHandler::State>
MessageHandler::SessionState::HandleMessage(std::string const& message)
{
    std::string const kPrintCommand("print ");

    if (message == "end_session")
    {
        std::cout << "[" << sessionName_ << "][End Session]" << std::endl;

        return std::make_unique<DefaultState>();
    }
    else if (message.compare(0, kPrintCommand.size(), kPrintCommand) == 0)
    {
        auto it = std::next(std::begin(message), kPrintCommand.size());
        std::string text(it, std::end(message));

        std::cout << "[" << sessionName_ << "][Print] " << text << std::endl;
        return nullptr;
    }
    else
    {
        std::cout << "[" << sessionName_ << "] \"" <<
            message << "\" is invalid message." << std::endl;
        return nullptr;
    }
}


