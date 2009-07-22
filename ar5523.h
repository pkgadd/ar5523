/*	$OpenBSD: if_ar5523reg.h,v 1.2 2006/09/18 16:34:23 damien Exp $	*/

/*-
 * Copyright (c) 2006
 *	Damien Bergamini <damien.bergamini@free.fr>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define AR5523_CONFIG_NO		1
#define AR5523_IFACE_INDEX	0

/* all fields are big endian */
struct ar5523_fwblock {
	__be32		flags;
#define AR5523_WRITE_BLOCK	(1 << 4)

	__be32	len;
#define AR5523_MAX_FWBLOCK_SIZE	2048

	__be32		total;
	__be32		remain;
	__be32		rxtotal;
	__be32		pad[123];
};

#define AR5523_MAX_RXCMDSZ	512
#define AR5523_MAX_TXCMDSZ	512

struct ar5523_cmd_hdr {
	__be32		len;
	__be32		code;
#define AR5523_CMD_SETUP		0x01
#define AR5523_CMD_02		0x02
#define AR5523_CMD_READ_MAC	0x03
#define AR5523_CMD_WRITE_MAC	0x04
#define AR5523_CMD_READ_EEPROM	0x05
#define AR5523_CMD_STATS		0x06
#define AR5523_CMD_07		0x07
#define AR5523_CMD_SHUTDOWN	0x08
#define AR5523_CMD_0B		0x0b
#define AR5523_CMD_0C		0x0c
#define AR5523_CMD_0F		0x0f
#define AR5523_NOTIF_STATS	0x10
#define AR5523_NOTIF_READY	0x12
#define AR5523_NOTIF_TX		0x13
#define AR5523_CMD_15		0x15
#define AR5523_CMD_SET_LED	0x17
#define AR5523_CMD_SET_XLED	0x18
#define AR5523_CMD_1B		0x1b
#define AR5523_CMD_1E		0x1e
#define AR5523_CMD_CRYPTO		0x1d
#define AR5523_CMD_SET_STATE	0x20
#define AR5523_CMD_SET_BSSID	0x21
#define AR5523_CMD_24		0x24
#define AR5523_CMD_SET_RATES	0x26
#define AR5523_CMD_27		0x27
#define AR5523_CMD_2E		0x2e
#define AR5523_CMD_31		0x31
#define AR5523_CMD_SET_FILTER	0x32
#define AR5523_CMD_SET_CHAN	0x34
#define AR5523_CMD_RESET		0x35
#define AR5523_CMD_SET_QUEUE	0x3a
#define AR5523_CMD_RESET_QUEUE	0x3b

	__u32		priv;	/* driver private data,
				   don't care about endianess */
	__be32		magic;
	__be32		reserved2[4];
};

struct ar5523_rx_desc {
	__be32		len;
	__be32		reserved1[8];
	__be32		rssi;
	__be32		freq;
	__be32		reserved2[5];
};

#define AR5523_MAKECTL(qid, len)	cpu_to_be32((qid) << 16 | (len))

struct ar5523_tx_desc {
	__be32		len;
	__u32		priv;	/* driver private data
				   don't care about endianess */
	__be32		type;
#define AR5523_TX_DATA	0xe
#define AR5523_TX_NULL	0xf

	__be32		magic;
	__be32		dest;
#define AR5523_ID_BSS		2
#define AR5523_ID_BROADCAST	0xffffffff

	__be32		flags;
#define AR5523_TX_NOTIFY	(1 << 24)	/* f/w will send a AR5523_NOTIF_TX */

	__be32		paylen;
};

/* structure for command AR5523_CMD_SETUP */
struct ar5523_cmd_setup {
	__be32		magic1;
	__be32		magic2;
	__be32		magic3;
	__be32		magic4;
};

/* structure for commands AR5523_CMD_READ_MAC and AR5523_CMD_READ_EEPROM */
struct ar5523_read_mac {
	__be32		len;
	__u8		data[32];
};

/* structure for command AR5523_CMD_WRITE_MAC */
struct ar5523_write_mac {
	__be32		reg;
	__be32		len;
	__u8		data[32];
};

