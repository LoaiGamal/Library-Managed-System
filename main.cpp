#include <iostream>
#include <string>

using namespace std;

struct CopyNode{
        string copyDate;
        bool available;
        string borrower;
        string borrowDate;
        int numberOfDaysToReturnTheBook;
        CopyNode *nextCopy;
};

class CopiesQueue{
private:
    CopyNode *frontt, *endd;
    int numberOfCopies;
public:
    CopiesQueue(){
        frontt = endd = nullptr;
        numberOfCopies = 0;
    }
    bool isEmpty(){
        return frontt==nullptr;
    }
    void addCopy(string copyDate){
        CopyNode *newCopy = new CopyNode;
        newCopy->copyDate = copyDate;
        newCopy->available = true;
        newCopy->borrower = "No borrower yet";
        newCopy->borrowDate = "This book does not borrowed";
        newCopy->nextCopy = nullptr;
        if(isEmpty()){
            frontt = endd = newCopy;
        }else{
            endd->nextCopy = newCopy;
            endd = newCopy;
        }
        numberOfCopies++;
        cout << endl;
    }
    void deleteCopy(){
        if(isEmpty()){
            cout << "There is no copies to delete.\n";
        }else if(numberOfCopies==1){
            delete frontt;
            delete endd;
            numberOfCopies--;
        }else{
            CopyNode *temp = frontt;
            frontt = frontt->nextCopy;
            temp->nextCopy = nullptr;
            delete temp;
            numberOfCopies--;
        }
        cout << endl;
    }
    CopyNode *getFrontt(){
        return frontt;
    }
    void printCopiesList(){
        if(isEmpty()){
            cout << "There is no copies for this book\n";
        }else{
            int i=1;
            CopyNode *temp = frontt;
            while (temp != nullptr){
                cout << "Copy number (" << i << ")" << endl;
                cout << "Copy Date: " << temp->copyDate << endl;
                cout << "Available: ";
                if(temp->available == true){
                    cout << "Available to borrow\n";
                }else{
                    cout << "unavailable to borrow\n";
                }
                cout << "Borrower: " << temp->borrower << endl;
                cout << "Borrow Date: " << temp->borrowDate << endl;
                cout << "Number Of Days To Return The Book: " << temp->numberOfDaysToReturnTheBook << endl;
                temp = temp->nextCopy;
                cout << endl;
                i++;
            }
        }
    }
};

struct BookNode{
    string bookName;
    string bookISBN;
    int numberOfCopies;
    CopiesQueue copiesList;
    BookNode *nextBook;
};

