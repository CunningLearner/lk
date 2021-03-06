/*
 * Copyright (c) 2015 Brian Swetland
 * Copyright (c) 2008 Google, Inc.
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

#define GET_STATUS           0
#define CLEAR_FEATURE        1
#define SET_FEATURE          3
#define SET_ADDRESS          5
#define GET_DESCRIPTOR       6
#define SET_DESCRIPTOR       7
#define GET_CONFIGURATION    8
#define SET_CONFIGURATION    9
#define GET_INTERFACE        10
#define SET_INTERFACE        11
#define SYNCH_FRAME          12
#define SET_SEL              48

#define TYPE_DEVICE          1
#define TYPE_CONFIGURATION   2
#define TYPE_STRING          3
#define TYPE_INTERFACE       4
#define TYPE_ENDPOINT        5
#define TYPE_BOS             15
#define TYPE_DEVICE_CAP      16
#define TYPE_SS_EP_COMP      48

#define DEVICE_READ          0x80
#define DEVICE_WRITE         0x00
#define INTERFACE_READ       0x81
#define INTERFACE_WRITE      0x01
#define ENDPOINT_READ        0x82
#define ENDPOINT_WRITE       0x02

typedef struct udc_descriptor udc_descriptor_t;

union setup_packet {
    struct {
        uint8_t type;
        uint8_t request;
        uint16_t value;
        uint16_t index;
        uint16_t length;
    };
    struct {
        uint32_t w0;
        uint32_t w1;
    };
} __attribute__ ((packed));

struct udc_descriptor {
    udc_descriptor_t *next;
    uint16_t tag; /* ((TYPE << 8) | NUM) */
    uint16_t len; /* total length */
    uint8_t data[4];
};

// driver calls this to build descriptors from device and gadgets
void udc_create_descriptors(udc_device_t *device, udc_gadget_t *gadget);

// driver uses this to obtain descriptors
udc_descriptor_t *udc_descriptor_find(unsigned tag);

// driver provides this
void udc_ept_desc_fill(udc_endpoint_t *ept, unsigned char *data);

