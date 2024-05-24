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
 * @file dhcp4cApi.h
 * @brief Defines the public interface for the RDK-Broadband DHCPv4 Client HAL.
 *
 * This header includes function prototypes, data structures, and constants used to manage
 * DHCPv4 client operations on cable modems.
 */
#ifndef _DHCP4_CLIENT_API_
#define _DHCP4_CLIENT_API_

/**
 * @defgroup DHCPV4C_HAL DHCPV4C HAL
 *
 * DHCPv4C HAL is used for the RDK-B DHCPv4 Client Status abstraction layer.
 *
 * @defgroup DHCPV4C_HAL_TYPES  DHCPV4C HAL Data Types
 * @ingroup  DHCPV4C_HAL
 *
 * @defgroup DHCPV4C_HAL_APIS   DHCPV4C HAL APIs
 * @ingroup  DHCPV4C_HAL
 *
 **/

/**
 * @addtogroup DHCPV4C_HAL_TYPES
 * @{
 */

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/
/**
 * @brief Represents the information for the DHCP client.
 *
 * This enumeration contains the different information used in DHCP client such as lease time, 
 * configuration attempts, interface name, FSM state and server information.
 */
/** Represents the information for the DHCPv4 client. */
enum DHCPC_CMD {
    DHCPC_CMD_LEASE_TIME,             /*!< Lease time obtained from the DHCP server. */
    DHCPC_CMD_LEASE_TIME_REMAIN,      /*!< Remaining lease time. */
    DHCPC_CMD_RENEW_TIME_REMAIN,      /*!< Remaining time for lease renewal. */
    DHCPC_CMD_REBIND_TIME_REMAIN,     /*!< Remaining time for rebinding. */
    DHCPC_CMD_CONFIG_ATTEMPTS,        /*!< Number of configuration attempts. */
    DHCPC_CMD_GET_IFNAME,             /*!< Interface name associated with the DHCP client. */
    DHCPC_CMD_FSM_STATE,              /*!< DHCP client's FSM state. */
    DHCPC_CMD_IP_ADDR,                /*!< IP address obtained from the server. */
    DHCPC_CMD_IP_MASK,                /*!< Subnet mask obtained from the server. */
    DHCPC_CMD_ROUTERS,                /*!< List of routers obtained from the server. */
    DHCPC_CMD_DNS_SVRS,               /*!< List of DNS servers obtained from the server. */
    DHCPC_CMD_DHCP_SVR,               /*!< IP addresses of the DHCP servers. */
    DHCPC_CMD_MAX                     /*!< Maximum value of the elements (not used). */
};


/**
 * @brief Represents the different types of modules in the DHCP client.
 *
 * This enumeration contains modules which defines embedded cable modem, router related functionality,
 * embedded multimedia terminal adapter. 
 */
/*!< Represents the different modules within the DHCPv4 client. */
enum DHCPC_MODULE{
    DHCPC_ECM,      /*!< Embedded Cable Modem (ECM) module. */
    DHCPC_EROUTER,  /*!< Router module. */
    DHCPC_EMTA      /*!< Embedded Multimedia Terminal Adapter (eMTA) module. */
};

#define MAX_IPV4_ADDR_LIST_NUMBER        4  //!< Maximum number of IPv4 addresses in the list  

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/**
 * @brief Represents IPv4 addresses.
 *
 * Holds information of the list of IPv4 addresses that are used by the specific server. 
 */
/**
 * @brief Represents a list of IPv4 addresses.
 */
typedef struct {
    int number; /*!< Number of IPv4 addresses in the list. */
    unsigned int addrList[MAX_IPV4_ADDR_LIST_NUMBER];  /*!< Array storing the IPv4 addresses (e.g., "192.168.0.1"). */

} ipv4AddrList_t;

/** @} */  //END OF GROUP DHCPV4C_HAL_TYPES

/**
 * @addtogroup DHCPV4C_HAL_APIS
 * @{
 */

/*
 * TODO (Error Handling Enhancement - DHCPv4 Client HAL):
 *   - Replace generic `RETURN_ERR` with a more descriptive error code enumeration.
 *   - Define specific error codes to pinpoint various failure scenarios, including:
 *       - Invalid input parameters (e.g., null pointers, invalid interface names)
 *       - DHCP server communication errors (e.g., timeout, invalid responses)
 *       - Network connectivity issues
 *       - Resource allocation failures (e.g., out-of-memory)
 *       - Internal errors within the HAL
 *   - Document the new error codes thoroughly in the header file and any relevant guides.
 */

/**
 * @brief Retrieves the E-Router's offered DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the lease time in seconds (max 604800).
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure.
 */
int dhcp4c_get_ert_lease_time(unsigned int *pValue);

