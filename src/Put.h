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
 *    Put.h
 *
 *  Created on: Nov 10, 2016
 *      Author: Youngho Kim
 *******************************************************************************/

#ifndef REST_PUT_H_
#define REST_PUT_H_

#include "RestBase.h"
#include "ResponseBase.h"

namespace rest {

/*
 *
 */
class Put : public RestBase, public ResponseBase {
public:
	Put(cpr::Url url, cpr::Header header, cpr::Body body);
	Put(cpr::Url url, cpr::Header header);
	virtual ~Put();
protected:
	cpr::Body m_body;

public:
	void setBody(cpr::Body body) { m_body = body; }
	static int status_callback_ref(int& status_code, const cpr::Response& r);
	virtual bool setResponse(const cpr::Response& r) throw (RestException, PixcamException);

protected:
    virtual void* run(void);
};

} /* namespace rest */ //end of rest

#endif /* REST_PUT_H_ */
