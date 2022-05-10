#include "Matrix.hpp"

int main() {
    zich::Matrix m1({0}, 1, 1);
    zich::Matrix m2({0}, 1, 1);

    try {
        std::cout << "Enter the first matrix: ";
        std::cin >> m1;
        std::cout << "Enter the second matrix: ";
        std::cin >> m2;
        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "The first matrix is: " << std::endl;
    std::cout << m1 << std::endl;
    std::cout << "The second matrix is: " << std::endl;
    std::cout << m2 << std::endl;

    try {
        m1 += m2;
        std::cout << "m1 += m2 is: " << std::endl
                  << m1 << std::endl;
        m1 -= m2;
        std::cout << "m1 -= m2 is: " << std::endl
                  << m1 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Size mismatch can't perform addition and or subtraction" << std::endl;
    }

    zich::Matrix m4 = +m1;
    std::cout << "+m1 is: " << std::endl
              << m4 << std::endl;
    m4 = -m2;
    std::cout << "-m2 is: " << std::endl
              << m4 << std::endl;

    std::cout << "m1++ is: " << std::endl
              << (m1++) << std::endl;
    std::cout << "m1-- is: " << std::endl
              << (m1--) << std::endl;
    std::cout << "++m2 is: " << std::endl
              << (++m2) << std::endl;
    std::cout << "--m2 is: " << std::endl
              << (--m2) << std::endl;

    try {
        m1 *= m2;
        std::cout << "m1 *= m2 is: " << std::endl
                  << m1 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Size mismatch can't perform multiplication" << std::endl;
    }

    m2 *= 3.14;
    std::cout << "m2 *= 3.14 is: " << std::endl
              << m2 << std::endl;

    try {
        bool res = m1 == m2;
        std::cout << "m1 == m2 is: " << res << std::endl;
        res = m1 != m2;
        std::cout << "m1 != m2 is: " << res << std::endl;
        res = m1 < m2;
        std::cout << "m1 < m2 is: " << res << std::endl;
        res = m1 > m2;
        std::cout << "m1 > m2 is: " << res << std::endl;
        res = m1 <= m2;
        std::cout << "m1 <= m2 is: " << res << std::endl;
        res = m1 >= m2;
        std::cout << "m1 >= m2 is: " << res << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Size mismatch can't perform comparison" << std::endl;
    }

    return 0;
}