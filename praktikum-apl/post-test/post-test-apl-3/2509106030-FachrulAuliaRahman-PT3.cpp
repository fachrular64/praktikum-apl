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

void TambahData(Penyewaan dataSewa[], int &jumlahData, int &nextId) {
    if (jumlahData < MAKS_DATA) {
        cout << "\n=== TAMBAH DATA PENYEWAAN ===\n";
        dataSewa[jumlahData].IdSewa = nextId;
        nextId++;

        cout << "Masukkan Nama Penyewa: ";
        getline(cin, dataSewa[jumlahData].NamaPenyewa);

        cout << "Masukkan Merek Powerbank: ";
        getline(cin, dataSewa[jumlahData].MerekPowerbank);

        cout << "Masukkan Durasi Sewa (Jam): ";
        cin >> dataSewa[jumlahData].DurasiJam;
        cin.ignore();

        jumlahData++;
        cout << ">>> Data berhasil ditambahkan! <<<\n";
    } else {
        cout << "Kapasitas data sudah penuh!\n";
    }
}

void LihatData(Penyewaan dataSewa[], int jumlahData) {
    if (jumlahData == 0) {
        cout << "\nBelum ada data penyewaan.\n";
        return;
    }
    
    cout << "\n=== DAFTAR PENYEWAAN POWER BANK ===\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << "ID Sewa         : " << dataSewa[i].IdSewa << "\n";
        cout << "Nama Penyewa    : " << dataSewa[i].NamaPenyewa << "\n";
        cout << "Merek Powerbank : " << dataSewa[i].MerekPowerbank << "\n";
        cout << "Durasi (Jam)    : " << dataSewa[i].DurasiJam << "\n";
        cout << "--------------------------------------\n";
    }
}

void LihatData(Penyewaan dataSewa[], int jumlahData, int indexTarget) {
    cout << "\n=== DETAIL DATA DITEMUKAN ===\n";
    cout << "ID Sewa         : " << dataSewa[indexTarget].IdSewa << "\n";
    cout << "Nama Penyewa    : " << dataSewa[indexTarget].NamaPenyewa << "\n";
    cout << "Merek Powerbank : " << dataSewa[indexTarget].MerekPowerbank << "\n";
    cout << "Durasi (Jam)    : " << dataSewa[indexTarget].DurasiJam << "\n";
    cout << "--------------------------------------\n";
}

int CariDataRekursif(Penyewaan dataSewa[], int jumlahData, int idTarget, int indexSekarang) {
    if (indexSekarang >= jumlahData) {
        return -1;
    }
    if (dataSewa[indexSekarang].IdSewa == idTarget) {
        return indexSekarang;
    }
    return CariDataRekursif(dataSewa, jumlahData, idTarget, indexSekarang + 1);
}

void UbahData(Penyewaan dataSewa[], int jumlahData) {
    LihatData(dataSewa, jumlahData);
    if (jumlahData == 0) return;

    int idTarget;
    cout << "\nMasukkan ID Penyewaan yang ingin diubah: ";
    cin >> idTarget;
    cin.ignore();

    int indexDitemukan = CariDataRekursif(dataSewa, jumlahData, idTarget, 0);

    if (indexDitemukan != -1) {
        cout << "\n=== UBAH DATA (ID: " << idTarget << ") ===\n";
        
        cout << "Nama Penyewa Baru (sebelumnya: " << dataSewa[indexDitemukan].NamaPenyewa << "): ";
        getline(cin, dataSewa[indexDitemukan].NamaPenyewa);

        cout << "Merek Powerbank Baru (sebelumnya: " << dataSewa[indexDitemukan].MerekPowerbank << "): ";
        getline(cin, dataSewa[indexDitemukan].MerekPowerbank);

        cout << "Durasi Sewa Baru (Jam) (sebelumnya: " << dataSewa[indexDitemukan].DurasiJam << "): ";
        cin >> dataSewa[indexDitemukan].DurasiJam;
        cin.ignore();

        cout << ">>> Data berhasil diubah! <<<\n";
    } else {
        cout << ">>> Data dengan ID tersebut tidak ditemukan! <<<\n";
    }
}

