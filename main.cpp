#include<iostream>
#include<string>   // for string manipulation
#include<algorithm>
#include<ctime>  // for time manipulation
#include<sstream> // for string stream
#include<iomanip>
#include<vector>
#include<fstream>

using namespace std;

// stringstream treat strings like streams 
// a stream is simply a flow (or sequence) of data — either going into a program (input) or coming out of a program (output).

// function to get current date
string getCurrentDate(){
    time_t now = time(0); // returns the current time in seconds since January 1, 1900
    tm *ltm = localtime(&now); // converts that raw time_t into a human-readable local time structure
    stringstream ss;  // Creates a std::stringstream object ss so it can be build a string using stream insertion (<<)
    
    // reads components from the tm structure and writes them into the stringstream in day/month/year form
    ss << (ltm->tm_mday) << "/" << (1 + ltm->tm_mon) << "/" << (1900 + ltm->tm_year);
    return ss.str();
}


// local broken-down time : the current date and time, expressed in our local time zone, split into components (year, month, day)

// parses a date in the string expiryDate and returns true if that date is strictly before today, otherwise false
// Function to check expire date of a medicine
bool isDateExpired(const string& expiryDate){
    time_t now = time(0);   // get the current calendar time
    tm *ltm = localtime(&now);  // convert now to local broken-down time
    int currentDay = ltm->tm_mday;
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = 1900 + ltm->tm_year;

    // Extract the expiry date
    int day, month, year;
    char slash;
    stringstream ss(expiryDate);  // creates a stream from the input string

    // the variable slash is used to consume the / characters.
    // attempts to read three integers separated by two characters
    ss >> day >> slash >> month >> slash >> year;

    // Comparing dates
    if (year < currentYear) return true;
    if (year == currentYear && month < currentMonth) return true;
    if (year == currentYear && month == currentMonth && day < currentDay) return true;
    return false;
}

class Medicine{
private:
    int medID;  // stores medicine ID
    string name; 
    string company; // stores medicine manifucturer company
    double price;
    int quantity;
    string expiryDate; // store the expirary date of the medicine

public:
    // Constructor
    Medicine(int id = 0, string medName = "", string comp = "", double medPrice = 0.0, int qty = 0, string expiry = "") : medID(id), name(medName), company(comp), price(medPrice), quantity(qty), expiryDate(expiry) {}

    // Update stock after selling
    bool updateStock(int soldQty) {
        if (soldQty <= quantity) {
            quantity -= soldQty; // selling means stock will be decreased
            return true;
        }
        return false;
    }

    // Add stock
    void addStock(int addQty) {
        quantity += addQty; // in stock the quantity will be increased
    }

    // if the quantity of any medicine is less than 10 then it will be considered as low stock
    bool isLowStock() const {
        if(quantity < 10){
            return true;
        }else{
            return false;
        }
    }

    // Checking expirary date of a medicine
    bool isExpired()const{
        return isDateExpired(expiryDate); // compare current date with expirary date
    }

    // display the console format of showing medicine
    void display()const{
        cout << left << setw(8)  << medID
         << left << setw(22) << name
         << left << setw(32) << company
         << right << setw(12) << fixed << setprecision(2) << price
         << right << setw(10) << quantity
         << right  << setw(14) << expiryDate
         << endl;
        if (isExpired()) {
            cout << " [EXPIRED]";
        } else if (isLowStock()) {
            cout << " [LOW STOCK]";
        }
        cout << endl;
    }


    // serializes the object into a CSV-style line
    //builds a single comma-separated string containing the member values and returns it
    // Serialize the strings
    string serialize() const {
        stringstream ss;

        // the << operator inserts each member value into the stream in that exact order
        //between each field a comma is inserted, producing a commaseparated line
        ss << medID << "," << name << "," << company << "," << price << "," << quantity << "," << expiryDate;
        return ss.str();
    }


