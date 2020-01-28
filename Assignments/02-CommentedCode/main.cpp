//////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Taylor Mendez
// Email:            tlmendez0302@my.msutexas.edu
// Label:            A02
// Title:            Commenting Code
// Course:           CMPS 2143
// Semester:         Spring 2020
//
// Description:
//       This program implements a class that allows a linked list to be used just like 
//       an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
//       array elements, but really it traverses the list to find the specified node using
//       an index value. It also overloads the "+" sign allowing a user to "add"
//       or "push" items onto the end of the list.
//       
// Usage: 
//      - $ ./main filename
//      - This will read in a file containing whatever values to be read into our list/array. 
//      
// Files:            
//      main.cpp    : driver program 
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

int A[100];   //array containing 101 ints

struct Node
{
    int x;
    Node *next;

    //constructor
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

/**
 * Class Name
 * 
 * Description:
 *      This class allows a linked list to be used as an array.
 * 
 * Public Methods:
 *                           List()
 *          void             Push(int)
 *          void             Insert(int)
 *          void             PrintTail()
 *          string           Print()
 *          int              Pop()
 *          List             operator+(const List &Rhs)
 *          int              operator[](int)
 *          friend ostream   &operator<<(ostream &, List)
 *         
 * Private Methods:
 * 
 * Usage: 
 * 
 *      Push(int 2);          //append node with value 2 
 *      Insert(int 3);        //insert node with  value of three to 
 *                            // a specific point in list
 *      PrintTail();          //print value in last node
 *      Print();              //prints all vallues in list
 *      Pop();                //
 *      L3 = L1 + L2;         //combine L1 and L2 into L3 list
 *      L3[5]                 //return value in position 6
 *      cout << L3;           //prints all values in L3
 *      
 */
class List
{
  private:
    Node *Head;   //list head
    Node *Tail;   //list tail
    int Size;     //list size

  public:

    //Constructor 
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public: Push
     * 
     * Description:
     *      appends node to the tail of the list
     * 
     * Params:
     *      int val:  value held in node
     * 
     * Returns:
     *      none
     */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public: Insert
     * 
     * Description:
     *      inserts node to a specific point in the list
     * 
     * Params:
     *      int val:  value held in node
     * 
     * Returns:
     *      none
     */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public: PrintTail
     * 
     * Description:
     *      prints the value held in the last node in the list
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      none
     */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }

    /**
     * Public: Print
     * 
     * Description:
     *      creates a string of all values in the list
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      string of all values in the list
     */
    string Print()
    {
        Node *Temp = Head;
        string list;   //string that will contain all values in the list

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented 
    int Pop()
    {
        Size--;
        return 0; //
    }

    /**
     * Public: operator+
     * 
     * Description:
     *      appends node to the tail of the list
     * 
     * Params:
     *      const List Rhs:  the second list
     * 
     * Returns:
     *      new list that holds the values of two lists
     */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    /**
     * Public: operator[]
     * 
     * Description:
     *      Implementation of [] operator. This function returns an
     *      int value as if the list were an array.
     * 
     * Params:
     *      int index:  desired index
     * 
     * Returns:
     *      int Temp->x:  value held in desired index
     */
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
     * Public: operator<<
     * 
     * Description:
     *      prints list by using overloaded "<<" operator
     * 
     * Params:
     *      ostream &os:  
     *      List L :  instance of list to be printed
     * 
     * Returns:
     *      ostream &os:  
     */
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1;   //creates instance of a list
    List L2;   //creates instance of a list

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
