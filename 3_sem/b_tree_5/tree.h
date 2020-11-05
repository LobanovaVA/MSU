#include "student.h"


class Btree;

class Node_Btree
{
  private:
    student ** pvalues;
    Node_Btree ** pchildren;
    int cur_size;
    friend class Btree;

  public:
    Node_Btree(int size = 0)
    {
      if(!size)
      {pvalues = 0; pchildren = 0;}
      else
      {
        pvalues = new student* [size];
        pchildren = new Node_Btree* [size + 1];
        for(int i = 0; i < size; i++)
        {pvalues[i] = 0;}
        for(int i = 0; i < size + 1; i++)
        {pchildren[i] = 0;}
      }
      cur_size = 0;
    }

    void delete_node()
    {
      int i = 0;
      for(i = 0; i < cur_size; i++)
      {delete pvalues[i];}
      if(cur_size)
      {delete [] pvalues; delete [] pchildren;}
      cur_size=0;
    }

    int find_ins(student *x)
    {
        int m =0, l = cur_size, s;
        while(m != l)
        {
            s = (m + l) / 2;
            if (*x > *pvalues[s]) m = s + 1;
            else l = s;
        }
        return m;
    }

                                                      void clear(int n)
                                                      {
                                                        for(int i = n; i < cur_size; i++)
                                                        {pvalues[i] = 0; pchildren[i + 1] = 0;}
                                                        cur_size = n;
                                                      }

    void full_clear()
    {
      int i = 0;
      for(i = 0; i < cur_size; i++)
      {pvalues[i] = 0; pchildren[i] = 0;
      }
      pchildren[i] = 0;
      cur_size = 0;
    }

    void print(int order)
    {
      if(!pvalues) {return;}
      for(int i = 0; i < (2 * order < MAX_LEN_PRINT ? 2 * order : MAX_LEN_PRINT); i++)
      {
        if(pvalues && pvalues[i] )pvalues[i] -> print();
        else {printf("N N");}
        printf(", ");
      }
      if(pchildren && pchildren[0] == 0) {printf("<END>");}
      printf("\n");
    }
};

class Btree
{
  private:
    int order;
    Node_Btree * root;
    
  public:
    Btree(int order) {this -> root = 0; this -> order = order;}

    void delete_tree(Node_Btree * root)
    {
      if(!root) return;
      for(int i = 0; i < root -> cur_size + 1; i++)
      {delete_tree(root -> pchildren[i]);}
      root -> delete_node();
      delete root;
    }

    int read(const char * filename);
    student * insert(student * value, Node_Btree * cur, Node_Btree ** p_left, Node_Btree ** p_right);
    student * insertnode(student * res, Node_Btree * cur, Node_Btree ** p_left, Node_Btree ** p_right);
    void print(Node_Btree * root, int level = 0, int index = -1);
    int getOrder() {return order;}
    Node_Btree * getRoot() {return root;}

    void testAll(int k)
    {
      double t1 = clock(); int res1 = task1(k); t1 = (clock() - t1) / CLOCKS_PER_SEC;
      printf("Result1: %9i Time1: %1.2f\n", res1, t1);
      double t2 = clock(); int res2 = task2(k); t2 = (clock() - t2) / CLOCKS_PER_SEC;
      printf("Result2: %9i Time2: %1.2f\n", res2, t2);
      double t3 = clock(); int res3 = task3(k); t3 = (clock() - t3) / CLOCKS_PER_SEC;
      printf("Result3: %9i Time3: %1.2f\n", res3, t3);
      double t4 = clock(); int res4 = task4(k); t4 = (clock() - t4) / CLOCKS_PER_SEC;
      printf("Result4: %9i Time4: %1.2f\n", res4, t4);
      double t5 = clock(); int res5 = task5(k); t5 = (clock() - t5) / CLOCKS_PER_SEC;
      printf("Result5: %9i Time5: %1.2f\n", res5, t5);
      double t6 = clock(); int res6 = task6(k); t6 = (clock() - t6) / CLOCKS_PER_SEC;
      printf("Result6: %9i Time6: %1.2f\n", res6, t6);
    }

