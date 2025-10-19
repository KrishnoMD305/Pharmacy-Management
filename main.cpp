#include<iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include<sstream>

using namespace std;

// function to get current date
string getCurrentDate(){
    time_t now = time(0); // returns the current time in seconds since January 1, 1970
    tm *ltm = localtime(&now); // converts that raw time_t into a human-readable local time structure
    stringstream ss;
    ss << (ltm->tm_mday) << "/" << (1 + ltm->tm_mon) << "/" << (1900 + ltm->tm_year);
    return ss.str();
}
class Medicine{
private:
    int medID;
    string name;
    string company;
    double price;
    int quantity;
    string expiryDate;

public:
    // Constructor
    Medicine(int id = 0, string medName = "", string comp = "", double medPrice = 0.0, int qty = 0, string expiry = "") : medID(id), name(medName), company(comp), price(medPrice), quantity(qty), expiryDate(expiry) {}

    // Update stock after selling
    bool updateStock(int soldQty) {
        if (soldQty <= quantity) {
            quantity -= soldQty;
            return true;
        }
        return false;
    }

    // Add stock
    void addStock(int addQty) {
        quantity += addQty;
    }

    bool isLowStock() const {
        if(quantity < 10){
            return true;
        }else{
            return false;
        }
    }
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