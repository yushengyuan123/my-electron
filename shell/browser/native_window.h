// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_H_

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/supports_user_data.h"
#include "content/public/browser/web_contents_user_data.h"
#include "extensions/browser/app_window/size_constraints.h"
#include "shell/browser/native_window_observer.h"
#include "ui/views/widget/widget_delegate.h"

namespace gin_helper {
class Dictionary;
}  // namespace gin_helper

namespace electron {
  class NativeWindow : public base::SupportsUserData, public views::WidgetDelegate {
    private:
      // Observers of this window.
      base::ObserverList<NativeWindowObserver> observers_;

      views::View* content_view_ = nullptr;

      // Minimum and maximum size, stored as content size.
      extensions::SizeConstraints size_constraints_;

      // Whether window has standard frame.
      bool has_frame_ = true;

    public:
      ~NativeWindow() override;

      // disable copy
      NativeWindow(const NativeWindow&) = delete;
      NativeWindow& operator=(const NativeWindow&) = delete;

      static NativeWindow* Create(const gin_helper::Dictionary& options,
                                NativeWindow* parent = nullptr);

      // virtual void Show() = 0;

      virtual extensions::SizeConstraints GetSizeConstraints() const;

      virtual extensions::SizeConstraints GetContentSizeConstraints() const;

      virtual gfx::Size GetMaximumSize() const;

      // Converts between content bounds and window bounds.
      virtual gfx::Rect ContentBoundsToWindowBounds(
            const gfx::Rect& bounds) const = 0;

      virtual gfx::Size GetMinimumSize() const;

      void NotifyWindowShow();

      bool has_frame() const { return has_frame_; }

      virtual void SetContentView(views::View* view) = 0;

      virtual gfx::NativeWindow GetNativeWindow() const = 0;

      views::Widget* widget() const { return widget_.get(); }
      views::View* content_view() const { return content_view_; }

      void AddObserver(NativeWindowObserver* obs) { observers_.AddObserver(obs); }

      void RemoveObserver(NativeWindowObserver* obs) {
        observers_.RemoveObserver(obs);
      }

    protected:
      std::unique_ptr<views::Widget> widget_;

      NativeWindow(const gin_helper::Dictionary& options, NativeWindow* parent);

      void set_content_view(views::View* view) { content_view_ = view; }

  };
}




#endif