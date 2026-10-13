// Copyright (c) 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/views/infobars/wayback_machine_infobar.h"

#include <memory>
#include <utility>

#include "base/functional/bind.h"
#include "brave/browser/infobars/wayback_machine_infobar_creator.h"
#include "brave/browser/infobars/wayback_machine_infobar_delegate.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/views/controls/label.h"

std::unique_ptr<infobars::InfoBar> CreateWaybackMachineInfoBar(
    std::unique_ptr<WaybackMachineInfoBarDelegate> delegate) {
  return std::make_unique<WaybackMachineInfoBar>(std::move(delegate));
}

WaybackMachineInfoBar::WaybackMachineInfoBar(
    std::unique_ptr<WaybackMachineInfoBarDelegate> delegate)
    : BraveConfirmInfoBar(std::move(delegate)) {
  // Unretained() is safe because this infobar owns the delegate.
  static_cast<WaybackMachineInfoBarDelegate*>(GetDelegate())
      ->SetCountdownChangedCallback(base::BindRepeating(
          &WaybackMachineInfoBar::OnCountdownChanged, base::Unretained(this)));
}

WaybackMachineInfoBar::~WaybackMachineInfoBar() = default;

void WaybackMachineInfoBar::OnCountdownChanged() {
  label_->SetText(GetDelegate()->GetMessageText());
  InvalidateLayout();
}

BEGIN_METADATA(WaybackMachineInfoBar)
END_METADATA
