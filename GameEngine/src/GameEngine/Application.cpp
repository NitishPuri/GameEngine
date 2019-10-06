#include "gepch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace GE {

  Application::Application()
  {
  }


  Application::~Application()
  {
  }

  void Application::Run()
  {
    WindowResizeEvent e(1280, 720);
    if (e.IsInCategory(EventCategoryApplication)) {
      GE_TRACE(e);
    }
    if (e.IsInCategory(EventCategoryInput)) {
      GE_TRACE(e);
    }
    
    while (true);
  }

}
