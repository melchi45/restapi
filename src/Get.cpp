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
#include "Get.h"

namespace rest {

Get::Get(cpr::Url url, cpr::Header header)
: RestBase(url, header)
{
	// TODO Auto-generated constructor stub

}

Get::~Get() {
	// TODO Auto-generated destructor stub
}


bool Get::setResponse(const cpr::Response& res) throw (RestException, RestExceptionExt)
{
	bool parsingRet = ResponseBase::setResponse(res);

//    log_info("Response Code: %d", r.status_code);
//    log_info("Response: %s", r.text.c_str());

    if(this->is_running()) {
//    	resume();
//    	stop();
    }

    return parsingRet;
}

cpr::Response Get::status_callback_ref(int& status_code, const cpr::Response& res)
{
	try {
		getInstance()->setResponse(res);
//    Post::m_status_code = r.status_code;
//    trigger();
//    pause();
   // dispatchEvent(*this);
	} catch (rest::RestExceptionExt& e) {
		log_error("%s", e.what());
	} catch (std::exception& e) {

	}

    return res;
}

void* Get::run(void)
{
	log_info("Get::run");

	int m_status_code = 0;
	auto callback = std::function<cpr::Response(cpr::Response)>(std::bind(Get::status_callback_ref,
			std::ref(m_status_code),
			std::placeholders::_1));

	log_debug("url: %s", m_url.c_str());
	std::map<std::string, std::string>::iterator it = m_header.begin();
	for(; it != m_header.end(); it++) {
		log_debug ("Headers : \"%s\" : \"%s\"", it->first.c_str(), it->second.c_str());
	}

	auto future = cpr::GetCallback(callback, m_url, m_header, cpr::Timeout{1000});
	m_response = future.get();

	return NULL;
}

int Get::send() throw (RestException, RestExceptionExt)
{
	int rtn = RestBase::send();

	if(getResponseStatusCode() != 200)
		throw (RestException(getResponseStatusCode()));

	if(getResultCode() != 0 )
		throw (RestExceptionExt(getResponseStatusCode(), getResultCode(), getResultMessage()));

	return rtn;
}

} /* namespace rest */ //end of rest
