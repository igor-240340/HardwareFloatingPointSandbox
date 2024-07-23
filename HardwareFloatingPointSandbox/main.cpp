#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <math.h>

#include <ctype.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

using namespace std;

void print_float_as_hex(float* a) {
    uint32_t intRep = *(uint32_t*)a;
    std::cout << std::hex << std::setfill('0') << std::setw(8) << intRep << std::endl;
}

void print_double_as_hex(double* a) {
    uint64_t intRep = *(uint64_t*)a;
    std::cout << std::hex << std::setfill('0') << std::setw(16) << intRep << std::endl;
}

void neg_inf() {
    float a = -1.0f;
    float b = 0.0f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << c << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    print_float_as_hex(&c);

    std::cout << '\n';
}

void pos_inf() {
    float a = 1.0f;
    float b = 0.0f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << c << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    print_float_as_hex(&c);

    std::cout << '\n';
}

void q_nan_pos() {
    uint32_t intRep = 0x7f800001;
    float a = *(float*)&intRep;
    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;

    print_float_as_hex(&a);

    std::cout << '\n';
}

void q_nan_neg() {
    uint32_t intRep = 0xff800001;
    float a = *(float*)&intRep;
    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;

    print_float_as_hex(&a);

    std::cout << '\n';
}

void sig_nan() {
    float a = 0.0f;
    float b = 0.0f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << c << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    print_float_as_hex(&c);

    std::cout << '\n';
}

void special_values() {
    neg_inf();
    pos_inf();
    sig_nan();
    q_nan_pos();
    q_nan_neg();
}

void func1() {
    float a = ((powf(2, 24) - 1) * powf(2, -23)) * powf(2, -126);
    float b = a - powf(2, -126);
    float c = powf(2, -126 - 23);
    // double d = powl(2, -150);
    float d = powf(2, -150);
    // float e = ( (powf(2, 24) - 1) * powf(2, -23) ) * powf(2, 128);
    float e = 340282346638528859811704183484516925440.0f;

    // std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    // std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    // std::cout << std::fixed << std::setprecision(150) << c << std::endl;
    // std::cout << std::fixed << std::setprecision(200) << d << std::endl;
    std::cout << std::fixed << std::setprecision(200) << e << std::endl;
}

// Суммирование со значениями с полной потерей точности при выравнивании
// порядка.
void func2() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = a + powl(2, -26);

    std::cout << std::fixed << std::setprecision(149) << b << std::endl;
}

void func3() {
    float a = powl(2, -26);
    float b = a + powl(2, -27);

    std::cout << std::fixed << std::setprecision(149) << a << std::endl;
    std::cout << std::fixed << std::setprecision(149) << b << std::endl;
    std::cout << std::fixed << std::setprecision(149) << abs(a - b) << std::endl;
}

