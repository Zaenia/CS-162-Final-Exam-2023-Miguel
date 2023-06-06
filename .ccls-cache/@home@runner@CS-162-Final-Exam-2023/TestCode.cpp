#include "TestCode.h"
#include "invalid_move_ex.h"
#include "Checkers.h"


void TestCode::runSelectedTest()
{
    int test = 0;
    std::cin >> test;
    switch (test)
    {
    case 1: TestCode::testRedCheckersAutoGrade(false); break;
    case 2: TestCode::testBlackCheckersAutoGrade(false); break;
    case 3: TestCode::testRedCheckersAutoGrade(true); break;
    case 4: TestCode::testBlackCheckersAutoGrade(true); break;
    case 5: TestCode::testRedCrownAutoGrade(); break;
    case 6: TestCode::testBlackCrownAutoGrade(); break;
    case 7: TestCode::testRedDoubleJumpAutoGrade(false); break;
    case 8: TestCode::testRedDoubleJumpAutoGrade(true); break;
    case 9: TestCode::testBlackDoubleJumpAutoGrade(false); break;
    case 10: TestCode::testBlackDoubleJumpAutoGrade(true); break;
    case 11: TestCode::testRedMultipleJumpAutoGrade(); break;
    case 12: TestCode::testBlackMultipleJumpAutoGrade(); break;
    case 13: TestCode::testInsertionOperatorOverload(); break;
    case 14: TestCode::testExtractionOperatorOverload(); break;
    case 15: TestCode::testExceptionsAutoGrade(); break;
    }
}

// Deletes the default RedCheckers and BlackCheckers that are instantianted in the class header files so they do not interfere with testing
void TestCode::deleteDefaultPieces()
{
    Checkers::r.clear();
    Checkers::b.clear();

    for (int i = 0; i < 8; i++) //rank
    {
        for (int j = 0; j < 8; j++) //file
        {
            Checkers::checkersBoard[i][j].setOccupant(nullptr);
        }
    }
}

// Prints all Square values of checkerBoard for input/output testing purposes
void TestCode::printSquareValues()
{
    std::cout << "--------" << std::endl;
    for (int i = 7; i >= 0; i--) // ranks
    {
        for (int j = 0; j < 8; j++) // files
        {
            if (Checkers::checkersBoard[i][j].isOccupied())
                std::cout << Checkers::checkersBoard[i][j].getOccupant()->getSymbol();
            else
                 std::cout << " ";

        }
        std::cout << std::endl;
    }
    std::cout << "--------" << std::endl;
}



// Instantiantes RedCheckers in Square d4 and attempts to move them to every other Square to test isMoveLegal() functionality.  Includes testing jumping with obstacles
void TestCode::testRedCheckers(bool crowned)
{
    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    std::cout << "Testing moving RedChecker to all locations with no obstacles  (should see upward diagonal moves from d4 only)" << std::endl;
    RedChecker r1 = RedChecker('d', 4);
    if (crowned)
        r1.crown();
    TestCode::moveToAllSquaresOutsideIn(&r1);
    Checkers::printBoard();

    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    std::cout << "Testing moving RedChecker to all locations surrounded by obstancles  (should see upward diagonal jumps from d4)" << std::endl;
    BlackChecker b1('c', 3);
    BlackChecker b2('c', 4);
    BlackChecker b3('c', 5);
    BlackChecker b4('e', 3);
    BlackChecker b5('e', 4);
    BlackChecker b6('e', 5);
    BlackChecker b7('d', 3);
    BlackChecker b8('d', 5);
    TestCode::moveToAllSquaresInsideOut(&r1);
    Checkers::printBoard();
}

void TestCode::testRedCheckersAutoGrade(bool crowned)
{
    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    RedChecker r1 = RedChecker('d', 4);
    if (crowned)
        r1.crown();
    TestCode::moveToAllSquaresOutsideIn(&r1);
    TestCode::printSquareValues();

    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    BlackChecker b1('c', 3);
    BlackChecker b2('c', 4);
    BlackChecker b3('c', 5);
    BlackChecker b4('e', 3);
    BlackChecker b5('e', 4);
    BlackChecker b6('e', 5);
    BlackChecker b7('d', 3);
    BlackChecker b8('d', 5);
    TestCode::moveToAllSquaresInsideOut(&r1);
    TestCode::printSquareValues();
}

