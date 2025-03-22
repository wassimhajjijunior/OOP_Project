User Authentication System

This C++ program implements a simple user authentication system that allows users to register and log in. Passwords are securely hashed using SHA-256 with a salt to protect user credentials. The system stores user data in a plain text file (`users.txt`) for simplicity.
Features

- User Registration: Users can create an account by providing a unique username and a password. The password is hashed with a randomly generated salt and stored securely.
- User Authentication: Registered users can log in by entering their username and password. The password entered by the user is hashed with the stored salt and compared with the saved hashed password.
- Salt and SHA-256: For additional security, passwords are not stored directly. Instead, a randomly generated salt is used in conjunction with the SHA-256 hashing algorithm.
Requirements
- C++ Compiler (e.g., g++, clang++)
- OpenSSL library (for SHA-256 hashing)
  
Installation
1. Clone the repository:
bash
git clone https://github.com/yourusername/user-authentication-system.git
cd user-authentication-system

2. Install OpenSSL:
- On Linux (Debian/Ubuntu):
bash
sudo apt-get install libssl-dev

- On macOS (Homebrew):
bash
brew install openssl

3. Compile the program:
bash
g++ -o auth_system main.cpp -lssl -lcrypto

Usage
After compiling the program, you can run it using the following command:
bash
./auth_system

Menu Options
- 1. Register: Register a new user by providing a unique username and a password. The password will be hashed and stored along with the username and salt.
- 2. Login: Authenticate using an existing username and password. The entered password will be hashed and compared with the stored hash.
- 3. Exit: Exit the program.
 Example
1. Register
2. Login
3. Exit

Choose an option: 1
Enter username: john_doe
Enter password: securepassword123
User registered successfully

1. Register
2. Login
3. Exit
Choose an option: 2
Enter username: john_doe
Enter password: securepassword123
Login successful

File Format
User data is stored in the file `users.txt` in the following format:

username,hashedPassword,salt

Each user is stored on a new line, with the username, hashed password, and salt separated by commas.

Test
To test the system:

1. Register a new user:
- Select the 1. Register option and provide a username and password.
- Verify that the user is successfully registered by checking the console message: `User registered successfully`.

2.Attempt to register with an existing username:
- Try to register again using the same username.
- The system should show an error message: `Error: Username already taken`.

3. Login with the registered user:
- Select the 2. Login option and enter the username and password.
- Verify that the login is successful and the console shows: `Login successful`.

4. Attempt login with an incorrect password:
- Select 2. Login and enter the correct username but an incorrect password.
- The system should show the message: `Incorrect password`.

5. Attempt login with a non-registered username:
- Select 2. Login and provide a username that is not registered.
- The system should show: `User not found`.


You can copy this improved version to your `README.md` file.
