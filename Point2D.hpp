#pragma once

#include <iostream>

class Point2D {
  private:   
    int x;
    int y;

  public:
    Point2D();
    Point2D(int a, int b);
    int getX() const;
    int getY() const;

    void setX(int);
    void setY(int);

    std::string to_string();
    Point2D& operator+=(const Point2D other);


    friend std::ostream& operator<< (std::ostream& output,const Point2D& p);

   
};