class BookLinkedList{
private:
    BookNode *first, *last;
    int numberOfBooks;
    int numberOfBorrowed;
    int numberOfAdding;

public:
    BookLinkedList(){
        first = last = nullptr;
        numberOfBooks=0;
        numberOfBorrowed=0;
        numberOfAdding=0;
    }
    bool isEmpty(){
        return (first == nullptr);
    }
    void insertAtBegin(string bookName, string bookISBN, int numberOfCopies){
        BookNode *newBook = new BookNode;
        newBook->bookName = bookName;
        newBook->bookISBN = bookISBN;
        newBook->numberOfCopies = numberOfCopies;
        for(int i=0; i<numberOfCopies; i++){
                string copyDate;
                cout << "Enter copy date of copy number " << (i+1) << ": ";
                cin >> copyDate;
                newBook->copiesList.addCopy(copyDate);
        }
        if (isEmpty()){
            newBook->nextBook = nullptr;
            first = last = newBook;
        }else{
            newBook->nextBook = first;
            first = newBook;
        }
        numberOfBooks+=newBook->numberOfCopies;
        numberOfAdding++;
        cout << endl;
    }
    void insertAtEnd(string bookName, string bookISBN, int numberOfCopies){
        BookNode *newBook = new BookNode;
        newBook->bookName = bookName;
        newBook->bookISBN = bookISBN;
        newBook->numberOfCopies = numberOfCopies;
        for(int i=0; i<numberOfCopies; i++){
                string copyDate;
                cout << "Enter copy date of copy number " << (i+1) << ": ";
                cin >> copyDate;
                newBook->copiesList.addCopy(copyDate);
        }
        newBook->nextBook = nullptr;
        if (isEmpty()){
            first = last = newBook;
        }else{
            last->nextBook = newBook;
            last = newBook;
        }
        numberOfBooks+=newBook->numberOfCopies;
        numberOfAdding++;
        cout << endl;
    }
    void InsertAtPos(string bookName, string bookISBN, int numberOfCopies, int pos){
        BookNode *newBook = new BookNode;
        BookNode *cur = first;
        newBook->bookName = bookName;
        newBook->bookISBN = bookISBN;
        newBook->numberOfCopies = numberOfCopies;
        for(int i=0; i<numberOfCopies; i++){
                string copyDate;
                cout << "Enter copy date of copy number " << (i+1) << ": ";
                cin >> copyDate;
                newBook->copiesList.addCopy(copyDate);
        }
        if ((isEmpty() && pos!=0) || (!isEmpty() && pos > numberOfBooks)){
            cout << "Invalid position.\n";
        }else if (pos==0){
            insertAtBegin(bookName, bookISBN, numberOfCopies);
        }else if (pos==numberOfBooks){
            insertAtEnd(bookName, bookISBN, numberOfCopies);
        }
        else{
            for (int i=1;i<pos-1;i++){
                cur = cur->nextBook;
            }
            newBook->nextBook = cur->nextBook;
            cur->nextBook = newBook;
            numberOfBooks+=newBook->numberOfCopies;
            numberOfAdding++;
        }
        cout << endl;
    }
    void deleteAtBegin(){
        if (isEmpty()){
            cout << "The list is already empty.\n";
        }else if(numberOfAdding == 1){
            numberOfBooks-=first->numberOfCopies;
            for(int i=0; i<first->numberOfCopies; i++){
                first->copiesList.deleteCopy();
            }
            numberOfAdding--;
            delete first;
            delete last;
        }else{
            BookNode *temp = first;
            first = first->nextBook;
            temp->nextBook = nullptr;
            numberOfBooks-=temp->numberOfCopies;
            temp->copiesList.deleteCopy();
            numberOfAdding--;
            delete temp;
        }
        cout << endl;
    }
    void deleteAtEnd(){
        if (isEmpty()){
            cout << "The list is already empty.\n";
        }else if(numberOfAdding == 1){
            numberOfBooks-=first->numberOfCopies;
            numberOfAdding--;
            first->copiesList.deleteCopy();
            delete first;
            delete last;
        }else{
            BookNode *temp = last;
            BookNode *cur = first;
            for (int i=1; i < (numberOfAdding-1); i++){
                cur = cur->nextBook;
            }
            last = cur;
            last->nextBook=nullptr;
            temp->nextBook=nullptr;
            numberOfBooks-=temp->numberOfCopies;
            temp->copiesList.deleteCopy();
            numberOfAdding--;
            delete temp;
        }
        cout << endl;
    }
    void deleteAtPos(int pos){
        if ((isEmpty() && pos!=0) || (!isEmpty() && pos > numberOfBooks)){
            cout << "Invalid position.\n";
        }else if (pos==0 || isEmpty()){
            deleteAtBegin();
        }else if (pos==numberOfBooks){
            deleteAtEnd();
        }else{
            BookNode *prev;
            BookNode *cur = first;
            for (int i=1;i<pos;i++){
                prev = cur;
                cur = cur->nextBook;
            }
            prev->nextBook = cur->nextBook;
            cur->nextBook = nullptr;
            numberOfBooks-=cur->numberOfCopies;
            cur->copiesList.deleteCopy();
            numberOfAdding--;
            delete cur;
        }
        cout << endl;
    }
    BookNode *getBook(string bookName){
        bool check = false;
        BookNode *temp = first;
        while(temp != nullptr){
            if(temp->bookName == bookName){
                check = true;
                return temp;
            }
            temp = temp->nextBook;
        }
        if (check == false){
            cout << "This book name does not exist \n";
        }
    }
    void searchBook(string bookName){
        bool checkBook = false;
        bool checkBorrow = false;
        BookNode *temp = first;
        while(temp != nullptr){
            if(temp->bookName == bookName){
                checkBook = true;
                break;
            }
            temp = temp->nextBook;
        }
        if (checkBook == false){
            cout << "This book name does not exist \n";
        }else if(checkBook==true){
            CopyNode *copyNode = temp->copiesList.getFrontt();
            while(copyNode != nullptr){
                if(copyNode->available == true){
                   checkBorrow = true;
                   break;
                }
                copyNode = copyNode->nextCopy;
            }
            if(checkBorrow==true){
                cout << "The book is found and there is available copies to borrow\n";
            }else{
                cout << "The book is found but there is unavailable copies to borrow\n";
            }
        }
        cout << endl;
    }
    void addingBookCopy(){
        string bookName;
        cout << "Enter book name: ";
        cin.ignore();
        getline(cin, bookName);
        BookNode *book = getBook(bookName);
        incrementNumberOFBooks();
        book->numberOfCopies++;
        string copyDate;
        cout << "Enter copy date: ";
        cin >> copyDate;
        book->copiesList.addCopy(copyDate);
        cout << endl;
    }
    void addingBookBorrow(){
        bool check = false;
        string bookName;
        cout << "Enter book name: ";
        cin.ignore();
        getline(cin, bookName);
        BookNode *borrowBook = getBook(bookName);
        CopyNode *copyBorrow = borrowBook->copiesList.getFrontt();
        while(copyBorrow != nullptr){
            if(copyBorrow->available == true){
                check = true;
                break;
            }
            copyBorrow = copyBorrow->nextCopy;
        }
        if(check == false){
            cout << "There is no copies to borrow\n";
        }else{
            incrementNumberOFBorrowedBooks();
            string borrowerName, borrowDate;
            int numberOfDays;
            cout << "Enter borrower name: ";
            getline(cin, borrowerName);
            cout << "Enter borrow date: ";
            cin >> borrowDate;
            cout << "Enter number of days to return book: ";
            cin >> numberOfDays;
            copyBorrow->borrower = borrowerName;
            copyBorrow->borrowDate = borrowDate;
            copyBorrow->numberOfDaysToReturnTheBook = numberOfDays;
            copyBorrow->available = false;
        }
        cout << endl;
    }
    void addingBookReturn(){
        bool check = false;
        string bookName;
        cout << "Enter book name: ";
        cin.ignore();
        getline(cin, bookName);
        BookNode *borrowBook = getBook(bookName);
        CopyNode *copyBorrow = borrowBook->copiesList.getFrontt();
        string s;
        cout << "Enter borrower name: ";
        getline(cin, s);
        while(copyBorrow != nullptr){
            if(copyBorrow->borrower == s){
                check = true;
                break;
            }
            copyBorrow = copyBorrow->nextCopy;
        }
        if(check == false){
            cout << "Borrower name is not found\n";
        }else{
            decrementNumberOFBorrowedBooks();
            copyBorrow->available = true;
            copyBorrow->borrower = "No borrower yet";
            copyBorrow->borrowDate = "This book does not borrowed";
            copyBorrow->numberOfDaysToReturnTheBook=0;
        }
        cout << endl;
    }
    void showBorrowStatistics(){
        cout << "Number of borrowed books: " << getNumberOfBorrowedBooks() << endl;
    }
    void libraryInventory(){
        cout << "Number of all books: " << getNumberOfBooks() << endl;
        cout << "Number of borrowed books: " << getNumberOfBorrowedBooks() << endl;
    }
    int getNumberOfBooks(){
        return numberOfBooks;
    }
    void incrementNumberOFBorrowedBooks(){
        numberOfBorrowed++;
    }
    void incrementNumberOFBooks(){
        numberOfBooks++;
    }
    void decrementNumberOFBorrowedBooks(){
        numberOfBorrowed--;
    }
    int getNumberOfBorrowedBooks(){
        return numberOfBorrowed;
    }
    void printBooksList(){
        if(isEmpty()){
            cout << "There is no books in library\n";
        }else{
            int i=1;
            BookNode *temp = first;
            while(temp!=nullptr){
                cout << "Book number (" << i << ")" << endl;
                cout << "Book Name: " << temp->bookName << endl;
                cout << "Book ISBN: " << temp->bookISBN << endl;
                cout << "Number Of Copies: " << temp->numberOfCopies << endl;
                cout << "Copies list: \n";
                temp->copiesList.printCopiesList();
                temp = temp->nextBook;
                cout << endl << endl;
                i++;
            }
        }
        cout << endl;
    }
};


