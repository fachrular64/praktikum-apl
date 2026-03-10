#include <iostream>
#include <string>
#include <cstdlib>

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
};

const int MAKS_DATA = 100;
Penyewaan DataSewa[MAKS_DATA];
int JumlahData = 0;
int NextId = 1;

void TambahData() {
    if (JumlahData < MAKS_DATA) {
        cout << "\n=== TAMBAH DATA PENYEWAAN ===\n";
        DataSewa[JumlahData].IdSewa = NextId;
        NextId++;

        cout << "Masukkan Nama Penyewa: ";
        getline(cin, DataSewa[JumlahData].NamaPenyewa);

        cout << "Masukkan Merek Powerbank: ";
        getline(cin, DataSewa[JumlahData].MerekPowerbank);

        cout << "Masukkan Durasi Sewa (Jam): ";
        cin >> DataSewa[JumlahData].DurasiJam;
        cin.ignore();

        JumlahData++;
        cout << ">>> Data berhasil ditambahkan! <<<\n";
    } else {
        cout << "Kapasitas data sudah penuh!\n";
    }
}

void LihatData() {
    if (JumlahData == 0) {
        cout << "\nBelum ada data penyewaan.\n";
        return;
    }
    
    cout << "\n=== DAFTAR PENYEWAAN POWER BANK ===\n";
    for (int i = 0; i < JumlahData; i++) {
        cout << "ID Sewa         : " << DataSewa[i].IdSewa << "\n";
        cout << "Nama Penyewa    : " << DataSewa[i].NamaPenyewa << "\n";
        cout << "Merek Powerbank : " << DataSewa[i].MerekPowerbank << "\n";
        cout << "Durasi (Jam)    : " << DataSewa[i].DurasiJam << "\n";
        cout << "--------------------------------------\n";
    }
}

void UbahData() {
    LihatData();
    if (JumlahData == 0) return;

    int IdTarget;
    cout << "\nMasukkan ID Penyewaan yang ingin diubah: ";
    cin >> IdTarget;
    cin.ignore();

    bool Ketemu = false;
    for (int i = 0; i < JumlahData; i++) {
        if (DataSewa[i].IdSewa == IdTarget) {
            Ketemu = true;
            cout << "\n=== UBAH DATA (ID: " << IdTarget << ") ===\n";
            
            cout << "Nama Penyewa Baru (sebelumnya: " << DataSewa[i].NamaPenyewa << "): ";
            getline(cin, DataSewa[i].NamaPenyewa);

            cout << "Merek Powerbank Baru (sebelumnya: " << DataSewa[i].MerekPowerbank << "): ";
            getline(cin, DataSewa[i].MerekPowerbank);

            cout << "Durasi Sewa Baru (Jam) (sebelumnya: " << DataSewa[i].DurasiJam << "): ";
            cin >> DataSewa[i].DurasiJam;
            cin.ignore();

            cout << ">>> Data berhasil diubah! <<<\n";
            break;
        }
    }
    if (!Ketemu) {
        cout << ">>> Data dengan ID tersebut tidak ditemukan! <<<\n";
    }
}

void HapusData() {
    LihatData();
    if (JumlahData == 0) return;

    int IdTarget;
    cout << "\nMasukkan ID Penyewaan yang ingin dihapus: ";
    cin >> IdTarget;
    cin.ignore();

    bool Ketemu = false;
    for (int i = 0; i < JumlahData; i++) {
        if (DataSewa[i].IdSewa == IdTarget) {
            Ketemu = true;
            for (int j = i; j < JumlahData - 1; j++) {
                DataSewa[j] = DataSewa[j + 1];
            }
            JumlahData--;
            cout << ">>> Data berhasil dihapus! <<<\n";
            break;
        }
    }
    if (!Ketemu) {
        cout << ">>> Data dengan ID tersebut tidak ditemukan! <<<\n";
    }
}

int main() {
    User PenggunaSah;
    PenggunaSah.Username = "Fachrul";
    PenggunaSah.Password = "030";

    bool IsLogin = false;
    int PercobaanSisa = 3;
    string InputNama, InputNim;

    cout << "=== SISTEM PENYEWAAN POWER BANK ===\n";
    cout << "Silakan Login untuk melanjutkan.\n";

    while (PercobaanSisa > 0 && !IsLogin) {
        cout << "\nUsername (Nama) : ";
        getline(cin, InputNama);
        cout << "Password (NIM)  : ";
        getline(cin, InputNim);

        if (InputNama == PenggunaSah.Username && InputNim == PenggunaSah.Password) {
            IsLogin = true;
            cout << ">>> Login Sukses! Selamat datang, " << PenggunaSah.Username << ". <<<\n";
        } else {
            PercobaanSisa--;
            cout << ">>> Username atau Password salah! <<<\n";
            if (PercobaanSisa > 0) {
                cout << "Sisa percobaan login Anda: " << PercobaanSisa << " kali\n";
            } else {
                cout << ">>> Anda telah gagal 3 kali. Program Berhenti. <<<\n";
                exit(0);
            }
        }
    }

    int PilihanMenu;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Data Penyewaan (Create)\n";
        cout << "2. Lihat Data Penyewaan (Read)\n";
        cout << "3. Ubah Data Penyewaan (Update)\n";
        cout << "4. Hapus Data Penyewaan (Delete)\n";
        cout << "5. Keluar\n";
        cout << "Pilih Menu (1-5): ";
        cin >> PilihanMenu;
        cin.ignore();

        switch (PilihanMenu) {
            case 1:
                TambahData();
                break;
            case 2:
                LihatData();
                break;
            case 3:
                UbahData();
                break;
            case 4:
                HapusData();
                break;
            case 5:
                cout << "Keluar dari sistem. Terima kasih!\n";
                break;
            default:
                cout << ">>> Pilihan tidak valid, silakan coba lagi. <<<\n";
        }
    } while (PilihanMenu != 5);

    return 0;
}