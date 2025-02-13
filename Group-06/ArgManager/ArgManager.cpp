/**
 * Implementation of the ArgManager class
 * 
 * By Will Crawford
 */

#include <iostream>
#include <vector>
#include "ArgManager.h"

/**
 * Constructor for ArgManager
 * @param argc the amount of arguments
 * @param argv the list of arguments
 */
cse::ArgManager::ArgManager(int argc, char *argv[])
{
    //Load in all the command line options
    LoadArgManager();

    //pass argc and argv
    _argc = argc;
    for (int i = 0; i < argc; i++)
    {
        _argv.push_back(argv[i]);
    }
}

/**
 * Loads in all of the command line options
 */
void cse::ArgManager::LoadArgManager()
{
    
}

/**
 * Checks if a string is present in the input arguments
 * @param argv the string to check for
 * @return if the string is present in the input arguments
 */
bool cse::ArgManager::Has(std::string argv)
{
    for (int i = 0 ; i < _argc; i++)
    {
        if (_argv[i] == argv)
        {
            return true;
        }
    }
    return false;
}

/**
 * Find a string and return the next string as the value of the option
 * @param argv the string to find
 * @return the next string as the value of the option
 */
std::string cse::ArgManager::GetOption(std::string argv)
{
    for (int i = 0 ; i < _argc; i++)
    {
        if (_argv[i] == argv)
        {
            return _argv[i + 1];
        }
    }
    return "";
}

/**
* Prints help info for ArgManager
*/
void cse::ArgManager::PrintHelp()
{
    std::cout << "--help has been triggered\n";
    std::cout << "arguments available:\n";
    std::cout << "[placeholder]" << std::endl;
}