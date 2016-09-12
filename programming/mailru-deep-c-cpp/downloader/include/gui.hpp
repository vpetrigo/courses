#ifndef MAILRU_COURSE_GUI_HPP
#define MAILRU_COURSE_GUI_HPP

// FLTK headers
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <memory>
#include <string>
#include <vector>

namespace downloader {
class Widget {
  // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
 public:
  Widget(Point xy, int w, int h, const string& s, Callback cb)
      : loc(xy), width(w), height(h), label(s), do_it(cb) {}

  virtual void move(int dx, int dy) {
    hide();
    pw->position(loc.x += dx, loc.y += dy);
    show();
  }

  Widget& operator=(const Widget&) = delete;
  Widget(const Widget&) = delete;

  virtual void hide() { pw->hide(); }
  virtual void show() { pw->show(); }
  virtual void attach(Window&) = 0;

  Point loc;
  int width;
  int height;
  string label;
  Callback do_it;

  virtual ~Widget() {}

 protected:
  // every Widget belongs to a Window
  Window* own;
  // connection to the FLTK Widget
  Fl_Widget* pw;
};

class Window : public Fl_Window {
 public:
  // let the system pick the location:
  Window(int w, int h, const std::string& title);

  virtual ~Window() = default

      int x_max() const {
    return width_;
  }
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
