// Задача 1. Адреса
// Дан файл in.txt, в котором находится N адресов
// Нужно считать адреса из файла in.txt и вывести их в файл out.txt в другом формате и в обратном порядке.

#include <iostream>
#include <fstream>
#include <string>

// создание класса для хранения адресов
class Address {

public:
    std::string city;
    std::string street;
    int house_number = 0;
    int flat_number = 0;

    // функция, чтобы собрать данные в одну строку для файла
    std::string format() {
        return city + ", " + street + ", " + std::to_string(house_number) + ", " + std::to_string(flat_number);
    }
};

int main() {

    std::ifstream in("in.txt"); // открытие файла in для чтения данных 
    std::ofstream out("out.txt"); // открытие файла out для записи данных 

    // получение сообщения, если файлы не открываются
    if (!in.is_open()) {
        std::cerr << "Ошибка, не удалось открыть файл in.txt" << std::endl;
        return 1;
    }
    if (!out.is_open()) {
        std::cerr << "Ошибка, не удалось создать файл out.txt" << std::endl;
        return 1;
    }

    int n = 0;
    in >> n; // чтение количества адресов из файла in
    in.ignore(); // пропуск перехода на новую строку для корректного чтения первого адреса

    // создание динамического массива для хранения адресов
    Address* arr = new Address[n];

    // заполнение данными данными из файла
    for (int i = 0; i < n; i++) {
        std::getline(in, arr[i].city);
        //std::getline(in, street_temp); 
        std::getline(in, arr[i].street);

        std::string h, f;
        std::getline(in, h); // чтение номера дома как строки
        arr[i].house_number = std::stoi(h); // Превращение в число

        std::getline(in, f); // чтение номера квартиры как строки
        arr[i].flat_number = std::stoi(f); // Превращение в число
    }

    in.close(); // закрытие файла in

    out << n << std::endl; // запись в файл общего количества

    // проход с конца массива к началу
    for (int i = n - 1; i >= 0; i--) {
        out << arr[i].format() << std::endl;
    }
    out.close(); // закрытие файла out

    // освобождение памяти
    delete[] arr;

    return 0;
}