void func4() {
    float a = 1.875f;
    float b = (powl(2, 24) - 1) * powl(2, -27);
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

void func5() {
    float a = 1.9921875f;
    float b = 0.0078124399296939373016357421875f;
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Пример, в котором округление перед денормализацией даёт в результате большую
// разницу с истинной суммой.
void func6() {
    float a = 1.99999988079071044921875f;
    float b = 0.124999992549419403076171875f;
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Пример для значений, сумма которых без переполнения, но при округлении
// возникает переполнение.
void func7() {
    float a = 1.99999988079071044921875f;
    // 0.5960465188081798260100185871124267578125E-7
    float b = powl(2, -24) + powl(2, -47);
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Пример для значений, сумма которых без переполнения, но при округлении
// возникает переполнение, при этом возникает превышение максимального значения
// экспоненты.
void func8() {
    float a = 1.99999988079071044921875f * powl(2, 127);
    // 0.5960465188081798260100185871124267578125E-7 * 2E-127
    float b = (powl(2, -24) + powl(2, -47)) * powl(2, 127);
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Максимальная сумма для точных значений B меньше единицы.
void func9() {
    float a = 1.99999988079071044921875f;
    float b = 0.999999940395355224609375f;
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Суммирование значений от 1 до максимального с округлением к четному.
void func10() {
    float a = 1.87501513957977294921875f;
    float b = 1.875f;
    float c = a + b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Пример к выяснению роли G-бита.
void func11() {
    float a = 1.0f;
    float b = powl(2, -23) + powl(2, -24) + powl(2, -25) + powl(2, -29);
    float c = a - b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Второй пример к выяснению роли G-бита.
void func12() {
    float a = 1.0f;
    float b = powl(2, -24) + powl(2, -26);
    float c = a - b;

    std::cout << std::fixed << std::setprecision(100) << a << std::endl;
    std::cout << std::fixed << std::setprecision(100) << b << std::endl;
    std::cout << std::fixed << std::setprecision(100) << c << std::endl;
}

// Минимальное денормализованное число.
void func13() {
    float a = powl(2, -149);
    float a2 = powl(2, -150);
    float a3 = -powl(2, -150);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << a2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << a3 << std::endl;
}

// Результат вычитания - минимальное денормализованное число.
void func14() {
    float a = powl(2, -126);
    float b = (powl(2, 23) - 1) * (powl(2, -23)) * powl(2, -126);
    float c = a - b;

    assert(c == powl(2, -149));

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Попытка определить денормализованное число за пределами минимального.
// Округляется до ближайшего.
void func15() {
    float a = powl(2, -126);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -127);
    float c = a - b;

    assert(c == 0);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Попытка определить отрицательное денормализованное число за пределами
// минимального.
// Округляется до отрицательного нуля.
void func16() {
    float a = powl(-2, -151);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << -0 + (-0) << std::endl;
}

// Сложение с наименьшим из множества с полной потерей бит.
// Меньшее значение на время вычисления суммы округляется до 2^-26.
void func17() {
    float a = 1.0f;
    float b = powl(2, -126);
    float c = a + b;

    assert(c == 1.0f);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Сложение с множеством с частичной потерей бит.
// Переполнение при округлении.
void func18() {
    float a = 1.99609375f;
    float b = 0.00390620506368577480316162109375f;
    float c = a + b;

    assert(c == 2.0f);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Сложение с множеством с частичной потерей бит.
// Переполнение при сложении.
void func19() {
    float a = 1.998046875f;
    float b = 0.00390620506368577480316162109375f;
    float c = a + b;

    assert(c == 2.001953125f);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Сложение с множеством с частичной потерей бит.
// Переполнение при округлении. Экспонента достигла максимума.
void func20() {
    float a = 1.99609375f * powl(2, 127);
    float b = 0.00390620506368577480316162109375f * powl(2, 127);
    float c = a + b;

    assert(c == std::numeric_limits<float>::infinity());

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Сложение с множеством с частичной потерей бит.
// Переполнение при сложении. Экспонента достигла максимума.
void func21() {
    float a = -1.998046875f * powl(2, 127);
    float b = -0.00390620506368577480316162109375f * powl(2, 127);
    float c = a + b;

    assert(c == -std::numeric_limits<float>::infinity());

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Сложение с множеством с частичной потерей бит.
// Одинаковый результат для серии разных значений.
// Результат совпадает еще до этапа округления, когда входные значения B
// округляются до нечетного S-бита.
void func22() {
    float a = 1.99609375f;

    float b1 = 0.00390620506368577480316162109375f;
    float b2 = 0.00390620506368577480316162109375f - powl(2, -32);
    float b3 = b2 - powl(2, -32);

    assert(b2 == 0.0039062048308551311492919921875f);
    assert(b3 == 0.00390620459802448749542236328125f);

    float c1 = a + b1;
    float c2 = a + b2;
    float c3 = a + b3;

    assert(c1 == 2.0f);
    assert(c2 == 2.0f);
    assert(c3 == 2.0f);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b3 << std::endl;
    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c3 << std::endl;
}

// Сложение с множеством без потери бит.
// Переполнение при сложении. Округление требуется.
void func23() {
    float a = 1.998046875f;
    float b = 0.00390613079071044921875f;
    float c = a + b;

    assert(c == 2.001953125f);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Сложение с множеством без потери бит, значения которого эквивалентны
// множеству A.
// Пример округления к четному.
void func24() {
    float a = 1.99999988079071044921875f;
    float b = 1.0f;
    float c = a + b;

    assert(c == 3.0f);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

void test_add() {
    // func1();
    // func2();
    // func3();
    // func4();
    // func5();
    // func6();
    // func7();
    // func8();
    // func9();
    // func10();
    // func11();
    // func12();
    // func13();
    // func14();
    // func15();
    // func16();
    // func17();

    // func18();
    // func19();
    // func20();
    // func21();
    // func22();
    // func23();
    func24();
}

// Умножение.
// Переполнения нет после перемножения мантисс.
// Переполнение есть после сложения экспонент.
void func25() {
    float a = 1.25f * powl(2, 127);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    assert(c == std::numeric_limits<float>::infinity());

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнения нет после перемножения мантисс.
// Переполнения нет после сложения экспонент.
void func26() {
    float a = 1.25f * powl(2, 126);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Переполнения нет после сложения экспонент.
// Переполнение после сдвига вправо.
void func27() {
    float a = 1.75f * powl(2, 126);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    assert(c == std::numeric_limits<float>::infinity());

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнения нет после перемножения мантисс.
// Антипереполнение есть после сложения экспонент.
// Переход к денормализованному числу и округление до нуля.
void func28() {
    float a = 1.25f * powl(2, -126);
    float b1 = 1.5f * powl(2, -24);
    float b2 = 1.5f * powl(2, -24 - 1); // Сдвигаемся еще на один бит вправо,
    // чтобы R-бит стал нулевым.
    float c1 = a * b1;
    float c2 = a * b2;

    assert(c1 == powl(2, -23) * powl(2, -126));
    assert(c2 == 0);

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c2 << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Переполнения нет после сложения экспонент.
// Переполнения нет после сдвига вправо.
void func29() {
    float a = 1.75f * powl(2, 125);
    float b = 1.5f * powl(2, 1);

    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Переполнения нет после сложения экспонент.
// Переполнение есть после сдвига вправо.
void func30() {
    float a = 1.75f * powl(2, 126);
    float b = 1.5f * powl(2, 1);

    float c = a * b;

    assert(c == std::numeric_limits<float>::infinity());

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Антипереполнения нет после сложения экспонент.
// Ни переполнения ни антипереполнения нет после сдвига вправо.
// Результат - нормализованное число.
void func31() {
    float a = 1.75f * powl(2, -125);
    float b = 1.5f * powl(2, -1);

    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Антипереполнение есть после сложения экспонент.
// Ни переполнения ни антипереполнения нет после сдвига вправо.
// Результат - нормализованное число.
void func32() {
    float a = 1.75f * powl(2, -126);
    float b = 1.5f * powl(2, -1);

    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Антипереполнение есть после сложения экспонент.
// Антипереполнение есть после сдвига вправо.
// Результат - денормализованное число.
void func33() {
    float a = 1.75f * powl(2, -126);
    float b = 1.5f * powl(2, -2);

    float c = a * b;

    assert(c < powl(2, -126));

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
    std::cout << std::fixed << c << std::endl;
}

// Умножение.
// Переполнение есть после перемножения мантисс.
// Переполнения нет после сложения экспонент (разные знаки).
// Переполнения нет после сдвига вправо.
void func34() {
    float a = 1.75f * powl(2, 127);
    float b = 1.5f * powl(2, -1);

    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
    std::cout << std::fixed << c << std::endl;
}

// Умножение.
// Произведение максимальных значений мантисс.
// Округление.
void func35() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
    std::cout << std::fixed << c << std::endl;
}

// Умножение.
// Произведение максимальных значений мантисс.
// Точное значение.
void func36() {
    double a = (powl(2, 24) - 1) * powl(2, -23);
    double b = (powl(2, 24) - 1) * powl(2, -23);
    double c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

void test_mul() {
    // func25();
    // func26();
    // func27();
    // func28();
    // func29();
    // func30();
    // func31();
    // func32();
    // func33();
    // func34();
    // func35();
    // func36();
}

/*
 * К ручной реализации всех случаев.
 */

 // Умножение.
 // Произведение мантисс: переполнения нет.
 // Сложение экспонент: одинаковые знаки, положительные, переполнения нет.
 // В таблице: случай 1.
void func37() {
    float a = 1.25f * powl(2, 126);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (одинаковые знаки, положительные): переполнения нет.
// Сдвиг мантиссы вправо и коррекция экспоненты: переполнения нет.
// В таблице: случай 2.
void func38() {
    float a = 1.75f * powl(2, 125);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (одинаковые знаки, положительные): переполнения нет.
// Сдвиг мантиссы вправо и коррекция экспоненты: переполнение есть.
// В таблице: случай 3.
void func39() {
    float a = 1.75f * powl(2, 126);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a2 = 1.75f * powl(2, 126);
    double b2 = 1.5f * powl(2, 1);
    double c2 = a2 * b2;

    std::cout << std::fixed << std::setprecision(200) << a2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c2 << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (одинаковые знаки, положительные): переполнение есть.
// Сдвиг мантиссы вправо и коррекция экспоненты: переполнение есть.
// В таблице: случай 4.
void func40() {
    float a = 1.75f * powl(2, 127);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a2 = 1.75f * powl(2, 127);
    double b2 = 1.5f * powl(2, 1);
    double c2 = a2 * b2;

    std::cout << std::fixed << std::setprecision(200) << a2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b2 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c2 << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (одинаковые знаки, отрицательные): антипереполнения нет.
// Сдвиг мантиссы вправо и коррекция экспоненты: антипереполнения нет.
// В таблице: случай 5.
void func41() {
    float a = 1.75f * powl(2, -125);
    float b = 1.5f * powl(2, -1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (одинаковые знаки, отрицательные): антипереполнение есть.
// Сдвиг мантиссы вправо и коррекция экспоненты: антипереполнения нет.
// В таблице: случай 6.
void func42() {
    float a = 1.75f * powl(2, -126);
    float b = 1.5f * powl(2, -1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (одинаковые знаки, отрицательные): антипереполнение есть.
// Сдвиг мантиссы вправо и коррекция экспоненты: антипереполнения есть.
// Результат - денормализованное число.
// В таблице: случай 7.
void func43() {
    float a = 1.75f * powl(2, -126);
    float b = 1.5f * powl(2, -2);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнение есть.
// Сложение экспонент (разные знаки): переполнения/антипереполнения нет и быть
// не может (для нормализованных операндов).
// Сдвиг мантиссы вправо и коррекция экспоненты: антипереполнения
// есть. Результат - нормализованное число.
// В таблице: случай 8.
void func44() {
    float a = 1.75f * powl(2, 127);
    float b = 1.5f * powl(2, -1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнения нет.
// Сложение экспонент (разные знаки): переполнения/антипереполнения нет и быть
// не может (для нормализованных операндов).
// Результат - нормализованное число.
// В таблице: случай 9.
void func45() {
    float a = 1.25f * powl(2, -126);
    float b = 1.5f * powl(2, +1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнения нет.
// Сложение экспонент (одинаковые знаки, отрицательные): антипереполнения нет.
// Результат - нормализованное число.
// В таблице: случай 10.
void func46() {
    float a = 1.25f * powl(2, -125);
    float b = 1.5f * powl(2, -1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнения нет.
// Сложение экспонент (одинаковые знаки, отрицательные): антипереполнение есть.
// Результат - ноль или денормализованное число.
// В таблице: случай 11.
void func47() {
    float a = 1.25f * powl(2, -126);
    float b = 1.5f * powl(2, -1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Умножение.
// Произведение мантисс: переполнения нет.
// Сложение экспонент (одинаковые знаки, положительные): переполнение есть.
// Результат - inf.
// В таблице: случай 12.
void func48() {
    float a = 1.25f * powl(2, 127);
    float b = 1.5f * powl(2, 1);
    float c = a * b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

void test_mul2() {
    // func37();
    // func38();
    // func39();
    // func40();
    // func41();
    // func42();
    // func43();
    // func44();
    // func45();
    // func46();
    // func47();
    func48();
}

// Умножение.
// Произведение мантисс: переполнения нет, округление в меньшую сторону.
// Сложение экспонент (одинаковые знаки, положительные): переполнения нет.
// Результат - округленное число.
// В таблице: случай 1 для RGS.
void func49() {
    float a = (1.0f + powl(2, -23)) * powl(2, 126);
    float b = (1.0f + powl(2, -23)) * powl(2, 1);
    float c = a * b;

    double a1 = (1.0f + powl(2, -23)) * powl(2, 126);
    double b1 = (1.0f + powl(2, -23)) * powl(2, 1);
    double c1 = a1 * b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Умножение.
// Произведение мантисс: переполнения нет, округление.
// Сложение экспонент (одинаковые знаки, отрицательные): антипереполнения нет.
// Результат - округленное число.
// В таблице: случай 10 для RGS.
void func50() {
    float a = 1.82358515262603759765625f * powl(2, -125);
    float b = 1.09674060344696044921875f * powl(2, -1);
    float c = a * b;

    double a1 = 1.82358515262603759765625f * powl(2, -125);
    double b1 = 1.09674060344696044921875f * powl(2, -1);
    double c1 = a1 * b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Умножение.
// Произведение нормализованного и денормализованного числа.
// Произведение мантисс: переполнения нет, округление.
// Сложение экспонент (разные знаки): антипереполнения нет (вообще, зависит от
// реализации). Результат - округленное денормализованное число.
// В таблице: случай без нормализации для RGS.
void func51() {
    float a = (powl(2, -23) + powl(2, -22) + powl(2, -21)) * powl(2, -126);
    float b = 1.0f + powl(2, -23);
    float c = a * b;

    double a1 = (powl(2, -23) + powl(2, -22) + powl(2, -21)) * powl(2, -126);
    double b1 = 1.0f + powl(2, -23);
    double c1 = a1 * b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Умножение.
// Произведение нормализованного и денормализованного числа.
// Произведение мантисс: переполнения нет, округление.
// Сложение экспонент (разные знаки): антипереполнения нет.
// Результат - округленное нормализованное число.
//
// NOTE: это пример к вопросу о необходимости предварительной нормализации перед
// умножением. Да, предварительная нормализация действительно нужна и даст
// повышенную точность в некоторых случаях, как этот.
// В таблице: случай с нормализацией для RGS.
void func52() {
    float a = (powl(2, -23) + powl(2, -22) + powl(2, -21)) * powl(2, -126);
    float b = (1.0f + powl(2, -23)) * powl(2, 30);
    float c = a * b;

    double a1 = (powl(2, -23) + powl(2, -22) + powl(2, -21)) * powl(2, -126);
    double b1 = (1.0f + powl(2, -23)) * powl(2, 30);
    double c1 = a1 * b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Для проверки умножения по схеме с RGS-битами.
void test_mul3() {
    // func49();
    // func50();
    // func51();
    func52();
}

// Деление.
// На выходе - нормализованное значение.
void func53() {
    float a = 1.82358515262603759765625f * powl(2, -125);
    float b = 1.09674060344696044921875f * powl(2, -1);
    float c = a / b;

    double a1 = 1.82358515262603759765625 * powl(2, -125);
    double b1 = 1.09674060344696044921875 * powl(2, -1);
    double c1 = a1 / b1;

    long double a2 = 1.82358515262603759765625 * powl(2, -125);
    long double b2 = 1.09674060344696044921875 * powl(2, -1);
    long double c2 = a2 / b2;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(300) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(300) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(300) << c1 << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(300) << a2 << std::endl;
    std::cout << std::fixed << std::setprecision(300) << b2 << std::endl;
    std::cout << std::fixed << std::setprecision(300) << c2 << std::endl;
}

// Деление.
// На выходе - денормализованное значение.
void func54() {
    float a = 0.5f;
    float b = 340282346638528859811704183484516925440.0f;
    float c = a / b;

    double a1 = 0.5;
    double b1 = 340282346638528859811704183484516925440.0;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Минимальная мантисса.
void func55() {
    float a = 1.0f;
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Деление.
// Максимальная мантисса.
void func56() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = 1.0f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Деление.
// Истинный результат: бесконечная периодическая дробь.
// Фактический результат: округленное значение.
void func57() {
    float a = 1.0f;
    float b = 0.666666686534881591796875f;
    float c = a / b;

    double a1 = 1.0f;
    double b1 = 0.666666686534881591796875f;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 1: нормализованная бесконечная периодическая дробь.
void func58() {
    float a = 1.26563179492950439453125f;
    float b = 1.25024521350860595703125f;
    float c = a / b;

    double a1 = 1.26563179492950439453125;
    double b1 = 1.25024521350860595703125;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Конечная дробь.
void func59() {
    float a = 1.875f;
    float b = 1.5f;
    float c = a / b;

    double a1 = 1.875;
    double b1 = 1.5;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Бесконечная периодическая дробь.
void func60() {
    float a = 1.8750002384185791015625f;
    float b = 1.50000011920928955078125f;
    float c = a / b;

    double a1 = 1.8750002384185791015625;
    double b1 = 1.50000011920928955078125;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
void func61() {
    float a = 1.82358515262603759765625f * powl(2, -125);
    float b = 1.50000011920928955078125f;
    float c = a / b;

    double a1 = 1.82358515262603759765625f * powl(2, -125);
    double b1 = 1.50000011920928955078125;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Наименьшее возможное частное двух мантисс.
// Денормализация вправо на 1 разряд.
// Истинное значение - бесконечная периодическая дробь.
void func62() {
    float a = 1.0f;
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.0f;
    double b1 = (powl(2, 24) - 1) * powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Наименьшее возможное частное двух мантисс.
// Денормализация вправо на 1 разряд.
// Истинное значение - бесконечная периодическая дробь.
// Возвращаемся к делимому.
void func63() {
    float a = 1.0f;
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    double a1 = 1.0f;
    double b1 = (powl(2, 24) - 1) * powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c * b << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 * b1 << std::endl;
}

// Деление.
// Денормализация вправо на 1 разряд.
// Истинное значение - конечная дробь.
// Округление не требуется.
void func64() {
    float a = powl(2, 0) + powl(2, -2) + powl(2, -4);
    float b = powl(2, 0) + powl(2, -1) + powl(2, -2);
    float c = a / b;

    double a1 = powl(2, 0) + powl(2, -2) + powl(2, -4);
    double b1 = powl(2, 0) + powl(2, -1) + powl(2, -2);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Денормализации нет.
// Истинное значение - конечная дробь.
// Округление не требуется.
void func65() {
    float a = powl(2, 0) + powl(2, -1) + powl(2, -3) + powl(2, -4);
    float b = powl(2, 0) + powl(2, -1);
    float c = a / b;

    double a1 = powl(2, 0) + powl(2, -1) + powl(2, -3) + powl(2, -4);
    double b1 = powl(2, 0) + powl(2, -1);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Денормализации нет.
// Истинное значение - бесконечная периодическая дробь.
void func66() {
    float a = powl(2, 0) + powl(2, -1) + powl(2, -3) + powl(2, -4) +
        powl(2, -10) + powl(2, -14) + powl(2, -18);
    float b = powl(2, 0) + powl(2, -7) + powl(2, -10) + powl(2, -14);
    float c = a / b;

    double a1 = powl(2, 0) + powl(2, -1) + powl(2, -3) + powl(2, -4) +
        powl(2, -10) + powl(2, -14) + powl(2, -18);
    double b1 = powl(2, 0) + powl(2, -7) + powl(2, -10) + powl(2, -14);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 1: денормализованная бесконечная периодическая дробь.
void case_1() {
    float a = 1.0f;
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    double a1 = 1.0;
    double b1 = (powl(2, 24) - 1) * powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 2: нормализованная бесконечная периодическая дробь.
void case_2() {
    float a = 1.688541412353515625f;
    float b = 1.00885009765625f;
    float c = a / b;

    double a1 = 1.688541412353515625;
    double b1 = 1.00885009765625;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 3: денормализованная конечная дробь.
void case_3() {
    float a = 1.3125f;
    float b = 1.75f;
    float c = a / b;

    double a1 = 1.3125;
    double b1 = 1.75;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 4: нормализованная конечная дробь.
void case_4() {
    float a = 1.6875f;
    float b = 1.5f;
    float c = a / b;

    double a1 = 1.6875;
    double b1 = 1.5;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 5: целоичесленные единицы, деление делимого на себя.
void case_5() {
    float a = 1.99999988079071044921875f;
    float b = 1.99999988079071044921875f;
    float c = a / b;

    double a1 = 1.99999988079071044921875;
    double b1 = 1.99999988079071044921875;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление.
// Случай 6: исходное делимое, деление делимого на единицу.
void case_6() {
    float a = 1.99999988079071044921875f;
    float b = 1.0f;
    float c = a / b;

    double a1 = 1.99999988079071044921875;
    double b1 = 1.0;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

void test_div() {
    // func53();
    // func54();
    // func55();
    // func56();
    // func57();
    // func58();
    // func59();
    // func60();
    // func61();
    // func62();
    // func63();
    // func64();
    // func65();
    // func66();

    case_1();
    //case_2();
    //case_3();
    //case_4();
    //case_5();
    //case_6();
}

void tmp_calc() {
    double a = 1.9272535937499999381117277152952738106250762939453125;
    float b = 1.26374995708465576171875;
    double c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;
}

// Здесь для каждого класса в множестве всех частных
// приводится по одной паре исходных мантисс.
// см. https://drive.google.com/file/d/1pGd8gUZaJXyT7rxJIgkfI-DZdxUyUldN/view?usp=drive_link

// Бесконечная периодическая денормализованная дробь.
void periodic_frac_denorm() {
    float a = 1.0f;
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.0f;
    double b1 = (powl(2, 24) - 1) * powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Бесконечная периодическая нормализованная дробь.
void periodic_frac_norm() {
    float a = 1.688541412353515625f;
    float b = 1.00885009765625f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.688541412353515625;
    double b1 = 1.00885009765625;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Конечная денормализованная дробь (денормализация в смысле промежуточного результата,
// а не формирование subnormal в терминологии IEEE-754). Далее везде подразумевается именно это.
void finit_frac_denorm() {
    float a = 1.3125f;
    float b = 1.75f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.3125;
    double b1 = 1.75;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Конечная нормализованная дробь.
void finit_frac_norm() {
    float a = 1.6875f;
    float b = 1.5f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.6875;
    double b1 = 1.5;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление делимого на себя.
void self_div() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = a;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = (powl(2, 24) - 1) * powl(2, -23);
    double b1 = a1;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Деление делимого на единицу.
void div_over_one() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = 1.0f;
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = (powl(2, 24) - 1) * powl(2, -23);
    double b1 = 1.0;
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Нормализованное частное мантисс.
// Нет ни переполнения ни антипереполнения экспоненты.
void normalized_no_overflow() {
    float a = 1.688541412353515625f * powl(2, 3);
    float b = 1.00885009765625f * powl(2, 106);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.688541412353515625 * powl(2, 3);
    double b1 = 1.00885009765625 * powl(2, 106);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Нормализованное частное мантисс.
// Есть переполнение экспоненты.
void normalized_overflow() {
    float a = 1.688541412353515625f * powl(2, 97);
    float b = 1.00885009765625f * powl(2, -95);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.688541412353515625 * powl(2, 97);
    double b1 = 1.00885009765625 * powl(2, -95);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Нормализованное частное мантисс.
// Есть антипереполнение экспоненты.
void normalized_underflow() {
    float a = 1.688541412353515625f * powl(2, -116);
    float b = 1.00885009765625f * powl(2, 20);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = 1.688541412353515625 * powl(2, -116);
    double b1 = 1.00885009765625 * powl(2, 20);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Денормализованное частное мантисс.
// Нет ни переполнения ни антипереполнения экспоненты.
// Нет ни переполнения ни антипереполнения экспоненты после нормализации
void denormalized_no_overflow_no_overflow() {
    float a = 1.0f * powl(2, 3);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 106);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.0 * powl(2, 3);
    double b1 = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 106);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Денормализованное частное мантисс.
// Нет ни переполнения ни антипереполнения экспоненты.
// Есть антипереполнение экспоненты после нормализации.
void denormalized_no_overflow_underflow() {
    float a = 1.0f * powl(2, -96);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 30);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = 1.0 * powl(2, -96);
    double b1 = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 30);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Денормализованное частное мантисс.
// Есть переполнение экспоненты.
// Нормализация.
// Нет переполнения экспоненты.
void denormalized_overflow_no_overflow() {
    float a = 1.0f * powl(2, 20);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -108);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.0 * powl(2, 20);
    double b1 = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -108);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Денормализованное частное мантисс.
// Есть переполнение экспоненты.
// Нормализация.
// Есть переполнение экспоненты.
void denormalized_overflow_overflow() {
    float a = 1.0f * powl(2, 20);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -109);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << std::endl;

    double a1 = 1.0 * powl(2, 20);
    double b1 = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -109);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;
}

// Денормализованное частное мантисс.
// Есть антипереполнение экспоненты.
// Нормализация.
// Есть антипереполнение экспоненты.
void denormalized_underflow_underflow() {
    float a = 1.0f * powl(2, -115);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 12);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = 1.0 * powl(2, -115);
    double b1 = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 12);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Делимое - денормализованное.
// Делитель - нормализованное.
void denormalized_over_normalized() {
    float a = 1.0f * powl(2, -130);
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = 1.0 * powl(2, -130);
    double b1 = (powl(2, 24) - 1) * powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Делимое - денормализованное.
// Делитель - денормализованное.
void denormalized_over_denormalized() {
}

// Делимое - наименьшая денормализованная мантисса.
// Делитель - наибольшая нормализованная мантисса.
// Результат - наименьшее возможное частное мантисс.
void denormalized_over_normalized_min() {
    float a = powl(2, -23);
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = powl(2, -23);
    double b1 = (powl(2, 24) - 1) * powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Делимое - наибольшая нормализованная мантисса.
// Делитель - наименьшая денормализованная мантисса.
// Результат - наибольшее частное мантисс.
void normalized_over_denormalized_max() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = powl(2, -23);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = (powl(2, 24) - 1) * powl(2, -23);
    double b1 = powl(2, -23);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Делимое - нормализованное.
// Делитель - денормализованное.
void normalized_over_denormalized() {
    float a = 1.0f;
    float b = (powl(2, 13) - 1) * powl(2, -12) * powl(2, -137);
    float c = a / b;

    std::cout << std::fixed << std::setprecision(200) << a << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c) << std::endl;

    std::cout << std::endl;

    double a1 = 1.0;
    double b1 = (powl(2, 13) - 1) * powl(2, -12) * powl(2, -137);
    double c1 = a1 / b1;

    std::cout << std::fixed << std::setprecision(200) << a1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << b1 << std::endl;
    std::cout << std::fixed << std::setprecision(200) << c1 << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(c1) << std::endl;
}

// Пример на потерю точности при операциях над целыми числами,
// преобразованными во float.
void int_float_case() {
    int ia = 1002543844;
    int ib = 325;
    int ic = ia / ib;

    float fa = 1002543844.0f;
    float fb = 325.0f;
    float fc = fa / fb;

    std::cout << std::fixed << std::setprecision(150) << ia << std::endl;
    std::cout << std::fixed << std::setprecision(150) << ib << std::endl;
    std::cout << std::fixed << std::setprecision(150) << ic << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(150) << fa << std::endl;
    std::cout << std::fixed << std::setprecision(150) << fb << std::endl;
    std::cout << std::fixed << std::setprecision(150) << fc << std::endl;

    std::cout << std::endl;
}

void division_research() {
    // Примеры без учета экспонент.
    //periodic_frac_denorm();
    //periodic_frac_norm();
    //finit_frac_denorm();
    //finit_frac_norm();
    //self_div();
    //div_over_one();

    // Примеры с учетом экспонент.
    //normalized_no_overflow();
    //normalized_overflow();
    //normalized_underflow();

    // Денормализованные частные.
    //denormalized_no_overflow_no_overflow();
    //denormalized_no_overflow_underflow();
    //denormalized_overflow_no_overflow();
    //denormalized_overflow_overflow();
    //denormalized_underflow_underflow();

    // Денормализованные аргументы на входе.
    //denormalized_over_normalized();
    //denormalized_over_denormalized();
    //normalized_over_denormalized();

    //denormalized_over_normalized_min();
    normalized_over_denormalized_max();
}

void hex_to_float() {
    uint32_t x = 0x3f9d70a4;
    float f = *((float*)&x);
    std::cout << std::fixed << std::setprecision(200) << f << std::endl;

    float t1 = 1.1327648162841796875f;
    uint32_t t2 = *((uint32_t*)&t1);
    std::cout << std::hex << t2 << std::endl;
}

//
// atof from z88dk. [https://github.com/z88dk/z88dk/blob/c8fbf61401c8783cd234adaf503a50f4e605b5a8/libsrc/math/cimpl/atof.c#L16]
double atof_z88dk(char* s)
{
    double sum,		/* the partial result */
        scale;		/* scale factor for the next digit */
    double ten;
    char* start,	/* copy if input pointer */
        * end,		/* points to end of number */
        c;			/* character from input line */
    int minus,		/* nonzero if number is negative */
        dot,		/* nonzero if *s is decimal point */
        decimal;	/* nonzero if decimal point found */

    ten = 10.;
    if (*s == '-') { minus = 1; ++s; }
    else minus = 0;
    start = s;
    decimal = 0;  /* no decimal point seen yet */
    while ((dot = (*s == '.')) || isdigit(*s)) {
        if (dot) ++decimal;
        ++s;	/* scan to end of string */
    }
    end = s;
    sum = 0.;		/* initialize answer */
    if (decimal) {
        /* handle digits to right of decimal */
        --s;
        while (*s != '.')
            sum = (sum + ((double)(*(s--) - '0'))) / 10.;
    }
    scale = 1.;	/* initialize scale factor */
    while (--s >= start) {
        /* handle remaining digits */
        sum += scale * ((double)(*s - '0'));
        scale *= 10.;
    }
    c = *end++;
    if (tolower(c) == 'e') {	/* interpret exponent */
        int neg;		/* nonzero if exp negative */
        int expon;		/* absolute value of exp */
        int k;			/* mask */

        neg = expon = 0;
        if (*end == '-') {
            /* negative exponent */
            neg = 1;
            ++end;
        }
        while (1) {	/* read an integer */
            if ((c = *end++) >= '0') {
                if (c <= '9') {
                    expon = expon * 10 + c - '0';
                    continue;
                }
            }
            break;
        }
        if (expon > 38) {
#if 0
            puts("overflow");
#endif
            expon = 0;
        }
        k = 32;	/* set one bit in mask */
        scale = 1.;
        while (k) {
            scale *= scale;
            if (k & expon) scale *= ten;
            k >>= 1;
        }
        if (neg) sum /= scale;
        else    sum *= scale;
    }
    if (minus) sum = -sum;
    return sum;
}

//
// atof из SDCC [https://sdcc.sourceforge.net/].
float atof_sdcc(const char* s)
{
    float value, fraction;
    signed char iexp;
    bool sign;

    //Skip leading blanks
    while (isspace(*s)) s++;

    //Get the sign
    if (*s == '-')
    {
        sign = 1;
        s++;
    }
    else
    {
        sign = 0;
        if (*s == '+') s++;
    }

    //Get the integer part
    for (value = 0.0; isdigit(*s); s++)
    {
        value = 10.0 * value + (*s - '0');
    }

    //Get the fraction
    if (*s == '.')
    {
        s++;
        for (fraction = 0.1; isdigit(*s); s++)
        {
            value += (*s - '0') * fraction;
            fraction *= 0.1;
        }
    }

    //Finally, the exponent (not very efficient, but enough for now*/
    if (toupper(*s) == 'E')
    {
        s++;
        iexp = (signed char)atoi(s);
        {
            while (iexp != 0)
            {
                if (iexp < 0)
                {
                    value *= 0.1;
                    iexp++;
                }
                else
                {
                    value *= 10.0;
                    iexp--;
                }
            }
        }
    }

    if (sign) value *= -1.0;
    return (value);
}

//
// atof из K&R.
double atof_kr(char s[]) {
    double val, power;
    int i = 0, sign;

    sign = (s[0] == '-') ? -1 : 1;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    return sign * val / power;
}

//
// atof from K&R.
// Теперь float вместо double.
float atof_kr_float(char s[]) {
    float val, power;
    int i = 0, sign;

    sign = (s[0] == '-') ? -1 : 1;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    return sign * val / power;
}

void atof_test() {
    char numString[] = "3.14159";

    std::cout << "desktop (native): \n";
    std::cout << "string: " << numString << '\n';
    double res0 = atof(numString);
    std::cout << "number: " << std::fixed << std::setprecision(150) << res0 << "\n";
    print_double_as_hex(&res0);
    std::cout << '\n';

    std::cout << "z88dk: \n";
    std::cout << "string: " << numString << '\n';
    double res1 = atof_z88dk(numString);
    std::cout << "number: " << std::fixed << std::setprecision(150) << res1 << "\n";
    print_double_as_hex(&res1);
    std::cout << '\n';

    std::cout << "sdcc: \n";
    std::cout << "string: " << numString << '\n';
    float res2 = atof_sdcc(numString);
    std::cout << "number: " << std::fixed << std::setprecision(150) << res2 << "\n";
    print_float_as_hex(&res2);
    std::cout << '\n';

    std::cout << "atof_kr: \n";
    //char num[] = "1.99999988079071044921875";
    std::cout << "string: " << numString << '\n';
    double res3 = atof_kr(numString);
    std::cout << "number: " << std::fixed << std::setprecision(150) << res3 << "\n";
    print_double_as_hex(&res3);
    std::cout << '\n';

    std::cout << "atof_kr_float: \n";
    //char num[] = "1.99999988079071044921875";
    std::cout << "string: " << numString << '\n';
    float res4 = atof_kr_float(numString);
    std::cout << "number: " << std::fixed << std::setprecision(150) << res4 << "\n";
    print_float_as_hex(&res4);
    std::cout << '\n';
}

//
// Реализация ftoa из z88dk [https://z88dk.org/site/].
// Оригинальная версия с double.
void ftoa_double(double x, int f, char* str) {
    double scale;           /* scale factor */
    int i,                  /* copy of f, and # digits before decimal point */
        d;                  /* a digit */

    if (x < 0.0) {
        *str++ = '-';
        x = -x;
    }
    i = f;
    scale = 2.0;
    while (i--)
        scale *= 10.0;
    x += 1.0 / scale;
    /* count places before decimal & scale the number */
    i = 0;
    scale = 1.0;
    while (x >= scale) {
        scale *= 10.0;
        i++;
    }
    if (i == 0)
        *str++ = '0';

    while (i--) {
        /* output digits before decimal */
        x = fabs(x);
        scale = floor(0.5 + scale * 0.1);
        d = x / scale;
        *str++ = d + '0';
        x = x - ((double)d * scale);
    }
    if (f <= 0) {
        *str = 0;
        return;
    }
    *str++ = '.';
    while (f--) {
        /* output digits after decimal */
        x = fabs(x);
        x *= 10.0;
        d = x;
        *str++ = d + '0';
        x -= (double)d;
    }
    *str = 0;
}

//
// Реализация ftoa из z88dk [https://z88dk.org/site/].
// Версия с float.
void ftoa_float(float x, int f, char* str) {
    float scale;            /* scale factor */
    int i,                  /* copy of f, and # digits before decimal point */
        d;                  /* a digit */

    if (x < 0.0f) {
        *str++ = '-';
        x = -x;
    }
    i = f;
    scale = 2.0f;
    while (i--)
        scale *= 10.0f;
    x += 1.0f / scale;
    /* count places before decimal & scale the number */
    i = 0;
    scale = 1.0f;
    while (x >= scale) {
        scale *= 10.0f;
        i++;
    }
    if (i == 0)
        *str++ = '0';

    while (i--) {
        /* output digits before decimal */
        x = fabs(x);
        scale = floor(0.5f + scale * 0.1f);
        d = x / scale;
        *str++ = d + '0';
        x = x - ((float)d * scale);
    }
    if (f <= 0) {
        *str = 0;
        return;
    }
    *str++ = '.';
    while (f--) {
        /* output digits after decimal */
        x = fabs(x);
        x *= 10.0f;
        d = x;
        *str++ = d + '0';
        x -= (float)d;
    }
    *str = 0;
}

//
// Реализация ftoa из z88dk [https://z88dk.org/site/].
// Версия с float и нашими модификациями: "лишний" код, устранение переполнения для граничных случаев.
void ftoa_float_mod(float num, int digitCount, char* str) {
    float scale;            // scale factor
    int i;                  // copy of digitCount, and # digits before decimal point
    int digit;              // a digit

    if (num < 0.0f) {
        *str++ = '-';
        num = -num;
    }
    i = 1;
    scale = 1.0f;
    float numDiv10 = num * 0.1f; // Чтобы избежать переполнения.
    while (numDiv10 >= scale) {
        scale *= 10.0f;
        i++;
    }

    while (i--) {
        digit = num / scale;
        *str++ = digit + '0';
        num = num - ((float)digit * scale);
        scale = scale * 0.1f;
    }
    if (digitCount <= 0) {
        *str = 0;
        return;
    }
    *str++ = '.';
    while (digitCount--) {
        num *= 10.0f;
        digit = num;
        *str++ = digit + '0';
        num -= (float)digit;
    }
    *str = 0;
}

void ftoa_double_test() {
    std::cout << "ftoa_double: 2^-126.\n";
    double minNormal = powf(2, -126);
    std::cout << std::fixed << std::setprecision(150) << minNormal << '\n';

    char minNormalString[255];
    ftoa_double(minNormal, 200, minNormalString);
    std::cout << minNormalString << '\n';

    std::cout << '\n';

    std::cout << "ftoa_double: (2^24 - 1) * 2^-23 * 2^127.\n";
    double maxNormal = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    std::cout << std::fixed << std::setprecision(150) << maxNormal << '\n';

    char maxNormalString[255];
    ftoa_double(maxNormal, 200, maxNormalString);
    std::cout << maxNormalString << '\n';
}

void ftoa_float_edge_cases_test() {
    std::cout << "ftoa_float: 2^-126.\n";
    float minNormal = powf(2, -126);
    std::cout << std::fixed << std::setprecision(150) << minNormal << '\n';

    char minNormalString[255];
    ftoa_float(minNormal, 200, minNormalString);
    std::cout << minNormalString << '\n';

    std::cout << '\n';

    std::cout << "ftoa_float: (2^24 - 1) * 2^-23 * 2^127.\n";
    float maxNormal = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    std::cout << std::fixed << std::setprecision(150) << maxNormal << '\n';

    char maxNormalString[255];
    ftoa_float(maxNormal, 200, maxNormalString);
    std::cout << maxNormalString << '\n';

    std::cout << '\n';

    // Минимальный порядок, при котором ломается и даёт ноль. Мантисса при этом максимальная.
    std::cout << "ftoa_float: (2^24 - 1) * 2^-23 * 2^126.\n";
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 126);
    std::cout << std::fixed << std::setprecision(100) << a << '\n';

    char aString[1024];
    ftoa_float(a, 200, aString);
    std::cout << aString << '\n';

    std::cout << '\n';

    // Оставляем тот же порядок, но берем минимальную мантиссу.
    std::cout << "ftoa_float: 1.0f * 2^126.\n";
    float b = 1.0f * powf(2, 126);
    std::cout << std::fixed << std::setprecision(100) << b << '\n';

    char bString[1024];
    ftoa_float(b, 200, bString);
    std::cout << bString << '\n';

    std::cout << '\n';

    // Берем максимальный порядок, но оставляем минимальную мантиссу.
    std::cout << "ftoa_float: 1.0f * 2^127.\n";
    float c = 1.0f * powf(2, 127);
    std::cout << std::fixed << std::setprecision(100) << c << '\n';

    char cString[1024];
    ftoa_float(c, 200, cString);
    std::cout << cString << '\n';
}

void ftoa_float_simple_test() {
    std::cout << "ftoa_float_simple_test\n";
    //float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, -100);
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    //float a = 723.05f;
    std::cout << std::fixed << std::setprecision(150) << a << '\n';

    char aString[255];
    ftoa_float(a, 10, aString);
    std::cout << aString << '\n';

    std::cout << '\n';
}

//
// К вопросу о том, почему после конвертации не все десятичные разряды оказываются истинными.
void incorrect_deciaml() {
    float a = 0.01251220703125f; // Точно представимо в одинарном float.
    print_float_as_hex(&a);
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    // Здесь мы сразу масштабируем всё число целиком.
    // Истинное десятичное представление a=0.01251220703125 после масштабирования должно быть равно 1251220.703125.
    // Но из-за округления в процессе умножения на степень десяти исходное десятичное представление исходной
    // двоичной дроби искажается и к 9 знаку мы уже теряем истинные десятичные разряды.
    float b = a * powf(10, 8);
    std::cout << std::fixed << std::setprecision(100) << b << "\n\n";

    std::cout << "\n";

    // А здесь мы последовательно умножаем на 10 и каждый раз отнимаем целую часть.
    //0.1251220703125;
    a *= 10.0f; a -= 0.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //1.251220703125;
    a *= 10.0f; a -= 1.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //2.51220703125;
    a *= 10.0f; a -= 2.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //5.1220703125;
    a *= 10.0f; a -= 5.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //1.220703125;
    a *= 10.0f; a -= 1.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //2.20703125;
    a *= 10.0f; a -= 2.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //2.0703125;
    a *= 10.0f; a -= 2.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //0.703125;
    a *= 10.0f; a -= 0.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //7.03125;
    a *= 10.0f; a -= 7.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //0.3125;
    a *= 10.0f; a -= 0.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //3.125;
    a *= 10.0f; a -= 3.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //1.25;
    a *= 10.0f; a -= 1.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //2.5;
    a *= 10.0f; a -= 2.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    //5;
    a *= 10.0f; a -= 5.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n\n";

    std::cout << "\n";

    // А здесь мы отнимаем те же разряды, но без попутного масштабирования.
    // Результат оказывается лучше, чем в первом случае, когда мы сразу масштабируем число целиком, но хуже, чем в предыдущем случае.
    a = 0.01251220703125f;
    a -= 0.01f;
    a -= 0.002f;
    a -= 0.0005f;
    a -= 0.00001f;
    a -= 0.000002f;
    a -= 0.0000002f;
    print_float_as_hex(&a);
    std::cout << std::fixed << std::setprecision(100) << a * powf(10, 8) << '\n';
}

void atof_mod_debugging() {
    //float a = 0.01251220703125f;
    float a = 3.141590118408203125f;
    char aString[255];
    char aString2[255];
    ftoa_float(a, 1, aString);
    ftoa_float_mod(a, 1, aString2);
    std::cout << aString << '\n';
    std::cout << aString2 << '\n';

    std::cout << '\n';

    std::cout << "ftoa_float: 2^-126.\n";
    float minNormal = powf(2, -126);
    std::cout << std::fixed << std::setprecision(100) << minNormal << "\n\n";

    char minNormalString[255];
    char minNormalString2[255];
    ftoa_float(minNormal, 200, minNormalString);
    ftoa_float_mod(minNormal, 200, minNormalString2);
    std::cout << minNormalString << '\n';
    std::cout << minNormalString2 << '\n';

    std::cout << '\n';

    std::cout << "ftoa_float: (2^24 - 1) * 2^-23 * 2^127.\n";
    float maxNormal = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    std::cout << std::fixed << std::setprecision(100) << maxNormal << "\n\n";

    char maxNormalString[255];
    char maxNormalString2[255];
    ftoa_float(maxNormal, 200, maxNormalString);
    ftoa_float_mod(maxNormal, 200, maxNormalString2);
    std::cout << maxNormalString << '\n';
    std::cout << maxNormalString2 << '\n';

    std::cout << '\n';

    std::cout << "ftoa_float: (2^24 - 1) * 2^-23 * 2^96.\n";
    float avgValue = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 125);
    std::cout << std::fixed << std::setprecision(100) << avgValue << "\n\n";

    char avgValueString[255];
    char avgValueString2[255];
    ftoa_float(-avgValue, 200, avgValueString);
    ftoa_float_mod(-avgValue, 200, avgValueString2);
    std::cout << avgValueString << '\n';
    std::cout << avgValueString2 << '\n';

    std::cout << '\n';

    // < 1.
    std::cout << "xxxx\n";
    float t = 0.00234723393805325031280517578125f;
    std::cout << std::fixed << std::setprecision(100) << t << "\n\n";

    char tString[255];
    char tString2[255];
    ftoa_float(t, 200, tString);
    ftoa_float_mod(t, 10, tString2);
    std::cout << tString << '\n';
    std::cout << tString2 << '\n';
}

void temp_test() {
    //float a = -123.45600128173828125f; // Точно представимо в одинарном float.
    //float a = 0.5f; // Точно представимо в одинарном float.
    //float a = 6546.67578125f; // Точно представимо в одинарном float.
    //float a = 0.08089999854564666748046875f; // Точно представимо в одинарном float.
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127); // Точно представимо в одинарном float.
    std::cout << std::fixed << std::setprecision(20) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 20, str);
    std::cout << str << '\n';
}

//
// Демонстрация изменения направления округления переменной типа float
// когда промежуточные вычисления происходят в double.
void double_float() {
    float val_float = (powf(2, 24) - 1) * powf(2, -23); // Базовое значение. Все единицы в мантиссе.
    float delta1_float = powf(2, -25) + powf(2, -26);
    float delta2_float = powf(2, -26);

    double delta1_double = powl(2, -25) + powl(2, -26);
    double delta2_double = powl(2, -26);

    float r1 = (val_float + delta1_double) + delta2_double; // Вычисления в double, округление только при конвертации в float. Округление в большую, повышение порядка.
    std::cout << std::fixed << std::setprecision(100) << r1 << "\n";
    print_float_as_hex(&r1);

    std::cout << '\n';

    float r2 = (val_float + delta1_float) + delta2_float; // Вычисления в float, округление при сложении, округление в меньшую сторону, результат - исходное значение.
    std::cout << std::fixed << std::setprecision(100) << r2 << "\n";
    print_float_as_hex(&r2);
}

int main() {
    // test_add();
    // test_mul();
    // test_mul2();
    // test_mul3();
    //test_div();
    //int_float_case();

    //tmp_calc();

    //division_research();

    //hex_to_float();

    //atof_test();

    //ftoa_double_test();
    //std::cout << '\n';
    //ftoa_float_edge_cases_test();

    //ftoa_float_simple_test();

    //incorrect_deciaml();

    //atof_mod_debugging();

    //temp_test();

    //special_values();
    double_float();

    return 0;
}
