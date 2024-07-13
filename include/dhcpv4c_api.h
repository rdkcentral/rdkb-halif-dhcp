/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**
 * @file dhcp4c_api.h
 * @brief Defines the public interface for the RDK-Broadband DHCPv4 Client HAL.
 */

#ifndef __DHCPV4_CLIENT_API_H__
#define __DHCPV4_CLIENT_API_H__


#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef BOOL
#define BOOL  unsigned char
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS     0
#endif

#ifndef STATUS_FAILURE
#define STATUS_FAILURE     -1
#endif

/**
 * @addtogroup DHCPV4C_HAL_TYPES
 * @{
 */
#define DHCPV4_MAX_IPV4_ADDRS   4

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/** Represents a list of IPv4 addresses. */
typedef struct {
    INT  numAddresses;  /*!< Number of IPv4 addresses in the list. */
    UINT addresses[DHCPV4_MAX_IPV4_ADDRS];  /*!< Array storing IPv4 addresses (e.g., "192.168.0.1"). */ 
} dhcpv4c_ip_list_t;
/** @} */  //END OF GROUP DHCPV4C_HAL_TYPES

/**
 * @addtogroup DHCPV4C_HAL_APIS
 * @{
 */

/**********************************************************************************
 *
 *  DHCPV4-Client Subsystem level function prototypes
 *
**********************************************************************************/

/*
 * TODO (DHCPv4 Client HAL Enhancements):
 *   - Expand API Functionality: Consider adding functions to handle specific DHCPv4 options or to provide more granular control over the DHCP client behavior.
 *   - Error Code Refinement: Review the existing `DHCPC_ERROR_t` enum to ensure it covers all potential error scenarios and consider adding more specific codes for common errors.
 *   - Additional Events:  Investigate whether adding callbacks for other DHCPv4 events (e.g., lease expiration warning, IP address conflict) would be beneficial to clients.
 *   - IPv6 Support:  Plan for future support by adding similar functions and structures for DHCPv6.
 */


/**
 * @brief Retrieves the E-Router's offered DHCP lease time (in seconds).
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the lease time.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ert_lease_time(UINT *pValue);

/**
 * @brief Retrieves the E-Router's remaining DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining lease time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ert_remain_lease_time(UINT *pValue);

/**
 * @brief Retrieves the E-Router's remaining DHCP lease renewal time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining renewal time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ert_remain_renew_time(UINT *pValue);

/**
 * @brief Retrieves the E-Router's remaining DHCP lease rebind time (in seconds).
 * 
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining rebind time.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ert_remain_rebind_time(UINT *pValue);

/**
 * @brief Retrieves the number of configuration attempts made by the E-Router.
 *
 * @param[out] pValue - Pointer to an integer where the configuration attempt count will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ert_config_attempts(INT *pValue);

/**
 * @brief Retrieves the E-Router interface name.
 *
 * This function populates the provided buffer with the name of the E-Router interface.
 *
 * @param[out] pName - Buffer (at least 64 bytes) to store the E-Router interface name (vendor-specific).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., null pointer, retrieval error).
 */
INT dhcpv4c_get_ert_ifname(CHAR *pName);

/**
 * @brief Retrieves the E-Router's DHCP client state.
 *
 * This function gets the current state of the DHCP client associated with the E-Router.
 *
 * @param[out] pValue - Pointer to an integer where the DHCP client state will be stored.
 *  @see `_COSA_DML_DHCPC_STATUS` for possible values.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 * 
 * TODO: Update `pValue` type to `_COSA_DML_DHCPC_STATUS` for type safety and clarity.
 */
INT dhcpv4c_get_ert_fsm_state(INT *pValue);

/**
 * @brief Retrieves the IP address of the E-Router interface.
 *
 * This function gets the IPv4 address currently assigned to the E-Router interface.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the retrieved IPv4 address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented.
 * TODO: Consider using a more appropriate data type for `pValue` to store the IPv4 address.
 */
INT dhcpv4c_get_ert_ip_addr(UINT *pValue);

/**
 * @brief Retrieves the subnet mask of the E-Router interface.
 * 
 * @param[out] pValue - Pointer to an unsigned integer to store the subnet mask.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * TODO: Consider using a more appropriate data type for `pValue` to store the subnet mask.
 */
INT dhcpv4c_get_ert_mask(UINT *pValue);

