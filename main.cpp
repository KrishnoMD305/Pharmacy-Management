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
    string serialize() const {
        stringstream ss;
        ss << medID << "," << name << "," << company << "," << price << "," << quantity << "," << expiryDate;
        return ss.str();
    }

    // Getters
    int getMedID() const { return medID; }
    string getName() const { return name; }
    string getCompany() const { return company; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getExpiryDate() const { return expiryDate; }

    // Setters
    void setName(const string& n) { name = n; }
    void setCompany(const string& c) { company = c; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }
    void setExpiryDate(const string& date) { expiryDate = date; }
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


class Customer{
private:
    int custID;
    string name;
    string phone;
    int purchaseCount; // For discount checking

public:
    // Constructor
    Customer(int id = 0, string custName = "", string custPhone = "", int purchases = 0) : custID(id), name(custName), phone(custPhone), purchaseCount(purchases) {}

    // Discount and purchasecount method
    void incrementPurchase(){
        purchaseCount++;
    }
    bool isEligibleForDiscount()const{
        return purchaseCount >= 5;
    }
    double getDiscountPercentage()const{
        if (purchaseCount >= 10) return 10.0;
        if (purchaseCount >= 5) return 5.0;
        return 0.0;
    }
};

class Invoice{
private: 
    int invoiceID;
    string customerName;
    string date;
    vector<pair<Medicine, int>> items; // Medicine and quantity
    double totalAmount;
    double discountAmount;
    double finalAmount;
public:
    // Constructors
    Invoice(int id, const string& custName) : invoiceID(id), customerName(custName), totalAmount(0.0), discountAmount(0.0), finalAmount(0.0) {
        date = getCurrentDate();
    }

    // Adding item to invoice
    void addItem(const Medicine& med, int qty) {
        items.push_back(make_pair(med, qty));
        totalAmount += med.getPrice() * qty;
    }
    // Discount and generate bill
    void applyDiscount(double discountPercent) {
        discountAmount = totalAmount * (discountPercent / 100.0);
        finalAmount = totalAmount - discountAmount;
    }
    void generateBill(double discountPercent = 0.0) {
        applyDiscount(discountPercent);
    }

    // Saving invoice to a file
    void saveToFile() const{
        ofstream file("invoices.txt", ios::app); // Append mode
        if(file.is_open()){ // Writing to file
            file << invoiceID << "," << customerName << "," << date << "," << totalAmount << "," << discountAmount << "," << (discountAmount > 0 ? finalAmount : totalAmount) << endl;
            file.close();
        }

    }

    // Getter
    double getFinalAmount() const {
        return discountAmount > 0 ? finalAmount : totalAmount;
    }

    // Printing Invoice to console
    void printInvoice() const{
        cout << "\n";
        cout << "╔════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              PHARMACY MANAGEMENT SYSTEM                    ║" << endl;
        cout << "║                    INVOICE                                 ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════╝" << endl;
        cout << "\nInvoice ID: " << invoiceID << endl;
        cout << "Date: " << date << endl;
        cout << "Customer: " << customerName << endl;
        cout << "\n" << string(60, '-') << endl;

        cout << left << setw(20) << "Medicine" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Subtotal" << endl;

        cout << string(60, '-') << endl;

        for(const auto& item : items){
            Medicine med = item.first;
            int qty = item.second;
            double subtotal = med.getPrice() * qty;

            // Showing the data
            cout << left << setw(20) << med.getName() << setw(10) << fixed << setprecision(2) << med.getPrice() << setw(10) << qty << setw(15) << subtotal << endl;
        }
        cout << string(60, '-') << endl;
        cout << right << setw(45) << "Total: $" << totalAmount << endl;

        if(discountAmount > 0){
            cout << right << setw(45) << "Discount: -$" << discountAmount << endl;
            cout << right << setw(45) << "Final Amount: $" << finalAmount << endl;
        }else{
            cout << right << setw(45) << "Final Amount: $" << totalAmount << endl;
        }

        cout << string(60, '=') << endl;
        cout << "\n      Thank you for your purchase!" << endl;
        cout << string(60, '=') << endl << endl;

    }
};

class Admin : public User {
private:
    vector<Medicine>* medicineInventory; 
    void saveMedicinesToFile() {
        ofstream file("medicines.txt");
        if (file.is_open()) {
            for (const auto& med : *medicineInventory) {
                file << med.serialize() << endl;
            }
            file.close();
        }
    }

public:
    Admin(int userId, string userName, string userContact, vector<Medicine>* inventory) : User(userId, userName, userContact), medicineInventory(inventory) {}

    // Display Admin menu
    void display(){
        cout << "\n";
        cout << "╔════════════════════════════════════╗" << endl;
        cout << "║         ADMIN MENU                 ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "1. Add Medicine" << endl;
        cout << "2. Remove Medicine" << endl;
        cout << "3. Update Medicine" << endl;
        cout << "4. View Inventory" << endl;
        cout << "5. View Reports" << endl;
        cout << "6. Check Expiry & Low Stock Alerts" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter choice: ";
    }
    
    // Adding medicine
    void addMedicine(){
        int id, qty;
        string name, company, expiry;
        double price;

        cout << "\n--- Add New Medicine ---" << endl;
        cout << "Enter Medicine ID: ";
        cin >> id;
        cin.ignore();

        // Checking if medicine is already exists 
        for (const auto& med : *medicineInventory) {
            if (med.getMedID() == id) {
                cout << "✗ Error: Medicine with ID " << id << " already exists!" << endl;
                return;
            }
        }

        cout << "Enter Medicine Name: ";
        getline(cin, name);
        cout << "Enter Company: ";
        getline(cin, company);
        cout << "Enter Price: $";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> qty;
        cin.ignore();
        cout << "Enter Expiry Date (DD/MM/YYYY): ";
        getline(cin, expiry);

        Medicine newMed(id, name, company, price, qty, expiry);
        medicineInventory->push_back(newMed); // Adding 

        cout << "✓ Medicine added successfully!" << endl;
        saveMedicinesToFile();
    }


    // Remove Medicine
    void removeMedicine(){
        int id;
        cout << "\n--- Remove Medicine ---" << endl;
        cout << "Enter Medicine ID to remove: ";
        cin >> id;

        // Search medicine
        auto it = remove_if(medicineInventory->begin(), medicineInventory->end(), [id](const Medicine& med) { return med.getMedID() == id; });
    }

    // Update medicine details
    void updatemedicine(){
        int id;
        cout << "\n--- Update Medicine ---" << endl;
        cout << "Enter Medicine ID to update: ";
        cin >> id;
        cin.ignore();

        bool found = false; 

        for(auto& med : *medicineInventory){
            if(med.getMedID() == id){
                found = true;
                cout << "\nCurrent Details:" << endl;
                cout << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << endl;
                med.display(); // Display details
                
                // Choices to perform
                cout << "\nWhat do you want to update?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Company" << endl;
                cout << "3. Price" << endl;
                cout << "4. Quantity" << endl;
                cout << "5. Expiry Date" << endl;
                cout << "6. Update All" << endl;
                cout << "Enter choice: ";

                // Taking input for choices
                int choice;
                cin >> choice;
                cin.ignore();

                // For storing temporary info
                string tempStr;
                double tempPrice;
                int tempQty;

                // Selecting choices using switch
                switch (choice){
                    case 1:
                        cout << "Enter new name: ";
                        getline(cin, tempStr);
                        med.setName(tempStr);
                        break;
                    case 2:
                        cout << "Enter new company: ";
                        getline(cin, tempStr);
                        med.setCompany(tempStr);
                        break;
                    case 3:
                        cout << "Enter new price: $";
                        cin >> tempPrice;
                        med.setPrice(tempPrice);
                        break;
                    case 4:
                        cout << "Enter new quantity: ";
                        cin >> tempQty;
                        med.setQuantity(tempQty);
                        break;
                    case 5:
                        cout << "Enter new expiry date (DD/MM/YYYY): ";
                        getline(cin, tempStr);
                        med.setExpiryDate(tempStr);
                        break;
                    case 6:
                        cout << "Enter new name: ";
                        getline(cin, tempStr);
                        med.setName(tempStr);
                        cout << "Enter new company: ";
                        getline(cin, tempStr);
                        med.setCompany(tempStr);
                        cout << "Enter new price: $";
                        cin >> tempPrice;
                        med.setPrice(tempPrice);
                        cout << "Enter new quantity: ";
                        cin >> tempQty;
                        med.setQuantity(tempQty);
                        cin.ignore();
                        cout << "Enter new expiry date (DD/MM/YYYY): ";
                        getline(cin, tempStr);
                        med.setExpiryDate(tempStr);
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        return;
                }

                // Confirmation message
                cout << "✓ Medicine updated successfully!" << endl;
                saveMedicinesToFile();
                break;
            }
        }
        if (!found) {
            cout << "✗ Medicine with ID " << id << " not found!" << endl;
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