#ifndef EMAIL_H
#define EMAIL_H

#include "flags.hpp"
#include "RFC822_header.hpp"
#include "Body.hpp"
#include "Envelope.hpp"
#include "../debug/debug.hpp"

using namespace std;

class Email
{
    private:
        unsigned long em_uid;
        unsigned long em_rfc822_size;
        unsigned char em_flags;
        string em_friendly_time;
        string em_internaldate;
        Envelope em_envelope;
        RFC822_header* em_rfc822_header;

    public:
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // !!!!!! TO MAKE PRIVATE !!!!!!!!!!!!!!!!!!!!!!!!!!!
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        Body* body;

        Email(): em_envelope() { body = new Body(); };
        ~Email() { delete body; };

        // Setters
        void set_uid(unsigned long u);
        void set_rfc822_size(unsigned long sz);
        void set_flags(unsigned int fl);
        void set_friendly_time(const string& time);
        void set_internaldate(const string& date);
        void set_envelope(const Envelope& env);
        void set_rfc822_header(RFC822_header* const hdr);

        // Getters
        unsigned long uid();
        unsigned long rfc822_size();
        unsigned int flags();
        string& friendly_time();
        string& internaldate();
        Envelope& envelope();
        RFC822_header* rfc822_header();

        // DEBUG
        void dump();
};

#endif /* end of include guard: EMAIL_H */
