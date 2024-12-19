#include<iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Hotel {
    int RoomID;
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


