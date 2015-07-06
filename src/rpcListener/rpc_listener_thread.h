#ifndef RPC_LISTENER_THREAD_H
#define RPC_LISTENER_THREAD_H

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

#include <yarp/os/RpcClient.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/Thread.h>
  
class RpcListenerThread : public yarp::os::Thread
{
	public:
		RpcListenerThread(yarp::os::RpcServer *input_rpc_port, yarp::os::RpcClient *output_rpc_port,  yarp::os::Port *event_port);   
		void run(); 
	   
	protected:
		/* thread parameters */
		yarp::os::RpcServer *input_rpc_port_;
		yarp::os::RpcClient *output_rpc_port_;
		yarp::os::Port 		*event_port_;
};

#endif