// Instantiantes BlackCheckers in Square d4 and attempts to move them to every other Square to test isMoveLegal() functionality.  Includes testing jumping with obstacles
void TestCode::testBlackCheckers(bool crowned)
{
    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    std::cout << "Testing moving BlackChecker to all locations with no obstacles  (should see downward diagonal moves from d4 only)" << std::endl;
    BlackChecker b1 = BlackChecker('d', 4);
    if (crowned)
        b1.crown();
    TestCode::moveToAllSquaresOutsideIn(&b1);
    Checkers::printBoard();

    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    std::cout << "Testing moving BlackChecker to all locations surrounded by obstancles  (should see downward diagonal jumps from d4 )" << std::endl;
    RedChecker r1('c', 3);
    RedChecker r2('c', 4);
    RedChecker r3('c', 5);
    RedChecker r4('e', 3);
    RedChecker r5('e', 4);
    RedChecker r6('e', 5);
    RedChecker r7('d', 3);
    RedChecker r8('d', 5);
    TestCode::moveToAllSquaresInsideOut(&b1);
    Checkers::printBoard();
}

void TestCode::testBlackCheckersAutoGrade(bool crowned)
{
    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    BlackChecker b1 = BlackChecker('d', 4);
    if (crowned)
        b1.crown();
    TestCode::moveToAllSquaresOutsideIn(&b1);
    TestCode::printSquareValues();

    Checkers::createBoard();
    TestCode::deleteDefaultPieces();
    RedChecker r1('c', 3);
    RedChecker r2('c', 4);
    RedChecker r3('c', 5);
    RedChecker r4('e', 3);
    RedChecker r5('e', 4);
    RedChecker r6('e', 5);
    RedChecker r7('d', 3);
    RedChecker r8('d', 5);
    TestCode::moveToAllSquaresInsideOut(&b1);
    TestCode::printSquareValues();
}

// Tests crowning functionality of red checkers
void TestCode::testRedCrown()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    // Test RedChecker Crowning
    std::cout << "Testing crowning red checker.  Should see checker appear in a7, move to c8 and become crowned, and move backward to c7 successfully" << std::endl;
    RedChecker r1 = RedChecker('a', 7);
    Checkers::printBoard();
    r1.move('b', 8);
    Checkers::printBoard();
    r1.move('c', 7);
    Checkers::printBoard();
}

void TestCode::testRedCrownAutoGrade()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    // Test RedChecker Crowning
    RedChecker r1 = RedChecker('a', 7);
    r1.move('b', 8);
    r1.move('c', 7);
    TestCode::printSquareValues();
}

// Tests crowning functionality of black checkers
void TestCode::testBlackCrown()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    // Test BlackChecker Crowning
    std::cout << "Testing crowning black checker.  Should see checker appear in a2, move to b1 and become crowned, and move backward to c2 successfully" << std::endl;
    BlackChecker b1 = BlackChecker('a', 2);
    Checkers::printBoard();
    b1.move('b', 1);
    Checkers::printBoard();
    b1.move('c', 2);
    Checkers::printBoard();
}

void TestCode::testBlackCrownAutoGrade()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    // Test BlackChecker Crowning
    BlackChecker b1 = BlackChecker('a', 2);
    b1.move('b', 1);
    b1.move('c', 2);
    TestCode::printSquareValues();
}

// Tests the ability of a crowned or uncrowned red checker to double jump (two jumps in one move)
void TestCode::testRedDoubleJump(bool crowned)
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    if (!crowned)
    {
        std::cout << "Testing red checker double jump. Should see red checker starting at c3 capture the black ckeckers at d4 and d6 and end up at c7" << std::endl;
        RedChecker r1('c', 3);
        BlackChecker b1('d', 4);
        BlackChecker b2('d', 6);
        Checkers::printBoard();
        Checkers::makeMove(false, "c3e5c7");
        Checkers::printBoard();
    }
    else
    {
        std::cout << "Testing crowned red checker double jump. Should see red checker starting at c7 capture the black ckeckers at d4 and d6 and end up at c3" << std::endl;
        RedChecker r1 = RedChecker('c', 7);
        r1.crown();
        BlackChecker b1('d', 4);
        BlackChecker b2('d', 6);
        Checkers::printBoard();
        Checkers::makeMove(false, "c7e5c3");
        Checkers::printBoard();
    }
}

