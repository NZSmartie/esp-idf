#include "lwip/ip.h"

/**
 * Source based IPv4 routing hook function. This function works only
 * when destination IP is broadcast IP.
 */
struct netif * ESP_IRAM_ATTR
ip4_route_src(const ip4_addr_t *src, const ip4_addr_t *dest)
{
  struct netif *netif = NULL;

  /* destination IP is broadcast IP? */
  if ((src != NULL) && (dest->addr == IPADDR_BROADCAST)) {
    /* iterate through netifs */
    for (netif = netif_list; netif != NULL; netif = netif->next) {
      /* is the netif up, does it have a link and a valid address? */
      if (netif_is_up(netif) && netif_is_link_up(netif) && !ip4_addr_isany_val(*netif_ip4_addr(netif))) {
        /* source IP matches? */
        if (ip4_addr_cmp(src, netif_ip4_addr(netif))) {
          /* return netif on which to forward IP packet */
          return netif;
        }
      }
    }
  }
  return netif;
}