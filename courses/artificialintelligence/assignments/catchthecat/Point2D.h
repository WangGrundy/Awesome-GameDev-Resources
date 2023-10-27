#ifndef AWESOMECPPCOURSE_POINT2D_H
#define AWESOMECPPCOURSE_POINT2D_H

#include <string>
#include <cstdint>
#include <vector>

using std::vector;

struct Point2D {
public:
  Point2D(int x, int y) : x(x), y(y){};
  Point2D() = default;
  int x, y;
  bool operator==(const Point2D& rhs) const;
  bool operator!=(const Point2D& rhs) const;
  Point2D& operator=(const Point2D& rhs);
  Point2D operator+(const Point2D& rhs) const;
  Point2D& operator+=(const Point2D& rhs);
  Point2D operator-(const Point2D& rhs) const;
  Point2D& operator-=(const Point2D& rhs);

  inline Point2D Up() const { return *this + UP; };
  inline Point2D Left() const { return *this + LEFT; };
  inline Point2D Right() const { return *this + RIGHT; };
  inline Point2D Down() const { return *this + DOWN; };

  const static Point2D UP;
  const static Point2D DOWN;
  const static Point2D LEFT;
  const static Point2D RIGHT;
  const static Point2D INFINITE;
  std::string to_string();

  inline Point2D NW() const{
    return (y % 2 == 0) ?
                        Point2D(x-1, y-1) :
                        Point2D(x, y-1);
  }
  inline Point2D NE() const{
    return (y % 2 == 0) ?
                        Point2D(x, y-1) :
                        Point2D(x+1, y-1);
  }
  inline Point2D E() const{
    return {x+1, y};
  }
  inline Point2D W() const{
    return {x-1, y};
  }
  inline Point2D SW() const{
    return (y % 2 == 0) ?
                        Point2D(x-1, y+1) :
                        Point2D(x, y+1);
  }
  inline Point2D SE() const{
    return (y % 2 == 0) ?
                        Point2D(x, y+1) :
                        Point2D(x+1, y+1);
  }

  inline vector<Point2D> Neighbors() const{
    return vector<Point2D>{NW(), NE(), E(), W(), SW(), SE()};
  }

  // for unordered set
  size_t operator()(const Point2D& p) const noexcept { return ((uint64_t)p.x) << 32 | (uint64_t)p.y; };

  uint64_t hash(Point2D const& p) const noexcept { return ((uint64_t)p.x) << 32 | (uint64_t)p.y; }
};

namespace std {
  template <> struct hash<Point2D> {
    std::size_t operator()(const Point2D& p) const noexcept { return p(p); }
  };
}  // namespace std

#endif  // AWESOMECPPCOURSE_POINT2D_H
