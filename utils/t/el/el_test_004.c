/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2004
 * Copyright (c) 2004 by Intel Corp.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *      Christina Hernandez<hernanc@us.ibm.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include <SaHpi.h>
#include <openhpi.h>
#include <oh_utils.h>


#include "el_test.h"


/**
 * main: EL test
 *
 * This test creates an EL and adds five events.
 * It then verifies there are five entries in the EL and
 * that the events are the same as the initial events.
 *
 * Return value: 0 on success, 1 on failure
 **/
int main(int argc, char **argv)
{
        oh_el *el, *el2;
        int x;
        SaErrorT retc;
	SaHpiEventT event;
	static char *data[5] = {
        	"Test data one",
        	"Test data two",
        	"Test data three",
        	"Test data four",
        	"Test data five"
	};

        /* create the EL */
        el = oh_el_create(30);

	el2 = oh_el_create(30);

	/* add 5 events to el */
	for(x=0;x<5;x++){
        	event.Source = 1;
        	event.EventType = SAHPI_ET_USER;
        	event.Timestamp = SAHPI_TIME_UNSPECIFIED;
        	event.Severity = SAHPI_DEBUG;
		strcpy((char *) &event.EventDataUnion.UserEvent.UserEventData.Data, data[x]);


        	retc = oh_el_append(el, &event, NULL, NULL);
        	if (retc != SA_OK) {
              	dbg("ERROR: oh_el_append failed.");
               	return 1;
        	}       
	}

       /* save the EL to file */
        retc = oh_el_map_to_file(el, "./elTest.data");
        if (retc != SA_OK) {
                dbg("ERROR: oh_el_map_to_file failed.");
                return 1;
        }

        /* get EL from file (el2) */
        retc = oh_el_map_from_file(el2, "./elTest.data");
	if (retc != SA_OK) {
                dbg("ERROR: oh_el_map_from_file failed.");
                return 1;
        }


        if(g_list_length(el->list) != g_list_length(el2->list)) {
                 dbg("ERROR: el->list != el2->list.");
                 return 1;
         }


        /* close the el */
        retc = oh_el_close(el);
        if (retc != SA_OK) {
                dbg("ERROR: oh_el_close failed.");
                return 1;
        }


        return 0;
}

