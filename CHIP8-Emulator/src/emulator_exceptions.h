#ifndef _EMULATOR_EXCEPTIONS_H_
#define _EMULATOR_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace CHIP_8_Emulator {

    class CPU_Exception : public std::exception {

        private:
            std::string m_message;

        public:
            CPU_Exception(const std::string& message) : m_message(message) {}
            const char* what() const throw() { return m_message.c_str(); }
    };
}

#endif

