#include <stdio.h>
#include "graf.h"

int main()
{
    graf* g = create_graph("grafic.txt");
    printg(g);
    nadji_naj(g);

    return 0;
}