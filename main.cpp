#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <numeric>
using complvector = std::vector<std::complex<double> >;

class fuckin_iterator
{
    private:
        size_t i;
    public:
       explicit fuckin_iterator(size_t pos):i(pos) {}
       size_t operator*() const {return i;}
       fuckin_iterator& operator++() 
       {
           ++i;
           return *this;
       }
       bool operator != (const fuckin_iterator& other)
       {
           return i != other.i;
       }
};
//////////////////////!
complvector fourier_convert(const complvector & fun, bool trf = false)
{
    complvector hilf(fun.size());
    const double sig {2. * M_PI * (trf ? -1. : 1.)};
    const double div {trf ? 1. : double(fun.size())};
    auto summ ([=, &fun](size_t j){
        return [=, &fun](std::complex<double> c, size_t i){
            return c + fun[i] * std::polar(1., sig * j * i/ double(fun.size()));
        };
    });
    auto sumfit ([=, &fun](size_t j){
        return std::accumulate(fuckin_iterator{0}, fuckin_iterator{fun.size()}, std::complex<double>{}, summ(j) )/ div;
    });
    std::transform(fuckin_iterator{0}, fuckin_iterator{fun.size()}, std::begin(hilf), sumfit);
    return hilf;
}
//////////////////!
static auto gen_func(size_t period)
{
    return [period, x{0}]() mutable {return sin(double(x++) * 2. * M_PI / period);};
}
template<typename Fun>
static complvector genfun_to_con(size_t len, Fun fun)
{
    complvector cv(len);
    std::generate(cv.begin(), cv.end(), fun);
    return cv;
}
////////////////////////!
void display() 
{
    const size_t period {200};
    const size_t length {500};
    std::vector<double> tmp(length);
    std::vector<double> tmpf(length);
    auto genfunc (genfun_to_con(length, gen_func(period)));
    auto fourfunc (fourier_convert(genfunc));
    auto realval ([](std::complex<double> c){return c.real();});
    std::transform(genfunc.begin(), genfunc.end(), tmp.begin(), realval);
    std::transform(fourfunc.begin(), fourfunc.end(), tmpf.begin(), realval);
    //for(const auto & x : tmpf) std::cout << x << " ";
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
    {
        glColor3f(1,0,0); glVertex2f(-20, 0); glVertex2f(500,0);
        glColor3f(0,1,0); glVertex2f(0, -100); glVertex2f(0,100);
    }
  glEnd();
  glBegin(GL_LINES);
    glColor3f(0,.2,1);
    for (float x = 0; x < 480; x += .2) 
    {
        glVertex2f(x, tmp[x]);
    }
  glEnd();
  glBegin(GL_LINES);
    glColor3f(1.,1.,1.);
    for (float x = 0; x < 450; x += .2) 
    {
        glVertex2f(x, tmpf[x]);
    }
  glEnd();
  glFlush();
}
void init() {
    glClearColor(0.25, 0.0, 0.2, 1.0);
    glColor3f(0.6, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 500.0, -1.2, 1.2, 0.0, 100.0);
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1024, 450);
  glutInitWindowPosition(40, 40);
  glutCreateWindow("Fourier transformation");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}