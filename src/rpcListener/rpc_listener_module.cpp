/* 
 * Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Bertand HIGY
 * email:  bertrand.higy@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include "rpc_listener_module.h"

using namespace std;
using namespace yarp::os;

bool RpcListenerModule::configure(ResourceFinder &rf)
{    
	module_name_ = rf.check("name", Value("rpcListener"), "Module name (string)").asString();
	setName(module_name_.c_str());

	// get the name of the input and output ports, automatically prefixing the module name by using getName()
	input_rpc_port_name_ = "/";
	input_rpc_port_name_ += getName(rf.check("input_rpc_port", Value("/input_rpc:io"), "Input rpc port (string)").asString());
	output_rpc_port_name_ = "/";
	output_rpc_port_name_ += getName(rf.check("output_rpc_port", Value("/output_rpc:io"), "Output rpc port (string)").asString());
	event_port_name_ = "/";
	event_port_name_ += getName(rf.check("event_port", Value("/events:o"), "Event port (string)").asString());
	
	// open ports
	if (!input_rpc_port_.open(input_rpc_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << input_rpc_port_name_ << endl;
		return false;
	}
	if (!output_rpc_port_.open(output_rpc_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << output_rpc_port_name_ << endl;
		return false;
	}
	if (!event_port_.open(event_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << event_port_name_ << endl;
		return false;
	}

   	// create the thread and pass pointers to the module parameters
	thread_ = new RpcListenerThread(&input_rpc_port_, &output_rpc_port_, &event_port_);
	// now start the thread to do the work
	thread_->start(); // this calls threadInit() and it if returns true, it then calls run()

   	return true ;
}

bool RpcListenerModule::updateModule()
{
	return true;
}

bool RpcListenerModule::interruptModule()
{
	input_rpc_port_.interrupt();
	output_rpc_port_.interrupt();
	event_port_.interrupt();
	return true;
}

bool RpcListenerModule::close()
{
	/* stop the thread */
	thread_->stop();

	input_rpc_port_.close();
	output_rpc_port_.close();
	event_port_.close();
	return true;
}

