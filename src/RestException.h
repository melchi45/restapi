/*******************************************************************************
*  Copyright (c) 1998 MFC Forum
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Module Name:
*
* Revision History:
*
* Date        Ver Name                    Description
* ----------  --- --------------------- -----------------------------------------
* 07-Jun-2016 0.1 Youngho Kim             Created
* ----------  --- --------------------- -----------------------------------------
*
* DESCRIPTION:
*
*  $Author:
*  $LastChangedBy:
*  $Date:
*  $Revision: 2949 $
*  $Id:
*  $HeadURL:
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
