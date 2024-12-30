#include<iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Hotel {
    int RoomID{};
    string CustomerName,BookingDate,price;


    void display() const {
        cout << "ID:" << RoomID << "\n Name:" << CustomerName << "\nDate:" << BookingDate << "\nPrice: $" << price
             << "\n\n";
    }

};

void BookRoom();
void readBookings();
void updateBooking();
void cancelBooking();

vector<Hotel> loadBookings();
void saveBookings(const vector<Hotel>& rooms);


const string filename ="bookings.txt";

int main() {
    int choice;

    do{
        cout<<"\n------HOTEL MANAGEMENT----\n";
        cout<<"1.Book a Room\n";
        cout<<"2.Read Bookings\n";
        cout<<"3.update Bookings\n";
        cout<<"4.Cancel Bookings\n";
        cout<<"5.Exit\n";
        cout<<"Enter the choice:";
        cin>>choice;

        switch (choice) {
            case 1:
                BookRoom();
                break;
            case 2:
                readBookings();
                break;
            case 3:
                updateBooking();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                cout<<"Exiting...........\n";
                break;
        }
    } while (choice !=5);
    return 0;
}

void BookRoom() {
    vector<Hotel> rooms = loadBookings();
    Hotel h;

    cout<<"Enter the Room ID:";
    cin >>h.RoomID;
    cin.ignore();
    cout<<"Enter the Customer Name:";
    getline(cin, h.CustomerName);
    cout<<"Enter the date of booking:";
    getline(cin,h.BookingDate);
    cout<<"Enter the Price of room:";
    getline(cin,h.price);

    rooms.push_back(h);
    saveBookings(rooms);
    cout<<"Booking added successfully!\n";
}

void readBookings() {
    vector<Hotel> rooms =loadBookings();

    if(rooms.empty()) {
        cout<<"No Bookings found.\n";
    }else{
        cout<<"\n----Customers List----";
        for(const auto& h:rooms) {
            h.display();
        }
    }
}

void updateBooking() {
    vector<Hotel> rooms =loadBookings();
    int ID;
    bool found =false;

    cout<<"Enter Room ID to update:";
    cin>>ID;

    for (auto& h : rooms) {
        if (h.RoomID == ID) {
            found=true;
            cin.ignore();
            cout<<"Enter  Customer's New Name:";
            getline(cin,h.CustomerName);
            cout<<"Enter the new date of the date:";
            getline(cin, h.BookingDate);
            cout<<"Enter the new price of room:";
            getline(cin,h.price);

            saveBookings(rooms);
            cout<<"Booking successfully updated!\n";
            break;
        }
    }
    if (!found) {
        cout<<"Booking with ID"<<ID<<"not found.\n";
    }
}
void cancelBooking() {
    vector<Hotel> rooms =loadBookings();
    int ID;
    bool found =false;

    cout<<"Enter Room ID to cancel:";
    cin>>ID;

    for (auto it =rooms.begin(); it !=rooms.end(); ++it) {
        if (it->RoomID == ID) {
            found = true;
            rooms.erase(it);
            saveBookings(rooms);
            cout<<"Rooms booking cancelled!..\n";
            break;
        }
    }if (!found) {
        cout<<"Room with ID"<<ID<<"not found.\n";
    }
}
vector<Hotel> loadBookings() {
    vector<Hotel> rooms;
    ifstream file(filename);
    if (file.is_open()) {
        Hotel h;
        while(file>>h.RoomID) {
            file.ignore();
            getline(file, h.CustomerName);
            getline(file,h.BookingDate);
            getline(file, h.price);
            rooms.push_back(h);
        }
        file.close();
    }
    return rooms;
}
void saveBookings(const vector<Hotel>& rooms) {
    ofstream  file(filename);
    if (file.is_open()) {
        for (const auto& h :rooms) {
            file << h.RoomID << "\n";
            file <<h.CustomerName<<"\n";
            file<<h.BookingDate<<"\n";
            file<<h.price<<"\n";
        }
        file.close();
    }else {
        cout<<"Error opening file for saving bookings.\n";
    }
}