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
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <json/json.h>

#include "RestBase.h"
#include "log_utils.h"

#if (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#endif

namespace rest {

RestBase::RestBase(cpr::Url url, cpr::Header header)
: m_url(url)
, m_header(header)
//, m_status_code(0)
{
	// TODO Auto-generated constructor stub
//	addListener(this);
}

RestBase::~RestBase() {
	// TODO Auto-generated destructor stub
//	removeListener(this);
}

void RestBase::setUri(std::string uri)
{
	m_url = cpr::Url(m_base_url + "/" + uri);
}

int RestBase::setAuthorizationToken(std::string token)
{
	Json::Reader reader;
	Json::FastWriter fastWriter;
	Json::Value root;
//	bool parsingRet;

	std::map<std::string, std::string>::iterator it = m_header.begin();
	for(; it != m_header.end(); it++) {
		if(it->first.compare("AuthorizationToken") == 0) {
			it->second = token;
		}
	}

	it = m_header.begin();
	for(; it != m_header.end(); it++) {
		log_debug ("Headers : \"%s\" : \"%s\"", it->first.c_str(), it->second.c_str());
	}

	return 0;
}

int RestBase::send() throw (RestException, RestExceptionExt)
{
    log_debug("start run");

	if (start() == 0) {
#if (!(defined(_WIN32) || defined(_WIN64)))
		usleep(1000);
#else
		Sleep(1000);
#endif

		if (this->is_running()) {
			if (stop() < 0) {
				log_error("fail to stop RestBase::send");
			}
		}
	}

	return 0;
}

} /* namespace rest */ //end of rest
