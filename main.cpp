#include <iostream>
#include <string>
using namespace std;

//  CONSTANTS & STRUCTURE

const int MAX_MEMBERS = 100;

struct Member {
    int    id;
    string name;
    int    age;
    string phone;
    string membershipType;
    float  fee;
    
};

//  GLOBAL DATA

Member members[MAX_MEMBERS];
int memberCount = 7;
int nextId = 1008;

void loadSampleData() {
    members[0] = {1001, "Ali",    22, "03001234567", "Basic",    2000.0};
    members[1] = {1002, "Sara",   25, "03011234567", "Standard", 3500.0};
    members[2] = {1003, "Zohaib", 28, "03021234567", "Premium",  5500.0};
    members[3] = {1004, "Nabeel", 30, "03031234567", "Basic",    2000.0};
    members[4] = {1005, "Fatima", 20, "03041234567", "Standard", 3500.0};
    members[5] = {1006, "Aliza",  19, "03051234567", "Premium",  5500.0};
    members[6] = {1007, "Wasay",  24, "03061234567", "Basic",    2000.0};
}

//  HELPER FUNCTIONS

float getFee(string type) {
    if (type == "Basic")    return 2000.0;
    if (type == "Standard") return 3500.0;
    if (type == "Premium")  return 5500.0;
    return 0.0;
}

int findMemberById(int id) {
    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id)
            return i;
    }
    return -1;
}

int readId() {
    int id;
    while (true) {
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid ID. Please enter a number: ";
        } else {
            break;
        }
    }
    return id;
}

string normalizeType(string type) {
    type[0] = toupper(type[0]);
    for (int i = 1; i < type.length(); i++)
        type[i] = tolower(type[i]);
    return type;
}

bool isValidName(string name) {
    if (name.length() < 3) {
        cout << "  [!] Name must be at least 3 characters." << endl;
        return false;
    }
    for (int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            cout << "  [!] Name must contain letters only." << endl;
            return false;
        }
    }
    return true;
}

bool isValidAge(int age) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  [!] Age must be a number." << endl;
        return false;
    }
    if (age < 16 || age > 80) {
        cout << "  [!] Age must be between 16 and 80." << endl;
        return false;
    }
    return true;
}

bool isValidPhone(string phone) {
    if (phone.length() != 11) {
        cout << "  [!] Phone must be exactly 11 digits." << endl;
        return false;
    }
    for (int i = 0; i < phone.length(); i++) {
        if (!isdigit(phone[i])) {
            cout << "  [!] Phone must contain numbers only." << endl;
            return false;
        }
    }
    return true;
}

bool isValidType(string type) {
    type = normalizeType(type);
    if (type != "Basic" && type != "Standard" && type != "Premium") {
        cout << "  [!] Type must be Basic, Standard, or Premium." << endl;
        return false;
    }
    return true;
}

// 1. ADD MEMBER

void addMember() {
    cout << "\n===== ADD NEW MEMBER =====" << endl;

    if (memberCount >= MAX_MEMBERS) {
        cout << "Member list is full!" << endl;
        return;
    }

    Member m;
    m.id = nextId++;

    // Name
    do {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, m.name);
    } while (!isValidName(m.name));

    // Age
    do {
        cout << "Enter Age: ";
        cin >> m.age;
    } while (!isValidAge(m.age));

    // Phone
    do {
        cout << "Enter Phone: ";
        cin >> m.phone;
    } while (!isValidPhone(m.phone));

    // Membership Type
    do {
        cout << "Enter Membership Type (Basic / Standard / Premium): ";
        cin >> m.membershipType;
    } while (!isValidType(m.membershipType));
    m.membershipType = normalizeType(m.membershipType);

    m.fee = getFee(m.membershipType);
    members[memberCount] = m;
    memberCount++;

    cout << "\nMember added successfully! ID: " << m.id << endl;
}

//  2. VIEW ALL MEMBERS

