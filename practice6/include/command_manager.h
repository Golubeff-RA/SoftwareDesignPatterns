#pragma once
#include <list>

#include "icommand.h"

class CommandManager {
private:
    static CommandManager* instance_;
    std::list<CommandPtr> command_list_;
    bool register_flag_ = true;

    CommandManager() = default;
    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;

    void ExecuteAllCommands() {
        register_flag_ = false;
        for (auto& cmd : command_list_) {
            cmd->Execute();
        }
        register_flag_ = true;
    }

public:
    static CommandManager* Instance() {
        if (!instance_) {
            instance_ = new CommandManager();
        }
        return instance_;
    }

    void Register(CommandPtr cmd) {
        if (!register_flag_) {
            return;
        }

        command_list_.push_back(std::move(cmd));
    }

    void UndoLastCmd() {
        if (command_list_.size() <= 1) {
            return;
        }

        command_list_.pop_back();
        ExecuteAllCommands();
    }
};

inline CommandManager* CommandManager::instance_ = nullptr;