    void task1solve(Node_Btree * root, int k, int & counter)
    {
      if(!root) {return;}
      for(int i = 0; i < root -> cur_size + 1; i++)
      {task1solve(root -> pchildren[i], k, counter);}
      if(root -> cur_size + 1 == k && root -> pchildren && root -> pchildren[0])
      {counter += root -> cur_size;}
    }

    int task2solve(Node_Btree * root, int k, int & counter, int & count_students)
    {
      if(!root) {return 0;}
      int n_nodes = 1;
      int n_students = root -> cur_size;
      count_students = n_students;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size +1 ; i++)
        {
          n_nodes += task2solve(root -> pchildren[i], k, counter, count_students);
          n_students += count_students;
        }
      }
      count_students = n_students;
      if (n_nodes <= k) counter += n_students;
      return n_nodes;
    }

    int task3solve(Node_Btree * root, int k, int &counter, int &count_students, int &res)
    {
      if(!root) {return 0;}
      int max = 0, tmp = 0;
      int n_students = root -> cur_size;
      count_students = n_students;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {
          tmp = task3solve(root -> pchildren[i], k, counter, count_students, res);
          n_students += count_students;
          max = tmp > max ? tmp : max;
        }
      }
      count_students = n_students;
      int height = max + 1;
      if(height <= k) 
      {res += n_students;}
      return height;
    }

    int  task4solve(Node_Btree * root, int k, int &counter, int h, int &count_students, int &res)
    {
      if(!root) return 0;
      int maxWidth = 0;
      int n_students = root -> cur_size;
      count_students = n_students;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {
          task4solve(root -> pchildren[i], k, counter, h - 1, count_students, res);
          n_students += count_students;
        }
      }
      count_students = n_students;
      if(maxWidth > k)
      {return k + 1;}
      int Width;
      int i;
      for(i = 1; i <= h; i++)
      {
        Width = getNodeWidth(root, i);
        if(Width > maxWidth)
        {maxWidth = Width; if(maxWidth > k) break;}
      }
      if(maxWidth <= k) {counter++; res += n_students;}
      return maxWidth;
    }

    int task5solve(Node_Btree* root, int level)
    {
      if(!root) {return 0;}
      if(level == 1)
      {return root -> cur_size;}
      else if (level > 1)
      {
        int tmp = 0;
        if(root -> pchildren[0])
        {
          for(int i = 0; i < root -> cur_size + 1; i++)
          {tmp += task5solve(root -> pchildren[i], level - 1);}
        }
        return tmp;
      }
      return 0;
    }

    void task6solve(Node_Btree * root, int k, int curlevel, int &counter, int &count_students)
    {
      if(!root) {return;}
      if(curlevel > k) {return;}
      count_students += root->cur_size;
      if(curlevel==k && !root->pchildren[0]){
        counter+=count_students;
      }
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {task6solve(root -> pchildren[i], k, curlevel + 1, counter, count_students);}
      }
      count_students -= root -> cur_size;
    }

    int getNodeWidth(Node_Btree* root, int level)
    {
      if(!root) {return 0;}
      if(level == 1) {return 1;}
      else if (level > 1)
      {
        int tmp = 0;
        if(root -> pchildren[0])
        {
          for(int i = 0; i < root -> cur_size + 1; i++)
          {tmp += getNodeWidth(root -> pchildren[i], level - 1);}
        }
        return tmp;
      }
      return 0;
    }

    int task1(int k)
    {
      int counter = 0;
      task1solve(root, k, counter);
      return counter;
    }

    int task2(int k)
    {
      int counter = 0, count_students = 0;
      task2solve(root, k, counter,count_students);
      return counter;
    }

    int task3(int k)
    {
      int counter = 0, sum = 0, res = 0;
      task3solve(root, k, counter, sum, res);
      return res;
    }

    int task4(int k)
    {
      int counter = 0, sum = 0, res = 0;
      task4solve(root, k, counter, getHeight(root), sum, res);
      return res;
    }

    int task5(int k)
    {return task5solve(root, k);}

    int task6(int k)
    {
      int counter = 0, count_students = 0;
      task6solve(root, k, 1, counter, count_students);
      return counter;
    }

    int getHeight(Node_Btree * root)
    {
      if(!root) {return 0;}
      int max = 0, tmp = 0;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {
          tmp = getHeight(root -> pchildren[i]);
          max = tmp > max ? tmp : max;
        }
      }
      int height = max + 1;
      return height;
    }
};