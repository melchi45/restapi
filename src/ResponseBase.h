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
#ifndef REST_RESPONSEBASE_H_
#define REST_RESPONSEBASE_H_

#include <json/json.h>
#include <cpr/cpr.h>
//#include "event/EventDispatcher.h"
#include "RestException.h"
#include "RestExceptionExt.h"

#include "log_utils.h"

namespace rest {

//const char * const vHeader     				= "header";
//const char * const vData     				= "data";
//const char * const vResultCode				= "resultCode";
//const char * const vResultMessage			= "resultMessage";

/*
 *
 */
class ResponseBase/* : public event::EventDispatcher */{
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
	virtual bool setResponse(const cpr::Response& res) throw (RestException, RestExceptionExt);
	int getResponseStatusCode();

	static ResponseBase* getInstance();
};

} /* namespace rest */ //end of rest

#endif /* REST_RESPONSEBASE_H_ */
