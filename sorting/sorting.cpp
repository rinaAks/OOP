#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
//вычисляем шаг - количество элементов / 2 (d)
//рассматриваем элементы 0 и d, затем 1 и d+1 и так далее
//  (то есть к 0 прибавляем d)
//на шаге: если у левого элемента больше значения, то меняем местами (0 и d-тый)
//дошли до n-го элемента - стоп
//меняем шаг, он становится половиной от прошлого шага

class Competition {
public:
    int solvedProblems, score, time, id;

    bool operator<(Competition& obj) {
        if (score != obj.score) return score < obj.score;
        if (time != obj.time) return time > obj.time;
        if (solvedProblems != obj.solvedProblems) return solvedProblems < obj.solvedProblems;
        if (id != obj.id) return id < obj.id;
        //если все равны
        return false;
    }

    friend ostream& operator<<(ostream& stream, Competition& obj) {
        return stream << "Participant " << obj.id <<
            ": score " << obj.score <<
            ", time " << obj.time << 
            ", solved problems " << obj.solvedProblems << endl;
    };

};
int i, j;
int comparHeap = 0;

template<typename Type>
class Sort {
private:
    static void heapify(Type arr[], int n, int i, Type* ind);
    int n; int* mass;
public:
    static int shellSort(Type mass[], int n);
    static int heapSort(Type arr[], int n);
    static int* makeIndMas(int n);
    static bool checkSort(Type* mass, int n, int *ind);
};

template<typename Type>
int Sort<Type>::shellSort(Type mass[], int n) {
    int* ind = makeIndMas(n);

    int tmp; int step;
    int h; int comparShell = 0;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = ind[i];
            for (j = i; j >= step; j -= step)
            {
                if (mass[tmp] < mass[ind[j - step]]) {
                    comparShell++;
                    ind[j] = ind[j - step];
                }
                else {
                    comparShell++;
                    break;
                }
            }
            ind[j] = tmp;
        }
    /*for (h = 1; h <= n / 9; h = h * 3 + 1);
    while (h >= 1)
    {
        for (i = h; i < n; i++) {
            for (j = i - h; j >= 0 && mass[ind[j]]> mass[ind[j + h]]; j -= h) {
                comparShell++;
                swap(ind[j], ind[j + h]);
            }
        }
        h = (h - 1) / 3;
    }*/
    for (i = 0; i < n; i++) {
        cout << mass[ind[i]] << " ";
    }
    if (checkSort(mass, n, ind)) {
        cout << "right! ";
        return comparShell;
    }
    else {
        cout << "wrong! ";
        return -1;
    }
}

template<typename Type>
void Sort<Type>::heapify(Type arr[], int n, int i, Type *ind)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
    if (l < n && arr[ind[l]] > arr[ind[largest]]) {
        largest = l;
    }

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[ind[r]] > arr[ind[largest]]) {
        largest = r;
    }

    // Если самый большой элемент не корень
    if (largest != i) {
        comparHeap++;
        swap(ind[i], ind[largest]);

        heapify(arr, n, largest, ind);
    }
}

template<typename Type>
int Sort<Type>::heapSort(Type arr[], int n)
{
    Type* ind = makeIndMas(n);
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ind);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(ind[0], ind[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0, ind);
    }
    /*for (int i = 0; i < n; i++) {
        cout << arr[ind[i]] << " ";
    }
    cout << endl;*/
    /*cout << "not sorted: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;*/
    if (checkSort(arr, n, ind)) {
        cout << "right! ";
        return comparHeap;
    }
    else {
        cout << "wrong! ";
        return -1;
    }
}

template<typename Type>
int* Sort<Type>::makeIndMas(int n) {
    int* ind;
    ind = new int[n];
    for (i = 0; i < n; i++) {
        ind[i] = i;
    }
    return ind;
}

template<typename Type>
bool Sort<Type>::checkSort(Type *mass, int n, int* ind) {
    for (int i = 0; i < n - 1; i++) {
        if (mass[ind[i+1]] < mass[ind[i]]) {
            return false;
        }
    }
    return true;
}

int* makeMas(int n, int option) {
    int* mass;
    mass = new int[n];
    if (option == 1) {
        for (int i = 0; i < n; i++) {
            mass[i] = rand() % 20;
        }
    }
    if (option == 2) {
        for (int i = 0; i < n; i++) {
            mass[i] = i;
        }
    }
    if (option == 3) {
        for (int i = n, j = 0; i > 0; i--, j++) {
            mass[j] = i;
        }
    }
    for (int i = 0; i < n; i++)
        cout << mass[i] << " ";
    cout << endl;
    return mass;
}


int main() {
    srand(time(NULL));
    int n;
    cout << "Number of participants: ";
    cin >> n;
    //1 - random, 2 - по возрастанию, 3 - по убыванию
    int* mas1 = makeMas(n, 1);
    int* mas2 = makeMas(n, 2);
    int* mas3 = makeMas(n, 3);

    cout << "Shell sort comparisons random: " << Sort<int>::shellSort(mas1, n) << endl;
    cout << "Heap sort comparisons random: " << Sort<int>::heapSort(mas1, n) << endl;
    cout << endl;
    cout << "Shell sort comparisons increase: " << Sort<int>::shellSort(mas2, n) << endl;
    cout << "Heap sort comparisons increase: " << Sort<int>::heapSort(mas2, n) << endl;
    cout << endl;
    cout << "Shell sort comparisons decrease: " << Sort<int>::shellSort(mas3, n) << endl;
    cout << "Heap sort comparisons decrease: " << Sort<int>::heapSort(mas3, n) << endl;
    
    cout << endl;

    Competition* participants;
    participants = new Competition[n];
    for (int i = 0; i < n; i++) {
        participants[i].score = rand() % 101;
        if (participants[i].score != 0) {
            participants[i].solvedProblems = rand() % 11;
        }
        else {
            participants[i].solvedProblems = 0;
        }
        participants[i].time = rand() % 301;
        participants[i].id = i;
    }
    for (int i = 0; i < n; i++) {
        cout << "Participant " << participants[i].id <<
            ": score " << participants[i].score <<
            ", time " << participants[i].time <<
            ", solved problems " << participants[i].solvedProblems << endl;
    }
    cout << endl;
    Sort<Competition>::shellSort(participants, n);
    cout << endl;
}
