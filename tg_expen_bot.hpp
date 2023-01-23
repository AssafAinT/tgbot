#ifndef __ASSAF_TG_EXPENSE_BOT_HPP__
#define __ASSAF_TG_EXPENSE_BOT_HPP__
#include <unordered_map> //std::unordered_map
#include <vector> //std::vector
#include <sstream> //std::stringstream
#include <iostream> //std::cout
// #include <sqlite3.h>
namespace TgUser
{
    class Users
    {
        public:
        typedef std::unordered_map<std::string,size_t> expense_map;
        explicit Users(){}
        void AddUser(int64_t uid)
        {
            m_UIDS.push_back(uid);
        }

        void AddExpense(int64_t uid, const std::string &expense)
        {   
            std::stringstream streamStr(expense);
            std::string command;
            std::string spec_expense;
            std::size_t expense_value = 0;
            streamStr >> command >> spec_expense >>  expense_value;

            std::cout << "Deserialized data: " <<  spec_expense << " "
                << expense_value << std::endl;
            
            m_userBalance[uid][spec_expense] += expense_value;
        }

        std::size_t GetExpense(int64_t uid, const std::string &expense)
        {
            std::cerr << expense << std::endl;
            return m_userBalance[uid][expense];
        }

        private: 
        std::vector<int64_t> m_UIDS; 
        std::unordered_map<int64_t , 
                           expense_map> m_userBalance;
    };

    struct UserDB
    {

    }
} // namespace name

#endif