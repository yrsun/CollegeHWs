#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()




LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()


LeafNode* LeafNode::remove(int value)
{ 
  deleteFromThis(value);

  if(count < (leafSize+1)/2)
  {
    if(leftSibling!=NULL)
    { 
      if(leftSibling->getCount() > (leafSize+1)/2)
      {//left borrow
        LeafNode* ptr = static_cast < LeafNode * > (leftSibling);
        this->insert(ptr->borrowfromLeft());
        return NULL;
      }
      else
      {//left merge
        LeafNode* ptr = static_cast < LeafNode * > (leftSibling);

        for(int i = 0; i < ptr->getCount(); i++)
        {
          this->insert(ptr->values[i]);
        }

        if(ptr->leftSibling!=NULL)
        {
          this->setLeftSibling(ptr->getLeftSibling());
          leftSibling->setRightSibling(this);
        }
        else
        {
          this->setLeftSibling(NULL);
        }

        ptr->setLeftSibling(NULL);
        ptr->setRightSibling(NULL);

        return ptr;
      }
    }
    else if(rightSibling!=NULL)
    { 
      if(rightSibling->getCount() > (leafSize+1)/2)
      {//right borrow
        LeafNode* ptr = static_cast < LeafNode * > (rightSibling);
        this->insert(ptr->borrowfromRight());
        return NULL;
      }
      else 
      {//right merge
        LeafNode* ptr = static_cast < LeafNode * > (rightSibling);

        for(int i = 0; i < ptr->getCount(); i++)
        {
          this->insert(ptr->values[i]);
        }

        if(ptr->rightSibling!=NULL)
        {
          this->setRightSibling(ptr->getRightSibling());
          rightSibling->setLeftSibling(this);
        }
        else
        {
          this->setRightSibling(NULL);
        }

        ptr->setLeftSibling(NULL);
        ptr->setRightSibling(NULL);

        return ptr;
      }
    }
  }
//    else // both siblings full or non-existent
//      return split(value, last);
  // To be written by students
  return NULL;  // filler for stub
}  // LeafNode::remove()

int LeafNode::borrowfromLeft()
{
  int max;
  max = values[count-1];
  deleteFromThis(max);
  return max;
}

int LeafNode::borrowfromRight()
{
  int min;
  min = values[0];
  deleteFromThis(min);
  return min;
}


void LeafNode::deleteFromThis(int value)
{
  int j=0;
  for (int i = 0; i < count; ++i)
  {
    if(i==count-1)
    {
      if(values[i]!=value&&j==0)
        count++;
      break;
    }
    if(values[i]>=value)
    {
      values[i]=values[i+1];
      j++;
    }
  }

  count--;
}

