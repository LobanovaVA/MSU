#include "tree.h"


int main(int argc, char * argv[])
{
    double t = 0;
    int m = 0, k = 0;
    if (argc != 4 || (m = atoi(argv[2])) == 0 || (k = atoi(argv[3])) == 0)
    {printf("Usage: %s filename m k\n", argv[0]); return 1;}
    const char * filename = argv[1];

    Btree tree(m);
    printf("Reading:\n"); tree.read(filename);

    printf("Print tree:\n"); tree.print(tree.getRoot());

    printf("Solving\n");
    while(1)
    {
      printf("Input k: ");
      if(scanf("%i", &k) != 1) {printf("Error read k!\n"); return 2;}
      printf("k = %i\n", k);
      if(k < 0) break;
      t =  clock();
      tree.testAll(k);
      printf("Total Time: %.2f\n", (clock() - t) / CLOCKS_PER_SEC);
    }

    tree.delete_tree(tree.getRoot());
    return 0;
}
