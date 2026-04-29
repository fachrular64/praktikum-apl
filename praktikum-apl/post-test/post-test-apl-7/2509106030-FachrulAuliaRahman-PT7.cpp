#include <iostream>
#include <string>
#include <cstdlib>
#include <limits> // Tambahan untuk library eksternal (PT7)
#include "powerbank.h" // Tambahan library buatan sendiri (PT7)

using namespace std;

const int MAKS_DATA = 100;

void TambahData(Penyewaan dataSewa[], int *jumlahData, int *nextId) {
    if (*jumlahData < MAKS_DATA) {
        cout << "\n=== TAMBAH DATA PENYEWAAN ===\n";
        
        dataSewa[*jumlahData].IdSewa = *nextId;
        (*nextId)++;

        cout << "Masukkan Nama Penyewa: ";
        getline(cin, dataSewa[*jumlahData].NamaPenyewa);

        cout << "Masukkan Merek Powerbank: ";
        getline(cin, dataSewa[*jumlahData].MerekPowerbank);

        cout << "Masukkan Durasi Sewa (Jam): ";
        cin >> dataSewa[*jumlahData].DurasiJam;
        cin.ignore();

        dataSewa[*jumlahData].ptrDurasi = &dataSewa[*jumlahData].DurasiJam;

        (*jumlahData)++;
        cout << ">>> Data berhasil ditambahkan! <<<\n";
    } else {
        cout << "Kapasitas data sudah penuh!\n";
    }
}

void LihatData(Penyewaan dataSewa[], int jumlahData) {
    if (jumlahData == 0) {
        // Diganti menggunakan throw untuk PT7
        throw RentalException("Belum ada data penyewaan.");
    }
    
    cout << "\n=== DAFTAR PENYEWAAN POWER BANK ===\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << "ID Sewa         : " << dataSewa[i].IdSewa << "\n";
        cout << "Nama Penyewa    : " << dataSewa[i].NamaPenyewa << "\n";
        cout << "Merek Powerbank : " << dataSewa[i].MerekPowerbank << "\n";
        cout << "Durasi (Jam)    : " << *(dataSewa[i].ptrDurasi) << "\n";
        cout << "--------------------------------------\n";
    }
}

void LihatData(Penyewaan dataSewa[], int jumlahData, int indexTarget) {
    cout << "\n=== DETAIL DATA DITEMUKAN ===\n";
    cout << "ID Sewa         : " << dataSewa[indexTarget].IdSewa << "\n";
    cout << "Nama Penyewa    : " << dataSewa[indexTarget].NamaPenyewa << "\n";
    cout << "Merek Powerbank : " << dataSewa[indexTarget].MerekPowerbank << "\n";
    cout << "Durasi (Jam)    : " << *(dataSewa[indexTarget].ptrDurasi) << "\n";
    cout << "--------------------------------------\n";
}

void SortNamaDescending(Penyewaan dataSewa[], int jumlahData) {
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (dataSewa[j].NamaPenyewa < dataSewa[j + 1].NamaPenyewa) {
                Penyewaan temp = dataSewa[j];
                dataSewa[j] = dataSewa[j + 1];
                dataSewa[j + 1] = temp;
                
                dataSewa[j].ptrDurasi = &dataSewa[j].DurasiJam;
                dataSewa[j + 1].ptrDurasi = &dataSewa[j + 1].DurasiJam;
            }
        }
    }
    cout << ">>> Data berhasil diurutkan berdasarkan Nama (Descending) dengan Bubble Sort! <<<\n";
}

void SortDurasiAscending(Penyewaan dataSewa[], int jumlahData) {
    for (int i = 0; i < jumlahData - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if (dataSewa[j].DurasiJam < dataSewa[minIndex].DurasiJam) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Penyewaan temp = dataSewa[i];
            dataSewa[i] = dataSewa[minIndex];
            dataSewa[minIndex] = temp;
            
            dataSewa[i].ptrDurasi = &dataSewa[i].DurasiJam;
            dataSewa[minIndex].ptrDurasi = &dataSewa[minIndex].DurasiJam;
        }
    }
    cout << ">>> Data berhasil diurutkan berdasarkan Durasi Sewa (Ascending) dengan Selection Sort! <<<\n";
}

void SortIdAscending(Penyewaan dataSewa[], int jumlahData) {
    for (int i = 1; i < jumlahData; i++) {
        Penyewaan key = dataSewa[i];
        int j = i - 1;
        while (j >= 0 && dataSewa[j].IdSewa > key.IdSewa) {
            dataSewa[j + 1] = dataSewa[j];
            dataSewa[j + 1].ptrDurasi = &dataSewa[j + 1].DurasiJam;
            j = j - 1;
        }
        dataSewa[j + 1] = key;
        dataSewa[j + 1].ptrDurasi = &dataSewa[j + 1].DurasiJam;
    }
}

