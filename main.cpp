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
bool isDateExpired(const string& expiryDate){
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
    bool isExpired()const{
        return isDateExpired(expiryDate);
    }

    void display()const{
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

    // Deserialize from string
    static Medicine deserialize(const string& data) {
        stringstream ss(data);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6) {
            return Medicine(
                stoi(tokens[0]),
                tokens[1],
                tokens[2],
                stod(tokens[3]),
                stoi(tokens[4]),
                tokens[5]
            );
        }
        return Medicine();
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

    // Show customer Info
    void display()const{
        cout << "Customer ID: " << custID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Total Purchases: " << purchaseCount << endl;

        // Discount checking
        if (isEligibleForDiscount()) {
            cout << "Discount: " << getDiscountPercentage() << "%" << endl;
        }

    }

    // Getters
    int getCustID()const{ return custID; }
    string getName()const{ return name; }
    string getPhone()const{ return phone; }
    int getPurchaseCount()const{ return purchaseCount; }

    // Serialize the customer lists
    string serialize() const {
        stringstream ss;
        ss << custID << "," << name << "," << phone << "," << purchaseCount;
        return ss.str();
    }

    // Extract customer info from string
    static Customer deserialize(const string& data) {
        stringstream ss(data);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 4) {
            return Customer( stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[3]));
        }
        return Customer();
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
    void updateMedicine(){
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

    // Viewing complete inventory
    void viewInventory()const{
        cout << "\n╔════════════════════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                           MEDICINE INVENTORY                                   ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════════════════════╝" << endl;

        if(medicineInventory->empty()){
            cout << "\nNo medicines in inventory!" << endl;
            return;
        }

        cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << "Status" << endl;
        cout << string(95, '-') << endl;
        for(const auto& med : *medicineInventory){
            med.display();
        }

        cout << "\nTotal Medicines: " << medicineInventory->size() << endl;
    }

    // Viewing sales summary repo
    void viewReports()const{
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║         SALES REPORTS              ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;

        ifstream file("invoices.txt"); // Opening file
        if(!file.is_open()){
            cout << "\nNo sales data available!" << endl;
            return;
        }

        double totalSales = 0.0;
        int totalInvoices = 0;
        string line;

        cout << "\n" << left << setw(12) << "Invoice ID" << setw(20) << "Customer" << setw(15) << "Date" << setw(15) << "Amount" << endl;
        cout << string(62, '-') << endl;

        while(getline(file, line)){
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if(tokens.size() == 6){
                cout << left << setw(12) << tokens[0] << setw(20) << tokens[1] << setw(15) << tokens[2] << "$" << setw(14) << tokens[5] << endl;
                totalSales += stod(tokens[5]);
                totalInvoices++;
            }
        }
        file.close();

        cout << string(62, '-') << endl;
        cout << "\nTotal Invoices: " << totalInvoices << endl;
        cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    }

    // checking alerts for low stock and expirary medicines
    void checkAlerts() const{
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║      EXPIRY & STOCK ALERTS         ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;

        bool hasExpired = false;
        bool hasLowStock = false;

        cout << "\nEXPIRED MEDICINES:" << endl;
        cout << string(80, '-') << endl;

        for(const auto& med : *medicineInventory){
            if (med.isExpired()) {
                hasExpired = true;
                cout << "ID: " << med.getMedID() << " | " << med.getName() << " | Expired on: " << med.getExpiryDate() << endl;
            }
        }
        if(!hasExpired){
            cout << "No expired medicines." << endl;
        }

        cout << "\nLOW STOCK MEDICINES (< 10 units):" << endl;
        cout << string(80, '-') << endl;

        for(const auto& med : *medicineInventory){
            if (med.isLowStock() && !med.isExpired()) {
                hasLowStock = true;
                cout << "ID: " << med.getMedID() << " | " << med.getName() << " | Stock: " << med.getQuantity() << " units" << endl;
            }
        }

        if(!hasLowStock){
            cout << "No low stock items." << endl;
        }
    }

};

// Handles Medicine sells and customers interaction
class Pharmacist : public User{
private:
    vector<Medicine>* medicineInventory;
    vector<Customer>* customerList;
    int invoiceCounter;

    // Save medicines to file
    void saveMedicinesToFile()const{
        ofstream file("medicines.txt");
        if (file.is_open()){
            for (const auto& med : *medicineInventory) {
                file << med.serialize() << endl;
            }
            file.close();
        }
    }

    // Saving Customer information in file
    void saveCustomersToFile()const{
        ofstream file("customers.txt");
        if (file.is_open()) {
            for(const auto& cust : *customerList){
                file << cust.serialize() << endl;
            }
            file.close();
        }
    }

    // Load invoice from file
    void loadInvoiceCounter(){
        ifstream file("invoice_counter.txt");
        if(file.is_open()){
            file >> invoiceCounter;
            file.close();
        }
    }

    // Save invoice to file
    void saveInvoiceCounter()const{
        ofstream file("invoice_counter.txt");
        if(file.is_open()){
            file << invoiceCounter;
            file.close();
        }
    }

public:

    // Constructor
    Pharmacist(int userId, string userName, string userContact, vector<Medicine>* inventory, vector<Customer>* customers) : User(userId, userName, userContact), medicineInventory(inventory), customerList(customers), invoiceCounter(1001) {
        loadInvoiceCounter();
    }

    // Show Menubar
    void showMenu(){
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║       PHARMACIST MENU              ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "1. Sell Medicine" << endl;
        cout << "2. Search Medicine" << endl;
        cout << "3. View Inventory" << endl;
        cout << "4. Check Expiry" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter choice: ";
    }

    // Sell medicine method for customers
    void sellMedicine(){
        string custName, custPhone;
        int custID = 0;
        bool isExistingCustomer = false;
        Customer* currentCustomer = nullptr;

        cout << "\n--- Sell Medicine ---" << endl;
        cout << "Is this an existing customer? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();

        if(choice == 'y' || choice == 'Y'){
            cout << "Enter Customer Phone: ";
            getline(cin, custPhone); // For searching

            // Searching for existing customer
            for(auto& cust : *customerList){
                if(cust.getPhone() == custPhone){
                    isExistingCustomer = true;
                    currentCustomer = &cust;
                    custID = cust.getCustID();
                    custName = cust.getName();
                    cout << "✓ Customer found: " << custName << endl;
                    break;
                }
            }

            if (!isExistingCustomer) {
                cout << "✗ Customer not found. Creating new customer..." << endl;
            }
        }

        // Creating new customers if not existed
        if(!isExistingCustomer){
            custID = customerList->size() + 1;
            cout << "Enter Customer Name: ";
            getline(cin, custName);
            cout << "Enter Customer Phone: ";
            getline(cin, custPhone);

            Customer newCust(custID, custName, custPhone, 0);
            customerList->push_back(newCust);
            currentCustomer = &customerList->back();
            saveCustomersToFile();
        }

        // Create Invoice
        Invoice invoice(invoiceCounter++, custName);

        // Add medicines to invoice
        char addMore = 'y';

        while(addMore == 'y' || addMore == 'Y'){
            int medID, qty;

            cout << "\nEnter Medicine ID: ";
            cin >> medID;

            bool found = false;
            for(auto& med : *medicineInventory){
                if(med.getMedID() == medID){
                    found = true;

                    // Expiry Checking
                    if (med.isExpired()) {
                        cout << "✗ Error: This medicine has expired!" << endl;
                        break;
                    }

                }
                cout << "Medicine: " << med.getName() << endl;
                cout << "Available Quantity: " << med.getQuantity() << endl;
                cout << "Price: $" << med.getPrice() << endl;
                cout << "Enter Quantity to sell: ";
                cin >> qty;

                if(qty > med.getQuantity()){
                    cout << "✗ Error: Insufficient stock!" << endl;
                }else if (qty <= 0){
                    cout << "✗ Error: Invalid quantity!" << endl;
                }else{
                    med.updateStock(qty);
                    invoice.addItem(med, qty);
                    cout << "✓ Added to invoice!" << endl;
                }
                break;
            }
            if(!found){
                cout << "✗ Medicine with ID " << medID << " not found!" << endl;
            }

            cout << "\nAdd more medicines? (y/n): ";
            cin >> addMore;
        }

        // Generate and print invoice
        double discount = currentCustomer->getDiscountPercentage();
        invoice.generateBill(discount);
        invoice.printInvoice();
        invoice.saveToFile();

        currentCustomer->incrementPurchase(); // Updating customer purchase count

        // Save the updated data
        saveMedicinesToFile();
        saveCustomersToFile();
        saveInvoiceCounter();

        cout << "\n✓ Sale completed successfully!" << endl; // Conformation message
    }

    // Method for searching medicine
    void searchMedicine()const{
        cout << "\n--- Search Medicine ---" << endl;
        cout << "1. Search by Name" << endl;
        cout << "2. Search by Company" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        string searchTerm;
        bool found = false;

        if(choice == 1){
            cout << "Enter Medicine Name: ";
            getline(cin, searchTerm);

            cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << endl;
            cout << string(75, '-') << endl;

            for (const auto& med : *medicineInventory) {
                if (med.getName().find(searchTerm) != string::npos) {
                    med.display();
                    found = true;
                }
            }
        }else if(choice == 2){
            cout << "Enter Company Name: ";
            getline(cin, searchTerm);

            cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << endl;
            cout << string(75, '-') << endl;

            for(const auto& med : *medicineInventory){
                if (med.getCompany().find(searchTerm) != string::npos) {
                    med.display();
                    found = true;
                }
            }
        }else{
            cout << "Invalid choice!" << endl;
            return;
        }

        if(!found){
            cout << "No medicines found matching '" << searchTerm << "'" << endl;
        }
    }

    // Checks for expired medicines
    void checkExpiry() const{
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║      EXPIRY CHECK REPORT           ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;

        bool hasExpired = false;

        cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(12) << "Expiry Date" << endl;
        cout << string(55, '-') << endl;

        if (!hasExpired) {
            cout << "✓ No expired medicines found!" << endl;
        } else {
            cout << "\n Please remove these expired medicines from inventory!" << endl;
        }
    }

    // For showing Inventory
    void viewInventory()const{
        cout << "\n╔════════════════════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                           MEDICINE INVENTORY                                   ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════════════════════╝" << endl;

        if(medicineInventory->empty()){
            cout << "\nNo medicines in inventory!" << endl;
            return;
        }

        cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << "Status" << endl;
        cout << string(95, '-') << endl;

        for(const auto& med : *medicineInventory){
            med.display();
        }

        cout << "\nTotal Medicines: " << medicineInventory->size() << endl;
    }


};

class PharmacySystem{
private:
    vector<Medicine> medicineInventory;
    vector<Customer> customerList;
    Admin* admin;
    Pharmacist* pharmacist;


    void displayMainMenu(){
            cout<<"\n";
            cout << "╔════════════════════════════════════╗" << endl;
            cout << "║  PHARMACY MANAGEMENT SYSTEM        ║" << endl;
            cout << "╚════════════════════════════════════╝" << endl;
            cout << "1. Admin Login" << endl;
            cout << "2. Pharmacist Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter choice: ";
        }


    // Admin loging operation
    void adminLogin(){
        int id;
        string password;

        cout << "\n--- Admin Login ---" << endl;
        cout << "Enter Admin ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Password: ";
        getline(cin, password);

        // Brute force authentication for admin log in 
        if(admin->login(id, password)){
            adminMenu();
        }else{
            cout << "\n Invalid credentials!" << endl;
        }


    }

    // Admin menu operation
    void adminMenu(){
        while(admin->isLoggedIn()){
            admin->display();

            int choice;
            cin >> choice;
            cin.ignore();

            switch(choice){
                case 1:
                    admin->addMedicine();
                    break;
                case 2:
                    admin->removeMedicine();
                    break;
                case 3:
                    admin->updateMedicine();
                    break;
                case 4:
                    admin->viewInventory();
                    break;
                case 5:
                    admin->viewReports();
                    break;
                case 6:
                    admin->checkAlerts();
                    break;
                case 7:
                    admin->logout();
                    break;
                default:
                    cout << "\n Invalid choice!" << endl;
            }
        }
    }

    // Pharmacist login operation
    void pharmacistLogin(){
        int id;
        string password;

        cout << "\n--- Pharmacist Login ---" << endl;
        cout << "Enter Pharmacist ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Password: ";
        getline(cin, password);

        // Brute Force authentication for pharmacist log in
        if(pharmacist->login(id, password)){
            pharmacistMenu();
        }else{
            cout << "\n Invalid credentials!" << endl;
        }
    }

    // Pharmacist menu operation
    void pharmacistMenu(){
        while(pharmacist->isLoggedIn()){
            pharmacist->showMenu();

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    pharmacist->sellMedicine();
                    break;
                case 2:
                    pharmacist->searchMedicine();
                    break;
                case 3:
                    pharmacist->viewInventory();
                    break;
                case 4:
                    pharmacist->checkExpiry();
                    break;
                case 5:
                    pharmacist->logout();
                    break;
                default:
                    cout << "\n Invalid choice!" << endl;
            }
        }
    }

    // Load Medicines Info from file
    void loadMedicinesFromFile(){
        ifstream file("medicines.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                Medicine med = Medicine::deserialize(line);
                if (med.getMedID() != 0) {
                    medicineInventory.push_back(med);
                }
            }
            file.close();
        }
    }
    
    // Load Customers info from file
    void loadCustomersFromFile(){
        ifstream file("customers.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                Customer cust = Customer::deserialize(line);
                if (cust.getCustID() != 0) {
                    customerList.push_back(cust);
                }
            }
            file.close();
        }
    }


public:
    // Constructor
    PharmacySystem(){
        // Initializing Users
        admin = new Admin(23070, "CSE_23", "015", &medicineInventory);
        pharmacist = new Pharmacist(2307090, "Ritovash Chanda", "01615058161", &medicineInventory, &customerList);

        loadMedicinesFromFile();
        loadCustomersFromFile();

    }

    void run(){
        while(true){
            displayMainMenu();
            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice){
                case 1:
                    adminLogin();
                    break;
                case 2:
                    pharmacistLogin();
                    break;
                case 3:
                    cout << "\n Thank you for using Pharmacy Management System!" << endl;
                    return;
                default:
                    cout << "\n Invalid choice! Please try again." << endl;
            }
        }
    }

    // Destructor
    ~PharmacySystem(){
        delete admin;
        delete pharmacist;
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