// Задача 1. Адреса
// Дан файл in.txt, в котором находится N адресов
// Нужно считать адреса из файла in.txt и вывести их в файл out.txt в другом формате и в обратном порядке.


#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>

// создание класса для адреса
class Address {
private:
    std::string city;
    std::string street;
    int house_num;
    int flat_num;

public:

    // конструктор по умолчанию для создания массива объектов
    Address() : city(""), street(""), house_num(0), flat_num(0) {}

    // конструктор с параметрами — нельзя создать пустой адрес
    Address(const std::string& city_name, const std::string& street_name, int house_number, int flat_number)
        : city(city_name), street(street_name), house_num(house_number), flat_num(flat_number) {
    }

    // метод для получения строки в нужном формате
    std::string get_output_address() const {
        return city + ", " + street + ", " + std::to_string(house_num) + ", " + std::to_string(flat_num);
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // открытие файлов
    std::ifstream in_file("in.txt");
    std::ofstream out_file("out.txt");

    // получение сообщения, если файлы не открываются
    if (!in_file.is_open()) {
        std::cerr << "Ошибка, не удалось открыть файл in.txt" << std::endl;
        return 1;
    }
    if (!out_file.is_open()) {
        std::cerr << "Ошибка, не удалось создать файл out.txt" << std::endl;
        return 1;
    }

    // чтение количество адресов из файла in
    int N;
    in_file >> N;
    in_file.ignore(); // игнорирование символов новой строки после чтения чисел

    // cоздание динамического массива
    Address* addresses = new Address[N];

    // чтение адресов в корректном формате
    for (int i = 0; i < N; ++i) {
        std::string city, street;
        int house, flat;

        // считывание строк полностью
        std::getline(in_file, city);      // прочитывает полностью название города
        std::getline(in_file, street);    // прочитывает полностью название улицы
        in_file >> house;
        in_file.ignore(); // пропуск \n для корректного считывания
        in_file >> flat;
        in_file.ignore();

        // создание объекта и присваивание элементу массива
        addresses[i] = Address(city, street, house, flat);
    }

    // вывод адресов в обратном порядке в файл out
    out_file << N << std::endl;
    for (int i = N - 1; i >= 0; --i) {
        out_file << addresses[i].get_output_address() << std::endl;
    }

    // удаление массива для очистки памяти
    delete[] addresses;

    // закрытие файлов
    in_file.close();
    out_file.close();

    return 0;
}