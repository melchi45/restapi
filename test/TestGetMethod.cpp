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
#include "TestGetMethod.h"

#include "log_utils.h"

namespace rest {

const char * const vContent		= "content";
const char * const vTitle		= "title";

TestGetMethod::TestGetMethod()
: Get(cpr::Url{"http://echo.jsontest.com/title/ipsum/content/blah"},
	  cpr::Header{{"AuthorizationToken",""}})
{
	// TODO Auto-generated constructor stub

}

TestGetMethod::~TestGetMethod() {
	// TODO Auto-generated destructor stub
}

const char* TestGetMethod::getContent()
{
	return m_root.get(vContent, "UTF-8").asString().c_str();
}

const char* TestGetMethod::getTitle()
{
	return m_root.get(vTitle, "UTF-8").asString().c_str();
}

bool TestGetMethod::setResponse(const cpr::Response& res) throw (RestException, RestExceptionExt)
{
	bool parsingRet = Get::setResponse(res);

    if(parsingRet) {
		log_debug("content: %s", m_root.get(vContent,"UTF-8").asString().c_str());
    	log_debug("title: %s", m_root.get(vTitle,"UTF-8").asString().c_str());
    }

	if (m_root.get(vContent, "UTF-8").asString().c_str() != NULL)
		throw (RestExceptionExt(ErrorType::JSON_PARSING_ERROR, std::string("Error Message")));

    return parsingRet;
}

} /* namespace rest */ //end of rest
