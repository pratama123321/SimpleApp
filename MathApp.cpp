#include <iostream>
#include <string>

using namespace std;

// Utilities
class Util {
    // for C-IN template generic parameter
    public:
        template <typename T>
        T input(string info) {
            T choose;
            cout << info << " : ";
            cin >> choose;

            return choose;
        }

        void exit() {
            while(true) {
                cout << endl;
                cout << "1. Kembali " << endl;
                cout << endl;
                
                string input = this->input<string>("Silahkan Pilih");

                if(input == "1") break;
            }
        }
};

// Repo Layer : Data Entity
class Repo {
    private:
        int length = 7;
        const string progammer = "Kukuh Nur Pratama";
        const string prodi = "Teknik Informatika";
        const string nim = "411222054";
        const float pi = 3.14;
        string* list = new string[length] {
            "1. Nama Pembuat Program",
            "2. Menghitung Volume Tabung",
            "3. Menghitung Volume Bola",
            "4. Menghitung Volume Limas Segi 4",
            "5. Menentukan Lulus dan Tidak Lulus",
            "6. Mencari Bilangan Terbesar",
            "7. Bilangan Ganjil atau Genap",
        };

    public:
        string* getAll() { return this->list; };

        const string getProgrammer() { return this->progammer; }

        const string getProdi() { return this->prodi; }

        const string getNim() { return this->nim; }

        const float getPi() { return this->pi; }
};

// Logic
// Service Layer : Interface
class Service {
    public:
        virtual string* showAppListService() = 0;

        virtual string* aboutMeService() = 0;

        virtual float volumeTabungService(float r, float tinggi) = 0;

        virtual float volumeBolaService(float r) = 0;

        virtual float volumeLimasSegi4Service(float sisi, float tinggi) = 0;

        virtual string lulusAtauTidakLulusService(float uts, float uas, float tugas) = 0;

        virtual int bilanganTerbesarService(int a, int b, int c) = 0;

        virtual string ganjilAtauGenapService(int a) = 0;
};

// Service Layer : Implementation
class ServiceImpl : Service {
    private:
        Repo repo;
        Util util;

    public: 
        string* showAppListService() override {
            return repo.getAll();
        }

        string* aboutMeService() override {
            return new string[3] {
                repo.getProgrammer(),
                repo.getProdi(),
                repo.getNim()
            };
        }

        float volumeTabungService(float r, float tinggi) override {
            return repo.getPi() * r * r * tinggi;
        }

        float volumeBolaService(float r) override {
            return ((4/3) * repo.getPi() * (r * r * r));
        }

        float volumeLimasSegi4Service(float sisi, float tinggi) override {
            return (sisi * sisi * tinggi) / 3;
        }
        
        string lulusAtauTidakLulusService(float uts, float uas, float tugas) override {
            float rataRata = (uts + uas + tugas) / 3;
            
            return rataRata >= 85 ? "Lulus" : "Tidak Lulus";
        }
        
        int bilanganTerbesarService(int a, int b, int c) override {
            int temp;
            if(a >= b && a >= c) {
                temp = a;
            } else if(b >= c) {
                temp = b;
            } else {
                temp = c;
            }
            
            return temp;
        }
        
        string ganjilAtauGenapService(int a) override {
            return (a % 2 == 0) ? "Genap" : "Ganjil";
        }
};

// Layer View : Interface
class View {
    public:
        virtual void showAppListView() {}

        virtual void aboutMeView() {};
        
        virtual void volumeTabungView() {}; 

        virtual void volumeBolaView() {};

        virtual void volumeLimasSegi4View() {};
        
        virtual void lulusAtauTidakLulusView() {};
        
        virtual void bilanganTerbesarView() {};
        
        virtual void ganjilAtauGenapView() {};
};

// Layer View : Implementation
class ViewImpl : View {
    private:
        ServiceImpl service;
        Util util;

    public:
        virtual void showAppListView() {
            for(int i = 0; i < sizeof(service.showAppListService()) - 1; i++) {
                cout << service.showAppListService()[i] << endl;
            }
            cout << "8. Keluar" << endl;
        }
        
        void aboutMeView() override {
            cout << "Hi..." << endl;
            cout << "Nama : " << service.aboutMeService()[0] << endl;
            cout << "Prodi : " << service.aboutMeService()[1] << " (" << service.aboutMeService()[2] << ") " << endl;
            util.exit();
        }

        void volumeTabungView() override {
            cout << "Menghitung Volume Tabung\n" << endl;
            float r = util.input<float>("Masukan Jari-Jari Tabung");
            float tinggi = util.input<float>("Masukan Tinngi Tabung");

            cout << endl;
            cout << "Volume Tabung : " << service.volumeTabungService(r, tinggi);
            cout << endl;
            util.exit();
        }

        void volumeBolaView() override {
            cout << "Menghitung Volume Bola\n" << endl;
            float r = util.input<float>("Masukan Jari-Jari Bola");

            cout << endl;
            cout << "Volume Bola : " << service.volumeBolaService(r);
            cout << endl;
            util.exit();
        }

        void volumeLimasSegi4View() override {
            cout << "Menghitung Volume Limas Segi 4\n" << endl;
            float sisi = util.input<float>("Masukan Panjang Sisi");
            float tinggi = util.input<float>("Masukan Tinggi");

            cout << endl;
            cout << "Volume Limas Segi 4 : " << service.volumeLimasSegi4Service(sisi, tinggi);
            cout << endl;
            util.exit();
        }
        
        void lulusAtauTidakLulusView() override {
            cout << "Cek Kelulusan\n" << endl;
            string name = util.input<string>("Masukan Nama Kamu");
            float uts = util.input<float>("Masukan Nilai UTS");
            float uas = util.input<float>("Masukan Nilai UAS");
            float tugas = util.input<float>("Masukan Nilai TUGAS");
            
            cout << endl;
            cout << name << " : " << service.lulusAtauTidakLulusService(uts, uas, tugas) << endl;
            util.exit();
        }
        
        void bilanganTerbesarView() override {
            cout << "Mencari Bilangan Terbesar Dari 3 Bilangan\n" << endl;
            int a = util.input<int>("Masukan Angka 1");
            int b = util.input<int>("Masukan Angka 2");
            int c = util.input<int>("Masukan Angka 3");
            
            cout << endl;
            cout << "Bilangan Terbesar Dari " << a << ", " << b << ", " << c << " Adalah : " << service.bilanganTerbesarService(a, b, c) << endl;
            util.exit();
        }
        
        void ganjilAtauGenapView() override {
            cout << "Cek Bilangan Ganjil Atau Genap\n" << endl;
            int a = util.input<int>("Masukan Bilangan");
            
            cout << endl;
            cout << "Bilangan " << a << " adalah " << service.ganjilAtauGenapService(a) << endl;
            util.exit();
        }
};

// Main App
int main() {
    while(true) {
        ViewImpl view;
        Util util;

        cout << endl;
        view.showAppListView();

        cout << endl;
        string input = util.input<string>("Silahkan Pilih");
        cout << endl;

        if(input == "1") {
            view.aboutMeView();
        } else if(input == "2") {
            view.volumeTabungView();
        } else if(input == "3") {
            view.volumeBolaView();
        } else if(input == "4") {
            view.volumeLimasSegi4View();
        } else if(input == "5") {
            view.lulusAtauTidakLulusView();
        } else if(input == "6") {
            view.bilanganTerbesarView();
        } else if(input == "7") {
            view.ganjilAtauGenapView();
        } else {
            break;
        }
    }
    return 0;
}
