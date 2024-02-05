#include <iostream>
#include <ctime>
using namespace std;

class HashTable {
private:
    char** hashT;
public:
    int q, r, c;
    //Размер хеш-таблицы q и параметры второй хеш-функции
    //должны задаваться в конструкторе.
    HashTable() {
        cout << "Enter size of the hash table: "; //вынести из конструктора
        cin >> q;
        cout << "Enter parameter r: ";
        cin >> r;
        cout << "Enter parameter c: ";
        cin >> c;
        hashT = new char* [q];
        for (int i = 0; i < q; i++) {
            hashT[i] = NULL;
        }
    }
    int HashFunction(char* S);
    int HashFunction2(int S);
    void AddString(char* p);
    void printTable() {
        cout << "\nHash table: " << endl;
        for (int i = 0; i < q; i++) {
            if (hashT[i] == NULL) cout << "Null\n";
            else cout << hashT[i] << endl;
        }
    };
    int SearchString(char* p);
};

/*вычисление хеш-функции, 
добавление уникальной строки, 
поиск строки, совпадающей с заданной.*/

void HashTable::AddString(char* p) {
    //cout << "string: " << p << endl;
    int k = HashFunction(p);
    //cout << "first hash: " << k << endl;
    int j = HashFunction2(k);
    //cout << "second hash: " << j << endl << endl;
    while (hashT[k] != NULL) {
        k = (k + j) % q;
    }
    hashT[k] = p;	
}

int HashTable::SearchString(char* p) {
    int k = HashFunction(p);
    //cout << "first hash: " << k << endl;

    int j = HashFunction2(k);
    //cout << "second hash: " << j << endl;
    while (hashT[k] != p && hashT[k] != NULL) //сравнивать строки
    {
        k = (k + j) % q;
    }
    //cout << "k " << k << endl;
    //cout << "p " << p << endl << endl;
    if (hashT[k] == p) return k;
    else return -1;
}

int HashTable::HashFunction(char* S) {
    int sum = 0;
    for (int i = 0; i < q; i++) {
        sum += (sum + S[i])*31 % q;
    }
    return sum % q;
}
int HashTable::HashFunction2(int S) {
    return S % r + c;
}

char* RandomString(int length) {
    char* p;
    p = new char[length + 1];
    for (int i = 0; i < length; i++) {
        p[i] = char('a' + rand() % ('z' - 'a'));
    }
    p[length] = '\0';
    return p;
}

int main()
{
    srand(time(0));
    char** sourceArray;
    int n, diap;
    cout << "Enter the number of lines: ";
    cin >> n;
    sourceArray = new char*[n];
    cout << "Enter the number of characters in each line: ";
    cin >> diap;
    for (int i = 0; i < n; i++) {
        sourceArray[i] = RandomString(diap);
    }
    //for (int i = 0; i < n; i++) cout << sourceArray[i] << endl;

    HashTable mainTable;
    int uniqueString = 0;
    for (int i = 0; i < n; i++) {
        if (mainTable.SearchString(sourceArray[i]) == -1) {
            uniqueString++;
            mainTable.AddString(sourceArray[i]);
        }
    }
    //mainTable.printTable();
    cout << "Number of unique string: " << uniqueString << endl;
    uniqueString = 0;

    int searchStrInd;

    char* searchStr;
    searchStr = new char[diap];
    searchStr = sourceArray[3];

    searchStrInd = mainTable.SearchString(searchStr);
    if (searchStrInd != -1) cout << "String: " << searchStr << "\nIndex of string: " << searchStrInd;
    else cout << "String is not found";

    return 0;
}
