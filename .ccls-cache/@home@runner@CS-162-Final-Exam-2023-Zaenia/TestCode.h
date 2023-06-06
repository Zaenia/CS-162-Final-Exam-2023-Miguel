#pragma once

#include "BlackChecker.h"
#include "CheckersPiece.h"
#include "invalid_move_ex.h"
#include "RedChecker.h"
#include <iostream>

class TestCode
{
public:

    static void runSelectedTest();
    static void deleteDefaultPieces();
    static void printSquareValues();
    static void testRedCrown();
    static void testRedCrownAutoGrade();
    static void testBlackCrown();
    static void testBlackCrownAutoGrade();
    static void testRedCheckers(bool crowned = false);
    static void testRedCheckersAutoGrade(bool crowned = false);
    static void testBlackCheckers(bool crowned = false);
    static void testBlackCheckersAutoGrade(bool crowned = false);
    static void testRedDoubleJump(bool crowned = false);
    static void testRedDoubleJumpAutoGrade(bool crowned = false);
    static void testBlackDoubleJump(bool crowned = false);
    static void testBlackDoubleJumpAutoGrade(bool crowned = false);
    static void testRedMultipleJump();
    static void testRedMultipleJumpAutoGrade();
    static void testBlackMultipleJump();
    static void testBlackMultipleJumpAutoGrade();
    static void testInsertionOperatorOverload();
    static void testExtractionOperatorOverload();
    static void testExceptionsAutoGrade();

    // This template is intended to be used to automatically create 63 checkers pieces of type T at Square d4 and attempt to move each piece to a different Square on the checker board (except square d4) starting with outside squares and moving inward (for testing non-jumping moves).
    template <typename T>
    static void moveToAllSquaresOutsideIn(T* cp)
    {
        T* objects = new T[64];
        int objectCounter = 0;
        for (int rank = 8; rank >= 5; rank--)
        {
            for (int file = 'h'; file >= 'a'; file--)
            {
                try
                {
                    // Make a copy of the cp object passed in 
                    *(objects + objectCounter) = *cp;
                    // Move the object to the appropriate square
                    (objects + objectCounter)->move(file, rank);
                    // Increment counter so loops below will access new objects
                    objectCounter++;
                }
                catch (invalid_move_ex ex) {}
            }
        }

        for (int rank = 1; rank <= 3; rank++)
        {
            for (int file = 'a'; file <= 'h'; file++)
            {
                try
                {
                    *(objects + objectCounter) = *cp;
                    (objects + objectCounter)->move(file, rank);
                    objectCounter++;
                }
                catch (invalid_move_ex) {}
            }
        }

        for (int file = 'a'; file < 'd'; file++)
        {
            try
            {
                *(objects + objectCounter) = *cp;
                (objects + objectCounter)->move(file, 4);
                objectCounter++;
            }
            catch (invalid_move_ex) {}
        }
        for (int file = 'h'; file > 'd'; file--)
        {
            try
            {
                *(objects + objectCounter) = *cp;
                (objects + objectCounter)->move(file, 4);
                objectCounter++;

            }
            catch (invalid_move_ex) {}
        }
        std::cout << objectCounter;
    }

    // This template is intended to be used to automatically create 63 checkers pieces of type T at Square d4 and attempt to move each piece to a different Square on the checker board (except square d4) starting with inside squares and moving outward (for testing jumping moves).
    template <typename T>
    static void moveToAllSquaresInsideOut(T* cp)
    {
        T* objects = new T[64];
        int objectCounter = 0;
        for (int rank = 5; rank <= 8; rank++)
        {
            for (int file = 'd'; file >= 'a'; file--)
            {
                try
                {
                    *(objects + objectCounter) = *cp;
                    (objects + objectCounter)->move(file, rank);
                    objectCounter++;
                }
                catch (invalid_move_ex) {}
            }
            for (int file = 'e'; file <= 'h'; file++)
            {
                try
                {
                    *(objects + objectCounter) = *cp;
                    (objects + objectCounter)->move(file, rank);
                    objectCounter++;
                }
                catch (invalid_move_ex) {}
            }
        }

        for (int rank = 3; rank >= 1; rank--)
        {
            for (int file = 'd'; file >= 'a'; file--)
            {
                try
                {
                    *(objects + objectCounter) = *cp;
                    (objects + objectCounter)->move(file, rank);
                    objectCounter++;
                }
                catch (invalid_move_ex) {}
            }
            for (int file = 'e'; file <= 'h'; file++)
            {
                try
                {
                    *(objects + objectCounter) = *cp;
                    (objects + objectCounter)->move(file, rank);
                    objectCounter++;
                }
                catch (invalid_move_ex) {}
            }
        }


        for (int file = 'c'; file >= 'a'; file--)
        {
            try
            {
                *(objects + objectCounter) = *cp;
                (objects + objectCounter)->move(file, 4);
                objectCounter++;

            }
            catch (invalid_move_ex) {}
        }

        for (int file = 'e'; file >= 'h'; file++)
        {
            try
            {
                *(objects + objectCounter) = *cp;
                (objects + objectCounter)->move(file, 4);
                objectCounter++;

            }
            catch (invalid_move_ex) {}
        }
    }
};