void TestCode::testRedDoubleJumpAutoGrade(bool crowned)
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    if (!crowned)
    {
        RedChecker r1 ('c', 3);
        BlackChecker b1('d', 4);
        BlackChecker b2('d', 6);
        Checkers::makeMove(false, "c3e5c7");
        TestCode::printSquareValues();
    }
    else
    {
        RedChecker r1 = RedChecker('c', 7);
        r1.crown();
        BlackChecker b1('d', 4);
        BlackChecker b2('d', 6);
        Checkers::makeMove(false, "c7e5c3");
        TestCode::printSquareValues();
    }
}

// Tests the ability of a crowned or uncrowned black checker to double jump (two jumps in one move)
void TestCode::testBlackDoubleJump(bool crowned)
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    if (!crowned)
    {
        std::cout << "Testing black checker double jump. Should see black checker starting at c7 capture the red ckeckers at d4 and d6 and end up at c3" << std::endl;
        BlackChecker b1('c', 7);
        RedChecker r1('d', 4);
        RedChecker r2('d', 6);
        Checkers::printBoard();
        Checkers::makeMove(true, "c7e5c3");
        Checkers::printBoard();
    }
    else
    {
        std::cout << "Testing crowned black checker double jump. Should see black checker starting at c3 capture the red ckeckers at d4 and d6 and end up at c7" << std::endl;
        BlackChecker b1 = BlackChecker('c', 3);
        b1.crown();
        RedChecker r1('d', 4);
        RedChecker r2('d', 6);
        Checkers::printBoard();
        Checkers::makeMove(true, "c3e5c7");
        Checkers::printBoard();
    }
}

void TestCode::testBlackDoubleJumpAutoGrade(bool crowned)
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    if (!crowned)
    {
        BlackChecker b1('c', 7);
        RedChecker r1('d', 4);
        RedChecker r2('d', 6);
        Checkers::makeMove(true, "c7e5c3");
        TestCode::printSquareValues();
    }
    else
    {
        BlackChecker b1 = BlackChecker('c', 3);
        b1.crown();
        RedChecker r1('d', 4);
        RedChecker r2('d', 6);
        Checkers::makeMove(true, "c3e5c7");
        TestCode::printSquareValues();
    }
}

// Tests the ability of a crowned red checker to jump 4 black checkers (forwards and backwards jumps)
void TestCode::testRedMultipleJump()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    std::cout << "Testing crowned red checker multiple jump. Should see crowned red checker starting at e3 capture the 4 black ckeckers and end up at e3" << std::endl;
    RedChecker r1 = RedChecker('e', 3);
    r1.crown();
    BlackChecker b1('d', 4);
    BlackChecker b2('d', 6);
    BlackChecker b3('f', 4);
    BlackChecker b4('f', 6);
    Checkers::printBoard();
    Checkers::makeMove(false, "e3c5e7g5e3");
    Checkers::printBoard();
}

void TestCode::testRedMultipleJumpAutoGrade()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    RedChecker r1 = RedChecker('e', 3);
    r1.crown();
    BlackChecker b1('d', 4);
    BlackChecker b2('d', 6);
    BlackChecker b3('f', 4);
    BlackChecker b4('f', 6);
    Checkers::makeMove(false, "e3c5e7g5e3");
    TestCode::printSquareValues();
}

// Tests the ability of a crowned black checker to jump 4 red checkers (forwards and backwards jumps)
void TestCode::testBlackMultipleJump()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    std::cout << "Testing crowned bla checker multiple jump. Should see crowned black checker starting at e3 capture the 4 red ckeckers and end up at e3" << std::endl;
    BlackChecker b1 = BlackChecker('e', 3);
    b1.crown();
    RedChecker r1('d', 4);
    RedChecker r2('d', 6);
    RedChecker r3('f', 4);
    RedChecker r4('f', 6);
    Checkers::printBoard();
    Checkers::makeMove(true, "e3c5e7g5e3");
    Checkers::printBoard();
}

