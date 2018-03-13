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
 *    Rest.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#ifndef REST_RESTBASE_H_
#define REST_RESTBASE_H_

#include <cpr/cpr.h>

#include "task/Thread.h"
#include "event/EventDispatcher.h"
#include "event/Listener.h"

#include "RestException.h"
#include "PixcamException.h"

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

protected:
    virtual void* run(void) = 0;

public:
    int setAuthorizationToken(std::string token);
    void setURL(cpr::Url url) { m_url = url; }
    void setHeader(cpr::Header header) { m_header = header; }
    void setBaseURL(std::string base_url) { m_base_url = base_url; }
    void setUri(std::string uri);
    virtual int send() throw (RestException, PixcamException);
};

} /* namespace rest */ //end of rest

#endif /* REST_RESTBASE_H_ */
