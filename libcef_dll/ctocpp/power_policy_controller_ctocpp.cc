// Copyright (c) 2020 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=a7437168189f476e39f2bc7c41748b1eca0c8c0d$
//

#include "libcef_dll/ctocpp/power_policy_controller_ctocpp.h"
#include "libcef_dll/shutdown_checker.h"

// VIRTUAL METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
int CefPowerPolicyControllerCToCpp::AddSystemWakeLock(
    WakeLockReason reason,
    const CefString& description) {
  shutdown_checker::AssertNotShutdown();

  cef_power_policy_controller_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_system_wake_lock))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: description; type: string_byref_const
  DCHECK(!description.empty());
  if (description.empty())
    return 0;

  // Execute
  int _retval =
      _struct->add_system_wake_lock(_struct, reason, description.GetStruct());

  // Return type: simple
  return _retval;
}

NO_SANITIZE("cfi-icall")
int CefPowerPolicyControllerCToCpp::AddScreenWakeLock(
    WakeLockReason reason,
    const CefString& description) {
  shutdown_checker::AssertNotShutdown();

  cef_power_policy_controller_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_screen_wake_lock))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: description; type: string_byref_const
  DCHECK(!description.empty());
  if (description.empty())
    return 0;

  // Execute
  int _retval =
      _struct->add_screen_wake_lock(_struct, reason, description.GetStruct());

  // Return type: simple
  return _retval;
}

NO_SANITIZE("cfi-icall")
int CefPowerPolicyControllerCToCpp::AddDimWakeLock(
    WakeLockReason reason,
    const CefString& description) {
  shutdown_checker::AssertNotShutdown();

  cef_power_policy_controller_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_dim_wake_lock))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: description; type: string_byref_const
  DCHECK(!description.empty());
  if (description.empty())
    return 0;

  // Execute
  int _retval =
      _struct->add_dim_wake_lock(_struct, reason, description.GetStruct());

  // Return type: simple
  return _retval;
}

NO_SANITIZE("cfi-icall")
void CefPowerPolicyControllerCToCpp::RemoveWakeLock(int block_id) {
  shutdown_checker::AssertNotShutdown();

  cef_power_policy_controller_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, remove_wake_lock))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->remove_wake_lock(_struct, block_id);
}

// CONSTRUCTOR - Do not edit by hand.

CefPowerPolicyControllerCToCpp::CefPowerPolicyControllerCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

CefPowerPolicyControllerCToCpp::~CefPowerPolicyControllerCToCpp() {
  shutdown_checker::AssertNotShutdown();
}

template <>
cef_power_policy_controller_t* CefCToCppRefCounted<
    CefPowerPolicyControllerCToCpp,
    CefPowerPolicyController,
    cef_power_policy_controller_t>::UnwrapDerived(CefWrapperType type,
                                                  CefPowerPolicyController* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType
    CefCToCppRefCounted<CefPowerPolicyControllerCToCpp,
                        CefPowerPolicyController,
                        cef_power_policy_controller_t>::kWrapperType =
        WT_POWER_POLICY_CONTROLLER;