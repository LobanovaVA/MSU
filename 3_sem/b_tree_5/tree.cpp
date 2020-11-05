#include "tree.h"


int Btree::read(const char * filename)
{
  FILE * fp;
  student buf; int i = 0;
  if(!(fp = fopen(filename, "r"))) return -1;
  if(!(buf.read(fp)))
  {fclose(fp); printf("cant read\n"); return -2;}

  Node_Btree ret1 = 0, ret2;
  Node_Btree * retP1 = &ret1, * retP2 = &ret2;
  student * res = insert(&((new student) -> move(buf)), 0, &retP1, &retP2);
  if(res) {insertnode(res, 0, &retP1, &retP2);}
  i++;
  while(1) 
  {
    if(!buf.read(fp)) {fclose(fp); return i;}
    student * res = insert(&((new student) -> move(buf)), 0, &retP1, &retP2);
    if(res) {insertnode(res, 0, &retP1, &retP2);}
    i++;
  }
}

student * Btree::insert(student * value, Node_Btree * cur, Node_Btree ** p_left, Node_Btree ** p_right)
{
  if(!root) {root = new Node_Btree(2 * order);}
  if(!cur) {cur = root;}
  int tmp = cur -> find_ins(value);
  if(cur->pchildren[0])
  {
    student * res = insert(value, cur -> pchildren[tmp], p_left, p_right);
    if(!(res == 0))
    {res = insertnode(res, cur, p_left, p_right);}
    return res;
  }
  else
  {
    if(cur -> cur_size < 2 * order)
    {
      for(int i = cur -> cur_size - 1; i >= tmp; i--)
      {cur -> pvalues[i + 1] = cur -> pvalues[i];}
      cur -> pvalues[tmp] = value; cur -> cur_size++;
      return 0;
    }
    else
    {
      Node_Btree * right = new Node_Btree(2 * order);
      student * median = 0;
      if(tmp<order)
      {median = cur -> pvalues[order - 1];}
      else if(tmp == order)
      {median = value;}
      else
      {median = cur -> pvalues[order];}

      if(tmp <= order)
      {
          for(int i = 0; i < order; i++)
          {
              right -> pvalues[i] = cur -> pvalues[i + order];
              cur -> pvalues[i + order] = 0;
          }
      }
      else
      {
          int i = 0;
          for(i = 0; i < tmp - order - 1; i++)
          {
              right -> pvalues[i] = cur -> pvalues[i + order + 1];
              cur -> pvalues[i + order + 1] = 0;
          }
          right -> pvalues[i] = value; i++;
          for(; i < order; i++)
          {
              right -> pvalues[i] = cur -> pvalues[i + order];
              cur -> pvalues[i + order] = 0;
          }
      }

      if(tmp < order)
      {
          for(int i = order - 1; i >= tmp; i--)
          {cur -> pvalues[i + 1] = cur -> pvalues[i];}
          cur -> pvalues[tmp] = value; cur -> cur_size++;
      }
      for(int i = order; i < 2 * order; i++)
      {
          cur -> pvalues[i] = 0;
          right -> pvalues[i] = 0;
      }
      right -> cur_size = order;
      cur -> cur_size = order;
      *p_right = right;
      *p_left = cur;
      return median;
    }
  }
}

student * Btree::insertnode(student * value, Node_Btree* cur, Node_Btree ** p_left, Node_Btree ** p_right)
{
    if(!cur)
    {
        cur = root;
        if(cur == root)
        {
            root = new Node_Btree(2 * order);
            root -> pvalues[0] = value;
            root -> pchildren[0] = *p_left;
            root -> pchildren[1] = *p_right;
            root -> cur_size++;
            return 0;
        }
    }
    int tmp = cur -> find_ins(value);
    if(cur -> cur_size < 2 * order)
    {
        for(int i = cur -> cur_size - 1; i >= tmp; i--)
        {
            cur -> pvalues[i + 1] = cur -> pvalues[i];
            cur -> pchildren[i + 2] = cur -> pchildren[i + 1];
        }
        cur -> pvalues[tmp] = value; cur -> cur_size++;
        cur -> pchildren[tmp] = *p_left;
        cur -> pchildren[tmp + 1] = *p_right;
        return 0;
    }
    else
    {
        Node_Btree * right = new Node_Btree(2 * order);
        student * median = 0;
        if(tmp < order)
        {median = cur -> pvalues[order - 1];}
        else if(tmp == order)
        {median = value;}
        else
        {median = cur -> pvalues[order];}
        if(tmp <= order)
        {
            int i = 0;
            for(i = 0; i < order; i++)
            {
                right -> pvalues[i] = cur -> pvalues[i + order];
                right -> pchildren[i] = cur -> pchildren[i + order];
                cur -> pvalues[i + order] = 0;
                cur -> pchildren[i + order] = 0;
            }
            right -> pchildren[i] = cur -> pchildren[i + order];
            cur -> pchildren[i + order] = 0;
        }
        else
        {
            int i = 0;
            for(i = 0; i < tmp - order - 1; i++)
            {
                right -> pvalues[i] = cur -> pvalues[i + order + 1];
                right -> pchildren[i] = cur -> pchildren[i + order + 1];
                cur -> pvalues[i + order + 1] = 0;
                cur -> pchildren[i + order + 1] = 0;
            }
            right -> pvalues[i] = value;
            right -> pchildren[i] = *p_left;
            cur -> pchildren[i + order + 1] = *p_right;
            i++;
            for(; i < order; i++) 
            {
                right -> pvalues[i] = cur -> pvalues[i + order];
                right -> pchildren[i] = cur -> pchildren[i + order];
                cur -> pvalues[i + order] = 0;
                cur -> pchildren[i + order] = 0;
            }
            right -> pchildren[i] = cur -> pchildren[i + order];
            cur -> pchildren[i + order] = 0;
        }

        if(tmp < order)
        {
            for(int i = order - 1; i >= tmp; i--)
            {
                cur -> pvalues[i + 1] = cur -> pvalues[i];
                cur -> pchildren[i + 2] = cur -> pchildren[i + 1];
            }
            cur -> pvalues[tmp] = value; cur -> cur_size++;
            cur -> pchildren[tmp] = *p_left;
            cur -> pchildren[tmp + 1] = *p_right;
        }

        if(tmp == order)
        {
            right -> pchildren[0] = *p_right;
            cur -> pchildren[order] = *p_left;
        }
        for(int i = order; i < 2 * order; i++)
        {
            cur -> pvalues[i] = 0;
            right -> pvalues[i] = 0;
        }
        right -> cur_size = order;
        cur -> cur_size = right -> cur_size = order;
        *p_right = right;
        *p_left = cur;
        return median;
  }
}



void Btree::print(Node_Btree * root, int level, int index)
{
  if(!root) {return;}
  if(level > MAX_PRINT) {return;}
  for(int i = 0; i < level; i++) {printf("| ");}
  if(index >= 0) {printf("%i: ", index);}
  root -> print(order);
  for(int i = 0; i < (2 * order + 1 < MAX_HEIGHT_PRINT ? 2 * order + 1 : MAX_HEIGHT_PRINT); i++)
  {print(root -> pchildren[i], level + 1, i);}
}
