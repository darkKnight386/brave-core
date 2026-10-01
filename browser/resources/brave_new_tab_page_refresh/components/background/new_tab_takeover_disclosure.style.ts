/* Copyright (c) 2026 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { color, font } from '@brave/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

import { sponsoredLogoWidth } from './background_caption.style'

export const style = scoped.css`
  .new-tab-takeover-disclosure {
    color: ${color.white};
    font: ${font.xSmall.regular};
    letter-spacing: -0.08px;
    text-shadow: 0px 1px 2px ${color.elevation.secondary},
      0px 1px 3px ${color.elevation.secondary};
    white-space: nowrap;
  }

  /* Gives the trigger the same width as the sponsored logo, so the label
     text can be centered under the logo while the tooltip (which floats
     relative to this element's edges, not the centered text) still lines
     up with the logo's left edge. */
  .new-tab-takeover-disclosure.align-with-logo {
    display: block;
    width: ${sponsoredLogoWidth}px;
    text-align: center;
  }

  .new-tab-takeover-disclosure-tooltip {
    font: ${font.small.regular};
    letter-spacing: -0.08px;

    /* 391px per the Figma spec is the overall tooltip width, which already
       includes the host's 16px of padding (--leo-tooltip-padding) on each
       side, so the slotted content's own max-width needs to be narrower. */
    max-width: 359px;

    a {
      color: inherit;
    }
  }

  /* Collapses the tooltip's shadow-DOM bubble, which stays visible even
     when the text inside it is hidden. */
  :scope:has(:popover-open) {
    --leo-tooltip-background: transparent;
    --leo-tooltip-padding: 0;
    --leo-tooltip-shadow: none;
  }

  :scope:has(:popover-open) .new-tab-takeover-disclosure-tooltip {
    display: none;
  }
`
