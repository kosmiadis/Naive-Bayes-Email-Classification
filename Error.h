#pragma once 
#include <string>
#include <iostream>

using namespace std;

class Error {
    private:
        string message;

    public:
        Error() {};
        Error(string message) { this->message = message; }

        string getMessage () const {
            return this->message;
        }

        void setMessage (string message) {
            this->message = message;
        }
};

ostream &operator<<(ostream &stream, const Error& err) {
    stream << "Error: " << err.getMessage() << endl;
    return stream;
}