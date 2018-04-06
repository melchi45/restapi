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
#ifndef REST_EXCEPTION_EXT_H_
#define REST_EXCEPTION_EXT_H_

#include "RestException.h"

namespace rest {

/*
 *
 */
class RestExceptionExt {
public:
	RestExceptionExt(int resultCode, std::string resultMessage);
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
		stringStream << ",\nResult Code: " << m_resultCode << "\nResult Message: " << m_resultMessage;
		std::string copyOfStr = stringStream.str();

		return copyOfStr.c_str();
	}
};

} /* namespace rest */ //end of rest

#endif /* REST_EXCEPTION_EXT_H_ */
