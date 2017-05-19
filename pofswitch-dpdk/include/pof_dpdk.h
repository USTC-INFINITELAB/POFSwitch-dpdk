#ifndef _POF_DPDK_H_
#define _POF_DPDK_H_

//add the headers you need
#include <stdint.h>
#include <inttypes.h>
#include <linux/if_ether.h>
#include <sys/socket.h>
#include <rte_config.h>
#include <rte_eal.h>
#include <rte_dev.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_prefetch.h>

#include "../include/pof_common.h"
#include "../include/pof_type.h"
#include "../include/pof_global.h"
#include "../include/pof_local_resource.h"
#include "../include/pof_log_print.h"
#include "../include/pof_conn.h"
#include "../include/pof_datapath.h"
#include "../include/pof_byte_transfer.h"
#include "../include/pof_hmap.h"
#include "../include/pof_memory.h"

//declare your functions or any others here;
#define RX_RING_SIZE 128
#define TX_RING_SIZE 512

#define NUM_MBUFS 8191
#define MBUF_SIZE (1600 + sizeof(struct rte_mbuf) + RTE_PKTMBUF_HEADROOM)
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 1
//#define BURST_SIZE 32
static const struct rte_eth_conf port_conf_default = {
	.rxmode = { .max_rx_pkt_len = ETHER_MAX_LEN }
};

static struct rte_mempool *mbuf_pool;
static struct rte_mbuf *tx_bufs[BURST_SIZE];

static inline int port_init(uint8_t port, struct rte_mempool *mbuf_pool);

uint32_t pof_dpdk_port_listen(struct pof_local_resource *lr);

//uint32_t pof_dpdk_port_listen(struct portInfo *port);

static uint32_t dpdk_recv_raw_task(void *arg_lr);

uint32_t dpdk_init(int argc, char *argv[]);

#define MAX_PORT_NAME 9
struct dpdk_port_info{
	uint8_t port_id;
	char port_name[MAX_PORT_NAME];
	struct ether_addr *port_mac_addr;
};

#define MAX_DPDK_PORT_NUM 32
///extern struct dpdk_port_info dpdk_port[MAX_DPDK_PORT_NUM];

uint32_t get_dpdk_port_info(struct dpdk_port_info dpdk_port[]);
uint32_t mac_to_str(struct ether_addr* mac_addrs, char mac_str[]);
uint32_t get_eth_name_by_hwaddr(const char *hwaddr, char name[]);

uint32_t checkDPDKPortNameInSys(const char *name);

uint32_t cmd_print_dpdkports();
#endif
