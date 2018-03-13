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
 *    Rest.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: Youngho Kim
 *******************************************************************************/
#include <unistd.h>
#include <json/json.h>

#include "RestBase.h"
#include "log/log_utils.h"

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

int RestBase::send() throw (RestException, PixcamException)
{
    log_debug("start run");

	if (start() == 0) {
		usleep(1000);

		if (this->is_running()) {
			if (stop() < 0) {
				log_error("fail to stop RestBase::send");
			}
		}
	}

	return 0;
}

} /* namespace rest */ //end of rest
