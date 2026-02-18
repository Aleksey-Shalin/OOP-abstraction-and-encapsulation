// Задача 2. Сортируем адреса
// В этом задании вы будете читать из файла адреса и выводить их в другой файл в другом формате, отсортированными по названию города.
// Задача программы заключается в том, чтобы считать адреса из файла in.txt, отсортировать их по названию города и вывести отсортированный список адресов в файл out.txt в другом формате.Не забудьте вывести количество адресов в начале.
// Города должны быть отсортированы в алфавитном порядке.

#include <iostream>
#include <fstream>
#include <string>

// класс для хранения адреса
class Address {
private:
    std::string city;
    std::string street;
    int house_number;
    int flat_number;

public:

    // конструктор по умолчанию нужен для массива
    Address() : city(""), street(""), house_number(0), flat_number(0) {}

    // конструктор с параметрами
    Address(std::string city_name, std::string street_name, int house_num, int flat_num) {
        city = city_name;
        street = street_name;
        house_number = house_num;
        flat_number = flat_num;
    }

    // метод для получения строки адреса и формирования вывода на консоль
    std::string get_output_address() const {
        return city + ", " + street + ", " +
            std::to_string(house_number) + ", " + std::to_string(flat_number);   // запись номеров в виде строк
    }

    // метод для получения названия города для сортировки
    std::string get_city() const {
        return city;
    }
};

// сортировка пузырьком по названию города
void city_name_sort(Address* addresses, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (addresses[j].get_city() > addresses[j + 1].get_city()) {  // сравнение названий городов и изменение местоположения объектов
                Address temp = addresses[j];
                addresses[j] = addresses[j + 1];
                addresses[j + 1] = temp;
            }
        }
    }
}

int main() {
    std::ifstream in_file("in.txt");
    std::ofstream out_file("out.txt");

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
    in_file.ignore(); // пропускаем остаток строки

    // создание массива объектов
    Address* addresses = new Address[N];

    // чтение адресов из файла
    for (int i = 0; i < N; i++) {
        std::string city, street;
        int house, flat;

        std::getline(in_file, city);
        std::getline(in_file, street);
        in_file >> house >> flat;
        in_file.ignore();

        // создание объекта через конструктор с параметрами с записью в массив
        addresses[i] = Address(city, street, house, flat);
    }

    // сортировка адресов
    city_name_sort(addresses, N);

    // запись в файл out
    out_file << N << std::endl;
    for (int i = 0; i < N; i++) {
        out_file << addresses[i].get_output_address() << std::endl;
    }

    // закрытие файлов
    in_file.close();
    out_file.close();

    // освобождение памяти
    delete[] addresses;

    return 0;
}
