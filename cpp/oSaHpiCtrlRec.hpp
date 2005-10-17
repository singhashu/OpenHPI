/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2005
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Author(s):
 *    W. David Ashley <dashley@us.ibm.com>
 */


#ifndef Included_oSaHpiCtrlRec
#define Included_oSaHpiCtrlRec

#include <stdio.h>
extern "C"
{
#include <SaHpi.h>
}


class oSaHpiCtrlRec : public SaHpiCtrlRecT {
    public:
        // constructors
        oSaHpiCtrlRec();
        // copy constructor
        oSaHpiCtrlRec(const oSaHpiCtrlRec& cr);
        // destructor
        ~oSaHpiCtrlRec() {
        }
        // other methods
        bool assignField(SaHpiCtrlRecT *ptr,
                         const char *field,
                         const char *value);
        inline bool assignField(const char *field,
                                const char *value) {
            return assignField(this, field, value);
        }
        inline SaHpiCtrlRecT *getStruct(void) {
            return this;
        }
        bool fprint(FILE *stream,
                    const int indent,
                    const SaHpiCtrlRecT *sr);
        inline bool fprint(FILE *stream,
                           const int indent) {
            return fprint(stream, indent, this);
        }
};

#endif