/**
 * @brief Retrieves the E-Router's remaining DHCP lease time.
 * 
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining lease time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_remain_lease_time(unsigned int *pValue);

/**
 * @brief Retrieves the E-Router's remaining DHCP lease renewal time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining renewal time in seconds.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_remain_renew_time(unsigned int *pValue);

/**
 * @brief Retrieves the E-Router's remaining DHCP lease rebind time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining rebind time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_remain_rebind_time(unsigned int *pValue);

/**
 * @brief Retrieves the number of configuration attempts made by the E-Router.
 *
 * @param[out] pValue - Pointer to an integer where the configuration attempt count will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_config_attempts(int *pValue);

/**
* @brief Gets the E-Router Interface Name.
*
* @param[out] pName It is a 64 byte character array that provides the interface name.
*                   \n It is vendor specific.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS which is 0 if successful.
* @retval STATUS_FAILURE which is -1 if any error is detected
*
*
* 
*
*
*/
int dhcp4c_get_ert_ifname(char *pName);

/**
 * @brief Retrieves the E-Router's DHCP client state.
 *
 * @param[out] pValue - Pointer to an integer where the DHCP client state will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * @note Possible values for `pValue`:
 *  - 1: RELEASED or INIT_REBOOT
 *  - 2: INIT_SELECTING
 *  - 3: REQUESTING
 *  - 4: REBINDING
 *  - 5: BOUND
 *  - 6: RENEWING or RENEW_REQUESTED
 *
 * TODO: Consider changing `pValue` to a `DhcpClientState` enum type for improved type safety and readability.
 */
int dhcp4c_get_ert_fsm_state(int *pValue);

/**
 * @brief Retrieves the IP address of the E-Router interface.
 * 
 * This function retrieves the IPv4 address currently assigned to the E-Router interface.
 *
 * @param[out] pValue - Pointer to an unsigned integer variable where the IP address will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_ip_addr(unsigned int *pValue);

/**
 * @brief Retrieves the subnet mask of the E-Router interface.
 * 
 * @param[out] pValue - Pointer to an unsigned integer variable where the subnet mask will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_mask(unsigned int *pValue);

/**
 * @brief Retrieves the E-Router's gateway IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer variable where the gateway IP address will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_gw(unsigned int *pValue);

/**
 * @brief Retrieves the E-Router's list of DNS servers.
 *
 * @param[out] pList - Pointer to an `ipv4AddrList_t` structure to store the list of DNS servers.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_dns_svrs(ipv4AddrList_t *pList);

/**
 * @brief Retrieves the IP address of the E-Router's DHCP server.
 *
 * This function fetches the IPv4 address of the DHCP server used by the E-Router.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the DHCP server's IP address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ert_dhcp_svr(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) offered DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer variable where the lease time (in seconds) will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_lease_time(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) remaining DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining lease time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_remain_lease_time(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) remaining DHCP lease renewal time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining renewal time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_remain_renew_time(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) remaining DHCP lease rebind time.
 *
 * @param[out] pValue - Pointer to an unsigned integer variable where the remaining rebind time will be stored (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_remain_rebind_time(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) number of DHCP configuration attempts.
 *
 * @param[out] pValue - Pointer to an integer where the configuration attempt count will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_config_attempts(int *pValue);

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
int dhcp4c_get_ecm_ifname(char *pName);

/**
 * @brief Retrieves the ECM's DHCP client state.
 *
 * This function retrieves the current state of the DHCP client associated with the Embedded Cable Modem (ECM).
 *
 * @param[out] pValue - Pointer to an integer where the DHCP client state will be stored.
 *  @see `enum DHCPC_CMD` for possible values.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 * TODO: Consider returning a `DHCPClientState` enum instead of an integer for improved type safety and clarity.
 */
int dhcp4c_get_ecm_fsm_state(int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the ECM's IPv4 address.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 */
int dhcp4c_get_ecm_ip_addr(unsigned int *pValue);

/**
 * @brief Retrieves the subnet mask of the ECM (Embedded Cable Modem) interface.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the subnet mask.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_mask(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) gateway IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer variable where the gateway IP address will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_gw(unsigned int *pValue);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) list of DNS servers.
 *
 * @param[out] pList - Pointer to an `ipv4AddrList_t` structure to store the list of DNS servers.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_ecm_dns_svrs(ipv4AddrList_t *pList);

/**
 * @brief Retrieves the ECM's (Embedded Cable Modem) DHCP server IP address.
 *
 * @param[out] pValue - Pointer to an unsigned integer variable where the DHCP server's IPv4 address will be stored.
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 *
 */
int dhcp4c_get_ecm_dhcp_svr(unsigned int *pValue);

/**
 * @brief Retrieves the eMTA's remaining DHCP lease time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining lease time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_emta_remain_lease_time(unsigned int *pValue);

/**
 * @brief Retrieves the eMTA's remaining DHCP lease renewal time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining renewal time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_emta_remain_renew_time(unsigned int *pValue);

/**
 * @brief Retrieves the eMTA's (Embedded Multimedia Terminal Adapter) remaining DHCP lease rebind time.
 *
 * @param[out] pValue - Pointer to an unsigned integer to store the remaining rebind time (in seconds).
 *
 * @returns Status of the operation:
 * @retval STATUS_SUCCESS - On success.
 * @retval STATUS_FAILURE - On failure (e.g., invalid pointer, retrieval error).
 */
int dhcp4c_get_emta_remain_rebind_time(unsigned int *pValue);

/** @} */  //END OF GROUP DHCPV4C_HAL_APIS

#endif
