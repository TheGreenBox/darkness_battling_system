#include "board.h"

#include <iostream>

void Test1() {
    std::cout << "TEST 1\n";
    TBoard board(3, 3);

                          board.LockCell(0, 1);
                          board.LockCell(1, 1);
    board.LockCell(2, 0); board.LockCell(2, 1); board.LockCell(2, 2);

    std::cout << board.ToString() << std::endl;

    size_t collapsed = board.CollapseRows();
    std::cout << "Collapsed " << collapsed << " rows\n";

    std::cout << board.ToString() << std::endl;
}

void Test2() {
    std::cout << "TEST 2\n";
    TBoard board(3, 3);

    board.LockCell(0, 0); board.LockCell(0, 1); board.LockCell(0, 2);
    board.LockCell(1, 0);
                          board.LockCell(2, 1);

    std::cout << board.ToString() << std::endl;

    size_t collapsed = board.CollapseRows();
    std::cout << "Collapsed " << collapsed << " rows\n";

    std::cout << board.ToString() << std::endl;
}

void Test3() {
    std::cout << "TEST 3\n";
    TBoard board(3, 3);

    board.LockCell(0, 0); board.LockCell(0, 1); board.LockCell(0, 2);
                          board.LockCell(1, 0);
    board.LockCell(2, 0); board.LockCell(2, 1); board.LockCell(2, 2);

    std::cout << board.ToString() << std::endl;

    size_t collapsed = board.CollapseRows();
    std::cout << "Collapsed " << collapsed << " rows\n";

    std::cout << board.ToString() << std::endl;
}

void EmptyTest() {
    std::cout << "TEST EMPTY\n";
    TBoard board(0, 0);

    std::cout << board.ToString();

    size_t collapsed = board.CollapseRows();
    std::cout << "Collapsed " << collapsed << " rows\n";

    std::cout << board.ToString();
}

int main() {
    Test1();
    Test2();
    Test3();
    EmptyTest();
    return 0;
}
