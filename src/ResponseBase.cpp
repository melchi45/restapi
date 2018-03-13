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
 *    ResponseBase.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#include "ResponseBase.h"
#include "PixcamException.h"

#include "log/log_utils.h"

namespace rest {

ResponseBase* ResponseBase::m_Instance = NULL;

ResponseBase::ResponseBase()
{
	// TODO Auto-generated constructor stub
	ResponseBase::m_Instance = this;
}

ResponseBase::~ResponseBase() {
	// TODO Auto-generated destructor stub
}

ResponseBase* ResponseBase::getInstance()
{
	return ResponseBase::m_Instance;
}

bool ResponseBase::setResponse(const cpr::Response& res) throw (RestException, PixcamException)
{
	bool parsingRet = false;
	m_response = res;

	if(m_response.status_code == 200) {
		Json::Reader reader;

		log_debug("response status code: %d", m_response.status_code);
		log_debug("response text: %s", m_response.text.c_str());

	    parsingRet = reader.parse(m_response.text, m_root);

	    if(m_response.status_code != 200) {
	    	log_error("Failed to request code: %d", m_response.status_code);

	    	throw RestException(m_response.status_code);
	    }

		if (!parsingRet) {
			log_error("Failed to parse Json : %s", reader.getFormattedErrorMessages().c_str());
			return parsingRet;
		}

	    if(getResultCode() != 0) {
	    	// Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
	    	// such member.
	    	std::string encoding = m_root.get("encoding", "UTF-8" ).asString();

	    	log_error("Result Code: %d", m_root[vHeader].get(vResultCode,"").asInt());
	    	log_error("Result Message: %s", m_root[vHeader].get(vResultMessage,"").asString().c_str());

			throw (PixcamException(m_response.status_code,
					m_root[vHeader].get(vResultCode, "").asInt(),
					m_root[vHeader].get(vResultMessage, "").asString()));
	    }
	}

	return parsingRet;
}

int ResponseBase::getResponseStatusCode()
{
	return m_response.status_code;
}

int ResponseBase::getResultCode()
{
	return m_root[vHeader].get(vResultCode,0).asInt();
}

std::string ResponseBase::getResultMessage()
{
	return m_root[vHeader].get(vResultMessage,"").asString();
}


/*
void ResponseBase::setResponse(const cpr::Response& r)
{
    log_info("Response Code: %d", r.status_code);
    log_info("Response: %s", r.text.c_str());

    m_response = r;
}
*/

} /* namespace rest */ //end of rest
