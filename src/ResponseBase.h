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
 *    ResponseBase.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#ifndef REST_RESPONSEBASE_H_
#define REST_RESPONSEBASE_H_

#include <json/json.h>
#include <cpr/cpr.h>
#include "event/EventDispatcher.h"
#include "RestException.h"
#include "PixcamException.h"

namespace rest {

const char * const vHeader     				= "header";
const char * const vData     				= "data";
const char * const vResultCode				= "resultCode";
const char * const vResultMessage			= "resultMessage";

/*
 *
 */
class ResponseBase : public event::EventDispatcher {
public:
	ResponseBase();
	virtual ~ResponseBase();

protected:
	cpr::Response m_response;
	Json::Value m_root;
//	Json::Value m_response_data;
//	Json::Value m_response_header;

	static ResponseBase* m_Instance;

public:
	virtual bool setResponse(const cpr::Response& res) throw (RestException, PixcamException);
	int getResponseStatusCode();
	int getResultCode();
	std::string getResultMessage();

	static ResponseBase* getInstance();
};

} /* namespace rest */ //end of rest

#endif /* REST_RESPONSEBASE_H_ */
