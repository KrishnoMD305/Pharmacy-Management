#include<iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include<sstream>
#include<iomanip>
#include<vector>
#include<fstream>

using namespace std;

// function to get current date
string getCurrentDate(){
    time_t now = time(0); // returns the current time in seconds since January 1, 1900
    tm *ltm = localtime(&now); // converts that raw time_t into a human-readable local time structure
    stringstream ss;
    ss << (ltm->tm_mday) << "/" << (1 + ltm->tm_mon) << "/" << (1900 + ltm->tm_year);
    return ss.str();
}

// Function to check expire date of a medicine
bool isDateExpired(string& expiryDate){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentDay = ltm->tm_mday;
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = 1900 + ltm->tm_year;

    // Extract the expiry date
    int day, month, year;
    char slash;
    stringstream ss(expiryDate);
    ss >> day >> slash >> month >> slash >> year;

    // Comparing dates
    if (year < currentYear) return true;
    if (year == currentYear && month < currentMonth) return true;
    if (year == currentYear && month == currentMonth && day < currentDay) return true;
    return false;
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

    // Checking expirary date of a medicine
    bool isExpired() {
        return isDateExpired(expiryDate);
    }

    void display(){
        cout << left << setw(8) << medID << setw(20) << name<< setw(15) << company << setw(10) << fixed << setprecision(2) << price << setw(10) << quantity << setw(12) << expiryDate;
        if (isExpired()) {
            cout << " [EXPIRED]";
        } else if (isLowStock()) {
            cout << " [LOW STOCK]";
        }
        cout << endl;
    }

    // Serialize the strings
    string serialize() {
        stringstream ss;
        ss << medID << "," << name << "," << company << "," << price << "," << quantity << "," << expiryDate;
        return ss.str();
    }

    // Getters
    int getMedID() { return medID; }
    string getName() { return name; }
    string getCompany() { return company; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }
    string getExpiryDate() { return expiryDate; }
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


class Admin : public User {
private:
    vector<Medicine>* medicineInventory; 
    void saveMedicinesToFile() {
        ofstream file("medicines.txt");
        if (file.is_open()) {
            for (const auto& med : *medicineInventory) {
                //file << med.serialize() << endl;
            }
            file.close();
        }
    }
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