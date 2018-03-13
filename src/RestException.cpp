/*******************************************************************************
 *  Copyright (c) 2013 Samsung Techwin Co., Ltd.
 *  
 *  Licensed to the Samsung Techwin Software Foundation under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Samsung SmartCam - SmartCam Camera Proejct
 *  http://www.samsungsmartcam.com
 *  
 *  Security Solution Division / B2C Camera S/W Development Team
 *
 *  $Author$
 *  $Date$
 *  $Revision$
 *  $Id$
 *  $HeadURL$
 *
 *  History 
 *    RestException.cpp
 *
 *  Created on: Nov 15, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#include "RestException.h"

namespace rest {

RestException::RestException(int status_code)
: m_StatusCode(status_code)
{
	// TODO Auto-generated constructor stub
}

RestException::~RestException() {
	// TODO Auto-generated destructor stub
}

} /* namespace rest */ //end of rest
