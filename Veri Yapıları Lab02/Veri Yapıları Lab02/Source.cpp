//Melisa DEMÝRHAN
//Özge KATIRCI
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include<sstream>
#include<algorithm>
#include<math.h>
#include "Poly.h"

using namespace std;

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode* CreatePoly(char* expr) {
    struct PolyNode* head = NULL;
    struct PolyNode* new_node, * ptr;
    string str(expr);
    string str2;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            str2 += str[i];
        }
    }
    str = str2;
    if (str[0] != '-')
    {
        str = "+" + str;
    }

    for (int i = 0; i < str.size(); i++)
    {
        string coef = "";
        string exp = "";

        bool sign = (str[i] == '-') ? 1 : 0;

        i++;

        while (str[i] != 'x' && str[i] != NULL)
        {
            coef += str[i];
            i++;
        }

        if (coef == "-" || coef == "+" || coef == "")
        {
            coef = "1";
        }
        double c = stod(coef);
        if (sign)
        {
            c = c * -1;
        }

        if (str[i] == NULL)
        {
            if (head == NULL)
            {
                new_node = new PolyNode[sizeof(PolyNode)];
                new_node->coef = c;
                new_node->exp = 0;
                new_node->next = NULL;
                head = new_node;
            }
            else
            {
                ptr = head;
                while (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                new_node = new PolyNode[sizeof(PolyNode)];
                new_node->coef = c;
                new_node->exp = 0;
                new_node->next = NULL;
                ptr->next = new_node;

            }
            break;
        }

        i++;

        if (str[i] == '^')
        {
            i++;
        }

        while (str[i] != '+' && str[i] != '-' && str[i] != NULL)
        {
            exp += str[i];
            i++;
        }

        if (exp == "-" || exp == "+" || exp == "")
        {
            exp = "1";
        }

        stringstream po;
        po << exp;
        int p;
        po >> p;

        if (head == NULL)
        {
            new_node = new PolyNode[sizeof(PolyNode)];
            new_node->coef = c;
            new_node->exp = p;
            new_node->next = NULL;
            head = new_node;
        }
        else
        {
            ptr = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            new_node = new PolyNode[sizeof(PolyNode)];
            new_node->coef = c;
            new_node->exp = p;
            new_node->next = NULL;
            ptr->next = new_node;
        }
        i--;
    }

    
   

    return head;
}

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
    PolyNode* current = poly;
    PolyNode* next;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
    poly = NULL;
} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode* head, double coef, int exp) {
    int temp = 0;
    PolyNode* p = head;
    struct PolyNode* q = NULL;

    while (p != NULL) {
        if (p->exp == exp) {
            temp = 1;
            p->coef += coef;
            if (p->coef == 0) {
                if (q == NULL)
                    head = p->next;
                else
                    q->next = p->next;

                q = NULL;
            }
        }
        q = p;
        p = p->next;

    }
    if (temp == 0) {
        PolyNode* node = new PolyNode();
        node->coef = coef;
        node->exp = exp;
        node->next = NULL;
        PolyNode** t = &head;
        while ((*t) != NULL && exp > (*t)->exp) {
            t = &((*t)->next);
        }
        node->next = *t;
        *t = node;
    }

   
   

    return  head;
} // end-AddNode