// ==============================================================================
// HIGHLIGHT POST-TEST 6: FITUR SEARCHING DENGAN POINTER SEBAGAI PARAMETER
// ==============================================================================

// 1. Pencarian Angka (ID Sewa) menggunakan BINARY SEARCH
// Membutuhkan data yang sudah terurut untuk dapat bekerja dengan benar
int BinarySearchID(Penyewaan dataSewa[], int jumlahData, int *idTarget) {
    int low = 0;
    int high = jumlahData - 1;

    while (low <= high) {
        // Menentukan nilai tengah (mid)
        int mid = low + (high - low) / 2; 

        // Mengecek apakah nilai mid sama dengan target yang ditunjuk pointer idTarget
        if (dataSewa[mid].IdSewa == *idTarget) {
            return mid; // Data ditemukan, kembalikan indeks
        } 
        // Jika nilai mid lebih kecil dari target, cari di sisi kanan
        else if (dataSewa[mid].IdSewa < *idTarget) {
            low = mid + 1; 
        } 
        // Jika nilai mid lebih besar dari target, cari di sisi kiri
        else {
            high = mid - 1; 
        }
    }
    return -1; // Data tidak ditemukan
}

// 2. Pencarian Huruf/Kata (Nama Penyewa) menggunakan LINEAR SEARCH
// Menelusuri data satu per satu dari awal hingga akhir, cocok untuk data acak
int LinearSearchNama(Penyewaan dataSewa[], int jumlahData, string *namaTarget) {
    for (int i = 0; i < jumlahData; i++) {
        // Membandingkan nama pada array dengan target yang ditunjuk pointer namaTarget
        if (dataSewa[i].NamaPenyewa == *namaTarget) {
            return i; // Data ditemukan, kembalikan indeks
        }
    }
    return -1; // Data tidak ditemukan
}
// ==============================================================================

void UbahData(Penyewaan dataSewa[], int &jumlahData) {
    if (jumlahData == 0) throw RentalException("Belum ada data penyewaan.");
    LihatData(dataSewa, jumlahData);
    
    int idTarget;
    cout << "\nMasukkan ID Penyewaan yang ingin diubah: ";
    cin >> idTarget;
    cin.ignore();

    SortIdAscending(dataSewa, jumlahData);
    int indexDitemukan = BinarySearchID(dataSewa, jumlahData, &idTarget);

    if (indexDitemukan != -1) {
        cout << "\n=== UBAH DATA (ID: " << idTarget << ") ===\n";
        
        cout << "Nama Penyewa Baru (sebelumnya: " << dataSewa[indexDitemukan].NamaPenyewa << "): ";
        getline(cin, dataSewa[indexDitemukan].NamaPenyewa);

        cout << "Merek Powerbank Baru (sebelumnya: " << dataSewa[indexDitemukan].MerekPowerbank << "): ";
        getline(cin, dataSewa[indexDitemukan].MerekPowerbank);

        cout << "Durasi Sewa Baru (Jam) (sebelumnya: " << *(dataSewa[indexDitemukan].ptrDurasi) << "): ";
        cin >> dataSewa[indexDitemukan].DurasiJam;
        cin.ignore();
        
        dataSewa[indexDitemukan].ptrDurasi = &dataSewa[indexDitemukan].DurasiJam;

        cout << ">>> Data berhasil diubah! <<<\n";
    } else {
        cout << ">>> Data dengan ID tersebut tidak ditemukan! <<<\n";
    }
}

