// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "power_policy_controller_impl.h"
#include "cef/include/cef_power_policy_controller.h"

#include "libcef/common/app_manager.h"

namespace {

// Converts a mojom::WakeLockReason to a
// cef_wake_lock_reason_t.
CefPowerPolicyController::WakeLockReason GetWakeLockReason(
    device::mojom::WakeLockReason reason) {
  switch (reason) {
    case device::mojom::WakeLockReason::kAudioPlayback:
      return CEF_AUDIOPLAYBACK;
    case device::mojom::WakeLockReason::kVideoPlayback:
      return CEF_VIDEOPLAYBACK;
    case device::mojom::WakeLockReason::kOther:
      return CEF_OTHER;
  }
  return CEF_OTHER;
}

}  // namespace

CefPowerPolicyControllerImpl::CefPowerPolicyControllerImpl() {

}

CefPowerPolicyControllerImpl::~CefPowerPolicyControllerImpl() {

}

// Returns the singleton CefPowerPolicyControllerImpl instance.
std::shared_ptr<CefPowerPolicyControllerImpl> CefPowerPolicyControllerImpl::Get() {
  static std::shared_ptr<CefPowerPolicyControllerImpl> powerPolicyController(
      new CefPowerPolicyControllerImpl);
  return powerPolicyController;
}

int CefPowerPolicyControllerImpl::AddSystemWakeLock(device::mojom::WakeLockReason reason,
                                                    const std::string& description)
{
  CefRefPtr<CefPowerPolicyController> controller;
  CefRefPtr<CefApp> application = CefAppManager::Get()->GetApplication();
  if (application)
    controller = application->GetPowerPolicyController();
  if (!controller)
    return 0;
  return controller->AddSystemWakeLock(GetWakeLockReason(reason),
                                       description);
}

int CefPowerPolicyControllerImpl::AddScreenWakeLock(device::mojom::WakeLockReason reason,
                                                    const std::string& description)
{
  CefRefPtr<CefPowerPolicyController> controller;
  CefRefPtr<CefApp> application = CefAppManager::Get()->GetApplication();
  if (application)
    controller = application->GetPowerPolicyController();
  if (!controller)
    return 0;
  return controller->AddScreenWakeLock(GetWakeLockReason(reason),
                                       description);
}

int CefPowerPolicyControllerImpl::AddDimWakeLock(device::mojom::WakeLockReason reason,
                                                 const std::string& description)
{
  CefRefPtr<CefPowerPolicyController> controller;
  CefRefPtr<CefApp> application = CefAppManager::Get()->GetApplication();
  if (application)
    controller = application->GetPowerPolicyController();
  if (!controller)
    return 0;
  return controller->AddDimWakeLock(GetWakeLockReason(reason),
                                    description);
}

void CefPowerPolicyControllerImpl::RemoveWakeLock(int block_id)
{
  CefRefPtr<CefPowerPolicyController> controller;
  CefRefPtr<CefApp> application = CefAppManager::Get()->GetApplication();
  if (application)
    controller = application->GetPowerPolicyController();
  if (!controller)
    return;
  controller->RemoveWakeLock(block_id);
}
