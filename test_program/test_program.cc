#include "base/strings/string16.h"
#include "tgk/core/SkColor.h"
#include "tgk/gfx/canvas.h"
#include "twk/base/event_loop/event_loop.h"
#include "twk/views/widget/widget.h"
#include "twk/views/widget/widget_delegate.h"
#include "twk/views/view.h"
#include "twk/views/background.h"
#include "twk/views/controls/styled_label.h"

#include "twk/views/controls/textfield/textfield.h"

class TestStyleView : public views::WidgetDelegateView {
 public:
  TestStyleView() {
    setFocusable(true);
    printf("create TestView %d\n", test_id_);
  }

  ~TestStyleView() override {
    printf("delete TestView %d\n",test_id_);
  }

  void onPaint(gfx::Canvas* canvas) override {
    canvas->fillRect(getLocalBounds(), SK_ColorCYAN);
  }

  virtual bool onMousePressed(const ui::MouseEvent& event) override {
    requestFocus();
    return true;
  }

  virtual void onBlur() override {
    printf("On Blur!!!\n");
  }

  int test_id_;
};

class PopupView : public views::WidgetDelegateView {
public:

  virtual bool onMousePressed(const ui::MouseEvent& event) override {
//    requestFocus();
//    return true;
    return true;
  }

  void onPaint(gfx::Canvas* canvas) override {
    canvas->fillRect(getLocalBounds(), SK_ColorYELLOW);
  }

};

void CreatePopupHostView(views::Widget* parent, gfx::Rect bounds) {
	views::Widget* widget = new views::Widget;
  views::Widget::InitParams params(views::Widget::InitParams::TYPE_WINDOW_FRAMELESS);
//  views::Widget::InitParams params(views::Widget::InitParams::TYPE_POPUP);
  PopupView* popup_webview = new PopupView();
  params.delegate = popup_webview;
  params.bounds = bounds;
  params.ownership = views::Widget::InitParams::NATIVE_WIDGET_OWNS_WIDGET;
  params.opacity = views::Widget::InitParams::TRANSLUCENT_WINDOW;
  params.shadow_type = views::Widget::InitParams::SHADOW_TYPE_NONE;
  params.child = true;
  params.owner = parent;
  widget->Init(params);
  widget->show();

//  return make_scoped_ptr(new PopupHostView(this, popup_webview));
}

int main(int argc, const char** argv) {
  views::Widget* widget_ = new views::Widget();
  views::Widget::InitParams params(views::Widget::InitParams::TYPE_WINDOW);
  views::WidgetDelegateView* widget_delegate_view = new TestStyleView();


  base::string16 custom_title;
//  std::wstring custom_title_std = L"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 가 나 다 라 마 바 사";
//  std::wstring custom_title_std = L"ToGate이(가) 이 사이트에서 비밀번호를 저장하도록 하시겠습니까?";
  std::wstring custom_title_std = L"ToGate 이(가) http://ims.tmaxsoft.com의 비밀번호를 저장하도록 하시겠습니까?";
  custom_title.assign(custom_title_std.begin(), custom_title_std.end());

  views::StyledLabel* title_label = new views::StyledLabel(custom_title, nullptr);
  title_label->setBounds(0, 0, 240, 80);
  title_label->set_background(views::Background::CreateSolidBackground(150, 150, 150));

//  widget_delegate_view->set_background(views::Background::CreateSolidBackground(0, 0, 200));
  widget_delegate_view->addChildView(title_label);
  widget_delegate_view->setBounds(0, 0, 240, 80);

  views::Textfield* text_field = new views::Textfield();
  text_field->setBounds(0, 0, 100, 100);
  widget_delegate_view->addChildView(text_field);


  params.delegate = widget_delegate_view;
  widget_->Init(params);
  widget_->setBounds(gfx::Rect(0,0,400,400));
  widget_->show();

  gfx::Rect popup_bounds(100, 100, 50, 50);
  CreatePopupHostView(widget_, popup_bounds);

  EventLoop *loop = EventLoop::GetEventLoop();
  loop->run();

  return 0;
}
