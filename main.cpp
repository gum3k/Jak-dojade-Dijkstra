#include <iostream>

using namespace std;


struct Lot {
    char zrodlo[20];
    char cel[20];
    int czas;
};
struct Zapytanie {
    char zrodlo[20];
    char cel[20];
    int typ;
};


struct Vertex {
    int x, y;
    char name[20] = { 0 };
    Vertex(int x, int y) : x(x), y(y) {}
};


struct Edge {
    Vertex* src;
    Vertex* dest;
    int waga;
    Edge(Vertex* src, Vertex* dest, int waga) : src(src), dest(dest), waga(waga) {}
};

class List {
public:
    struct Node {
        Edge* data;
        Node* next;
        Node(Edge* data) : data(data), next(NULL) {}
    };

    Node* head;

    List() : head(NULL) {}

    void add(Edge* data) {
        Node* node = new Node(data);
        node->next = head;
        head = node;
    }

    ~List() {
        Node* node = head;
        while (node != NULL) {
            Node* next = node->next;
            delete node->data;
            delete node;
            node = next;
        }
    }
};

List** createGraph(char** map, int width, int height, Vertex** vertices, Lot* loty, int k, int num_vertices, Vertex** allVertices) {
    int index = 0;
    int nr_nazwy = 0;
    int tymczX = 0;
    int tymczY = 0;
    int indexAll = 0;
    List** graph = new List * [width * height];
    for (int i = 0; i < width * height; i++) {
        graph[i] = new List();
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == '*' || map[y][x] == '#') {
                Vertex* v1 = new Vertex(x, y);
                Vertex* v2;
                if (map[y][x] == '*') {
                    if ((y - 1) > 0 && map[y - 1][x] != '#' && map[y - 1][x] != '.' && map[y - 1][x] != '*') {
                        tymczY = y - 1;
                        tymczX = x;
                    }
                    else if ((y + 1) < height && map[y + 1][x] != '#' && map[y + 1][x] != '.' && map[y + 1][x] != '*') {
                        tymczY = y + 1;
                        tymczX = x;
                    }
                    else if ((x - 1) >= 0 && map[y][x - 1] != '#' && map[y][x - 1] != '.' && map[y][x - 1] != '*') {
                        tymczY = y;
                        tymczX = x - 1;
                    }
                    else if ((x + 1) < width && map[y][x + 1] != '#' && map[y][x + 1] != '.' && map[y][x + 1] != '*') {
                        tymczY = y;
                        tymczX = x + 1;
                    }
                    else if ((y - 1) >= 0 && (x - 1) >= 0 && map[y - 1][x - 1] != '#' && map[y - 1][x - 1] != '.' && map[y - 1][x - 1] != '*') {
                        tymczY = y - 1;
                        tymczX = x - 1;
                    }
                    else if ((y + 1) < height && (x + 1) < width && map[y + 1][x + 1] != '#' && map[y + 1][x + 1] != '.' && map[y + 1][x + 1] != '*') {
                        tymczY = y + 1;
                        tymczX = x + 1;
                    }
                    else if ((y - 1) >= 0 && (x + 1) < width && map[y - 1][x + 1] != '#' && map[y - 1][x + 1] != '.' && map[y - 1][x + 1] != '*') {
                        tymczY = y - 1;
                        tymczX = x + 1;
                    }
                    else if ((y + 1) < height && (x - 1) >= 0 && map[y + 1][x - 1] != '#' && map[y + 1][x - 1] != '.' && map[y + 1][x - 1] != '*') {
                        tymczY = y + 1;
                        tymczX = x - 1;
                    }
                    while ((tymczX - 1) >= 0 && map[tymczY][tymczX - 1] >= 'A' && map[tymczY][tymczX - 1] <= 'Z') {
                        if (tymczX > 0)
                            tymczX--;
                    }
                    while (tymczY < height && tymczX < width && ((map[tymczY][tymczX] >= 'A' && map[tymczY][tymczX] <= 'Z') || (map[tymczY][tymczX] >= '0' && map[y][tymczX] <= '9'))) {
                        v1->name[nr_nazwy] = map[tymczY][tymczX];
                        tymczX++;
                        nr_nazwy++;
                    }
                    nr_nazwy = 0;
                    vertices[index] = v1;
                    allVertices[indexAll] = v1;
                    indexAll++;
                    index++;
                }
                else {
                    allVertices[indexAll] = nullptr;
                    indexAll++;
                }
                if ((x - 1) >= 0 && (map[y][x - 1] == '#' || map[y][x - 1] == '*')) {
                    v2 = new Vertex(x - 1, y);
                    graph[y * width + x]->add(new Edge(v1, v2, 1));
                    graph[y * width + x - 1]->add(new Edge(v2, v1, 1));
                }
                if ((y - 1) >= 0 && (map[y - 1][x] == '#' || map[y - 1][x] == '*')) {
                    v2 = new Vertex(x, y - 1);
                    graph[y * width + x]->add(new Edge(v1, v2, 1));
                    graph[(y - 1) * width + x]->add(new Edge(v2, v1, 1));
                }
                if ((x + 1) < width && (map[y][x + 1] == '#' || map[y][x + 1] == '*')) {
                    v2 = new Vertex(x + 1, y);
                    graph[y * width + x]->add(new Edge(v1, v2, 1));
                    graph[y * width + x + 1]->add(new Edge(v2, v1, 1));
                }
                if ((y + 1) < height && (map[y + 1][x] == '#' || map[y + 1][x] == '*')) {
                    v2 = new Vertex(x, y + 1);
                    graph[y * width + x]->add(new Edge(v1, v2, 1));
                    graph[(y + 1) * width + x]->add(new Edge(v2, v1, 1));
                }
            }
            else {
                allVertices[indexAll] = nullptr;
                indexAll++;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        Vertex* v1 = nullptr;
        Vertex* v2 = nullptr;
        int twoCities = 0;
        for (int j = 0; j < num_vertices; j++) {
            if (strcmp(loty[i].zrodlo, vertices[j]->name) == 0) {
                v1 = vertices[j];
                twoCities++;
            }
            if (strcmp(loty[i].cel, vertices[j]->name) == 0) {
                v2 = vertices[j];
                twoCities++;
            }
            if (twoCities == 2) {
                break;
            }
        }
        graph[v1->y * width + v1->x]->add(new Edge(v1, v2, loty[i].czas));
    }
    return graph;
}