void mainMenu(){
    cout << "1- Add new book\n";
    cout << "2- Delete book\n";
    cout << "3- Search book\n";
    cout << "4- Add book copy\n";
    cout << "5- Add book borrow\n";
    cout << "6- Add book return\n";
    cout << "7- Show borrow statistics\n";
    cout << "8- Library inventory\n";
    cout << "9- Show all books\n";
    cout << "10- Exit\n \n";
    cout << "Your choice: ";
}

void addingMenu(){
    cout << endl << endl;
    cout << "1- Adding in beginning\n";
    cout << "2- Adding in last\n";
    cout << "3- Adding in certain position\n";
    cout << "4- Back\n \n";
    cout << "Your choice: ";
}

void deleteingMenu(){
    cout << endl << endl;
    cout << "1- Delete from beginning\n";
    cout << "2- Delete from last\n";
    cout << "3- Delete from certain position\n";
    cout << "4- Back\n \n";
    cout << "Your choice: ";
}

int main()
{
    BookLinkedList library;
    while(true){
        mainMenu();
        int mainMenueChoice;
        cin >> mainMenueChoice;
        if(mainMenueChoice==1){
            addingMenu();
            int addingMenueChoice;
            string bookName, bookISBN;
            int numberOfCopies;
            cin >> addingMenueChoice;
            cout << endl;
            if(addingMenueChoice==1){
                cout << "Book name: ";
                cin.ignore();
                getline(cin, bookName);
                cout << "Book ISBN: ";
                cin >> bookISBN;
                cout << "Number of copies: ";
                cin >> numberOfCopies;
                library.insertAtBegin(bookName, bookISBN, numberOfCopies);
            }else if(addingMenueChoice==2){
                cout << "Book name: ";
                cin.ignore();
                getline(cin, bookName);
                cout << "Book ISBN: ";
                cin >> bookISBN;
                cout << "Number of copies: ";
                cin >> numberOfCopies;
                library.insertAtEnd(bookName, bookISBN, numberOfCopies);
            }else if(addingMenueChoice==3){
                int pos;
                cout << "The position you want to add in: ";
                cin >> pos;
                cout << "Book name: ";
                cin.ignore();
                getline(cin, bookName);
                cout << "Book ISBN: ";
                cin >> bookISBN;
                cout << "Number of copies: ";
                cin >> numberOfCopies;
                library.InsertAtPos(bookName, bookISBN, numberOfCopies, pos);
            }else if(addingMenueChoice==4){
            }else{
                cout << "You entered wrong choice ... try again\n";
            }
        }else if(mainMenueChoice==2){
            deleteingMenu();
            int deletingMenueChoice;
            cin >> deletingMenueChoice;
            cout << endl;
            if(deletingMenueChoice==1){
                library.deleteAtBegin();
            }else if(deletingMenueChoice==2){
                library.deleteAtEnd();
            }else if(deletingMenueChoice==3){
                int pos;
                cout << "The position you want to delete from: ";
                cin >> pos;
                library.deleteAtPos(pos);
            }else if(deletingMenueChoice==4){
            }else{
                cout << "You entered wrong choice ... try again\n";
            }
        }else if(mainMenueChoice==3){
            cout << endl;
            string bookName;
            cout << "Enter the name of the book you want to search for: ";
            cin.ignore();
            getline(cin, bookName);
            library.searchBook(bookName);
            cout << endl;
        }else if(mainMenueChoice==4){
            cout << endl;
            library.addingBookCopy();
        }else if(mainMenueChoice==5){
            cout << endl;
            library.addingBookBorrow();
        }else if(mainMenueChoice==6){
            cout << endl;
            library.addingBookReturn();
        }else if(mainMenueChoice==7){
            cout << endl;
            library.showBorrowStatistics();
        }else if(mainMenueChoice==8){
            cout << endl;
            library.libraryInventory();
        }else if(mainMenueChoice==9){
            cout << endl;
            library.printBooksList();
        }else if(mainMenueChoice==10){
            return 0;
        }else{
            cout << "You entered wrong choice ... try again\n";
        }
    }
    return 0;
}