/* structure for command AR5523_CMD_0B */
struct ar5523_cmd_0b {
	__be32		code;
	__be32		reserved;
	__be32		size;
	__u8		data[44];
};

/* structure for command AR5523_CMD_0C */
struct ar5523_cmd_0c {
	__be32		magic1;
	__be32		magic2;
	__be32		magic3;
};

/* structure for command AR5523_CMD_SET_LED */
struct ar5523_cmd_led {
	__be32		which;
#define AR5523_LED_LINK		0
#define AR5523_LED_ACTIVITY	1

	__be32		state;
#define AR5523_LED_OFF	0
#define AR5523_LED_ON	1
};

/* structure for command AR5523_CMD_SET_XLED */
struct ar5523_cmd_xled {
	__be32		which;
	__be32		rate;
	__be32		mode;
};


/* structure for command AR5523_CMD_CRYPTO */
struct ar5523_cmd_crypto {
	__be32		keyidx;
#define AR5523_DEFAULT_KEY	6

	__be32		magic1;
	__be32		size;
	__be32		reserved1;
	__be32		mask;
#define AR5523_ADDR_LEN		6		/* size of 802.11 address */
	__u8		addr[AR5523_ADDR_LEN];
	__be16		reserved2;
	__be32		flags;
	__be32		reserved3[2];
	__u8		key[68];
	__u8		magic2[136];
	__u8		magic3[136];
};

/* structure for command AR5523_CMD_SET_RATES */
struct ar5523_cmd_rates {
	__be32		magic1;
	__be32		reserved;
	__be32		size;
	__u8		nrates;
#define AR5523_MAX_NRATES	30
	__u8		rates[AR5523_MAX_NRATES];
};

/* structure for command AR5523_CMD_SET_CHAN */
struct ar5523_set_chan {
	__be32		flags;
	__be32		freq;
	__be32		magic1;
	__be32		magic2;
	__be32		reserved1;
	__be32		magic3;
	__be32		reserved2;
};

/* structure for command AR5523_CMD_SET_QUEUE */
struct ar5523_qinfo {
	__be32		qid;
#define AR5523_AC_TO_QID(ac)	(ac)	/* id function */

	__be32		size;
	__be32		ac;
	__be32		aifsn;
	__be32		logcwmin;
	__be32		logcwmax;
	__be32		txop;
	__be32		acm;
	__be32		magic1;
	__be32		magic2;
};

/* structure for command AR5523_CMD_31 */
struct ar5523_cmd_31 {
	__be32		magic1;
	__be32		magic2;
};

/* structure for command AR5523_CMD_SET_FILTER */
struct ar5523_cmd_filter {
	__be32		filter;
	__be32		flags;
};

/* structure for command AR5523_CMD_SET_BSSID */
struct ar5523_cmd_bssid {
	__be32		reserved1;
	__be32		flags1;
	__be32		flags2;
	__be32		reserved2;
	__be32		len;
	__u8		bssid[AR5523_ADDR_LEN];
};


#define AR5523_EEPROM_MACADDR	0x0b
#define AR5523_EEPROM_RXBUFSZ	0x0f

#define AR5523_MAX_TXBUFSZ	\
	(sizeof(__be32) + sizeof(struct ar5523_tx_desc) + IEEE80211_MAX_LEN)

/* this is in net/ieee80211.h, but that conflicts with the mac80211 headers */
#define IEEE80211_2ADDR_LEN	16

/* from OpenBSD */
#define IEEE80211_WEP_IVLEN			3	/* 24bit */
#define IEEE80211_WEP_KIDLEN			1	/* 1 octet */
#define IEEE80211_WEP_CRCLEN			4	/* CRC-32 */
#define IEEE80211_CRC_LEN			4
#define IEEE80211_MAX_LEN \
	(2300 + IEEE80211_CRC_LEN + \
	 (IEEE80211_WEP_IVLEN + IEEE80211_WEP_KIDLEN + IEEE80211_WEP_CRCLEN))

#define AR5523_MIN_RXBUFSZ				\
	(((sizeof(__be32) + IEEE80211_2ADDR_LEN +	\
	   sizeof(struct ar5523_rx_desc)) + 3) & ~3)
