#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define MAX_POINTS 10000

// Прототипи функцій
double function(double x);
double derivative(double x);

int main(void)
{
    double x1, x2, delta, x;
    unsigned int n, i;
    int choice;

    // Налаштовуємо консоль Windows для виведення українських літер у UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    printf("Лабораторна робота № 3. Дослідження функції. Варіант 16\n");
    printf("1 - Ввести X1, X2 та кількість точок N\n");
    printf("2 - Ввести X1, X2 та крок delta\n");
    printf("Оберіть спосіб введення (1 або 2): ");

    // Перевіряємо вибір способу введення
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Помилка: потрібно ввести 1 або 2.\n");
        return 1;
    }

    // Введення початкового значення аргументу
    printf("Введіть початкове значення X1: ");
    if (scanf("%lf", &x1) != 1) {
        printf("Помилка введення X1.\n");
        return 1;
    }

    // Введення кінцевого значення аргументу
    printf("Введіть кінцеве значення X2: ");
    if (scanf("%lf", &x2) != 1) {
        printf("Помилка введення X2.\n");
        return 1;
    }

    // Перевіряємо, щоб початкове значення було меншим за кінцеве
    if (x1 >= x2) {
        printf("Помилка: X1 має бути меншим за X2.\n");
        return 1;
    }

    if (choice == 1) {
        // Перший спосіб: користувач вводить кількість точок
        printf("Введіть кількість точок N (від 2 до %d): ", MAX_POINTS);
        if (scanf("%u", &n) != 1 || n < 2 || n > MAX_POINTS) {
            printf("Помилка: N має бути в межах від 2 до %d.\n", MAX_POINTS);
            return 1;
        }

        // Знаходимо крок між точками
        delta = (x2 - x1) / (n - 1);
    } else {
        // Другий спосіб: користувач вводить крок зміни аргументу
        printf("Введіть крок delta: ");
        if (scanf("%lf", &delta) != 1 || delta <= 0 || delta > x2 - x1) {
            printf("Помилка: delta має бути більше за 0 і не більше за X2-X1.\n");
            return 1;
        }

        // Перевіряємо, щоб кількість точок не була завеликою
        if ((x2 - x1) / delta > MAX_POINTS - 1) {
            printf("Помилка: зменште кількість точок, збільшивши delta.\n");
            return 1;
        }

        // Обчислюємо кількість точок для заданого кроку
        n = (unsigned int)((x2 - x1) / delta + 1e-9) + 1;
    }

    // Виводимо початкові дані
    printf("\nПочаткові дані:\n");
    printf("X1 = %.6f\n", x1);
    printf("X2 = %.6f\n", x2);
    printf("Крок delta = %.6f\n", delta);
    printf("Кількість точок N = %u\n", n);

    // Таблиця значень початкової функції
    printf("\nТаблиця значень функції f(x):\n");
    printf("--------------------------------------------------\n");
    printf("| № точки |       x        |        f(x)         |\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        x = x1 + i * delta;
        printf("| %7u | %14.6f | %19.6f |\n", i + 1, x, function(x));
    }

    printf("--------------------------------------------------\n");

    // Таблиця значень похідної функції
    printf("\nТаблиця значень похідної f'(x):\n");
    printf("--------------------------------------------------\n");
    printf("| № точки |       x        |       f'(x)         |\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        x = x1 + i * delta;
        printf("| %7u | %14.6f | %19.6f |\n", i + 1, x, derivative(x));
    }

    printf("--------------------------------------------------\n");
    return 0;
}

// Обчислення функції для 16-го варіанта
// f(x) = (x - 50) * cos(x / 10) - 3*x + 500
// Аргумент функції cos задається в радіанах
double function(double x)
{
    return (x - 50.0) * cos(x / 10.0) - 3.0 * x + 500.0;
}

// Чисельне обчислення похідної методом центральної різниці
double derivative(double x)
{
    double h = 0.0001;
    return (function(x + h) - function(x - h)) / (2.0 * h);
}