/**
 * @brief Retrieves the IP address of the E-Router's gateway.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the gateway IP address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented. 
 *
 * TODO: Consider using a more appropriate data type for `pValue` to store the IPv4 address.
 */
INT dhcpv4c_get_ert_gw(UINT *pValue);

/**
 * @brief Retrieves the list of DNS servers associated with the E-Router.
 *
 * @param[out] pList - Pointer to a `dhcpv4c_ip_list_t` structure to store the list of DNS server IP addresses.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ert_dns_svrs(dhcpv4c_ip_list_t *pList);

/**
 * @brief Retrieves the E-Router's DHCP server IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the DHCP server's IPv4 address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented. 
 *
 * TODO: Consider using a more appropriate data type for `pValue` to store the IPv4 address.
 */
INT dhcpv4c_get_ert_dhcp_svr(UINT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) offered DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the lease time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ecm_lease_time(UINT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) remaining DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining lease time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ecm_remain_lease_time(UINT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) remaining DHCP lease renewal time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining renewal time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ecm_remain_renew_time(UINT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) remaining DHCP lease rebind time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining rebind time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ecm_remain_rebind_time(UINT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) number of DHCP configuration attempts.
 *
 * @param[out] pValue - Pointer to an integer where the configuration attempt count will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_ecm_config_attempts(INT *pValue);

/**
 * @brief Retrieves the ECM (Embedded Cable Modem) interface name.
 *
 * This function populates the provided buffer with the name of the ECM interface.
 *
 * @param[out] pName - Buffer (at least 64 bytes) to store the ECM interface name (vendor-specific).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., null pointer, retrieval error).
 */
INT dhcpv4c_get_ecm_ifname(CHAR *pName);

/**
 * @brief Retrieves the ECM's DHCP client state.
 *
 * This function gets the current state of the DHCP client associated with the Embedded Cable Modem (ECM).
 *
 * @param[out] pValue - Pointer to an integer where the DHCP client state will be stored.
 *  See `_COSA_DML_DHCPC_STATUS` for possible values.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 * 
 * TODO: Update `pValue` type to `_COSA_DML_DHCPC_STATUS` for type safety and clarity.
 */
INT dhcpv4c_get_ecm_fsm_state(INT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the ECM's IPv4 address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented. 
 *
 * TODO: Consider using a more appropriate data type for `pValue` to store the IPv4 address.
 */
INT dhcpv4c_get_ecm_ip_addr(UINT *pValue);

/**
 * @brief Retrieves the subnet mask of the ECM (Embedded Cable Modem) interface.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the subnet mask.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 * 
 * TODO: Consider using a more appropriate data type for `pValue` to store the subnet mask.
 */
INT dhcpv4c_get_ecm_mask(UINT *pValue);

/**
 * @brief Retrieves the subnet mask of the ECM (Embedded Cable Modem) interface.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the subnet mask.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 * 
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented. 
 * 
 * TODO: Consider using a more appropriate data type for `pValue` to store the subnet mask.
 */
INT dhcpv4c_get_ecm_gw(UINT *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) list of DNS servers.
 *
 * @param[out] pList - Pointer to a `dhcpv4c_ip_list_t` structure to store the list of DNS server IP addresses.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 * 
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented.
 */
INT dhcpv4c_get_ecm_dns_svrs(dhcpv4c_ip_list_t *pList);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) DHCP server IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the DHCP server's IPv4 address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * @see ipv4AddrList_t  For a description of how IPv4 addresses are represented. 
 *
 * TODO: Consider using a more appropriate data type for `pValue` to store the IPv4 address.
 */
INT dhcpv4c_get_ecm_dhcp_svr(UINT *pValue);

/**
 * @brief Retrieves the eMTA's (Embedded Multimedia Terminal Adapter) remaining DHCP lease time (in seconds).
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining lease time.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_emta_remain_lease_time(UINT *pValue);

/**
 * @brief Retrieves the eMTA's (Embedded Multimedia Terminal Adapter) remaining DHCP lease renewal time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining renewal time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_emta_remain_renew_time(UINT *pValue);

/**
 * @brief Retrieves the eMTA's (Embedded Multimedia Terminal Adapter) remaining DHCP lease rebind time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining rebind time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
INT dhcpv4c_get_emta_remain_rebind_time(UINT *pValue);

/** @} */  //END OF GROUP DHCPV4C_HAL_APIS
#endif