    // static is used so that it can be called without creating an object
    // takes a string (previously created by serialize()) and converts it back into a Medicine object by extracting each field value from the string
    // Deserialize from string
    static Medicine deserialize(const string& data) {
        stringstream ss(data); // allows reading character-by-character from the string
        string token; // temporary string to hold each piece
        vector<string> tokens; // 

        // reads characters from ss until a comma is found
        while (getline(ss, token, ',')){
            tokens.push_back(token);
        }

        // there must be exactly 6 fields
        // prevents errors if the string is incomplete
        if (tokens.size() == 6){
            return Medicine(stoi(tokens[0]), tokens[1], tokens[2], stod(tokens[3]), stoi(tokens[4]), tokens[5]);
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

    // Overloading < operator for medicine
    bool operator<(const Medicine& other)const{
        return price < other.price;
    }

    // Overloading > operator for medicine
    bool operator>(const Medicine& other)const{
        return price > other.price;
    }

    // Overloaded + operator 
    Medicine operator+(const Medicine& other)const{
        if(medID == other.medID){
            Medicine temp = *this;
            temp.quantity += other.quantity;
            return temp;
        }
        return *this;
    }

    // Overloaded == operator
    bool operator==(const Medicine& other) const {
        return medID == other.medID;
    }


    // Setters
    void setName(const string& n) { name = n; }
    void setCompany(const string& c) { company = c; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }
    void setExpiryDate(const string& date) { expiryDate = date; }
};

class User{
protected:
    int ID;  // stores user id
    string name; // stores name
    string contact;
    bool loggedin; // log in validity
public:
    // Constructors
    User(int userID=0, string username="", string usercontact="") : ID(userID),name(username),contact(usercontact), loggedin(false) {}

    // Destructors
    ~User(){}

    // checing log in info
    bool login(int userId, const string& password) {
        if (userId == ID) {
            loggedin = true;
            cout << "\n✓ Login successful! Welcome, " << name << endl;
            return true;
        }
        return false;
    }

    // logout operation
    void logout() {
        loggedin = false;
        cout << "\n✓ Logged out successfully!" << endl;
    }

    // getters
    int getId() { return ID; }
    string getName() { return name; }
    string getContact() { return contact; }
    bool isLoggedIn() { return loggedin; }

};


class Customer{
private:
    int custID;  // stores customer ID
    string name; // stores name of the customer
    string phone;
    int purchaseCount; // For discount checking

public:
    // Constructor
    Customer(int id = 0, string custName = "", string custPhone = "", int purchases = 0) : custID(id), name(custName), phone(custPhone), purchaseCount(purchases) {}

    // Discount and purchasecount method
    void incrementPurchase(){
        ++(*this);
    }
    bool isEligibleForDiscount()const{
        return purchaseCount >= 5;
    }
    double getDiscountPercentage()const{
        if (purchaseCount >= 10) return 10.0; // 10% discount
        if (purchaseCount >= 5) return 5.0;  // 5% discount
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

    // Overloaded ++ operator
    Customer& operator++(){
        purchaseCount++;
        return *this;
    }

    // Overloaded < operator for customer class
    bool operator<(const Customer& other)const{
        return purchaseCount < other.purchaseCount;
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

// invoice is a bill or record generated whenever a sale or purchase takes place
class Invoice{
private: 
    int invoiceID;
    string customerName;
    string date;
    vector<pair<Medicine, int>> items; // Medicine and quantity
    double totalAmount; // total sales cost
    double discountAmount; // if there is any discount
    double finalAmount; // total sales cost after discount if have any
public:
    // Constructors
    Invoice(int id, const string& custName) : invoiceID(id), customerName(custName), totalAmount(0.0), discountAmount(0.0), finalAmount(0.0) {
        date = getCurrentDate(); // extracting current date
    }

    // Adding item to invoice
    void addItem(const Medicine& med, int qty) {
        items.push_back(make_pair(med, qty)); // aded medicine with quantity
        totalAmount += med.getPrice() * qty;
    }
    // Discount and generate bill
    void applyDiscount(double discountPercent) { // calculating discount here
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
            // writing with a format
            file << invoiceID << "," << customerName << "," << date << "," << totalAmount << "," << discountAmount << "," << (discountAmount > 0 ? finalAmount : totalAmount) << endl;
            file.close();
        }

    }

    // Getter
    double getFinalAmount() const{
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

        // create a string containing 60 dashes
        cout << string(60, '-') << endl;

        // auto is used to internally indicate the datatype of items vector
        for(const auto& item : items){
            Medicine med = item.first; // Medicine object
            int qty = item.second; // quantity of the medicine
            double subtotal = med.getPrice() * qty;

            // Showing the data
            cout << left << setw(20) << med.getName() << setw(10) << fixed << setprecision(2) << med.getPrice() << setw(10) << qty << setw(15) << subtotal << endl;
        }
        cout << string(60, '-') << endl;
        cout << right << setw(45) << "Total: $" << totalAmount << endl;

        // Showing discount price if there is have any
        if(discountAmount > 0){
            cout << right << setw(45) << "Discount: -$" << discountAmount << endl;
            cout << right << setw(45) << "Final Amount: $" << finalAmount << endl;
        }else{
            cout << right << setw(45) << "Final Amount: $" << totalAmount << endl;
        }

        // Thank you message
        cout << string(60, '=') << endl;
        cout << "\n      Thank you for your purchase!" << endl;
        cout << string(60, '=') << endl << endl;

    }
};

class Admin : public User {
private:
    // stores collection of all Medicine objects available in the pharmacy
    // stores collection of all Customer objects registered in the pharmacy

    vector<Medicine>* medicineInventory; // medicineInventory is a pointer to a vector<Medicine>
    vector<Customer>* customerList; // customerList is a pointer to a vector<Customer>

    void saveMedicinesToFile(){
        // Opens a file for writing 
        // if the file doesn’t exist, it will be created
        // if it exists, its content will be overwritten
        ofstream file("medicines.txt");

        if (file.is_open()){ // checks if the file was successfully opened.
            for (const auto& med : *medicineInventory){ // dereferences the pointer to access the actual vector of Medicine objects
                file << med.serialize() << endl;   // converts the Medicine object into a single string CSV-style
            }
            file.close();
        }
    }

public:
    // Constructor
    Admin(int userId, string userName, string userContact, vector<Medicine>* inventory, vector<Customer>* customers) : User(userId, userName, userContact), medicineInventory(inventory), customerList(customers) {}

    // Display Admin menu
    void display(){
        cout << "\n";
        cout << "\n" << endl;
        cout << "         ADMIN MENU                 " << endl;
        cout << "\n" << endl;
        cout << "1. Add Medicine" << endl;
        cout << "2. Remove Medicine" << endl;
        cout << "3. Update Medicine" << endl;
        cout << "4. View Inventory" << endl;
        cout << "5. View Reports" << endl;
        cout << "6. Check Expiry & Low Stock Alerts" << endl;
        cout << "7. Sort Medicines by Price" << endl;
        cout << "8. Restock Medicine" << endl;
        cout << "9. View Customer Loyalty Ranking" << endl;
        cout << "10. Logout" << endl;
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
        cin.ignore(); // ignore characters left in the input buffer

        // Checking if medicine is already exists 
        for (const auto& med : *medicineInventory) {
            if (med.getMedID() == id) {
                cout << "✗ Error: Medicine with ID " << id << " already exists!" << endl;
                return;
            }
        }

        // taking input
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
        saveMedicinesToFile(); // called saving method
    }


    // Remove Medicine
    void removeMedicine(){
        int id;
        cout << "\n--- Remove Medicine ---" << endl;
        cout << "Enter Medicine ID to remove: ";
        cin >> id;

        // Search medicine
        // mark for removal any medicine whose ID is matched
        // returns a iterator of that medicine if found or else returns a end iterator if not fount
        auto it = remove_if(medicineInventory->begin(), medicineInventory->end(), [id](const Medicine& med) { return med.getMedID() == id; });

        // Removing medicine
        if(it != medicineInventory->end()){
            medicineInventory->erase(it, medicineInventory->end());
            cout << "✓ Medicine removed successfully!" << endl;
            saveMedicinesToFile(); // saving the updated list after removal
        }else{
            cout << "✗ Medicine with ID " << id << " not found!" << endl;
        }
    }

    // Update medicine details
    void updateMedicine(){
        int id;
        cout << "\n--- Update Medicine ---" << endl;
        cout << "Enter Medicine ID to update: ";
        cin >> id;
        cin.ignore(); // ignore characters left in the input buffer

        bool found = false; 

        // const keyword is not used because medicine will be modified
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
                string tempStr; // storing name company and expirary date temporarily
                double tempPrice;
                int tempQty;

                // Selecting choices using switch
                switch (choice){
                    case 1:
                        cout << "Enter new name: ";
                        getline(cin, tempStr);
                        med.setName(tempStr); // seting new name using setter
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
                    case 6: // Updating all info at once
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
                saveMedicinesToFile(); // saving the updated medicine list back to file
                break;
            }
        }
        if (!found) {
            cout << "✗ Medicine with ID " << id << " not found!" << endl;
        }
    }

    // Viewing complete inventory
    // showing details of medicine
    void viewInventory()const{
        cout << "\n╔════════════════════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                           MEDICINE INVENTORY                                   ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════════════════════╝" << endl;

        if(medicineInventory->empty()){
            cout << "\nNo medicines in inventory!" << endl;
            return;
        }

        cout << "\n" 
         << left << setw(8)  << "ID"
         << left << setw(22) << "Name"        // slightly wider
         << left << setw(32) << "Company"     
         << right << setw(15) << "Price"      
         << right << setw(10) << "Quantity"
         << left  << setw(14) << "Expiry" 
         << endl;
        cout << string(95, '-') << endl;

        for(const auto& med : *medicineInventory){
            med.display(); // displaying for each medicine
        }

        cout << "\nTotal Medicines: " << medicineInventory->size() << endl;
    }

    // Viewing sales summary repo
    void viewReports()const{
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║         SALES REPORTS              ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;

        // input file stream
        // used to read data from files
        // opens the file in read mode
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

        while(getline(file, line)){ // reads the file line by line into the string line
            stringstream ss(line);
            string token;
            vector<string> tokens;

            // tokenizing the line
            // splits the line by commas into individual pieces
            while (getline(ss, token, ',')){ 
                tokens.push_back(token);
            }

            // ensures the line has exactly 6 fields
            // prevents errors if the line is malformed or missing data
            if(tokens.size() == 6){
                cout << left << setw(12) << tokens[0] << setw(20) << tokens[1] << setw(15) << tokens[2] << "$" << setw(14) << tokens[5] << endl;
                totalSales += stod(tokens[5]); // converts the total price (string) to a double
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

        // we want to just read data, no modify is needed, to ensure that const in used
        // showing all expired medicine if have any
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

        // showing low stock medicine if have any
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

    // For sorting medicine (< and > overloaded used for medicine)
    void sortMedicinesByPrice(){
        if(medicineInventory->empty()){
            cout << "\nNo medicines in inventory!" << endl;
            return;
        }

        cout << "\n--- Sort Medicines by Price ---" << endl;
        cout << "1. Sort by Price (Low to High)" << endl;
        cout << "2. Sort by Price (High to Low)" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();  // // ignore characters left in the input buffer

        vector<Medicine> sortedList = *medicineInventory; // temporary list initialized

        // Overloaded operator is used here
        if(choice == 1){
            sort(sortedList.begin(), sortedList.end()); // sort function
            cout << "\n✓ Medicines sorted by price (Low to High):" << endl;
        }else if(choice == 2){ // uses lambda function
            sort(sortedList.begin(), sortedList.end(), [](const Medicine& a, const Medicine& b){ return a > b; });
            cout << "\n✓ Medicines sorted by price (High to Low):" << endl;
        }else{
            cout << "Invalid choice!" << endl;
            return;
        }

        cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << endl;
        cout << string(85, '-') << endl;

        // showing the sorted list 
        for(const auto& med : sortedList){ // uses const so that no modification is allowed
            cout << left << setw(8) << med.getMedID() << setw(20) << med.getName() << setw(15) << med.getCompany() << setw(10) << fixed << setprecision(2) << med.getPrice() << setw(10) << med.getQuantity() << setw(12) << med.getExpiryDate() << endl;
        }

    }

    // For restocking (Overloaded the + operator)
    void restockMedicine(){ // Restocking means create new quantity for a medicine
        int id, addQty;

        cout << "\n--- Restock Medicine ---" << endl;
        cout << "Enter Medicine ID to restock: ";
        cin >> id;
        cin.ignore(); // ignore characters left in the input buffer

        bool found = false;

        for(auto& med : *medicineInventory){
            if(med.getMedID() == id){
                found = true;
                cout << "\nCurrent Stock: " << med.getQuantity() << " units" << endl;
                cout << "Enter quantity to add: ";
                cin >> addQty;
                cin.ignore();

                // restocked medicine
                Medicine additionalStock(id, med.getName(), med.getCompany(), med.getPrice(), addQty, med.getExpiryDate());
                Medicine restocked = med + additionalStock; // usage overloaded operator
                med = restocked;

                cout << "✓ Medicine restocked successfully!" << endl;
                cout << "New Stock: " << med.getQuantity() << " units" << endl;
                saveMedicinesToFile(); // saved the restocked medicines
                break;
            }
        }

        if(!found){
            cout << "✗ Medicine with ID " << id << " not found!" << endl;
        }
    }

    void viewCustomerLoyaltyRanking()const{
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║   CUSTOMER LOYALTY RANKING         ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;

        if(customerList->empty()){
            cout << "\nNo customers in database!" << endl;
            return;
        }

        vector<Customer> sortedCustomers = *customerList; // temporary list for soting
        //
        // uses lambda function
        sort(sortedCustomers.begin(), sortedCustomers.end(), [](const Customer& a, const Customer& b){ return !(a < b); });

        cout << "\n" << left << setw(8) << "Rank" << setw(12) << "Cust ID" << setw(20) << "Name" << setw(15) << "Phone" << setw(12) << "Purchases" << "Discount" << endl;
        cout << string(85, '-') << endl;

        int rank = 1;
        for(const auto& cust : sortedCustomers){ // we don't allow modification so const is used
            cout << left << setw(8) << rank++ << setw(12) << cust.getCustID() << setw(20) << cust.getName() << setw(15) << cust.getPhone() << setw(12) << cust.getPurchaseCount() << cust.getDiscountPercentage() << "%" << endl;
        }
        cout << "\nTotal Customers: " << customerList->size() << endl;

    }


};

// Handles Medicine sells and customers interaction
class Pharmacist : public User{
private:
    vector<Medicine>* medicineInventory; // a pointer to a vector<Medicine>
    vector<Customer>* customerList; // a pointer to a vector<Customer>
    // collection of all Medicine objects available in the pharmacy
    // collection of all Customer objects registered in the pharmacy

    int invoiceCounter; // count the number of invoices

    // Save medicines to file
    void saveMedicinesToFile()const{
        //output file stream
        /* 
        Opens a file for writing 
        if the file doesn’t exist, it will be created
        if it exists, its content will be overwritten
        */
        ofstream file("medicines.txt");
        if (file.is_open()){
            for (const auto& med : *medicineInventory) {
                // CSV is done by serialize() method
                file << med.serialize() << endl; // writing in a CSV format 
            }
            file.close();
        }
    }

    // Saving Customer information in file
    void saveCustomersToFile()const{
        //output file stream
        /* 
        Opens a file for writing 
        if the file doesn’t exist, it will be created
        if it exists, its content will be overwritten
        */
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
        // used to read the last saved invoice number so that the program can continue numbering invoices sequentially.

        // input file stream

        ifstream file("invoice_counter.txt");
        if(file.is_open()){
            file >> invoiceCounter; // reads the integer value from the file and stores it in invoiceCounter
            file.close();
        }
    }

    // Save invoice to file
    void saveInvoiceCounter()const{
        //output file stream
        /* 
        Opens a file for writing 
        if the file doesn’t exist, it will be created
        if it exists, its content will be overwritten
        */
        ofstream file("invoice_counter.txt");
        if(file.is_open()){
            file << invoiceCounter; // writes the value of invoiceCounter as text into the file
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
        cout << "\n" << endl;
        cout << "       PHARMACIST MENU              " << endl;
        cout << "\n" << endl;
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
        Customer* currentCustomer = nullptr; // declare a temporary empty customer so that we can directly push back to customer list

        cout << "\n--- Sell Medicine ---" << endl;
        cout << "Is this an existing customer? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // ignore characters left in the input buffer

        // If it is an existing cutomer
        if(choice == 'y' || choice == 'Y'){
            cout << "Enter Customer Phone: ";
            getline(cin, custPhone); // For searching

            // Searching for existing customer
            for(auto& cust : *customerList){
                if(cust.getPhone() == custPhone){ // if phone number matched
                    isExistingCustomer = true;
                    currentCustomer = &cust; // geting customer info into the temporary variable
                    custID = cust.getCustID();
                    custName = cust.getName();
                    cout << "✓ Customer found: " << custName << endl;
                    break;
                }
            }

            // if not a existing customer
            if (!isExistingCustomer) {
                cout << "✗ Customer not found. Creating new customer..." << endl;
            }
        }

        // Creating new customers if not existed
        if(!isExistingCustomer){
            custID = customerList->size() + 1; // customers are numbered 1,2,3,....
            cout << "Enter Customer Name: ";
            getline(cin, custName);
            cout << "Enter Customer Phone: ";
            getline(cin, custPhone);

            // Creating new customer object
            Customer newCust(custID, custName, custPhone, 0);
            customerList->push_back(newCust); // push it to customer list
            currentCustomer = &customerList->back(); // returns the reference of the last element
            // as the currently added customer is in the last element of the vector
            
            saveCustomersToFile(); // saving the updated customer list
        }

        // Create Invoice
        Invoice invoice(invoiceCounter++, custName); // saving invoice with invoice number and customer name

        // Add medicines to invoice
        char addMore = 'y';

        // Medicine addition to customer
        while(addMore == 'y' || addMore == 'Y'){
            int medID, qty;

            cout << "\nEnter Medicine ID: ";
            cin >> medID;
            cin.ignore();

            bool found = false;
            for(auto& med : *medicineInventory){
                if(med.getMedID() == medID){
                    found = true;

                    // Expiry Checking
                    if (med.isExpired()) {
                        cout << "✗ Error: This medicine has expired!" << endl;
                        break;
                    }

                    cout << "Medicine: " << med.getName() << endl;
                    cout << "Available Quantity: " << med.getQuantity() << endl;
                    cout << "Price: $" << med.getPrice() << endl;
                    cout << "Enter Quantity to sell: ";
                    cin >> qty; // take the quantity of how much a customer want

                    // showing error message for low stock and invalid quantity
                    if(qty > med.getQuantity()){
                        cout << "✗ Error: Insufficient stock!" << endl;
                    }else if (qty <= 0){
                        cout << "✗ Error: Invalid quantity!" << endl;
                    }else{
                        med.updateStock(qty); // update the stock to new quantity 
                        invoice.addItem(med, qty); // update item in the invoice
                        cout << "✓ Added to invoice!" << endl;
                    }
                    break;
                }
                
            }
            //
            // Error message
            if(!found){
                cout << "✗ Medicine with ID " << medID << " not found!" << endl;
            }

            // If more medicine in needed loop will continue 
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
        cin.ignore(); // // ignore characters left in the input buffer

        string searchTerm;
        bool found = false;

        if(choice == 1){
            cout << "Enter Medicine Name: ";
            getline(cin, searchTerm); // taking medicine name or keyword of it

            cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << endl;
            cout << string(75, '-') << endl;

            for (const auto& med : *medicineInventory) {
                if (med.getName().find(searchTerm) != string::npos){ // if any keyword is found related to saved medicine then it will return the iterator of it or else no position
                    med.display();
                    found = true;
                }
            }
        }else if(choice == 2){
            cout << "Enter Company Name: ";
            getline(cin, searchTerm); // taking company name and keyword of it

            cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(10) << "Price" << setw(10) << "Quantity" << setw(12) << "Expiry" << endl;
            cout << string(75, '-') << endl;

            for(const auto& med : *medicineInventory){
                if (med.getCompany().find(searchTerm) != string::npos){ // // if any keyword is found related to saved medicine then it will return the iterator of it or else no position
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
    void checkExpiry()const{
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║      EXPIRY CHECK REPORT           ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;

        bool hasExpired = false;

        cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Company" << setw(12) << "Expiry Date" << endl;
        cout << string(55, '-') << endl;

        // SHow the expired medicines
        for (const auto& med : *medicineInventory) {
            if (med.isExpired()) {
                hasExpired = true;
                cout << left << setw(8) << med.getMedID() << setw(20) << med.getName() << setw(15) << med.getCompany() << setw(12) << med.getExpiryDate() << endl;
            }
        }

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

        // Showing the medicine
        for(const auto& med : *medicineInventory){
            med.display();
        }

        cout << "\nTotal Medicines: " << medicineInventory->size() << endl;
    }


};

// combination of all classes happen here 
class PharmacySystem{
private:
    vector<Medicine> medicineInventory;
    vector<Customer> customerList;
    Admin* admin;
    Pharmacist* pharmacist;


    // display the main menu after running 
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
        cin.ignore(); // ignore characters left in the input buffer
        cout << "Enter Password: ";
        getline(cin, password);

        // Brute force authentication for admin log in 
        if(admin->login(id, password)){
            adminMenu(); // menu selection method
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
            cin.ignore(); // ignore characters left in the input buffer

            // selecting method by choicing 
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
                    admin->sortMedicinesByPrice();
                    break;
                case 8:
                    admin->restockMedicine();
                    break;
                case 9:
                    admin->viewCustomerLoyaltyRanking();
                    break;
                case 10:
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
        cin.ignore();  // // ignore characters left in the input buffer
        cout << "Enter Password: ";
        getline(cin, password);

        // Brute Force authentication for pharmacist log in
        if(pharmacist->login(id, password)){
            pharmacistMenu(); // log in menu operation 
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
            cin.ignore(); // ignore characters left in the input buffer

            // choicing method by selecting switch cases
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
        // input file stream


        ifstream file("medicines.txt");
        if (file.is_open()){
            string line;
            while (getline(file, line)){ // reads one line at a time from the file
                Medicine med = Medicine::deserialize(line); // converts the csv file into medicine object 
                if (med.getMedID() != 0) {
                    medicineInventory.push_back(med);
                }
            }
            file.close();
        }
    }
    
    // Load Customers info from file
    void loadCustomersFromFile(){
        // input file stream 
        ifstream file("customers.txt");
        if (file.is_open()){
            string line;
            while (getline(file, line)){
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
        // Admin info
        admin = new Admin(23070, "CSE_23", "015", &medicineInventory, &customerList);
        
        // Pharmacist info 
        pharmacist = new Pharmacist(2307090, "Ritovash Chanda", "01615058161", &medicineInventory, &customerList);


        loadMedicinesFromFile(); // load medicine to medicine inventory
        loadCustomersFromFile(); // load customers info to customerlist

    }

    // main menu running option 
    // loop through the choices and methods
    void run(){
        while(true){
            displayMainMenu();
            int choice;
            cin >> choice;
            cin.ignore();  // ignore characters left in the input buffer

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
        // deleting the pointers
        delete admin;  //
        delete pharmacist;
    }

};


// main function to control the whole 
int main(){
    cout << "\n";

    cout << "         WELCOME TO PHARMACY MANAGEMENT SYSTEM          " << endl;
    cout << "                                                        " << endl;
    cout << "\n";

    PharmacySystem system;
    system.run();
    return 0;
}