//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
    PolyNode* poly3 = NULL;

    while (poly1->next)
    {
        poly3 = AddNode(poly3, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    if (poly1->exp == 0 || poly1 != NULL)
    {
        poly3 = AddNode(poly3, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2->next)
    {
        poly3 = AddNode(poly3, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }
    if (poly2->exp == 0 || poly2 != NULL)
    {
        poly3 = AddNode(poly3, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }

    PolyNode* current = poly3;
    PolyNode* prev = NULL, * next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    poly3 = prev;

    return poly3;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
    PolyNode* poly3 = NULL;

    while (poly1->next)
    {
        poly3 = AddNode(poly3, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    if (poly1->exp == 0 || poly1 != NULL)
    {
        poly3 = AddNode(poly3, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2->next)
    {
        poly3 = AddNode(poly3, -1 * (poly2->coef), poly2->exp);
        poly2 = poly2->next;
    }
    if (poly2->exp == 0 || poly2 != NULL)
    {
        poly3 = AddNode(poly3, -1 * (poly2->coef), poly2->exp);
        poly2 = poly2->next;
    }
    PolyNode* current = poly3;
    PolyNode* prev = NULL, * next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    poly3 = prev;
    return poly3;

} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
    struct PolyNode* poly3 = NULL;

    PolyNode* ptr1, * ptr2;
    ptr1 = poly1;
    ptr2 = poly2;
    while (ptr1 != NULL && ptr2 != NULL) {
        while (ptr1 != NULL) {
            while (ptr2 != NULL) {
                int  exp;
                double coef;
                if (ptr1->next == 0 && ptr2->next == 0)
                {
                    coef = ptr1->coef * ptr2->coef;
                    exp = ptr1->exp + ptr2->exp;
                    poly3 = AddNode(poly3, coef, exp);
                    break;
                }
                coef = ptr1->coef * ptr2->coef;
                exp = ptr1->exp + ptr2->exp;

                poly3 = AddNode(poly3, coef, exp);

                ptr2 = ptr2->next;
            }
            ptr2 = poly2;

            ptr1 = ptr1->next;
        }
    }

    PolyNode* current = poly3;
    PolyNode* prev = NULL, * next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    poly3 = prev;
    return poly3;
} //end-Multiply
//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode* poly, double x) {
    double result = 0;
    while (poly->next)
    {
        result += ((double)poly->coef * (double)pow(x, poly->exp));
        poly = poly->next;
    }
    if (poly->exp == 0)
    {
        result += (double)poly->coef;
    }

  
    return result;
} //end-Evaluate
//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
    PolyNode* p = new PolyNode[sizeof(PolyNode)];
    PolyNode* poly2 = p;
    p = poly2;

    while (poly->next)
    {
        if (poly->next->exp == 0)
        {
            poly2->coef = poly->coef * poly->exp;
            poly2->exp = poly->exp - 1;
            poly2->next = NULL;
            break;
        }
        else
        {

            poly2->coef = poly->coef * poly->exp;
            poly2->exp = poly->exp - 1;
            poly = poly->next;

            poly2->next = new PolyNode[sizeof(PolyNode)];
            poly2 = poly2->next;
            poly2->next = NULL;
        }
    }

    if (poly->exp == 0 && poly->coef != '\0')
    {
        poly2->coef = 0;
        poly2->exp = 0;
        poly2->next = NULL;
    }

    if (poly->exp != '\0' && poly->coef != '\0' && poly->next == NULL)
    {
        poly2->coef = poly->coef * poly->exp;
        poly2->exp = poly->exp - 1;
        poly2->next = NULL;
    }

    poly = p;
    return poly;
} //end-Derivative
//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode* poly, int x1, int x2) {
    int x, y, j = -13;
    double control;

    for (y = 12; -12 < y; y--)
    {
        if (y == 0)
        {
            for (int i = -39; i <= 39; i++)
            {
                if (i % 5 == 0) {
                    cout << "+";
                }
                else
                {
                    cout << "-";
                }
            }
        }
        for (x = -39; x <= 39; x++)
        {
            if (x == 0)
            {
                j++;
                if (y != 0)
                {
                    if (j % 5 == 0)
                    {
                        if (j != 30)
                        {
                            cout << "+";
                        }
                    }
                    else
                    {
                        cout << "|";
                    }
                }
            }

            if (x <= x2 && x >= x1)
            {
                control = Evaluate(poly, x);

                if (y != 0 && x != 0)
                {
                    if ((abs(y - control) < 0.5))
                    {
                        cout << "*";
                    }
                    else {
                        cout << " ";
                    }
                }
            }
            else
            {
                if (y != 0)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
} //end-Plot