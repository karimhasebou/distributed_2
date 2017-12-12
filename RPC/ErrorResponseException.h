//
//  ErrorResponseException.cpp
//  distributed_2
//
//  Created by Farida Eid on 12/12/17.
//
//

#ifndef ERROR_RESPONSE
#define ERROR_RESPONSE

#include <exception>

class ErrorResponseException : public std::runtime_error
{
public:
    ErrorResponseException(char const* const message) throw()
    : std::runtime_error(message) {
        
    }
};

#endif
