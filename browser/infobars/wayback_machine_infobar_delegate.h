// Copyright (c) 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_INFOBARS_WAYBACK_MACHINE_INFOBAR_DELEGATE_H_
#define BRAVE_BROWSER_INFOBARS_WAYBACK_MACHINE_INFOBAR_DELEGATE_H_

#include <string>

#include "base/functional/callback.h"
#include "base/timer/timer.h"
#include "brave/components/brave_wayback_machine/wayback_snapshot_info.h"
#include "brave/components/infobars/core/brave_confirm_infobar_delegate.h"

namespace content {
class WebContents;
}

// Delegate for the infobar shown when an automatic check finds a snapshot of a
// missing page. Counts down and then loads the snapshot.
class WaybackMachineInfoBarDelegate : public BraveConfirmInfoBarDelegate {
 public:
  // Adds the infobar for |snapshot_info| to |contents|, unless one is already
  // showing.
  static void Create(content::WebContents* contents,
                     const WaybackSnapshotInfo& snapshot_info);

  // Asynchronously removes the infobar from |contents|, if it is showing.
  static void Remove(content::WebContents* contents);

  WaybackMachineInfoBarDelegate(const WaybackMachineInfoBarDelegate&) = delete;
  WaybackMachineInfoBarDelegate& operator=(
      const WaybackMachineInfoBarDelegate&) = delete;
  ~WaybackMachineInfoBarDelegate() override;

  // The number of seconds counted down before the snapshot is loaded.
  static constexpr int kCountdownSeconds = 5;

  // Returns the snapshot this infobar is about to load.
  const WaybackSnapshotInfo& snapshot_info() const { return snapshot_info_; }

  // Returns the number of seconds until the snapshot is loaded.
  int seconds_remaining() const { return seconds_remaining_; }

  // Sets a callback that is run whenever |seconds_remaining()| decreases.
  void SetCountdownChangedCallback(base::RepeatingClosure callback);

  // Fires once per second of the countdown.
  base::OneShotTimer& countdown_timer_for_testing() { return countdown_timer_; }

  // BraveConfirmInfoBarDelegate:
  InfoBarIdentifier GetIdentifier() const override;
  ui::ImageModel GetIcon() const override;
  bool EqualsDelegate(infobars::InfoBarDelegate* delegate) const override;
  bool IsCloseable() const override;
  std::u16string GetMessageText() const override;
  std::u16string GetButtonLabel(InfoBarButton button) const override;
  bool Accept() override;
  bool ShouldSupportMultiLine() const override;

 private:
  explicit WaybackMachineInfoBarDelegate(
      const WaybackSnapshotInfo& snapshot_info);

  void StartCountdownTimer();
  void OnCountdownTick();
  void NavigateToSnapshot();

  const WaybackSnapshotInfo snapshot_info_;
  int seconds_remaining_ = kCountdownSeconds;
  base::OneShotTimer countdown_timer_;
  base::RepeatingClosure countdown_changed_callback_;
};

#endif  // BRAVE_BROWSER_INFOBARS_WAYBACK_MACHINE_INFOBAR_DELEGATE_H_
