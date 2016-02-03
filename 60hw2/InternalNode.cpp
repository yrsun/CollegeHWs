#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()

BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
  {
    children[i + 1] = children[i];
    keys[i + 1] = keys[i];
  } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()

void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
  {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
  } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()


int InternalNode::getMaximum() const
{
  if(count > 0) // should always be the case
    return children[count - 1]->getMaximum();
  else
    return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
  {
    addToThis(ptr, pos + 1);
    return NULL;
  } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    addToLeft(last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      addToRight(ptr, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


BTreeNode* InternalNode::remove(int value)
{  // to be written by students
  int i, j;
  for(i=0; i< count && keys[i]<=value; i++);
  
  BTreeNode *ptr = children[i-1]->remove(value);

  for(j=0; j<count;j++)
  keys[j]=children[j]->getMinimum();

  if(ptr)
  {
    deleteChild(ptr);
  }

  if(leftSibling == NULL && rightSibling == NULL && parent == NULL && count == 1)
  {
    return this;
  }

  if(count < (internalSize+1)/2)
  {
    if(leftSibling != NULL)
    {
      if(leftSibling->getCount() > (internalSize+1)/2)
      {//left borrow
        InternalNode* Iptr = static_cast < InternalNode * > (leftSibling);
        this->insert(Iptr->borrowfromLeft());
        return NULL;
      }
      else
      {//left merge
        InternalNode* Iptr = static_cast < InternalNode * > (leftSibling);

        for(int i = 0; i < Iptr->getCount(); i++)
        {
          this->insert(Iptr->children[i]);
        }

        if(Iptr->leftSibling!=NULL)
        {
          this->setLeftSibling(Iptr->getLeftSibling());
          leftSibling->setRightSibling(this);
        }
        else
        {
          this->setLeftSibling(NULL);
        }

        Iptr->setLeftSibling(NULL);
        Iptr->setRightSibling(NULL);

        return Iptr;
      }
    }
    else if(rightSibling != NULL)
    {
      if(rightSibling->getCount() > (internalSize+1)/2)
      {//right borrow
        InternalNode* Iptr = static_cast < InternalNode * > (rightSibling);
        this->insert(Iptr->borrowfromRight());
        return NULL;
      }
      else
      {//right merge
        InternalNode* Iptr = static_cast < InternalNode * > (rightSibling);

        for(int i = 0; i < Iptr->getCount(); i++)
        {
          this->insert(Iptr->children[i]);
        }

        if(Iptr->rightSibling!=NULL)
        {
          this->setRightSibling(Iptr->getRightSibling());
          rightSibling->setLeftSibling(this);
        }
        else
        {
          this->setRightSibling(NULL);
        }

        Iptr->setLeftSibling(NULL);
        Iptr->setRightSibling(NULL);

        return Iptr;
      }
    }
  }




  return NULL; // filler for stub
} // InternalNode::remove(int value)

BTreeNode* InternalNode::borrowfromLeft()
{
  BTreeNode *max;
  max = children[count-1];
  deleteChild(max);
  return max;
}

BTreeNode* InternalNode::borrowfromRight()
{
  BTreeNode *min;
  min = children[0];
  deleteChild(min);
  return min;
}

void InternalNode::deleteChild(BTreeNode *ptr)
{
  for (int i = 0; i < count; ++i)
  {
    if(i==count-1)
    {
      break;
    }
    if(children[i]>=ptr)
    {
      children[i]=children[i+1];
      keys[i]=children[i]->getMinimum();
    }
  }
  count--;
}

BTreeNode* InternalNode::firstChild()
{
  return children[0];
}

void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMinimum(this);
      break;
    }
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()

