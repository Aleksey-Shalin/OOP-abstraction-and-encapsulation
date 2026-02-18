// Задача 2. Сортируем адреса
// В этом задании вы будете читать из файла адреса и выводить их в другой файл в другом формате, отсортированными по названию города.
// Задача программы заключается в том, чтобы считать адреса из файла in.txt, отсортировать их по названию города и вывести отсортированный список адресов в файл out.txt в другом формате.Не забудьте вывести количество адресов в начале.
// Города должны быть отсортированы в алфавитном порядке.

#include<iostream>
#include<fstream>
#include<string>


// класс для хранения адреса
class Address {
private:
    std::string city;
    std::string street;
    int house_number;
    int flat_number;

public:
    // конструктор с параметрами
    Address(std::string city, std::string street, int house_number, int flat_number) {
        this->city = city;
        this->street = street;
        this->house_number = house_number;
        this->flat_number = flat_number;
    }

    // метод для получения строки адреса
    std::string get_output_address() const {
        return city + ", " + street + ", " + std::to_string(house_number) + ", " + std::to_string(flat_number);
    }

    // метод для получения названия города для сортировки
    std::string get_city() const {
        return city;
    }
};

// функция сортировки адресов по названию города
void city_name_sort(Address** addresses, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (addresses[j]->get_city() > addresses[j + 1]->get_city()) {
                Address* temp = addresses[j];
                addresses[j] = addresses[j + 1];
                addresses[j + 1] = temp;
            }
        }
    }
}

int main() {
    std::ifstream in_file("in.txt");    // открытие файла для чтения из файла
    std::ofstream out_file("out.txt");  // открытие файла для записи в файл

    // чтение ошибки, если файл не удалось открыть
    if (!in_file.is_open()) {
        std::cerr << "Ошибка открытия файла in.txt" << std::endl;
        return 1;
    }
    if (!out_file.is_open()) {
        std::cerr << "Ошибка открытия файла out.txt" << std::endl;
        return 1;
    }

    // чтение количества адресов
    int N;
    in_file >> N;
    in_file.ignore();

    // создание динамического массива указателей на адреса
    Address** addresses = new Address * [N];

    // считывание адресов из файла
    for (int i = 0; i < N; i++) {
        std::string city, street;
        int house_number, flat_number;

        std::getline(in_file, city);
        std::getline(in_file, street);
        in_file >> house_number;
        in_file >> flat_number;
        in_file.ignore();

        addresses[i] = new Address(city, street, house_number, flat_number);
    }

    // сортировка по названию города
    city_name_sort(addresses, N);

    // вывод в файл
    out_file << N << std::endl;
    for (int i = 0; i < N; i++) {
        out_file << addresses[i]->get_output_address() << std::endl;
    }

    // закрытие файлов
    in_file.close();
    out_file.close();

    // освобождение памяти
    for (int i = 0; i < N; i++) {
        delete addresses[i];
    }
    delete[] addresses;

    return 0;
}