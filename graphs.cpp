#include <iostream>
#include <ctime>
#include <iomanip>
#include <math.h>

using namespace std;

#define INF 1e30

class Vertex { //с англ. вершина
public:
    //int vertexNum; //номер вершины
    double xVertex = -1, yVertex = -1;

    Vertex() {
        xVertex = (rand() % 100) + 1;
        yVertex = (rand() % 100) + 1;
    }
};

class Edge {
public:
    int aEdge, bEdge; double weight;
    bool operator<(Edge& obj) {
        if (weight != obj.weight) return weight < obj.weight;
        return false;
    }
    Edge& operator=(const Edge& obj) {
        if (this != &obj) {
            aEdge = obj.aEdge;
            bEdge = obj.bEdge;
            weight = obj.weight;
        }
        return *this;
    }
};

class WGraph {
    double** matrix; //матрица смежности
    int verticesNum; //число вершин
    Edge* spanEdges = new Edge[verticesNum*(verticesNum-1)/2]; int spanEdgesNum = 0;
    int compNum;
public:
    WGraph(int k) {
        verticesNum = k;
        matrix = new double*[verticesNum];
        for (int i = 0; i < verticesNum; i++) {
            matrix[i] = new double [verticesNum];
        }
        for (int i = 0; i < verticesNum; i++) {
            for (int j = 0; j < verticesNum; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    ~WGraph() {
        for (int i = 0; i < verticesNum; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void setEdge(int a, int b, double weight);
    void printEdgeMatrix() {
        cout << "\nMatrix:\n";
        for (int i = 0; i < verticesNum; i++) {
            for (int j = 0; j < verticesNum; j++) {
                cout << setw(10) << matrix[i][j] << " ";
            }
            cout << endl;
        }
    };
    Edge* getSpanTree();

    void search(int ver, int* P) {
        P[ver] = compNum;
        for (int j = 0; j < verticesNum; j++)
            if ((matrix[ver][j] > 0) && !P[j])
                search(j, P);
    }
    int* getComp() {
        int* P = new int[verticesNum];
        compNum = 0;
        for (int i = 0; i < verticesNum; i++)
            P[i] = 0;
        for (int i = 0; i < verticesNum; i++)
            if (!P[i]) {
                compNum++;
                search(i, P);
            }
        return P;
    }
};

void WGraph::setEdge(int a, int b, double weight) {
    if (a < 0 || a >= verticesNum) return;
    if (b < 0 || b >= verticesNum) return;
    matrix[a][b] = weight;
    matrix[b][a] = weight;
}

Edge* WGraph::getSpanTree() {
    Edge* span = new Edge[verticesNum - 1];
    double wmin;
    int i, j, vm, * B = new int[verticesNum];
    B[0] = -1;
    for (i = 1; i < verticesNum; i++) B[i] = 0;
    for (i = 1; i < verticesNum; i++) {
        wmin = INF; vm = 0;
        for (j = 1; j < verticesNum; j++)
            if (B[j] != -1 && wmin > matrix[j][B[j]])
            {
                vm = j; wmin = matrix[j][B[j]];
            }
        if (!vm) break; //можно убрать
        span[i - 1].aEdge = vm;
        span[i - 1].bEdge = B[vm];
        span[i - 1].weight = matrix[vm][B[vm]];

        B[vm] = -1;
        for (j = 1; j < verticesNum; j++)
            if (B[j] != -1 && matrix[j][B[j]] > matrix[j][vm])
                B[j] = vm;
    }
    return span;
}

void sortt(Edge* arr, int* ind, int length) {
    int tmp; int step;
    int h, j;
    for (step = length / 2; step > 0; step /= 2)
        for (int i = step; i < length; i++)
        {
            tmp = ind[i];
            for (j = i; j >= step; j -= step)
            {
                if (arr[tmp] < arr[ind[j - step]]) {
                    ind[j] = ind[j - step];
                }
                else {
                    break;
                }
            }
            ind[j] = tmp;
        }
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    Vertex *ver;
    ver = new Vertex[n];
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex" << setw(3) << i << ": x =" << setw(3) << ver[i].xVertex  << ", y =" << setw(3) <<  ver[i].yVertex << endl;
    }
    //убрать edge
    Edge* edge;
    edge = new Edge[n * (n - 1) / 2]; int count = 0;
    WGraph matrixW(n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i != j) {
                edge[count].aEdge = i;
                edge[count].bEdge = j;

                edge[count].weight = pow((pow((ver[i].xVertex-ver[j].xVertex),2) + pow((ver[i].yVertex - ver[j].yVertex), 2)), 0.5);
                matrixW.setEdge(edge[count].aEdge, edge[count].bEdge, edge[count].weight);
                count++;
            }
        }
    }
    cout << endl;
    //вывод всех рёбер и их весов
    /*for (int i = 0; i < n * (n - 1) / 2; i++) {
        cout << "Edge" << setw(3) << i << ": a =" << setw(3) << edge[i].aEdge <<
            ", b =" << setw(3) << edge[i].bEdge << ", weight = " << edge[i].weight << endl;
    }*/
    Edge* span;
    span = matrixW.getSpanTree();
    for (int i = 0; i < n-1; i++) {
        cout << "Span edge" << setw(3) << i << ": a =" << setw(3) << span[i].aEdge <<
            ", b =" << setw(3) << span[i].bEdge << ", weight = " << span[i].weight << endl;
    }

    int* indexMasSort;
    indexMasSort = new int[n - 1];
    for (int i = 0; i < n - 1; i++) {
        indexMasSort[i] = i;
    }
    cout << endl;
    sortt(span, indexMasSort, n - 1);
    for (int i = 0; i < n - 1; i++) {
        cout << "Edge number " << indexMasSort[i] << "   weight " << span[indexMasSort[i]].weight << endl;
    }
    cout << endl;

    int k;
    cout << "Enter number of clusters: ";
    cin >> k; cout << endl;
    int nCl = n - k;
    Edge* edgeCluster;
    edgeCluster = new Edge[nCl]; count = 0;
    WGraph matrixCluster(n);
    for (int i = 0; i < nCl; i++) {
        edgeCluster[i] = span[indexMasSort[i]];
        matrixCluster.setEdge(edgeCluster[i].aEdge, edgeCluster[i].bEdge, edgeCluster[i].weight);
    }
    for (int i = 0; i < nCl; i++) {
        cout << "Edge" << setw(3) << i << ": a =" << setw(3) << edgeCluster[i].aEdge <<
            ", b =" << setw(3) << edgeCluster[i].bEdge << ", weight = " << edgeCluster[i].weight << endl;
    }
    matrixCluster.printEdgeMatrix();
    int* R = matrixCluster.getComp();
    for (int j = 0; j < n; j++) {
        R[j] -= 1;
    }
    cout << endl;
    for (int i = 0; i < k; i++) {
        cout << "Component " << i << " vertices ";
        for (int j = 0; j < n; j++) {
            if (R[j] == i) {
                cout << j << " ";
            }
        }
        cout << endl;
    }


    int compCount;
    Vertex min, max, centroid;

    for (int i = 0; i < k; i++) {
        compCount = 0;
        min.xVertex = 101; min.yVertex = 101;
        max.xVertex = -1; max.yVertex = -1;
        centroid.xVertex = -1; centroid.yVertex = -1;

        for (int j = 0; j < n; j++) {
            if (R[j] == i) {
                compCount++; 

                if (ver[j].xVertex > max.xVertex && ver[j].yVertex > max.yVertex) {
                    max.xVertex = ver[j].xVertex;
                    max.yVertex = ver[j].yVertex;
                }

                if (ver[j].xVertex < min.xVertex && ver[j].yVertex < min.yVertex) {
                    min.xVertex = ver[j].xVertex;
                    min.yVertex = ver[j].yVertex;
                }

                centroid.xVertex += ver[j].xVertex;
                centroid.yVertex += ver[j].yVertex;
            }
        }

        centroid.xVertex /= compCount;
        centroid.yVertex /= compCount;

        cout << "\nComponent " << i << ": \nVertex number = " << compCount <<
            ", min = " << min.xVertex << " " << min.yVertex <<
            ", max = " << max.xVertex << " " << max.yVertex <<
            ", centroid = " << centroid.xVertex << " " << centroid.yVertex << endl;
    }

    return 0;
}
