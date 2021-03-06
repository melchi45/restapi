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
#include "Put.h"

namespace rest {


Put::Put(cpr::Url url, cpr::Header header, cpr::Body body)
: RestBase(url, header)
, m_body(body)
{
	// TODO Auto-generated constructor stub

}

Put::Put(cpr::Url url, cpr::Header header)
: RestBase(url, header)
{
	// TODO Auto-generated constructor stub

}

Put::~Put() {
	// TODO Auto-generated destructor stub
}


bool Put::setResponse(const cpr::Response& r) throw (RestException, RestExceptionExt)
{
	bool parsingRet = ResponseBase::setResponse(r);


    if(this->is_running()) {
//    	resume();
//    	stop();
    }

    return parsingRet;
}

int Put::status_callback_ref(int& status_code, const cpr::Response& r)
{
    getInstance()->setResponse(r);
//    Post::m_status_code = r.status_code;
//    trigger();
//    pause();
   // dispatchEvent(*this);

    return r.status_code;
}

void* Put::run(void)
{
	if (!this->is_running()) {
		log_debug("Post::run");

		int m_status_code = 0;
		auto callback = std::function<int(cpr::Response)>(std::bind(Put::status_callback_ref,
			std::ref(m_status_code),
			std::placeholders::_1));

		log_debug("url: %s", m_url.c_str());
		std::map<std::string, std::string>::iterator it = m_header.begin();
		for (; it != m_header.end(); it++) {
			log_debug("Headers : \"%s\" : \"%s\"", it->first.c_str(), it->second.c_str());
		}
		log_debug("m_body: %s", m_body.c_str());

		auto future = cpr::PutCallback(callback, m_url, m_header, m_body);
	}
	return NULL;
}

} /* namespace rest */ //end of rest
