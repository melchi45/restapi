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
#include "RestExceptionExt.h"
#include "log_utils.h"

namespace rest {

RestExceptionExt::RestExceptionExt(int resultCode, std::string resultMessage)
: m_resultCode(resultCode)
, m_resultMessage(resultMessage)
{
	// TODO Auto-generated constructor stub
	log_error("http result code: %d, return code: %d, error message: %s", resultCode, resultMessage.c_str());
}

RestExceptionExt::~RestExceptionExt() {
	// TODO Auto-generated destructor stub
}

} /* namespace rest */ //end of rest
