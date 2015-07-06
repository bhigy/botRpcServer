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

#include <cstdlib>

#include <yarp/os/Bottle.h>
#include <yarp/os/Time.h>

#include "rpc_listener_thread.h"

using namespace std;
using namespace yarp::os;

RpcListenerThread::RpcListenerThread(RpcServer *input_rpc_port, RpcClient *output_rpc_port,  Port *event_port)
	: input_rpc_port_(input_rpc_port), output_rpc_port_(output_rpc_port), event_port_(event_port)
{
}

void RpcListenerThread::run()
{
	while (!isStopping())
	{
		Bottle request, reply, event;
				
		// Reading request
		cout << "Waiting for a message..." << endl;
		input_rpc_port_->read(request, true);
		cout << "Message: " << request.toString() << endl;
		event.addString("request");
		event.append(request);
		event_port_->write(event);
		
		// Transmitting the request
		output_rpc_port_->write(request, reply);

		// Writing the reply
		cout << "Reply: >>" << reply.toString() << endl;
		event.clear();
		event.addString("reply");
		event.append(reply);
		event_port_->write(event);
		input_rpc_port_->reply(reply);
	}
}