void TestCode::testBlackMultipleJumpAutoGrade()
{
    // Create an empty checkers board
    Checkers::createBoard();
    deleteDefaultPieces();

    BlackChecker b1 = BlackChecker('e', 3);
    b1.crown();
    RedChecker r1('d', 4);
    RedChecker r2('d', 6);
    RedChecker r3('f', 4);
    RedChecker r4('f', 6);
    Checkers::makeMove(true, "e3c5e7g5e3");
    TestCode::printSquareValues();
}

// Tests overload of insertion operator by comparing the output of TestCode::printSquareValues() to the output of similar code that has been modified to use the insertion operator with std::cout
void TestCode::testInsertionOperatorOverload()
{
    Checkers::createBoard();
    TestCode::printSquareValues();
    std::cout << "Testing Insertion Operator overload. Should see the board print as above." << std::endl;

    std::cout << "--------" << std::endl;
    for (int i = 7; i >= 0; i--) // ranks
    {
        for (int j = 0; j < 8; j++) // files
        {
            if (Checkers::checkersBoard[i][j].isOccupied())
                std::cout << Checkers::checkersBoard[i][j];
            else
                std::cout << " ";

        }
        std::cout << std::endl;
    }
    std::cout << "--------" << std::endl;
}

// Tests the overloading of the extraction operator by using it to move a black checker from b6 to c5
void TestCode::testExtractionOperatorOverload()
{
    Checkers::createBoard();
    
    TestCode::printSquareValues();
    std::cout << "Testing Extraction Operator overload. Should b6 move to c5." << std::endl;
    Checkers::checkersBoard[6 - 1]['b' - 'a'] >> Checkers::checkersBoard[5 - 1]['c' - 'a'];
    TestCode::printSquareValues();
}

// Tests the implementation exception handling by running code that should throw exceptions in 6 different scenarios  
void TestCode::testExceptionsAutoGrade()
{
    try
    {
        std::cout << "Trying move with odd number of characters: ";
        Checkers::createBoard();
        Checkers::getMove(true); // enter value b6c5e
        std::cout << "Failed" << std::endl;
    }
    catch (invalid_move_ex)
    {
        std::cout << "Pass" << std::endl;
    }
    try
    {
        std::cout << "Trying out of bounds move: ";
        Checkers::createBoard();
        Checkers::getMove(true); // enter value b6j5
        std::cout << "Failed" << std::endl;
    }
    catch (invalid_move_ex)
    {
        std::cout << "Pass" << std::endl;
    }

    try
    {
        std::cout << "Attempt to move red during blacks' turn: ";
        Checkers::createBoard();
        Checkers::makeMove(true, Checkers::getMove(true)); // enter value a3b4
        std::cout << "Failed" << std::endl;
    }
    catch (invalid_move_ex)
    {
        std::cout << "Pass" << std::endl;
    }

    try
    {
        std::cout << "Attempt to move black during red's turn: ";
        Checkers::createBoard();
        Checkers::makeMove(false, Checkers::getMove(false)); // enter value b6c5
        std::cout << "Failed" << std::endl;
    }
    catch (invalid_move_ex)
    {
        std::cout << "Pass" << std::endl;
    }

    try
    {
        std::cout << "Attempt to move black from unoccupied square: ";
        Checkers::createBoard();
        Checkers::makeMove(true, Checkers::getMove(true)); // enter value c5d4
        std::cout << "Failed" << std::endl;
    }
    catch (invalid_move_ex)
    {
        std::cout << "Pass" << std::endl;
    }

    try
    {
        std::cout << "Attempt to move to occupied square: ";
        Checkers::createBoard();
        Checkers::makeMove(true, Checkers::getMove(true)); // enter value a7b6
        std::cout << "Failed" << std::endl;
    }
    catch (invalid_move_ex)
    {
        std::cout << "Pass" << std::endl;
    }
}