void HapusData(Penyewaan dataSewa[], int &jumlahData) {
    LihatData(dataSewa, jumlahData);
    if (jumlahData == 0) return;

    int idTarget;
    cout << "\nMasukkan ID Penyewaan yang ingin dihapus: ";
    cin >> idTarget;
    cin.ignore();

    int indexDitemukan = CariDataRekursif(dataSewa, jumlahData, idTarget, 0);

    if (indexDitemukan != -1) {
        for (int j = indexDitemukan; j < jumlahData - 1; j++) {
            dataSewa[j] = dataSewa[j + 1];
        }
        jumlahData--;
        cout << ">>> Data berhasil dihapus! <<<\n";
    } else {
        cout << ">>> Data dengan ID tersebut tidak ditemukan! <<<\n";
    }
}

int main() {
    Penyewaan dataSewa[MAKS_DATA];
    int jumlahData = 0;
    int nextId = 1;

    User penggunaSah;
    penggunaSah.Username = "Fachrul";
    penggunaSah.Password = "030";

    bool isLogin = false;
    int percobaanSisa = 3;
    string inputNama, inputNim;

    cout << "=== SISTEM PENYEWAAN POWER BANK ===\n";
    cout << "Silakan Login untuk melanjutkan.\n";

    while (percobaanSisa > 0 && !isLogin) {
        cout << "\nUsername (Nama) : ";
        getline(cin, inputNama);
        cout << "Password (NIM)  : ";
        getline(cin, inputNim);

        if (inputNama == penggunaSah.Username && inputNim == penggunaSah.Password) {
            isLogin = true;
            cout << ">>> Login Sukses! Selamat datang, " << penggunaSah.Username << ". <<<\n";
        } else {
            percobaanSisa--;
            cout << ">>> Username atau Password salah! <<<\n";
            if (percobaanSisa > 0) {
                cout << "Sisa percobaan login Anda: " << percobaanSisa << " kali\n";
            } else {
                cout << ">>> Anda telah gagal 3 kali. Program Berhenti. <<<\n";
                exit(0);
            }
        }
    }

    int pilihanMenu;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Data Penyewaan (Create)\n";
        cout << "2. Lihat Data Penyewaan (Read)\n";
        cout << "3. Cari Data Spesifik (Demo Overloading & Rekursif)\n";
        cout << "4. Ubah Data Penyewaan (Update)\n";
        cout << "5. Hapus Data Penyewaan (Delete)\n";
        cout << "6. Keluar\n";
        cout << "Pilih Menu (1-6): ";
        cin >> pilihanMenu;
        cin.ignore();

        switch (pilihanMenu) {
            case 1:
                TambahData(dataSewa, jumlahData, nextId);
                break;
            case 2:
                LihatData(dataSewa, jumlahData);
                break;
            case 3: {
                if (jumlahData == 0) {
                    cout << "\nBelum ada data penyewaan.\n";
                } else {
                    int idCari;
                    cout << "\nMasukkan ID Penyewaan yang ingin dicari: ";
                    cin >> idCari;
                    cin.ignore();
                    
                    int indexDitemukan = CariDataRekursif(dataSewa, jumlahData, idCari, 0);
                    if (indexDitemukan != -1) {
                        LihatData(dataSewa, jumlahData, indexDitemukan);
                    } else {
                        cout << ">>> Data dengan ID tersebut tidak ditemukan! <<<\n";
                    }
                }
                break;
            }
            case 4:
                UbahData(dataSewa, jumlahData);
                break;
            case 5:
                HapusData(dataSewa, jumlahData);
                break;
            case 6:
                cout << "Keluar dari sistem. Terima kasih!\n";
                break;
            default:
                cout << ">>> Pilihan tidak valid, silakan coba lagi. <<<\n";
        }
    } while (pilihanMenu != 6);

    return 0;
}