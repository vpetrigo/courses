#ifndef MAILRU_COURSE_GUI_HPP
#define MAILRU_COURSE_GUI_HPP

// FLTK headers
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <memory>
#include <string>
#include <vector>

namespace downloader {
// FLTK callback function definition
using Address = void*;
using Callback = void (*)(Address, Address);

struct Point {
  Point() : x_{0}, y_{0} {}
  Point(int x, int y) : x_{x}, y_{y} {}

  int x_;
  int y_;
};

class Widget {
  // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
 public:
  Widget(Point xy, int w, int h, const std::string& s, Callback cb)
      : loc{xy}, width{w}, height{h}, label{s}, do_it{cb} {}

  virtual void move(int dx, int dy) {
    hide();
    pw_->position(loc.x += dx, loc.y += dy);
    show();
  }

  Widget& operator=(const Widget&) = delete;
  Widget(const Widget&) = delete;

  virtual void hide() { pw_->hide(); }
  virtual void show() { pw_->show(); }
  virtual void attach(Window&) = 0;
  virtual ~Widget() = default;

  Point loc;
  int width;
  int height;
  string label;
  Callback do_it;

 protected:
  // every Widget belongs to a Window
  Window* own_;
  // connection to the FLTK Widget
  Fl_Widget* pw_;
};

class ProgressBar : public Widget {
 public:
  ProgressBar(Point xy, int w, int h, const std::string& s)
      : Widget(xy, w, h, s, nullptr) {}

  void attach(Window& w) override;
};

class Window : public Fl_Window {
 public:
  // let the system pick the location:
  Window(int w, int h, const std::string& title);

  virtual ~Window() = default;

  int x_max() const { return width_; }
  int y_max() const { return height_; }

  void resize(int ww, int hh) {
    width_ = ww, height_ = hh;
    size(ww, hh);
  }

  void set_label(const std::string& s) { copy_label(s.c_str()); }
  // add widget to window
  void attach(Widget&);
  // remove w from window (deactivates callbacks)
  void detach(Widget& w);

 protected:
  void draw();

 private:
  int width_;
  int height_;  // window size

  // initialize Window
  void init();
};

}  // namespace downloader

#endif  // MAILRU_COURSE_GUI_HPP
