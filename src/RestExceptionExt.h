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
 *    RestExceptionExt.h
 *
 *  Created on: Nov 15, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#ifndef REST_EXCEPTION_EXT_H_
#define REST_EXCEPTION_EXT_H_

#include "RestException.h"

namespace rest {

/*
 *
 */
class RestExceptionExt : public RestException {
public:
	RestExceptionExt(int status_code, int resultCode, std::string resultMessage);
	virtual ~RestExceptionExt();

protected:
	int m_resultCode;
	std::string m_resultMessage;

public:
	int ResultCode() { return m_resultCode; }
	std::string ResultMessage() { return m_resultMessage; }

	virtual const char* what() const throw()
	{
		std::ostringstream stringStream;
		stringStream << "\nStatus Code: " << m_StatusCode << ",\nResult Code: " << m_resultCode << "\nResult Message: " << m_resultMessage;
		std::string copyOfStr = stringStream.str();

		return copyOfStr.c_str();
	}
};

} /* namespace rest */ //end of rest

#endif /* REST_EXCEPTION_EXT_H_ */
