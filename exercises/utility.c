/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Utility methods for the assignments - Source
 * @date 29-06-2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

void swap(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}