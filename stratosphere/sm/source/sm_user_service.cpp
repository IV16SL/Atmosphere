/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <switch.h>
#include <stratosphere.hpp>

#include "sm_user_service.hpp"
#include "sm_service_manager.hpp"

namespace sts { namespace sm {

    Result UserService::Initialize(PidDescriptor pid) {
        this->pid = pid.pid;
        this->has_initialized = true;
        return ResultSuccess;
    }

    Result UserService::EnsureInitialized() {
        if (!this->has_initialized) {
            return ResultSmInvalidClient;
        }
        return ResultSuccess;
    }

    Result UserService::GetService(Out<MovedHandle> out_h, ServiceName service) {
        R_TRY(this->EnsureInitialized());
        return sm::GetServiceHandle(out_h.GetHandlePointer(), this->pid, service);
    }

    Result UserService::RegisterService(Out<MovedHandle> out_h, ServiceName service, u32 max_sessions, bool is_light) {
        R_TRY(this->EnsureInitialized());
        return sm::RegisterService(out_h.GetHandlePointer(), this->pid, service, max_sessions, is_light);
    }

    Result UserService::UnregisterService(ServiceName service) {
        R_TRY(this->EnsureInitialized());
        return sm::UnregisterService(this->pid, service);
    }

    Result UserService::AtmosphereInstallMitm(Out<MovedHandle> srv_h, Out<MovedHandle> qry_h, ServiceName service) {
        R_TRY(this->EnsureInitialized());
        return sm::InstallMitm(srv_h.GetHandlePointer(), qry_h.GetHandlePointer(), this->pid, service);
    }

    Result UserService::AtmosphereUninstallMitm(ServiceName service) {
        R_TRY(this->EnsureInitialized());
        return sm::UninstallMitm(this->pid, service);
    }

    Result UserService::AtmosphereAcknowledgeMitmSession(Out<u64> client_pid, Out<MovedHandle> fwd_h, ServiceName service) {
        R_TRY(this->EnsureInitialized());
        return sm::AcknowledgeMitmSession(client_pid.GetPointer(), fwd_h.GetHandlePointer(), this->pid, service);
    }

    Result UserService::AtmosphereAssociatePidTidForMitm(u64 pid, u64 tid) {
        R_TRY(this->EnsureInitialized());
        return sm::AssociatePidTidForMitm(pid, tid);
    }

}}
