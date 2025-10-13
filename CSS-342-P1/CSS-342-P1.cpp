// CSS 342 P1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PPMImage.h"

using namespace std;

int main()
{
    PPMImage test(10, 10, 255);
    PPMImage tester(10, 10, 255);

   /*vector<RGBValue> vec;
    RGBValue red;
    red.red = 128;

    for (int i = 0; i < 10; i++) {
        vec.push_back(red);
    }

    PPMLine tester(vec, 255);*/
    RGBValue purple;
    purple.blue = 128;
    purple.red = 128;
    RGBValue green;
    green.green = 128;
    RGBValue red;
    red.red = 128;
    //test.drawLine(3, 7, 8, 5, purple);
    
    for (int i = 0; i < 10; i++) {
        test.drawLine(i, 0, i, 9, purple);
        tester.drawLine(i, 0, i, 9, purple);
    }
    

    /*tester.drawLine(2, 0, 2, 7, green);
    tester.drawLine(0, 0, 0, 3, red);*/
    //tester = test;

    PPMImage test2 = test - tester;

    PPMImage t;
    PPMImage t2;
    bool test3;

    test3 = test == tester;
    system("pause");
}