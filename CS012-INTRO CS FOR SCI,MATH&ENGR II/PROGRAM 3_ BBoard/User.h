#include <string>

using namespace std;

class User{
    private:
    string username;
    string password;

    public:
    User();
    User(const string & , const string & );
    string getUsername() const;
    bool checkLogin(const string & , const string & );
    bool changePassword(const string & , const string & );
};
