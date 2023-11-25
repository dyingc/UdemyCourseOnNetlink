/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  This file contains common routines and definitions to be used in kernel and user space
 *
 *        Version:  1.0
 *        Created:  11/22/2019 12:16:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Er. Abhishek Sagar, Juniper Networks (https://csepracticals.wixsite.com/csepracticals), sachinites@gmail.com
 *        Company:  Juniper Networks
 *
 *        This file is part of the Netlink Sockets Course distribution (https://github.com/sachinites) 
 *        Copyright (c) 2019 Abhishek Sagar.
 *        This program is free software: you can redistribute it and/or modify it under the terms of the GNU General 
 *        Public License as published by the Free Software Foundation, version 3.
 *        
 *        This program is distributed in the hope that it will be useful, but
 *        WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *        General Public License for more details.
 *
 *        visit website : https://csepracticals.wixsite.com/csepracticals for more courses and projects
 *                                  
 * =====================================================================================
 */

#ifndef __NL_COMMON__
#define __NL_COMMON__

#include <linux/netlink.h>

/* maximum payload size in Bytes exchanged between kernel and userspace
 * in either directions*/
#define MAX_PAYLOAD 1024

/*User defined NL MSG TYPES, should be > 16 */
#define NLMSG_GREET     20

/* user define netlink protocol.
 * It should match with Netlink Socket protocol opened in kernel space.*/

/* Define a New Netlink protocol ID
 * In file linux/netlink.h, you can see in line no [8-33]
 * lists the reserved IDs used for Netlink protocols already implemented
 * in Linux. We can use upto max 31th protocol number for Netlink. Let
 * us just pick the unused one - 31 below */

#define NETLINK_TEST_PROTOCOL   31

static inline char *
netlink_get_msg_type(__u16 nlmsg_type){

    switch(nlmsg_type){
        case NLMSG_NOOP:
            return "NLMSG_NOOP";
        case NLMSG_ERROR:
            return "NLMSG_ERROR";
        case NLMSG_DONE:
            return "NLMSG_DONE";
        case NLMSG_OVERRUN:
            return "NLMSG_OVERRUN";
        case NLMSG_GREET:
            return "NLMSG_GREET";
        default:
            return "NLMSG_UNKNOWN";
    }
}

/*static inline void
nlmsg_dump(struct nlmsghdr *nlh){
#ifdef __KERNEL__
    printk(KERN_INFO "Dumping Netlink Msgs Hdr");
#else
    printf("Dumping Netlink Msgs Hdr");
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg Type = %s", 
        netlink_get_msg_type(nlh->nlmsg_type));
#else
    printf("  Netlink Msg Type = %s",
        netlink_get_msg_type(nlh->nlmsg_type));
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg len  = %d", nlh->nlmsg_len);
#else
    printf("  Netlink Msg len  = %d", nlh->nlmsg_len);
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg flags  = %d", nlh->nlmsg_flags);
#else
    printf("  Netlink Msg flags  = %d", nlh->nlmsg_flags);
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg Seq#  = %d", nlh->nlmsg_seq);
#else
    printf("  Netlink Msg Seq#  = %d", nlh->nlmsg_seq);
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg Pid#  = %d", nlh->nlmsg_pid);
#else
    printf("  Netlink Msg Pid#  = %d", nlh->nlmsg_pid);
#endif
}*/

//static inline char* nlmsg_type_to_name(__u16 nlmsg_type);
static inline void nlmsg_flags_to_names(__u16 nlmsg_flags, char *flag_str);

static inline void
nlmsg_dump(struct nlmsghdr *nlh){
    if (!nlh)
        return;

    char flag_str[256]; // Ensure this is large enough for all flag names

    nlmsg_flags_to_names(nlh->nlmsg_flags, flag_str);
#ifdef __KERNEL__
    printk(KERN_INFO " Length of message including header: %u\n", nlh->nlmsg_len);
    printk(KERN_INFO " Message content: %u (%s)\n", nlh->nlmsg_type, netlink_get_msg_type(nlh->nlmsg_type));
    printk(KERN_INFO " Message content: %u (%s)\n", nlh->nlmsg_type, netlink_get_msg_type(nlh->nlmsg_type));
    printk(KERN_INFO " Additional flags: 0x%04x (%s)\n", nlh->nlmsg_flags, flag_str);
    printk(KERN_INFO " Sequence number: %u\n", nlh->nlmsg_seq);
    printk(KERN_INFO " Sending process port ID: %u\n", nlh->nlmsg_pid);
#else
    printk(" Length of message including header: %u\n", nlh->nlmsg_len);
    printk(" Message content: %u (%s)\n", nlh->nlmsg_type, netlink_get_msg_type(nlh->nlmsg_type));
    printk(" Additional flags: 0x%04x (%s)\n", nlh->nlmsg_flags, flag_str);
    printk(" Sequence number: %u\n", nlh->nlmsg_seq);
    printk(" Sending process port ID: %u\n", nlh->nlmsg_pid);
#endif
}

/*static inline char* nlmsg_type_to_name(__u16 nlmsg_type) {
    switch (nlmsg_type) {
        case NLMSG_NOOP:
            return "NLMSG_NOOP";
        case NLMSG_ERROR:
            return "NLMSG_ERROR";
        case NLMSG_DONE:
            return "NLMSG_DONE";
        case NLMSG_OVERRUN:
            return "NLMSG_OVERRUN";
        case NLMSG_GREET:
            return "NLMSG_GREET";
        default:
            return "NLMSG_UNDEFINED";
    }
}*/

static inline void nlmsg_flags_to_names(__u16 flags, char *flag_str) {
    flag_str[0] = '\0'; // Initialize the string

    if (flags & NLM_F_REQUEST)
        strcat(flag_str, "NLM_F_REQUEST ");
    if (flags & NLM_F_MULTI)
        strcat(flag_str, "NLM_F_MULTI ");
    if (flags & NLM_F_ACK)
        strcat(flag_str, "NLM_F_ACK ");
    if (flags & NLM_F_ECHO)
        strcat(flag_str, "NLM_F_ECHO ");
    if (flags & NLM_F_DUMP_INTR)
        strcat(flag_str, "NLM_F_DUMP_INTR ");
    if (flags & NLM_F_DUMP_FILTERED)
        strcat(flag_str, "NLM_F_DUMP_FILTERED ");
    if (flags & NLM_F_ROOT)
        strcat(flag_str, "NLM_F_ROOT ");
    if (flags & NLM_F_MATCH)
        strcat(flag_str, "NLM_F_MATCH ");
    if (flags & NLM_F_ATOMIC)
        strcat(flag_str, "NLM_F_ATOMIC ");
    if (flags & NLM_F_DUMP)
        strcat(flag_str, "NLM_F_DUMP ");
    if (flags & NLM_F_REPLACE)
        strcat(flag_str, "NLM_F_REPLACE ");
    if (flags & NLM_F_EXCL)
        strcat(flag_str, "NLM_F_EXCL ");
    if (flags & NLM_F_CREATE)
        strcat(flag_str, "NLM_F_CREATE ");
    if (flags & NLM_F_APPEND)
        strcat(flag_str, "NLM_F_APPEND ");
    if (flags & NLM_F_NONREC)
        strcat(flag_str, "NLM_F_NONREC ");
    if (flags & NLM_F_CAPPED)
        strcat(flag_str, "NLM_F_CAPPED ");
    if (flags & NLM_F_ACK_TLVS)
        strcat(flag_str, "NLM_F_ACK_TLVS ");

    if (flag_str[0] == '\0') // No flag was set
        strcat(flag_str, "NONE");
}

#endif /* __NL_COMMON__ */
