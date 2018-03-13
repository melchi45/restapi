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
 *    RestException.h
 *
 *  Created on: Nov 15, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#ifndef REST_RESTEXCEPTION_H_
#define REST_RESTEXCEPTION_H_

#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream
#include <exception>
#include <stdexcept>

namespace rest {

/*
 *
 */
class RestException : public std::exception {
public:
	explicit RestException(int status_code);
	virtual ~RestException();

protected:
	int m_StatusCode;

public:
	virtual const int StatusCode() const throw () {
		return m_StatusCode;
	}

	virtual const char* what() const throw()
	{
		std::ostringstream stringStream;
		stringStream << "Status Code: " << m_StatusCode;
		std::string copyOfStr = stringStream.str();

		return copyOfStr.c_str();
	}
};

} /* namespace rest */ //end of rest

#endif /* REST_RESTEXCEPTION_H_ */
