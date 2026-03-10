#include <iostream>
using namespace std;

int main() {
    string username, password;
    int kesempatan = 0;

    // ===== LOGIN =====
    while (kesempatan < 3) {
        cout << "===== LOGIN =====" << endl;
        cout << "Masukkan Nama     : ";
        cin >> username;
        cout << "Masukkan Password (3 digit NIM): ";
        cin >> password;

        if (username == "arul" && password == "030") { // ganti sesuai kebutuhan
            cout << "Login Berhasil!\n\n";
            break;
        } else {
            cout << "Login Salah!\n\n";
            kesempatan++;
        }
    }

    if (kesempatan == 3) {
        cout << "Anda salah 3 kali. Program berhenti.";
        return 0;
    }

    // ===== MENU =====
    int pilihan;
    float nilai;

    do {
        cout << "\n==============================" << endl;
        cout << "      PROGRAM KONVERSI" << endl;
        cout << "==============================" << endl;
        cout << "1. Meter > Kilometer & Centimeter" << endl;
        cout << "2. Kilometer > Meter & Centimeter" << endl;
        cout << "3. Centimeter > Meter & Kilometer" << endl;
        cout << "4. Keluar" << endl;
        cout << "==============================" << endl;
        cout << "Pilih Menu : ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                cout << "Masukkan nilai (Meter): ";
                cin >> nilai;
                cout << "Hasil: " << nilai/1000 << " km dan "
                     << nilai*100 << " cm" << endl;
                break;

            case 2:
                cout << "Masukkan nilai (Kilometer): ";
                cin >> nilai;
                cout << "Hasil: " << nilai*1000 << " m dan "
                     << nilai*100000 << " cm" << endl;
                break;

            case 3:
                cout << "Masukkan nilai (Centimeter): ";
                cin >> nilai;
                cout << "Hasil: " << nilai/100 << " m dan "
                     << nilai/100000 << " km" << endl;
                break;

            case 4:
                cout << "Program selesai." << endl;
                break;

            default:
                cout << "Menu tidak tersedia!" << endl;
        }

    } while (pilihan != 4);

    return 0;
}