void dijkstra(List** graph, int width, int height, char* nameStart, char* nameEnd, int* dist, int* prev, Vertex** vertices, int num_verticles, Vertex** AllVertices, int CzyWypisz) {
    Vertex* start = nullptr;
    Vertex* end = nullptr;
    int index = 0;
    int numVertices = width * height;
    int twoCities = 0;
    for (int i = 0; i < num_verticles; i++) {
        if (strcmp(vertices[i]->name, nameStart) == 0) {
            start = vertices[i];
            twoCities++;
        }
        if (strcmp(vertices[i]->name, nameEnd) == 0) {
            end = vertices[i];
            twoCities++;
        }
        if (twoCities == 2) {
            break;
        }
    }
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[start->y * width + start->x] = 0;

    Vertex** queue = new Vertex * [numVertices];
    int queueSize = 0;

    queue[queueSize++] = start;
    while (queueSize > 0) {
        int minDistIndex = 0;
        for (int i = 1; i < queueSize; i++) {
            if (dist[queue[i]->y * width + queue[i]->x] < dist[queue[minDistIndex]->y * width + queue[minDistIndex]->x])
                minDistIndex = i;
        }
        Vertex* u = queue[minDistIndex];

        queue[minDistIndex] = queue[--queueSize];

        List::Node* curr = graph[u->y * width + u->x]->head;
        while (curr != NULL) {
            Vertex* v = curr->data->dest;
            int alt = dist[u->y * width + u->x] + curr->data->waga;
            if (alt < dist[v->y * width + v->x]) {
                dist[v->y * width + v->x] = alt;
                prev[v->y * width + v->x] = u->y * width + u->x;

                queue[queueSize++] = v;
            }
            curr = curr->next;
        }
    }
    int* path = new int[numVertices];
    int current = end->y * width + end->x;
    while (current != -1) {
        path[index] = current;
        current = prev[current];
        index++;
    }
    cout << dist[end->y * width + end->x];
    if (CzyWypisz == 1) {
        for (int i = numVertices - 1; i >= 0; i--) {
            if (path[i] >= 0 && path[i] < numVertices && AllVertices[path[i]] != NULL && (strcmp(AllVertices[path[i]]->name, nameStart) != 0) && (strcmp(AllVertices[path[i]]->name, nameEnd) != 0)) {

                putchar(' ');
                fputs(AllVertices[path[i]]->name, stdout);
            }
        }
    }
    delete[] visited;
    delete[] path;
}


int main()
{
    int num_verticles = 0;
    int w, h, k, q;
    Vertex** vertices;
    Lot* loty;
    Zapytanie* zapytania;
    char** mapa;
    cin >> w >> h;
    Vertex** AllVertices = new Vertex * [w * h];
    mapa = new char* [h];
    for (int i = 0; i < h; i++)
        mapa[i] = new char[w];

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            mapa[i][j] = _getchar_nolock();
            while (mapa[i][j] == '\n' || mapa[i][j] == ' ') {
                mapa[i][j] = _getchar_nolock();
            }
        }
    }


    cin >> k;
    loty = new Lot[k];

    for (int i = 0; i < k; i++) {
        cin >> loty[i].zrodlo;
        cin >> loty[i].cel;
        cin >> loty[i].czas;
    }


    cin >> q;
    zapytania = new Zapytanie[q];

    for (int i = 0; i < q; i++) {
        cin >> zapytania[i].zrodlo;
        cin >> zapytania[i].cel;
        cin >> zapytania[i].typ;
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (mapa[i][j] == '*') {
                num_verticles++;
            }
        }
    }
    vertices = new Vertex * [num_verticles];
    List** graf = createGraph(mapa, w, h, vertices, loty, k, num_verticles, AllVertices);
    int* dist = new int[w * h];
    int* prev = new int[w * h];
    for (int i = 0; i < q; i++) {
        dijkstra(graf, w, h, zapytania[i].zrodlo, zapytania[i].cel, dist, prev, vertices, num_verticles, AllVertices, zapytania[i].typ);
        cout << endl;
    }

    for (int i = 0; i < h; i++) {
        delete[] mapa[i];
    }
    delete[] mapa;

    delete[] loty;
    delete[] zapytania;

    delete[] AllVertices;

    delete[] dist;
    delete[] prev;

    delete[] vertices;

    for (int i = 0; i < h * w; i++) {
        delete graf[i];
    }
    delete[] graf;

    return 0;
}
