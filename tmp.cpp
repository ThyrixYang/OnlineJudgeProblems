//
//  main.c
//  DS_01
//
//  Created by app  on 2021/2/28.
//  Copyright  2021年 app . All rights reserved.
//

#include <stdio.h>
int squareByValue(int a) { return a *= a; }
void squareByReference(int &a) { a *= a; }

int main()
{
    int x = 2, y = 3;
    printf("Before:x = %d", x, ",");
    squareByValue(x);
    printf("After:x = %d", x, "\n");
    printf("Before:y = %d", y, ",");
    squareByReference(x);
    printf("After:y = %d", y, "\n");
    return 0;
}
