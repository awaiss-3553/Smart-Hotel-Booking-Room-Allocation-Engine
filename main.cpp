#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Abstract Base Class
class Room {
protected:
    int roomNumber;
    string guestName;
    int stayDays;
    double baseRatePerNight;

public:
    static int totalRoomsBooked;
    static double totalRevenueGenerated;

    Room(int rNo, string guest, int days, double rate) {
        roomNumber = rNo;
        guestName = guest;
        stayDays = days;
        baseRatePerNight = rate;
        totalRoomsBooked++;
    }

    // Pure Virtual Functions
    virtual double calculateFinalBill() = 0;
    virtual void printInvoice() = 0;

    virtual ~Room() {} // Virtual Destructor
};

// Static Members Initialization
int Room::totalRoomsBooked = 0;
double Room::totalRevenueGenerated = 0.0;

// Derived Class 1: Standard Room (Flat rate + 5% service tax)
class StandardRoom : public Room {
public:
    StandardRoom(int rNo, string guest, int days)
        : Room(rNo, guest, days, 5000.0) {} // 5,000 PKR per night

    double calculateFinalBill() override {
        double subtotal = baseRatePerNight * stayDays;
        double tax = subtotal * 0.05; // 5% service tax
        return subtotal + tax;
    }

    void printInvoice() override {
        double total = calculateFinalBill();
        cout << "\n--- [Standard Room Invoice] ---" << endl;
        cout << "Room No: " << roomNumber << " | Guest: " << guestName << endl;
        cout << "Stay Duration: " << stayDays << " Nights @ " << baseRatePerNight << " PKR/night" << endl;
        cout << "Taxes (5%): " << (baseRatePerNight * stayDays * 0.05) << " PKR" << endl;
        cout << "Total Bill: " << total << " PKR" << endl;
    }
};

// Derived Class 2: Deluxe Suite (Luxury rate + Complimentary Breakfast + 16% Govt Tax)
class DeluxeSuite : public Room {
private:
    bool includesAirportShuttle;

public:
    DeluxeSuite(int rNo, string guest, int days, bool shuttle)
        : Room(rNo, guest, days, 15000.0), includesAirportShuttle(shuttle) {} // 15,000 PKR per night

    double calculateFinalBill() override {
        double subtotal = baseRatePerNight * stayDays;
        double tax = subtotal * 0.16; // 16% sales tax
        double shuttleFee = includesAirportShuttle ? 3000.0 : 0.0;
        return subtotal + tax + shuttleFee;
    }

    void printInvoice() override {
        double total = calculateFinalBill();
        cout << "\n--- [Deluxe Suite Invoice (VIP Perks)] ---" << endl;
        cout << "Room No: " << roomNumber << " | Guest: " << guestName << endl;
        cout << "Stay Duration: " << stayDays << " Nights @ " << baseRatePerNight << " PKR/night" << endl;
        cout << "Luxury Amenities: Complimentary Buffet Breakfast Included" << endl;
        if (includesAirportShuttle) {
            cout << "Airport Shuttle Service: 3000.00 PKR" << endl;
        }
        cout << "Govt Luxury Tax (16%): " << (baseRatePerNight * stayDays * 0.16) << " PKR" << endl;
        cout << "Total Bill: " << total << " PKR" << endl;
    }
};

int main() {
    cout << fixed << setprecision(2);

    // Polymorphic Collection via Base Class Pointers
    Room* reservations[2];

    reservations[0] = new StandardRoom(104, "Nauman", 3);
    reservations[1] = new DeluxeSuite(501, "Dr. Tariq", 2, true);

    cout << "=== Hotel Front Desk System ===" << endl;

    // Process invoices dynamically and compute total revenue
    for (int i = 0; i < 2; i++) {
        reservations[i]->printInvoice();
        Room::totalRevenueGenerated += reservations[i]->calculateFinalBill();
    }

    cout << "\n======================================" << endl;
    cout << "Total Rooms Booked Today: " << Room::totalRoomsBooked << endl;
    cout << "Total Revenue Collected:  " << Room::totalRevenueGenerated << " PKR" << endl;
    cout << "======================================" << endl;

    // Memory Cleanup
    for (int i = 0; i < 2; i++) {
        delete reservations[i];
    }

    return 0;
}
