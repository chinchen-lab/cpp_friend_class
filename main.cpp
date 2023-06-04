#include <iostream>
using namespace std;

class CPoint {
private:
    friend class CLine;
    int x, y;
    void Offset(int diff) {
        x += diff; y += diff;
    }
    friend CPoint offset(CPoint &, int); // outer function (friend)
public:
    CPoint() { x = 0; y = 0; }
    CPoint(int a, int b) { x = a; y = b; }
    void set(int a, int b) { x = a; y = b; }
    void Print() { cout << x << " " << y << endl; }
};

CPoint offset(CPoint &p, int diff) {
    p.x += diff; p.y += diff;
    return p;
}

class CLine {
private:
    CPoint p1, p2;
public:
    CLine(int x, int y, int w, int z) {
        p1.x = x; p1.y = y; // access private in CPoint
        p2.x = w; p2.y = z;
    }
    void Print() {
        // call public Print in CPoint
        cout << "Point 1:"; p1.Print();
        cout << "Point 2:"; p2.Print();
    }
    void Display() {
        offset(p1, 100); // call friend func. in CPoint
        p2.Offset(200);  // call private func. in CPoint
        Print();
    }
};

int main() {
    CPoint p1(2, 4), p2(6, 8);
    p1.Print(); p2.Print(); // 2 4; 6 8
    //p1.Offset(3); // error! --> Offset is private function! main is not CPoint's friend
    
    CLine l1(1, 3, 5, 7), l2(2, 4, 6, 8);
    l1.Print(); // 1 3; 5 7
    l2.Display(); //102 104; 206 208
}