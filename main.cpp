#include <bits/stdc++.h>
using namespace std;
#include <openssl/sha.h>

class User
{
public:
    string username;
    string hashedPassword;
    string salt;
    User(string uname, string hpass, string slt)
    {
        username = uname;
        hashedPassword = hpass;
        salt = slt;
    }
    string toString()
    {
        return username + "," + hashedPassword + "," + salt;
    }
};

class Hasher
{
public:
    static string generateSalt()
    {
        random_device rd;
        uniform_int_distribution<int> dist(33, 126);
        string salt = "";
        for (int i = 0; i < 16; i++)
        {
            salt += static_cast<char>(dist(rd));
        }
        return salt;
    }
    static string hashPassword(string password, string salt)
    {
        string input = password + salt;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.length(), hash);

        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
};

class UserRepository
{
private:
    string filename = "users.txt";

public:
    void saveUser(User user)
    {
        ofstream outFile(filename, ios::app);
        outFile << user.toString() << endl;
        outFile.close();
    }
    vector<User> getUsers()
    {
        ifstream inFile(filename);
        vector<User> users;
        string line;

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string username, hashedPassword, salt;

            getline(ss, username, ',');
            getline(ss, hashedPassword, ',');
            getline(ss, salt, ',');

            users.push_back(User(username, hashedPassword, salt));
        }
        inFile.close();
        return users;
    }
};

class AuthenticationService
{
private:
    UserRepository repo;

public:
    void registerUser(string username, string password)
    {
        vector<User> users = repo.getUsers();
        for (User user : users)
        {
            if (user.username == username)
            {
                cout << "Error: Username already taken" << endl;
                return;
            }
        }
        string salt = Hasher::generateSalt();
        string hashedPassword = Hasher::hashPassword(password, salt);

        User newUser(username, hashedPassword, salt);
        repo.saveUser(newUser);

        cout << "User registered successfully" << endl;
    }
    bool authenticateUser(string username, string password)
    {
        vector<User> users = repo.getUsers();
        for (User user : users)
        {
            if (user.username == username)
            {
                string inputHashedPassword = Hasher::hashPassword(password, user.salt);
                if (inputHashedPassword == user.hashedPassword)
                {
                    cout << "Login successful" << endl;
                    return true;
                }
                else
                {
                    cout << "Incorrect password" << endl;
                    return false;
                }
            }
        }

        cout << "User not found" << endl;
        return false;
    }
};

int main()
{
    AuthenticationService authService;
    int choice;
    string username, password;

    while (true)
    {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        if ((cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input Please enter a number (1, 2, or 3)." << endl;
            continue;
        }
        if (choice == 3)
        {
            cout << "Goodbye" << endl;
            break;
        }
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (choice == 1)
        {
            authService.registerUser(username, password);
        }
        else if (choice == 2)
        {
            authService.authenticateUser(username, password);
        }
        else
        {
            cout << "Invalid choice Try again." << endl;
        }
    }
    return 0;
}
