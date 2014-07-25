/****************************************************************************
 *
 *   Copyright (C) 2014 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file gnss_receiver.hpp
 *
 * UAVCAN --> ORB bridge for GNSS messages:
 *     uavcan.equipment.gnss.Fix
 *
 * @author Pavel Kirienko <pavel.kirienko@gmail.com>
 * @author Andrew Chambers <achamber@gmail.com>
 */

#pragma once

#include <drivers/drv_hrt.h>

#include <uORB/uORB.h>
#include <uORB/topics/vehicle_gps_position.h>

#include <uavcan/uavcan.hpp>
#include <uavcan/equipment/gnss/Fix.hpp>

class UavcanGnssReceiver
{
public:
	UavcanGnssReceiver(uavcan::INode& node);

	int init();

private:
	/**
	 * GNSS fix message will be reported via this callback.
	 */
	void gnss_fix_sub_cb(const uavcan::ReceivedDataStructure<uavcan::equipment::gnss::Fix> &msg);


	typedef uavcan::MethodBinder<UavcanGnssReceiver*,
		void (UavcanGnssReceiver::*)(const uavcan::ReceivedDataStructure<uavcan::equipment::gnss::Fix>&)>
		FixCbBinder;

	/*
	 * libuavcan related things
	 */
	uavcan::INode													&_node;
	uavcan::Subscriber<uavcan::equipment::gnss::Fix, FixCbBinder>	_uavcan_sub_status;

	/*
	 * uORB
	 */
	struct vehicle_gps_position_s 	_report;					///< uORB topic for gnss position
	orb_advert_t			_report_pub;					///< uORB pub for gnss position

};
