#pragma once
#include <Types_Z.h>
#include <string.h>

/**
 * @brief Used by `Console_Z` to keep track of commands
 * 
 */

typedef bool (*CommandProc)(void);

struct Command_Z{
    U32 commandName;
    U32 aliasName;
    CommandProc callback;
    Command_Z* next;

    /**
     * @brief Construct a new Command_Z object
     * I'm not sure why it didn't inline it in his case... Two things are for sure, the symbol is not present but the function is
     * 
     * 
     * First verified to match: 2024-03-22 18:33:27
     */
    Command_Z(){
        commandName = 0;
        aliasName = 0;
        next = NULL;
        callback = NULL;
    }
};

/**
 * @brief The script engine
 * This class isn't just for the developer console. It also runs all of the .tsc's.
 */
class Console_Z{
    char dummy1[9140];

    //Forward linked list of all of the registered commands
    //Allocated by `AddCommand`
    Command_Z* m_pCommands; 

    char dummy2[17420];
    
    //Number of parameters given to the current command being interpreted
    int m_NbParam;

    //String parameters of current command being interpreted
    char* m_StrParam[16];

    //Presence of float parameters of current command being interpreted
    unsigned char m_IsFloatParamArray[16];

    //Float parameters of current command being interpreted
    float m_FloatParamArray[16];

public:
    //Number of parameters given to present active command
    //Implied to exist by the Zouna source
    inline S32 GetNbParam() const{
        return m_NbParam;
    }

    //Is `i`th given parameter of present active command a float?
    //Implied to exist by the Zouna source
    inline Bool IsParamFloat(const U32 i) const{
        return m_IsFloatParamArray[i];
    } 

    //Get the `i`th given float parameter of present active command
    //Implied to exist by the Zouna source
    inline Float GetParamFloat(const U32 i) const{
        return m_FloatParamArray[i];
    } 

    /**
     * @brief Register a command with the script engine
     * 
     * `comment` is unused by WALL-E
     * 
     * First verified to match: 2024-03-22 18:14:31
     * 
     * @param command The command's name
     * Uppercase characters and numbers are treated as part of the command's alias. An alias of a command is 
     * an alternative way of invoking it besides `command`, probably as a convenient developer shortcut.
     * @param callback What to call when the command gets invoked
     * Callback returns true if it's successful, false if otherwise
     * @param comment 
     */
    void AddCommand(const Char* command, CommandProc callback, const Char* comment);
};