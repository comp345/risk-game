#include <any>
#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

extern void riskGameDriver(string filename = ""); // driver for A2 P3

int main(int, char **)
{
    /* *************************************** */
    /*          A2 P3 : Main Game play         */
    /* *************************************** */


   riskGameDriver("../debug.txt");


}