void viewAllMembers() {
    cout << "\n===== ALL MEMBERS =====" << endl;

    if (memberCount == 0) {
        cout << "No members found." << endl;
        return;
    }

    for (int i = 0; i < memberCount; i++) {
        cout << "\nID      : " << members[i].id << endl;
        cout << "Name    : " << members[i].name << endl;
        cout << "Age     : " << members[i].age << endl;
        cout << "Phone   : " << members[i].phone << endl;
        cout << "Type    : " << members[i].membershipType << endl;
        cout << "Fee     : Rs. " << members[i].fee << endl;
        cout << "------------------------" << endl;
    }

    cout << "Total Members: " << memberCount << endl;
}

// 3. SEARCH MEMBER BY ID

void searchMember() {
    cout << "\n===== SEARCH MEMBER =====" << endl;

    int id;
    cout << "Enter Member ID: ";
    id = readId();

    int idx = findMemberById(id);

    if (idx == -1) {
        cout << "Member not found." << endl;
        return;
    }

    cout << "\nID      : " << members[idx].id << endl;
    cout << "Name    : " << members[idx].name << endl;
    cout << "Age     : " << members[idx].age << endl;
    cout << "Phone   : " << members[idx].phone << endl;
    cout << "Type    : " << members[idx].membershipType << endl;
    cout << "Fee     : Rs. " << members[idx].fee << endl;
}

// 4. UPDATE MEMBER

void updateMember() {
    cout << "\n===== UPDATE MEMBER =====" << endl;

    int id;
    cout << "Enter Member ID: ";
    id = readId();

    int idx = findMemberById(id);

    if (idx == -1) {
        cout << "Member not found." << endl;
        return;
    }

    // Name
    string newName;
    do {
        cout << "Current Name: " << members[idx].name << endl;
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, newName);
    } while (!isValidName(newName));
    members[idx].name = newName;

    // Age
    int newAge;
    do {
        cout << "Current Age: " << members[idx].age << endl;
        cout << "Enter New Age: ";
        cin >> newAge;
    } while (!isValidAge(newAge));
    members[idx].age = newAge;

    // Phone
    string newPhone;
    do {
        cout << "Current Phone: " << members[idx].phone << endl;
        cout << "Enter New Phone: ";
        cin >> newPhone;
    } while (!isValidPhone(newPhone));
    members[idx].phone = newPhone;

    // Membership Type
    string newType;
    do {
        cout << "Current Type: " << members[idx].membershipType << endl;
        cout << "Enter New Type (Basic / Standard / Premium): ";
        cin >> newType;
    } while (!isValidType(newType));
    members[idx].membershipType = normalizeType(newType);
    members[idx].fee = getFee(members[idx].membershipType);

    cout << "\nMember updated successfully!" << endl;
}

// 5. DELETE MEMBER

void deleteMember() {
    cout << "\n===== DELETE MEMBER =====" << endl;

    int id;
    cout << "Enter Member ID to delete: ";
    id = readId();

    int idx = findMemberById(id);

    if (idx == -1) {
        cout << "Member not found." << endl;
        return;
    }

    cout << "Are you sure you want to delete " << members[idx].name << "? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = idx; i < memberCount - 1; i++)
            members[i] = members[i + 1];
        memberCount--;
        cout << "Member deleted successfully." << endl;
    } else {
        cout << "Deletion cancelled." << endl;
    }
}

//  MAIN MENU

int main() {
    loadSampleData();
    int choice;

    do {
        cout << "\n=========================" << endl;
        cout << "   GYM MEMBERSHIP SYSTEM  " << endl;
        cout << "=========================" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. View All Members" << endl;
        cout << "3. Search Member by ID" << endl;
        cout << "4. Update Member" << endl;
        cout << "5. Delete Member" << endl;
        cout << "0. Exit" << endl;
        cout << "=========================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)      addMember();
        else if (choice == 2) viewAllMembers();
        else if (choice == 3) searchMember();
        else if (choice == 4) updateMember();
        else if (choice == 5) deleteMember();
        else if (choice == 0) cout << "Goodbye!" << endl;
        else cout << "Invalid choice. Try again." << endl;

    } while (choice != 0);

    return 0;
}
