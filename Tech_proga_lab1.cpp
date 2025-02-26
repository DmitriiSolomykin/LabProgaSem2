//Объект книга. Поля - Атор(char), название(char), количество страниц (unsigned int)

#include <iostream>
#include <string>

using namespace std;


struct Book {
    string author;
    string name;
    unsigned int page;
};

void sortArr(Book books[], int numBook);
void complectionArr(Book books[], int numBook);
void printArr(const Book books[], int numBook);

int main() {
	setlocale(LC_ALL, "ru");
	system("chcp 1251 > text");

    int numBooks;

    cout << "Введите количество книг: ";
    cin >> numBooks;

    Book* books = new Book[numBooks];

    complectionArr(books, numBooks);
    sortArr(books, numBooks);
    printArr(books, numBooks);

    delete[] books;

    return 0;
}

void complectionArr(Book books[], int numBooks) {
    for (int i = 0; i < numBooks; i++) {
        cout << "Кинга номер " << i + 1 << ":\n";

        cout << "Автор: ";
        cin.ignore();
        getline(cin, books[i].author);

        cout << "Название: ";
        getline(cin, books[i].name);

        cout << "Количество страниц: ";
        cin >> books[i].page;
    }
}

void sortArr(Book books[], int numBooks) {
    for (int i = 1; i < numBooks; i++) {
        Book key = books[i];
        int j = i - 1;

        while (j >= 0 && books[j].name > key.name) {
            books[j + 1] = books[j];
            j--;
        }
        books[j + 1] = key;
    }
}

void printArr(const Book books[], int numBooks) {
    for (int i = 0; i < numBooks; i++) {
        cout << "Книга номер " << i + 1 << ":\n";
        cout << "  Автор: " << books[i].author << endl;
        cout << "  Название: " << books[i].name << endl;
        cout << "  Количество страниц: " << books[i].page << endl;
    }
}