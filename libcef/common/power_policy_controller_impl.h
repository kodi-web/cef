// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_LIBCEF_COMMON_POWER_POLICY_CONTROLLER_H_
#define CEF_LIBCEF_COMMON_POWER_POLICY_CONTROLLER_H_
#pragma once

#include "services/device/public/mojom/wake_lock.mojom.h"
#include <memory>

class CefPowerPolicyControllerImpl {
public:
  CefPowerPolicyControllerImpl();
  ~CefPowerPolicyControllerImpl();

  // Returns the singleton CefPowerPolicyControllerImpl instance.
  static std::shared_ptr<CefPowerPolicyControllerImpl> Get();

  int AddSystemWakeLock(device::mojom::WakeLockReason reason, const std::string& description);
  int AddScreenWakeLock(device::mojom::WakeLockReason reason, const std::string& description);
  int AddDimWakeLock(device::mojom::WakeLockReason reason, const std::string& description);
  void RemoveWakeLock(int block_id);
};

#endif  // CEF_LIBCEF_COMMON_POWER_POLICY_CONTROLLER_H_
