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
#ifndef REST_RESTBASE_H_
#define REST_RESTBASE_H_

#include <cpr/cpr.h>

#include "Thread.h"

#include "RestException.h"
#include "RestExceptionExt.h"

#include "log_utils.h"

namespace rest {

/*
 *
 */
class RestBase: public Thread/*, public event::Listener */ {
public:
	RestBase(cpr::Url url, cpr::Header header);
	virtual ~RestBase();

protected:
    cpr::Url m_url;
    cpr::Header m_header;
    std::string m_base_url;

private:
	int16_t request_count;

protected:
    virtual void* run(void);

public:
    int setAuthorizationToken(std::string token);
    void setURL(cpr::Url url) { m_url = url; }
    void setHeader(cpr::Header header) { m_header = header; }
    void setBaseURL(std::string base_url) { m_base_url = base_url; }
    void setUri(std::string uri);
	int16_t getRequestCount() { return request_count; }
    virtual int send() throw (RestException, RestExceptionExt);
};

} /* namespace rest */ //end of rest

#endif /* REST_RESTBASE_H_ */
