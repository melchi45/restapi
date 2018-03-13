/*******************************************************************************
 *  Copyright (c) 2016 Hanwha Techwin Co., Ltd.
 *
 *  Licensed to the Hanwha Techwin Software Foundation under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Smart Home Camera - Hanwha B2C Action Cam Project
 *  http://www.samsungsmartcam.com
 *
 *  Security Solution Division / Camera S/W Development Team
 *  Home Security Camera SW Dev. Group
 *
 *  @file
 *  Contains implementation of logging tools.
 *
 *  $Author$
 *  $LastChangedBy$
 *  $Date$
 *  $Revision$
 *  $Id$
 *  $HeadURL$
 *******************************************************************************

  MODULE NAME:

  REVISION HISTORY:

  Date        Ver Name                    Description
  ----------  --- --------------------- -----------------------------------------
  07-Jun-2016 0.1 Youngho Kim             Created
 ...............................................................................

  DESCRIPTION:


 ...............................................................................
 *******************************************************************************/

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread
{
public:
	Thread();
	virtual ~Thread();

    // Create the thread and start work
    // Note 1
    int start();
    int stop(); // Note 2
    bool is_running();
private:
    volatile bool m_stoprequested; // Note 5
    volatile bool m_running;
    pthread_mutex_t m_mutex; // Variable declarations added 4/14/2010
    pthread_t m_thread;

    // This is the static class function that serves as a C style function pointer
    // for the pthread_create call
    static void* start_thread(void *obj);

    // Compute and save fibonacci numbers as fast as possible
    void do_work();
    void display_pthread_attr(pthread_attr_t *attr);
protected:
	pthread_attr_t m_thread_attr;
	const char *title;

protected:
    virtual void* run(void) = 0;

    // referene url
    // https://apiexamples.com/c/pthread/pthread_attr_init.html
    virtual int set_pthread_attr();
    void display_current_attr();
};

#endif /* THREAD_H_ */
