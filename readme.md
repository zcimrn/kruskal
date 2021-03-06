# Алгоритм Краскала

Данный алгоритм позволяет достаточно эффективно найти минимальное остовное дерево в связном графе

## Постановка задачи

В файле **input.txt** в виде матрицы расстояний записан граф. Требуется найти минимальное остовное дерево с помощью алгоритма Краскала и вывести в файл **output.txt** суммарную длину всех его рёбер, а также сами эти рёбра.

## Псевдокод

    G = граф
    E = список рёбер G
    удаляем все рёбра из G
    сортируем E по неубыванию длин
    T = пустой список рёбер минимального остовного дерева
    для каждого ребра e из E:
        a, b = вершины ребра e
        если a и b находятся в разных компонентах связности G:
            добавить в T ребро e
            объединить компоненты связности a и b ребром e

## Структуры данных

Ребро представлено в виде структуры, где **a** и **b** это вершины, которые ребро соединяет, а **l** это длина ребра
```cpp
struct Edge {
    int a, b, l;

    ...

};
```

Изначальный граф и остовное дерево будем хранить в виде списков рёбер `std::vector<Edge>` 
Для проверки и объединения компонент связности будем использовать СНМ, которая представлена в коде классом `DSU`
```cpp
class DSU {
private:
    std::vector<int> parent, rank;
    int size = 0;

    ...

public:

    ...

    void make_set(int x) { ... }

    int find_set(int x) { ... }

    void union_sets(int a, int b) { ... }
};
```

## Как запускать

Первым делом нужно клонировать репозиторий
```sh
git clone git@github.com:zcimrn/kruskal
cd kruskal
```

После чего собрать с помощью `make`
```sh
make
```

Так как программа планирует читать граф из **input.txt**, необходимо его сгенерировать 
`gen_test` позволяет сгенерировать полный граф, принимает два необязательных параметра:
- `max_node_count` &mdash; количество вершин
- `max_edge_length` &mdash; максимальная длина ребра

```sh
./gen_test 10 100
```

После чего запускаем саму программу
```sh
./kruskal
```

Отлично, программа вывела время работы, а правильный ответ записан в **output.txt**

## Тесты корректности

![image](https://graphonline.ru/tmp/saved/bK/bKZrJfZUzJVmfReO.png)

**input.txt**

    7
    0 7 8 2 ~ ~ 5
    7 0 ~ 7 ~ ~ ~
    8 ~ 0 ~ ~ 2 8
    2 7 ~ 0 ~ 7 ~
    ~ ~ ~ ~ 0 ~ 4
    ~ ~ 2 7 ~ 0 7
    5 ~ 8 ~ 4 7 0

**output.txt**

    27
    1 4
    3 6
    5 7
    1 7
    1 2
    4 6

![image](https://graphonline.ru/tmp/saved/Dg/DgOqdxBzKsnuXqiO.png)

**input.txt**

    7
    0 ~ ~ 4 ~ ~ 9
    ~ 0 ~ ~ 8 ~ ~
    ~ ~ 0 5 3 ~ 2
    4 ~ 5 0 4 5 9
    ~ 8 3 4 0 ~ 2
    ~ ~ ~ 5 ~ 0 ~
    9 ~ 2 9 2 ~ 0

**output.txt**

    25
    3 7
    5 7
    1 4
    4 5
    4 6
    2 5

![image](https://graphonline.ru/tmp/saved/jY/jYJwYQWbdeofNtMc.png)

**input.txt**

    7
    0 6 4 ~ ~ 2 10
    6 0 ~ ~ ~ 7 6
    4 ~ 0 8 6 ~ 10
    ~ ~ 8 0 8 ~ 10
    ~ ~ 6 8 0 4 ~
    2 7 ~ ~ 4 0 9
    10 6 10 10 ~ 9 0

**output.txt**

    30
    1 6
    1 3
    5 6
    1 2
    2 7
    3 4

## Тесты производительности

Проверим время работы на полных графах с разным количеством вершин и максимальной длиной ребра равной 1000000
```sh
./gen_test <количество вершин> 1000000
./kruskal
```

| Количество | Время     |
|          -:|         -:|
|        100 |  0.003927 |
|        200 |  0.015992 |
|        300 |  0.034656 |
|        400 |  0.063029 |
|        500 |  0.099495 |
|        600 |  0.146084 |
|        700 |  0.200686 |
|        800 |  0.267820 |
|        900 |  0.342634 |
|       1000 |  0.419897 |
|       2000 |  1.805504 |
|       3000 |  4.409858 |
|       4000 |  7.823605 |
|       5000 | 12.455837 |
|       6000 | 18.458873 |
|       7000 | 25.120442 |
|       8000 | 33.252308 |
|       9000 | 42.337381 |
|      10000 | 52.894956 |
