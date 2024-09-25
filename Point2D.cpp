#include "Point2D.hpp"

Point2D::Point2D() {x=0; y=0;}

Point2D::Point2D(int a, int b) : x(a) , y(b) {}

 int Point2D::getX() const
 {
    return x;
 }

 int Point2D::getY() const
 {
    return y;
 }


 void Point2D::setX(int a)
 {
    x = a;
 }
void Point2D::setY(int b)
{
    y = b;
}

Point2D& Point2D::operator+=(Point2D other)
{
   x += other.getX();
   y += other.getY();
   return *this;

}


std::ostream& operator<< (std::ostream& output,const Point2D& p)
{
     output << "["<< p.getX() << ',' << p.getY() <<"]";
     return output;
}