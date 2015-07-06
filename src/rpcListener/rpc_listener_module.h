#ifndef RPC_LISTENER_MODULE_H
#define RPC_LISTENER_MODULE_H

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

#include <yarp/os/ResourceFinder.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/RFModule.h>

#include "rpc_listener_thread.h"

class RpcListenerModule: public yarp::os::RFModule
{
	public:
	   
	   bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
	   bool interruptModule();                       // interrupt, e.g., the ports 
	   bool close();                                 // close and shut down the module
	   bool respond();
	   bool updateModule();
	   
   private:
	   /* module parameters */
	   std::string 	module_name_;
	   std::string 	input_rpc_port_name_;
	   std::string 	output_rpc_port_name_;
	   std::string 	event_port_name_;
	 
	   /* class variables */
	   yarp::os::RpcServer 	input_rpc_port_;
	   yarp::os::RpcClient 	output_rpc_port_;
	   yarp::os::Port		event_port_;
	   RpcListenerThread	*thread_;
};

#endif
