/**
 * Arg Manger Class
 * 
 * By Will Crawford
 */

#ifndef ARGMANAGER__ARGMANAGER_H
#define ARGMANAGER__ARGMANAGER_H

#include <iostream>
#include <vector>

namespace cse {

    class ArgManager {
    public:
        ArgManager(int argc, char *argv[]);
        void LoadArgManager();
        bool Has(std::string argv);
        std::string GetOption(std::string argv);
        void PrintHelp();
        
    private:
        //store args

        /// number of arguments
        int _argc = 0;

        /// List of options that have been given
        std::vector<std::string> _argv;
    };
}

#endif //ARGMANAGER__ARGMANAGER_H