void HapusData(Penyewaan dataSewa[], int &jumlahData) {
    if (jumlahData == 0) throw RentalException("Belum ada data penyewaan.");
    LihatData(dataSewa, jumlahData);
    
    int idTarget;
    cout << "\nMasukkan ID Penyewaan yang ingin dihapus: ";
    cin >> idTarget;
    cin.ignore();

    SortIdAscending(dataSewa, jumlahData);
    int indexDitemukan = BinarySearchID(dataSewa, jumlahData, &idTarget);

    if (indexDitemukan != -1) {
        for (int j = indexDitemukan; j < jumlahData - 1; j++) {
            dataSewa[j] = dataSewa[j + 1];
            dataSewa[j].ptrDurasi = &dataSewa[j].DurasiJam;
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
        cout << "3. Cari Data Penyewaan (Searching)\n";
        cout << "4. Ubah Data Penyewaan (Update)\n";
        cout << "5. Hapus Data Penyewaan (Delete)\n";
        cout << "6. Urutkan Data (Sorting)\n";
        cout << "7. Keluar\n";
        
        try {
            cout << "Pilih Menu (1-7): ";
            // Validasi input menu menggunakan exception handling
            if (!(cin >> pilihanMenu)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw RentalException("Input harus berupa angka (1-7)!");
            }
            cin.ignore();
            
            switch (pilihanMenu) {
                case 1:
                    TambahData(dataSewa, &jumlahData, &nextId);
                    break;
                case 2:
                    LihatData(dataSewa, jumlahData);
                    break;
                
                // =================================================================
                // IMPLEMENTASI MENU SEARCHING BARU
                // =================================================================
                case 3: {
                    if (jumlahData == 0) {
                        throw RentalException("Belum ada data penyewaan.");
                    } else {
                        int pilihCari;
                        cout << "\n=== MENU SEARCHING ===\n";
                        cout << "1. Cari ID Sewa (Angka) - Menggunakan Binary Search\n";
                        cout << "2. Cari Nama Penyewa (Huruf) - Menggunakan Linear Search\n";
                        cout << "Pilih metode pencarian (1-2): ";
                        
                        if (!(cin >> pilihCari)) {
                            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw RentalException("Metode pencarian harus berupa angka!");
                        }
                        cin.ignore();

                        if (pilihCari == 1) {
                            int idCari;
                            cout << "\nMasukkan ID Penyewaan yang ingin dicari: ";
                            cin >> idCari;
                            cin.ignore();
                            
                            // Sortir ID terlebih dahulu karena Binary Search wajib berurutan
                            cout << "(Sistem mengurutkan ID secara otomatis...)\n";
                            SortIdAscending(dataSewa, jumlahData); 
                            
                            int indexDitemukan = BinarySearchID(dataSewa, jumlahData, &idCari);
                            if (indexDitemukan != -1) {
                                LihatData(dataSewa, jumlahData, indexDitemukan);
                            } else {
                                cout << ">>> Data dengan ID " << idCari << " tidak ditemukan! <<<\n";
                            }
                        } 
                        else if (pilihCari == 2) {
                            string namaCari;
                            cout << "\nMasukkan Nama Penyewa yang ingin dicari: ";
                            getline(cin, namaCari);
                            
                            int indexDitemukan = LinearSearchNama(dataSewa, jumlahData, &namaCari);
                            if (indexDitemukan != -1) {
                                LihatData(dataSewa, jumlahData, indexDitemukan);
                            } else {
                                cout << ">>> Data dengan Nama \"" << namaCari << "\" tidak ditemukan! <<<\n";
                            }
                        } else {
                            cout << ">>> Pilihan pencarian tidak valid! <<<\n";
                        }
                    }
                    break;
                }
                // =================================================================
                case 4:
                    UbahData(dataSewa, jumlahData);
                    break;
                case 5:
                    HapusData(dataSewa, jumlahData);
                    break;
                case 6: {
                    if (jumlahData < 2) {
                        throw RentalException("Data masih kurang untuk diurutkan (minimal 2 data).");
                    } else {
                        int pilihSort;
                        cout << "\n=== MENU SORTING ===\n";
                        cout << "1. Berdasarkan Nama Penyewa (Descending - Bubble Sort)\n";
                        cout << "2. Berdasarkan Durasi Sewa  (Ascending  - Selection Sort)\n";
                        cout << "3. Berdasarkan ID Sewa      (Ascending  - Insertion Sort)\n";
                        cout << "Pilih metode sorting (1-3): ";
                        
                        if (!(cin >> pilihSort)) {
                            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw RentalException("Metode sorting harus berupa angka!");
                        }
                        cin.ignore();

                        if (pilihSort == 1) {
                            SortNamaDescending(dataSewa, jumlahData);
                            LihatData(dataSewa, jumlahData);
                        } else if (pilihSort == 2) {
                            SortDurasiAscending(dataSewa, jumlahData);
                            LihatData(dataSewa, jumlahData);
                        } else if (pilihSort == 3) {
                            SortIdAscending(dataSewa, jumlahData);
                            cout << ">>> Data berhasil dikembalikan sesuai urutan ID (Ascending) dengan Insertion Sort! <<<\n";
                            LihatData(dataSewa, jumlahData);
                        } else {
                            cout << ">>> Pilihan sorting tidak valid! <<<\n";
                        }
                    }
                    break;
                }
                case 7:
                    cout << "Keluar dari sistem. Terima kasih!\n";
                    break;
                default:
                    throw RentalException("Pilihan tidak valid, silakan coba lagi.");
            }
        } 
        catch (RentalException &e) {
            cout << "\n>>> [ERROR]: " << e.getPesan() << " <<<\n";
        }

    } while (pilihanMenu != 7);

    return 0;
}