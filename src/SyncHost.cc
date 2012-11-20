//------------------------------------------------------------------------------
// Copyright (c) 2011-2012 by European Organization for Nuclear Research (CERN)
// Author: Justin Salmon <jsalmon@cern.ch>
//------------------------------------------------------------------------------
// XRootD is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// XRootD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with XRootD.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <sys/time.h>
#include <iostream>
#include <xrootd/XrdCl/XrdClStatus.hh>
#include <xrootd/XrdSys/XrdSysPthread.hh>

#include "SyncHost.hh"
#include "XrdCl/XrdClFileSystem.hh"

SyncHost::SyncHost(XrdSysCondVar *cv) {
    this->cv = cv;
}

SyncHost::~SyncHost() {
}

void* SyncHost::DoStat(XrdCl::URL *url, std::string *statpath) {
    XrdCl::XRootDStatus status;
    XrdCl::FileSystem fs(*url);

    Host::Init();
    
    status = fs.Stat(*statpath, statinfo, 5);
    gettimeofday(&resptime, NULL);

    if (status.IsError()) Disable();
    this->status = status;
    done = true;
}

