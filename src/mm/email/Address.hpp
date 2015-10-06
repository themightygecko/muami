/*
 * MELKONIAN Marc
 * IED 13410425
 * Address.hpp: An envelope address as described in the RFC 3501
 *
 * Doc: https://tools.ietf.org/html/rfc3501#section-9
 *
 * Grammar:
 * --------
 *
 *    address      = "(" addr-name SP addr-adl SP addr-mailbox SP
 *                   addr-host ")"
 *
 *    addr-adl     = nstring
 *                     ; Holds route from [RFC-2822] route-addr if
 *                     ; non-NIL
 *
 *    addr-host    = nstring
 *                     ; NIL indicates [RFC-2822] group syntax.
 *                     ; Otherwise, holds [RFC-2822] domain name
 *
 *    addr-mailbox = nstring
 *                     ; NIL indicates end of [RFC-2822] group; if
 *                     ; non-NIL and addr-host is NIL, holds
 *                     ; [RFC-2822] group name.
 *                     ; Otherwise, holds [RFC-2822] local-part
 *                     ; after removing [RFC-2822] quoting
 *
 *    addr-name    = nstring
 *                     ; If non-NIL, holds phrase from [RFC-2822]
 *                     ; mailbox after removing [RFC-2822] quoting
 */

#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "../utils/util.hpp"
#include "../debug/debug.hpp"

using namespace std;

class Address
{
    private:
        string addr_adl;
        string addr_host;
        string addr_mailbox;
        string addr_name;

    public:
        Address() {};
        ~Address() {};

        // Setters
        void set_adl(const string& adl);
        void set_host(const string& host);
        void set_mailbox(const string& mailbox);
        void set_name(const string& name);

        // Getters
        string adl();
        string host();
        string mailbox();
        string name();

        // DEBUG
        void dump();
};

istream& operator>>(istream& is, Address* a);

#endif /* end of include guard: ADDRESS_H */
