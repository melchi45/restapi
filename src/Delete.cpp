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
#include "Delete.h"

namespace rest {

Delete::Delete(cpr::Url url, cpr::Header header, cpr::Body body)
: RestBase(url, header)
, m_body(body)
{
	// TODO Auto-generated constructor stub
//	this->addListener(this);
}

Delete::Delete(cpr::Url url, cpr::Header header)
: RestBase(url, header)
{
	// TODO Auto-generated constructor stub
//	this->removeListener(this);
}

Delete::~Delete() {
	// TODO Auto-generated destructor stub
}


bool Delete::setResponse(const cpr::Response& r) throw (RestException, RestExceptionExt)
{
	bool parsingRet = ResponseBase::setResponse(r);

//    log_info("Response Code: %d", r.status_code);
//    log_info("Response: %s", r.text.c_str());

    if(this->is_running()) {
//    	resume();
//    	stop();
    }

    return parsingRet;
}

cpr::Response Delete::status_callback_ref(int& status_code, const cpr::Response& r)
{
	try {
		getInstance()->setResponse(r);
//    Post::m_status_code = r.status_code;
//    trigger();
//    pause();
   // dispatchEvent(*this);

		//this->dispatchEvent();
	} catch (rest::RestException& e) {
		log_error("%s", e.what());
	} catch (std::exception& e) {

	}

    return r;
}

void* Delete::run(void)
{
	if (!this->is_running()) {
		log_debug("Delete::run");

		int m_status_code = 0;
		auto callback = std::function<cpr::Response(cpr::Response)>(std::bind(Delete::status_callback_ref,
			std::ref(m_status_code),
			std::placeholders::_1));

		log_debug("url: %s", m_url.c_str());
		std::map<std::string, std::string>::iterator it = m_header.begin();
		for (; it != m_header.end(); it++) {
			log_debug("Headers : \"%s\" : \"%s\"", it->first.c_str(), it->second.c_str());
		}
		log_debug("m_body: %s", m_body.c_str());

		auto future = cpr::DeleteCallback(callback, m_url, m_header, m_body, cpr::Timeout{ 1000 });
		m_response = future.get();
	}
	return NULL;
}

int Delete::send() throw (RestException, RestExceptionExt)
{
	int rtn = RestBase::send();

	if(getResponseStatusCode() != 200)
		throw (RestException(getResponseStatusCode()));

	return rtn;
}

} /* namespace rest */ //end of rest
