#ifndef POWERBANK_H
#define POWERBANK_H

#include <iostream>
#include <string>

using namespace std;

struct User {
    string Username;
    string Password;
};

struct Penyewaan {
    int IdSewa;
    string NamaPenyewa;
    string MerekPowerbank;
    int DurasiJam;
    int *ptrDurasi; 
};

// Class untuk Exception Handling
class RentalException {
private:
    string pesan;
public:
    RentalException(string p) {
        pesan = p;
    }
    string getPesan() {
        return pesan;
    }
};

#endif