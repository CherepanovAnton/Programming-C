/*******************************************************************************
* Programmers: Hayden LaCelle, John Pierce, Ryan Gould                        *
 * Class: CPT_S 122; Lab Section 12L                                           *
 * Programming Assignment: PA #9 - Graphical Game: UNO in C++!                 *
 * Last Updated: 4/25/2025                                                     *
 *                                                                             *
 * Description: This programming assignment requires the development of a      *
 *              graphical application. For this, we have chosen to make a      *
 *              game -- and why not something with a good variety of colors,   *
 *              text, some shapes, and of course, some good-old board game fun *
 *              virtualized? Welcome to UNO in C++!                            *
 *                                                                             *
 * GitHub Repository: https://github.com/HaydenDoesTech/UNOPlusPlus            *
 *                                                                             *
 * Development KanBan Board: https://github.com/users/HaydenDoesTech/projects/ *
 *                           1                                                 *
 ******************************************************************************/
//
// #ifndef TESTCLASS_HPP
// #define TESTCLASS_HPP
// #include "Game.hpp"
// #include "Menu.hpp"
// #include "AI.hpp"
// #include "Game.hpp"
// #include <iostream>
//
// class TestClass {
// public:
//
//     TestClass()=default;
//     ~TestClass()=default;
//
//    void test_get_topdiscard() {
//        Player p1, p2;
//        Game test(p1,p2);
//         Card TestC("Blue", "3", 1);
//         test.getDiscardPile().push_back(TestC);
//         test.get_top_discard();
//         cout << "Top discard: "<< test.get_top_discard()<<'\n';
//     }
//
//     void test_get_topdraw() {
//        Player p1, p2;
//        Game test(p1,p2);
//        Card TestC("Blue", "3", 1);
//         test.getDrawPile().push_back(TestC);
//         cout << "Top draw: "<< test.get_top_draw()<<'\n';
//
//     }
//     void test_discard() {
//        Player p1, p2;
//         Game test(p1,p2);
//         Card TestC("Blue", "3", 1);
//         test.discard(TestC);
//         test.get_top_discard();
//         cout << "Discarded Card: "<< test.get_top_discard()<<'\n';
//
//     }
//     // void test_string_to_color() {
//     //    Player p1, p2;
//     //    Game test(p1,p2);
//     //    cout<<"Testing string red to SF:: red" << test.stringToColor("Red")<< '\n';
//     // }
//     void test_draw() {
//        Player p1, p2;
//        std::vector<Card> TestC;
//         Game test(p1,p2);
//        std::vector<Card> Hand;
//        Hand[0] = {"Blue", "3", 1};
//        Hand[1] = {"Blue", "4", 1};
//        Hand[2] = {"Blue", "5", 1};
//        Hand[3] = {"Blue", "6", 1};
//        Hand[4] = {"Blue", "7", 1};
//        Hand[5] = {"Blue", "8", 1};
//        Hand[6] = {"Blue", "9", 1};
//        p1.setHandIndex(0, Hand[0]);
//        p1.setHandIndex(1, Hand[1]);
//        p1.setHandIndex(2, Hand[2]);
//        p1.setHandIndex(3, Hand[3]);
//        p1.setHandIndex(4, Hand[4]);
//        p1.setHandIndex(5, Hand[5]);
//        p1.setHandIndex(6, Hand[6]);
//        TestC= p1.getHand();
//        std::cout << TestC[0] << '\n';
//
//     }
// };
//
//
// #endif //TESTCLASS_HPP
//
