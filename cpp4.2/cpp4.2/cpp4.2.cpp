#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Address {
private:
    std::string city;
    std::string street;
    std::string home;
    std::string flat;
public:
    Address(const std::string& city, const std::string& street, const std::string& home,
        const std::string& flat) : city(city), street(street), home(home), flat(flat) {}
    friend std::ostream& operator<< (std::ostream& out, const Address& x);
    //friend bool operator> (const Address &x, const Address&y);
    friend bool operator< (const Address& x, const Address& y);
    std::string get_city() { return city; }
    std::string get_street() { return street; }
    std::string get_home() { return home; }
    std::string get_flat() { return flat; }
};

std::ostream& operator<< (std::ostream& out, const Address& x) {
    out << x.city << " " << x.street << " " << x.home << " " << x.flat << '\n';
    return out;
}
/* for reverse sorting
bool operator> (const Address &x, const Address&y){
        if(x.city.compare(y.city) > 0)
            return true;
        else
            return false;
}
*/

bool operator< (const Address& x, const Address& y) {
    if (x.city.compare(y.city) < 0)
        return true;
    else
        return false;
}

Address from_txt(std::fstream& in) {
    std::string city, street, home, flat;
    if (!in.is_open()) {
        std::cout << "<in.txt> not open\n";
        exit(0);
    }
    getline(in, city);
    getline(in, street);
    getline(in, home);
    getline(in, flat);
    Address data{ city, street, home, flat };
    return data;
}

void to_txt(const int& count, const std::vector <Address>& data) {
    std::fstream out;
    out.open("out.txt");
    if (!out.is_open()) {
        std::cout << "<<out.txt>> not open\n";
        exit(0);
    }
    out << count << '\n';
    for (int i = count - 1; i >= 0; --i) {
        out << data[i];
    }
    out.close();
}

void bubbleSort(std::vector<Address>& x) {
    for (int i = 0; i + 1 < x.size(); ++i) {
        for (int k = 0; k + 1 < x.size() - i; ++k) {
            if (x[k] < x[k + 1]) {
                std::swap(x[k], x[k + 1]);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int count;
    std::vector <Address> data;
    std::fstream in("in.txt");
    in >> count;
    in.seekg(3);
    for (int i = 0; i < count; ++i) {
        data.push_back(from_txt(in));
    }
    in.close();
    bubbleSort(data);
    to_txt(count, data);
    return 0;
}