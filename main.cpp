#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Medicine{
private:
    int medID;
    string name;
    string company;
    double price;
    int quantity;
    string expiryDate;

};

class User{
protected:
    int ID; 
    string name;
    string contact;
    bool loggedin;
public:
    User(int userID=0, string username="", string usercontact="") : ID(userID),name(username),contact(usercontact), loggedin(false) {}

    ~User(){}

    bool login(int userId, const string& password) {
        if (userId == ID) {
            loggedin = true;
            cout << "\n✓ Login successful! Welcome, " << name << endl;
            return true;
        }
        return false;
    }

    void logout() {
        loggedin = false;
        cout << "\n✓ Logged out successfully!" << endl;
    }

    int getId() { return ID; }
    string getName() { return name; }
    string getContact() { return contact; }
    bool isLoggedIn() { return loggedin; }

};

class Pharmacy_system{
    private:
        void display_Main_menu(){
            cout<<"\n";
            cout << "╔════════════════════════════════════╗" << endl;
            cout << "║  PHARMACY MANAGEMENT SYSTEM        ║" << endl;
            cout << "╚════════════════════════════════════╝" << endl;
            cout << "1. Admin Login" << endl;
            cout << "2. Pharmacist Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter choice: ";
        }
};

int main(){
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                        ║" << endl;
    cout << "║         WELCOME TO PHARMACY MANAGEMENT SYSTEM          ║" << endl;
    cout << "║                                                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    return 0;
}